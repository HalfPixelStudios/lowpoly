
#include "headers/primitive.h"

/* number of slots each vertex takes up */
/* 3 = 3 (position)  ; do normals and texture later */
#define SPHERE_VERTEX_STRIDE 3

float plane_verticies[] = {
    -0.5f, -0.5f, 0.0f, 0.0f,
     0.5f, -0.5f, 1.0f, 0.0f,
     0.5f,  0.5f, 1.0f, 1.0f,
    -0.5f,  0.5f, 0.0f, 1.0f
};

unsigned int plane_indicies[] = {
    0, 1, 2,
    2, 3, 0
};

float cube_verticies[192] = {
    // position (x y z), texture (x y), normal (x y z)
    -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  0.0f,  0.0f,  1.0f, 
     0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
     0.5f,  0.5f,  0.5f,  1.0f,  1.0f,  0.0f,  0.0f,  1.0f,
    -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f,

     0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,
     0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  1.0f,  0.0f,  0.0f,
     0.5f,  0.5f, -0.5f,  1.0f,  1.0f,  1.0f,  0.0f,  0.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  1.0f,  0.0f,  0.0f,

     0.5f, -0.5f, -0.5f,  0.0f,  0.0f,  0.0f,  0.0f, -1.0f,
    -0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, -1.0f,
    -0.5f,  0.5f, -0.5f,  1.0f,  1.0f,  0.0f,  0.0f, -1.0f,
     0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, -1.0f,

    -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,
    -0.5f, -0.5f,  0.5f,  1.0f,  0.0f, -1.0f,  0.0f,  0.0f,
    -0.5f,  0.5f,  0.5f,  1.0f,  1.0f, -1.0f,  0.0f,  0.0f,
    -0.5f,  0.5f, -0.5f,  0.0f,  1.0f, -1.0f,  0.0f,  0.0f,

    -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  0.0f,  1.0f,  0.0f,
     0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
     0.5f,  0.5f, -0.5f,  1.0f,  1.0f,  0.0f,  1.0f,  0.0f,
    -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,

    -0.5f, -0.5f, -0.5f,  0.0f,  0.0f,  0.0f, -1.0f,  0.0f,
     0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f, -1.0f,  0.0f,
     0.5f, -0.5f,  0.5f,  1.0f,  1.0f,  0.0f, -1.0f,  0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f,  1.0f,  0.0f, -1.0f,  0.0f
};

unsigned int cube_indicies[36] = {
    0, 1, 2,
    2, 3, 0,

    4, 5, 6,
    6, 7, 4,

    8, 9, 10,
    10, 11, 8,

    12, 13, 14,
    14, 15, 12,

    16, 17, 18,
    18, 19, 16,

    20, 21, 22,
    22, 23, 20
};

float*
generateUVSphere(int slice_count, int stack_count)
{
    const int vertex_count = slice_count*(stack_count-1) + 2; // add 2 for vertices at poles

    /* vertex layout in memory */
    /* first 2 vertices are the poles, followed by contiguous chains */
    /* of each slice from top to down */
    float* sphere_vertices = (float*)malloc(sizeof(float)*vertex_count*SPHERE_VERTEX_STRIDE);
    /* unsigned int sphere_indices[]; */

    /* set vertices at the poles */
    sphere_vertices[0] = 0.0f;
    sphere_vertices[1] = 1.0f;
    sphere_vertices[2] = 0.0f;

    sphere_vertices[3] = 0.0f;
    sphere_vertices[4] = -1.0f;
    sphere_vertices[5] = 0.0f;

    /* loop through each slice */
    for (int i = 0; i < slice_count; i++) {

        /* loop through each stack */
        for (int j = 1; j < stack_count; j++) {

            const float theta = i*2*glm::pi<float>()/slice_count; // slice angle
            const float phi = glm::pi<float>()/2-j*glm::pi<float>()/stack_count; // stack angle

            const float x = glm::cos(theta)*glm::cos(phi);
            const float y = glm::sin(phi);
            const float z = glm::sin(theta)*glm::cos(phi);

            const int vertex_offset = (i*(stack_count-1)+(j-1)+2)*SPHERE_VERTEX_STRIDE;
            sphere_vertices[vertex_offset]   = x;
            sphere_vertices[vertex_offset+1] = y;
            sphere_vertices[vertex_offset+2] = z;

        }
    } 

    return sphere_vertices;

}

