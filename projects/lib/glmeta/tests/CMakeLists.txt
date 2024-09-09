add_executable(glmeta_example test.cpp)
target_link_libraries(glmeta_example PRIVATE glmeta)

add_test(NAME test_glmeta_simple COMMAND glmeta_example)
