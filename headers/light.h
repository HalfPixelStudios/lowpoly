#ifndef __LIGHT_H__
#define __LIGHT_H__

#include <GLFW/glfw3.h>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

class Light
{
private:
    glm::vec3 position;
    glm::vec3 color;
    float intensity;
public:
    Light(glm::vec3 position, glm::vec3 color, float intensity);
    ~Light();
    inline glm::vec3 getPosition(void) const { return position; }
    inline glm::vec3 getColor(void) const { return color; }
};



#endif // __LIGHT_H__
