#ifndef __Slicer_H_
#define __Slicer_H_

class Slicer {
public:
    Slicer(lua_State *L, std::string stlFileContents) {
//    http://stackoverflow.com/questions/16863540/parse-svg-path-definition-d-in-lua
        layers = {"M 20 30 L 20 20 20 40 40 40"};

    }

    std::vector<std::string>* getLayers() {
        return &layers;
    };

private:
    std::vector<std::string> layers;
};


#endif //__Slicer_H_
