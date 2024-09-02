cmake_minimum_required(VERSION 3.12..3.29)

project(glfwpp VERSION 3.4 LANGUAGES CXX)

option(BUILD_TESTING OFF)

add_library(${PROJECT_NAME} INTERFACE)
add_library(${PROJECT_NAME}::${PROJECT_NAME} ALIAS ${PROJECT_NAME})
target_include_directories(${PROJECT_NAME} INTERFACE ${PROJECT_SOURCE_DIR}/interface)
target_link_libraries(${PROJECT_NAME} INTERFACE glfw glad Boost::signals2)
target_compile_definitions(${PROJECT_NAME} INTERFACE GLFW_INCLUDE_NONE)

add_library(GlfwPlusPlus)
target_sources(GlfwPlusPlus PRIVATE src/glfw.cpp)
add_library(glfw::glfw ALIAS GlfwPlusPlus)
target_include_directories(GlfwPlusPlus PUBLIC ${PROJECT_SOURCE_DIR}/include)
target_link_libraries(GlfwPlusPlus PUBLIC glfw)
target_compile_definitions(GlfwPlusPlus PUBLIC GLFW_INCLUDE_NONE)

if (PROJECT_IS_TOP_LEVEL AND BUILD_TESTING)
  include(CTest)
endif()

if (BUILD_TESTING)
  add_subdirectory(tests)
endif()
