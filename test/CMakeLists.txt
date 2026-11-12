cmake_minimum_required(VERSION 3.30 FATAL_ERROR)

project(cp-algorithms LANGUAGES CXX)

# generating snippets
set(SNIPPETS_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include/snippets)
find_package(Python3 3.10 REQUIRED COMPONENTS Interpreter)
execute_process(
    COMMAND
        ${Python3_EXECUTABLE}
        "${CMAKE_CURRENT_SOURCE_DIR}/scripts/extract_snippets.py"
        --src-dir=${CMAKE_CURRENT_SOURCE_DIR}/../src
        --target-dir=${SNIPPETS_DIR}
        --remove-prev-target-dir
    COMMAND_ERROR_IS_FATAL ANY
)

# loading googletest
include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG v1.17.0
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)
include(GoogleTest)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

file(GLOB_RECURSE SNIPPETS_SOURCES CONFIGURE_DEPENDS ${SNIPPETS_DIR}/*.h)
file(GLOB_RECURSE TEST_SOURCES CONFIGURE_DEPENDS src/test_*.cpp)

add_executable(main ${TEST_SOURCES} ${SNIPPETS_SOURCES})
target_link_libraries(main PRIVATE GTest::gtest_main GTest::gtest GTest::gmock)
target_include_directories(main PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)

enable_testing()
gtest_discover_tests(main)
