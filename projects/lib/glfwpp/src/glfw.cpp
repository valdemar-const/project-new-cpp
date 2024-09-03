#include <glfw/glfw.hpp>

#include <glfw/glfw3.h>

#include <type_traits>

namespace glfw::wrap
{

struct Init_Hint_Applier
{
    template<typename Hint>
    void
    operator()(Hint hint) const
    {
        glfwInitHint((int32_t)hint.hint, (int32_t)hint.value);
    }

    template<>
    void
    operator()<std::monostate>(std::monostate hint) const
    {
    }
};

struct Window_Hint_Applier
{
    template<typename Hint>
    void
    operator()(Hint hint) const
    {
        using T = std::decay_t<decltype(hint.value)>;
        if constexpr (std::is_same_v<T, std::string>)
        {
            glfwWindowHintString((int32_t)hint.hint, hint.value.data());
        }
        else
        {
            glfwWindowHint((int32_t)hint.hint, (int32_t)hint.value);
        }
    }

    template<>
    void
    operator()<std::monostate>(std::monostate hint) const
    {
    }
};

void
get_version(int32_t *major, int32_t *minor, int32_t *rev)
{
    glfwGetVersion(major, minor, rev);
}

std::string_view
get_version_string(void)
{
    return {glfwGetVersionString()};
}

bool
platform_supported(Platform platform)
{
    return glfwPlatformSupported((int32_t)platform);
}

std::pair<ErrorCode, std::string_view>
get_error()
{
    const char *description = nullptr;
    ErrorCode   code        = static_cast<ErrorCode>(glfwGetError(&description));
    return std::make_pair(code, description);
}

void
init_hint(Init_Hint hint)
{
    std::visit(Init_Hint_Applier {}, hint);
}

void
init_allocator(const Allocator *allocator)
{
    glfwInitAllocator((GLFWallocator *)allocator);
}

#if defined(VK_VERSION_1_0)
void
init_vulkan_loader(PFN_vkGetInstanceProcAddr loader)
{
    glfwInitVulkanLoader(loader);
}
#endif

ErrorFun
set_error_callback(ErrorFun callback)
{
    return glfwSetErrorCallback(callback);
}

// constructor/destructor

ErrorCode
init()
{
    return static_cast<ErrorCode>(glfwInit());
}

void
terminate(void)
{
    glfwTerminate();
}

Platform
get_platform(void)
{
    return static_cast<Platform>(glfwGetPlatform());
}

std::vector<Monitor *>
get_monitors()
{
    std::vector<Monitor *> result;

    int32_t count = 0;
    auto    data  = (Monitor **)glfwGetMonitors(&count);
    result.reserve(count);
    for (auto i = 0; i < count; ++i)
    {
        result.push_back(data[i]);
    }
    return result;
}

Monitor *
get_primary_monitor(void)
{
    return (Monitor *)glfwGetPrimaryMonitor();
}

// Core callbacks

MonitorFun
set_monitor_callback(MonitorFun callback)
{
    return (MonitorFun)glfwSetMonitorCallback((GLFWmonitorfun)callback);
}

JoystickFun
set_joystick_callback(JoystickFun callback)
{
    return (JoystickFun)glfwSetJoystickCallback(callback);
}

// Client API

void
swap_interval(int32_t interval)
{
    glfwSwapInterval(interval);
}

bool
extension_supported(const char *extension)
{
    return glfwExtensionSupported(extension);
}

GlProc
get_proc_address(const char *procname)
{
    return glfwGetProcAddress(procname);
}

bool
vulkan_supported(void)
{
    return glfwVulkanSupported();
}

std::vector<std::string_view>
get_required_instance_extensions()
{
    std::vector<std::string_view> result;

    uint32_t count = 0;
    auto     data  = glfwGetRequiredInstanceExtensions(&count);
    for (int i = 0; i < count; ++i)
    {
        result.push_back(data[i]);
    }
    return result;
}

// handling

void
poll_events(void)
{
    glfwPollEvents();
}

void
wait_events(void)
{
    glfwWaitEvents();
}

void
wait_events_timeout(double timeout)
{
    glfwWaitEventsTimeout(timeout);
}

void
post_empty_event(void)
{
    glfwPostEmptyEvent();
}

// input output check

bool
raw_mouse_motion_supported(void)
{
    return glfwRawMouseMotionSupported();
}

std::string_view
get_key_name(int32_t key, int32_t scancode)
{
    return {glfwGetKeyName(key, scancode)};
}

int32_t
get_key_scancode(int32_t key)
{
    return glfwGetKeyScancode(key);
}

// cursors

Cursor *
create_cursor(const Image *image, int32_t xhot, int32_t yhot)
{
    return (Cursor *)glfwCreateCursor((GLFWimage *)image, xhot, yhot);
}

Cursor *
create_standard_cursor(int32_t shape)
{
    return (Cursor *)glfwCreateStandardCursor(shape);
}

void
destroy_cursor(Cursor *cursor)
{
    glfwDestroyCursor((GLFWcursor *)cursor);
}

// joystick

int32_t
joystick_present(int32_t jid)
{
    return glfwJoystickPresent(jid);
}

std::vector<float>
get_joystick_axes(int32_t jid)
{
    std::vector<float> result;

    int32_t count = 0;
    auto    data  = glfwGetJoystickAxes(jid, &count);
    for (int i = 0; i < count; ++i)
    {
        result.push_back(data[i]);
    }

    return result;
}

std::vector<uint8_t>
get_joystick_buttons(int32_t jid)
{
    std::vector<uint8_t> result;

    int32_t count = 0;
    auto    data  = glfwGetJoystickButtons(jid, &count);
    for (int i = 0; i < count; ++i)
    {
        result.push_back(data[i]);
    }

    return result;
}

std::vector<uint8_t>
get_joystick_hats(int32_t jid)
{
    std::vector<uint8_t> result;

    int32_t count = 0;
    auto    data  = glfwGetJoystickHats(jid, &count);
    for (int i = 0; i < count; ++i)
    {
        result.push_back(data[i]);
    }

    return result;
}

std::string_view
get_joystick_name(int32_t jid)
{
    return {glfwGetJoystickName(jid)};
}

const char *
get_joystick_guid(int32_t jid)
{
    return glfwGetJoystickGUID(jid);
}

void
set_joystick_user_pointer(int32_t jid, void *pointer)
{
    glfwSetJoystickUserPointer(jid, pointer);
}

void *
get_joystick_user_pointer(int32_t jid)
{
    return glfwGetJoystickUserPointer(jid);
}

int32_t
joystick_is_gamepad(int32_t jid)
{
    return glfwJoystickIsGamepad(jid);
}

// gamepad

int32_t
update_gamepad_mappings(const char *string)
{
    return glfwUpdateGamepadMappings(string);
}

std::string_view
get_gamepad_name(int32_t jid)
{
    return {glfwGetGamepadName(jid)};
}

int32_t
get_gamepad_state(int32_t jid, GamepadState *state)
{
    return glfwGetGamepadState(jid, (GLFWgamepadstate *)state);
}

// chrono

double
get_time(void)
{
    return glfwGetTime();
}

void
set_time(double time)
{
    glfwSetTime(time);
}

uint64_t
get_timer_value(void)
{
    return glfwGetTimerValue();
}

uint64_t
get_timer_frequency(void)
{
    return glfwGetTimerFrequency();
}

// Vulkan support
#if defined(VK_VERSION_1_0)
VkResult
create_window_surface(VkInstance instance, Window *window, const VkAllocationCallbacks *allocator, VkSurfaceKHR *surface)
{
    return glfwCreateWindowSurface();
}

VkProc
get_instance_proc_address(VkInstance instance, const char *procname)
{
    return glfwGetInstanceProcAddress();
}

int32_t
get_physical_device_presentation_support(VkInstance instance, VkPhysicalDevice device, uint32_t queuefamily)
{
    return glfwGetPhysicalDevicePresentationSupport();
}
#endif
// Window

void
default_window_hints()
{
    glfwDefaultWindowHints();
}

void
window_hint(Window_Hint hint)
{
    std::visit(Window_Hint_Applier {}, hint);
}

std::string
window_hint_string(int hint)
{
    std::string result;
    result.resize(128);
    glfwWindowHintString(hint, result.data());
    return result.data();
}

Window *
create_window(int32_t width, int32_t height, std::string_view title, Monitor *monitor, Window *share)
{
    return (Window *)glfwCreateWindow(width, height, title.data(), (GLFWmonitor *)monitor, (GLFWwindow *)share);
}

void
destroy_window(Window *window)
{
    return glfwDestroyWindow((GLFWwindow *)window);
}

int32_t
window_should_close(Window *window)
{
    return glfwWindowShouldClose((GLFWwindow *)window);
}

std::string_view
get_window_title(Window *window)
{
    return {glfwGetWindowTitle((GLFWwindow *)window)};
}

void
get_window_pos(Window *window, int32_t *xpos, int32_t *ypos)
{
    glfwGetWindowPos((GLFWwindow *)window, xpos, ypos);
}

void
get_window_size(Window *window, int32_t *width, int32_t *height)
{
    glfwGetWindowSize((GLFWwindow *)window, width, height);
}

void
get_window_frame_size(Window *window, int32_t *left, int32_t *top, int32_t *right, int32_t *bottom)
{
    glfwGetWindowFrameSize((GLFWwindow *)window, left, top, right, bottom);
}

void
get_window_content_scale(Window *window, float *xscale, float *yscale)
{
    glfwGetWindowContentScale((GLFWwindow *)window, xscale, yscale);
}

float
get_window_opacity(Window *window)
{
    return glfwGetWindowOpacity((GLFWwindow *)window);
}

Monitor *
get_window_monitor(Window *window)
{
    return (Monitor *)glfwGetWindowMonitor((GLFWwindow *)window);
}

int32_t
get_window_attrib(Window *window, int32_t attrib)
{
    return glfwGetWindowAttrib((GLFWwindow *)window, attrib);
}

void *
get_window_user_pointer(Window *window)
{
    return glfwGetWindowUserPointer((GLFWwindow *)window);
}

void
get_framebuffer_size(Window *window, int32_t *width, int32_t *height)
{
    glfwGetFramebufferSize((GLFWwindow *)window, width, height);
}

void
set_window_should_close(Window *window, int32_t value)
{
    glfwSetWindowShouldClose((GLFWwindow *)window, value);
}

void
set_window_title(Window *window, const char *title)
{
    glfwSetWindowTitle((GLFWwindow *)window, title);
}

void
set_window_icon(Window *window, int32_t count, const Image *images)
{
    glfwSetWindowIcon((GLFWwindow *)window, count, (GLFWimage *)images);
}

void
set_window_pos(Window *window, int32_t xpos, int32_t ypos)
{
    glfwSetWindowPos((GLFWwindow *)window, xpos, ypos);
}

void
set_window_size_limits(Window *window, int32_t minwidth, int32_t minheight, int32_t maxwidth, int32_t maxheight)
{
    glfwSetWindowSizeLimits((GLFWwindow *)window, minwidth, minheight, maxwidth, maxheight);
}

void
set_window_aspect_ratio(Window *window, int32_t numer, int32_t denom)
{
    glfwSetWindowAspectRatio((GLFWwindow *)window, numer, denom);
}

void
set_window_size(Window *window, int32_t width, int32_t height)
{
    glfwSetWindowSize((GLFWwindow *)window, width, height);
}

void
set_window_opacity(Window *window, float opacity)
{
    glfwSetWindowOpacity((GLFWwindow *)window, opacity);
}

void
set_window_monitor(Window *window, Monitor *monitor, int32_t xpos, int32_t ypos, int32_t width, int32_t height, int32_t refreshRate)
{
    glfwSetWindowMonitor((GLFWwindow *)window, (GLFWmonitor *)monitor, xpos, ypos, width, height, refreshRate);
}

void
set_window_attrib(Window *window, int32_t attrib, int32_t value)
{
    glfwSetWindowAttrib((GLFWwindow *)window, attrib, value);
}

void
set_window_user_pointer(Window *window, void *pointer)
{
    glfwSetWindowUserPointer((GLFWwindow *)window, pointer);
}

// window events

WindowPosFun
set_window_pos_callback(Window *window, WindowPosFun callback)
{
    return (WindowPosFun)glfwSetWindowPosCallback((GLFWwindow *)window, (GLFWwindowposfun)callback);
}

WindowSizeFun
set_window_size_callback(Window *window, WindowSizeFun callback)
{
    return (WindowSizeFun)glfwSetWindowSizeCallback((GLFWwindow *)window, (GLFWwindowsizefun)callback);
}

WindowCloseFun
set_window_close_callback(Window *window, WindowCloseFun callback)
{
    return (WindowCloseFun)glfwSetWindowCloseCallback((GLFWwindow *)window, (GLFWwindowclosefun)callback);
}

WindowRefreshFun
set_window_refresh_callback(Window *window, WindowRefreshFun callback)
{
    return (WindowRefreshFun)glfwSetWindowRefreshCallback((GLFWwindow *)window, (GLFWwindowrefreshfun)callback);
}

WindowFocusFun
set_window_focus_callback(Window *window, WindowFocusFun callback)
{
    return (WindowFocusFun)glfwSetWindowFocusCallback((GLFWwindow *)window, (GLFWwindowfocusfun)callback);
}

WindowIconifyFun
set_window_iconify_callback(Window *window, WindowIconifyFun callback)
{
    return (WindowIconifyFun)glfwSetWindowIconifyCallback((GLFWwindow *)window, (GLFWwindowiconifyfun)callback);
}

WindowMaximizeFun
set_window_maximize_callback(Window *window, WindowMaximizeFun callback)
{
    return (WindowMaximizeFun)glfwSetWindowMaximizeCallback((GLFWwindow *)window, (GLFWwindowmaximizefun)callback);
}

FramebufferSizeFun
set_framebuffer_size_callback(Window *window, FramebufferSizeFun callback)
{
    return (FramebufferSizeFun)glfwSetFramebufferSizeCallback((GLFWwindow *)window, (GLFWframebuffersizefun)callback);
}

WindowContentScaleFun
set_window_content_scale_callback(Window *window, WindowContentScaleFun callback)
{
    return (WindowContentScaleFun)glfwSetWindowContentScaleCallback((GLFWwindow *)window, (GLFWwindowcontentscalefun)callback);
}

// window input/output

void
set_input_mode(Window *window, int32_t mode, int32_t value)
{
    glfwSetInputMode((GLFWwindow *)window, mode, value);
}

void
set_cursor_pos(Window *window, double xpos, double ypos)
{
    glfwSetCursorPos((GLFWwindow *)window, xpos, ypos);
}

void
set_cursor(Window *window, Cursor *cursor)
{
    glfwSetCursor((GLFWwindow *)window, (GLFWcursor *)cursor);
}

void
set_clipboard_string(Window *window, const char *string)
{
    glfwSetClipboardString((GLFWwindow *)window, string);
}

int32_t
get_input_mode(Window *window, int32_t mode)
{
    return glfwGetInputMode((GLFWwindow *)window, mode);
}

int32_t
get_key(Window *window, int32_t key)
{
    return glfwGetKey((GLFWwindow *)window, key);
}

int32_t
get_mouse_button(Window *window, int32_t button)
{
    return glfwGetMouseButton((GLFWwindow *)window, button);
}

void
get_cursor_pos(Window *window, double *xpos, double *ypos)
{
    glfwGetCursorPos((GLFWwindow *)window, xpos, ypos);
}

std::string_view
get_clipboard_string(Window *window)
{
    return {glfwGetClipboardString((GLFWwindow *)window)};
}

KeyFun
set_key_callback(Window *window, KeyFun callback)
{
    return (KeyFun)glfwSetKeyCallback((GLFWwindow *)window, (GLFWkeyfun)callback);
}

CharFun
set_char_callback(Window *window, CharFun callback)
{
    return (CharFun)glfwSetCharCallback((GLFWwindow *)window, (GLFWcharfun)callback);
}

CharModsFun
set_char_mods_callback(Window *window, CharModsFun callback)
{
    return (CharModsFun)glfwSetCharModsCallback((GLFWwindow *)window, (GLFWcharmodsfun)callback);
}

MouseButtonFun
set_mouse_button_callback(Window *window, MouseButtonFun callback)
{
    return (MouseButtonFun)glfwSetMouseButtonCallback((GLFWwindow *)window, (GLFWmousebuttonfun)callback);
}

CursorPosFun
set_cursor_pos_callback(Window *window, CursorPosFun callback)
{
    return (CursorPosFun)glfwSetCursorPosCallback((GLFWwindow *)window, (GLFWcursorposfun)callback);
}

CursorEnterFun
set_cursor_enter_callback(Window *window, CursorEnterFun callback)
{
    return (CursorEnterFun)glfwSetCursorEnterCallback((GLFWwindow *)window, (GLFWcursorenterfun)callback);
}

ScrollFun
set_scroll_callback(Window *window, ScrollFun callback)
{
    return (ScrollFun)glfwSetScrollCallback((GLFWwindow *)window, (GLFWscrollfun)callback);
}

DropFun
set_drop_callback(Window *window, DropFun callback)
{
    return (DropFun)glfwSetDropCallback((GLFWwindow *)window, (GLFWdropfun)callback);
}

// window control

void
iconify_window(Window *window)
{
    glfwIconifyWindow((GLFWwindow *)window);
}

void
restore_window(Window *window)
{
    glfwRestoreWindow((GLFWwindow *)window);
}

void
maximize_window(Window *window)
{
    glfwMaximizeWindow((GLFWwindow *)window);
}

void
show_window(Window *window)
{
    glfwShowWindow((GLFWwindow *)window);
}

void
hide_window(Window *window)
{
    glfwHideWindow((GLFWwindow *)window);
}

void
focus_window(Window *window)
{
    glfwFocusWindow((GLFWwindow *)window);
}

void
request_window_attention(Window *window)
{
    glfwRequestWindowAttention((GLFWwindow *)window);
}

// window Context

void
make_context_current(Window *window)
{
    glfwMakeContextCurrent((GLFWwindow *)window);
}

void
swap_buffers(Window *window)
{
    glfwSwapBuffers((GLFWwindow *)window);
}

// monitor

void
get_monitor_pos(Monitor *monitor, int32_t *xpos, int32_t *ypos)
{
    glfwGetMonitorPos((GLFWmonitor *)monitor, xpos, ypos);
}

void
get_monitor_workarea(Monitor *monitor, int32_t *xpos, int32_t *ypos, int32_t *width, int32_t *height)
{
    glfwGetMonitorWorkarea((GLFWmonitor *)monitor, xpos, ypos, width, height);
}

void
get_monitor_physical_size(Monitor *monitor, int32_t *widthMM, int32_t *heightMM)
{
    glfwGetMonitorPhysicalSize((GLFWmonitor *)monitor, widthMM, heightMM);
}

void
get_monitor_content_scale(Monitor *monitor, float *xscale, float *yscale)
{
    glfwGetMonitorContentScale((GLFWmonitor *)monitor, xscale, yscale);
}

std::string_view
get_monitor_name(Monitor *monitor)
{
    return {glfwGetMonitorName((GLFWmonitor *)monitor)};
}

void
set_monitor_user_pointer(Monitor *monitor, void *pointer)
{
    glfwSetMonitorUserPointer((GLFWmonitor *)monitor, pointer);
}

void *
get_monitor_user_pointer(Monitor *monitor)
{
    return glfwGetMonitorUserPointer((GLFWmonitor *)monitor);
}

std::vector<VidMode>
get_video_modes(Monitor *monitor)
{
    std::vector<VidMode> result;

    int32_t count = 0;
    auto    data  = (VidMode *)glfwGetVideoModes((GLFWmonitor *)monitor, &count);
    for (int i = 0; i < count; ++i)
    {
        result.push_back(data[i]);
    }

    return result;
}

const VidMode *
get_video_mode(Monitor *monitor)
{
    return (VidMode *)glfwGetVideoMode((GLFWmonitor *)monitor);
}

void
set_gamma(Monitor *monitor, float gamma)
{
    glfwSetGamma((GLFWmonitor *)monitor, gamma);
}

const GammaRamp *
get_gamma_ramp(Monitor *monitor)
{
    return (GammaRamp *)glfwGetGammaRamp((GLFWmonitor *)monitor);
}

void
set_gamma_ramp(Monitor *monitor, const GammaRamp *ramp)
{
    glfwSetGammaRamp((GLFWmonitor *)monitor, (GLFWgammaramp *)ramp);
}

} // namespace glfw::wrap
