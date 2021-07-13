#version 300 es
layout(location = 0) in vec4 pos;
layout(location = 1) in vec2 tex_coord;

out mediump vec2 v_TexCoord;

uniform mediump mat4 u_Transform;

void
main() {
    gl_Position = u_Transform * pos;
    v_TexCoord = tex_coord;
};
