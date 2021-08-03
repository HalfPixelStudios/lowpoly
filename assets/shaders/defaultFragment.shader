#version 300 es
layout(location = 0) out mediump vec4 color;

uniform mediump vec3 u_ModelColor;
uniform mediump vec3 u_AmbientColor;

void
main() {
    color = vec4(u_ModelColor * u_AmbientColor, 1.0);
}
