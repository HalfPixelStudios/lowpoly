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

    /* setup imgui */
    ImGui::CreateContext();
    ImGui_ImplGlfw_InitForOpenGL(win, true);
    ImGui_ImplOpenGL3_Init("#version 300 es");

    ImGui::StyleColorsDark();

    /* setup objects */
    VertexArrayObject cube_vao;
    VertexBuffer cube_vb(cube_verticies, sizeof(cube_verticies)/sizeof(cube_verticies[0]), GL_STATIC_DRAW);
    cube_vb.bind();

    cube_vao.addAttribute<float>(3);
    cube_vao.addAttribute<float>(2);
    cube_vao.addAttribute<float>(3);
    cube_vao.bindToVertexBuffer(cube_vb);

    IndexBuffer cube_ib(cube_indicies, sizeof(cube_indicies)/sizeof(cube_indicies[0]), GL_STATIC_DRAW);

    cube_vao.unbind();
    cube_vb.unbind();
    cube_ib.unbind();

    int sphere_vertex_count;
    int sphere_index_count;
    float* sphere_vertices;
    unsigned int* sphere_indices; // free these after
    int sphere_triangle_count = generateUVSphere(10, 10, &sphere_vertex_count, &sphere_index_count, &sphere_vertices, &sphere_indices);
    printf("%i, %i, %i\n", sphere_vertex_count, sphere_index_count, sphere_triangle_count);

    for (int i = 0; i < sphere_vertex_count; i++) {
        printf("[%i] %f,%f,%f\n", i, sphere_vertices[i*3], sphere_vertices[i*3+1], sphere_vertices[i*3+2]);
    }

    VertexArrayObject sphere_vao;
    VertexBuffer sphere_vb(sphere_vertices, sphere_vertex_count*3, GL_STATIC_DRAW);
    sphere_vb.bind();

    sphere_vao.addAttribute<float>(3);
    sphere_vao.bindToVertexBuffer(sphere_vb);

    IndexBuffer sphere_ib(sphere_indices, sphere_index_count, GL_STATIC_DRAW);

    sphere_vao.unbind();
    sphere_vb.unbind();
    sphere_ib.unbind();

    /* shaders */
    Shader default_shader("assets/shaders/defaultVertex.shader", "assets/shaders/defaultFragment.shader");
    /* Shader textured_shader("assets/shaders/texturedVertex.shader", "assets/shaders/texturedFragment.shader"); */
    Shader unlit_shader("assets/shaders/unlitVertex.shader", "assets/shaders/unlitFragment.shader");

    // TODO: check invalid location

    /* textures */
    Texture container_diffuseMap("assets/textures/container_diffuse.png");
    Texture container_specularMap("assets/textures/container_specular.png");

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
        glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)4/3, 0.1f, 100.0f); 
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

        /* model = glm::rotate(model, (float)glfwGetTime(), glm::vec3(1.0f, 1.0f, 0.0f)); */
        default_shader.setUniformMat4f("u_MVP.view", view);
        default_shader.setUniformMat4f("u_MVP.projection", projection);

        glm::mat4 model;
        for (int i = 0; i < sizeof(crate_positions)/sizeof(glm::vec3); i++) {
            model = glm::translate(glm::mat4(1.0), crate_positions[i]);
            default_shader.setUniformMat4f("u_MVP.model", model);
            renderer.draw(cube_vao, cube_ib, default_shader, 12);
        }

        unlit_shader.bind();
        unlit_shader.setUniform3f("u_ModelColor", glm::vec3(1.0f, 1.0f, 1.0f));

        unlit_shader.setUniformMat4f("u_MVP.view", view);
        unlit_shader.setUniformMat4f("u_MVP.projection", projection);
        unlit_shader.setUniformMat4f("u_MVP.model", glm::scale(glm::mat4(1.0), glm::vec3(3.0f, 3.0f, 3.0f)));

        renderer.draw(sphere_vao, sphere_ib, unlit_shader, sphere_triangle_count);
        /* renderer.draw(cube_vao, cube_ib, unlit_shader, 12); */

        /* unlit_shader.bind(); */
        /* unlit_shader.setUniform3f("u_ModelColor", main_light.getColor()); */

        /* model = glm::mat4(1.0f); */
        /* model = glm::translate(model, main_light.getPosition()); */
        /* unlit_shader.setUniformMat4f("u_MVP.model", model); */
        /* unlit_shader.setUniformMat4f("u_MVP.view", view); */
        /* unlit_shader.setUniformMat4f("u_MVP.projection", projection); */
        
        /* renderer.draw(cube_vao, cube_ib, unlit_shader, 12); */

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

