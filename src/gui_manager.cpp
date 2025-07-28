#include "gui_manager.h"
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <iostream>
#include <cstring>


GuiManager::GuiManager() : window(nullptr) {
    std::strncpy(script_path, "script.lua", sizeof(script_path)); // Default script path
}

GuiManager::~GuiManager() {
    shutdown();
}

bool GuiManager::initialize(int width, int height, const char* title) {
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return false;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    window = glfwCreateWindow(width, height, title, nullptr, nullptr);
    if (!window) {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return false;
    }
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 330");
    return true;
}

void GuiManager::render(const LuaHelper& lua_helper) {
    glfwPollEvents();

    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    // Render Lua-defined UI
    lua_helper.callFunction("render_ui");

    // Render debug window
    renderDebugWindow(lua_helper);

    ImGui::Render();
    int display_w, display_h;
    glfwGetFramebufferSize(window, &display_w, &display_h);
    glViewport(0, 0, display_w, display_h);
    glClearColor(0.45f, 0.55f, 0.60f, 1.00f);
    glClear(GL_COLOR_BUFFER_BIT);
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    glfwSwapBuffers(window);
}

void GuiManager::renderDebugWindow(const LuaHelper& lua_helper) {
    ImGui::Begin("Debug Window");
    ImGui::Text("Current Script: %s", lua_helper.getCurrentScript().c_str());
    ImGui::InputText("Script Path", script_path, sizeof(script_path));
    if (ImGui::Button("Load Script")) {
        lua_helper.loadScript(script_path);
    }
    if (ImGui::Button("Reload Current Script")) {
        lua_helper.loadScript(lua_helper.getCurrentScript());
    }
    ImGui::Text("Lua Status: %s", lua_helper.getLastError().empty() ? "OK" : lua_helper.getLastError().c_str());
    ImGui::End();
}

bool GuiManager::shouldClose() const {
    return glfwWindowShouldClose(window);
}

void GuiManager::shutdown() {
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    if (window) {
        glfwDestroyWindow(window);
        window = nullptr;
    }
    glfwTerminate();
}