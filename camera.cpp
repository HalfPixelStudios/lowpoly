
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "headers/camera.h"

Camera::Camera(float move_speed)
    : position(glm::vec3(0.0f, 0.0f, 0.0f)), cam_forward(glm::vec3(0.0f, 0.0f, 1.0f)), move_speed(move_speed)
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

    if (glfwGetKey(win, GLFW_KEY_W) == GLFW_PRESS)
        position += move_speed * cam_forward;
    if (glfwGetKey(win, GLFW_KEY_S) == GLFW_PRESS)
        position -= move_speed * cam_forward;
    if (glfwGetKey(win, GLFW_KEY_D) == GLFW_PRESS)
        position += move_speed * cam_right;
    if (glfwGetKey(win, GLFW_KEY_A) == GLFW_PRESS)
        position -= move_speed * cam_right;

}

glm::mat4
Camera::getViewMatrix(void)
{
    return glm::lookAt(
        position,
        position+cam_forward,
        glm::vec3(0.0f, 1.0f, 0.0f)
    );
}
