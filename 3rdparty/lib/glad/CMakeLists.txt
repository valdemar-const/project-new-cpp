cmake_minimum_required(VERSION 3.12..3.29)

project(GLAD VERSION 0.1.36 LANGUAGES C CXX)

add_library(glad INTERFACE)
target_include_directories(glad INTERFACE ${PROJECT_SOURCE_DIR}/include)
target_sources(glad INTERFACE ${PROJECT_SOURCE_DIR}/src/glad.c)
