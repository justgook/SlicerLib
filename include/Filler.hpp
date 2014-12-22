#ifndef __Filler_H_
#define __Filler_H_

class Filler {
public:
    Filler(lua_State *L, std::vector<std::string>* sliceLayers) {
//        http://stackoverflow.com/questions/16863540/parse-svg-path-definition-d-in-lua
        layers = {"M 21 31 L 21 21 21 41 41 41"};

    };
    std::vector<std::string>* getLayers() {
        return &layers;
    };

private:
    std::vector<std::string> layers;
};


#endif //__Filler_H_
