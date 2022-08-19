#ifndef COMP345_MAPVGLOADER_H
#define COMP345_MAPVGLOADER_H

#include "MapVG.h"
#include <iostream>
#include <fstream>
#include <sstream>

using std::string;

class MapVGLoader {

public:
    MapVG* load(string villageName);
};

#endif
