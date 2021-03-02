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

macro(configure_msvc_runtime)
  if(MSVC)

    # Default to statically-linked runtime.
    if("${MSVC_RUNTIME}" STREQUAL "")
      set(MSVC_RUNTIME "static")
    endif()

    # Set compiler options.
    set(variables
      CMAKE_C_FLAGS_DEBUG
      CMAKE_C_FLAGS_MINSIZEREL
      CMAKE_C_FLAGS_RELEASE
      CMAKE_C_FLAGS_RELWITHDEBINFO
      CMAKE_CXX_FLAGS_DEBUG
      CMAKE_CXX_FLAGS_MINSIZEREL
      CMAKE_CXX_FLAGS_RELEASE
      CMAKE_CXX_FLAGS_RELWITHDEBINFO
    )
    if(${MSVC_RUNTIME} STREQUAL "static")
      message(STATUS
        "MSVC -> forcing use of statically-linked runtime."
      )
      foreach(variable ${variables})
        if(${variable} MATCHES "/MD")
          string(REGEX REPLACE "/MD" "/MT" ${variable} "${${variable}}")
        endif()
      endforeach()
    else()
      message(STATUS
        "MSVC -> forcing use of dynamically-linked runtime."
      )
      foreach(variable ${variables})
        if(${variable} MATCHES "/MT")
          string(REGEX REPLACE "/MT" "/MD" ${variable} "${${variable}}")
        endif()
      endforeach()
    endif()
  endif()
endmacro()

configure_msvc_runtime()

add_definitions(-DPROJECT_VERSION="${PROJECT_VERSION}")
add_definitions(-DPROJECT_GIT="${PROJECT_GIT}")
add_executable(scard main.cpp)
target_link_libraries(scard ${SCARD})
