add_executable(TestVersionString test_version_string.cpp)
target_link_libraries(TestVersionString PRIVATE example::example)

add_test(NAME test-version-string COMMAND TestVersionString)
