#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "headers/shaderutils.h"
#include "headers/glutils.h"
#include "headers/renderobjects.h"

int
main()
{
    GLFWwindow* win;

    if (!glfwInit()) {
        std::cerr << "Failed to initialize glfw" << std::endl;
        return 1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    win = glfwCreateWindow(400, 400, "LowPoly", NULL, NULL);
    glfwMakeContextCurrent(win);

    if (glewInit() != GLEW_OK) {
        std::cerr << "Failed to initialize glew" << std::endl;
        return 1;
    }

    /* opengl config */
    glCall(glPolygonMode(GL_FRONT_AND_BACK, GL_LINE));

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

    /* vertex array object */
    unsigned int vao_id;
    glCall(glGenVertexArrays(1, &vao_id));
    glCall(glBindVertexArray(vao_id));

    /* vertex buffers */
    VertexBuffer vb(triangle_pos, 8, GL_STATIC_DRAW);
    vb.bind();

    glCall(glEnableVertexAttribArray(0));
    glCall(glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2*sizeof(float), 0));

    /* index buffers */
    IndexBuffer ib(indicies, 6, GL_STATIC_DRAW);
    ib.bind();

    /* shaders */
    std::string vertexShader = readShader("shaders/basicVertex.shader");
    std::string fragmentShader = readShader("shaders/basicFragment.shader");

    // TODO: check for errors reading shader files

    unsigned int shader = generateShader(vertexShader, fragmentShader);
    glCall(glUseProgram(shader));

    /* uniforms */
    int u_Color_loc = glGetUniformLocation(shader, "u_Color");
    // TODO: check invalid location

    /* clean up */
    glCall(glBindVertexArray(0));
    glCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
    glCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
    glCall(glUseProgram(0));

    /* main loop */
    while (!glfwWindowShouldClose(win)) {

        glCall(glClear(GL_COLOR_BUFFER_BIT));

        /* prepare draw call */
        glCall(glUseProgram(shader));
        glCall(glUniform4f(u_Color_loc, 1.0f, 1.0f, 0.0f, 1.0f));

        glCall(glBindVertexArray(vao_id));
        glCall(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr));

        glfwSwapBuffers(win);
        glfwPollEvents();

    }

    glfwTerminate();
    return 0;
}

