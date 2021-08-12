#version 300 es
layout(location = 0) out mediump vec4 color;

#include assets/shaders/common.shaderh

in mediump vec2 v_TexCoord;
in mediump vec3 v_Normal;
in mediump vec3 v_FragPosition;

uniform Material u_Material;
uniform mediump vec3 u_ViewerPosition;
uniform DirectionalLight u_DirectionalLights[MAX_DIRECTIONAL_LIGHTS];
uniform PointLight u_PointLights[MAX_POINT_LIGHTS];
uniform SpotLight u_SpotLights[MAX_SPOT_LIGHTS];

mediump vec3 computeDirectionalLight(DirectionalLight light, mediump vec3 lightRay, mediump vec3 normRay, mediump vec3 viewRay);
mediump vec3 computePointLight(PointLight light);
mediump vec3 computeSpotLight(SpotLight light);

void
main() {
    mediump vec3 outputColor = vec3(0.0);

    outputColor += u_Material.ambient;

    for (int i = 0; i < MAX_DIRECTIONAL_LIGHTS; i++) {
        outputColor += computeDirectionalLight(
            u_DirectionalLights[i],
            normalize(-u_DirectionalLights[i].direction),
            normalize(v_Normal), // this can be optimized (do it outside the loop)
            normalize(u_ViewerPosition-v_FragPosition)
        );
    }

    color = texture(u_Material.diffuse, v_TexCoord) * vec4(outputColor, 1.0);
}

mediump vec3
computeDirectionalLight(DirectionalLight light, mediump vec3 lightRay, mediump vec3 normRay, mediump vec3 viewRay)
{
    mediump vec3 diffuseLight = max(dot(normRay, lightRay), 0.0) * light.color;

    mediump vec3 reflectedRay = reflect(-lightRay, normRay);
    mediump vec3 specularLight = vec3(texture(u_Material.specular, v_TexCoord))
        * light.specularStrength
        * pow(max(dot(viewRay, reflectedRay), 0.0), light.specularShininess)
        * light.color;

    return diffuseLight + specularLight;
}

/*     mediump vec3 lightRay = (u_Light.type == LIGHTTYPE_DIRECTIONAL) ? normalize(-v_LightDirection) : normalize(v_LightPosition - v_FragPosition); */
/*     mediump vec3 normRay = normalize(v_Normal); */

/*     /1* ambient lighting calculation *1/ */
/*     mediump vec4 ambientLight = vec4(u_Material.ambient, 1.0); */

/*     /1* diffuse lighting calculation *1/ */
/*     mediump vec4 diffuseLight = max(dot(normRay, lightRay), 0.0) * vec4(u_Light.color, 1.0); */

/*     /1* specular lighting calculation *1/ */
/*     mediump vec3 viewRay = normalize(-v_FragPosition); */
/*     mediump vec3 reflectedRay = reflect(-lightRay, normRay); */
/*     mediump vec4 specularLight = texture(u_Material.specular, v_TexCoord) */
/*         * u_Light.specularStrength */
/*         * pow(max(dot(viewRay, reflectedRay), 0.0), u_Light.specularShininess) */
/*         * vec4(u_Light.color, 1.0); */

/*     /1* calculate light attenuation *1/ */
/*     mediump float distanceToLight = distance(v_LightPosition, v_FragPosition); */
/*     mediump float attenuation = 1.0/(1.0 + u_Light.attenuationLinear*distanceToLight + u_Light.attenuationQuadratic*pow(distanceToLight, 2.0)); */

/*     if (u_Light.type == LIGHTTYPE_DIRECTIONAL) { */
/*         color = texture(u_Material.diffuse, v_TexCoord) * (ambientLight + diffuseLight + specularLight); */

/*     } else if (u_Light.type == LIGHTTYPE_SPOTLIGHT) { */
/*         /1* check to see if ray is within spotlight *1/ */
/*         mediump float rayAngle = dot(lightRay, normalize(-v_LightDirection)); */
/*         mediump float spotlightIntensity = clamp((rayAngle-u_Light.outerCutoff)/(u_Light.innerCutoff-u_Light.outerCutoff) , 0.0, 1.0); */
        
/*         color = texture(u_Material.diffuse, v_TexCoord) */
/*             * (ambientLight + diffuseLight*spotlightIntensity + specularLight*spotlightIntensity) */
/*             * vec4(attenuation*vec3(1.0, 1.0, 1.0), 1.0); */

/*     } else { */
/*         color = texture(u_Material.diffuse, v_TexCoord) */
/*             * (ambientLight + diffuseLight + specularLight) */
/*             * vec4(attenuation*vec3(1.0, 1.0, 1.0), 1.0); */
/*     } */
