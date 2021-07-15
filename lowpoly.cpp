#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

#include "headers/shaderutils.h"
#include "headers/glutils.h"
#include "headers/renderobjects.h"
#include "headers/renderer.h"
#include "headers/texture.h"
#include "headers/primitive.h"

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
    glfwWindowHint(GLFW_SAMPLES, 4);

    const int win_width = 800;
    const int win_height = 600;
    win = glfwCreateWindow(win_width, win_height, "LowPoly", NULL, NULL);
    glfwMakeContextCurrent(win);

    if (glewInit() != GLEW_OK) {
        std::cerr << "Failed to initialize glew" << std::endl;
        return 1;
    }

    /* opengl config */
    /* glCall(glPolygonMode(GL_FRONT_AND_BACK, GL_LINE)); */
    glCall(glEnable(GL_MULTISAMPLE));

    glCall(glEnable(GL_BLEND));
    glCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
    glCall(glBlendEquation(GL_FUNC_ADD));

    glCall(glEnable(GL_DEPTH_TEST));

    /* setup imgui */
    ImGui::CreateContext();
    ImGui_ImplGlfw_InitForOpenGL(win, true);
    ImGui_ImplOpenGL3_Init("#version 300 es");

    ImGui::StyleColorsDark();

    /* vertex array object */
    VertexArrayObject vao;

    VertexBuffer vb(cube_verticies, sizeof(cube_verticies)/sizeof(cube_verticies[0]), GL_STATIC_DRAW);
    vb.bind();

    vao.addAttribute<float>(3);
    vao.addAttribute<float>(2);
    vao.bindToVertexBuffer(vb);

    IndexBuffer ib(cube_indicies, sizeof(cube_indicies)/sizeof(cube_indicies[0]), GL_STATIC_DRAW);
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
    bool show_demo_window = true;

    /* glm::mat4 cam_position = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -3.0f)); */
    /* glm::mat4 cam_target = glm::mat4(1.0f); */
    /* glm::mat4 cam_direction = glm::normalize(cam_position - cam_target); */

    glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)4/3, 0.1f, 100.0f); 
    glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -3.0f));
    glm::mat4 model = glm::scale(glm::mat4(1.0f), glm::vec3(1.0f, 1.0f, 1.0f));

    /* main loop */
    while (!glfwWindowShouldClose(win)) {

        renderer.clear();

        /* imgui */
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        ImGui::ShowDemoWindow(&show_demo_window);
    
        /* setup draw call */
        basic_shader.bind();
        basic_shader.setUniform4f("u_Color", 1.0f, 1.0f, 0.0f, 1.0f);

        tex.bind(0);
        basic_shader.setUniform1i("u_Texture", 0);

        glm::mat4 newModel= glm::rotate(model, (float)glfwGetTime(), glm::vec3(1.0f, 1.0f, 1.0f));

        /* glm::mat4 mvp = projection * view * model; */
        glm::mat4 mvp = projection * view * newModel;
        basic_shader.setUniformMat4f("u_MVP", mvp);

        renderer.draw(vao, ib, basic_shader);

        /* render imgui */
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(win);
        glfwPollEvents();

    }

    /* clean up */
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(win);
    glfwTerminate();
    return 0;
}

