find_program(EXEC_XGETTEXT xgettext)
find_program(EXEC_MSGINIT  msginit)
find_program(EXEC_MSGMERGE msgmerge)
find_program(EXEC_MSGFMT   msgfmt)

include(i18n/gettext_locale_codes.cmake)

file(GLOB_RECURSE PROJECT_SOURCES "${PROJECT_SOURCE_DIR}/*.cpp" "${PROJECT_SOURCE_DIR}/*.hpp")
message(STATUS "LocaleGenDir=${CMAKE_CURRENT_LIST_DIR}")

foreach(locale IN LISTS LOCALES_SUPPORTED)
  file(MAKE_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/${locale}/LC_MESSAGES)

  set(main_pot_file ${CMAKE_CURRENT_LIST_DIR}/${PROJECT_NAME}.pot)
  if (NOT EXISTS ${main_pot_file})
    message(STATUS "Locale template not exists. Create: ${main_pot_file}")
    execute_process(COMMAND ${EXEC_XGETTEXT} --from-code=UTF-8 --output=${main_pot_file} --keyword=_ ${PROJECT_SOURCES})
  endif()

  set(locale_file ${CMAKE_CURRENT_LIST_DIR}/${locale}/LC_MESSAGES/${PROJECT_NAME}.po)
  if (NOT EXISTS ${locale_file})
    message(STATUS "Locale ${locale} not exists. Create: ${${locale_file}}")
    execute_process(COMMAND ${EXEC_MSGINIT} --input=${main_pot_file} --output-file=${locale_file} --locale=${locale} --no-translator)
  endif()

  set(locale_destination "$<TARGET_FILE_DIR:${PROJECT_NAME}>/resources/i18n/${locale}/LC_MESSAGES/${PROJECT_NAME}.mo")
  add_custom_command(TARGET ${PROJECT_NAME}
    POST_BUILD
      COMMAND ${EXEC_XGETTEXT} --from-code=UTF-8 --output=${main_pot_file} --keyword=_ ${PROJECT_SOURCES}
      COMMAND ${EXEC_MSGMERGE} --update --no-fuzzy-matching ${locale_file} ${main_pot_file}
      COMMAND ${EXEC_MSGFMT} ${locale_file} --output-file=${locale_destination}
    COMMENT "Generator locale files for ${PROJECT_NAME}"
    VERBATIM
    COMMAND_EXPAND_LISTS)
endforeach()
