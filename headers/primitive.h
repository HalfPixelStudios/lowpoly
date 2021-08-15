#ifndef __PRIMITIVE_H__
#define __PRIMITIVE_H__

#include "glm/glm.hpp"
#include "glm/gtc/constants.hpp"
#include <cstdio>

/* contains some primitive meshes */

/* float plane_verticies[] = { */
/*     -0.5f, -0.5f, 0.0f, 0.0f, */
/*      0.5f, -0.5f, 1.0f, 0.0f, */
/*      0.5f,  0.5f, 1.0f, 1.0f, */
/*     -0.5f,  0.5f, 0.0f, 1.0f */
/* }; */

/* unsigned int plane_indicies[] = { */
/*     0, 1, 2, */
/*     2, 3, 0 */
/* }; */

extern float cube_verticies[192];
extern unsigned int cube_indicies[36];

unsigned int generateUVSphere(int slice_count, int stack_count);

#endif // __PRIMITIVE_H__
