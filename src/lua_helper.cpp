#include "lua_helper.h"
#include <iostream>

LuaHelper::LuaHelper() {
    L = luaL_newstate();
    luaL_openlibs(L);
    last_error = "";
    current_script = "script.lua"; // Default script
}

LuaHelper::~LuaHelper() {
    lua_close(L);
}

bool LuaHelper::loadScript(const std::string& filename) const {
    int status = luaL_dofile(L, filename.c_str());
    checkError(status, "loading " + filename);
    if (status == LUA_OK) {
        current_script = filename; // Update current script path
    }
    return status == LUA_OK;
}

bool LuaHelper::callFunction(const std::string& func_name, int num_args, int num_results) const {
    lua_getglobal(L, func_name.c_str());
    if (!lua_isfunction(L, -1)) {
        last_error = "Function " + func_name + " not found in " + current_script;
        lua_pop(L, 1);
        return false;
    }
    int status = lua_pcall(L, num_args, num_results, 0);
    checkError(status, "calling " + func_name);
    return status == LUA_OK;
}

void LuaHelper::checkError(int status, const std::string& context) const {
    if (status != LUA_OK) {
        last_error = "Lua error in " + context + ": " + lua_tostring(L, -1);
        std::cerr << last_error << std::endl;
        lua_pop(L, 1);
    } else {
        last_error = "";
    }
}