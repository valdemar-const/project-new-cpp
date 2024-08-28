#include <Glfw_App.hpp>
#include <App.hpp>

#include <helpers.hpp>

#include <Shader_Program.hpp>
#include <Render_Target.hpp>

#include <iostream>
#include <filesystem>

void render();

void
error_clb(int error_code, const char *description)
{
}

void
monitor_clb(GLFWmonitor *monitor, int event)
{
}

void
joystic_clb(int jid, int event)
{
}

void
window_pos_clb(GLFWwindow *window, int xpos, int ypos)
{
}

void
window_size_clb(GLFWwindow *window, int width, int height)
{
}

void
window_close_clb(GLFWwindow *window)
{
}

void
window_refresh_clb(GLFWwindow *window)
{
    render();
    glfwSwapBuffers(window);
    glFinish();
}

void
window_focus_clb(GLFWwindow *window, int focused)
{
}

void
window_iconify_clb(GLFWwindow *window, int iconified)
{
}

void
window_maximize_clb(GLFWwindow *window, int maximized)
{
}

void
framebuffer_size_clb(
        GLFWwindow *window,
        int         width,
        int         height
)
{
    // int width, height;
    // glfwGetFramebufferSize(window, &width, &height);

    glViewport(0, 0, width, height);
}

void
window_content_scale_clb(GLFWwindow *window, float xscale, float yscale)
{
}

void
key_clb(
        GLFWwindow *window,
        int         key,
        int         scancode,
        int         action,
        int         mods
)
{
    if (GLFW_PRESS == action)
    {
        switch (key)
        {
        case GLFW_KEY_ESCAPE:
            glfwSetWindowShouldClose(window, true);
            break;

        case GLFW_KEY_W:
            app::render_state.toggle_wireframe = !app::render_state.toggle_wireframe;
            glPolygonMode(GL_FRONT_AND_BACK, (app::render_state.toggle_wireframe) ? GL_LINE : GL_FILL);
            app::render_state.is_need_redraw = true;
            break;
        }
    }
}

void
char_clb(GLFWwindow *window, unsigned int codepoint)
{
}

void
char_mods_clb(GLFWwindow *window, unsigned int codepoint, int mods)
{
}

void
mouse_button_clb(GLFWwindow *window, int button, int action, int mods)
{
}

void
cursor_pos_clb(GLFWwindow *window, double xpos, double ypos)
{
}

void
cursor_enter_clb(GLFWwindow *window, int entered)
{
}

void
scroll_clb(GLFWwindow *window, double xoffset, double yoffset)
{
}

void
drop_clb(GLFWwindow *window, int path_count, const char *paths[])
{
}

void
render()
{
    glClear(GL_COLOR_BUFFER_BIT);
    if (app::render_state.passthrough.get() && app::render_state.quad.get())
    {
        app::render_state.passthrough->use();
        app::render_state.quad->draw();
    }
}

void
main_loop_iter()
{
    glfwPollEvents();
    if (app::render_state.is_need_redraw)
    {
        render();
        app::render_state.is_need_redraw = false;
    }
    glfwSwapBuffers(app::render_state.window);
}

int
main(
        int   argc,
        char *argv[]
)
{
    using std::filesystem::path;

    assert(glfwInit());

    glfwWindowHint(GLFW_SAMPLES, 1);
    glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_API);      // GLFW_OPENGL_API/GLFW_OPENGL_ES_API
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);         // 4
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);         // 6
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE); // Used for Mac
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_DOUBLEBUFFER, GLFW_TRUE);

    glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);
    glfwWindowHint(GLFW_SCALE_TO_MONITOR, GLFW_TRUE);
    glfwWindowHint(GLFW_SCALE_FRAMEBUFFER, GLFW_TRUE);
    glfwWindowHint(GLFW_REFRESH_RATE, GLFW_DONT_CARE);
    glfwSwapInterval(1);

    auto w = app::render_state.window = glfwCreateWindow(640, 640, "GL", nullptr, nullptr);
    assert(w);

    // setup global callbacks

    glfwSetErrorCallback(error_clb);
    glfwSetMonitorCallback(monitor_clb);
    glfwSetJoystickCallback(joystic_clb);

    // setup windows callbacks

    glfwSetWindowPosCallback(w, window_pos_clb);
    glfwSetWindowSizeCallback(w, window_size_clb);
    glfwSetWindowCloseCallback(w, window_close_clb);
    glfwSetWindowRefreshCallback(w, window_refresh_clb);
    glfwSetWindowFocusCallback(w, window_focus_clb);
    glfwSetWindowIconifyCallback(w, window_iconify_clb);
    glfwSetWindowMaximizeCallback(w, window_maximize_clb); // *

    glfwSetFramebufferSizeCallback(w, framebuffer_size_clb);
    glfwSetWindowContentScaleCallback(w, window_content_scale_clb); // *

    glfwSetKeyCallback(w, key_clb);
    glfwSetCharCallback(w, char_clb);
    glfwSetCharModsCallback(w, char_mods_clb);
    glfwSetMouseButtonCallback(w, mouse_button_clb);
    glfwSetCursorPosCallback(w, cursor_pos_clb);
    glfwSetCursorEnterCallback(w, cursor_enter_clb);
    glfwSetScrollCallback(w, scroll_clb);
    glfwSetDropCallback(w, drop_clb);

    glfwMakeContextCurrent(w);

    // load/check OpenGL extensions

    assert(gladLoadGLLoader((GLADloadproc)glfwGetProcAddress));
    std::vector<std::string> required_ext = {
            "GL_ARB_gpu_shader_fp64",
            "GL_ARB_vertex_attrib_64bit"
    };

    for (const auto &ext : required_ext)
    {
        if (!glfwExtensionSupported(ext.data()))
        {
            std::cerr << "GL extension " << ext << ": not supported" << std::endl;
        }
    }

    // check monitor specs

    int           count;
    GLFWmonitor **monitors = glfwGetMonitors(&count);

    float xscale, yscale;
    glfwGetWindowContentScale(w, &xscale, &yscale); // for specific window/monitor

    int width, height;
    glfwGetFramebufferSize(w, &width, &height);

    for (size_t i = 0; i < count; ++i)
    {
        GLFWmonitor *monitor = monitors[i];
        int          width_mm, height_mm;
        glfwGetMonitorPhysicalSize(monitor, &width_mm, &height_mm);

        const GLFWvidmode *mode = glfwGetVideoMode(monitor);

        std::cout << "Monitor: " << glfwGetMonitorName(monitor)
                  << " " << width_mm << " x " << height_mm << "(mm),"
                  << " " << width << " x " << height << "(px),"
                  << " " << xscale << " x " << yscale << "(dpi scale factor)" << std::endl
                  << "\tCurrent video mode:" << std::endl
                  << "\t\twidth = " << mode->width << std::endl
                  << "\t\theight = " << mode->height << std::endl
                  << "\t\tredBits = " << mode->redBits << std::endl
                  << "\t\tgreenBits = " << mode->greenBits << std::endl
                  << "\t\tblueBits = " << mode->blueBits << std::endl
                  << "\t\trefreshRate = " << mode->refreshRate << std::endl
                  << std::endl;

        int                count;
        const GLFWvidmode *modes = glfwGetVideoModes(monitor, &count);

        for (size_t j = 0; j < count; ++j)
        {
            GLFWvidmode vidmode = modes[j];
            std::cout << "\tVideo Mode " << j << std::endl;

            std::cout << "\t\twidth = " << vidmode.width << std::endl
                      << "\t\theight = " << vidmode.height << std::endl
                      << "\t\tredBits = " << vidmode.redBits << std::endl
                      << "\t\tgreenBits = " << vidmode.greenBits << std::endl
                      << "\t\tblueBits = " << vidmode.blueBits << std::endl
                      << "\t\trefreshRate = " << vidmode.refreshRate << std::endl;
        }

        std::cout << std::endl;
    }

    // setup drawing

    glClearColor(1.f, 1.f, 1.f, 1.f);

    // compile draw triangle program

    std::string vertex_data   = helpers::read_file(path {"assets/shaders/gl3/vertex.glsl"}.generic_string());
    std::string fragment_data = helpers::read_file(path {"assets/shaders/gl3/fragment.glsl"}.generic_string());

    app::render_state.vertex   = std::make_shared<graphics::VertexShader>(vertex_data);
    app::render_state.fragment = std::make_shared<graphics::FragmentShader>(fragment_data);

    app::render_state.passthrough = std::make_unique<graphics::ShaderProgram>(app::render_state.vertex, app::render_state.fragment);
    app::render_state.passthrough->link();

    std::vector<glm::dvec2> vertices = {
            {0.5, 0.5},
            {0.5, -0.5},
            {-0.5, -0.5},
            {-0.5, 0.5}
    };

    std::vector<std::uint32_t> indices = {
            0, 1, 3, 1, 2, 3
    };

    std::vector<glm::dvec2> vert_no_indices = {
            {-0.5, -0.5},
            {0.5, -0.5},
            {0.0, 0.5}
    };

    app::render_state.quad = std::make_shared<graphics::Gl_Render_Target>(
#if 1
            vertices,
            indices
#else
            vert_no_indices
#endif
    );

    // setup VAO for square

    while (!glfwWindowShouldClose(app::render_state.window))
    {
        main_loop_iter();
    }

    glfwDestroyWindow(app::render_state.window);
    glfwTerminate();

    return 0;
}
