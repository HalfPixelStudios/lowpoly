#version 300 es
layout(location = 0) in vec4 pos;

uniform mediump mat4 u_MVP;

void
main() {
    gl_Position = u_MVP * pos;
};
