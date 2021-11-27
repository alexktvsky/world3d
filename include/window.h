#ifndef WINDOW_H
#define WINDOW_H

#include <string>

#include "scene.h"

class Window {
public:
    Window(const std::string &name, int width, int height);
    void show(void);
    void close(void);
    void assignScene(Scene *scene);
    static void changeSize(int width, int height);
    static void render(void);
    static void specKeyHandler(int key, int x, int y);
    static void keyboardHandler(uint8_t key, int x, int y);
    static void timerHandler(int value);
    static void motionHandler(int x, int y);
    static void motionPassiveHandler(int x, int y);
    static void loop(void);
private:
    static void initSystem(void);
    std::string m_name;
    int m_width;
    int m_height;
    int m_id;
    static Window *m_window;
    static Scene *m_scene;
    bool m_do_capture_cursor = true;
}; // End of class

#endif // WINDOW_H
