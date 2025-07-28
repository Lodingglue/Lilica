#ifndef LUA_HELPER_H
#define LUA_HELPER_H

#include <lua.hpp>
#include <string>

class LuaHelper {
public:
    LuaHelper();
    ~LuaHelper();
    lua_State* getState() const { return L; }
    bool loadScript(const std::string& filename) const; // Loads script and updates current_script
    bool callFunction(const std::string& func_name, int num_args = 0, int num_results = 0) const;
    std::string getLastError() const { return last_error; }
    std::string getCurrentScript() const { return current_script; } // Get current script path

private:
    lua_State* L;
    mutable std::string last_error;
    mutable std::string current_script;
    void checkError(int status, const std::string& context) const;
};

#endif // LUA_HELPER_H