#ifndef __Slicer_H_
#define __Slicer_H_

#include <lua.hpp>
#include "Exception.hpp"
#include "Base.hpp"

class Slicer: public Base {
public:
    Slicer(const char *filename): Base(filename, 100) {

    }
    std::vector<std::string> exec(const char * stlFileContents) {
        std::vector<std::string> layers;
        lua_getglobal(L, "exec");
        if (lua_isnil(L, -1)) {
            throw(Exception(100 + 3, "exec function not found"));
        }
        lua_pushstring(L, stlFileContents);
        lua_call(L, 1, 1);

        if (lua_isnil(L, -1)) {
            throw(Exception(100 + 4, "exec function return nil"));
        }

        lua_pushnil(L);
        while (lua_next(L, -2)) {
            layers.push_back((std::string) lua_tostring(L, -1));
            lua_pop(L, 1);
        }
        clean();
        return layers;
    };
};


#endif //__Slicer_H_
