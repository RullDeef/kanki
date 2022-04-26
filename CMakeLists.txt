cmake_minimum_required(VERSION 3.10.0)

project(kanki VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(CMAKE_AUTOUIC_SEARCH_PATHS src/ui)

set(TOOLS_SOURCE
    src/tools/logger.cpp
    src/tools/convertor.cpp
)

set(MODEL_SOURCE
    src/model/card.cpp
    src/model/deck.cpp
    src/model/collection.cpp
    src/model/cardsnapshot.cpp
    src/model/session.cpp

    src/viewapi/cardparams.cpp
    src/viewapi/deckparams.cpp
    src/viewapi/collectionparams.cpp

    src/core/collectionexporter.cpp
    src/core/modelmanager.cpp
    src/core/collectioncontroller.cpp
    src/core/deckcontroller.cpp
    src/core/cardcontroller.cpp
    src/core/controllerprovider.cpp

    src/core/spacedrepetionlearn.cpp
)

set(REPO_SOURCE
    src/db/filecollectionrepo.cpp
    src/db/filesessionrepo.cpp
    src/db/filerepofactory.cpp
)

set(UI_SOURCE
    src/ui/qtdeckview.cpp
    src/ui/qtcollectionview.cpp
    
    src/ui/main_window.cpp
    src/ui/deck_window.cpp
    src/ui/cardview_widget.cpp
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
add_executable(unit_tests unit_tests/main.cpp)
target_include_directories(unit_tests
    PRIVATE src
    PRIVATE unit_tests)
target_sources(unit_tests
    PRIVATE ${TOOLS_SOURCE}
    PRIVATE ${MODEL_SOURCE}
    PRIVATE ${REPO_SOURCE}
    unit_tests/core/spacedreptests.cpp)
target_link_libraries(unit_tests gtest_main gmock_main)
include(GoogleTest)
gtest_discover_tests(unit_tests)
