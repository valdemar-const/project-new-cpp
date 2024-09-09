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

namespace types
{
    using GLenum  = unsigned int;
    using GLubyte = khronos_uint8_t;
    using GLint   = int;
    using GLuint  = unsigned int;
} // namespace types

namespace constants
{

}

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

} // namespace functions

namespace extensions
{

}

namespace exceptions
{

}

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

namespace impl
{

    template<Client_Api Client_Api, size_t Version_Major, size_t Version_Minor, Profile Profile, typename Enable = void>
    struct glGetStringi_enabled
    {
    };

    template<Client_Api Client_Api, size_t Version_Major, size_t Version_Minor, Profile Profile>
    struct glGetStringi_enabled<
            Client_Api,
            Version_Major,
            Version_Minor,
            Profile,
            typename std::enable_if<(Client_Api == Client_Api::Gl || Client_Api == Client_Api::Gles2) && Version_Major >= 3>::type>
    {
        functions::glGetStringi::Proc_Type GetStringi;
    };

    template<Client_Api Client_Api, size_t Version_Major, size_t Version_Minor, Profile Profile, Load_Strategy Load_Strategy, typename... Extensions>
    class GL_Load_Context_Basic : public glGetStringi_enabled<Client_Api, Version_Major, Version_Minor, Profile>
    {
      public: // traits
      public:

        GL_Load_Context_Basic(functions::GL_Load_Proc gl_load_proc)
            : gl_load_proc_(gl_load_proc)
        {
            bool is_lazy = Load_Strategy == Load_Strategy::Lazy;

            GetString   = functions::glGetString {"glGetString", gl_load_proc, is_lazy};
            GetIntegerv = functions::glGetIntegerv {"glGetIntegerv", gl_load_proc, is_lazy};
        }

        std::function<functions::glGetString::Proc_Type>   GetString;
        std::function<functions::glGetIntegerv::Proc_Type> GetIntegerv;

      protected:

        functions::GL_Load_Proc    gl_load_proc_;
        std::set<std::string_view> extensions_;
    };

} // namespace impl

template<Client_Api Client_Api, size_t Version_Major, size_t Version_Minor, Profile Profile, Load_Strategy Load_Strategy, typename... Extensions>
class GL_Load_Context : public impl::GL_Load_Context_Basic<Client_Api, Version_Major, Version_Minor, Profile, Load_Strategy, Extensions...>
{
  public: // traits
  public:

    GL_Load_Context(functions::GL_Load_Proc gl_load_proc)
        : impl::GL_Load_Context_Basic<Client_Api, Version_Major, Version_Minor, Profile, Load_Strategy, Extensions...>(gl_load_proc)
    {
    }
};

} // namespace glmeta
