#include <glad/glad.h>
#include <glfw/glfw.hpp>

#include <toml++/toml.hpp>

#include <iostream>
#include <sstream>
#include <string_view>

#include <set>
#include <unordered_map>
#include <functional>

#include <algorithm>
#include <numeric>
#include <random>

#include <cassert>
#include <cstdlib>

using namespace std::string_literals;

struct glLoadContext
{
    using Func_glClearColor = std::function<void(GLfloat r, GLfloat g, GLfloat b, GLfloat a)>;
    using Func_glClear      = std::function<void(GLbitfield buffers_mask)>;

    enum class Loader
    {
        Glad
    };

    glLoadContext(glfw::wrap::Window *window, Loader load_with = Loader::Glad)
        : context_(window)
    {
        const std::unordered_map<Loader, std::function<void()>> loader_func {
                std::make_pair(Loader::Glad, std::bind(&glLoadContext::load_by_glad, this))
        };

        loader_func.at(load_with)();
    }

    glfw::wrap::Window *
    get()
    {
        return context_;
    }

    void
    make_current()
    {
        glfw::wrap::make_context_current(context_);
    }

    Func_glClearColor ClearColor;
    Func_glClear      Clear;

  private:

    void
    load_by_glad()
    {
        glfw::wrap::make_context_current(context_);
        assert(gladLoadGLLoader((GLADloadproc)glfw::wrap::get_proc_address));

        Clear      = glClear;
        ClearColor = glClearColor;
    }

  private:

    glfw::wrap::Window *context_;
};

void
print_platform_info()
{
    using namespace glfw::wrap;

    const std::unordered_map<Platform, std::string_view> platform_name {
            std::make_pair(Platform::Undefined, "Undefined"),
            std::make_pair(Platform::Win32, "Win32"),
            std::make_pair(Platform::Cocoa, "Cocoa"),
            std::make_pair(Platform::Wayland, "Wayland"),
            std::make_pair(Platform::X11, "X11")
    };

    std::cout << "glfw.platform: " << platform_name.at(get_platform()) << std::endl;
}

void
print_monitors_info()
{
    using namespace glfw::wrap;

    auto primary = get_primary_monitor();
    std::cout << "monitors:" << std::endl;

    for (auto m : get_monitors())
    {
        for (auto vm : get_video_modes(m))
        {
            std::cout << "{" << std::endl;
            std::cout << "\tname: " << get_monitor_name(m) << std::endl;
            {
                int x, y;
                get_monitor_pos(m, &x, &y);
                std::cout << "\tpos: " << x << ", " << y << std::endl;
            }
            {
                float x, y;
                get_monitor_content_scale(m, &x, &y);
                std::cout << "\tscale: " << x << ", " << y << std::endl;
            }
            {
                int w, h;
                get_monitor_physical_size(m, &w, &h);
                std::cout << "\tsize: " << w << ", " << h << std::endl;
            }
            {
                int x, y, w, h;
                get_monitor_workarea(m, &x, &y, &w, &h);
                std::cout << "\tworkarea: " << x << ", " << y << ", " << w << ", " << h << std::endl;
            }

            std::cout << "\theight: " << vm.height << std::endl;
            std::cout << "\twidth: " << vm.width << std::endl;
            std::cout << "\trefreshRate: " << vm.refreshRate << std::endl;
            std::cout << "\tredBits: " << vm.redBits << std::endl;
            std::cout << "\tgreenBits: " << vm.greenBits << std::endl;
            std::cout << "\tblueBits: " << vm.blueBits << std::endl;
            std::cout << "}" << std::endl;
        }
    }
}

void
print_gl_info()
{
    using namespace glfw::wrap;

    std::cout << "opengl.vendor: " << glGetString(GL_VENDOR) << std::endl;
    std::cout << "opengl.renderer: " << glGetString(GL_RENDERER) << std::endl;
    std::cout << "opengl.version: " << glGetString(GL_VERSION) << std::endl;
    std::cout << "opengl.shading_lang_version: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;
    std::cout << "opengl.extensions: [" << std::endl;

    auto get_context_ext = []() -> std::set<std::string>
    {
        std::set<std::string> ext_names;

        GLint ext_num = 0;
        glGetIntegerv(GL_NUM_EXTENSIONS, &ext_num);
        for (size_t i = 0; i < ext_num; ++i)
        {
            ext_names.insert({(char *)glGetStringi(GL_EXTENSIONS, i)});
        }

        return ext_names;
    };

    const auto extensions       = get_context_ext();
    auto       print_extensions = [](const auto &extensions)
    {
        auto ext_string = std::accumulate(extensions.cbegin(), extensions.cend(), std::string {}, [](auto acc, const auto &elem)
                                          {
                                              return std::move((acc.empty()) ? ("\t" + elem) : (acc + ",\n\t" + elem));
                                          });
        std::cout << ext_string << std::endl;
    };

    print_extensions(extensions);
    std::cout << "]" << std::endl;
    std::cout << "\topengl.extensions_count: " << extensions.size() << std::endl;
}

int
main(
        int   argc,
        char *argv[]
)
{
    using namespace glfw::wrap;

    std::srand((unsigned)time(NULL));

    auto apply_init_hints = [](const auto &hints)
    {
        std::for_each(
                hints.begin(),
                hints.end(),
                [](const auto hint)
                {
                    init_hint(hint);
                }
        );
    };

    auto apply_window_hints = [](const auto &hints)
    {
        std::for_each(
                hints.begin(),
                hints.end(),
                [](const auto hint)
                {
                    window_hint(hint);
                }
        );
    };

    auto print_context_gl_info = [](Window *window)
    {
        make_context_current(window);
        print_platform_info();
        print_monitors_info();
        print_gl_info();
        request_window_attention(window);
    };

    auto configure_gl_context = [&](Window *window) -> glLoadContext
    {
        make_context_current(window);
        swap_interval(1);

        auto gl = glLoadContext(window);

        // print_context_gl_info(window);

        auto rand_float = []()
        {
            return static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
        };

        gl.ClearColor(rand_float(), rand_float(), rand_float(), 1.0);
        return gl;
    };

    auto configure_gl_contexts = [&](const auto &contexts) -> std::map<Window *, glLoadContext>
    {
        std::map<Window *, glLoadContext> result;

        std::for_each(contexts.cbegin(), contexts.cend(), [&](const auto ctx)
                      {
                          result.insert(std::make_pair(ctx, configure_gl_context(ctx)));
                      });
        return result;
    };

    const std::vector<Init_Hint> init_hints_gles_3_0 {
            {hint::init::AnglePlatformType {AnglePlatformType::OpenGles}}
    };

    const std::vector<Window_Hint> window_hints_gles_3_0 {
            {hint::window::ClientApi {ClientApi::OpenGles}},
            {hint::window::ContextCreationApi {ContextCreationApi::Egl}},
            {hint::window::ContextVersionMajor {3}},
            {hint::window::ContextVersionMinor {0}},
            {hint::window::OpenGlForwardCompat {true}},
            {hint::window::OpenGlProfile {OpenGlProfile::Core}},
            {hint::window::DoubleBuffer {true}},
            {hint::window::ContextNoError {false}},

            {hint::window::Resizable {true}},
            {hint::window::ScaleToMonitor {true}},
            {hint::window::ScaleFrameBuffer {true}},
            {hint::window::RefreshRate {}}
    };

    const std::vector<Window_Hint> window_hints_gl_4_6 {
            {hint::window::ClientApi {ClientApi::OpenGl}},
            {hint::window::ContextCreationApi {ContextCreationApi::Native}},
            {hint::window::ContextVersionMajor {4}},
            {hint::window::ContextVersionMinor {6}},
            {hint::window::OpenGlForwardCompat {true}},
            {hint::window::OpenGlProfile {OpenGlProfile::Core}},
            {hint::window::DoubleBuffer {true}},
            {hint::window::ContextNoError {false}},

            {hint::window::Resizable {true}},
            {hint::window::ScaleToMonitor {true}},
            {hint::window::ScaleFrameBuffer {true}},
            {hint::window::RefreshRate {}}
    };

    apply_init_hints(init_hints_gles_3_0);
    auto res = init();

    std::set<Window *> windows;

    apply_window_hints(window_hints_gles_3_0);
    auto window = create_window(640, 640, "Wrapped GLFW GLES 3.0", nullptr, nullptr);
    windows.insert(window);

    default_window_hints();

    apply_window_hints(window_hints_gl_4_6);
    window = create_window(640, 640, "Wrapped GLFW GL 4.6", nullptr, nullptr);
    windows.insert(window);

    auto gl_contexts = configure_gl_contexts(windows);

    while (!windows.empty())
    {
        std::set<Window *> windows_to_close;
        for (auto window : windows)
        {
            if (!window_should_close(window))
            {
                poll_events();

                make_context_current(window);
                auto &gl = gl_contexts.at(window);
                gl.Clear(GL_COLOR_BUFFER_BIT);

                swap_buffers(window);
            }
            else
            {
                windows_to_close.insert(window);
            }
        }
        for (auto window : windows_to_close)
        {
            windows.erase(window);
            destroy_window(window);
        }
    }

    ::glfw::wrap::terminate();

    return EXIT_SUCCESS;
}
