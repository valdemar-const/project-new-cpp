#include <glfwpp/glfwpp.hpp>

#include <iostream>
#include <format>

#include <cstdlib>

int
main(
        int   argc,
        char *argv[]
)
{
    glfw::App app;
    auto     &w = app.create_window(640, 640, "ExampleGlfwPP");

    w.on_window_pos.connect(
            [](glfw::Window &w, int x, int y) -> void
            {
                std::cout << x << ":" << y << std::endl;
            }
    );

    app.run();

    return EXIT_SUCCESS;
}
