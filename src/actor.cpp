#include <glm/gtx/rotate_vector.hpp>

#include "actor.h"


Actor::Actor(void)
    : m_position(0.0, 0.0, 0.0)
    , m_up(0.0, 1.0, 0.0)
    , m_forward(0.0, 0.0, -1.0) {}

Actor::Actor(const glm::vec3 &vec)
    : m_position(vec)
    , m_up(0.0, 1.0, 0.0)
    , m_forward(0.0, 0.0, -1.0) {}

void Actor::forward(GLfloat step) {
    m_position += m_forward * step;
}

void Actor::back(GLfloat step) {
    m_position -= m_forward * step;
}

void Actor::left(GLfloat step) {
    glm::vec3 temp = glm::cross(m_up, m_forward);
    m_position -= temp * step;
}

void Actor::right(GLfloat step) {
    glm::vec3 temp = glm::cross(m_up, m_forward);
    m_position += temp * step;
}

void Actor::rotateX(GLfloat angle) {
    justRotateX(angle);
    m_saved_x_angle += angle;
}

void Actor::justRotateX(GLfloat angle) {
    glm::vec3 cross = glm::cross(m_forward, m_up);
    m_up = glm::rotate(m_up, angle, cross);
}

void Actor::rotateY(GLfloat angle) {
    m_up = {0.0, 1.0, 0.0};
    m_forward = glm::rotate(m_forward, angle, m_up);
    justRotateX(m_saved_x_angle);
}
