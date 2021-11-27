#ifndef ACTOR_H
#define ACTOR_H

#if defined(__APPLE__)
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#else
#include <GL/gl.h>
#include <GL/glu.h>
#endif

#include <glm/glm.hpp>

class Actor {
public:
    Actor(void);
    Actor(const glm::vec3 &vec);
    void forward(GLfloat step);
    void back(GLfloat step);
    void left(GLfloat step);
    void right(GLfloat step);
    void rotateX(GLfloat angle);
    void rotateY(GLfloat angle);
    void rotateZ(GLfloat angle);
    void applyTransform(void);
    float getPositionX(void) const { return m_position[0]; }
    float getPositionY(void) const { return m_position[1]; }
    float getPositionZ(void) const { return m_position[2]; }
protected:
    void justRotateX(GLfloat angle);
    glm::vec3 m_position;
    glm::vec3 m_up;
    glm::vec3 m_forward;
    float m_saved_x_angle;
}; // End of class

#endif // ACTOR_H
