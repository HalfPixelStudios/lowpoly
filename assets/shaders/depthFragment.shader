#version 300 es
layout(location = 0) out mediump vec4 color;

uniform mediump float u_NearCulling;
uniform mediump float u_FarCulling;

mediump float depthLinearization(mediump float raw_depth);

void
main()
{
    color = vec4(vec3(1.0-depthLinearization(gl_FragCoord.z)/u_FarCulling), 1.0);
}

mediump float
depthLinearization(mediump float raw_depth)
{
    mediump float z = raw_depth * 2.0 - 1.0;
    return (2.0*u_NearCulling*u_FarCulling)/(u_FarCulling+u_NearCulling-z*(u_FarCulling-u_NearCulling));
}
