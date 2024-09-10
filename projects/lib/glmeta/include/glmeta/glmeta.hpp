#pragma once

#include <KHR/khrplatform.h>

#include <string_view>
#include <unordered_map>
#include <set>

#include <functional>
#include <type_traits>
#include <compare>

#include <stdexcept>

namespace glmeta
{

enum class Client_Api : uint8_t
{
    Gl,
    Gles1,
    Gles2
};

enum class Profile : uint8_t
{
    None,
    Compat,
    Core
};

enum class Load_Strategy : uint8_t
{
    Immediate,
    Lazy
};

namespace types
{
    using GLenum     = unsigned int;
    using GLbitfield = unsigned int;
    using GLubyte    = khronos_uint8_t;
    using GLint      = int;
    using GLuint     = unsigned int;
    using GLfloat    = khronos_float_t;
} // namespace types

namespace constants
{
    using namespace types;

    constexpr GLenum GL_VERSION       = 0x1F02;
    constexpr GLenum GL_MAJOR_VERSION = 0x821B;
    constexpr GLenum GL_MINOR_VERSION = 0x821C;
    constexpr GLenum GL_VENDOR        = 0x1F00;
    constexpr GLenum GL_RENDERER      = 0x1F01;

    constexpr GLenum GL_CONTEXT_PROFILE_MASK = 0x9126;
    constexpr GLenum GL_CONTEXT_FLAGS        = 0x821E;

    constexpr GLenum GL_NUM_EXTENSIONS = 0x821D;
    constexpr GLenum GL_EXTENSIONS     = 0x1F03;

    constexpr GLenum GL_CONTEXT_CORE_PROFILE_BIT            = 0x00000001;
    constexpr GLenum GL_CONTEXT_COMPATIBILITY_PROFILE_BIT   = 0x00000002;
    constexpr GLenum GL_CONTEXT_FLAG_FORWARD_COMPATIBLE_BIT = 0x00000001;
    constexpr GLenum GL_CONTEXT_FLAG_DEBUG_BIT              = 0x00000002;
    constexpr GLenum GL_CONTEXT_FLAG_ROBUST_ACCESS_BIT      = 0x00000004;
    constexpr GLenum GL_CONTEXT_FLAG_NO_ERROR_BIT           = 0x00000008;
    constexpr GLenum GL_NUM_SHADING_LANGUAGE_VERSIONS       = 0x82E9;
    constexpr GLenum GL_SHADING_LANGUAGE_VERSION            = 0x8B8C;

    constexpr GLenum GL_COLOR_BUFFER_BIT = 0x00004000;
} // namespace constants

namespace functions
{
    using namespace types;

    using GL_Any_Proc  = void();
    using GL_Load_Proc = std::function<GL_Any_Proc *(std::string_view)>;

    template<typename Result, typename... Args>
    using GL_Proc = Result(Args...);

    template<typename Result, typename... Args>
    class GL_Functor
    {
      public:

        using Proc_Type = GL_Proc<Result, Args...>;
        const std::string func_name;

      public:

        GL_Functor(std::string_view func_name, GL_Load_Proc gl_load_proc, bool is_lazy = false)
            : func_name(func_name)
            , gl_load_proc_(gl_load_proc)
            , proc_(reinterpret_cast<Proc_Type *>((is_lazy) ? nullptr : gl_load_proc(func_name)))
            , is_loaded_(!is_lazy)
        {
        }

        bool
        empty() const
        {
            return is_loaded_ && proc_ == nullptr;
        }

        Result
        operator()(Args... args)
        {
            if (proc_)
            {
                return proc_(args...);
            }
            else if (!is_loaded_)
            {
                proc_      = reinterpret_cast<Proc_Type *>(gl_load_proc_(func_name));
                is_loaded_ = true;
                return proc_(args...);
            }
            else
            {
                std::string error_msg {"OpenGL function " + func_name + " not loaded from context"};
                throw std::runtime_error(error_msg);
            }
        }

      private:

        GL_Load_Proc gl_load_proc_;
        Proc_Type   *proc_      = nullptr;
        bool         is_loaded_ = false;
    };

    using glGetString   = GL_Functor<const GLubyte *, GLenum>;
    using glGetIntegerv = GL_Functor<void, GLenum, GLint *>;
    using glGetStringi  = GL_Functor<const GLubyte *, GLenum, GLuint>;
    using glClearColor  = GL_Functor<void, GLfloat, GLfloat, GLfloat, GLfloat>;
    using glClear       = GL_Functor<void, GLbitfield>;

} // namespace functions

namespace extensions
{

}

namespace exceptions
{

}

namespace impl
{

    template<Client_Api Client_Api, size_t Version_Major, size_t Version_Minor, Profile Profile, typename Enable = void>
    struct glGetStringi_enabled
    {
      public: // traits

        static bool constexpr value = false;
    };

    template<Client_Api Client_Api, size_t Version_Major, size_t Version_Minor, Profile Profile>
    struct glGetStringi_enabled<
            Client_Api,
            Version_Major,
            Version_Minor,
            Profile,
            typename std::enable_if<(Client_Api == Client_Api::Gl || Client_Api == Client_Api::Gles2) && Version_Major >= 3>::type>
    {
      public: // traits

        static bool constexpr value = true;

      public:

        std::function<functions::glGetStringi::Proc_Type> GetStringi;
    };

    template<Client_Api Client_Api, size_t Version_Major, size_t Version_Minor, Profile Profile, Load_Strategy Load_Strategy, typename... Extensions>
    class GL_Load_Context_Basic : public glGetStringi_enabled<Client_Api, Version_Major, Version_Minor, Profile>
    {
      public: // traits

        using glGetStringi_enabled = glGetStringi_enabled<Client_Api, Version_Major, Version_Minor, Profile>;

      public:

        GL_Load_Context_Basic(functions::GL_Load_Proc gl_load_proc)
            : gl_load_proc_(gl_load_proc)
        {
            bool is_lazy = Load_Strategy == Load_Strategy::Lazy;

            GetString   = functions::glGetString {"glGetString", gl_load_proc, is_lazy};
            GetIntegerv = functions::glGetIntegerv {"glGetIntegerv", gl_load_proc, is_lazy};

            if constexpr (glGetStringi_enabled::value)
            {
                glGetStringi_enabled::GetStringi = functions::glGetStringi {"glGetStringi", gl_load_proc, is_lazy};
            }

            ClearColor = functions::glClearColor {"glClearColor", gl_load_proc, is_lazy};
            Clear      = functions::glClear {"glClear", gl_load_proc, is_lazy};
        }

        std::function<functions::glGetString::Proc_Type>   GetString;
        std::function<functions::glGetIntegerv::Proc_Type> GetIntegerv;
        std::function<functions::glClearColor::Proc_Type>  ClearColor;
        std::function<functions::glClear::Proc_Type>       Clear;

      protected:

        functions::GL_Load_Proc    gl_load_proc_;
        std::set<std::string_view> extensions_;
    };

} // namespace impl

template<Client_Api Client_Api, size_t Version_Major, size_t Version_Minor, Profile Profile, Load_Strategy Load_Strategy, typename... Extensions>
class GL_Load_Context : public impl::GL_Load_Context_Basic<Client_Api, Version_Major, Version_Minor, Profile, Load_Strategy, Extensions...>
{
  public: // traits

    using Context = impl::GL_Load_Context_Basic<Client_Api, Version_Major, Version_Minor, Profile, Load_Strategy, Extensions...>;

  public: // types

    struct GL_Version
    {
        int major = 0;
        int minor = 0;
    };

  public:

    GL_Load_Context(functions::GL_Load_Proc gl_load_proc)
        : impl::GL_Load_Context_Basic<Client_Api, Version_Major, Version_Minor, Profile, Load_Strategy, Extensions...>(gl_load_proc)
    {
        using namespace constants;

        Context::GetIntegerv(GL_MAJOR_VERSION, &version.major);
        Context::GetIntegerv(GL_MINOR_VERSION, &version.minor);
        std::string_view version_string {(char *)Context::GetString(GL_VERSION)};

        size_t res = version_string.find("ES");
        if (res != version_string.npos)
        {
            if (version.major >= 2)
            {
                loaded_api = (version.major >= 2) ? Client_Api::Gles2 : Client_Api::Gles1;
            }
        }
        else
        {
            loaded_api = Client_Api::Gl;
        }
    }

  public:

    GL_Version         version;
    glmeta::Client_Api loaded_api;
};

} // namespace glmeta
