#version 300 es
layout(location = 0) in vec3 pos;

#include assets/shaders/common.shaderh

uniform MVP u_MVP;

void main()
{
    gl_Position = u_MVP.projection * u_MVP.view * u_MVP.model * vec4(pos, 1.0);
}
