#ifndef __PRIMITIVE_H__
#define __PRIMITIVE_H__

#include "glm/glm.hpp"
#include "glm/gtc/constants.hpp"
#include <cstdio>

/* contains some primitive meshes */
extern float cube_verticies[192];
extern unsigned int cube_indicies[36];

float* generateUVSphere(int slice_count, int stack_count);

#endif // __PRIMITIVE_H__
