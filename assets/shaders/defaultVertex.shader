#version 300 es
layout(location = 0) in vec3 pos;
layout(location = 1) in vec2 tex_coord;
layout(location = 2) in vec3 normal;

out mediump vec2 v_TexCoord;
out mediump vec3 v_Normal;
out mediump vec3 v_FragPosition;
out mediump vec3 v_LightPosition;

struct MVP {
    mediump mat4 model;
    mediump mat4 view;
    mediump mat4 projection;
};
uniform MVP u_MVP;

struct Light {
    mediump vec3 position;
    mediump vec3 color;
    mediump float specularStrength;
    mediump float specularShininess;
};
uniform Light u_Light;

void
main() {
    gl_Position = u_MVP.projection * u_MVP.view * u_MVP.model * vec4(pos, 1.0);
    v_TexCoord = tex_coord;
    v_Normal = vec3(u_MVP.view * u_MVP.model * vec4(normal, 0.0));
    v_FragPosition = vec3(u_MVP.view * u_MVP.model * vec4(pos, 1.0)); // position of each fragment in world space
    v_LightPosition = vec3(u_MVP.view * vec4(u_Light.position, 1.0));
};
