project(ExampleWx VERSION 1.0 LANGUAGES CXX)

add_executable(${PROJECT_NAME})
target_sources(${PROJECT_NAME}
  PRIVATE
    resources/example.rc
    src/main.cpp)
target_link_libraries(${PROJECT_NAME} PRIVATE -static-libgcc -static-libstdc++)
target_link_libraries(${PROJECT_NAME} PRIVATE example::example wx::core wx::xrc)
target_include_directories(${PROJECT_NAME} PRIVATE .)

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

if (WIN32)
  target_sources(${PROJECT_NAME} PRIVATE resources/example.exe.manifest)
  set_target_properties(${PROJECT_NAME}
    PROPERTIES
      WIN32_EXECUTABLE ON)
endif()

configure_file(resources/ui/StartPage.xrc ${CMAKE_BINARY_DIR}/bin/resources/ui/StartPage.xrc COPYONLY)
