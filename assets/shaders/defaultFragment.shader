#version 300 es
layout(location = 0) out mediump vec4 color;

in mediump vec3 v_Normal;
in mediump vec3 v_FragPosition;

uniform mediump vec3 u_ModelColor;
uniform mediump vec3 u_AmbientColor;
uniform mediump vec3 u_LightPosition;
uniform mediump vec3 u_LightColor;

void
main() {
    /* diffuse lighting calculation */
    mediump vec3 normRay = normalize(v_Normal);
    mediump vec3 lightRay = normalize(u_LightPosition - v_FragPosition);
    mediump vec3 diffuse = max(dot(normRay, lightRay), 0.0) * u_LightColor;

    color = vec4(u_ModelColor * (u_AmbientColor + diffuse), 1.0);
}
