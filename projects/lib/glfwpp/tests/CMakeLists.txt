add_executable(test_glfwpp_simple simple.cpp)
target_link_libraries(test_glfwpp_simple PRIVATE tomlplusplus::tomlplusplus glfw::glfw glad::gl_core46_noext_gles_core30_noext_mx)

add_test(NAME test-glfwpp-simple COMMAND test_glfwpp_simple)
