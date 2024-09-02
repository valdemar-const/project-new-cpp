// Glfw State

// static

GLFWAPI void                      glfwGetVersion                           (int32_t* major, int32_t* minor, int32_t* rev);
GLFWAPI const char*               glfwGetVersionString                     (void);

GLFWAPI int32_t                   glfwPlatformSupported                    (int32_t platform);

GLFWAPI int32_t                   glfwGetError                             (const char** description);

GLFWAPI void                      glfwInitHint                             (int32_t hint, int32_t value);
GLFWAPI void                      glfwInitAllocator                        (const GLFWallocator* allocator);
GLFWAPI void                      glfwInitVulkanLoader                     (PFN_vkGetInstanceProcAddr loader);

GLFWAPI GLFWerrorfun              glfwSetErrorCallback                     (GLFWerrorfun callback);

// constructor/destructor

GLFWAPI int32_t                   glfwInit                                 (void);
// GLFWAPI int32_t                glfwReInit                               (void);
GLFWAPI void                      glfwTerminate                            (void);

GLFWAPI int32_t                   glfwGetPlatform                          (void);

GLFWAPI GLFWmonitor**             glfwGetMonitors                          (int32_t* count);
GLFWAPI GLFWmonitor*              glfwGetPrimaryMonitor                    (void);

// Core callbacks

GLFWAPI GLFWmonitorfun            glfwSetMonitorCallback                   (GLFWmonitorfun callback);
GLFWAPI GLFWjoystickfun           glfwSetJoystickCallback                  (GLFWjoystickfun callback);

// Client API

GLFWAPI void                      glfwSwapInterval                         (int32_t interval);

GLFWAPI int32_t                   glfwExtensionSupported                   (const char* extension);
GLFWAPI GLFWglproc                glfwGetProcAddress                       (const char* procname);

GLFWAPI int32_t                   glfwVulkanSupported                      (void);
GLFWAPI const char**              glfwGetRequiredInstanceExtensions        (uint32_t* count);

// Event handling

GLFWAPI void                      glfwPollEvents                           (void);
GLFWAPI void                      glfwWaitEvents                           (void);
GLFWAPI void                      glfwWaitEventsTimeout                    (double timeout);
GLFWAPI void                      glfwPostEmptyEvent                       (void);

// input output check

GLFWAPI int32_t                   glfwRawMouseMotionSupported              (void);

GLFWAPI const char*               glfwGetKeyName                           (int32_t key, int32_t scancode);
GLFWAPI int32_t                   glfwGetKeyScancode                       (int32_t key);

// cursors

GLFWAPI GLFWcursor*               glfwCreateCursor                         (const GLFWimage* image, int32_t xhot, int32_t yhot);
GLFWAPI GLFWcursor*               glfwCreateStandardCursor                 (int32_t shape);
GLFWAPI void                      glfwDestroyCursor                        (GLFWcursor* cursor);

// joystick

GLFWAPI int32_t                   glfwJoystickPresent                      (int32_t jid);
GLFWAPI const float*              glfwGetJoystickAxes                      (int32_t jid, int32_t* count);
GLFWAPI const unsigned char*      glfwGetJoystickButtons                   (int32_t jid, int32_t* count);
GLFWAPI const unsigned char*      glfwGetJoystickHats                      (int32_t jid, int32_t* count);
GLFWAPI const char*               glfwGetJoystickName                      (int32_t jid);
GLFWAPI const char*               glfwGetJoystickGUID                      (int32_t jid);
GLFWAPI void                      glfwSetJoystickUserPointer               (int32_t jid, void* pointer);
GLFWAPI void*                     glfwGetJoystickUserPointer               (int32_t jid);
GLFWAPI int32_t                   glfwJoystickIsGamepad                    (int32_t jid);

// gamepad

GLFWAPI int32_t                   glfwUpdateGamepadMappings                (const char* string);
GLFWAPI const char*               glfwGetGamepadName                       (int32_t jid);
GLFWAPI int32_t                   glfwGetGamepadState                      (int32_t jid, GLFWgamepadstate* state);

// chrono

GLFWAPI double                    glfwGetTime                              (void);
GLFWAPI void                      glfwSetTime                              (double time);
GLFWAPI uint64_t                  glfwGetTimerValue                        (void);
GLFWAPI uint64_t                  glfwGetTimerFrequency                    (void);

// Vulkan support

GLFWAPI VkResult                  glfwCreateWindowSurface                  (VkInstance instance, GLFWwindow* window, const VkAllocationCallbacks* allocator, VkSurfaceKHR* surface);
GLFWAPI GLFWvkproc                glfwGetInstanceProcAddress               (VkInstance instance, const char* procname);
GLFWAPI int32_t                   glfwGetPhysicalDevicePresentationSupport (VkInstance instance, VkPhysicalDevice device, uint32_t queuefamily);

// Window

GLFWAPI GLFWwindow*               glfwCreateWindow                         (int32_t width, int32_t height, const char* title, GLFWmonitor* monitor, GLFWwindow* share);
GLFWAPI void                      glfwDestroyWindow                        (GLFWwindow* window);

GLFWAPI int32_t                   glfwWindowShouldClose                    (GLFWwindow* window);
GLFWAPI const char*               glfwGetWindowTitle                       (GLFWwindow* window);
GLFWAPI void                      glfwGetWindowPos                         (GLFWwindow* window, int32_t* xpos, int32_t* ypos);
GLFWAPI void                      glfwGetWindowSize                        (GLFWwindow* window, int32_t* width, int32_t* height);
GLFWAPI void                      glfwGetWindowFrameSize                   (GLFWwindow* window, int32_t* left, int32_t* top, int32_t* right, int32_t* bottom);
GLFWAPI void                      glfwGetWindowContentScale                (GLFWwindow* window, float* xscale, float* yscale);
GLFWAPI float                     glfwGetWindowOpacity                     (GLFWwindow* window);
GLFWAPI GLFWmonitor*              glfwGetWindowMonitor                     (GLFWwindow* window);
GLFWAPI int32_t                   glfwGetWindowAttrib                      (GLFWwindow* window, int32_t attrib);
GLFWAPI void*                     glfwGetWindowUserPointer                 (GLFWwindow* window);
GLFWAPI void                      glfwGetFramebufferSize                   (GLFWwindow* window, int32_t* width, int32_t* height);

GLFWAPI void                      glfwSetWindowShouldClose                 (GLFWwindow* window, int32_t value);
GLFWAPI void                      glfwSetWindowTitle                       (GLFWwindow* window, const char* title);
GLFWAPI void                      glfwSetWindowIcon                        (GLFWwindow* window, int32_t count, const GLFWimage* images);
GLFWAPI void                      glfwSetWindowPos                         (GLFWwindow* window, int32_t xpos, int32_t ypos);
GLFWAPI void                      glfwSetWindowSizeLimits                  (GLFWwindow* window, int32_t minwidth, int32_t minheight, int32_t maxwidth, int32_t maxheight);
GLFWAPI void                      glfwSetWindowAspectRatio                 (GLFWwindow* window, int32_t numer, int32_t denom);
GLFWAPI void                      glfwSetWindowSize                        (GLFWwindow* window, int32_t width, int32_t height);
GLFWAPI void                      glfwSetWindowOpacity                     (GLFWwindow* window, float opacity);
GLFWAPI void                      glfwSetWindowMonitor                     (GLFWwindow* window, GLFWmonitor* monitor, int32_t xpos, int32_t ypos, int32_t width, int32_t height, int32_t refreshRate);
GLFWAPI void                      glfwSetWindowAttrib                      (GLFWwindow* window, int32_t attrib, int32_t value);
GLFWAPI void                      glfwSetWindowUserPointer                 (GLFWwindow* window, void* pointer);

// window events

GLFWAPI GLFWwindowposfun          glfwSetWindowPosCallback                 (GLFWwindow* window, GLFWwindowposfun callback);
GLFWAPI GLFWwindowsizefun         glfwSetWindowSizeCallback                (GLFWwindow* window, GLFWwindowsizefun callback);
GLFWAPI GLFWwindowclosefun        glfwSetWindowCloseCallback               (GLFWwindow* window, GLFWwindowclosefun callback);
GLFWAPI GLFWwindowrefreshfun      glfwSetWindowRefreshCallback             (GLFWwindow* window, GLFWwindowrefreshfun callback);
GLFWAPI GLFWwindowfocusfun        glfwSetWindowFocusCallback               (GLFWwindow* window, GLFWwindowfocusfun callback);
GLFWAPI GLFWwindowiconifyfun      glfwSetWindowIconifyCallback             (GLFWwindow* window, GLFWwindowiconifyfun callback);
GLFWAPI GLFWwindowmaximizefun     glfwSetWindowMaximizeCallback            (GLFWwindow* window, GLFWwindowmaximizefun callback);
GLFWAPI GLFWframebuffersizefun    glfwSetFramebufferSizeCallback           (GLFWwindow* window, GLFWframebuffersizefun callback);
GLFWAPI GLFWwindowcontentscalefun glfwSetWindowContentScaleCallback        (GLFWwindow* window, GLFWwindowcontentscalefun callback);

// window input/output

GLFWAPI void                      glfwSetInputMode                         (GLFWwindow* window, int32_t mode, int32_t value);
GLFWAPI void                      glfwSetCursorPos                         (GLFWwindow* window, double xpos, double ypos);
GLFWAPI void                      glfwSetCursor                            (GLFWwindow* window, GLFWcursor* cursor);
GLFWAPI void                      glfwSetClipboardString                   (GLFWwindow* window, const char* string);

GLFWAPI int32_t                   glfwGetInputMode                         (GLFWwindow* window, int32_t mode);
GLFWAPI int32_t                   glfwGetKey                               (GLFWwindow* window, int32_t key);
GLFWAPI int32_t                   glfwGetMouseButton                       (GLFWwindow* window, int32_t button);
GLFWAPI void                      glfwGetCursorPos                         (GLFWwindow* window, double* xpos, double* ypos);
GLFWAPI const char*               glfwGetClipboardString                   (GLFWwindow* window);

GLFWAPI GLFWkeyfun                glfwSetKeyCallback                       (GLFWwindow* window, GLFWkeyfun callback);
GLFWAPI GLFWcharfun               glfwSetCharCallback                      (GLFWwindow* window, GLFWcharfun callback);
GLFWAPI GLFWcharmodsfun           glfwSetCharModsCallback                  (GLFWwindow* window, GLFWcharmodsfun callback);
GLFWAPI GLFWmousebuttonfun        glfwSetMouseButtonCallback               (GLFWwindow* window, GLFWmousebuttonfun callback);
GLFWAPI GLFWcursorposfun          glfwSetCursorPosCallback                 (GLFWwindow* window, GLFWcursorposfun callback);
GLFWAPI GLFWcursorenterfun        glfwSetCursorEnterCallback               (GLFWwindow* window, GLFWcursorenterfun callback);
GLFWAPI GLFWscrollfun             glfwSetScrollCallback                    (GLFWwindow* window, GLFWscrollfun callback);
GLFWAPI GLFWdropfun               glfwSetDropCallback                      (GLFWwindow* window, GLFWdropfun callback);

// window control

GLFWAPI void                      glfwIconifyWindow                        (GLFWwindow* window);
GLFWAPI void                      glfwRestoreWindow                        (GLFWwindow* window);
GLFWAPI void                      glfwMaximizeWindow                       (GLFWwindow* window);
GLFWAPI void                      glfwShowWindow                           (GLFWwindow* window);
GLFWAPI void                      glfwHideWindow                           (GLFWwindow* window);
GLFWAPI void                      glfwFocusWindow                          (GLFWwindow* window);
GLFWAPI void                      glfwRequestWindowAttention               (GLFWwindow* window);

// window Context

GLFWAPI void                      glfwMakeContextCurrent                   (GLFWwindow* window);
GLFWAPI void                      glfwSwapBuffers                          (GLFWwindow* window);

// monitor

GLFWAPI void                      glfwGetMonitorPos                        (GLFWmonitor* monitor, int32_t* xpos, int32_t* ypos);
GLFWAPI void                      glfwGetMonitorWorkarea                   (GLFWmonitor* monitor, int32_t* xpos, int32_t* ypos, int32_t* width, int32_t* height);
GLFWAPI void                      glfwGetMonitorPhysicalSize               (GLFWmonitor* monitor, int32_t* widthMM, int32_t* heightMM);
GLFWAPI void                      glfwGetMonitorContentScale               (GLFWmonitor* monitor, float* xscale, float* yscale);
GLFWAPI const char*               glfwGetMonitorName                       (GLFWmonitor* monitor);
GLFWAPI void                      glfwSetMonitorUserPointer                (GLFWmonitor* monitor, void* pointer);
GLFWAPI void*                     glfwGetMonitorUserPointer                (GLFWmonitor* monitor);
GLFWAPI const GLFWvidmode*        glfwGetVideoModes                        (GLFWmonitor* monitor, int32_t* count);
GLFWAPI const GLFWvidmode*        glfwGetVideoMode                         (GLFWmonitor* monitor);
GLFWAPI void                      glfwSetGamma                             (GLFWmonitor* monitor, float gamma);
GLFWAPI const GLFWgammaramp*      glfwGetGammaRamp                         (GLFWmonitor* monitor);
GLFWAPI void                      glfwSetGammaRamp                         (GLFWmonitor* monitor, const GLFWgammaramp* ramp);
