cmake_minimum_required(VERSION 3.5)

project(scard LANGUAGES CXX VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_library(SCARD NAME winscard REQUIRED)

find_package(Git REQUIRED)
execute_process(COMMAND "${GIT_EXECUTABLE}" describe --always --tags
    RESULT_VARIABLE PROJECT_RESULT
    OUTPUT_VARIABLE PROJECT_GIT
    ECHO_OUTPUT_VARIABLE
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    )
string(REGEX REPLACE "\n$" "" PROJECT_GIT "${PROJECT_GIT}")
message("Project VERSION ${PROJECT_VERSION}")
message("Project GIT     ${PROJECT_GIT}")
add_definitions(-DPROJECT_VERSION="${PROJECT_VERSION}")
add_definitions(-DPROJECT_GIT="${PROJECT_GIT}")
add_executable(scard main.cpp)
target_link_libraries(scard ${SCARD})
