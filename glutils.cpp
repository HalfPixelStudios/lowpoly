
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <cstdio>

#include "headers/glutils.h"

unsigned int
glSizeOfType(GLenum type)
{
    switch (type) {
        case GL_FLOAT: return 4;
        case GL_UNSIGNED_INT: return 4;
    }
    ASSERT(false);
    return 0;
}

void
glPurgeErrors(void)
{
    while (glGetError() != GL_NO_ERROR);
}

bool
glRetrieveErrors(const char* file, int line_number)
{
    GLenum gl_err;
    bool isError;
    
    isError = false;
    while ((gl_err = glGetError()) != GL_NO_ERROR) {
        fprintf(stderr, "[OpenGL Error] (0x%x): %s %d\n", gl_err, file, line_number);
        isError = true;
    }

    return isError;
}

