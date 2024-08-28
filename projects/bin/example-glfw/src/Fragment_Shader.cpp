#include <Fragment_Shader.hpp>

namespace graphics
{

FragmentShader::FragmentShader(std::string source)
    : Shader(source, Type::fragment)
{
}

} // namespace graphics
