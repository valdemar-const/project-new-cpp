cmake_minimum_required(VERSION 3.14...3.29)

# -- Toplevel Project

project(NewProject
  VERSION   0.0.0.0
  LANGUAGES CXX)

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

# -- Support installable packages
CPMAddPackage("gh:TheLartians/PackageProject.cmake@1.8.0")

# -- Enable testing

include(CTest)

# -- Subprojects

add_subdirectory(projects/lib/example)
add_subdirectory(projects/bin/example-cli)
