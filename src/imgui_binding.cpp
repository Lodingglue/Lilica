#include "imgui_binding.h"
#include <imgui.h>
#include <string>
#include <vector>

static int lua_imgui_begin(lua_State* L) {
    const char* name = luaL_checkstring(L, 1);
    ImGui::Begin(name);
    return 0;
}

static int lua_imgui_end(lua_State* L) {
    ImGui::End();
    return 0;
}

static int lua_imgui_text(lua_State* L) {
    const char* text = luaL_checkstring(L, 1);
    ImGui::Text("%s", text);
    return 0;
}

static int lua_imgui_button(lua_State* L) {
    const char* label = luaL_checkstring(L, 1);
    bool clicked = ImGui::Button(label);
    lua_pushboolean(L, clicked);
    return 1;
}

static int lua_imgui_slider_float(lua_State* L) {
    const char* label = luaL_checkstring(L, 1);
    float value = (float)luaL_checknumber(L, 2);
    float min = (float)luaL_checknumber(L, 3);
    float max = (float)luaL_checknumber(L, 4);
    bool changed = ImGui::SliderFloat(label, &value, min, max);
    lua_pushboolean(L, changed);
    lua_pushnumber(L, value);
    return 2;
}

static int lua_imgui_checkbox(lua_State* L) {
    const char* label = luaL_checkstring(L, 1);
    bool value = lua_toboolean(L, 2);
    bool changed = ImGui::Checkbox(label, &value);
    lua_pushboolean(L, changed);
    lua_pushboolean(L, value);
    return 2;
}

static int lua_imgui_input_text(lua_State* L) {
    const char* label = luaL_checkstring(L, 1);
    const char* value = luaL_checkstring(L, 2);
    char buffer[256];
    strncpy(buffer, value, sizeof(buffer));
    bool changed = ImGui::InputText(label, buffer, sizeof(buffer));
    lua_pushboolean(L, changed);
    lua_pushstring(L, buffer);
    return 2;
}

static int lua_imgui_input_int(lua_State* L) {
    const char* label = luaL_checkstring(L, 1);
    int value = (int)luaL_checkinteger(L, 2);
    bool changed = ImGui::InputInt(label, &value);
    lua_pushboolean(L, changed);
    lua_pushinteger(L, value);
    return 2;
}

static int lua_imgui_combo(lua_State* L) {
    const char* label = luaL_checkstring(L, 1);
    int current_item = (int)luaL_checkinteger(L, 2);
    luaL_checktype(L, 3, LUA_TTABLE);
    std::vector<std::string> items;
    lua_pushnil(L);
    while (lua_next(L, 3)) {
        items.push_back(luaL_checkstring(L, -1));
        lua_pop(L, 1);
    }
    std::vector<const char*> c_items;
    for (const auto& item : items) c_items.push_back(item.c_str());
    bool changed = ImGui::Combo(label, &current_item, c_items.data(), (int)c_items.size());
    lua_pushboolean(L, changed);
    lua_pushinteger(L, current_item);
    return 2;
}

static int lua_imgui_list_box(lua_State* L) {
    const char* label = luaL_checkstring(L, 1);
    int current_item = (int)luaL_checkinteger(L, 2);
    luaL_checktype(L, 3, LUA_TTABLE);
    std::vector<std::string> items;
    lua_pushnil(L);
    while (lua_next(L, 3)) {
        items.push_back(luaL_checkstring(L, -1));
        lua_pop(L, 1);
    }
    std::vector<const char*> c_items;
    for (const auto& item : items) c_items.push_back(item.c_str());
    bool changed = ImGui::ListBox(label, &current_item, c_items.data(), (int)c_items.size());
    lua_pushboolean(L, changed);
    lua_pushinteger(L, current_item);
    return 2;
}

static int lua_imgui_color_edit3(lua_State* L) {
    const char* label = luaL_checkstring(L, 1);
    float color[3] = {
        (float)luaL_checknumber(L, 2),
        (float)luaL_checknumber(L, 3),
        (float)luaL_checknumber(L, 4)
    };
    bool changed = ImGui::ColorEdit3(label, color);
    lua_pushboolean(L, changed);
    lua_pushnumber(L, color[0]);
    lua_pushnumber(L, color[1]);
    lua_pushnumber(L, color[2]);
    return 4;
}

static int lua_imgui_progress_bar(lua_State* L) {
    float fraction = (float)luaL_checknumber(L, 1);
    ImGui::ProgressBar(fraction);
    return 0;
}

static int lua_imgui_tree_node(lua_State* L) {
    const char* label = luaL_checkstring(L, 1);
    bool open = ImGui::TreeNode(label);
    lua_pushboolean(L, open);
    return 1;
}

static int lua_imgui_tree_pop(lua_State* L) {
    ImGui::TreePop();
    return 0;
}

static int lua_imgui_separator(lua_State* L) {
    ImGui::Separator();
    return 0;
}

static int lua_imgui_begin_menu_bar(lua_State* L) {
    bool open = ImGui::BeginMenuBar();
    lua_pushboolean(L, open);
    return 1;
}

static int lua_imgui_end_menu_bar(lua_State* L) {
    ImGui::EndMenuBar();
    return 0;
}

static int lua_imgui_begin_menu(lua_State* L) {
    const char* label = luaL_checkstring(L, 1);
    bool open = ImGui::BeginMenu(label);
    lua_pushboolean(L, open);
    return 1;
}

static int lua_imgui_end_menu(lua_State* L) {
    ImGui::EndMenu();
    return 0;
}

static int lua_imgui_menu_item(lua_State* L) {
    const char* label = luaL_checkstring(L, 1);
    bool selected = ImGui::MenuItem(label);
    lua_pushboolean(L, selected);
    return 1;
}

static int lua_imgui_begin_child(lua_State* L) {
    const char* str_id = luaL_checkstring(L, 1);
    float width = (float)luaL_optnumber(L, 2, 0);
    float height = (float)luaL_optnumber(L, 3, 0);
    ImGui::BeginChild(str_id, ImVec2(width, height));
    return 0;
}

static int lua_imgui_end_child(lua_State* L) {
    ImGui::EndChild();
    return 0;
}

static int lua_imgui_same_line(lua_State* L) {
    ImGui::SameLine();
    return 0;
}

void registerImGuiBindings(lua_State* L) {
    lua_newtable(L);
    lua_pushcfunction(L, lua_imgui_begin); lua_setfield(L, -2, "Begin");
    lua_pushcfunction(L, lua_imgui_end); lua_setfield(L, -2, "End");
    lua_pushcfunction(L, lua_imgui_text); lua_setfield(L, -2, "Text");
    lua_pushcfunction(L, lua_imgui_button); lua_setfield(L, -2, "Button");
    lua_pushcfunction(L, lua_imgui_slider_float); lua_setfield(L, -2, "SliderFloat");
    lua_pushcfunction(L, lua_imgui_checkbox); lua_setfield(L, -2, "Checkbox");
    lua_pushcfunction(L, lua_imgui_input_text); lua_setfield(L, -2, "InputText");
    lua_pushcfunction(L, lua_imgui_input_int); lua_setfield(L, -2, "InputInt");
    lua_pushcfunction(L, lua_imgui_combo); lua_setfield(L, -2, "Combo");
    lua_pushcfunction(L, lua_imgui_list_box); lua_setfield(L, -2, "ListBox");
    lua_pushcfunction(L, lua_imgui_color_edit3); lua_setfield(L, -2, "ColorEdit3");
    lua_pushcfunction(L, lua_imgui_progress_bar); lua_setfield(L, -2, "ProgressBar");
    lua_pushcfunction(L, lua_imgui_tree_node); lua_setfield(L, -2, "TreeNode");
    lua_pushcfunction(L, lua_imgui_tree_pop); lua_setfield(L, -2, "TreePop");
    lua_pushcfunction(L, lua_imgui_separator); lua_setfield(L, -2, "Separator");
    lua_pushcfunction(L, lua_imgui_begin_menu_bar); lua_setfield(L, -2, "BeginMenuBar");
    lua_pushcfunction(L, lua_imgui_end_menu_bar); lua_setfield(L, -2, "EndMenuBar");
    lua_pushcfunction(L, lua_imgui_begin_menu); lua_setfield(L, -2, "BeginMenu");
    lua_pushcfunction(L, lua_imgui_end_menu); lua_setfield(L, -2, "EndMenu");
    lua_pushcfunction(L, lua_imgui_menu_item); lua_setfield(L, -2, "MenuItem");
    lua_pushcfunction(L, lua_imgui_begin_child); lua_setfield(L, -2, "BeginChild");
    lua_pushcfunction(L, lua_imgui_end_child); lua_setfield(L, -2, "EndChild");
    lua_pushcfunction(L, lua_imgui_same_line); lua_setfield(L, -2, "SameLine");
    lua_setglobal(L, "imgui");
}