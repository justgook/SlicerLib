#include <fstream>
#include <iomanip>


#include <tclap/CmdLine.h>
#include <Exception.hpp>

//using namespace std;



//http://gamedevgeek.com/tutorials/calling-lua-functions/
/* the Lua interpreter */

//#define concat(first, second) first second

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
            throw(Exception(101, "STL file not found"));
        }

        std::string sltContents((std::istreambuf_iterator<char>(inputStlFile)), std::istreambuf_iterator<char>());
        slicer = new Slicer(slicerFileLua.getValue().c_str());
        std::vector<std::string> path = slicer->exec(sltContents.c_str());

        // Getting all data and push to files
        if (middleFiles.getValue()) {
            std::cout << "================================================================================" << std::endl;
            int index = 0;
            for (std::vector<std::string>::const_iterator i = path.begin(); i != path.end(); ++i) {
                std::ofstream myfile;
                std::string filename = "example";
                filename += std::to_string(index);
                filename += ".svg";
                myfile.open(filename);
                myfile << "<?xml version=\"1.0\" standalone=\"no\"?>" << std::endl
                        << "<!DOCTYPE svg PUBLIC \"-//W3C//DTD SVG 1.1//EN\" \"http://www.w3.org/Graphics/SVG/1.1/DTD/svg11.dtd\">" << std::endl
                        << "<svg width=\"4cm\" height=\"4cm\" viewBox=\"0 0 400 400\" xmlns=\"http://www.w3.org/2000/svg\" version=\"1.1\">" << std::endl
                        << "<title>Example triangle01- simple example of a path</title>" << std::endl
                        << "<desc>A path that draws a triangle</desc>" << std::endl
                        << "<rect x=\"1\" y=\"1\" width=\"398\" height=\"398\" fill=\"none\" stroke=\"blue\" />" << std::endl
                        << "<path d=\"" << *i << "\" fill=\"red\" stroke=\"blue\" stroke-width=\"3\" />" << std::endl
                        << "</svg>" << std::endl;
                myfile.close();
                index++;
            }
            std::cout << "================================================================================" << std::endl;
        }


    }
    catch (TCLAP::ArgException &e)  // catch any exceptions
    {
        std::cerr << "error: " << e.error() << " " << e.argId() << " " << std::endl;

    }
    catch (const Exception &e) {
        std::cerr << "SlicerLib Exeptions ( " << e.code() << " - " << e.error() << ")" << std::endl;

    }

    return 0;
}