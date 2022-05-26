cmake_minimum_required(VERSION 3.10.0)

project(kanki VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(CMAKE_AUTOUIC_SEARCH_PATHS src/ui src/ui/editor src/ui/learn)

set(TOOLS_SOURCE
    src/tools/logger.cpp
    # src/tools/convertor.cpp
)

set(MODEL_SOURCE
    src/model/card.cpp
    src/model/deck.cpp
    src/model/collection.cpp
    src/model/snapshot.cpp
    src/model/session.cpp

    # src/core/collectionmanager.cpp
)

set(REPO_SOURCE
    # src/db/filecollectionrepo.cpp
    # src/db/filesessionrepo.cpp
)

set(UI_SOURCE
    src/ui/editor/qteditorview.cpp
    src/ui/editor/deck_window.cpp
    src/ui/editor/card_window.cpp
    src/ui/editor/cardview_widget.cpp

    src/ui/learn/qtlearnerview.cpp
    src/ui/learn/learn_window.cpp
    src/ui/learn/info_window.cpp
    
    src/ui/main_window.cpp
)

find_package(Qt5 COMPONENTS Widgets REQUIRED)

add_executable(kanki src/main.cpp)
target_include_directories(kanki
    PRIVATE src
    PRIVATE /usr/include/x86_64-linux-gnu/qt5/QtWidgets/5.15.2/QtWidgets)
target_sources(kanki
    PRIVATE ${TOOLS_SOURCE}
    PRIVATE ${MODEL_SOURCE}
    PRIVATE ${REPO_SOURCE}
    PRIVATE ${UI_SOURCE})
target_link_libraries(kanki Qt5::Widgets)

subdirs(vendor)

enable_testing()

set(UNIT_SOURCE
    unit_tests/core/spacedlearner.cpp
)

add_executable(unit_tests unit_tests/main.cpp)
target_include_directories(unit_tests
    PRIVATE src
    PRIVATE unit_tests)
target_sources(unit_tests
    PRIVATE ${TOOLS_SOURCE}
    PRIVATE ${MODEL_SOURCE}
    PRIVATE ${REPO_SOURCE}
    PRIVATE ${UNIT_SOURCE})
target_link_libraries(unit_tests gtest_main gmock_main)
include(GoogleTest)
gtest_discover_tests(unit_tests)
