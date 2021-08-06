#version 300 es
layout(location = 0) in vec4 pos;
layout(location = 2) in vec4 normal;

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
    mediump vec3 lightPosition;
    mediump vec3 lightColor;
    mediump vec3 viewerPosition;
};
uniform Light u_Light;

void
main() {
    gl_Position = u_MVP.projection * u_MVP.view * u_MVP.model * pos;
    v_Normal = vec3(u_MVP.view * u_MVP.model * normal);
    v_FragPosition = vec3(u_MVP.view * u_MVP.model * pos); // position of each fragment in world space
    v_LightPosition = vec3(u_MVP.view * vec4(u_Light.lightPosition, 1.0));
};
