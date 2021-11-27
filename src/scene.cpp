#include "scene.h"


Scene::Scene(void) {
}

void Scene::drawGround(void) {

    GLfloat f_extent = 20.0;
    GLfloat f_step = 1.0;
    GLfloat y = -0.4;
    
    glBegin(GL_LINES);
    for (GLfloat i = -f_extent; i <= f_extent; i += f_step) {
        glVertex3f(i, y, f_extent);
        glVertex3f(i, y, -f_extent);

        glVertex3f(f_extent, y, i);
        glVertex3f(-f_extent, y, i);
    }
    glEnd();
}

void Scene::changeSize(int w, int h) {
    // Prevent a divide by zero, when window is too short
    if (h == 0) {
        h = 1;
    }

    glViewport(0, 0, w, h);

    // Reset the coordinate system before modifying
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    GLfloat aspect = static_cast<GLfloat>(w) / static_cast<GLfloat>(h);
    // Set the clipping volume
    gluPerspective(35.0, aspect, 1.0, 50.0);
        
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    m_x_center = w / 2;
    m_y_center = h / 2;
}

void Scene::render(void) {
    // Set color of clear
    glClearColor(0.0, 0.0, 1.0, 1.0);

    // Draw everything as wire frame
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    // Clear the window with current clearing color
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);


    glPushMatrix();

        m_camera.applyTransform();
        drawGround();

        glPopMatrix();

    glPopMatrix();

}

void Scene::specKeyHandler(int key, int x, int y) {

    (void) x;
    (void) y;

    switch (key) {
    case 0: // KEY_UP
        m_camera.rotateX(0.01);
        break;
    case 1: // KEY_DOWN
        m_camera.rotateX(-0.01);
        break;
    case 2: // KEY_LEFT
        m_camera.rotateY(-0.1);
        break;
    case 3: // KEY_RIGHT
        m_camera.rotateY(0.1);
        break;
    }
}

void Scene::keyboardHandler(uint8_t key, int x, int y) {

    (void) x;
    (void) y;

    switch (key) {
    case 'w':
        m_camera.forward(0.1);
        break;
    case 's':
        m_camera.back(0.1);
        break;
    case 'a':
        m_camera.left(0.1);
        break;
    case 'd':
        m_camera.right(0.1);
        break;
    }
}

void Scene::motionHandler(int x, int y) {
    (void) x;
    (void) y;
}

void Scene::motionPassiveHandler(int x, int y) {

    static const float multi_x = 0.0005;
    static const float multi_y = 0.00005;

    float x_delta = static_cast<float>(x - m_x_center);
    float y_delta = static_cast<float>(m_y_center - y);

    m_camera.rotateX(multi_y * y_delta);
    m_camera.rotateY(multi_x * x_delta);
}
