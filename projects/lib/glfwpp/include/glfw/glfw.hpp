#include <functional>
#include <cstdint>

namespace glfw::wrap
{

enum class Position : uint32_t
{
    Any = 0x80000000
};

enum class ButtonState : int32_t
{
    Release = 0,
    Press   = 1,
    Repeat  = 2
};

enum class ErrorCode : int32_t
{
    Ok                   = 0,
    NotInitialized       = 0x00010001,
    NoCurrentContext     = 0x00010002,
    InvalidEnum          = 0x00010003,
    InvalidValue         = 0x00010004,
    OutOfMemory          = 0x00010005,
    ApiUnavailable       = 0x00010006,
    VersionUnavailable   = 0x00010007,
    PlatformError        = 0x00010008,
    FormatUnavailable    = 0x00010009,
    NoWindowContext      = 0x0001000A,
    CursorUnavailable    = 0x0001000B,
    FeatureUnavailable   = 0x0001000C,
    FeatureUnimplemented = 0x0001000D,
    PlatformUnavailable  = 0x0001000E
};

enum class InitHintCode : int32_t
{
    // Shared
    Platform           = 0x00050003,
    JoystickHatButtons = 0x00050001,
    AnglePlatformType  = 0x00050002,
    // OSX specific
    CocoaChdirResources = 0x00051001,
    CocoaMenubar        = 0x00051002,
    // X11 specific
    X11XcbVulkanSurface = 0x00052001,
    // Wayland specific
    WaylandLibdecor = 0x00053001
};

enum class WindowHintCode : int32_t
{
    Focused                = 0x00020001,
    Iconified              = 0x00020002,
    Resizable              = 0x00020003,
    Visible                = 0x00020004,
    Decorated              = 0x00020005,
    AutoIconify            = 0x00020006,
    Floating               = 0x00020007,
    Maximized              = 0x00020008,
    CenterCursor           = 0x00020009,
    TransparentFrameBuffer = 0x0002000A,
    Hovered                = 0x0002000B,
    FocusOnShow            = 0x0002000C,
    MousePassthrough       = 0x0002000D,
    PositionX              = 0x0002000E,
    PositionY              = 0x0002000F,
    RedBits                = 0x00021001,
    GreenBits              = 0x00021002,
    BlueBits               = 0x00021003,
    AlphaBits              = 0x00021004,
    DepthBits              = 0x00021005,
    StencilBits            = 0x00021006,
    AccumRedBits           = 0x00021007,
    AccumGreenBits         = 0x00021008,
    AccumBlueBits          = 0x00021009,
    AccumAlphaBits         = 0x0002100A,
    AuxBuffers             = 0x0002100B,
    Stereo                 = 0x0002100C,
    Samples                = 0x0002100D,
    SrgbCapable            = 0x0002100E,
    RefreshRate            = 0x0002100F,
    DoubleBuffer           = 0x00021010,
    ClientApi              = 0x00022001,
    ContextVersionMajor    = 0x00022002,
    ContextVersionMinor    = 0x00022003,
    ContextRevision        = 0x00022004,
    ContextRobustness      = 0x00022005,
    OpenGlForwardCompat    = 0x00022006,
    ContextDebug           = 0x00022007,
    OpenGlProfile          = 0x00022008,
    ContextReleaseBehavior = 0x00022009,
    ContextNoError         = 0x0002200A,
    ContextCreationApi     = 0x0002200B,
    ScaleToMonitor         = 0x0002200C,
    ScaleFrameBuffer       = 0x0002200D,
    CocoaRetinaFrameBuffer = 0x00023001,
    CocoaFrameName         = 0x00023002,
    CocoaGraphicsSwitching = 0x00023003,
    X11ClassName           = 0x00024001,
    X11InstanceName        = 0x00024002,
    Win32KeyboardMenu      = 0x00025001,
    Win32ShowDefault       = 0x00025002,
    WaylandAppId           = 0x00026001
};

enum class InputModeCode : int32_t
{
    Cursor             = 0x00033001,
    StickyKeys         = 0x00033002,
    StickyMouseButtons = 0x00033003,
    LockKeyMods        = 0x00033004,
    RawMouseMotion     = 0x00033005
};

enum class PlatformValue : uint32_t
{
    Undefined = 0x00060005,
    Win32     = 0x00060001,
    Cocoa     = 0x00060002,
    Wayland   = 0x00060003,
    X11       = 0x00060004,
    Any       = 0x00060000
};

enum class AnglePlatformTypeValue : int32_t
{
    None     = 0x00037001,
    OpenGl   = 0x00037002,
    OpenGLES = 0x00037003,
    D3D9     = 0x00037004,
    D3D11    = 0x00037005,
    Vulkan   = 0x00037007,
    Metal    = 0x00037008
};

enum class ContextRobustnessValue : int32_t
{
    NoRobustness        = 0,
    NoResetNotification = 0x00031001,
    LoseContextOnReset  = 0x00031002
};

enum class ClientApiValue : int32_t
{
    None     = 0,
    OpenGL   = 0x00030001,
    OpenGLES = 0x00030002
};

enum class ContextApiValue : int32_t
{
    Native = 0x00036001,
    Egl    = 0x00036002,
    Osmesa = 0x00036003
};

enum class WaylandLibdecorValue : int32_t
{
    Prefer  = 0x00038001,
    Disable = 0x00038002
};

enum class OpenGlProfileValue : int32_t
{
    Any    = 0,
    Core   = 0x00032001,
    Compat = 0x00032002
};

enum class ContextReleaseBehaviorValue : int32_t
{
    Any   = 0,
    Flush = 0x00035001,
    None  = 0x00035002
};

enum class InputModeCursorValue : int32_t
{
    Normal   = 0x00034001,
    Hidden   = 0x00034002,
    Disabled = 0x00034003,
    Captured = 0x00034004
};

enum class SamplesValue : int32_t
{
    off = 0,
    x1  = 1,
    x2  = 2,
    x4  = 4,
    x8  = 8,
    x16 = 16
};

enum class CursorShapes : int32_t
{
    Arrow        = 0x00036001,
    Ibeam        = 0x00036002,
    Crosshair    = 0x00036003,
    PointingHand = 0x00036004,
    ResizeEw     = 0x00036005,
    ResizeNs     = 0x00036006,
    ResizeNwse   = 0x00036007,
    ResizeNesw   = 0x00036008,
    ResizeAll    = 0x00036009,
    NotAllowed   = 0x0003600A
};

enum class ConnectionStatus : int32_t
{
    Connected    = 0x00040001,
    Disconnected = 0x00040002
};

enum class JoystickHatButtons : int32_t
{
    Centered  = 0,
    Up        = 1,
    Right     = 2,
    Down      = 4,
    Left      = 8,
    RightUp   = (Right | Up),
    RightDown = (Right | Down),
    LeftUp    = (Left | Up),
    LeftDown  = (Left | Down)
};

enum class Key : int32_t
{
    Unknown = -1,
    // Printable
    Sym_Space        = 32,
    Sym_Apostrophe   = 39,
    Sym_Comma        = 44,
    Sym_Minus        = 45,
    Sym_Period       = 46,
    Sym_Slash        = 47,
    Sym_0            = 48,
    Sym_1            = 49,
    Sym_2            = 50,
    Sym_3            = 51,
    Sym_4            = 52,
    Sym_5            = 53,
    Sym_6            = 54,
    Sym_7            = 55,
    Sym_8            = 56,
    Sym_9            = 57,
    Sym_Semicolon    = 59,
    Sym_Sym_Equal    = 61,
    Sym_A            = 65,
    Sym_B            = 66,
    Sym_C            = 67,
    Sym_D            = 68,
    Sym_E            = 69,
    Sym_F            = 70,
    Sym_G            = 71,
    Sym_H            = 72,
    Sym_I            = 73,
    Sym_J            = 74,
    Sym_K            = 75,
    Sym_L            = 76,
    Sym_M            = 77,
    Sym_N            = 78,
    Sym_O            = 79,
    Sym_P            = 80,
    Sym_Q            = 81,
    Sym_R            = 82,
    Sym_S            = 83,
    Sym_T            = 84,
    Sym_U            = 85,
    Sym_V            = 86,
    Sym_W            = 87,
    Sym_X            = 88,
    Sym_Y            = 89,
    Sym_Z            = 90,
    Sym_LeftBracket  = 91,
    Sym_Backslash    = 92,
    Sym_RightBracket = 93,
    Sym_GraveAccent  = 96,
    Sym_World_1      = 161,
    Sym_World_2      = 162,
    // functional
    Fn_Escape       = 256,
    Fn_Enter1       = 257,
    Fn_Tab          = 258,
    Fn_Backspace    = 259,
    Fn_Insert       = 260,
    Fn_Delete       = 261,
    Fn_Right        = 262,
    Fn_Left         = 263,
    Fn_Down         = 264,
    Fn_Up           = 265,
    Fn_PageUp       = 266,
    Fn_PageDown     = 267,
    Fn_Home         = 268,
    Fn_End          = 269,
    Fn_CapsLock     = 280,
    Fn_ScrollLock   = 281,
    Fn_NumLock      = 282,
    Fn_PrintScreen  = 283,
    Fn_Pause        = 284,
    Fn_F1           = 290,
    Fn_F2           = 291,
    Fn_F3           = 292,
    Fn_F4           = 293,
    Fn_F5           = 294,
    Fn_F6           = 295,
    Fn_F7           = 296,
    Fn_F8           = 297,
    Fn_F9           = 298,
    Fn_F10          = 299,
    Fn_F11          = 300,
    Fn_F12          = 301,
    Fn_F13          = 302,
    Fn_F14          = 303,
    Fn_F15          = 304,
    Fn_F16          = 305,
    Fn_F17          = 306,
    Fn_F18          = 307,
    Fn_F19          = 308,
    Fn_F20          = 309,
    Fn_F21          = 310,
    Fn_F22          = 311,
    Fn_F23          = 312,
    Fn_F24          = 313,
    Fn_F25          = 314,
    Fn_0            = 320,
    Fn_1            = 321,
    Fn_2            = 322,
    Fn_3            = 323,
    Fn_4            = 324,
    Fn_5            = 325,
    Fn_6            = 326,
    Fn_7            = 327,
    Fn_8            = 328,
    Fn_9            = 329,
    Fn_Decimal      = 330,
    Fn_Divide       = 331,
    Fn_Multiply     = 332,
    Fn_Subtract     = 333,
    Fn_Add          = 334,
    Fn_Enter2       = 335,
    Fn_Equal        = 336,
    Fn_LeftShift    = 340,
    Fn_LeftControl  = 341,
    Fn_LeftAlt      = 342,
    Fn_LeftSuper    = 343,
    Fn_RightShift   = 344,
    Fn_RightControl = 345,
    Fn_RightAlt     = 346,
    Fn_RightSuper   = 347,
    Fn_Menu         = 348
};

enum class ModifierKey : int32_t
{
    Shift    = 0x0001,
    Control  = 0x0002,
    Alt      = 0x0004,
    Super    = 0x0008,
    CapsLock = 0x0010,
    NumLock  = 0x0020
};

enum class MouseButton : int32_t
{
    Btn_1  = 0,
    Btn_2  = 1,
    Btn_3  = 2,
    Btn_4  = 3,
    Btn_5  = 4,
    Btn_6  = 5,
    Btn_7  = 6,
    Btn_8  = 7,
    Left   = Btn_1,
    Right  = Btn_2,
    Middle = Btn_3
};

enum JoystickButton : int32_t
{
    Btn_1  = 0,
    Btn_2  = 1,
    Btn_3  = 2,
    Btn_4  = 3,
    Btn_5  = 4,
    Btn_6  = 5,
    Btn_7  = 6,
    Btn_8  = 7,
    Btn_9  = 8,
    Btn_10 = 9,
    Btn_11 = 10,
    Btn_12 = 11,
    Btn_13 = 12,
    Btn_14 = 13,
    Btn_15 = 14,
    Btn_16 = 15
};

enum class GamepadButton : int32_t
{
    A           = 0,
    B           = 1,
    X           = 2,
    Y           = 3,
    LeftBumper  = 4,
    RightBumper = 5,
    Back        = 6,
    Start       = 7,
    Guide       = 8,
    LeftThumb   = 9,
    RightThumb  = 10,
    DpadUp      = 11,
    DpadRight   = 12,
    DpadDown    = 13,
    DpadLeft    = 14,
    Cross       = A,
    Circle      = B,
    Square      = X,
    Triangle    = Y
};

enum GamepadAxis : int32_t
{
    LeftX        = 0,
    LeftY        = 1,
    RightX       = 2,
    RightY       = 3,
    LeftTrigger  = 4,
    RightTrigger = 5
};

}; // namespace glfw::wrap

namespace glfw::wrap
{
struct Monitor; // forward decl
struct Window;  // forward decl
struct Cursor;  // forward decl

struct VidMode
{
    int32_t width;
    int32_t height;
    int32_t redBits;
    int32_t greenBits;
    int32_t blueBits;
    int32_t refreshRate;
};

struct GammaRamp
{
    unsigned short *red;
    unsigned short *green;
    unsigned short *blue;
    uint32_t        size;
};

struct Image
{
    int32_t        width;
    int32_t        height;
    unsigned char *pixels;
};

struct GamepadState
{
    unsigned char buttons[15];
    float         axes[6];
};

using AllocateFun   = void *(*)(size_t size, void *user);
using ReallocateFun = void *(*)(void *block, size_t size, void *user);
using DeallocateFun = void (*)(void *block, void *user);

struct Allocator
{
    AllocateFun   allocate;
    ReallocateFun reallocate;
    DeallocateFun deallocate;
    void         *user;
};

}; // namespace glfw::wrap

namespace glfw::wrap
{
using DefaultFun = std::function<void()>;

using ErrorFun    = void (*)(int32_t error_code, const char *description);
using MonitorFun  = void (*)(Monitor *monitor, int32_t event);
using JoystickFun = void (*)(int32_t jid, int32_t event);

using KeyFun         = void (*)(Window *window, int32_t key, int32_t scancode, int32_t action, int32_t mods);
using CharFun        = void (*)(Window *window, uint32_t codepoint);
using CharModsFun    = void (*)(Window *window, uint32_t codepoint, int32_t mods);
using MouseButtonFun = void (*)(Window *window, int32_t button, int32_t action, int32_t mods);
using CursorPosFun   = void (*)(Window *window, double xpos, double ypos);
using CursorEnterFun = void (*)(Window *window, int32_t entered);
using ScrollFun      = void (*)(Window *window, double xoffset, double yoffset);
using DropFun        = void (*)(Window *window, int32_t path_count, const char *paths[]);

using WindowPosFun          = void (*)(Window *window, int32_t xpos, int32_t ypos);
using WindowSizeFun         = void (*)(Window *window, int32_t width, int32_t height);
using WindowCloseFun        = void (*)(Window *window);
using WindowRefreshFun      = void (*)(Window *window);
using WindowFocusFun        = void (*)(Window *window, int32_t focused);
using WindowIconifyFun      = void (*)(Window *window, int32_t iconified);
using WindowMaximizeFun     = void (*)(Window *window, int32_t maximized);
using FramebufferSizeFun    = void (*)(Window *window, int32_t width, int32_t height);
using WindowContentScaleFun = void (*)(Window *window, float xscale, float yscale);

}; // namespace glfw::wrap

namespace glfw::wrap
{
using GlProc = void (*)(void);
}; // namespace glfw::wrap

namespace glfw::wrap
{
using VkProc = void (*)(void);
}; // namespace glfw::wrap

namespace glfw::wrap
{
// Glfw State

// static

void        get_version(int32_t *major, int32_t *minor, int32_t *rev);
const char *get_version_string(void);

int32_t platform_supported(int32_t platform);

int32_t get_error(const char **description);

void init_hint(int32_t hint, int32_t value);
void init_allocator(const Allocator *allocator);
#if defined(VK_VERSION_1_0)
void init_vulkan_loader(PFN_vkGetInstanceProcAddr loader);
#endif
ErrorFun set_error_callback(ErrorFun callback);

// constructor/destructor

int32_t init(void);
void    terminate(void);

int32_t get_platform(void);

Monitor **get_monitors(int32_t *count);
Monitor  *get_primary_monitor(void);

// Core callbacks

MonitorFun  set_monitor_callback(MonitorFun callback);
JoystickFun set_joystick_callback(JoystickFun callback);

// Client API

void swap_interval(int32_t interval);

int32_t extension_supported(const char *extension);
GlProc  get_proc_address(const char *procname);

int32_t      vulkan_supported(void);
const char **get_required_instance_extensions(uint32_t *count);

// handling

void poll_events(void);
void wait_events(void);
void wait_events_timeout(double timeout);
void post_empty_event(void);

// input output check

int32_t raw_mouse_motion_supported(void);

const char *get_key_name(int32_t key, int32_t scancode);
int32_t     get_key_scancode(int32_t key);

// cursors

Cursor *create_cursor(const Image *image, int32_t xhot, int32_t yhot);
Cursor *create_standard_cursor(int32_t shape);
void    destroy_cursor(Cursor *cursor);

// joystick

int32_t              joystick_present(int32_t jid);
const float         *get_joystick_axes(int32_t jid, int32_t *count);
const unsigned char *get_joystick_buttons(int32_t jid, int32_t *count);
const unsigned char *get_joystick_hats(int32_t jid, int32_t *count);
const char          *get_joystick_name(int32_t jid);
const char          *get_joystick_guid(int32_t jid);
void                 set_joystick_user_pointer(int32_t jid, void *pointer);
void                *get_joystick_user_pointer(int32_t jid);
int32_t              joystick_is_gamepad(int32_t jid);

// gamepad

int32_t     update_gamepad_mappings(const char *string);
const char *get_gamepad_name(int32_t jid);
int32_t     get_gamepad_state(int32_t jid, GamepadState *state);

// chrono

double   get_time(void);
void     set_time(double time);
uint64_t get_timer_value(void);
uint64_t get_timer_frequency(void);

// Vulkan support
#if defined(VK_VERSION_1_0)
VkResult create_window_surface(VkInstance instance, Window *window, const VkAllocationCallbacks *allocator, VkSurfaceKHR *surface);
VkProc   get_instance_proc_address(VkInstance instance, const char *procname);
int32_t  get_physical_device_presentation_support(VkInstance instance, VkPhysicalDevice device, uint32_t queuefamily);
#endif

// Window

Window *create_window(int32_t width, int32_t height, const char *title, Monitor *monitor, Window *share);
void    destroy_window(Window *window);

int32_t     window_should_close(Window *window);
const char *get_window_title(Window *window);
void        get_window_pos(Window *window, int32_t *xpos, int32_t *ypos);
void        get_window_size(Window *window, int32_t *width, int32_t *height);
void        get_window_frame_size(Window *window, int32_t *left, int32_t *top, int32_t *right, int32_t *bottom);
void        get_window_content_scale(Window *window, float *xscale, float *yscale);
float       get_window_opacity(Window *window);
Monitor    *get_window_monitor(Window *window);
int32_t     get_window_attrib(Window *window, int32_t attrib);
void       *get_window_user_pointer(Window *window);
void        get_framebuffer_size(Window *window, int32_t *width, int32_t *height);

void set_window_should_close(Window *window, int32_t value);
void set_window_title(Window *window, const char *title);
void set_window_icon(Window *window, int32_t count, const Image *images);
void set_window_pos(Window *window, int32_t xpos, int32_t ypos);
void set_window_size_limits(Window *window, int32_t minwidth, int32_t minheight, int32_t maxwidth, int32_t maxheight);
void set_window_aspect_ratio(Window *window, int32_t numer, int32_t denom);
void set_window_size(Window *window, int32_t width, int32_t height);
void set_window_opacity(Window *window, float opacity);
void set_window_monitor(Window *window, Monitor *monitor, int32_t xpos, int32_t ypos, int32_t width, int32_t height, int32_t refreshRate);
void set_window_attrib(Window *window, int32_t attrib, int32_t value);
void set_window_user_pointer(Window *window, void *pointer);

// window events

WindowPosFun          set_window_pos_callback(Window *window, WindowPosFun callback);
WindowSizeFun         set_window_size_callback(Window *window, WindowSizeFun callback);
WindowCloseFun        set_window_close_callback(Window *window, WindowCloseFun callback);
WindowRefreshFun      set_window_refresh_callback(Window *window, WindowRefreshFun callback);
WindowFocusFun        set_window_focus_callback(Window *window, WindowFocusFun callback);
WindowIconifyFun      set_window_iconify_callback(Window *window, WindowIconifyFun callback);
WindowMaximizeFun     set_window_maximize_callback(Window *window, WindowMaximizeFun callback);
FramebufferSizeFun    set_framebuffer_size_callback(Window *window, FramebufferSizeFun callback);
WindowContentScaleFun set_window_content_scale_callback(Window *window, WindowContentScaleFun callback);

// window input/output

void set_input_mode(Window *window, int32_t mode, int32_t value);
void set_cursor_pos(Window *window, double xpos, double ypos);
void set_cursor(Window *window, Cursor *cursor);
void set_clipboard_string(Window *window, const char *string);

int32_t     get_input_mode(Window *window, int32_t mode);
int32_t     get_key(Window *window, int32_t key);
int32_t     get_mouse_button(Window *window, int32_t button);
void        get_cursor_pos(Window *window, double *xpos, double *ypos);
const char *get_clipboard_string(Window *window);

KeyFun         set_key_callback(Window *window, KeyFun callback);
CharFun        set_char_callback(Window *window, CharFun callback);
CharModsFun    set_char_mods_callback(Window *window, CharModsFun callback);
MouseButtonFun set_mouse_button_callback(Window *window, MouseButtonFun callback);
CursorPosFun   set_cursor_pos_callback(Window *window, CursorPosFun callback);
CursorEnterFun set_cursor_enter_callback(Window *window, CursorEnterFun callback);
ScrollFun      set_scroll_callback(Window *window, ScrollFun callback);
DropFun        set_drop_callback(Window *window, DropFun callback);

// window control

void iconify_window(Window *window);
void restore_window(Window *window);
void maximize_window(Window *window);
void show_window(Window *window);
void hide_window(Window *window);
void focus_window(Window *window);
void request_window_attention(Window *window);

// window Context

void make_context_current(Window *window);
void swap_buffers(Window *window);

// monitor

void             get_monitor_pos(Monitor *monitor, int32_t *xpos, int32_t *ypos);
void             get_monitor_workarea(Monitor *monitor, int32_t *xpos, int32_t *ypos, int32_t *width, int32_t *height);
void             get_monitor_physical_size(Monitor *monitor, int32_t *widthMM, int32_t *heightMM);
void             get_monitor_content_scale(Monitor *monitor, float *xscale, float *yscale);
const char      *get_monitor_name(Monitor *monitor);
void             set_monitor_user_pointer(Monitor *monitor, void *pointer);
void            *get_monitor_user_pointer(Monitor *monitor);
const VidMode   *get_video_modes(Monitor *monitor, int32_t *count);
const VidMode   *get_video_mode(Monitor *monitor);
void             set_gamma(Monitor *monitor, float gamma);
const GammaRamp *get_gamma_ramp(Monitor *monitor);
void             set_gamma_ramp(Monitor *monitor, const GammaRamp *ramp);

} // namespace glfw::wrap
