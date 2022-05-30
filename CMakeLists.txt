cmake_minimum_required(VERSION 3.10.0)

project(kanki VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(TOOLS_SOURCE
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

subdirs(vendor/gtest)

enable_testing()

set(UNIT_SOURCE
    unit_tests/core/spacedlearner.cpp
    unit_tests/core/spacedestimator.cpp
)

add_executable(unit_tests)
target_include_directories(unit_tests
    PRIVATE src
    PRIVATE unit_tests)
target_sources(unit_tests
    PRIVATE ${TOOLS_SOURCE}
    PRIVATE ${MODEL_SOURCE}
    PRIVATE ${UNIT_SOURCE})
target_link_libraries(unit_tests gtest_main gmock_main)
include(GoogleTest)
gtest_discover_tests(unit_tests)
