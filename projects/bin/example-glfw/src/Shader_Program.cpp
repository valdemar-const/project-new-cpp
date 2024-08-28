#include <Shader_Program.hpp>

#include <stdexcept>

namespace graphics
{

ShaderProgram::ShaderProgram(
        std::shared_ptr<VertexShader>   vertex,
        std::shared_ptr<FragmentShader> fragment
)
    : vertex_(vertex)
    , fragment_(fragment)
    , is_linked_(false)
    , id_(GL_NONE)
{
}

GLuint
ShaderProgram::link()
{
    id_ = glCreateProgram();
    glAttachShader(id_, vertex_->compile());
    glAttachShader(id_, fragment_->compile());
    glLinkProgram(id_);

    GLint res = 0;
    glGetProgramiv(id_, GL_LINK_STATUS, &res);
    if (!res)
    {
        constexpr size_t maxlen     = 1024;
        GLsizei          log_length = 0;
        GLchar           message[maxlen];
        glGetProgramInfoLog(id_, maxlen, &log_length, message);
        throw std::runtime_error(message);
    }
    is_linked_ = true;
    vertex_.reset();
    fragment_.reset();
    return id_;
}

bool
ShaderProgram::is_linked() const
{
    return is_linked_;
}

GLuint
ShaderProgram::get_id() const
{
    if (is_linked_)
    {
        return id_;
    }
    else
    {
        throw std::logic_error("Shader was not compiled");
    }
}

void
ShaderProgram::use()
{
    if (is_linked_)
    {
        glUseProgram(id_);
    }
}

} // namespace graphics
