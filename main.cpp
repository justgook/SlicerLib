#include <fstream>
#include <iomanip>


#include <lua.hpp>
#include <tclap/CmdLine.h>

//using namespace std;



//http://gamedevgeek.com/tutorials/calling-lua-functions/
/* the Lua interpreter */
lua_State *L;

#define concat(first, second) first second

//http://luapower.com/

#include "Slicer.hpp"
#include "Filler.hpp"


Slicer *slicer;
Filler *filler;

int main(int argc, const char *const *argv) {


    try {

        TCLAP::CmdLine cmd("Command description message", ' ', "0.9");

        TCLAP::MultiArg<std::string> preProcessFileLua("a", "preporcesor-file", "Pre-porcesor script file", false, "preporcess.lua");
        TCLAP::ValueArg<std::string> slicerFileLua("s", "slicer-file", "Slicing script file", true, "", "slice.lua");
        TCLAP::ValueArg<std::string> fillerFileLua("f", "filler-file", "Filling script file", false, "", "fille.lua");
        TCLAP::ValueArg<std::string> supporterFileLua("p", "supporter-file", "Support script file", false, "", "support.lua");
        TCLAP::ValueArg<std::string> exporterFileLua("e", "exporter-file", "Export script file", false, "", "export.lua");
        TCLAP::ValueArg<std::string> output("o", "output",
                "Write out all compiled files into the specified directory."
                        "default build folder relative (to project root) or absolute path", false, "", "DIR");
        TCLAP::UnlabeledValueArg<std::string> stlFileName("inputfile", "STL file that will be sliced", true, "3.14", "model.stl");
        TCLAP::SwitchArg middleFiles("v", "verbose", "Output all debug info / middle-build files ");

        cmd.add(middleFiles);
        cmd.add(slicerFileLua);
        cmd.add(preProcessFileLua);
        cmd.add(fillerFileLua);
        cmd.add(supporterFileLua);
        cmd.add(exporterFileLua);
        cmd.add(output);
        cmd.add(stlFileName);
        cmd.parse(argc, argv);

        std::cout << "STL: " << stlFileName.getValue() << std::endl;
        std::cout << "Slicer: " << slicerFileLua.getValue() << std::endl;

        std::ifstream inputStlFile(stlFileName.getValue());
        if (!inputStlFile.good()) {
            throw(TCLAP::ArgException("101 - STL file not found"));
        }


        L = luaL_newstate();
        luaL_openlibs(L);


        std::string sltContents((std::istreambuf_iterator<char>(inputStlFile)), std::istreambuf_iterator<char>());
        slicer = new Slicer(L, slicerFileLua.getValue().c_str());
        slicer->exec(sltContents);


    } catch (TCLAP::ArgException &e)  // catch any exceptions
    {
        std::cerr << "error: " << e.error() << " " << e.argId() << " " << std::endl;
    }

    lua_close(L);

    return 0;
}