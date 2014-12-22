#include <fstream>
#include <iomanip>


#include <lua.hpp>
#include <tclap/CmdLine.h>

//using namespace std;



//http://gamedevgeek.com/tutorials/calling-lua-functions/
/* the Lua interpreter */
lua_State *L;

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


#define concat(first, second) first second

//http://luapower.com/

#include "Slicer.hpp"
#include "Filler.hpp"


Slicer *slicer;
Filler *filler;

int main() {
    L = luaL_newstate();
    luaL_openlibs(L);

    const char *file = concat(SCRIPT_FOLDER, "/test.lua");

    luaL_dofile(L, file);


    //Just check for file load
    const char *testSTLfile = concat(SCRIPT_FOLDER, "/../stl/effector_e3d.stl");
    std::ifstream inputFile(testSTLfile);
    //TODO ADD CHECK if file exists
    std::string contents((std::istreambuf_iterator<char>(inputFile)), std::istreambuf_iterator<char>());
//    std::cout << contents << std::endl;
    inputFile.close();



    /* Call Slicer and to result */
//    http://www.geeks3d.com/glslhacker/reference/scripting_mesh.php
    slicer = new Slicer(L, contents);

    /* Call Filler and to result */
    filler = new Filler(L, slicer->getLayers());



    /* call the add function */
    int sum = luaadd(350, 15);

    /* print the result */
    printf("The sum is %d\n", sum);

    lua_close(L);

    return 0;
}