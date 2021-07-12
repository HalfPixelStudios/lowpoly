#version 300 es
layout(location = 0) out mediump vec4 color;

in mediump vec2 v_TexCoord;

uniform mediump vec4 u_Color;
uniform mediump sampler2D u_Texture;

void
main() {
    color = mix(texture(u_Texture, v_TexCoord), u_Color, 0.5);
}
