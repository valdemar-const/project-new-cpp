#include <glad/gl.h>
#undef __gl_h_
#undef __gl3_h_
#undef __glext_h_
#undef __gl3ext_h_
#include <glad/gles2.h>
#include <glfw/glfw.hpp>

#include <toml++/toml.hpp>

#include <iostream>
#include <sstream>
#include <string_view>

#include <set>
#include <bitset>
#include <unordered_map>
#include <functional>

#include <algorithm>
#include <numeric>
#include <random>

#include <cassert>
#include <cstdlib>

using namespace std::string_literals;

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
                auto [x, y] = get_monitor_pos(m);
                std::cout << "\tpos: " << x << ", " << y << std::endl;
            }
            {
                auto [x, y] = get_monitor_content_scale(m);
                std::cout << "\tscale: " << x << ", " << y << std::endl;
            }
            {
                auto [w, h] = get_monitor_physical_size(m);
                std::cout << "\tsize: " << w << ", " << h << std::endl;
            }
            {
                auto [pos, size] = get_monitor_workarea(m);
                std::cout << "\tworkarea: " << pos.x << ", " << pos.y << ", " << size.width << ", " << size.height << std::endl;
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

auto print_gl_info = [](const auto &context)
{
    using namespace glfw::wrap;

    std::cout << "opengl.vendor: " << context.GetString(GL_VENDOR) << std::endl;
    std::cout << "opengl.renderer: " << context.GetString(GL_RENDERER) << std::endl;
    {
        GLint major, minor;
        context.GetIntegerv(GL_MAJOR_VERSION, &major);
        context.GetIntegerv(GL_MINOR_VERSION, &minor);
        std::cout << "opengl.version: " << major << "." << minor << std::endl;
    }
    std::cout << "opengl.version_info: " << context.GetString(GL_VERSION) << std::endl;
    {
        GLint profile;
        context.GetIntegerv(GL_CONTEXT_PROFILE_MASK, &profile);
        bool is_profile_core   = (profile & GL_CONTEXT_CORE_PROFILE_BIT) == GL_CONTEXT_CORE_PROFILE_BIT;
        bool is_profile_compat = (profile & GL_CONTEXT_COMPATIBILITY_PROFILE_BIT) == GL_CONTEXT_COMPATIBILITY_PROFILE_BIT;
        std::cout << "opengl.profile: " << ((is_profile_core) ? "core" : "compatibility") << std::endl;
    }
    {
        GLint contextf;
        context.GetIntegerv(GL_CONTEXT_FLAGS, &contextf);
        bool is_compat   = (contextf & GL_CONTEXT_FLAG_FORWARD_COMPATIBLE_BIT) == GL_CONTEXT_FLAG_FORWARD_COMPATIBLE_BIT;
        bool is_debug    = (contextf & GL_CONTEXT_FLAG_DEBUG_BIT) == GL_CONTEXT_FLAG_DEBUG_BIT;
        bool is_robust   = (contextf & GL_CONTEXT_FLAG_ROBUST_ACCESS_BIT) == GL_CONTEXT_FLAG_ROBUST_ACCESS_BIT;
        bool is_no_error = (contextf & GL_CONTEXT_FLAG_NO_ERROR_BIT) == GL_CONTEXT_FLAG_NO_ERROR_BIT;

        std::cout << "opengl.context.is_compat: " << std::boolalpha << is_compat << std::endl;
        std::cout << "opengl.context.is_debug: " << std::boolalpha << is_debug << std::endl;
        std::cout << "opengl.context.is_robust: " << std::boolalpha << is_robust << std::endl;
        std::cout << "opengl.context.is_no_error: " << std::boolalpha << is_no_error << std::endl;
    }
    {
        GLint shader_lang_versions = 0;
        context.GetIntegerv(GL_NUM_SHADING_LANGUAGE_VERSIONS, &shader_lang_versions);
        std::vector<std::string_view> shader_versions;
        shader_versions.resize(shader_lang_versions);
        GLint next_ver_id = 0;
        for (auto &ver : shader_versions)
        {
            ver = (char *)context.GetStringi(GL_SHADING_LANGUAGE_VERSION, next_ver_id++);
        }
        if (shader_lang_versions)
        {
            auto version = std::accumulate(shader_versions.cbegin(), shader_versions.cend(), std::string {}, [](auto acc, const auto ver)
                                           {
                                               if (ver.empty())
                                               {
                                                   return std::move(acc);
                                               }
                                               else
                                               {
                                                   return std::move((acc.empty()) ? "\t" + std::string {ver} : acc + ",\n\t" + std::string {ver});
                                               }
                                           });

            std::cout << "opengl.glsl_version: [" << std::endl
                      << version << std::endl
                      << "]" << std::endl;
        }
    }
    std::cout << "opengl.shading_lang_version: " << context.GetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;
    std::cout << "opengl.extensions: [" << std::endl;

    auto get_context_ext = [](const auto &context) -> std::set<std::string>
    {
        std::set<std::string> ext_names;

        GLint ext_num = 0;
        context.GetIntegerv(GL_NUM_EXTENSIONS, &ext_num);
        for (size_t i = 0; i < ext_num; ++i)
        {
            ext_names.insert({(char *)context.GetStringi(GL_EXTENSIONS, i)});
        }

        return ext_names;
    };

    const auto extensions       = get_context_ext(context);
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
};

int
main(int argc, char *argv[])

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
                    glfw::wrap::init_hint(hint);
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
                    glfw::wrap::window_hint(hint);
                }
        );
    };

    auto print_context_gl_info = [](const auto &context)
    {
        print_platform_info();
        print_monitors_info();
        print_gl_info(context);
    };

    auto configure_gl_context = [&](Window *window) -> std::variant<GladGLContext, GladGLES2Context>
    {
        make_context_current(window);
        swap_interval(1);

        GladGLContext    context;
        GladGLES2Context context_es2;

        bool is_gl_loaded = false;
        bool is_es_loaded = false;
        is_gl_loaded      = gladLoadGLContext(&context, (GLADloadfunc)glfw::wrap::get_proc_address);
        is_es_loaded      = gladLoadGLES2Context(&context_es2, (GLADloadfunc)glfw::wrap::get_proc_address);

        auto rand_float = []()
        {
            return static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
        };

        if (is_gl_loaded)
        {
            print_context_gl_info(context);
            context.ClearColor(rand_float(), rand_float(), rand_float(), 1.0);
            return context;
        }
        else
        {
            print_context_gl_info(context_es2);
            context_es2.ClearColor(rand_float(), rand_float(), rand_float(), 1.0);
            return context_es2;
        }
    };

    auto configure_gl_contexts = [&](const auto &contexts) -> std::map<Window *, std::variant<GladGLContext, GladGLES2Context>>
    {
        std::map<Window *, std::variant<GladGLContext, GladGLES2Context>> result;

        std::for_each(contexts.cbegin(), contexts.cend(), [&](const auto ctx)
                      {
                          result.insert(std::make_pair(ctx, configure_gl_context(ctx)));
                      });
        return result;
    };

    const std::vector<Init_Hint> init_hints_gles_3_0 {
            {hint::init::AnglePlatformType {AnglePlatformType::OpenGl}}
    };

    const std::vector<Window_Hint> window_hints_gles_3_0 {
            {hint::window::ClientApi {ClientApi::OpenGles}},
            {hint::window::ContextCreationApi {ContextCreationApi::Native}},
            {hint::window::ContextVersionMajor {3}},
            {hint::window::ContextVersionMinor {0}},
#ifdef __APPLE__
            {hint::window::OpenGlForwardCompat {true}}, // for MacOS only
#endif
            {hint::window::OpenGlProfile {OpenGlProfile::Core}},
            {hint::window::DoubleBuffer {true}},
            {hint::window::ContextNoError {false}},
            {hint::window::ContextRobustness {ContextRobustness::LoseContextOnReset}},
            {hint::window::ContextDebug {true}},

            {hint::window::Resizable {false}},
            {hint::window::ScaleToMonitor {true}},
            {hint::window::ScaleFrameBuffer {true}},
            {hint::window::RefreshRate {}}
    };

    const std::vector<Window_Hint> window_hints_gl_4_6 {
            {hint::window::ClientApi {ClientApi::OpenGl}},
            {hint::window::ContextCreationApi {ContextCreationApi::Native}},
            {hint::window::ContextVersionMajor {4}},
            {hint::window::ContextVersionMinor {6}},
#ifdef __APPLE__
            {hint::window::OpenGlForwardCompat {true}}, // for MacOS only
#endif
            {hint::window::OpenGlProfile {OpenGlProfile::Core}},
            {hint::window::DoubleBuffer {true}},
            {hint::window::ContextNoError {false}},
            {hint::window::ContextRobustness {ContextRobustness::LoseContextOnReset}},
            {hint::window::ContextDebug {true}},

            {hint::window::Resizable {false}},
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
                std::visit([](const auto &gl) -> void
                           {
                               gl.Clear(GL_COLOR_BUFFER_BIT);
                           },
                           gl_contexts.at(window));

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
