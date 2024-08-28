cmake_minimum_required(VERSION 3.12..3.29)

project(ExampleGlfwpp VERSION 0.1 LANGUAGES CXX)

add_executable(${PROJECT_NAME})
target_sources(${PROJECT_NAME}
	PRIVATE
		src/main.cpp)

target_link_libraries     (${PROJECT_NAME} PRIVATE glfwpp::glfwpp glm::glm tomlplusplus::tomlplusplus)
target_include_directories(${PROJECT_NAME} PRIVATE include)

add_custom_command(TARGET ${PROJECT_NAME}
  PRE_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/assets $<TARGET_FILE_DIR:${PROJECT_NAME}>/assets)

set_target_properties(${PROJECT_NAME}
  PROPERTIES
    CMAKE_CXX_STANDARD          20
    CMAKE_CXX_STANDARD_REQUIRED YES
    CMAKE_CXX_EXTENSIONS        NO
    RUNTIME_OUTPUT_DIRECTORY    ${CMAKE_BINARY_DIR}/bin
    LIBRARY_OUTPUT_DIRECTORY    ${CMAKE_BINARY_DIR}/lib
    ARCHIVE_OUTPUT_DIRECTORY    ${CMAKE_BINARY_DIR}/obj)
