#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <cstdio>

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
#include "headers/camera.h"
#include "headers/light.h"
#include "headers/model.h"

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

    const int win_width = 1600;
    const int win_height = 900;
    win = glfwCreateWindow(win_width, win_height, "LowPoly", NULL, NULL);
    glfwMakeContextCurrent(win);
    glfwSetInputMode(win, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

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
    glCall(glEnable(GL_STENCIL_TEST));

    /* setup imgui */
    ImGui::CreateContext();
    ImGui_ImplGlfw_InitForOpenGL(win, true);
    ImGui_ImplOpenGL3_Init("#version 300 es");

    ImGui::StyleColorsDark();

    /* setup objects */
    Mesh cube_mesh(cube_verticies, std::vector<Texture>(), cube_indicies);

    /* shaders */
    Shader default_shader("assets/shaders/defaultVertex.shader", "assets/shaders/defaultFragment.shader");
    Shader depth_shader("assets/shaders/depthVertex.shader", "assets/shaders/depthFragment.shader");
    Shader unlit_shader("assets/shaders/unlitVertex.shader", "assets/shaders/unlitFragment.shader");
    Shader solid_shader("assets/shaders/solidVertex.shader", "assets/shaders/solidFragment.shader");

    // TODO: check invalid location

    /* textures */
    Texture container_diffuseMap("assets/textures/container_diffuse.png", TextureType_Diffuse);
    Texture container_specularMap("assets/textures/container_specular.png", TextureType_Specular);

    /* models */
    Model monkey_model("assets/models/monkey.obj");

    Renderer renderer;
    bool show_demo_window = true;

    Camera main_cam(0.25f, 0.25f);
    Light main_light(glm::vec3(4.0f, 4.0f, 4.0f), glm::vec3(1.0f, 1.0f, 1.0f), 1.0f);

    glm::vec3 crate_positions[200];
    float crate_radius = 20;
    #define randRange 2*((double)rand()/RAND_MAX - 0.5)
    for (int i = 0; i < 200; i++) {
        crate_positions[i] = glm::vec3(crate_radius*randRange, crate_radius*randRange, crate_radius*randRange);
    }

    /* main loop */
    while (!glfwWindowShouldClose(win)) {

        renderer.clear();

        /* imgui */
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        /* ImGui::ShowDemoWindow(&show_demo_window); */
    
        /* mvp */
        const float near_culling = 1.0f;
        const float far_culling = 50.0f;
        glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)4/3, near_culling, far_culling); 
        glm::mat4 view = main_cam.getViewMatrix();

        /* setup draw call */
        default_shader.bind();
        default_shader.setUniform3f("u_Material.ambient", main_light.getColor() * 0.1f);
        container_diffuseMap.bind(1);
        default_shader.setUniform1i("u_Material.diffuse", 1);
        container_specularMap.bind(0);
        default_shader.setUniform1i("u_Material.specular", 0);

        default_shader.setUniform3f("u_ViewerPosition", main_cam.getPosition());

        default_shader.setUniform3f("u_DirectionalLights[0].direction", main_light.getPosition());
        default_shader.setUniform3f("u_DirectionalLights[0].color", main_light.getColor());
        default_shader.setUniform1f("u_DirectionalLights[0].specularStrength", 4.0);
        default_shader.setUniform1f("u_DirectionalLights[0].specularShininess", 2.0);

        default_shader.setUniform3f("u_PointLights[0].position", glm::vec3(0.0f, 0.0f, 0.0f));
        default_shader.setUniform3f("u_PointLights[0].color", glm::vec3(0.0f, 0.0f, 1.0f));
        default_shader.setUniform1f("u_PointLights[0].specularStrength", 4.0);
        default_shader.setUniform1f("u_PointLights[0].specularShininess", 2.0);
        default_shader.setUniform1f("u_PointLights[0].attenuationLinear", 0.045f);
        default_shader.setUniform1f("u_PointLights[0].attenuationQuadratic", 0.0075f);

        default_shader.setUniform3f("u_SpotLights[0].position", main_cam.getPosition());
        default_shader.setUniform3f("u_SpotLights[0].direction", main_cam.getForwardVector());
        default_shader.setUniform3f("u_SpotLights[0].color", glm::vec3(0.0f, 1.0f, 0.0f));
        default_shader.setUniform1f("u_SpotLights[0].specularStrength", 4.0);
        default_shader.setUniform1f("u_SpotLights[0].specularShininess", 2.0);
        default_shader.setUniform1f("u_SpotLights[0].attenuationLinear", 0.045f);
        default_shader.setUniform1f("u_SpotLights[0].attenuationQuadratic", 0.0075f);
        default_shader.setUniform1f("u_SpotLights[0].innerCutoff", glm::cos(glm::radians(12.0f)));
        default_shader.setUniform1f("u_SpotLights[0].outerCutoff", glm::cos(glm::radians(14.0f)));

        default_shader.setUniformMat4f("u_MVP.view", view);
        default_shader.setUniformMat4f("u_MVP.projection", projection);

        glCall(glStencilMask(0x00));
        glm::mat4 model;
        for (int i = 0; i < sizeof(crate_positions)/sizeof(glm::vec3); i++) {
            model = glm::translate(glm::mat4(1.0), crate_positions[i]);
            default_shader.setUniformMat4f("u_MVP.model", model);
            renderer.drawMesh(cube_mesh, default_shader);
        }

        /* object outlining */
        glCall(glStencilMask(0xFF));
        glCall(glStencilFunc(GL_ALWAYS, 1, 0xFF));
        glCall(glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE));

        default_shader.setUniformMat4f("u_MVP.model", glm::mat4(1.0f));
        renderer.drawMesh(cube_mesh, default_shader);

        glCall(glStencilMask(0x00));
        glCall(glStencilFunc(GL_NOTEQUAL, 1, 0xFF));
        glCall(glDisable(GL_DEPTH_TEST));

        solid_shader.bind();
        solid_shader.setUniform3f("u_Color", glm::vec3(1.0f, 0.0f, 0.0f));
        solid_shader.setUniformMat4f("u_MVP.view", view);
        solid_shader.setUniformMat4f("u_MVP.projection", projection);
        solid_shader.setUniformMat4f("u_MVP.model", glm::scale(glm::mat4(1.0f), glm::vec3(1.05f, 1.05f, 1.05f)));
        renderer.drawMesh(cube_mesh, solid_shader);

        glCall(glEnable(GL_DEPTH_TEST));
        glCall(glStencilMask(0xFF));
        glCall(glStencilFunc(GL_ALWAYS, 1, 0xFF));

        /* render imgui */
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        /* input */
        main_cam.processInput(win);

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

