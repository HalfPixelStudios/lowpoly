
#ifndef __CAMERA_H__
#define __CAMERA_H__

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

class Camera
{
private:
    glm::vec3 position;
    float move_speed;
public:
    Camera(glm::vec3 init_position, float move_speed);
    ~Camera(void);
    glm::mat4 getViewMatrix(void);
};



#endif // __CAMERA_H__
