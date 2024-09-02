namespace glfw
{

const struct Version
{
    int major;
    int minor;
    int revision;
} version {GLFW_VERSION_MAJOR, GLFW_VERSION_MINOR, GLFW_VERSION_REVISION};

enum Boolean : int32_t
{
    False,
    True
};

enum Position : int32_t
{
    Any = GLFW_ANY_POSITION
};

enum class Button_State : int32_t
{
    Release = GLFW_RELEASE,
    Press   = GLFW_PRESS,
    Repeat  = GLFW_REPEAT
};

enum class Error_Code : int32_t
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

enum class Init_Hint_Code : int32_t
{
    // Shared
    Platform           = GLFW_PLATFORM,
    JoystickHatButtons = GLFW_JOYSTICK_HAT_BUTTONS,
    AnglePlatformType  = GLFW_ANGLE_PLATFORM_TYPE,
    // OSX specific
    CocoaChdirResources = GLFW_COCOA_CHDIR_RESOURCES,
    CocoaMenubar        = GLFW_COCOA_MENUBAR,
    // X11 specific
    X11XcbVulkanSurface = GLFW_X11_XCB_VULKAN_SURFACE,
    // Wayland specific
    WaylandLibdecor = GLFW_WAYLAND_LIBDECOR
};

enum class Window_Hint_Code : int32_t
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
    OpenGlForwardCompat    = GLFW_OPENGL_FORWARD_COMPAT,
    ContextDebug           = GLFW_CONTEXT_DEBUG,
    OpenGlDebugContext     = GLFW_OPENGL_DEBUG_CONTEXT,
    OpenGlProfile          = GLFW_OPENGL_PROFILE,
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

enum class Input_Mode_Code : int32_t
{
    Cursor             = GLFW_CURSOR,
    StickyKeys         = GLFW_STICKY_KEYS,
    StickyMouseButtons = GLFW_STICKY_MOUSE_BUTTONS,
    LockKeyMods        = GLFW_LOCK_KEY_MODS,
    RawMouseMotion     = GLFW_RAW_MOUSE_MOTION
};

enum class Platform_Value : int32_t
{
    Undefined = GLFW_PLATFORM_NULL,
    Win32     = GLFW_PLATFORM_WIN32,
    Cocoa     = GLFW_PLATFORM_COCOA,
    Wayland   = GLFW_PLATFORM_WAYLAND,
    X11       = GLFW_PLATFORM_X11,
    Any       = GLFW_ANY_PLATFORM
};

enum class Angle_Platform_Type_Value : int32_t
{
    None     = GLFW_ANGLE_PLATFORM_TYPE_NONE,
    OpenGl   = GLFW_ANGLE_PLATFORM_TYPE_OPENGL,
    OpenGLES = GLFW_ANGLE_PLATFORM_TYPE_OPENGLES,
    D3D9     = GLFW_ANGLE_PLATFORM_TYPE_D3D9,
    D3D11    = GLFW_ANGLE_PLATFORM_TYPE_D3D11,
    Vulkan   = GLFW_ANGLE_PLATFORM_TYPE_VULKAN
};

enum class Context_Robustness_Value : int32_t
{
    NoRobustness        = GLFW_NO_ROBUSTNESS,
    NoResetNotification = GLFW_NO_RESET_NOTIFICATION,
    LoseContextOnReset  = GLFW_LOSE_CONTEXT_ON_RESET
};

enum class Client_Api_Value : int32_t
{
    None     = GLFW_NO_API,
    OpenGL   = GLFW_OPENGL_API,
    OpenGLES = GLFW_OPENGL_ES_API
};

enum class Context_Api_Value : int32_t
{
    Native = GLFW_NATIVE_CONTEXT_API,
    Egl    = GLFW_EGL_CONTEXT_API,
    Osmesa = GLFW_OSMESA_CONTEXT_API
};

enum class Wayland_Libdecor_Value : int32_t
{
    Prefer  = GLFW_WAYLAND_PREFER_LIBDECOR,
    Disable = GLFW_WAYLAND_DISABLE_LIBDECOR
};

enum class OpenGl_Profile_Value : int32_t
{
    Any    = GLFW_OPENGL_ANY_PROFILE,
    Core   = GLFW_OPENGL_CORE_PROFILE,
    Compat = GLFW_OPENGL_COMPAT_PROFILE
};

enum class Context_Release_Behavior_Value : int32_t
{
    Any   = GLFW_ANY_RELEASE_BEHAVIOR,
    Flush = GLFW_RELEASE_BEHAVIOR_FLUSH,
    None  = GLFW_RELEASE_BEHAVIOR_NONE
};

enum class Input_Mode_Cursor_Value : int32_t
{
    Normal   = GLFW_CURSOR_NORMAL,
    Hidden   = GLFW_CURSOR_HIDDEN,
    Disabled = GLFW_CURSOR_DISABLED,
    Captured = GLFW_CURSOR_CAPTURED
};

enum class Samples_Value : int32_t
{
    off = 0,
    x1  = 1,
    x2  = 2,
    x4  = 4,
    x8  = 8,
    x16 = 16
};

enum class Cursor_Shapes : int32_t
{
    Arrow        = GLFW_ARROW_CURSOR,
    Ibeam        = GLFW_IBEAM_CURSOR,
    Crosshair    = GLFW_CROSSHAIR_CURSOR,
    PointingHand = GLFW_POINTING_HAND_CURSOR,
    ResizeEw     = GLFW_RESIZE_EW_CURSOR,
    ResizeNs     = GLFW_RESIZE_NS_CURSOR,
    ResizeNwse   = GLFW_RESIZE_NWSE_CURSOR,
    ResizeNesw   = GLFW_RESIZE_NESW_CURSOR,
    ResizeAll    = GLFW_RESIZE_ALL_CURSOR,
    NotAllowed   = GLFW_NOT_ALLOWED_CURSOR,
    Hresize      = GLFW_HRESIZE_CURSOR,
    Vresize      = GLFW_VRESIZE_CURSOR,
    Hand         = GLFW_HAND_CURSOR
};

enum class Connection_Status : int32_t
{
    Connected    = GLFW_CONNECTED,
    Disconnected = GLFW_DISCONNECTED
};

enum Joystick_Hat_Buttons : int32_t
{
    Centered  = GLFW_HAT_CENTERED,
    Up        = GLFW_HAT_UP,
    Right     = GLFW_HAT_RIGHT,
    Down      = GLFW_HAT_DOWN,
    Left      = GLFW_HAT_LEFT,
    RightUp   = GLFW_HAT_RIGHT_UP,
    RightDown = GLFW_HAT_RIGHT_DOWN,
    LeftUp    = GLFW_HAT_LEFT_UP,
    LeftDown  = GLFW_HAT_LEFT_DOWN
};

enum Key : int32_t
{
    Unknown = GLFW_KEY_UNKNOWN,
    // Printable
    k_SPACE         = GLFW_KEY_SPACE,
    k_APOSTROPHE    = GLFW_KEY_APOSTROPHE,
    k_COMMA         = GLFW_KEY_COMMA,
    k_MINUS         = GLFW_KEY_MINUS,
    k_PERIOD        = GLFW_KEY_PERIOD,
    k_SLASH         = GLFW_KEY_SLASH,
    k_0             = GLFW_KEY_0,
    k_1             = GLFW_KEY_1,
    k_2             = GLFW_KEY_2,
    k_3             = GLFW_KEY_3,
    k_4             = GLFW_KEY_4,
    k_5             = GLFW_KEY_5,
    k_6             = GLFW_KEY_6,
    k_7             = GLFW_KEY_7,
    k_8             = GLFW_KEY_8,
    k_9             = GLFW_KEY_9,
    k_SEMICOLON     = GLFW_KEY_SEMICOLON,
    k_EQUAL         = GLFW_KEY_EQUAL,
    k_A             = GLFW_KEY_A,
    k_B             = GLFW_KEY_B,
    k_C             = GLFW_KEY_C,
    k_D             = GLFW_KEY_D,
    k_E             = GLFW_KEY_E,
    k_F             = GLFW_KEY_F,
    k_G             = GLFW_KEY_G,
    k_H             = GLFW_KEY_H,
    k_I             = GLFW_KEY_I,
    k_J             = GLFW_KEY_J,
    k_K             = GLFW_KEY_K,
    k_L             = GLFW_KEY_L,
    k_M             = GLFW_KEY_M,
    k_N             = GLFW_KEY_N,
    k_O             = GLFW_KEY_O,
    k_P             = GLFW_KEY_P,
    k_Q             = GLFW_KEY_Q,
    k_R             = GLFW_KEY_R,
    k_S             = GLFW_KEY_S,
    k_T             = GLFW_KEY_T,
    k_U             = GLFW_KEY_U,
    k_V             = GLFW_KEY_V,
    k_W             = GLFW_KEY_W,
    k_X             = GLFW_KEY_X,
    k_Y             = GLFW_KEY_Y,
    k_Z             = GLFW_KEY_Z,
    k_LEFT_BRACKET  = GLFW_KEY_LEFT_BRACKET,
    k_BACKSLASH     = GLFW_KEY_BACKSLASH,
    k_RIGHT_BRACKET = GLFW_KEY_RIGHT_BRACKET,
    k_GRAVE_ACCENT  = GLFW_KEY_GRAVE_ACCENT,
    k_WORLD_1       = GLFW_KEY_WORLD_1,
    k_WORLD_2       = GLFW_KEY_WORLD_2,
    // functional
    k_ESCAPE        = GLFW_KEY_ESCAPE,
    k_ENTER         = GLFW_KEY_ENTER,
    k_TAB           = GLFW_KEY_TAB,
    k_BACKSPACE     = GLFW_KEY_BACKSPACE,
    k_INSERT        = GLFW_KEY_INSERT,
    k_DELETE        = GLFW_KEY_DELETE,
    k_RIGHT         = GLFW_KEY_RIGHT,
    k_LEFT          = GLFW_KEY_LEFT,
    k_DOWN          = GLFW_KEY_DOWN,
    k_UP            = GLFW_KEY_UP,
    k_PAGE_UP       = GLFW_KEY_PAGE_UP,
    k_PAGE_DOWN     = GLFW_KEY_PAGE_DOWN,
    k_HOME          = GLFW_KEY_HOME,
    k_END           = GLFW_KEY_END,
    k_CAPS_LOCK     = GLFW_KEY_CAPS_LOCK,
    k_SCROLL_LOCK   = GLFW_KEY_SCROLL_LOCK,
    k_NUM_LOCK      = GLFW_KEY_NUM_LOCK,
    k_PRINT_SCREEN  = GLFW_KEY_PRINT_SCREEN,
    k_PAUSE         = GLFW_KEY_PAUSE,
    k_F1            = GLFW_KEY_F1,
    k_F2            = GLFW_KEY_F2,
    k_F3            = GLFW_KEY_F3,
    k_F4            = GLFW_KEY_F4,
    k_F5            = GLFW_KEY_F5,
    k_F6            = GLFW_KEY_F6,
    k_F7            = GLFW_KEY_F7,
    k_F8            = GLFW_KEY_F8,
    k_F9            = GLFW_KEY_F9,
    k_F10           = GLFW_KEY_F10,
    k_F11           = GLFW_KEY_F11,
    k_F12           = GLFW_KEY_F12,
    k_F13           = GLFW_KEY_F13,
    k_F14           = GLFW_KEY_F14,
    k_F15           = GLFW_KEY_F15,
    k_F16           = GLFW_KEY_F16,
    k_F17           = GLFW_KEY_F17,
    k_F18           = GLFW_KEY_F18,
    k_F19           = GLFW_KEY_F19,
    k_F20           = GLFW_KEY_F20,
    k_F21           = GLFW_KEY_F21,
    k_F22           = GLFW_KEY_F22,
    k_F23           = GLFW_KEY_F23,
    k_F24           = GLFW_KEY_F24,
    k_F25           = GLFW_KEY_F25,
    k_KP_0          = GLFW_KEY_KP_0,
    k_KP_1          = GLFW_KEY_KP_1,
    k_KP_2          = GLFW_KEY_KP_2,
    k_KP_3          = GLFW_KEY_KP_3,
    k_KP_4          = GLFW_KEY_KP_4,
    k_KP_5          = GLFW_KEY_KP_5,
    k_KP_6          = GLFW_KEY_KP_6,
    k_KP_7          = GLFW_KEY_KP_7,
    k_KP_8          = GLFW_KEY_KP_8,
    k_KP_9          = GLFW_KEY_KP_9,
    k_KP_DECIMAL    = GLFW_KEY_KP_DECIMAL,
    k_KP_DIVIDE     = GLFW_KEY_KP_DIVIDE,
    k_KP_MULTIPLY   = GLFW_KEY_KP_MULTIPLY,
    k_KP_SUBTRACT   = GLFW_KEY_KP_SUBTRACT,
    k_KP_ADD        = GLFW_KEY_KP_ADD,
    k_KP_ENTER      = GLFW_KEY_KP_ENTER,
    k_KP_EQUAL      = GLFW_KEY_KP_EQUAL,
    k_LEFT_SHIFT    = GLFW_KEY_LEFT_SHIFT,
    k_LEFT_CONTROL  = GLFW_KEY_LEFT_CONTROL,
    k_LEFT_ALT      = GLFW_KEY_LEFT_ALT,
    k_LEFT_SUPER    = GLFW_KEY_LEFT_SUPER,
    k_RIGHT_SHIFT   = GLFW_KEY_RIGHT_SHIFT,
    k_RIGHT_CONTROL = GLFW_KEY_RIGHT_CONTROL,
    k_RIGHT_ALT     = GLFW_KEY_RIGHT_ALT,
    k_RIGHT_SUPER   = GLFW_KEY_RIGHT_SUPER,
    k_MENU          = GLFW_KEY_MENU,
    // Last
    k_LAST = GLFW_KEY_LAST
};

enum Modifier_Key : int32_t
{
    mod_SHIFT     = GLFW_MOD_SHIFT,
    mod_CONTROL   = GLFW_MOD_CONTROL,
    mod_ALT       = GLFW_MOD_ALT,
    mod_SUPER     = GLFW_MOD_SUPER,
    mod_CAPS_LOCK = GLFW_MOD_CAPS_LOCK,
    mod_NUM_LOCK  = GLFW_MOD_NUM_LOCK
};

enum Mouse_Button : int32_t
{
    mb_1      = GLFW_MOUSE_BUTTON_1,
    mb_2      = GLFW_MOUSE_BUTTON_2,
    mb_3      = GLFW_MOUSE_BUTTON_3,
    mb_4      = GLFW_MOUSE_BUTTON_4,
    mb_5      = GLFW_MOUSE_BUTTON_5,
    mb_6      = GLFW_MOUSE_BUTTON_6,
    mb_7      = GLFW_MOUSE_BUTTON_7,
    mb_8      = GLFW_MOUSE_BUTTON_8,
    mb_LAST   = GLFW_MOUSE_BUTTON_LAST,
    mb_LEFT   = GLFW_MOUSE_BUTTON_LEFT,
    mb_RIGHT  = GLFW_MOUSE_BUTTON_RIGHT,
    mb_MIDDLE = GLFW_MOUSE_BUTTON_MIDDLE
};

enum Joystick_Button : int32_t
{
    jb_1    = GLFW_JOYSTICK_1,
    jb_2    = GLFW_JOYSTICK_2,
    jb_3    = GLFW_JOYSTICK_3,
    jb_4    = GLFW_JOYSTICK_4,
    jb_5    = GLFW_JOYSTICK_5,
    jb_6    = GLFW_JOYSTICK_6,
    jb_7    = GLFW_JOYSTICK_7,
    jb_8    = GLFW_JOYSTICK_8,
    jb_9    = GLFW_JOYSTICK_9,
    jb_10   = GLFW_JOYSTICK_10,
    jb_11   = GLFW_JOYSTICK_11,
    jb_12   = GLFW_JOYSTICK_12,
    jb_13   = GLFW_JOYSTICK_13,
    jb_14   = GLFW_JOYSTICK_14,
    jb_15   = GLFW_JOYSTICK_15,
    jb_16   = GLFW_JOYSTICK_16,
    jb_LAST = GLFW_JOYSTICK_LAST
};

enum Gamepad_Button : int32_t
{
    gb_A            = GLFW_GAMEPAD_BUTTON_A,
    gb_B            = GLFW_GAMEPAD_BUTTON_B,
    gb_X            = GLFW_GAMEPAD_BUTTON_X,
    gb_Y            = GLFW_GAMEPAD_BUTTON_Y,
    gb_LEFT_BUMPER  = GLFW_GAMEPAD_BUTTON_LEFT_BUMPER,
    gb_RIGHT_BUMPER = GLFW_GAMEPAD_BUTTON_RIGHT_BUMPER,
    gb_BACK         = GLFW_GAMEPAD_BUTTON_BACK,
    gb_START        = GLFW_GAMEPAD_BUTTON_START,
    gb_GUIDE        = GLFW_GAMEPAD_BUTTON_GUIDE,
    gb_LEFT_THUMB   = GLFW_GAMEPAD_BUTTON_LEFT_THUMB,
    gb_RIGHT_THUMB  = GLFW_GAMEPAD_BUTTON_RIGHT_THUMB,
    gb_DPAD_UP      = GLFW_GAMEPAD_BUTTON_DPAD_UP,
    gb_DPAD_RIGHT   = GLFW_GAMEPAD_BUTTON_DPAD_RIGHT,
    gb_DPAD_DOWN    = GLFW_GAMEPAD_BUTTON_DPAD_DOWN,
    gb_DPAD_LEFT    = GLFW_GAMEPAD_BUTTON_DPAD_LEFT,
    gb_LAST         = GLFW_GAMEPAD_BUTTON_LAST,
    gb_CROSS        = GLFW_GAMEPAD_BUTTON_CROSS,
    gb_CIRCLE       = GLFW_GAMEPAD_BUTTON_CIRCLE,
    gb_SQUARE       = GLFW_GAMEPAD_BUTTON_SQUARE,
    gb_TRIANGLE     = GLFW_GAMEPAD_BUTTON_TRIANGLE
};

enum Gamepad_Axis : int32_t
{
    ga_LEFT_X        = GLFW_GAMEPAD_AXIS_LEFT_X,
    ga_LEFT_Y        = GLFW_GAMEPAD_AXIS_LEFT_Y,
    ga_RIGHT_X       = GLFW_GAMEPAD_AXIS_RIGHT_X,
    ga_RIGHT_Y       = GLFW_GAMEPAD_AXIS_RIGHT_Y,
    ga_LEFT_TRIGGER  = GLFW_GAMEPAD_AXIS_LEFT_TRIGGER,
    ga_RIGHT_TRIGGER = GLFW_GAMEPAD_AXIS_RIGHT_TRIGGER,
    ga_LAST          = GLFW_GAMEPAD_AXIS_LAST
};

struct Video_Mode
{
    int width;
    int height;
    int redBits;
    int greenBits;
    int blueBits;
    int refreshRate;
};

struct Gamma_Ramp
{
    unsigned short *red;
    unsigned short *green;
    unsigned short *blue;
    unsigned int    size;
};

struct Image
{
    int            width;
    int            height;
    unsigned char *pixels;
};

struct Gamepad_State
{
    unsigned char buttons[15];
    float         axes[6];
};

struct Allocator
{
    GLFWallocatefun   allocate;
    GLFWreallocatefun reallocate;
    GLFWdeallocatefun deallocate;
    void             *user;
};

} // namespace glfw
