#include "MapVGLoader.h"
#include "MapVG.h"
#include <iostream>

using std::ifstream;
using std::istringstream;
using std::cout;
using std::endl;

MapVG* MapVGLoader::load(string villageName) {
    ifstream myFile("./MapVGLoad.txt");
    string mystring, data, nodeNumber;
    MapVG *vgMap = new MapVG(villageName);
    if(!myFile.is_open()){
        perror("Error opening");
        exit(EXIT_FAILURE);
    }
    else {
        while (getline(myFile, mystring)) {
            if(mystring.size() > 6){
                perror("Incorrect format, map can't load");
                exit(EXIT_FAILURE);
            }
            istringstream var(mystring);
            var >> nodeNumber >> data;
            vgMap->setTileData(nodeNumber, stod(data));
        }
        myFile.close();
    }
    return vgMap;
}
