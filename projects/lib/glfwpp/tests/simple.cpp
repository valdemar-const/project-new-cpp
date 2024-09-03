#include <glfwpp/glfwpp.hpp>

#include <cstdlib>

int
main(
        int   argc,
        char *argv[]
)
{
    auto &app = glfw::glfw();
    app.create_window(640, 480, "GlfwPlusPlus");

    app.run();

    return EXIT_SUCCESS;
}
