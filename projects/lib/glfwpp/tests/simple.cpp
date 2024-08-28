#include <glfwpp/glfwpp.hpp>

#include <cstdlib>

int
main(
        int   argc,
        char *argv[]
)
{
    glfw::App app;
    app.create_window(640, 480, "GlfwPlusPlus");
    app.create_window(640, 480, "GlfwPlusPlus");

    app.run();

    return EXIT_SUCCESS;
}
