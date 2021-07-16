
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "headers/camera.h"

Camera::Camera(glm::vec3 init_position, float move_speed)
    : position(init_position), move_speed(move_speed)
{
}

Camera::~Camera(void)
{
}

glm::mat4
Camera::getViewMatrix(void)
{
    /* return glm::translate(glm::mat4(1.0f), position); */
    const glm::vec3 vec3_forward = glm::vec3(0.0f, 0.0f, 1.0f);
    const glm::vec3 vec3_up = glm::vec3(0.0f, 1.0f, 0.0f);
    return glm::lookAt(position, position+vec3_forward, vec3_up);
}
