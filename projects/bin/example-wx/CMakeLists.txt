project(ExampleWx VERSION 1.0 LANGUAGES CXX)

set(CFG_APP_NAME    ${PROJECT_NAME})
set(CFG_APP_VERSION ${PROJECT_VERSION})
configure_file(templates/config.h.in ${CMAKE_CURRENT_BINARY_DIR}/config/config.h)

add_executable(${PROJECT_NAME})
target_sources(${PROJECT_NAME}
  PRIVATE
    resources/example.rc
    src/AppExample.cpp
    src/FrameMain.cpp
    src/main.cpp)
target_link_libraries(${PROJECT_NAME} PRIVATE -static-libgcc -static-libstdc++)
target_link_libraries(${PROJECT_NAME} PRIVATE example::example wx::core wx::xrc)
target_include_directories(${PROJECT_NAME}
  PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    include
    ${CMAKE_CURRENT_BINARY_DIR}/config)

# gen translations

include(i18n/locale_gen.cmake)

# copy resources
message(STATUS "wxWidgets: ${wxWidgets_SOURCE_DIR}")
find_file(WX_TRANSLATION NAMES locale/ru.mo PATHS ${wxWidgets_SOURCE_DIR} NO_DEFAULT_PATH REQUIRED)

add_custom_command(TARGET ${PROJECT_NAME}
  PRE_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/resources/ui $<TARGET_FILE_DIR:${PROJECT_NAME}>/resources/ui
    COMMAND ${CMAKE_COMMAND} -E copy ${WX_TRANSLATION} "$<TARGET_FILE_DIR:${PROJECT_NAME}>/resources/i18n/ru/LC_MESSAGES/ru.mo")

# copy *.dll dependencies to target executable directory
if (CMAKE_IMPORT_LIBRARY_SUFFIX AND (BUILD_SHARED_LIBS OR wxBUILD_SHARED))
  add_custom_command(TARGET ${PROJECT_NAME}
    POST_BUILD
      COMMAND ${CMAKE_COMMAND} -E copy_if_different "$<TARGET_RUNTIME_DLLS:${PROJECT_NAME}>" "$<TARGET_FILE_DIR:${PROJECT_NAME}>"
      COMMAND_EXPAND_LISTS)
endif()

# configure output directories
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

# setting up windows specific manifest file
if (WIN32)
  target_sources(${PROJECT_NAME} PRIVATE resources/example.exe.manifest)
  set_target_properties(${PROJECT_NAME}
    PROPERTIES
      WIN32_EXECUTABLE ON)
endif()
