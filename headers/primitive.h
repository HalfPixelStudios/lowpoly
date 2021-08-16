#ifndef __PRIMITIVE_H__
#define __PRIMITIVE_H__

#include "glm/glm.hpp"
#include "glm/gtc/constants.hpp"
#include <cstdio>

/* contains some primitive meshes */
extern float cube_verticies[192];
extern unsigned int cube_indicies[36];

int generateUVSphere(int slice_count, int stack_count, int* n_vertices, int* n_indices, float** vertices, unsigned int** indices);

#endif // __PRIMITIVE_H__
