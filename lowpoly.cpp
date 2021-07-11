#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "headers/shaderutils.h"
#include "headers/glutils.h"
#include "headers/renderobjects.h"
#include "headers/renderer.h"

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
    VertexArrayObject vao;

    VertexBuffer vb(triangle_pos, 8, GL_STATIC_DRAW);
    vb.bind();

    vao.addAttribute<float>(2);
    vao.bindToVertexBuffer(vb);

    IndexBuffer ib(indicies, 6, GL_STATIC_DRAW);
    ib.bind();

    /* shaders */
    Shader basic_shader("shaders/basicVertex.shader", "shaders/basicFragment.shader");
    basic_shader.bind();

    // TODO: check invalid location

    /* clean up */
    vao.unbind();
    vb.unbind();
    ib.unbind();
    basic_shader.unbind();

    Renderer renderer;

    /* uniform stuff, move later */
    int u_Color_loc = basic_shader.getUniformLocation("u_Color");

    /* main loop */
    while (!glfwWindowShouldClose(win)) {

        renderer.clear();
    
        /* set uniforms, abstract later */
        basic_shader.bind();
        glCall(glUniform4f(u_Color_loc, 1.0f, 1.0f, 0.0f, 1.0f));

        renderer.draw(vao, ib, basic_shader);

        glfwSwapBuffers(win);
        glfwPollEvents();

    }

    glfwTerminate();
    return 0;
}

