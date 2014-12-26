#ifndef __Base_H_
#define __Base_H_

#include <lua.hpp>
#include "Exception.hpp"

class Base {

public:
    Base(const char *filename, const int errorBase_):errorBase(errorBase_)  {
        L = luaL_newstate();
        luaL_openlibs(L);

        if (luaL_dofile(L, filename)) {
            throw(Exception(errorBase + 2, lua_tostring(L, -1)));
        }
    }

    ~Base() {
        lua_close(L);
    }

    //https://eliasdaler.wordpress.com/2013/10/20/lua_and_cpp_pt2/

    std::string getName() {
        lua_getglobal(L, "name");
        if (lua_isnil(L, -1)) {
            throw(Exception(errorBase + 5, "cant get name or name is nil"));
        }
        std::string name = (std::string) lua_tostring(L, -1);
        clean();
        return name;
    }

    std::string getDescription() {
        lua_getglobal(L, "description");
        if (lua_isnil(L, -1)) {
            throw(Exception(errorBase + 6, "cant get description or description is nil"));
        }
        std::string description = (std::string) lua_tostring(L, -1);
        clean();
        return description;
    }

    std::string getVersion() {
        lua_getglobal(L, "version");
        if (lua_isnil(L, -1)) {
            throw(Exception(errorBase + 7, "cant get version or version is nil"));
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



protected:
    lua_State *L;

    void clean() {
        int n = lua_gettop(L);
        lua_pop(L, n);
    }
private:
    int errorBase;
};


#endif //__Base_H_
