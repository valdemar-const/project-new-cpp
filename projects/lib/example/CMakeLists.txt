# -- TARGET: Example

project(Example VERSION 1.0 LANGUAGES CXX)

add_library(${PROJECT_NAME})
target_sources(${PROJECT_NAME}
  PRIVATE
    src/example.cpp)
target_include_directories(${PROJECT_NAME}
  PUBLIC  include
  PRIVATE ${CMAKE_BINARY_DIR}/lib/example)

set(EXAMPLE_VERSION ${PROJECT_VERSION})

configure_file(templates/config.h.in ${CMAKE_BINARY_DIR}/include/example/config/config.h @ONLY)

target_include_directories(${PROJECT_NAME}
  PUBLIC  ${CMAKE_BINARY_DIR}/include
  PRIVATE ${CMAKE_BINARY_DIR}/include/example/config)

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

add_library(example::example ALIAS ${PROJECT_NAME})

# -- Tests

add_subdirectory(tests)

# -- Docs

add_subdirectory(doc)
