#include "MapGBLoader.h"
#include "MapGB.h"
#include <iostream>
#include <sstream>

using std::ifstream;
using std::istringstream;
using std::cout;
using std::endl;
using std::to_string;

MapGB* MapGBLoader::load(int numberOfPlayers) {
    // Selecting the appropriate game map from a list of files as stored in a directory
    ifstream myFile("./game"+to_string(numberOfPlayers)+".txt");
    string mystring, data, nodeNumber;
    MapGB *mapGB = new MapGB(numberOfPlayers);
    if (!myFile.is_open()) {
        perror("Error opening");
        exit(EXIT_FAILURE);
    } else {
        while (getline(myFile, mystring)) {
            if (mystring.size() > 8) {
                perror("Incorrect format, map can't load");
                exit(EXIT_FAILURE);
            }
            istringstream var(mystring);
            var >> nodeNumber >> data; 
            mapGB->setTileData(nodeNumber,stod(data));
        }
        myFile.close();
        return mapGB;
    }
}
