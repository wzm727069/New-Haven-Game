#ifndef COMP345_MAPGBLOADER_H
#define COMP345_MAPGBLOADER_H

#include <string>
#include <fstream>
#include "MapGB.h"

using std::string;

class MapGBLoader {
public:
    MapGB* load(int numberOfPlayers);
};

#endif 
