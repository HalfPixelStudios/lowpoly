
#ifndef __CAMERA_H__
#define __CAMERA_H__

#include <GLFW/glfw3.h>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

class Camera
{
private:
    glm::vec3 position;
    glm::vec3 rotation; // pitch, yaw, roll (in degrees)
    glm::vec3 cam_forward;
    glm::vec2 prev_mouse;
    float move_speed;
    float sensitivity;
public:
    Camera(float move_speed, float sensitivity);
    ~Camera(void);
    void processInput(GLFWwindow* win);
    glm::mat4 getViewMatrix(void);
};



#endif // __CAMERA_H__
