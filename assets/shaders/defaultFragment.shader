#version 300 es
layout(location = 0) out mediump vec4 color;

in mediump vec3 v_Normal;
in mediump vec3 v_FragPosition;
in mediump vec3 v_LightPosition;

struct Material {
    mediump vec3 ambient;
    mediump vec3 diffuse;
    mediump float specular;
};
uniform Material u_Material;

struct Light {
    mediump vec3 lightPosition;
    mediump vec3 lightColor;
    mediump vec3 viewerPosition;
};
uniform Light u_Light;

void
main() {
    mediump vec3 lightRay = normalize(v_LightPosition - v_FragPosition);
    mediump vec3 normRay = normalize(v_Normal);

    /* ambient lighting calculation */
    mediump vec3 ambientLight = u_Material.ambient;

    /* diffuse lighting calculation */
    mediump vec3 diffuseLight = max(dot(normRay, lightRay), 0.0) * u_Light.lightColor;

    /* specular lighting calculation */
    mediump vec3 viewRay = normalize(-v_FragPosition);
    mediump vec3 reflectedRay = reflect(-lightRay, normRay);
    mediump vec3 specularLight = pow(max(dot(viewRay, reflectedRay), 0.0), u_Material.specular) * u_Light.lightColor;

    color = vec4(u_Material.diffuse * (ambientLight + diffuseLight ), 1.0);
}
