#include <iostream>

#include <lua.hpp>
#include <tclap/CmdLine.h>

//using namespace std;



//http://gamedevgeek.com/tutorials/calling-lua-functions/
/* the Lua interpreter */
lua_State* L;

int luaadd ( int x, int y )
{
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
    sum = (int)lua_tointeger(L, -1);
    lua_pop(L, 1);

    return sum;
}


#define concat(first, second) first second

int main() {
    L = luaL_newstate();
    luaL_openlibs(L);
    const char* file = concat(SCRIPT_FOLDER, "/test.lua");

    luaL_dofile(L, file);

    /* call the add function */
    int sum = luaadd( 10, 15 );

    /* print the result */
    printf( "The sum is %d\n", sum );

    lua_close(L);

    return 0;
}