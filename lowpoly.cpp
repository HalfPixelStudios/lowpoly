#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "headers/shaderutils.h"
#include "headers/glutils.h"
#include "headers/renderobjects.h"
#include "headers/renderer.h"
#include "headers/texture.h"

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
    /* glCall(glPolygonMode(GL_FRONT_AND_BACK, GL_LINE)); */
    glCall(glEnable(GL_BLEND));
    glCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
    glCall(glBlendEquation(GL_FUNC_ADD));

    /* make a buffer */
    float verticies[] = {
        -0.5f, -0.5f, 0.0f, 0.0f,
         0.5f, -0.5f, 1.0f, 0.0f,
         0.5f,  0.5f, 1.0f, 1.0f,
        -0.5f,  0.5f, 0.0f, 1.0f
    };
    unsigned int indicies[] = {
        0, 1, 2,
        2, 3, 0
    };

    /* vertex array object */
    VertexArrayObject vao;

    VertexBuffer vb(verticies, sizeof(verticies)/sizeof(verticies[0]), GL_STATIC_DRAW);
    vb.bind();

    vao.addAttribute<float>(2);
    vao.addAttribute<float>(2);
    vao.bindToVertexBuffer(vb);

    IndexBuffer ib(indicies, sizeof(indicies)/sizeof(indicies[0]), GL_STATIC_DRAW);
    ib.bind();

    /* shaders */
    Shader basic_shader("assets/shaders/basicVertex.shader", "assets/shaders/basicFragment.shader");
    basic_shader.bind();

    // TODO: check invalid location

    /* textures */
    Texture tex("assets/textures/nagato.png");

    /* clean up */
    vao.unbind();
    vb.unbind();
    ib.unbind();
    basic_shader.unbind();

    Renderer renderer;

    /* main loop */
    while (!glfwWindowShouldClose(win)) {

        renderer.clear();
    
        /* setup draw call */
        basic_shader.bind();
        basic_shader.setUniform4f("u_Color", 1.0f, 1.0f, 0.0f, 1.0f);

        tex.bind(0);
        basic_shader.setUniform1i("u_Texture", 0);

        renderer.draw(vao, ib, basic_shader);

        glfwSwapBuffers(win);
        glfwPollEvents();

    }

    glfwTerminate();
    return 0;
}

