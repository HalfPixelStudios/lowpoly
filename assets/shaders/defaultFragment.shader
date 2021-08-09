#version 300 es
layout(location = 0) out mediump vec4 color;

in mediump vec2 v_TexCoord;
in mediump vec3 v_Normal;
in mediump vec3 v_FragPosition;
in mediump vec3 v_LightPosition;
in mediump vec3 v_LightDirection;

#include assets/shaders/common.shaderh

uniform Material u_Material;
uniform Light u_Light;

/* struct PointLight { */
/*     mediump vec3 position; // don't use this uniform in fragment shader, this one is not in view space */
/*     mediump vec3 color; */
/*     mediump float specularStrength; // brightness of specular */
/*     mediump float specularShininess;  // shininess of specular (tendancy to bounce light) */

/*     mediump float attenuationLinear; // linear term for point light attenuation */
/*     mediump float attenuationQuadratic; //quadratic term for point light attenuation */
/* }; */

/* struct DirectionalLight { */
/* }; */

/* struct SpotLight { */
/* }; */

void
main() {
    mediump vec3 lightRay = (u_Light.type == LIGHTTYPE_DIRECTIONAL) ? normalize(-v_LightDirection) : normalize(v_LightPosition - v_FragPosition);
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

    /* calculate light attenuation */
    mediump float distanceToLight = distance(v_LightPosition, v_FragPosition);
    mediump float attenuation = 1.0/(1.0 + u_Light.attenuationLinear*distanceToLight + u_Light.attenuationQuadratic*pow(distanceToLight, 2.0));

    if (u_Light.type == LIGHTTYPE_DIRECTIONAL) {
        color = texture(u_Material.diffuse, v_TexCoord) * (ambientLight + diffuseLight + specularLight);

    } else if (u_Light.type == LIGHTTYPE_SPOTLIGHT) {
        /* check to see if ray is within spotlight */
        mediump float rayAngle = dot(lightRay, normalize(-v_LightDirection));
        mediump float spotlightIntensity = clamp((rayAngle-u_Light.outerCutoff)/(u_Light.innerCutoff-u_Light.outerCutoff) , 0.0, 1.0);
        
        color = texture(u_Material.diffuse, v_TexCoord)
            * (ambientLight + diffuseLight*spotlightIntensity + specularLight*spotlightIntensity)
            * vec4(attenuation*vec3(1.0, 1.0, 1.0), 1.0);

    } else {
        color = texture(u_Material.diffuse, v_TexCoord)
            * (ambientLight + diffuseLight + specularLight)
            * vec4(attenuation*vec3(1.0, 1.0, 1.0), 1.0);
    }
}
