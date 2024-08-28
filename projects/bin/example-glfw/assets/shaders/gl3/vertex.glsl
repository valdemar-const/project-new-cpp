#version 460 core
#extension GL_ARB_gpu_shader_fp64     : enable
#extension GL_ARB_vertex_attrib_64bit : enable

layout (location = 0) in dvec2 aPos;

void main()
{
    gl_Position = vec4(aPos.x, aPos.y, 0.0, 1.0);
}
