cmake_minimum_required(VERSION 3.12..3.29)

project(glmeta VERSION 1.0 LANGUAGES CXX)

option(BUILD_TESTING OFF)

add_library(${PROJECT_NAME} INTERFACE)
# add_library(${PROJECT_NAME}::${PROJECT_NAME} ALIAS ${PROJECT_NAME})
target_include_directories(${PROJECT_NAME} INTERFACE ${PROJECT_SOURCE_DIR}/include)

if (PROJECT_IS_TOP_LEVEL AND BUILD_TESTING)
  include(CTest)
endif()

if (BUILD_TESTING)
  add_subdirectory(tests)
endif()
