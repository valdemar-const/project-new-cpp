#include <glfwpp/glfwpp.hpp>

#include <cstdlib>

int
main(
        int   argc,
        char *argv[]
)
{
    glfw::App app;
    app.create_window(640, 640, "ExampleGlfwPP");

    app.run();

    return EXIT_SUCCESS;
}
