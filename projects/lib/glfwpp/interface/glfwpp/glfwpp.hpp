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

    using Pos_Clb              = std::function<void(Window &, int /*xpos*/, int /*ypos*/)>;
    using Size_Clb             = std::function<void(Window &, int /*width*/, int /*height*/)>;
    using Close_Clb            = std::function<void(Window &)>;
    using Refresh_Clb          = std::function<void(Window &)>;
    using Focus_Clb            = std::function<void(Window &, int /*focused*/)>;
    using Iconify_Clb          = std::function<void(Window &, int /*iconified*/)>;
    using Maximize_Clb         = std::function<void(Window &, int /*maximized*/)>;
    using Framebuffer_Size_Clb = std::function<void(Window &, int /*width*/, int /*height*/)>;
    using Content_Scale_Clb    = std::function<void(Window &, float /*xscale*/, float /*yscale*/)>;
    using Key_Clb              = std::function<void(Window &, int /*key*/, int /*scancode*/, int /*action*/, int /*mods*/)>;
    using Char_Clb             = std::function<void(Window &, unsigned /*codepoint*/)>;
    using Char_Mods_Clb        = std::function<void(Window &, unsigned /*codepoint*/, int /*mods*/)>;
    using Mouse_Button_Clb     = std::function<void(Window &, int /*button*/, int /*action*/, int /*mods*/)>;
    using Cursor_Pos_Clb       = std::function<void(Window &, double /*xpos*/, double /*ypos*/)>;
    using Cursor_Enter_Clb     = std::function<void(Window &, int /*entered*/)>;
    using Scroll_Clb           = std::function<void(Window &, double /*xoffset*/, double /*yoffset*/)>;
    using Drop_Clb             = std::function<void(Window &, int /*path_count*/, /*paths*/ const char **)>;

    struct Window_Callback_Context
    {
        Window_Callback_Context(std::map<GLFWwindow *, Window *> &windows_db)
            : windows_db_(windows_db)
        {
        }

        Window &
        getw(GLFWwindow *w) const
        {
            return *windows_db_.at(w);
        };

      protected:

        std::map<GLFWwindow *, Window *> &windows_db_;
    };

  public:  // default callbacks
  private: // hidden constructor

    Window(App *owner, int width, int height, std::string title = {}, std::optional<std::reference_wrapper<Monitor>> monitor = {}, std::optional<std::reference_wrapper<Window>> share_context_with = {});
    Window(Window &copy_from)            = default;
    Window &operator=(Window &copy_from) = default;

  public:

    Window(Window &&move_from);
    Window &operator=(Window &&move_from);

    ~Window();

    GLFWwindow *get() const;

    bool should_close() const;
    void make_current() const;
    void swap_buffers() const;

  public: // signals

    boost::signals2::signal<void(Window &, int /*xpos*/, int /*ypos*/)>                                  on_window_pos;
    boost::signals2::signal<void(Window &, int /*width*/, int /*height*/)>                               on_size;
    boost::signals2::signal<void(Window &)>                                                              on_close;
    boost::signals2::signal<void(Window &)>                                                              on_refresh;
    boost::signals2::signal<void(Window &, int /*focused*/)>                                             on_focus;
    boost::signals2::signal<void(Window &, int /*iconified*/)>                                           on_iconify;
    boost::signals2::signal<void(Window &, int /*maximized*/)>                                           on_maximize;
    boost::signals2::signal<void(Window &, int /*width*/, int /*height*/)>                               on_framebuffer_size;
    boost::signals2::signal<void(Window &, float /*xscale*/, float /*yscale*/)>                          on_content_scale;
    boost::signals2::signal<void(Window &, int /*key*/, int /*scancode*/, int /*action*/, int /*mods*/)> on_key;
    boost::signals2::signal<void(Window &, unsigned /*codepoint*/)>                                      on_char;
    boost::signals2::signal<void(Window &, unsigned /*codepoint*/, int /*mods*/)>                        on_char_mods;
    boost::signals2::signal<void(Window &, int /*button*/, int /*action*/, int /*mods*/)>                on_mouse_button;
    boost::signals2::signal<void(Window &, double /*xpos*/, double /*ypos*/)>                            on_cursor_pos;
    boost::signals2::signal<void(Window &, int /*entered*/)>                                             on_cursor_enter;
    boost::signals2::signal<void(Window &, double /*xoffset*/, double /*yoffset*/)>                      on_scroll;
    boost::signals2::signal<void(Window &, int /*path_count*/, /*paths*/ const char **)>                 on_drop;

  protected:

    GLFWwindow *self_  = nullptr;
    App        *owner_ = nullptr;

  protected:

    friend class App;

  private:

    static void
    default_window_pos_clb(GLFWwindow *self, int xpos, int ypos)
    {
        auto &context = *static_cast<Window_Callback_Context *>(glfwGetWindowUserPointer(self));
        assert(self == context.getw(self).get());
        context.getw(self).on_window_pos(context.getw(self), xpos, ypos);
    };

    static void
    default_size_clb(GLFWwindow *self, int width, int height)
    {
        auto &context = *static_cast<Window_Callback_Context *>(glfwGetWindowUserPointer(self));
        assert(self == context.getw(self).get());
        context.getw(self).on_size(context.getw(self), width, height);
    };

    static void
    default_close_clb(GLFWwindow *self)
    {
        auto &context = *static_cast<Window_Callback_Context *>(glfwGetWindowUserPointer(self));
        assert(self == context.getw(self).get());
        context.getw(self).on_close(context.getw(self));
    };

    static void
    default_refresh_clb(GLFWwindow *self)
    {
        auto &context = *static_cast<Window_Callback_Context *>(glfwGetWindowUserPointer(self));
        assert(self == context.getw(self).get());
        context.getw(self).on_refresh(context.getw(self));
    };

    static void
    default_focus_clb(GLFWwindow *self, int focused)
    {
        auto &context = *static_cast<Window_Callback_Context *>(glfwGetWindowUserPointer(self));
        assert(self == context.getw(self).get());
        context.getw(self).on_focus(context.getw(self), focused);
    };

    static void
    default_iconify_clb(GLFWwindow *self, int iconified)
    {
        auto &context = *static_cast<Window_Callback_Context *>(glfwGetWindowUserPointer(self));
        assert(self == context.getw(self).get());
        context.getw(self).on_iconify(context.getw(self), iconified);
    };

    static void
    default_maximize_clb(GLFWwindow *self, int maximized)
    {
        auto &context = *static_cast<Window_Callback_Context *>(glfwGetWindowUserPointer(self));
        assert(self == context.getw(self).get());
        context.getw(self).on_maximize(context.getw(self), maximized);
    };

    static void
    default_framebuffer_size_clb(GLFWwindow *self, int width, int height)
    {
        auto &context = *static_cast<Window_Callback_Context *>(glfwGetWindowUserPointer(self));
        assert(self == context.getw(self).get());
        context.getw(self).on_framebuffer_size(context.getw(self), width, height);
    };

    static void
    default_content_scale_clb(GLFWwindow *self, float xscale, float yscale)
    {
        auto &context = *static_cast<Window_Callback_Context *>(glfwGetWindowUserPointer(self));
        assert(self == context.getw(self).get());
        context.getw(self).on_content_scale(context.getw(self), xscale, yscale);
    };

    static void
    default_key_clb(GLFWwindow *self, int key, int scancode, int action, int mods)
    {
        auto &context = *static_cast<Window_Callback_Context *>(glfwGetWindowUserPointer(self));
        assert(self == context.getw(self).get());
        context.getw(self).on_key(context.getw(self), key, scancode, action, mods);
    };

    static void
    default_char_clb(GLFWwindow *self, unsigned codepoint)
    {
        auto &context = *static_cast<Window_Callback_Context *>(glfwGetWindowUserPointer(self));
        assert(self == context.getw(self).get());
        context.getw(self).on_char(context.getw(self), codepoint);
    };

    static void
    default_char_mods_clb(GLFWwindow *self, unsigned codepoint, int mods)
    {
        auto &context = *static_cast<Window_Callback_Context *>(glfwGetWindowUserPointer(self));
        assert(self == context.getw(self).get());
        context.getw(self).on_char_mods(context.getw(self), codepoint, mods);
    };

    static void
    default_mouse_button_clb(GLFWwindow *self, int button, int action, int mods)
    {
        auto &context = *static_cast<Window_Callback_Context *>(glfwGetWindowUserPointer(self));
        assert(self == context.getw(self).get());
        context.getw(self).on_mouse_button(context.getw(self), button, action, mods);
    };

    static void
    default_cursor_pos_clb(GLFWwindow *self, double xpos, double ypos)
    {
        auto &context = *static_cast<Window_Callback_Context *>(glfwGetWindowUserPointer(self));
        assert(self == context.getw(self).get());
        context.getw(self).on_cursor_pos(context.getw(self), xpos, ypos);
    };

    static void
    default_cursor_enter_clb(GLFWwindow *self, int entered)
    {
        auto &context = *static_cast<Window_Callback_Context *>(glfwGetWindowUserPointer(self));
        assert(self == context.getw(self).get());
        context.getw(self).on_cursor_enter(context.getw(self), entered);
    };

    static void
    default_scroll_clb(GLFWwindow *self, double xoffset, double yoffset)
    {
        auto &context = *static_cast<Window_Callback_Context *>(glfwGetWindowUserPointer(self));
        assert(self == context.getw(self).get());
        context.getw(self).on_scroll(context.getw(self), xoffset, yoffset);
    };

    static void
    default_drop_clb(GLFWwindow *self, int path_count, const char **paths)
    {
        auto &context = *static_cast<Window_Callback_Context *>(glfwGetWindowUserPointer(self));
        assert(self == context.getw(self).get());
        context.getw(self).on_drop(context.getw(self), path_count, paths);
    };

  private:

    static std::map<GLFWwindow *, Window *> windows_;
};

inline std::map<GLFWwindow *, Window *> Window::windows_ = {};

inline Window::Window(App *owner, int width, int height, std::string title, std::optional<std::reference_wrapper<Monitor>> monitor, std::optional<std::reference_wrapper<Window>> share_context_with)
    : owner_(owner)
{
    GLFWmonitor *target_monitor = monitor.has_value() ? monitor.value().get().get() : nullptr;
    GLFWwindow  *share_context  = share_context_with.has_value() ? share_context_with.value().get().get() : nullptr;

    self_ = glfwCreateWindow(width, height, title.data(), target_monitor, share_context);

    auto *clb_context = new Window_Callback_Context {windows_};

    glfwSetWindowUserPointer(self_, clb_context);

    glfwSetWindowPosCallback(self_, default_window_pos_clb);
#if 0
    glfwSetWindowSizeCallback(self_, default_size_clb);
    glfwSetWindowCloseCallback(self_, default_close_clb);
    glfwSetWindowRefreshCallback(self_, default_refresh_clb);
    glfwSetWindowFocusCallback(self_, default_focus_clb);
    glfwSetWindowIconifyCallback(self_, default_iconify_clb);
    glfwSetWindowMaximizeCallback(self_, default_maximize_clb);
    glfwSetFramebufferSizeCallback(self_, default_framebuffer_size_clb);
    glfwSetWindowContentScaleCallback(self_, default_content_scale_clb);
    glfwSetKeyCallback(self_, default_key_clb);
    glfwSetCharCallback(self_, default_char_clb);
    glfwSetCharModsCallback(self_, default_char_mods_clb);
    glfwSetMouseButtonCallback(self_, default_mouse_button_clb);
    glfwSetCursorPosCallback(self_, default_cursor_pos_clb);
    glfwSetCursorEnterCallback(self_, default_cursor_enter_clb);
    glfwSetScrollCallback(self_, default_scroll_clb);
    glfwSetDropCallback(self_, default_drop_clb);
#endif
    windows_.insert(std::make_pair(self_, this));
}

inline Window::Window(Window &&move_from)
{
    std::swap(owner_, move_from.owner_);
    std::swap(self_, move_from.self_);
    windows_.at(self_) = this;
}

inline Window &
Window::operator=(Window &&move_from)
{
    std::swap(self_, move_from.self_);
    std::swap(owner_, move_from.owner_);
    windows_.at(self_) = this;
}

inline Window::~Window()
{
    if (self_)
    {
        auto *context = reinterpret_cast<Window_Callback_Context *>(glfwGetWindowUserPointer(self_));
        if (context)
        {
            delete context;
        }
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
