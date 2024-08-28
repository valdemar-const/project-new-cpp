#pragma once

#include <GLFW/glfw3.h>

#include <string_view>

#include <vector>
#include <set>
#include <map>
#include <variant>
#include <optional>
#include <functional>

#include <atomic>

#include <cstdint>

namespace glfw
{

class Monitor;      // forward decl
class Window_Hints; // forward decl
class Window;       // forward decl
class App;          // forward decl

namespace window_hint
{
    enum Samples
    {
        off = 0,
        x1  = 1,
        x2  = 2,
        x4  = 4,
        x8  = 8,
        x16 = 16
    };

    enum class Renderer_Api
    {
        None,
        OpenGL,
        OpenGLES
    };

    struct Renderer_GL
    {
        enum class Profile
        {
            Any,
            Core,
            Compat
        } profile;

        struct Gl_Version
        {
            uint8_t major;
            uint8_t minor;
        } version;

        bool enable_forward_compat;
    };
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
    : self_(wrapped_monitor) {
    };

inline GLFWmonitor *
Monitor::get() const
{
    return self_;
};

struct Window_Hints
{
    using Samples = window_hint::Samples;

  public: // fields

    Samples samples = Samples::off;
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

    Window(int width, int height, std::string title = {}, std::optional<std::reference_wrapper<Monitor>> monitor = {}, std::optional<std::reference_wrapper<Window>> share_context_with = {});

  public:

    Window(Window &&move_from);
    Window &operator=(Window &&move_from);

    ~Window();

    GLFWwindow *get() const;

    bool should_close() const;

  protected:

    GLFWwindow *self_ = nullptr;

  protected:

    friend class App;
};

inline Window::Window(int width, int height, std::string title, std::optional<std::reference_wrapper<Monitor>> monitor, std::optional<std::reference_wrapper<Window>> share_context_with)
{
    GLFWmonitor *target_monitor = monitor.has_value() ? monitor.value().get().get() : nullptr;
    GLFWwindow  *share_context  = share_context_with.has_value() ? share_context_with.value().get().get() : nullptr;

    self_ = glfwCreateWindow(width, height, title.data(), target_monitor, share_context);
};

inline Window::Window(Window &&move_from)
{
    std::swap(self_, move_from.self_);
}

inline Window &
Window::operator=(Window &&move_from)
{
    std::swap(self_, move_from.self_);
}

inline Window::~Window()
{
    if (self_)
    {
        glfwDestroyWindow(self_);
    }
};

inline GLFWwindow *
Window::get() const
{
    return self_;
};

inline bool
Window::should_close() const
{
    return glfwWindowShouldClose(self_);
};

class App
{
  public:

    using Window_Id = size_t;

  public:

    App();
    ~App();

    Window &create_window(int width, int height, std::string title = {}, std::optional<std::reference_wrapper<Monitor>> monitor = {}, std::optional<std::reference_wrapper<Window>> share_context_with = {});

    void run();

  protected:

    std::map<Window_Id, Window> windows_;
};

inline App::App()
{
    glfwInit();
};

inline App::~App()
{
    glfwTerminate();
};

inline Window &
App::create_window(int width, int height, std::string title, std::optional<std::reference_wrapper<Monitor>> monitor, std::optional<std::reference_wrapper<Window>> share_context_with)
{
    static std::atomic_size_t window_id {1}; // 0 means none
    auto                     &result = windows_.emplace(std::make_pair(window_id++, Window {width, height, title, monitor, share_context_with})).first->second;
    return result;
};

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
            }
        }

        for (auto wid : to_delete_windows)
        {
            windows_.erase(wid);
        }
    }
};

} // namespace glfw
