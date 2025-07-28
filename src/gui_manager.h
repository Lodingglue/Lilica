#ifndef GUI_MANAGER_H
#define GUI_MANAGER_H

#include <GLFW/glfw3.h>
#include "lua_helper.h"

class GuiManager {
public:
    GuiManager();
    ~GuiManager();
    bool initialize(int width, int height, const char* title);
    void render(const LuaHelper& lua_helper);
    bool shouldClose() const;
    void shutdown();

private:
    GLFWwindow* window;
    char script_path[256];
    void renderDebugWindow(const LuaHelper& lua_helper);
};

#endif // GUI_MANAGER_H