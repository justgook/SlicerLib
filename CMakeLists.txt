cmake_minimum_required(VERSION 2.8.4)


set(MY_APP_NAME "SlicerLib")




# project version http://semver.org/
SET( PROJECT_MAJOR_VERSION 5 )
SET( PROJECT_MINOR_VERSION 00 )
SET( PROJECT_PATCH_LEVEL 00 )
project(${MY_APP_NAME})


##CHANGE ME TO SOMETHING REAL FOR PRODUCTION!
add_definitions(-DSCRIPT_FOLDER="${CMAKE_CURRENT_SOURCE_DIR}/test/lua")


include_directories("${CMAKE_CURRENT_SOURCE_DIR}/vendor")



set (LUA_INCLUDE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/vendor/lua-5.3.0-beta/src")

include_directories(${LUA_INCLUDE_DIRS})

set (LUA_CORE_SRCS
  ${LUA_INCLUDE_DIRS}/lapi.c
  ${LUA_INCLUDE_DIRS}/lcode.c
  ${LUA_INCLUDE_DIRS}/lctype.c
  ${LUA_INCLUDE_DIRS}/ldebug.c
  ${LUA_INCLUDE_DIRS}/ldo.c
  ${LUA_INCLUDE_DIRS}/ldump.c
  ${LUA_INCLUDE_DIRS}/lfunc.c
  ${LUA_INCLUDE_DIRS}/lgc.c
  ${LUA_INCLUDE_DIRS}/llex.c
  ${LUA_INCLUDE_DIRS}/lmem.c
  ${LUA_INCLUDE_DIRS}/lobject.c
  ${LUA_INCLUDE_DIRS}/lopcodes.c
  ${LUA_INCLUDE_DIRS}/lparser.c
  ${LUA_INCLUDE_DIRS}/lstate.c
  ${LUA_INCLUDE_DIRS}/lstring.c
  ${LUA_INCLUDE_DIRS}/ltable.c
  ${LUA_INCLUDE_DIRS}/ltm.c
  ${LUA_INCLUDE_DIRS}/lundump.c
  ${LUA_INCLUDE_DIRS}/lvm.c
  ${LUA_INCLUDE_DIRS}/lzio.c
  ${LUA_INCLUDE_DIRS}/lauxlib.c
  ${LUA_INCLUDE_DIRS}/lbaselib.c
  ${LUA_INCLUDE_DIRS}/lbitlib.c
  ${LUA_INCLUDE_DIRS}/lcorolib.c
  ${LUA_INCLUDE_DIRS}/ldblib.c
  ${LUA_INCLUDE_DIRS}/liolib.c
  ${LUA_INCLUDE_DIRS}/lmathlib.c
  ${LUA_INCLUDE_DIRS}/loslib.c
  ${LUA_INCLUDE_DIRS}/lstrlib.c
  ${LUA_INCLUDE_DIRS}/ltablib.c
  ${LUA_INCLUDE_DIRS}/lutf8lib.c
  ${LUA_INCLUDE_DIRS}/loadlib.c
  ${LUA_INCLUDE_DIRS}/linit.c
     )

add_library (lua ${LUA_CORE_SRCS})



set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp)
add_executable(${MY_APP_NAME} ${SOURCE_FILES})

target_link_libraries(${MY_APP_NAME} lua)



set_target_properties(${MY_APP_NAME}
    PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    #output result to bin folder - for easear use whe testing plugins, and project data
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin"
    #COMPILE_FLAGS ${EXTRA_FLAGS}
)