#pragma once

#include <Material.hpp>

#include <glm/vec2.hpp>
#include <glad/glad.h>

#include <vector>

#include <cstdint>

namespace graphics
{

class Gl_Render_Target
{
  public:

    Gl_Render_Target(const std::vector<glm::dvec2> &mesh = {}, const std::vector<std::uint32_t> &indices = {});
    ~Gl_Render_Target();

    void draw() const;

  protected:

    GLuint VAO;
    GLuint VBO;
    GLuint EBO;
    size_t vertex_count;

    Material material;
};

} // namespace graphics
