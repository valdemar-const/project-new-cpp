#pragma once

#include <Shader.hpp>

#include <string>

namespace graphics
{

class FragmentShader : public Shader
{
  public:

    FragmentShader(std::string source);
};

} // namespace graphics
