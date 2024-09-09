#pragma once

#include <KHR/khrplatform.h>

#include <string_view>
#include <unordered_map>
#include <set>

#include <functional>
#include <type_traits>
#include <compare>

#include <exception>

namespace glmeta
{

namespace basic_types
{
    using GLenum  = unsigned int;
    using GLubyte = khronos_uint8_t;
    using GLint   = int;
    using GLuint  = unsigned int;
} // namespace basic_types

namespace constants
{

}

namespace functions
{
    using namespace basic_types;

    using GL_Any_Proc  = void();
    using GL_Load_Proc = std::function<GL_Any_Proc *(std::string_view)>;

    template<typename Result, typename... Args>
    using GL_Proc = Result(Args...);

    using glGetString   = GL_Proc<const GLubyte *, GLenum>;
    using glGetIntegerv = GL_Proc<void, GLenum, GLint *>;
    using glGetStringi  = GL_Proc<const GLubyte *, GLenum, GLuint>;

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
    Gles
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

    template<Client_Api Client_Api, size_t Version_Major, size_t Version_Minor, Profile Profile, Load_Strategy Load_Strategy, typename... Extensions>
    class GL_Load_Context_Basic
    {
      public: // traits
      public:

        GL_Load_Context_Basic(functions::GL_Load_Proc gl_load_proc)
            : gl_load_proc_(gl_load_proc)
        {
        }

        functions::glGetString   GetString;
        functions::glGetIntegerv GetIntegerv;
        functions::glGetStringi  GetStringi;

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
