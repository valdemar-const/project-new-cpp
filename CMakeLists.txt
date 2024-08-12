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
CPMAddPackage(NAME PackageProject.cmake
  VERSION        1.11.2
  GIT_REPOSITORY "https://github.com/TheLartians/PackageProject.cmake"
  GIT_TAG        v1.11.2
  GIT_SHALLOW
  EXCLUDE_FROM_ALL)

CPMAddPackage(NAME wxWidgets
  VERSION          3.2.5
  URL              "https://github.com/wxWidgets/wxWidgets/releases/download/v3.2.5/wxWidgets-3.2.5.7z"
  URL_HASH         "SHA256=9efad97c9eac8be6ce2b71723027070987fd519860bdefde2cf6c438b3383f6d"
  # GIT_REPOSITORY   "https://github.com/wxWidgets/wxWidgets"
  # GIT_TAG          v3.2.5
  # GIT_SHALLOW
  EXCLUDE_FROM_ALL
  OPTIONS
    "wxBUILD_SHARED OFF"
    "wxUSE_STL      ON")

# -- Enable testing

include(CTest)

# -- Subprojects

add_subdirectory(projects/lib/example)
add_subdirectory(projects/bin/example-cli)
add_subdirectory(projects/bin/example-wx)
