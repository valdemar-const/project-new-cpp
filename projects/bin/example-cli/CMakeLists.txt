project(ExampleCli VERSION 1.0 LANGUAGES CXX)

add_executable(${PROJECT_NAME})
target_sources(${PROJECT_NAME}
  PRIVATE
    src/main.cpp)
target_link_libraries(${PROJECT_NAME} PRIVATE example::example)

string(TOLOWER ${PROJECT_NAME} OUTPUT_NAME)
set_target_properties(${PROJECT_NAME}
  PROPERTIES
    OUTPUT_NAME              ${OUTPUT_NAME}
    CXX_STANDARD             20
    CXX_STANDARD_REQUIRED    ON
    CXX_EXTENSIONS           OFF
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
    LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib
    ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
