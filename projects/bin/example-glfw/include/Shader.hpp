#pragma once

#include <glad/glad.h>

#include <string>

namespace graphics
{

struct to_shader_source
{
    const char *p;

    to_shader_source(
            const std::string &s
    )
        : p(s.c_str())
    {
    }

    operator const char **()
    {
        return &p;
    }
};

class Shader
{
  public:

    enum class Type : GLuint
    {
        vertex   = GL_VERTEX_SHADER,
        fragment = GL_FRAGMENT_SHADER
    };

  public:

    Shader(std::string source, Type type);
    Shader(const Shader &copy_from);
    Shader(Shader &&move_from);

    ~Shader();

    GLuint compile() noexcept(false);
    bool   is_compiled() const;
    void   clean();

    GLuint get_id() const noexcept(false);

  public:

    Shader &operator=(const Shader &copy_from);
    Shader &operator=(Shader &&move_from);

  protected:

    std::string source_;
    Type        type_;
    bool        is_compiled_;
    GLuint      id_;
};

} // namespace graphics
