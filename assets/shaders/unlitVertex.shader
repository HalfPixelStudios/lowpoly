#version 300 es
layout(location = 0) in vec4 pos;
layout(location = 2) in vec4 normal;

uniform mediump mat4 u_Model;
uniform mediump mat4 u_View;
uniform mediump mat4 u_Projection;

void
main() {
    gl_Position = u_Projection * u_View * u_Model * pos;
}
