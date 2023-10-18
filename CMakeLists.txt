cmake_minimum_required(VERSION 3.10)


set(PROJECT_NAME DiscordMipsEmulator)

project(${PROJECT_NAME})

set(CMAKE_CXX_STANDARD 20)


find_package(Catch2 3 REQUIRED)
find_package(dpp REQUIRED)


set(SOURCE_DIR ${CMAKE_SOURCE_DIR}/src)
set(TEST_DIR ${CMAKE_SOURCE_DIR}/test)
set(OBJECT_DIR ${CMAKE_SOURCE_DIR}/obj)
set(INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include)
set(BUILD_DIR ${CMAKE_SOURCE_DIR}/build)

file(GLOB_RECURSE SOURCES ${SOURCE_DIR}/*.cpp)
message("Sources: ${SOURCES}\n")

add_executable(${PROJECT_NAME} ${SOURCES})

set_target_properties(${PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${BUILD_DIR})

target_include_directories(${PROJECT_NAME} PUBLIC ${SOURCE_DIR} ${INCLUDE_DIR})

find_library(DPP_LIBRARY dpp)
target_link_libraries(${PROJECT_NAME} PUBLIC ${DPP_LIBRARY})
target_link_libraries(${PROJECT_NAME} PRIVATE Catch2::Catch2)

target_compile_options(${PROJECT_NAME} PUBLIC -Wall -Wextra -Wpedantic -g)

include(CTest)
include(Catch)
#catch_discover_tests(${PROJECT_NAME})


