
#ifndef __CAMERA_H__
#define __CAMERA_H__

#include <GLFW/glfw3.h>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

class Camera
{
private:
    glm::vec3 position;
    glm::vec3 cam_forward;
    float move_speed;
public:
    Camera(float move_speed);
    ~Camera(void);
    void processInput(GLFWwindow* win);
    glm::mat4 getViewMatrix(void);
};



#endif // __CAMERA_H__
