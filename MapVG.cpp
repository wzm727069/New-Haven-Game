#include "MapVG.h"
#include "Graph/Graph.h"
#include <cctype>

using std::string;
using std::to_string;

MapVG::MapVG(string name){
    resourceFlags = new vector<bool>;
    resourceFlags->assign(4, false);
    villageName = new string(name);
    board = new Graph(false);
    buildingCount = new int(0);
    vector<string> reachableNodes;
    int nodeName, fromNode, toNorthNode, toSouthNode, toEastNode, toWestNode, i, j, k, l, m;

    //Creating a connected graph.
    for( i = 0; i < 30; i++){ 
        board->addNode(0, to_string(i));
    }
    for(j = 0; j < 5; j++){
        fromNode = j;
        toSouthNode = fromNode + 5;
        toEastNode = fromNode + 1;
        toWestNode = fromNode - 1;
        board->addEdge(to_string(fromNode), to_string(toSouthNode));
        if(fromNode == 0){
            board->addEdge(to_string(fromNode), to_string(toEastNode));
        }
        else if(fromNode == 4){
            board->addEdge(to_string(fromNode), to_string(toWestNode));
        }
        else{
            board->addEdge(to_string(fromNode), to_string(toEastNode));
            board->addEdge(to_string(fromNode), to_string(toWestNode));
        }
    }
    for(k = 5; k < 25; k++){
        fromNode = k;
        toSouthNode = fromNode + 5;
        toNorthNode = fromNode - 5;
        toEastNode = fromNode + 1;
        toWestNode = fromNode - 1;
        board->addEdge(to_string(fromNode), to_string(toNorthNode));
        board->addEdge(to_string(fromNode), to_string(toSouthNode));
        if(fromNode % 5 == 0){
            board->addEdge(to_string(fromNode), to_string(toEastNode));
        }
        else if(fromNode % 5 == 4){ 
            board->addEdge(to_string(fromNode), to_string(toWestNode));
        }
        else{ 
            board->addEdge(to_string(fromNode), to_string(toWestNode));
            board->addEdge(to_string(fromNode), to_string(toEastNode));
        }
    }
    for( l = 25; l < 30; l++){
        fromNode = l;
        toNorthNode = fromNode - 5;
        toEastNode = fromNode + 1;
        toWestNode = fromNode - 1;
        board->addEdge(to_string(fromNode), to_string(toNorthNode));
        if(fromNode == 25){
            board->addEdge(to_string(fromNode), to_string(toEastNode));
        }
        else if(fromNode == 29){
            board->addEdge(to_string(fromNode), to_string(toWestNode));
        }
        else{
            board->addEdge(to_string(fromNode), to_string(toWestNode));
            board->addEdge(to_string(fromNode), to_string(toEastNode));
        }
    }
}

MapVG::MapVG() : MapVG("unspecified"){}

MapVG::MapVG(const MapVG &MapVG){
    villageName = MapVG.villageName;
    resourceFlags = new vector<bool>(*MapVG.resourceFlags);
    board = new Graph(*MapVG.board);
    buildingCount = new int(*MapVG.buildingCount);
}

MapVG::~MapVG(){
    delete villageName;
    delete resourceFlags;
    delete board;
    delete buildingCount;
};

string MapVG::getName(){
    return *villageName;
}

Graph* MapVG::getBoard() {
    return board;
}

vector<bool>* MapVG::getFlags() {
    return resourceFlags;
}

double MapVG::getTileData(string position) const{
    return board->getNodeValue(position);
}

void MapVG::setTileData(string position, double data) {
    board->setNodeValue(position, data);
}

string MapVG::getNorth(string position){
    vector<string> neighbors = board->neighborNames(position);
    for (int i = 0; i < neighbors.size(); i++) {
        if(stoi(neighbors.at(i)) <= stoi(position)-5)
            return neighbors.at(i);
    }
    return "";
}
string MapVG::getSouth(string position){
    vector<string> neighbors = board->neighborNames(position);
    for (int i = 0; i < neighbors.size(); i++) {
        if(stoi(neighbors.at(i)) >= stoi(position)+5)
            return neighbors.at(i);
    }
    return "";
}
string MapVG::getEast(string position){
    vector<string> neighbors = board->neighborNames(position);
    for (int i = 0; i < neighbors.size(); i++) {
        if(stoi(neighbors.at(i)) == stoi(position)+1)
            return neighbors.at(i);
    }
    return "";
}
string MapVG::getWest(string position){
    vector<string> neighbors = board->neighborNames(position);
    for (int i = 0; i < neighbors.size(); i++) {
        if(stoi(neighbors.at(i)) == stoi(position)-1)
            return neighbors.at(i);
    }
    return "";
}

int MapVG::getBuildingCount(){
    return *buildingCount;
}

void MapVG::incrementBuildingCount(){
    *buildingCount = *buildingCount+1;
}

vector<string> MapVG::toStrings(){
    vector<string> strings;
    strings.assign(7, "");
    int index = 0;
    for(int i = 0; i < 6; i++){
        for(int j = 0; j < 5; j++){
            int data = getTileData(to_string(j+i*5));
            strings.at(index) += '|';
            if(data == 0){
                if(i<2)
                    strings.at(index) += ' ';
                strings.at(index) += to_string(j+i*5);
            }
            else {
                int type = data/100%10;
                int flipped = data%10;
                char c = ' ';
                if (type == 1)
                    c = 'W';
                else if(type == 2)
                    c = 'F';
                else if(type == 3)
                    c = 'Q';
                else if(type == 4)
                    c = 'M';
                if (flipped)
                    c = tolower(c);

                strings.at(index) += " ";
                strings.at(index) += c;
            }
        }
        strings.at(index) += "| ";
        strings.at(index) += to_string(6-i);
        index++;
    }
    strings.at(index) += "  5  4  3  4  5  X";
    return strings;
}
