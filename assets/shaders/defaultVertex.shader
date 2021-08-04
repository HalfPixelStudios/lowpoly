#version 300 es
layout(location = 0) in vec4 pos;
layout(location = 2) in vec4 normal;

out mediump vec3 v_Normal;
out mediump vec3 v_FragPosition;

uniform mediump mat4 u_Model;
uniform mediump mat4 u_View;
uniform mediump mat4 u_Projection;

void
main() {
    gl_Position = u_Projection * u_View * u_Model * pos;
    v_Normal = vec3(normal);
    v_FragPosition = vec3(u_Model * pos); // position of each fragment in world space
};
