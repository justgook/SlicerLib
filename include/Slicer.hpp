#ifndef __Slicer_H_
#define __Slicer_H_

#include <lua.hpp>
#include "Exception.hpp"

class Slicer {
public:
    Slicer(const char *filename) {
        L = luaL_newstate();
        luaL_openlibs(L);

        if (luaL_dofile(L, filename)) {
            throw(Exception(102, lua_tostring(L, -1)));
        }
    }

    ~Slicer() {
        lua_close(L);
    }

    //https://eliasdaler.wordpress.com/2013/10/20/lua_and_cpp_pt2/

    std::string getName() {
        lua_getglobal(L, "name");
        if (lua_isnil(L, -1)) {
            throw(Exception(105, "cant get name or name is nil"));
        }
        std::string name = (std::string) lua_tostring(L, -1);
        clean();
        return name;
    }

    std::string getDescription() {
        lua_getglobal(L, "description");
        if (lua_isnil(L, -1)) {
            throw(Exception(106, "cant get description or description is nil"));
        }
        std::string description = (std::string) lua_tostring(L, -1);
        clean();
        return description;
    }

    std::string getVersion() {
        lua_getglobal(L, "version");
        if (lua_isnil(L, -1)) {
            throw(Exception(107, "cant get version or version is nil"));
        }
        std::string version = (std::string) lua_tostring(L, -1);
        clean();
        return version;
    }

    bool validateLuaFile() {
        return true;
    }

    bool validateConfig() {
        return true;
    }

    void setConfigs() {

    }

    void getConfigs() {

    }

    std::vector<std::string> exec(const char *stlFileContents) {
        std::vector<std::string> layers;
        lua_getglobal(L, "exec");
        if (lua_isnil(L, -1)) {
            throw(Exception(103, "exec function not found"));
        }
        lua_pushstring(L, stlFileContents);
        lua_call(L, 1, 1);

        if (lua_isnil(L, -1)) {
            throw(Exception(104, "exec function return nil"));
        }

        lua_pushnil(L);
        while (lua_next(L, -2)) {
            layers.push_back((std::string) lua_tostring(L, -1));
            lua_pop(L, 1);
        }
        clean();
        return layers;
    };

private:
    lua_State *L;

    void clean() {
        int n = lua_gettop(L);
        lua_pop(L, n);
    }

//    std::vector<std::string> layers;
};


#endif //__Slicer_H_
