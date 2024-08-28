#pragma once

#include <Vertex_Shader.hpp>
#include <Fragment_Shader.hpp>

#include <glad/glad.h>

#include <memory>

namespace graphics
{

class ShaderProgram
{
  public:

    ShaderProgram(std::shared_ptr<VertexShader> vertex, std::shared_ptr<FragmentShader> fragment);

    GLuint link();
    bool   is_linked() const;

    GLuint get_id() const;
    void   use();

  protected:

    GLuint                          id_;
    std::shared_ptr<VertexShader>   vertex_;
    std::shared_ptr<FragmentShader> fragment_;
    bool                            is_linked_;
};

} // namespace graphics
