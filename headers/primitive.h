#ifndef __PRIMITIVE_H__
#define __PRIMITIVE_H__

#include "glm/glm.hpp"
#include "glm/gtc/constants.hpp"
#include <cstdio>
#include <vector>

#include "renderobjects.h"

/* contains some primitive meshes */
extern std::vector<Vertex> cube_verticies;
extern std::vector<unsigned int> cube_indicies;

int generateUVSphere(int slice_count, int stack_count, int* n_vertices, int* n_indices, float** vertices, unsigned int** indices);

#endif // __PRIMITIVE_H__
