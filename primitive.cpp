
#include "headers/primitive.h"

/* number of slots each vertex takes up */
/* 5 = 3 (position) + 2 (texture) + 3 (normal) ; do normals and texture later */
#define SPHERE_VERTEX_STRIDE 3

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

std::vector<Vertex> cube_verticies {
    // position (x y z), texture (x y), normal (x y z)
    Vertex { glm::vec3(-0.5f, -0.5f,  0.5f),  glm::vec2(0.0f,  0.0f),  glm::vec3(0.0f,  0.0f,  1.0f) },
    Vertex { glm::vec3( 0.5f, -0.5f,  0.5f),  glm::vec2(1.0f,  0.0f),  glm::vec3(0.0f,  0.0f,  1.0f) },
    Vertex { glm::vec3( 0.5f,  0.5f,  0.5f),  glm::vec2(1.0f,  1.0f),  glm::vec3(0.0f,  0.0f,  1.0f) },
    Vertex { glm::vec3(-0.5f,  0.5f,  0.5f),  glm::vec2(0.0f,  1.0f),  glm::vec3(0.0f,  0.0f,  1.0f) },

    Vertex { glm::vec3( 0.5f, -0.5f,  0.5f),  glm::vec2(0.0f,  0.0f),  glm::vec3(1.0f,  0.0f,  0.0f) },
    Vertex { glm::vec3( 0.5f, -0.5f, -0.5f),  glm::vec2(1.0f,  0.0f),  glm::vec3(1.0f,  0.0f,  0.0f) },
    Vertex { glm::vec3( 0.5f,  0.5f, -0.5f),  glm::vec2(1.0f,  1.0f),  glm::vec3(1.0f,  0.0f,  0.0f) },
    Vertex { glm::vec3( 0.5f,  0.5f,  0.5f),  glm::vec2(0.0f,  1.0f),  glm::vec3(1.0f,  0.0f,  0.0f) },

    Vertex { glm::vec3( 0.5f, -0.5f, -0.5f),  glm::vec2(0.0f,  0.0f),  glm::vec3(0.0f,  0.0f, -1.0f) },
    Vertex { glm::vec3(-0.5f, -0.5f, -0.5f),  glm::vec2(1.0f,  0.0f),  glm::vec3(0.0f,  0.0f, -1.0f) },
    Vertex { glm::vec3(-0.5f,  0.5f, -0.5f),  glm::vec2(1.0f,  1.0f),  glm::vec3(0.0f,  0.0f, -1.0f) },
    Vertex { glm::vec3( 0.5f,  0.5f, -0.5f),  glm::vec2(0.0f,  1.0f),  glm::vec3(0.0f,  0.0f, -1.0f) },

    Vertex { glm::vec3(-0.5f, -0.5f, -0.5f),  glm::vec2(0.0f,  0.0f), -glm::vec3(1.0f,  0.0f,  0.0f) },
    Vertex { glm::vec3(-0.5f, -0.5f,  0.5f),  glm::vec2(1.0f,  0.0f), -glm::vec3(1.0f,  0.0f,  0.0f) },
    Vertex { glm::vec3(-0.5f,  0.5f,  0.5f),  glm::vec2(1.0f,  1.0f), -glm::vec3(1.0f,  0.0f,  0.0f) },
    Vertex { glm::vec3(-0.5f,  0.5f, -0.5f),  glm::vec2(0.0f,  1.0f), -glm::vec3(1.0f,  0.0f,  0.0f) },

    Vertex { glm::vec3(-0.5f,  0.5f,  0.5f),  glm::vec2(0.0f,  0.0f),  glm::vec3(0.0f,  1.0f,  0.0f) },
    Vertex { glm::vec3( 0.5f,  0.5f,  0.5f),  glm::vec2(1.0f,  0.0f),  glm::vec3(0.0f,  1.0f,  0.0f) },
    Vertex { glm::vec3( 0.5f,  0.5f, -0.5f),  glm::vec2(1.0f,  1.0f),  glm::vec3(0.0f,  1.0f,  0.0f) },
    Vertex { glm::vec3(-0.5f,  0.5f, -0.5f),  glm::vec2(0.0f,  1.0f),  glm::vec3(0.0f,  1.0f,  0.0f) },

    Vertex { glm::vec3(-0.5f, -0.5f, -0.5f),  glm::vec2(0.0f,  0.0f),  glm::vec3(0.0f, -1.0f,  0.0f) },
    Vertex { glm::vec3( 0.5f, -0.5f, -0.5f),  glm::vec2(1.0f,  0.0f),  glm::vec3(0.0f, -1.0f,  0.0f) },
    Vertex { glm::vec3( 0.5f, -0.5f,  0.5f),  glm::vec2(1.0f,  1.0f),  glm::vec3(0.0f, -1.0f,  0.0f) },
    Vertex { glm::vec3(-0.5f, -0.5f,  0.5f),  glm::vec2(0.0f,  1.0f),  glm::vec3(0.0f, -1.0f,  0.0f) }
};

std::vector<unsigned int> cube_indicies {
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

int
generateUVSphere(int slice_count, int stack_count, int* n_vertices, int* n_indices, float** vertices, unsigned int** indices)
{
    //TODO: maybe check for invalid sizes

    const int vertex_count = slice_count*(stack_count-1) + 2; // add 2 for vertices at poles
    const int index_count = 2*(3*slice_count) + slice_count*(stack_count-2)*2*3; // triangular faces at poles + quad faces in middle

    /* vertex layout in memory */
    /* first 2 vertices are the poles, followed by contiguous chains */
    /* of each slice from top to down */
    float* sphere_vertices = (float*)malloc(sizeof(float)*vertex_count*SPHERE_VERTEX_STRIDE);
    unsigned int* sphere_indices = (unsigned int*)malloc(sizeof(unsigned int)*index_count);

    /* set vertices at the poles */
    sphere_vertices[0] = 0.0f;
    sphere_vertices[1] = 1.0f;
    sphere_vertices[2] = 0.0f;

    sphere_vertices[3] = 0.0f;
    sphere_vertices[4] = -1.0f;
    sphere_vertices[5] = 0.0f;

    /* loop through each slice */
    int vertex_offset = 2*SPHERE_VERTEX_STRIDE;
    for (int i = 0; i < slice_count; i++) {

        /* loop through each stack */
        for (int j = 1; j < stack_count; j++) {

            const float theta = i*2*glm::pi<float>()/slice_count; // slice angle
            const float phi = glm::pi<float>()/2-j*glm::pi<float>()/stack_count; // stack angle

            const float x = glm::cos(theta)*glm::cos(phi);
            const float y = glm::sin(phi);
            const float z = glm::sin(theta)*glm::cos(phi);

            sphere_vertices[vertex_offset]   = x;
            sphere_vertices[vertex_offset+1] = y;
            sphere_vertices[vertex_offset+2] = z;

            vertex_offset += SPHERE_VERTEX_STRIDE;

        }

    } 

    int index_offset = 0;
    for (int i = 0; i < slice_count; i++) {

        /* top triangluar faces */
        sphere_indices[index_offset] = 0; // top pole
        sphere_indices[index_offset+1] = i*stack_count+2; // first item in stack
        sphere_indices[index_offset+2] = (i == slice_count-1 ? 0 : i+1)*stack_count+2; // first item next stack
        index_offset += 3;

        /* bottom triangular faces */
        sphere_indices[index_offset] = 1; // bottom pole
        sphere_indices[index_offset+1] = (i == slice_count-1 ? 0 : i+1)*stack_count+(stack_count-1)+2; // last item next stack
        sphere_indices[index_offset+2] = i*stack_count+(stack_count-1)+2; // last item in stack
        index_offset += 3;

        /* middle quad faces */
        for (int j = 0; j < stack_count-2; j++) {

            sphere_indices[index_offset] = i*stack_count+j+2; // top left vertex
            sphere_indices[index_offset+1] = i*stack_count+(j+1)+2; // bottom left vertex
            sphere_indices[index_offset+2] = (i == slice_count-1 ? 0 : i+1)*stack_count+(j+1)+2; // bottom right vertex
            index_offset += 3;

            sphere_indices[index_offset] = (i == slice_count-1 ? 0 : i+1)*stack_count+(j+1)+2; // bottom right vertex
            sphere_indices[index_offset+1] = (i == slice_count-1 ? 0 : i+1)*stack_count+j+2; // top right corner
            sphere_indices[index_offset+2] = i*stack_count+j+2; // top left vertex
            index_offset += 3;
        }
    }

    /* for (int i = 0; i < vertex_count; i++) { */
    /*     printf("[%i] %f,%f,%f\n", i, sphere_vertices[i*3], sphere_vertices[i*3+1], sphere_vertices[i*3+2]); */
    /* } */
    /* for (int i = 0; i < (int)index_count/3; i++) { */
    /*     printf("[%i] %i,%i,%i\n", i, sphere_indices[i*3], sphere_indices[i*3+1], sphere_indices[i*3+2]); */
    /* } */

    *n_vertices = vertex_count;
    *n_indices = index_count;
    *vertices = sphere_vertices;
    *indices = sphere_indices;

    /* return number of triangles */
    return (int)index_count/3;
}

