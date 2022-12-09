cmake_minimum_required(VERSION 3.10.0)

project(kanki VERSION 0.1.0 LANGUAGES CXX)

# ------------------------------ project options -----------------------------
option(BUILD_WITH_QT "Build kanki with Qt5 GUI" ON)
option(BUILD_WITH_REDIS "Build kanki with redis support" OFF)
option(BUILD_UNIT_TESTS "Build unit_tests target" ON)
# ----------------------------------------------------------------------------

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(UUID_SYSTEM_GENERATOR ON)
add_subdirectory(vendor/stduuid)

file(GLOB TOOLS_SOURCE src/tools/*.cpp)
file(GLOB MODEL_SOURCE src/model/*.cpp src/core/*.cpp)
file(GLOB REPO_SOURCE src/db/model/*.cpp src/db/file*.cpp)
file(GLOB VIEW_SOURCE src/ui/model/*.cpp src/ui/iuifactory.cpp)
file(GLOB CLI_SOURCE src/ui/cli/*.cpp)
file(GLOB SOLUTION_SOURCE src/solution/*.cpp)

if(BUILD_UNIT_TESTS)
    subdirs(vendor/gtest)
    enable_testing()

    set(UNIT_SOURCE
        unit_tests/builders/builder_base.cpp
        unit_tests/builders/cardbuilder.cpp
        unit_tests/builders/deckbuilder.cpp
        unit_tests/builders/collectionbuilder.cpp

        unit_tests/mock/db/dtoreader.cpp
        unit_tests/mock/db/dtowriter.cpp

        unit_tests/core/spacedlearner.cpp
        unit_tests/core/spacedestimator.cpp

        unit_tests/db/filecollectionrepo.cpp
    )

    add_executable(unit_tests)
    target_include_directories(unit_tests
        PRIVATE vendor/stduuid/include
        PRIVATE src
        PRIVATE unit_tests)
    target_sources(unit_tests
        PRIVATE ${TOOLS_SOURCE}
        PRIVATE ${MODEL_SOURCE}
        PRIVATE ${REPO_SOURCE}
        PRIVATE ${UNIT_SOURCE})

    target_link_libraries(unit_tests gtest_main gmock_main stduuid)
    include(GoogleTest)
    gtest_discover_tests(unit_tests)
endif()

add_executable(kanki src/main.cpp)
target_link_libraries(kanki stduuid)

target_include_directories(kanki
    PRIVATE vendor/stduuid/include
    PRIVATE src)
target_sources(kanki
    PRIVATE ${TOOLS_SOURCE}
    PRIVATE ${MODEL_SOURCE}
    PRIVATE ${REPO_SOURCE}
    PRIVATE ${VIEW_SOURCE}
    PRIVATE ${CLI_SOURCE}
    PRIVATE ${SOLUTION_SOURCE}
)

if(BUILD_WITH_QT)
    find_package(Qt5 REQUIRED COMPONENTS Core Widgets)
    set(CMAKE_AUTOMOC ON)
    set(CMAKE_AUTORCC ON)
    set(CMAKE_AUTOUIC ON)

    file(GLOB QT_SOURCE src/ui/qt/*.cpp src/ui/qt/**/*.cpp)
    file(GLOB QT_SOURCE_UI src/ui/qt/**/*.ui)
    qt5_wrap_ui(QT_SOURCE_UI ${QT_SOURCE_UI})

    qt5_wrap_cpp(QT_SOURCE_MOC src/ui/qt/main_window.hpp)
    qt5_wrap_cpp(QT_SOURCE_MOC src/ui/qt/learn/learn_window.hpp)
    qt5_wrap_cpp(QT_SOURCE_MOC src/ui/qt/learn/info_window.hpp)
    qt5_wrap_cpp(QT_SOURCE_MOC src/ui/qt/learn/repeat_window.hpp)
    qt5_wrap_cpp(QT_SOURCE_MOC src/ui/qt/editor/card_window.hpp)
    qt5_wrap_cpp(QT_SOURCE_MOC src/ui/qt/editor/cardview_widget.hpp)
    qt5_wrap_cpp(QT_SOURCE_MOC src/ui/qt/editor/deck_window.hpp)

    qt5_wrap_cpp(QT_SOURCE_MOC src/ui/qt/editor/qteditorview.hpp)
    qt5_wrap_cpp(QT_SOURCE_MOC src/ui/qt/learn/qtlearnerview.hpp)

    add_compile_definitions(USE_FEATURE_UI_QT)
    target_sources(kanki PRIVATE ${QT_SOURCE} ${QT_SOURCE_UI} ${QT_SOURCE_MOC})
    target_include_directories(kanki PRIVATE ${PROJECT_BINARY_DIR})
    target_link_libraries(kanki Qt5::Core Qt5::Widgets)
endif()

if(BUILD_WITH_REDIS)
    add_subdirectory(vendor/hiredis)

    option(REDIS_PLUS_PLUS_BUILD_SHARED OFF)
    option(REDIS_PLUS_PLUS_USE_TLS OFF)
    add_subdirectory(vendor/redis-plus-plus)
    set_target_properties(redis++_static PROPERTIES ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")

    add_compile_definitions(USE_FEATURE_DB_REDIS)

    set(REDIS_SOURCE src/db/redis/rediscollectionrepo.cpp)

    target_sources(kanki PRIVATE ${REDIS_SOURCE})
    target_link_libraries(kanki hiredis_static redis++_static)

    if(BUILD_UNIT_TESTS)
        target_sources(unit_tests PRIVATE ${REDIS_SOURCE})
        target_link_libraries(unit_tests hiredis_static redis++_static)
        target_include_directories(unit_tests
            PRIVATE vendor/redis-plus-plus/src/sw/redis++
            PRIVATE vendor/redis-plus-plus/src/sw/redis++/cxx17
            PRIVATE vendor/redis-plus-plus/src/sw/redis++/no_tls
        )
    endif()
endif()
