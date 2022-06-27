#ifndef TRANSFORM_H
#define TRANSFORM_H

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

// Transform Class
class Transform
{
public:
    glm::vec3 position; // Position of the Actor
    glm::vec3 rotation; // Rotation of the Actor
    glm::vec3 scale;    // Scale of the Actor
    // Standard Constructor for the Transform Class. Sets position at origin
    Transform();
    // Constructor for the Transform Class. Sets the position/rotation/scale at initialisation
    Transform(glm::vec3 pos, glm::vec3 rot, glm::vec3 scl);
    // Resets the transform the object and sets position at origin
    void reset_to_origin();

private:
};

#endif // !TRANSFORM_H
