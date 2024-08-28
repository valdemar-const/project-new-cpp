#include <Shader.hpp>

#include <stdexcept>

namespace graphics
{

Shader::Shader(
        std::string  source,
        Shader::Type type
)
    : source_(source)
    , type_(type)
    , is_compiled_(false)
    , id_(GL_NONE)
{
}

Shader::Shader(
        const Shader &copy_from
)
    : Shader(copy_from.source_, copy_from.type_)
{
    if (copy_from.is_compiled_)
    {
        compile();
    }
}

Shader::Shader(
        Shader &&move_from
)
    : Shader(std::move(move_from.source_), std::move(move_from.type_))
{
    id_                    = std::move(move_from.id_);
    move_from.is_compiled_ = false;
}

Shader::~Shader()
{
    clean();
}

GLuint
Shader::compile() noexcept(false)
{
    if (is_compiled_)
    {
        return id_;
    }

    id_ = glCreateShader(static_cast<GLuint>(type_));
    glShaderSource(id_, 1, to_shader_source(source_), nullptr);
    glCompileShader(id_);

    GLint res = 0;
    glGetShaderiv(id_, GL_COMPILE_STATUS, &res);
    if (!res)
    {
        constexpr size_t maxlen     = 1024;
        GLsizei          log_length = 0;
        GLchar           message[maxlen];
        glGetShaderInfoLog(id_, maxlen, &log_length, message);
        throw std::runtime_error(message);
    }
    is_compiled_ = true;
    return id_;
}

bool
Shader::is_compiled() const
{
    return is_compiled_;
}

void
Shader::clean()
{
    if (is_compiled_)
    {
        glDeleteShader(id_);
        id_          = 0;
        is_compiled_ = false;
    }
}

GLuint
Shader::get_id() const noexcept(false)
{
    if (is_compiled_)
    {
        return id_;
    }
    else
    {
        throw std::logic_error("Shader was not compiled");
    }
}

Shader &
Shader::operator=(
        const Shader &copy_from
)
{
    source_ = copy_from.source_;
    type_   = copy_from.type_;
    if (copy_from.is_compiled_)
    {
        compile();
    }
    return *this;
}

Shader &
Shader::operator=(
        Shader &&move_from
)
{
    source_                = std::move(move_from.source_);
    type_                  = std::move(move_from.type_);
    id_                    = std::move(move_from.id_);
    is_compiled_           = std::move(move_from.is_compiled_);
    move_from.is_compiled_ = false;

    return *this;
}

} // namespace graphics
