cmake_minimum_required(VERSION 3.20)
project(aoc2025 CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Fetch Catch2 for testing
include(FetchContent)
FetchContent_Declare(
    Catch2
    GIT_REPOSITORY https://github.com/catchorg/Catch2.git
    GIT_TAG        v3.5.4
)
FetchContent_MakeAvailable(Catch2)

# Output directory
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Include directories
include_directories(${CMAKE_SOURCE_DIR}/include)

# Find all day source files (day*.cpp, excluding test files)
file(GLOB all_day_sources "src/day*.cpp")
list(FILTER all_day_sources EXCLUDE REGEX ".*_test\\.cpp$")
set(day_sources ${all_day_sources})

# Core sources
set(core_sources 
    src/main.cpp
    src/aoc2025.cpp
)

# All sources
set(all_sources ${core_sources} ${day_sources})

# Create main executable
add_executable(aoc2025 ${all_sources})

# Set C++ compiler options
if(MSVC)
    target_compile_options(aoc2025 PRIVATE /W4 /permissive-)
else()
    target_compile_options(aoc2025 PRIVATE -Wall -Wextra -pedantic)
endif()

# Find all day test files (day*_test.cpp)
file(GLOB day_test_sources "src/day*_test.cpp")

# Create test executable with Catch2
add_executable(test_runner 
    src/test_runner.cpp
    src/aoc2025.cpp
    ${day_sources}
    ${day_test_sources}
)
set_target_properties(test_runner PROPERTIES WIN32_EXECUTABLE FALSE)

# Link Catch2 to test executable
target_link_libraries(test_runner PRIVATE Catch2::Catch2WithMain)

# Set Windows subsystem to console (not GUI) - must be after target creation
if(WIN32 AND MSVC)
    target_link_options(test_runner PRIVATE "/SUBSYSTEM:CONSOLE" "/ENTRY:mainCRTStartup")
elseif(WIN32)
    # For MinGW/Clang on Windows - ensure console subsystem
    target_link_options(test_runner PRIVATE "-Wl,-subsystem,console")
endif()

# Set C++ compiler options for tests
if(MSVC)
    target_compile_options(test_runner PRIVATE /W4 /permissive-)
else()
    target_compile_options(test_runner PRIVATE -Wall -Wextra -pedantic)
endif()

include(CTest)
if(BUILD_TESTING)
    list(APPEND CMAKE_MODULE_PATH ${Catch2_SOURCE_DIR}/extras)
    include(Catch)
    catch_discover_tests(test_runner)
endif()

# Copy day directories (with data.txt files) to build directory
file(GLOB day_dirs RELATIVE ${CMAKE_SOURCE_DIR} "day*")
foreach(day_dir ${day_dirs})
    if(IS_DIRECTORY ${CMAKE_SOURCE_DIR}/${day_dir})
        file(COPY ${CMAKE_SOURCE_DIR}/${day_dir} DESTINATION ${CMAKE_BINARY_DIR})
    endif()
endforeach()

