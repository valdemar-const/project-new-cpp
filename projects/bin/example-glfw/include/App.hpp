#pragma once

#include <Vertex_Shader.hpp>
#include <Fragment_Shader.hpp>
#include <Shader_Program.hpp>
#include <Render_Target.hpp>

#include <GLFW/glfw3.h>

#include <memory>

namespace app
{

struct state
{
    GLFWwindow *window = nullptr;

    bool is_need_redraw   = true;
    bool toggle_wireframe = false;

    std::shared_ptr<graphics::VertexShader>   vertex      = nullptr;
    std::shared_ptr<graphics::FragmentShader> fragment    = nullptr;
    std::unique_ptr<graphics::ShaderProgram>  passthrough = nullptr;

    std::shared_ptr<graphics::Gl_Render_Target> quad = nullptr;
};

extern state render_state;

} // namespace app
