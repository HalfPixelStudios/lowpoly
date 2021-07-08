#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "headers/shaderutils.h"

int
main()
{
    GLFWwindow* win;

    if (!glfwInit()) {
        std::cerr << "Failed to initialize glfw" << std::endl;
        return 1;
    }

    win = glfwCreateWindow(400, 400, "LowPoly", NULL, NULL);
    glfwMakeContextCurrent(win);

    if (glewInit() != GLEW_OK) {
        std::cerr << "Failed to initialize glew" << std::endl;
        return 1;
    }

    /* make a buffer */
    float triangle_pos[] = {
        -0.5f, -0.5f,
         0.0f,  0.5f,
         0.5f, -0.5f,
    };

    unsigned int buffer;
    glGenBuffers(1, &buffer);
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    glBufferData(GL_ARRAY_BUFFER, 6*sizeof(float), triangle_pos, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2*sizeof(float), 0);

    /* write shaders */
    std::string vertexShader = R"glsl(
        #version 300 es
        layout(location = 0) in vec4 pos;
        
        void
        main() {
            gl_Position = pos;
        };
        )glsl";

    std::string fragmentShader = R"glsl(
        #version 300 es
        layout(location = 0) out mediump vec4 color;
        
        void
        main() {
            color = vec4(1.0, 0.0, 0.0, 1.0);
        };
        )glsl";

    unsigned int shader = generateShader(vertexShader, fragmentShader);
    glUseProgram(shader);

    /* main loop */
    while (!glfwWindowShouldClose(win)) {

        glClear(GL_COLOR_BUFFER_BIT);

        glDrawArrays(GL_TRIANGLES, 0, 3);

        glfwSwapBuffers(win);
        glfwPollEvents();

    }

    glfwTerminate();
    return 0;
}

