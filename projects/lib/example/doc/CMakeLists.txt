# -- Configure Doxygen

set(DOXYGEN_PROJECT_NAME     ${PROJECT_NAME})
set(DOXYGEN_PROJECT_VERSION  ${PROJECT_VERSION})
set(DOXYGEN_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/doc/${PROJECT_NAME}/doxygen)
set(DOXYGEN_INCLUDE_PATH     "")
set(DOXYGEN_INPUT            "${PROJECT_SOURCE_DIR}/include, ${PROJECT_SOURCE_DIR}/src")

configure_file(example.doxygen.in ${CMAKE_CURRENT_BINARY_DIR}/example.doxygen)

# -- Configure Sphinx

set(SPHINX_PROJECT          ${PROJECT_NAME})
set(SPHINX_YEAR             2024)
set(SPHINX_AUTHOR           "Vladimir Novikov")
set(SPHINX_VERSION          ${PROJECT_VERSION})
set(SPHINX_RELEASE          "stable")
set(SPHINX_TEMPLATES_PATH   ${CMAKE_CURRENT_SOURCE_DIR}/_templates)
set(SPHINX_HTML_STATIC_PATH ${CMAKE_CURRENT_SOURCE_DIR}/_static)

set(BREATHE_PROJECT "")
string(TOLOWER "lib${SPHINX_PROJECT}" BREATHE_PROJECT)
set(BREATHE_PROJECT_PATH    ${DOXYGEN_OUTPUT_DIRECTORY}/xml)

configure_file(conf.py.in ${CMAKE_CURRENT_BINARY_DIR}/conf.py)

# -- Copy docs resources to build dir

configure_file(index.rst ${CMAKE_CURRENT_BINARY_DIR}/index.rst COPYONLY)

# -- TARGET: Documentation

add_custom_target(${PROJECT_NAME}Docs
  DEPENDS index.rst ${CMAKE_CURRENT_BINARY_DIR}/conf.py ${CMAKE_CURRENT_BINARY_DIR}/example.doxygen
  WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}"
  COMMAND doxygen ${CMAKE_CURRENT_BINARY_DIR}/example.doxygen
  COMMAND sphinx-build "${CMAKE_CURRENT_BINARY_DIR}" "${CMAKE_BINARY_DIR}/doc/${PROJECT_NAME}"
  VERBATIM)
