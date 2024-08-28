#pragma once

#include <Shader.hpp>

#include <string>

namespace graphics
{

class VertexShader : public Shader
{
  public:

    VertexShader(std::string source);
};

} // namespace graphics
