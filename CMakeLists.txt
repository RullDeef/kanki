cmake_minimum_required(VERSION 3.10.0)

project(kanki VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(TOOLS_SOURCE
    src/tools/convertor.cpp
    src/tools/logger.cpp
)

set(MODEL_SOURCE
    src/model/card.cpp
    src/model/deck.cpp
    src/model/collection.cpp
    src/model/snapshot.cpp
    src/model/session.cpp

    src/core/spacedlearner.cpp
    src/core/spacedestimator.cpp
    src/core/collectionmanager.cpp
    src/core/sessionmanager.cpp
    src/core/editorcontroller.cpp
    src/core/learnercontroller.cpp
)

set(REPO_SOURCE
    src/dto/collectionparser.cpp
    src/dto/collectionbuilder.cpp
    src/dto/sessionparser.cpp
    src/dto/sessionbuilder.cpp
    
    src/db/filereader.cpp
    src/db/filewriter.cpp
    src/db/filedtoiofactory.cpp
    src/db/filecollectionrepo.cpp
    src/db/filesessionrepo.cpp
)

set(VIEW_SOURCE
    src/view/convertor.cpp
    src/view/editoradapter.cpp
    src/view/learneradapter.cpp
)

set(CLI_SOURCE
    src/cli/view/editorview.cpp
    src/cli/view/learnerview.cpp
    src/cli/menu.cpp
    src/cli/application.cpp
)

subdirs(vendor/gtest)

enable_testing()

set(UNIT_SOURCE
    unit_tests/core/spacedlearner.cpp
    unit_tests/core/spacedestimator.cpp

    unit_tests/db/filecollectionrepo.cpp
)

add_executable(unit_tests)
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

add_executable(kanki_cli src/main.cpp)
target_include_directories(kanki_cli PRIVATE src)
target_sources(kanki_cli
    PRIVATE ${TOOLS_SOURCE}
    PRIVATE ${MODEL_SOURCE}
    PRIVATE ${REPO_SOURCE}
    PRIVATE ${VIEW_SOURCE}
    PRIVATE ${CLI_SOURCE}
)
