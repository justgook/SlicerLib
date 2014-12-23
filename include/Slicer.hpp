#ifndef __Slicer_H_
#define __Slicer_H_

#include <lua.hpp>

class Slicer {
public:
    Slicer(lua_State *L, const char *filename) {
        if (luaL_dofile(L, filename)) {
            printf("error 102 - %s\n", lua_tostring(L, -1));
        }
        // !! READ !!
        // http://www.geeks3d.com/glslhacker/reference/scripting_mesh.php

//    http://stackoverflow.com/questions/16863540/parse-svg-path-definition-d-in-lua

    }


    //https://eliasdaler.wordpress.com/2013/10/20/lua_and_cpp_pt2/

    std::string getName() {
        return "Name place holder";
    }

    std::string getDescription() {
        return "Description place holder";
    }

    bool validateLuaFile(){
        return true;
    }

    bool validateConfig() {
        return true;
    }

    void setConfigs() {

    }

    void getConfigs() {

    }


    std::vector<std::string> *exec(std::string stlFileContents) {
        return &layers;
    };

private:
    int luaadd(int x, int y) {
        int sum;

        /* the function name */
        lua_getglobal(L, "add");

        /* the first argument */
        lua_pushnumber(L, x);

        /* the second argument */
        lua_pushnumber(L, y);

        /* call the function with 2 arguments, return 1 result */
        lua_call(L, 2, 1);

        /* get the result */
        sum = (int) lua_tointeger(L, -1);
        lua_pop(L, 1);

        return sum;
    }

    std::vector<std::string> layers;
};


#endif //__Slicer_H_
