#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "headers/camera.h"

Camera::Camera(float move_speed, float sensitivity)
    : position(glm::vec3(0.0f, 0.0f, 0.0f)),
      rotation(glm::vec3(0.0f, 90.0f, 0.0f)),
      cam_forward(glm::vec3(0.0f, 0.0f, 0.0f)),
      prev_mouse(glm::vec2(0.0f, 0.0f)),
      move_speed(move_speed),
      sensitivity(sensitivity)
{
}

Camera::~Camera(void)
{
}

void
Camera::processInput(GLFWwindow* win)
{

    /* careful, there will be issues if camera is facing straight up */
    glm::vec3 cam_right = glm::normalize(glm::cross(cam_forward, glm::vec3(0.0f, 1.0f, 0.0f)));

    /* process keyboard */
    if (glfwGetKey(win, GLFW_KEY_W) == GLFW_PRESS)
        position += move_speed * cam_forward;
    if (glfwGetKey(win, GLFW_KEY_S) == GLFW_PRESS)
        position -= move_speed * cam_forward;
    if (glfwGetKey(win, GLFW_KEY_D) == GLFW_PRESS)
        position += move_speed * cam_right;
    if (glfwGetKey(win, GLFW_KEY_A) == GLFW_PRESS)
        position -= move_speed * cam_right;

    double mouse_x, mouse_y;
    glfwGetCursorPos(win, &mouse_x, &mouse_y);

    float x_offset = (mouse_x-prev_mouse.x)*sensitivity;
    float y_offset = (mouse_y-prev_mouse.y)*sensitivity;

    rotation.x = glm::clamp(rotation.x-y_offset, -89.0f, 89.0f); // pitch
    rotation.y += x_offset; // yaw

    prev_mouse = glm::vec2(mouse_x, mouse_y);
}

glm::mat4
Camera::getViewMatrix(void)
{
    /* calculate cam forward */
    cam_forward = glm::normalize(glm::vec3(
        cos(glm::radians(rotation.y)) * cos(glm::radians(rotation.x)),
        sin(glm::radians(rotation.x)),
        sin(glm::radians(rotation.y)) * cos(glm::radians(rotation.x))
    ));

    return glm::lookAt(
        position,
        position+cam_forward,
        glm::vec3(0.0f, 1.0f, 0.0f)
    );
}
