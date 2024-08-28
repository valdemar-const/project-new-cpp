#include <Render_Target.hpp>

namespace graphics
{

Gl_Render_Target::Gl_Render_Target(
        const std::vector<glm::dvec2>    &mesh,
        const std::vector<std::uint32_t> &indices
)
    : VAO(GL_NONE)
    , VBO(GL_NONE)
    , EBO(GL_NONE)
{
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    {
        glGenBuffers(1, &VBO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, mesh.size() * sizeof(mesh[0]), mesh.data(), GL_STATIC_DRAW);
        vertex_count = mesh.size();

        if (!indices.empty())
        {
            glGenBuffers(1, &EBO);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(indices[0]), indices.data(), GL_STATIC_DRAW);
            vertex_count = indices.size();
        }

        glVertexAttribLPointer(0, 2, GL_DOUBLE, 2 * sizeof(mesh[0].x), nullptr);
        glEnableVertexAttribArray(0);
    }
    glBindVertexArray(0);
}

Gl_Render_Target::~Gl_Render_Target()
{
    glDeleteVertexArrays(1, &VAO);
    if (EBO)
    {
        glDeleteBuffers(1, &EBO);
    }
    glDeleteBuffers(1, &VBO);
}

void
Gl_Render_Target::draw() const
{
    glBindVertexArray(VAO);
    if (EBO)
    {
        glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(vertex_count), GL_UNSIGNED_INT, nullptr);
    }
    else
    {
        glDrawArrays(GL_TRIANGLES, 0, static_cast<GLsizei>(vertex_count));
    }
}

} // namespace graphics
