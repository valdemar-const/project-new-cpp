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

    w.make_current();
    glClearColor(0.5, 1.0, 0.5, 1.0);

    w.on_refresh.connect(
            [](glfw::Window &window) -> void
            {
                window.make_current();
                glClear(GL_COLOR_BUFFER_BIT);
                window.swap_buffers();
                glFinish();
            }
    );

    w.on_size.connect(
            [](glfw::Window &window, int width, int height) -> void
            {
                window.make_current();
                glClear(GL_COLOR_BUFFER_BIT);
            }
    );

    w.on_framebuffer_size.connect(
            [](glfw::Window &window, int width, int height) -> void
            {
                window.make_current();
                glViewport(0, 0, width, height);
            }
    );

    app.on_window_process.connect(
            [](glfw::App &app, glfw::App::Window_Id wid, glfw::Window &window) -> void
            {
                window.make_current();
                glClear(GL_COLOR_BUFFER_BIT);
            }
    );

    app.run();

    return EXIT_SUCCESS;
}
