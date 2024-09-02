#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <boost/signals2/signal.hpp>

#include <iostream>

#include <string_view>

#include <vector>
#include <set>
#include <unordered_set>
#include <map>
#include <unordered_map>
#include <variant>
#include <optional>
#include <functional>

#include <algorithm>

#include <atomic>

#include <cstdint>
#include <cassert>

namespace glfw
{

class Monitor;       // forward decl
class Window_Hints;  // forward decl
class Window;        // forward decl
class Context_Hints; // forward decl
class Context;       // forward decl

constexpr size_t id_none {0};
constexpr size_t id_start {1};

namespace window_hint
{
    enum class Code : int32_t
    {
        Focused                = GLFW_FOCUSED,
        Iconified              = GLFW_ICONIFIED,
        Resizable              = GLFW_RESIZABLE,
        Visible                = GLFW_VISIBLE,
        Decorated              = GLFW_DECORATED,
        AutoIconify            = GLFW_AUTO_ICONIFY,
        Floating               = GLFW_FLOATING,
        Maximized              = GLFW_MAXIMIZED,
        CenterCursor           = GLFW_CENTER_CURSOR,
        TransparentFrameBuffer = GLFW_TRANSPARENT_FRAMEBUFFER,
        Hovered                = GLFW_HOVERED,
        FocusOnShow            = GLFW_FOCUS_ON_SHOW,
        MousePassthrough       = GLFW_MOUSE_PASSTHROUGH,
        PositionX              = GLFW_POSITION_X,
        PositionY              = GLFW_POSITION_Y,
        RedBits                = GLFW_RED_BITS,
        GreenBits              = GLFW_GREEN_BITS,
        BlueBits               = GLFW_BLUE_BITS,
        AlphaBits              = GLFW_ALPHA_BITS,
        DepthBits              = GLFW_DEPTH_BITS,
        StencilBits            = GLFW_STENCIL_BITS,
        AccumRedBits           = GLFW_ACCUM_RED_BITS,
        AccumGreenBits         = GLFW_ACCUM_GREEN_BITS,
        AccumBlueBits          = GLFW_ACCUM_BLUE_BITS,
        AccumAlphaBits         = GLFW_ACCUM_ALPHA_BITS,
        AuxBuffers             = GLFW_AUX_BUFFERS,
        Stereo                 = GLFW_STEREO,
        Samples                = GLFW_SAMPLES,
        SrgbCapable            = GLFW_SRGB_CAPABLE,
        RefreshRate            = GLFW_REFRESH_RATE,
        DoubleBuffer           = GLFW_DOUBLEBUFFER,
        ClientApi              = GLFW_CLIENT_API,
        ContextVersionMajor    = GLFW_CONTEXT_VERSION_MAJOR,
        ContextVersionMinor    = GLFW_CONTEXT_VERSION_MINOR,
        ContextRevision        = GLFW_CONTEXT_REVISION,
        ContextRobustness      = GLFW_CONTEXT_ROBUSTNESS,
        OpenglForwardCompat    = GLFW_OPENGL_FORWARD_COMPAT,
        ContextDebug           = GLFW_CONTEXT_DEBUG,
        OpenglDebugContext     = GLFW_OPENGL_DEBUG_CONTEXT,
        OpenglProfile          = GLFW_OPENGL_PROFILE,
        ContextReleaseBehavior = GLFW_CONTEXT_RELEASE_BEHAVIOR,
        ContextNoError         = GLFW_CONTEXT_NO_ERROR,
        ContextCreationApi     = GLFW_CONTEXT_CREATION_API,
        ScaleToMonitor         = GLFW_SCALE_TO_MONITOR,
        ScaleFrameBuffer       = GLFW_SCALE_FRAMEBUFFER,
        CocoaRetinaFrameBuffer = GLFW_COCOA_RETINA_FRAMEBUFFER,
        CocoaFrameName         = GLFW_COCOA_FRAME_NAME,
        CocoaGraphicsSwitching = GLFW_COCOA_GRAPHICS_SWITCHING,
        X11ClassName           = GLFW_X11_CLASS_NAME,
        X11InstanceName        = GLFW_X11_INSTANCE_NAME,
        Win32KeyboardMenu      = GLFW_WIN32_KEYBOARD_MENU,
        Win32ShowDefault       = GLFW_WIN32_SHOWDEFAULT,
        WaylandAppId           = GLFW_WAYLAND_APP_ID
    };

    enum Client_Api : int32_t
    {
        None     = GLFW_NO_API,
        OpenGL   = GLFW_OPENGL_API,
        OpenGLES = GLFW_OPENGL_ES_API
    };

    enum Samples : uint8_t
    {
        off = 0,
        x1  = 1,
        x2  = 2,
        x4  = 4,
        x8  = 8,
        x16 = 16
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
  public: // types

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

    using Signal_Pos              = boost::signals2::signal<void(Window &, int /*xpos*/, int /*ypos*/)>;
    using Signal_Size             = boost::signals2::signal<void(Window &, int /*width*/, int /*height*/)>;
    using Signal_Close            = boost::signals2::signal<void(Window &)>;
    using Signal_Refresh          = boost::signals2::signal<void(Window &)>;
    using Signal_Focus            = boost::signals2::signal<void(Window &, int /*focused*/)>;
    using Signal_Iconify          = boost::signals2::signal<void(Window &, int /*iconified*/)>;
    using Signal_Maximize         = boost::signals2::signal<void(Window &, int /*maximized*/)>;
    using Signal_Framebuffer_Size = boost::signals2::signal<void(Window &, int /*width*/, int /*height*/)>;
    using Signal_Content_Scale    = boost::signals2::signal<void(Window &, float /*xscale*/, float /*yscale*/)>;
    using Signal_Key              = boost::signals2::signal<void(Window &, int /*key*/, int /*scancode*/, int /*action*/, int /*mods*/)>;
    using Signal_Char             = boost::signals2::signal<void(Window &, unsigned /*codepoint*/)>;
    using Signal_Char_Mods        = boost::signals2::signal<void(Window &, unsigned /*codepoint*/, int /*mods*/)>;
    using Signal_Mouse_Button     = boost::signals2::signal<void(Window &, int /*button*/, int /*action*/, int /*mods*/)>;
    using Signal_Cursor_Pos       = boost::signals2::signal<void(Window &, double /*xpos*/, double /*ypos*/)>;
    using Signal_Cursor_Enter     = boost::signals2::signal<void(Window &, int /*entered*/)>;
    using Signal_Scroll           = boost::signals2::signal<void(Window &, double /*xoffset*/, double /*yoffset*/)>;
    using Signal_Drop             = boost::signals2::signal<void(Window &, int /*path_count*/, /*paths*/ const char **)>;

  private: // hidden constructor

    Window(Context *owner, int width, int height, std::string title = {}, std::optional<std::reference_wrapper<Monitor>> monitor = {}, std::optional<std::reference_wrapper<Window>> share_context_with = {});
    Window(Window &copy_from)            = delete;
    Window &operator=(Window &copy_from) = delete;

  public: // public constructors

    Window(Window &&move_from) noexcept(false);
    Window &operator=(Window &&move_from) noexcept(false);

    ~Window() noexcept(true);

    GLFWwindow *get() const;

  public: // setters/getters

    void set_title(std::string);
    void set_icon(int count, GLFWimage *images);
    void set_pos(int xpos, int ypos);
    void set_size_limits(int minwidth, int minheight, int maxwidth, int maxheight);
    void set_aspect_ratio(int numer, int denom);
    void set_size(int width, int height);
    void set_opacity(float opacity);

    bool should_close() const;

  public: // context control

    void make_current(bool is_on = true) const;
    void swap_buffers() const;

  public: // signals

    Signal_Pos              on_window_pos;
    Signal_Size             on_size;
    Signal_Close            on_close;
    Signal_Refresh          on_refresh;
    Signal_Focus            on_focus;
    Signal_Iconify          on_iconify;
    Signal_Maximize         on_maximize;
    Signal_Framebuffer_Size on_framebuffer_size;
    Signal_Content_Scale    on_content_scale;
    Signal_Key              on_key;
    Signal_Char             on_char;
    Signal_Char_Mods        on_char_mods;
    Signal_Mouse_Button     on_mouse_button;
    Signal_Cursor_Pos       on_cursor_pos;
    Signal_Cursor_Enter     on_cursor_enter;
    Signal_Scroll           on_scroll;
    Signal_Drop             on_drop;

  protected:

    GLFWwindow *self_  = nullptr;
    Context    *owner_ = nullptr;

  protected:

    friend class Context;

  private: // for signals support

    struct Window_Callback_Context; // forward decl

    void setup_default_callbacks();

    static void
    default_window_pos_clb(GLFWwindow *self, int xpos, int ypos);

    static void
    default_size_clb(GLFWwindow *self, int width, int height);

    static void
    default_close_clb(GLFWwindow *self);

    static void
    default_refresh_clb(GLFWwindow *self);

    static void
    default_focus_clb(GLFWwindow *self, int focused);

    static void
    default_iconify_clb(GLFWwindow *self, int iconified);

    static void
    default_maximize_clb(GLFWwindow *self, int maximized);

    static void
    default_framebuffer_size_clb(GLFWwindow *self, int width, int height);

    static void
    default_content_scale_clb(GLFWwindow *self, float xscale, float yscale);

    static void
    default_key_clb(GLFWwindow *self, int key, int scancode, int action, int mods);

    static void
    default_char_clb(GLFWwindow *self, unsigned codepoint);

    static void
    default_char_mods_clb(GLFWwindow *self, unsigned codepoint, int mods);

    static void
    default_mouse_button_clb(GLFWwindow *self, int button, int action, int mods);

    static void
    default_cursor_pos_clb(GLFWwindow *self, double xpos, double ypos);

    static void
    default_cursor_enter_clb(GLFWwindow *self, int entered);

    static void
    default_scroll_clb(GLFWwindow *self, double xoffset, double yoffset);

    static void
    default_drop_clb(GLFWwindow *self, int path_count, const char **paths);

  private: // for getting Window instance by GLFWwindow pointer in default callbacks functions

    static std::map<GLFWwindow *, Window *> windows_;
};

struct Window::Window_Callback_Context
{
    inline Window_Callback_Context(const std::map<GLFWwindow *, Window *> &windows_db)
        : windows_db_(windows_db)
    {
    }

    inline Window &
    getw(GLFWwindow *w) const
    {
        return *windows_db_.at(w);
    };

  protected:

    const std::map<GLFWwindow *, Window *> &windows_db_;
};

inline std::map<GLFWwindow *, Window *> Window::windows_ = {};

inline Window::Window(Context *owner, int width, int height, std::string title, std::optional<std::reference_wrapper<Monitor>> monitor, std::optional<std::reference_wrapper<Window>> share_context_with)
    : owner_(owner)
{
    GLFWmonitor *target_monitor = monitor.has_value() ? monitor.value().get().get() : nullptr;
    GLFWwindow  *share_context  = share_context_with.has_value() ? share_context_with.value().get().get() : nullptr;

    self_ = glfwCreateWindow(width, height, title.data(), target_monitor, share_context);

    setup_default_callbacks();
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
        windows_.erase(self_);
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
Window::make_current(bool is_on) const
{
    glfwMakeContextCurrent((is_on) ? self_ : nullptr);
}

inline void
Window::swap_buffers() const
{
    glfwSwapBuffers(self_);
}

inline void
Window::setup_default_callbacks()
{
    glfwSetWindowPosCallback(self_, default_window_pos_clb);
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

    windows_.insert(std::make_pair(self_, this));
    auto *clb_context = new Window_Callback_Context {windows_};
    glfwSetWindowUserPointer(self_, clb_context);
}

inline void
Window::default_window_pos_clb(GLFWwindow *self, int xpos, int ypos)
{
    auto &context = *static_cast<Window_Callback_Context *>(glfwGetWindowUserPointer(self));
    assert(self == context.getw(self).get());
    context.getw(self).on_window_pos(context.getw(self), xpos, ypos);
};

inline void
Window::default_size_clb(GLFWwindow *self, int width, int height)
{
    auto &context = *static_cast<Window_Callback_Context *>(glfwGetWindowUserPointer(self));
    assert(self == context.getw(self).get());
    context.getw(self).on_size(context.getw(self), width, height);
};

inline void
Window::default_close_clb(GLFWwindow *self)
{
    auto &context = *static_cast<Window_Callback_Context *>(glfwGetWindowUserPointer(self));
    assert(self == context.getw(self).get());
    context.getw(self).on_close(context.getw(self));
};

inline void
Window::default_refresh_clb(GLFWwindow *self)
{
    auto &context = *static_cast<Window_Callback_Context *>(glfwGetWindowUserPointer(self));
    assert(self == context.getw(self).get());
    context.getw(self).on_refresh(context.getw(self));
};

inline void
Window::default_focus_clb(GLFWwindow *self, int focused)
{
    auto &context = *static_cast<Window_Callback_Context *>(glfwGetWindowUserPointer(self));
    assert(self == context.getw(self).get());
    context.getw(self).on_focus(context.getw(self), focused);
};

inline void
Window::default_iconify_clb(GLFWwindow *self, int iconified)
{
    auto &context = *static_cast<Window_Callback_Context *>(glfwGetWindowUserPointer(self));
    assert(self == context.getw(self).get());
    context.getw(self).on_iconify(context.getw(self), iconified);
};

inline void
Window::default_maximize_clb(GLFWwindow *self, int maximized)
{
    auto &context = *static_cast<Window_Callback_Context *>(glfwGetWindowUserPointer(self));
    assert(self == context.getw(self).get());
    context.getw(self).on_maximize(context.getw(self), maximized);
};

inline void
Window::default_framebuffer_size_clb(GLFWwindow *self, int width, int height)
{
    auto &context = *static_cast<Window_Callback_Context *>(glfwGetWindowUserPointer(self));
    assert(self == context.getw(self).get());
    context.getw(self).on_framebuffer_size(context.getw(self), width, height);
};

inline void
Window::default_content_scale_clb(GLFWwindow *self, float xscale, float yscale)
{
    auto &context = *static_cast<Window_Callback_Context *>(glfwGetWindowUserPointer(self));
    assert(self == context.getw(self).get());
    context.getw(self).on_content_scale(context.getw(self), xscale, yscale);
};

inline void
Window::default_key_clb(GLFWwindow *self, int key, int scancode, int action, int mods)
{
    auto &context = *static_cast<Window_Callback_Context *>(glfwGetWindowUserPointer(self));
    assert(self == context.getw(self).get());
    context.getw(self).on_key(context.getw(self), key, scancode, action, mods);
};

inline void
Window::default_char_clb(GLFWwindow *self, unsigned codepoint)
{
    auto &context = *static_cast<Window_Callback_Context *>(glfwGetWindowUserPointer(self));
    assert(self == context.getw(self).get());
    context.getw(self).on_char(context.getw(self), codepoint);
};

inline void
Window::default_char_mods_clb(GLFWwindow *self, unsigned codepoint, int mods)
{
    auto &context = *static_cast<Window_Callback_Context *>(glfwGetWindowUserPointer(self));
    assert(self == context.getw(self).get());
    context.getw(self).on_char_mods(context.getw(self), codepoint, mods);
};

inline void
Window::default_mouse_button_clb(GLFWwindow *self, int button, int action, int mods)
{
    auto &context = *static_cast<Window_Callback_Context *>(glfwGetWindowUserPointer(self));
    assert(self == context.getw(self).get());
    context.getw(self).on_mouse_button(context.getw(self), button, action, mods);
};

inline void
Window::default_cursor_pos_clb(GLFWwindow *self, double xpos, double ypos)
{
    auto &context = *static_cast<Window_Callback_Context *>(glfwGetWindowUserPointer(self));
    assert(self == context.getw(self).get());
    context.getw(self).on_cursor_pos(context.getw(self), xpos, ypos);
};

inline void
Window::default_cursor_enter_clb(GLFWwindow *self, int entered)
{
    auto &context = *static_cast<Window_Callback_Context *>(glfwGetWindowUserPointer(self));
    assert(self == context.getw(self).get());
    context.getw(self).on_cursor_enter(context.getw(self), entered);
};

inline void
Window::default_scroll_clb(GLFWwindow *self, double xoffset, double yoffset)
{
    auto &context = *static_cast<Window_Callback_Context *>(glfwGetWindowUserPointer(self));
    assert(self == context.getw(self).get());
    context.getw(self).on_scroll(context.getw(self), xoffset, yoffset);
};

inline void
Window::default_drop_clb(GLFWwindow *self, int path_count, const char **paths)
{
    auto &context = *static_cast<Window_Callback_Context *>(glfwGetWindowUserPointer(self));
    assert(self == context.getw(self).get());
    context.getw(self).on_drop(context.getw(self), path_count, paths);
};

namespace context_errors
{
    class platform_unavailable : public std::runtime_error
    {
      public:

        inline platform_unavailable(std::string what)
            : runtime_error(what)
        {
        }
    };

    class platform_error : public std::runtime_error
    {
      public:

        inline platform_error(std::string what)
            : runtime_error(what)
        {
        }
    };

}; // namespace context_errors

namespace context_hint
{
    enum Hint_Id : uint32_t
    {
        Platform                = GLFW_PLATFORM,
        JoystickHatButtons      = GLFW_JOYSTICK_HAT_BUTTONS,
        AnglePlatformType       = GLFW_ANGLE_PLATFORM_TYPE,
        GlfwCocoaChdirResources = GLFW_COCOA_CHDIR_RESOURCES,
        CocoaMenubar            = GLFW_COCOA_MENUBAR,
        X11XcbVulkanSurface     = GLFW_X11_XCB_VULKAN_SURFACE,
        WaylandLibdecor         = GLFW_WAYLAND_LIBDECOR
    };

    struct Platform
    {
        const Hint_Id id = Hint_Id::Platform;
        enum class Hint_Value : int32_t
        {
            Undefined = GLFW_PLATFORM_NULL,
            Win32     = GLFW_PLATFORM_WIN32,
            Cocoa     = GLFW_PLATFORM_COCOA,
            Wayland   = GLFW_PLATFORM_WAYLAND,
            X11       = GLFW_PLATFORM_X11,
            Any       = GLFW_ANY_PLATFORM
        } value = Hint_Value::Any;
    };

    struct Joystick_Hat_Buttons
    {
        const Hint_Id id    = Hint_Id::JoystickHatButtons;
        bool          value = true;
    };

    struct Angle_Platform_Type
    {
        const Hint_Id id = Hint_Id::AnglePlatformType;
        enum class Hint_Value : int32_t
        {
            None     = GLFW_ANGLE_PLATFORM_TYPE_NONE,
            OpenGl   = GLFW_ANGLE_PLATFORM_TYPE_OPENGL,
            OpenGLES = GLFW_ANGLE_PLATFORM_TYPE_OPENGLES,
            D3D9     = GLFW_ANGLE_PLATFORM_TYPE_D3D9,
            D3D11    = GLFW_ANGLE_PLATFORM_TYPE_D3D11,
            Vulkan   = GLFW_ANGLE_PLATFORM_TYPE_VULKAN
        } value = Hint_Value::None;
    };

    struct Cocoa_Chdir_Resources
    {
        const Hint_Id id    = Hint_Id::GlfwCocoaChdirResources;
        bool          value = true;
    };

    struct Cocoa_Menubar
    {
        const Hint_Id id    = Hint_Id::CocoaMenubar;
        bool          value = true;
    };

    struct X11_Xcb_Vulkan_Surface
    {
        const Hint_Id id    = Hint_Id::X11XcbVulkanSurface;
        bool          value = true;
    };

    struct Wayland_Libdecor
    {
        const Hint_Id id = Hint_Id::WaylandLibdecor;
        enum class Hint_Value : int32_t
        {
            Prefer  = GLFW_WAYLAND_PREFER_LIBDECOR,
            Disable = GLFW_WAYLAND_DISABLE_LIBDECOR
        } value = Hint_Value::Prefer;
    };
}; // namespace context_hint

class Context_Hints
{
    context_hint::Platform               Platform {};
    context_hint::Joystick_Hat_Buttons   Joystick_Hat_Buttons {};
    context_hint::Angle_Platform_Type    Angle_Platform_Type {};
    context_hint::Cocoa_Chdir_Resources  Cocoa_Chdir_Resources {};
    context_hint::Cocoa_Menubar          Cocoa_Menubar {};
    context_hint::X11_Xcb_Vulkan_Surface X11_Xcb_Vulkan_Surface {};
    context_hint::Wayland_Libdecor       Wayland_Libdecor {};
};

class Context
{
  public:

    using Hint_Platform               = context_hint::Platform;
    using Hint_Joystick_Hat_Buttons   = context_hint::Joystick_Hat_Buttons;
    using Hint_Angle_Platform_Type    = context_hint::Angle_Platform_Type;
    using Hint_Cocoa_Chdir_Resources  = context_hint::Cocoa_Chdir_Resources;
    using Hint_Cocoa_Menubar          = context_hint::Cocoa_Menubar;
    using Hint_X11_Xcb_Vulkan_Surface = context_hint::X11_Xcb_Vulkan_Surface;
    using Hint_Wayland_Libdecor       = context_hint::Wayland_Libdecor;

    using Window_Id = size_t;
    using Error_Msg = std::string_view;

    enum Error_Code : int32_t
    {
        Ok                   = GLFW_NO_ERROR,
        NotInitialized       = GLFW_NOT_INITIALIZED,
        NoCurrentContext     = GLFW_NO_CURRENT_CONTEXT,
        InvalidEnum          = GLFW_INVALID_ENUM,
        InvalidValue         = GLFW_INVALID_VALUE,
        OutOfMemory          = GLFW_OUT_OF_MEMORY,
        ApiUnavailable       = GLFW_API_UNAVAILABLE,
        VersionUnavailable   = GLFW_VERSION_UNAVAILABLE,
        PlatformError        = GLFW_PLATFORM_ERROR,
        FormatUnavailable    = GLFW_FORMAT_UNAVAILABLE,
        NoWindowContext      = GLFW_NO_WINDOW_CONTEXT,
        CursorUnavailable    = GLFW_CURSOR_UNAVAILABLE,
        FeatureUnavailable   = GLFW_FEATURE_UNAVAILABLE,
        FeatureUnimplemented = GLFW_FEATURE_UNIMPLEMENTED,
        PlatformUnavailable  = GLFW_PLATFORM_UNAVAILABLE
    };

    enum Special_Window_Id : Window_Id
    {
        shared = -1
    };

    enum Platform : int32_t
    {
        Undefined = GLFW_PLATFORM_NULL,
        Win32     = GLFW_PLATFORM_WIN32,
        Cocoa     = GLFW_PLATFORM_COCOA,
        Wayland   = GLFW_PLATFORM_WAYLAND,
        X11       = GLFW_PLATFORM_X11
    };

    struct Version; // forward decl

  public: // signal types

    using Signal_On_Window_Process = boost::signals2::signal<void(Context &app, Window_Id wid, Window &)>;
    using Signal_On_Error          = boost::signals2::signal<void(Error_Code error_code, Error_Msg description)>;

  private:

    Context();

  public:

    static Version                          version();
    static bool                             platform_supported(Platform platform);
    static std::pair<Error_Code, Error_Msg> get_error();

    static void          init_hint(Hint_Platform hint);
    static void          init_hint(Hint_Joystick_Hat_Buttons hint);
    static void          init_hint(Hint_Angle_Platform_Type hint);
    static void          init_hint(Hint_Cocoa_Chdir_Resources hint);
    static void          init_hint(Hint_Cocoa_Menubar hint);
    static void          init_hint(Hint_X11_Xcb_Vulkan_Surface hint);
    static void          init_hint(Hint_Wayland_Libdecor hint);
    static Context_Hints init_hints();
    static void          init_hints(Context_Hints hints);

  public: // initialization

    static Context &get();

    Context(const Context &copy_from)             = delete;
    Context &operator=(const Context &copy_from)  = delete;
    Context(const Context &&move_from)            = delete;
    Context &operator=(const Context &&move_from) = delete;

    ~Context();

  public: // windows/context creation

    void          reset_next_window_hints();
    void          set_next_window_hints(Window_Hints hints);
    Window_Hints &get_next_window_hints() const;
    Window       &create_window(int width, int height, std::string title = {}, std::optional<std::reference_wrapper<Monitor>> monitor = {}, std::optional<std::reference_wrapper<Window>> share_context_with = {});

  public: // main loop

    void run();

  public:

    Signal_On_Window_Process on_window_process;
    Signal_On_Error          on_error;

  protected:

    void apply_window_hints(const Window_Hints &hints);
    void apply_window_hint(const Window_Hints::Renderer &renderer);

  protected:

    static Context_Hints        next_init_hints_;
    Window_Hints                next_window_hints_ {};
    std::map<Window_Id, Window> windows_;

  private:

    void set_default_callbacks();

    void default_error_clb(int error_code, const char *description);
};

struct Context::Version
{
    int32_t major    = GLFW_VERSION_MAJOR;
    int32_t minor    = GLFW_VERSION_MINOR;
    int32_t revision = GLFW_VERSION_REVISION;

    static std::string_view string();
};

inline std::string_view
Context::Version::string()
{
    return glfwGetVersionString();
}

inline Context::Version
Context::version()
{
    Context::Version result;
    glfwGetVersion(&result.major, &result.minor, &result.revision);
    return result;
}

inline Context_Hints Context::next_init_hints_ = {};

inline bool
Context::platform_supported(Platform platform)
{
    return glfwPlatformSupported(platform);
}

inline std::pair<Context::Error_Code, std::string_view>
Context::get_error()
{
    const char *error_msg = nullptr;
    int         code      = glfwGetError(&error_msg);
    return std::make_pair(static_cast<Error_Code>(code), error_msg);
}

inline Context &
Context::get()
{
    static Context ctx;

    return ctx;
}

inline Context::Context()
{
    int res = glfwInit();
    switch (res)
    {
    case Error_Code::PlatformUnavailable:
        {
            throw context_errors::platform_unavailable("Platform unavailable");
        }
        break;
    case Error_Code::PlatformError:
        {
            throw context_errors::platform_error("Platform error");
        }
        break;
    case Error_Code::Ok:
    default:
        {
            /* do nothing */
        }
    }
}

inline Context::~Context()
{
    for (const auto &[wid, window] : windows_)
    {
        window.make_current(false);
    }
    glfwTerminate();
}

inline void
Context::reset_next_window_hints()
{
    // TODO:
}

inline void
Context::set_next_window_hints(Window_Hints hints)
{
    // TODO:
}

inline Window &
Context::create_window(int width, int height, std::string title, std::optional<std::reference_wrapper<Monitor>> monitor, std::optional<std::reference_wrapper<Window>> share_context_with)
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

    std::visit(Renderer_Api_Loader {result}, next_window_hints_.renderer);

    return result;
}

inline void
Context::run()
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

            on_window_process(*this, wid, window);

            window.swap_buffers();
        }

        for (auto wid : to_delete_windows)
        {
            windows_.erase(wid);
        }
    }
}

void
Context::apply_window_hints(const Window_Hints &hints)
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
Context::apply_window_hint(const Window_Hints::Renderer &renderer)
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

inline Context &
glfw()
{
    return Context::get();
}

} // namespace glfw
