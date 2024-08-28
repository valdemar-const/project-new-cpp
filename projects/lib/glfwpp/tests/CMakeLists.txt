add_executable(test_glfwpp_simple simple.cpp)
target_link_libraries(test_glfwpp_simple PRIVATE glfwpp::glfwpp)

add_test(NAME test-glfwpp-simple COMMAND test_glfwpp_simple)
