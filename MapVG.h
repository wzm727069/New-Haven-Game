#ifndef COMP345_MAPVG_H
#define COMP345_MAPVG_H

#include <string>
#include "Graph/Graph.h"
#include <vector>
#include <ostream>

using std::string;
using std::vector;
using std::ostream;

class MapVG{
private:
    string* villageName;
    vector<bool>* resourceFlags;
    int* buildingCount;
public:
    Graph *board;
    MapVG(string name);
    MapVG();
    MapVG(const MapVG &vgMap);
    ~MapVG();

    string getName();
    Graph* getBoard();
    vector<bool>* getFlags();
    double getTileData(string position) const;
    void setTileData(string position, double data);
    string getNorth(string position);
    string getSouth(string position);
    string getEast(string position);
    string getWest(string position);
    int getBuildingCount();
    void incrementBuildingCount();
    vector<string> toStrings();
};
#endif 
