#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "headers/shaderutils.h"
#include "headers/glutils.h"

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
         0.5f, -0.5f,
         0.5f,  0.5f,
        -0.5f,  0.5f
    };
    unsigned int indicies[] = {
        0, 1, 2,
        2, 3, 0
    };

    /* vertex buffers */
    unsigned int vbuf_id;
    glGenBuffers(1, &vbuf_id);
    glBindBuffer(GL_ARRAY_BUFFER, vbuf_id);
    glBufferData(GL_ARRAY_BUFFER, 8*sizeof(float), triangle_pos, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2*sizeof(float), 0);

    /* index buffers */
    unsigned int ibuf_id;
    glGenBuffers(1, &ibuf_id);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibuf_id);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6*sizeof(unsigned int), indicies, GL_STATIC_DRAW);

    /* shaders */
    std::string vertexShader = readShader("shaders/basicVertex.shader");
    std::string fragmentShader = readShader("shaders/basicFragment.shader");

    // TODO: check for errors reading shader files

    unsigned int shader = generateShader(vertexShader, fragmentShader);
    glUseProgram(shader);

    /* main loop */
    while (!glfwWindowShouldClose(win)) {

        glClear(GL_COLOR_BUFFER_BIT);

        glCall(glDrawElements(GL_TRIANGLES, 6, GL_INT, nullptr));

        glfwSwapBuffers(win);
        glfwPollEvents();

    }

    glfwTerminate();
    return 0;
}

