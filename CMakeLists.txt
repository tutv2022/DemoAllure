cmake_minimum_required(VERSION 3.14)
project(DemoAllureProject CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Include directories
include_directories(${CMAKE_SOURCE_DIR}/src)
include_directories(${CMAKE_SOURCE_DIR}/include)

# Source files
set(SOURCES
    src/Calculator.cpp
    src/StringOperations.cpp
)

# Create library
add_library(DemoAllureProjectLib ${SOURCES})

# GoogleTest - Try to find system-installed version first
find_package(GTest QUIET)

if(GTest_FOUND)
    message(STATUS "Using system-installed GoogleTest")
else()
    message(STATUS "GoogleTest not found in system, downloading via FetchContent...")
    include(FetchContent)
    FetchContent_Declare(
      googletest
      URL https://github.com/google/googletest/archive/03597a01ee50ed33e9fd7189c2b4b0c8b8e2c4e0.zip
    )
    # For Windows: Prevent overriding the parent project's compiler/linker settings
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
    FetchContent_MakeAvailable(googletest)
endif()

# Test executable
add_executable(
    DemoAllureProjectTests
    tests/CalculatorTests.cpp
    tests/StringOperationTests.cpp
    tests/main.cpp
)

target_link_libraries(
    DemoAllureProjectTests
    PRIVATE
    DemoAllureProjectLib
    GTest::gtest
    GTest::gtest_main
)

# Enable testing
enable_testing()

# Add test
add_test(NAME DemoAllureProjectTests COMMAND DemoAllureProjectTests)

# Set output directory for test results
set_target_properties(DemoAllureProjectTests PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)

