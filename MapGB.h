#ifndef COMP345_MAPGB_H
#define COMP345_MAPGB_H

#include "Graph/Graph.h"
#include <string>
#include <ostream>
#include <vector>

using std::string;
using std::ostream;
using std::vector;

class MapGB{

private:
    Graph *board;
public:
    int playerCount;
    MapGB();
    MapGB(int numOfPlayers);
    MapGB(MapGB &mapGB);
    Graph* getBoard();
    double getTileData(string position) const;
    void setTileData(string position, double data);
    string getNorth(string position);
    string getSouth(string position);
    string getEast(string position);
    string getWest(string position);
    vector<string> toStrings();
};
#endif 
