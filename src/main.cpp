#include <cstdio>
#include <cstdint>
#include <cstddef>

#ifdef _WIN32
#include <windows.h>
#endif

#include "window.h"
#include "scene.h"


int main(void) {

    Window window("world3d", 800, 600);
    Scene scene1;

    window.assignScene(&scene1);

#ifdef _WIN32
    HWND hw = GetConsoleWindow();
    ShowWindow(hw, SW_HIDE);
#endif

    window.show();
    Window::loop();

    return 0;
}
