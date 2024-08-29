#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <boost/signals2/signal.hpp>

#include <iostream>

#include <string_view>

#include <vector>
#include <set>
#include <map>
#include <variant>
#include <optional>
#include <functional>

#include <atomic>

#include <cstdint>
#include <cassert>

namespace glfw
{

class Monitor;      // forward decl
class Window_Hints; // forward decl
class Window;       // forward decl
class App;          // forward decl

constexpr size_t id_none {0};
constexpr size_t id_start {1};

namespace window_hint
{
    enum Samples : uint8_t
    {
        off = 0,
        x1  = 1,
        x2  = 2,
        x4  = 4,
        x8  = 8,
        x16 = 16
    };

    enum Client_Api : int32_t
    {
        None     = GLFW_NO_API,
        OpenGL   = GLFW_OPENGL_API,
        OpenGLES = GLFW_OPENGL_ES_API
    };

    struct Renderer_None
    {
        const Client_Api client_api = Client_Api::None;
    };

    struct Renderer_Gl
    {
        const Client_Api client_api = Client_Api::OpenGL;

        enum Profile : int32_t
        {
            Any    = GLFW_OPENGL_ANY_PROFILE,
            Core   = GLFW_OPENGL_CORE_PROFILE,
            Compat = GLFW_OPENGL_COMPAT_PROFILE
        } profile = Core;

        struct Gl_Version
        {
            uint8_t major = 3;
            uint8_t minor = 3;
        } version;

        bool                  enable_forward_compat = true;
        std::set<std::string> required_ext;
    };

    struct Renderer_Gles
    {
        const Client_Api client_api = Client_Api::OpenGLES;
    };

    using Renderer = std::variant<Renderer_Gl, Renderer_Gles>;
}; // namespace window_hint

class Monitor
{
  public:

    Monitor(GLFWmonitor *wrapped_monitor);

    GLFWmonitor *get() const;

  protected:

    GLFWmonitor *self_ = nullptr;
};

inline Monitor::Monitor(GLFWmonitor *wrapped_monitor)
    : self_(wrapped_monitor)
{
}

inline GLFWmonitor *
Monitor::get() const
{
    return self_;
}

struct Window_Hints
{
    using Samples       = window_hint::Samples;
    using Client_Api    = window_hint::Client_Api;
    using Renderer      = window_hint::Renderer;
    using Renderer_None = window_hint::Renderer_None;
    using Renderer_Gl   = window_hint::Renderer_Gl;
    using Renderer_Gles = window_hint::Renderer_Gles;
    using Refresh_Rate  = int32_t;
    using Swap_Interval = uint8_t;

    enum Refresh_Rate_Reserved : Refresh_Rate
    {
        DontCare = -1
    };

  public: // fields

    Samples       samples                  = Samples::off;
    Renderer      renderer                 = Renderer_Gl {};
    bool          enable_double_buffer     = true;
    bool          enable_resizible         = true;
    bool          enable_scale_to_monitor  = true;
    bool          enable_scale_framebuffer = true;
    Refresh_Rate  refresh_rate             = Refresh_Rate_Reserved::DontCare;
    Swap_Interval swap_interval            = 1;
};

class Window
{
  public: // types

    using Pos_Clb              = std::function<void(int /*xpos*/, int /*ypos*/)>;
    using Size_Clb             = std::function<void(int /*width*/, int /*height*/)>;
    using Close_Clb            = std::function<void()>;
    using Refresh_Clb          = std::function<void()>;
    using Focus_Clb            = std::function<void(int /*focused*/)>;
    using Iconify_Clb          = std::function<void(int /*iconified*/)>;
    using Maximize_Clb         = std::function<void(int /*maximized*/)>;
    using Framebuffer_Size_Clb = std::function<void(int /*width*/, int /*height*/)>;
    using Content_Scale_Clb    = std::function<void(float /*xscale*/, float /*yscale*/)>;
    using Key_Clb              = std::function<void(int /*key*/, int /*scancode*/, int /*action*/, int /*mods*/)>;
    using Char_Clb             = std::function<void(unsigned /*codepoint*/)>;
    using Char_Mods_Clb        = std::function<void(unsigned /*codepoint*/, int /*mods*/)>;
    using Mouse_Button_Clb     = std::function<void(int /*button*/, int /*action*/, int /*mods*/)>;
    using Cursor_Pos_Clb       = std::function<void(double /*xpos*/, double /*ypos*/)>;
    using Cursor_Enter_Clb     = std::function<void(int /*entered*/)>;
    using Scroll_Clb           = std::function<void(double /*xoffset*/, double /*yoffset*/)>;
    using Drop_Clb             = std::function<void(int /*path_count*/, /*paths*/ const char **)>;

  public: // default callbacks

    const Pos_Clb              default_window_pos_clb       = [](int xpos, int ypos) -> void { /* do nothing */ };
    const Size_Clb             default_size_clb             = [](int width, int height) -> void { /* do nothing */ };
    const Close_Clb            default_close_clb            = []() -> void { /* do nothing */ };
    const Refresh_Clb          default_refresh_clb          = []() -> void { /* do nothing */ };
    const Focus_Clb            default_focus_clb            = [](int focused) -> void { /* do nothing */ };
    const Iconify_Clb          default_iconify_clb          = [](int iconified) -> void { /* do nothing */ };
    const Maximize_Clb         default_maximize_clb         = [](int maximized) -> void { /* do nothing */ };
    const Framebuffer_Size_Clb default_framebuffer_size_clb = [](int width, int height) -> void { /* do nothing */ };
    const Content_Scale_Clb    default_content_scale_clb    = [](float xscale, float yscale) -> void { /* do nothing */ };
    const Key_Clb              default_key_clb              = [](int key, int scancode, int action, int mods) -> void { /* do nothing */ };
    const Char_Clb             default_char_clb             = [](unsigned codepoint) -> void { /* do nothing */ };
    const Char_Mods_Clb        default_char_mods_clb        = [](unsigned codepoint, int mods) -> void { /* do nothing */ };
    const Mouse_Button_Clb     default_mouse_button_clb     = [](int button, int action, int mods) -> void { /* do nothing */ };
    const Cursor_Pos_Clb       default_cursor_pos_clb       = [](double xpos, double ypos) -> void { /* do nothing */ };
    const Cursor_Enter_Clb     default_cursor_enter_clb     = [](int entered) -> void { /* do nothing */ };
    const Scroll_Clb           default_scroll_clb           = [](double xoffset, double yoffset) -> void { /* do nothing */ };
    const Drop_Clb             default_drop_clb             = [](int path_count, const char **paths) -> void { /* do nothing */ };

  private: // hidden constructor

    Window(App *owner, int width, int height, std::string title = {}, std::optional<std::reference_wrapper<Monitor>> monitor = {}, std::optional<std::reference_wrapper<Window>> share_context_with = {});

  public:

    Window(Window &&move_from);
    Window &operator=(Window &&move_from);

    ~Window();

    GLFWwindow *get() const;

    bool should_close() const;
    void make_current() const;
    void swap_buffers() const;

  public: // signals

    boost::signals2::signal<void(int /*xpos*/, int /*ypos*/)>                                  on_window_pos_clb;
    boost::signals2::signal<void(int /*width*/, int /*height*/)>                               on_size_clb;
    boost::signals2::signal<void()>                                                            on_close_clb;
    boost::signals2::signal<void()>                                                            on_refresh_clb;
    boost::signals2::signal<void(int /*focused*/)>                                             on_focus_clb;
    boost::signals2::signal<void(int /*iconified*/)>                                           on_iconify_clb;
    boost::signals2::signal<void(int /*maximized*/)>                                           on_maximize_clb;
    boost::signals2::signal<void(int /*width*/, int /*height*/)>                               on_framebuffer_size_clb;
    boost::signals2::signal<void(float /*xscale*/, float /*yscale*/)>                          on_content_scale_clb;
    boost::signals2::signal<void(int /*key*/, int /*scancode*/, int /*action*/, int /*mods*/)> on_key_clb;
    boost::signals2::signal<void(unsigned /*codepoint*/)>                                      on_char_clb;
    boost::signals2::signal<void(unsigned /*codepoint*/, int /*mods*/)>                        on_char_mods_clb;
    boost::signals2::signal<void(int /*button*/, int /*action*/, int /*mods*/)>                on_mouse_button_clb;
    boost::signals2::signal<void(double /*xpos*/, double /*ypos*/)>                            on_cursor_pos_clb;
    boost::signals2::signal<void(int /*entered*/)>                                             on_cursor_enter_clb;
    boost::signals2::signal<void(double /*xoffset*/, double /*yoffset*/)>                      on_scroll_clb;
    boost::signals2::signal<void(int /*path_count*/, /*paths*/ const char **)>                 on_drop_clb;

  protected:

    GLFWwindow *self_  = nullptr;
    App        *owner_ = nullptr;

  protected:

    friend class App;
};

inline Window::Window(App *owner, int width, int height, std::string title, std::optional<std::reference_wrapper<Monitor>> monitor, std::optional<std::reference_wrapper<Window>> share_context_with)
    : owner_(owner)
{
    GLFWmonitor *target_monitor = monitor.has_value() ? monitor.value().get().get() : nullptr;
    GLFWwindow  *share_context  = share_context_with.has_value() ? share_context_with.value().get().get() : nullptr;

    self_ = glfwCreateWindow(width, height, title.data(), target_monitor, share_context);
}

inline Window::Window(Window &&move_from)
{
    std::swap(owner_, move_from.owner_);
    std::swap(self_, move_from.self_);
}

inline Window &
Window::operator=(Window &&move_from)
{
    std::swap(self_, move_from.self_);
    std::swap(owner_, move_from.owner_);
}

inline Window::~Window()
{
    if (self_)
    {
        glfwDestroyWindow(self_);
    }
}

inline GLFWwindow *
Window::get() const
{
    return self_;
}

inline bool
Window::should_close() const
{
    return glfwWindowShouldClose(self_);
}

inline void
Window::make_current() const
{
    glfwMakeContextCurrent(self_);
}

inline void
Window::swap_buffers() const
{
    glfwSwapBuffers(self_);
}

class App
{
  public:

    using Window_Id = size_t;

    enum Special_Window_Id : Window_Id
    {
        shared = -1
    };

  public:

    App();
    ~App();

    void    set_next_window_hints(Window_Hints hints);
    Window &create_window(int width, int height, std::string title = {}, std::optional<std::reference_wrapper<Monitor>> monitor = {}, std::optional<std::reference_wrapper<Window>> share_context_with = {});

    void run();

  protected:

    void apply_window_hints(const Window_Hints &hints);
    void apply_window_hint(const Window_Hints::Renderer &renderer);

  protected:

    Window_Hints                next_window_hints_ {};
    std::map<Window_Id, Window> windows_;
};

inline App::App()
{
    glfwInit();
}

inline App::~App()
{
    glfwTerminate();
}

inline void
App::set_next_window_hints(Window_Hints hints)
{
}

inline Window &
App::create_window(int width, int height, std::string title, std::optional<std::reference_wrapper<Monitor>> monitor, std::optional<std::reference_wrapper<Window>> share_context_with)
{
    static std::atomic_size_t window_id {id_start}; // 0 means none

    struct Renderer_Api_Loader
    {
        Renderer_Api_Loader(const Window &context)
            : context_(context) {};

        void
        operator()(const Window_Hints::Renderer_None &renderer) const
        {
            /* do nothing */
        }

        void
        operator()(const Window_Hints::Renderer_Gl &renderer) const
        {
            context_.make_current();

            // load/check OpenGL extensions

            assert(gladLoadGLLoader((GLADloadproc)glfwGetProcAddress));

#if 0
            /*
             * "GL_ARB_gpu_shader_fp64",
             * "GL_ARB_vertex_attrib_64bit"
             */
#endif
            for (const auto &ext : renderer.required_ext)
            {
                if (!glfwExtensionSupported(ext.data()))
                {
                    std::cerr << "GL extension " << ext << ": not supported" << std::endl;
                }
            }
        }

        void
        operator()(const Window_Hints::Renderer_Gles &renderer) const
        {
            /* do nothing */
        }

      protected:

        const Window &context_;
    };

    apply_window_hints(next_window_hints_);
    auto &result = windows_.emplace(std::make_pair(window_id++, Window {this, width, height, title, monitor, share_context_with})).first->second;

    // std::visit(Renderer_Api_Loader {result}, next_window_hints_.renderer);

    return result;
}

inline void
App::run()
{
    while (!windows_.empty())
    {
        std::set<Window_Id> to_delete_windows;

        glfwPollEvents();
        for (auto &[wid, window] : windows_)
        {
            if (window.should_close())
            {
                to_delete_windows.insert(wid);
                continue;
            }

            window.swap_buffers();
        }

        for (auto wid : to_delete_windows)
        {
            windows_.erase(wid);
        }
    }
}

void
App::apply_window_hints(const Window_Hints &hints)
{
    glfwWindowHint(GLFW_SAMPLES, hints.samples);

    apply_window_hint(hints.renderer);

    glfwWindowHint(GLFW_DOUBLEBUFFER, hints.enable_double_buffer);
    glfwWindowHint(GLFW_RESIZABLE, hints.enable_resizible);
    glfwWindowHint(GLFW_SCALE_TO_MONITOR, hints.enable_scale_to_monitor);
    glfwWindowHint(GLFW_SCALE_FRAMEBUFFER, hints.enable_scale_framebuffer);

    glfwWindowHint(GLFW_REFRESH_RATE, hints.refresh_rate);
    glfwSwapInterval(hints.swap_interval);
}

inline void
App::apply_window_hint(const Window_Hints::Renderer &renderer)
{
    struct Renderer_Visitor_Static
    {
        void
        operator()(const Window_Hints::Renderer_None &renderer) const
        {
            /* do nothing */
        }

        void
        operator()(const Window_Hints::Renderer_Gl &renderer) const
        {
            glfwWindowHint(GLFW_CLIENT_API, renderer.client_api);
            glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, renderer.version.major);
            glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, renderer.version.minor);
            glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, renderer.enable_forward_compat);
            glfwWindowHint(GLFW_OPENGL_PROFILE, renderer.profile);
        }

        void
        operator()(const Window_Hints::Renderer_Gles &renderer) const
        {
            glfwWindowHint(GLFW_CLIENT_API, renderer.client_api);
            /* do nothing */
        }
    } hints_applyer;

    std::visit(hints_applyer, renderer);
}

} // namespace glfw
