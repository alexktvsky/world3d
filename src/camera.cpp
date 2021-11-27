#include <glm/gtc/type_ptr.hpp>

#include "camera.h"


void Camera::applyTransform(void) {

    glm::vec3 flipped(-m_forward[0], -m_forward[1], -m_forward[2]);

    // Derive X vector
    glm::vec3 axis_x = glm::cross(flipped, m_up);

    glm::mat4x4 matrix;

    // Populate matrix, note this is just the rotation and is transposed
    matrix[0][0] = axis_x[0];
    matrix[1][0] = axis_x[1];
    matrix[2][0] = axis_x[2];
    matrix[3][0] = 0.0;
    
    matrix[0][1] = m_up[0];
    matrix[1][1] = m_up[1];
    matrix[2][1] = m_up[2];
    matrix[3][1] = 0.0;
    
    matrix[0][2] = flipped[0];
    matrix[1][2] = flipped[1];
    matrix[2][2] = flipped[2];
    matrix[3][2] = 0.0;
    
    matrix[0][3] = 0.0;
    matrix[1][3] = 0.0;
    matrix[2][3] = 0.0;
    matrix[3][3] = 1.0;

    // Do the rotation first
    glMultMatrixf(glm::value_ptr(matrix));

    glTranslatef(-m_position[0], -m_position[1], -m_position[2]);
}
