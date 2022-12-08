cmake_minimum_required(VERSION 3.10.0)

option(UUID_SYSTEM_GENERATOR ON)
add_subdirectory(vendor/stduuid)

option(REDIS_PLUS_PLUS_BUILD_SHARED OFF)
option(REDIS_PLUS_PLUS_USE_TLS ON)
add_subdirectory(vendor/redis-plus-plus)

project(kanki VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt5 COMPONENTS Core Widgets REQUIRED)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(AUTOUIC_SEARCH_PATHS src/ui/qt)

set(TOOLS_SOURCE
    src/tools/convertor.cpp
    src/tools/logger.cpp
)

set(MODEL_SOURCE
    src/model/card.cpp
    src/model/deck.cpp
    src/model/deckcollection.cpp
    src/model/snapshot.cpp
    src/model/session.cpp

    src/core/spacedlearner.cpp
    src/core/spacedestimator.cpp
    src/core/collectionmanager.cpp
    src/core/sessionmanager.cpp
    src/core/editorcontroller.cpp
    src/core/learnercontroller.cpp
    src/core/iocontroller.cpp
)

set(REPO_SOURCE
    src/db/model/collectionparser.cpp
    src/db/model/collectionbuilder.cpp
    src/db/model/sessionparser.cpp
    src/db/model/sessionbuilder.cpp
    
    src/db/filereader.cpp
    src/db/filewriter.cpp
    src/db/filedtoiofactory.cpp
    src/db/filecollectionrepo.cpp
    src/db/filesessionrepo.cpp
    src/db/fileexporter.cpp
    src/db/fileimporter.cpp

    src/db/redis/rediscollectionrepo.cpp
)

set(VIEW_SOURCE
    src/ui/model/convertor.cpp
    src/ui/model/editoradapter.cpp
    src/ui/model/learneradapter.cpp
    src/ui/model/ioviewadapter.cpp
    
    src/ui/iuifactory.cpp
)

set(CLI_SOURCE
    src/ui/cli/editorview.cpp
    src/ui/cli/learnerview.cpp
    src/ui/cli/ioview.cpp
    src/ui/cli/menu.cpp
    src/ui/cli/application.cpp
    src/ui/cli/uifactory.cpp
)

set(QT_SOURCE
    src/ui/qt/qtuifactory.cpp
    src/ui/qt/main_window.cpp
    src/ui/qt/qtioview.cpp

    src/ui/qt/editor/card_window.cpp
    src/ui/qt/editor/cardview_widget.cpp
    src/ui/qt/editor/deck_window.cpp
    src/ui/qt/editor/qteditorview.cpp

    src/ui/qt/learn/info_window.cpp
    src/ui/qt/learn/learn_window.cpp
    src/ui/qt/learn/repeat_window.cpp
    src/ui/qt/learn/qtlearnerview.cpp
)

set(SOLUTION_SOURCE
    src/solution/solution.cpp
    src/solution/cfgsolution.cpp
)

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
    unit_tests/db/redis/rediscollectionrepo.cpp
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
target_link_libraries(unit_tests gtest_main gmock_main stduuid redis++)
include(GoogleTest)
gtest_discover_tests(unit_tests)

add_executable(kanki src/main.cpp)
target_link_libraries(kanki stduuid redis++ Qt5::Core Qt5::Widgets)

target_include_directories(kanki
    PRIVATE vendor/stduuid/include
    PRIVATE src)
target_sources(kanki
    PRIVATE ${TOOLS_SOURCE}
    PRIVATE ${MODEL_SOURCE}
    PRIVATE ${REPO_SOURCE}
    PRIVATE ${VIEW_SOURCE}
    PRIVATE ${CLI_SOURCE}
    PRIVATE ${QT_SOURCE}
    PRIVATE ${SOLUTION_SOURCE}
)
