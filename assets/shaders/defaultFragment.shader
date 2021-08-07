#version 300 es
layout(location = 0) out mediump vec4 color;

in mediump vec2 v_TexCoord;
in mediump vec3 v_Normal;
in mediump vec3 v_FragPosition;
in mediump vec3 v_LightPosition;

struct Material {
    mediump vec3 ambient;
    mediump sampler2D diffuse;
    mediump sampler2D specular;
};
uniform Material u_Material;

struct Light {
    mediump vec3 position;
    mediump vec3 color;
    mediump float specularStrength; // brightness of specular
    mediump float specularShininess;  // shininess of specular (tendancy to bounce light)
};
uniform Light u_Light;

void
main() {
    mediump vec3 lightRay = normalize(v_LightPosition - v_FragPosition);
    mediump vec3 normRay = normalize(v_Normal);

    /* ambient lighting calculation */
    mediump vec4 ambientLight = vec4(u_Material.ambient, 1.0);

    /* diffuse lighting calculation */
    mediump vec4 diffuseLight = max(dot(normRay, lightRay), 0.0) * vec4(u_Light.color, 1.0);

    /* specular lighting calculation */
    mediump vec3 viewRay = normalize(-v_FragPosition);
    mediump vec3 reflectedRay = reflect(-lightRay, normRay);
    mediump vec4 specularLight = texture(u_Material.specular, v_TexCoord)
        * u_Light.specularStrength
        * pow(max(dot(viewRay, reflectedRay), 0.0), u_Light.specularShininess)
        * vec4(u_Light.color, 1.0);

    color = texture(u_Material.diffuse, v_TexCoord) * (ambientLight + diffuseLight + specularLight);
}
