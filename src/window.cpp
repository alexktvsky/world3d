#include <GL/freeglut.h>

extern "C" {
#include <unistd.h>
}

#include "window.h"


Window *Window::m_window;
Scene *Window::m_scene;

Window::Window(const std::string &name, int width, int height)
    : m_name(name)
    , m_width(width)
    , m_height(height) {}

void Window::show() {

    m_window = this;

    initSystem();

    glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB|GLUT_DEPTH);
    glutInitWindowSize(m_width, m_height);
    m_id = glutCreateWindow(m_name.c_str());
    glutDisplayFunc(render);
    glutReshapeFunc(changeSize);
    glutSpecialFunc(specKeyHandler);
    glutKeyboardFunc(keyboardHandler);
    glutTimerFunc(33, timerHandler, 1);

    glutSetCursor(GLUT_CURSOR_NONE);
    glutMotionFunc(motionHandler);
    glutPassiveMotionFunc(motionPassiveHandler);
    // glutMouseFunc();
}

void Window::close(void) {
    glutDestroyWindow(m_id);
}

void Window::initSystem(void) {

    static bool inited = false;

    if (inited) {
        return;
    }

    static int dummy_argc = 1;
    static const char *dummy_argv = "a.out";

    glutInit(&dummy_argc, const_cast<char**>(&dummy_argv));

    inited = true;
}

void Window::changeSize(int width, int height) {
    m_scene->changeSize(width, height);
}

void Window::render(void) {
    m_scene->render();
    int x = glutGet(GLUT_WINDOW_WIDTH) / 2;
    int y = glutGet(GLUT_WINDOW_HEIGHT) / 2;
    if (m_window->m_do_capture_cursor) {
        glutWarpPointer(x, y);
        glutSetCursor(GLUT_CURSOR_NONE);
    }
    else {
        glutSetCursor(GLUT_CURSOR_INHERIT);
    }
    glutSwapBuffers();
}

void Window::specKeyHandler(int key, int x, int y) {

    switch (key) {
    case GLUT_KEY_UP:
        key = 0;
        break;
    case GLUT_KEY_DOWN:
        key = 1;
        break;
    case GLUT_KEY_LEFT:
        key = 2;
        break;
    case GLUT_KEY_RIGHT:
        key = 3;
        break;
    case 114: // LEFT CTRL
        if (m_window->m_do_capture_cursor) {
            m_window->m_do_capture_cursor = false;
        }
        else {
            m_window->m_do_capture_cursor = true;
        }
    }
    m_scene->specKeyHandler(key, x, y);
}

void Window::keyboardHandler(uint8_t key, int x, int y) {
    switch (key) {
    case 27: // ESC KEY
        // glutLeaveMainLoop();
        exit(0);
    }
    m_scene->keyboardHandler(key, x, y);
}

void Window::timerHandler(int value) {
    (void) value;
    glutPostRedisplay();
    glutTimerFunc(3, timerHandler, 1);
}

void Window::motionHandler(int x, int y) {
    if (m_window->m_do_capture_cursor) {
        m_scene->motionHandler(x, y);
    }
}

void Window::motionPassiveHandler(int x, int y) {
    if (m_window->m_do_capture_cursor) {
        m_scene->motionPassiveHandler(x, y);
    }
}

void Window::assignScene(Scene *m_scene) {
    this->m_scene = m_scene;
}

void Window::loop(void) {
    glutMainLoop();
}
