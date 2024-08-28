#include <Vertex_Shader.hpp>

namespace graphics
{

VertexShader::VertexShader(
        std::string source
)
    : Shader(source, Type::vertex)
{
}

} // namespace graphics
