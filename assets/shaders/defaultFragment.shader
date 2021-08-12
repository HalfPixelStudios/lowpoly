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

mediump vec3 computeDirectionalLight(DirectionalLight light, mediump vec3 normRay, mediump vec3 viewRay);
mediump vec3 computePointLight(PointLight light, mediump vec3 normRay, mediump vec3 viewRay);
mediump vec3 computeSpotLight(SpotLight light, mediump vec3 normRay, mediump vec3 viewRay);

mediump vec3 calculateDiffuseLight(mediump vec3 lightRay, mediump vec3 normRay, mediump vec3 lightColor);
mediump vec3 calculateSpecularLight(mediump vec3 viewRay, mediump vec3 reflectedRay, mediump vec3 lightColor, mediump float specularStrength, mediump float specularShininess);
mediump float calculateAttenuationValue(mediump vec3 lightPosition, mediump float attenuationLinear, mediump float attenuationQuadratic);

void
main() {
    mediump vec3 outputColor = vec3(0.0);

    outputColor += u_Material.ambient;

    mediump vec3 normRay = normalize(v_Normal);
    mediump vec3 viewRay = normalize(u_ViewerPosition-v_FragPosition);

    for (int i = 0; i < MAX_DIRECTIONAL_LIGHTS; i++)
        outputColor += computeDirectionalLight(u_DirectionalLights[i], normRay, viewRay);

    for (int i = 0; i < MAX_POINT_LIGHTS; i++)
        outputColor += computePointLight(u_PointLights[i], normRay, viewRay);

    for (int i = 0; i < MAX_SPOT_LIGHTS; i++)
        outputColor += computeSpotLight(u_SpotLights[i], normRay, viewRay);

    color = texture(u_Material.diffuse, v_TexCoord) * vec4(outputColor, 1.0);
}

mediump vec3
computeDirectionalLight(DirectionalLight light, mediump vec3 normRay, mediump vec3 viewRay)
{
    mediump vec3 lightRay = normalize(-light.direction);

    mediump vec3 diffuseLight = calculateDiffuseLight(lightRay, normRay, light.color);
    mediump vec3 specularLight = calculateSpecularLight(
        viewRay, reflect(-lightRay, normRay),
        light.color, light.specularStrength, light.specularShininess
    );

    return diffuseLight + specularLight;
}

mediump vec3
computePointLight(PointLight light, mediump vec3 normRay, mediump vec3 viewRay)
{
    mediump vec3 lightRay = normalize(light.position-v_FragPosition);

    mediump vec3 diffuseLight = calculateDiffuseLight(lightRay, normRay, light.color);
    mediump vec3 specularLight = calculateSpecularLight(
        viewRay, reflect(-lightRay, normRay),
        light.color, light.specularStrength, light.specularShininess
    );
    mediump float attenuation = calculateAttenuationValue(light.position, light.attenuationLinear, light.attenuationQuadratic);

    return (diffuseLight + specularLight) * attenuation;
}

mediump vec3
computeSpotLight(SpotLight light, mediump vec3 normRay, mediump vec3 viewRay)
{
    mediump vec3 lightRay = normalize(light.position-v_FragPosition);

    mediump vec3 diffuseLight = calculateDiffuseLight(lightRay, normRay, light.color);
    mediump vec3 specularLight = calculateSpecularLight(
        viewRay, reflect(-lightRay, normRay),
        light.color, light.specularStrength, light.specularShininess
    );
    mediump float attenuation = calculateAttenuationValue(light.position, light.attenuationLinear, light.attenuationQuadratic);

    /* check to see if ray is within spotlight */
    mediump float rayAngle = dot(lightRay, normalize(-light.direction));
    mediump float spotlightIntensity = clamp((rayAngle-light.outerCutoff)/(light.innerCutoff-light.outerCutoff) , 0.0, 1.0);
    
    return (diffuseLight + specularLight) * spotlightIntensity * attenuation;
}

mediump vec3
calculateDiffuseLight(mediump vec3 lightRay, mediump vec3 normRay, mediump vec3 lightColor)
{
    return max(dot(normRay, lightRay), 0.0) * lightColor;
}

mediump vec3
calculateSpecularLight(mediump vec3 viewRay, mediump vec3 reflectedRay, mediump vec3 lightColor, mediump float specularStrength, mediump float specularShininess)
{
    return vec3(texture(u_Material.specular, v_TexCoord))
        * specularStrength
        * pow(max(dot(viewRay, reflectedRay), 0.0), specularShininess)
        * lightColor;
}

mediump float
calculateAttenuationValue(mediump vec3 lightPosition, mediump float attenuationLinear, mediump float attenuationQuadratic)
{
    mediump float distanceToLight = distance(lightPosition, v_FragPosition);
    return 1.0/(1.0 + attenuationLinear*distanceToLight + attenuationQuadratic*pow(distanceToLight, 2.0));
}
