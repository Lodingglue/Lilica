#include "gui_manager.h"
#include "lua_helper.h"
#include "imgui_binding.h"



int main() {
    LuaHelper lua_helper;
    registerImGuiBindings(lua_helper.getState());
    if (!lua_helper.loadScript("script.lua")) {
        return -1;
    }

    GuiManager gui_manager;
    if (!gui_manager.initialize(1280, 720, "Lilica - A Lua Wrapped Imgui Controller")) {
        return -1;
    }

    while (!gui_manager.shouldClose()) {
        gui_manager.render(lua_helper);
    }

    gui_manager.shutdown();
    return -1;
}