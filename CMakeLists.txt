cmake_minimum_required(VERSION 3.21...3.29)

# -- Toplevel Project

project(NewProject
  VERSION   0.0.0.0
  LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD   20)
set(CMAKE_CXX_EXTENSIONS OFF)

# -- Build guard

if(PROJECT_SOURCE_DIR STREQUAL PROJECT_BINARY_DIR)
  message(FATAL_ERROR "In-source builds not allowed. Please make a new directory (called a build directory) and run CMake from there.")
endif()

# -- Configure CPM

if(NOT DEFINED CPM_SOURCE_CACHE)
  set(CPM_SOURCE_CACHE ${PROJECT_SOURCE_DIR}/3rdparty/cpm_cache CACHE STRING "")
endif()

set(CPM_DOWNLOAD_ALL                ON CACHE BOOL "")
set(CPM_USE_NAMED_CACHE_DIRECTORIES ON CACHE BOOL "")

# -- Best dependency manager

include(cmake/CPM.cmake)
include(cmake/fetch_project_3rdparty.cmake)

# -- Enable testing

include(CTest)

# -- Subprojects

add_subdirectory(projects/lib/example)
add_subdirectory(projects/lib/glfwpp)
add_subdirectory(projects/bin/example-cli)
add_subdirectory(projects/bin/example-wx)
add_subdirectory(projects/bin/example-glfw)
