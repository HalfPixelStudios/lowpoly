#version 300 es
layout(location = 0) out mediump vec4 color;

uniform mediump vec3 u_Color;

void
main()
{
    color = vec4(u_Color, 1.0);
}
