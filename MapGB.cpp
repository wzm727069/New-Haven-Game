#include "MapGB.h"

using std::string;
using std::to_string;
using std::stoi;

MapGB::MapGB(int numOfPlayers) {
    playerCount = numOfPlayers;
    int fromNode, toSouthNode, toNorthNode, toEastNode, toWestNode, i, j, k, l, m, n, o, p, q, r, s;
    board = new Graph(false);
    switch(numOfPlayers) {
        case 2:{
            for (i = 0; i < 25; i++) { 
                board->addNode(0, to_string(i));
            }
            for (j = 0; j < 25; j++) {
                fromNode = j;
                toSouthNode = fromNode + 5;
                toEastNode = fromNode + 1;
                toWestNode = fromNode - 1;
                toNorthNode = fromNode - 5;
                
                if (fromNode == 0) { 
                    board->addEdge(to_string(fromNode), to_string(toSouthNode));
                    board->addEdge(to_string(fromNode), to_string(toEastNode));
                } else if (fromNode == 4) { 
                    board->addEdge(to_string(fromNode), to_string(toSouthNode));
                    board->addEdge(to_string(fromNode), to_string(toWestNode));
                } else if (fromNode == 20) { 
                    board->addEdge(to_string(fromNode), to_string(toNorthNode));
                    board->addEdge(to_string(fromNode), to_string(toEastNode));
                } else if (fromNode == 24) { 
                    board->addEdge(to_string(fromNode), to_string(toNorthNode));
                    board->addEdge(to_string(fromNode), to_string(toWestNode));
                } else if (fromNode == 1 || fromNode == 2 || fromNode == 3) { 
                    board->addEdge(to_string(fromNode), to_string(toEastNode));
                    board->addEdge(to_string(fromNode), to_string(toWestNode));
                    board->addEdge(to_string(fromNode), to_string(toSouthNode));
                } else if (fromNode == 21 || fromNode == 22 || fromNode == 23) { 
                    board->addEdge(to_string(fromNode), to_string(toEastNode));
                    board->addEdge(to_string(fromNode), to_string(toWestNode));
                    board->addEdge(to_string(fromNode), to_string(toNorthNode));
                } else if (fromNode % 5 == 0) { 
                    board->addEdge(to_string(fromNode), to_string(toNorthNode));
                    board->addEdge(to_string(fromNode), to_string(toEastNode));
                    board->addEdge(to_string(fromNode), to_string(toSouthNode));
                } else if (fromNode % 5 == 4) { 
                    board->addEdge(to_string(fromNode), to_string(toWestNode));
                    board->addEdge(to_string(fromNode), to_string(toNorthNode));
                    board->addEdge(to_string(fromNode), to_string(toSouthNode));
                } else {
                    board->addEdge(to_string(fromNode), to_string(toNorthNode));
                    board->addEdge(to_string(fromNode), to_string(toSouthNode));
                    board->addEdge(to_string(fromNode), to_string(toEastNode));
                    board->addEdge(to_string(fromNode), to_string(toWestNode));
                }
            }
            break;
        }
        case 3: {
            for (l = 0; l < 35; l++) {
                board->addNode(0, to_string(l));
            }
            for (m = 0; m < 35; m++) {
                fromNode = m;
                toSouthNode = fromNode + 5;
                toEastNode = fromNode + 1;
                toWestNode = fromNode - 1;
                toNorthNode = fromNode - 5;
                if (fromNode == 0) { 
                    board->addEdge(to_string(fromNode), to_string(toSouthNode));
                    board->addEdge(to_string(fromNode), to_string(toEastNode));
                } else if (fromNode == 4) { 
                    board->addEdge(to_string(fromNode), to_string(toSouthNode));
                    board->addEdge(to_string(fromNode), to_string(toWestNode));
                } else if (fromNode == 30) { 
                    board->addEdge(to_string(fromNode), to_string(toNorthNode));
                    board->addEdge(to_string(fromNode), to_string(toEastNode));
                } else if (fromNode == 34) { 
                    board->addEdge(to_string(fromNode), to_string(toNorthNode));
                    board->addEdge(to_string(fromNode), to_string(toWestNode));
                } else if (fromNode == 1 || fromNode == 2 || fromNode == 3) { 
                    board->addEdge(to_string(fromNode), to_string(toEastNode));
                    board->addEdge(to_string(fromNode), to_string(toWestNode));
                    board->addEdge(to_string(fromNode), to_string(toSouthNode));
                } else if (fromNode == 31 || fromNode == 32 || fromNode == 33) { 
                    board->addEdge(to_string(fromNode), to_string(toEastNode));
                    board->addEdge(to_string(fromNode), to_string(toWestNode));
                    board->addEdge(to_string(fromNode), to_string(toNorthNode));
                } else if (fromNode % 5 == 0) { 
                    board->addEdge(to_string(fromNode), to_string(toNorthNode));
                    board->addEdge(to_string(fromNode), to_string(toEastNode));
                    board->addEdge(to_string(fromNode), to_string(toSouthNode));
                } else if (fromNode % 5 == 4) { 
                    board->addEdge(to_string(fromNode), to_string(toWestNode));
                    board->addEdge(to_string(fromNode), to_string(toNorthNode));
                    board->addEdge(to_string(fromNode), to_string(toSouthNode));
                } else { 
                    board->addEdge(to_string(fromNode), to_string(toNorthNode));
                    board->addEdge(to_string(fromNode), to_string(toSouthNode));
                    board->addEdge(to_string(fromNode), to_string(toEastNode));
                    board->addEdge(to_string(fromNode), to_string(toWestNode));
                }
            }
            break;
        }
        case 4: {
            for (o = 0; o < 45; o++) {
                board->addNode(0, to_string(o));
            }
            for (p = 0; p < 5; p++) { 
                fromNode = p;
                toEastNode = fromNode + 1;
                toSouthNode = fromNode + 6;
                toWestNode = fromNode - 1;
                board->addEdge(to_string(fromNode), to_string(toSouthNode)); 
                if (fromNode == 4) { 
                    board->addEdge(to_string(fromNode), to_string(toWestNode));
                }
                else if(fromNode == 0){ 
                    board->addEdge(to_string(fromNode), to_string(toEastNode));
                }
                else { 
                    board->addEdge(to_string(fromNode), to_string(toWestNode));
                    board->addEdge(to_string(fromNode), to_string(toEastNode)); 

                }
            }
            for(int t = 5; t < 12; t++){
                fromNode = t;
                toEastNode = fromNode + 1;
                toWestNode = fromNode - 1;
                toNorthNode = fromNode - 6;
                toSouthNode = fromNode + 7;
                board->addEdge(to_string(fromNode), to_string(toSouthNode)); 
                if (fromNode == 5) {
                    board->addEdge(to_string(fromNode), to_string(toEastNode));
                } else if (fromNode == 11) { 
                    board->addEdge(to_string(fromNode), to_string(toWestNode));
                }
                else{
                    board->addEdge(to_string(fromNode), to_string(toNorthNode));
                    board->addEdge(to_string(fromNode), to_string(toEastNode));
                    board->addEdge(to_string(fromNode), to_string(toWestNode));
                }
            }
            for (q = 12; q < 33; q++) {
                fromNode = q;
                toEastNode = fromNode + 1;
                toSouthNode = fromNode + 7;
                toWestNode = fromNode - 1;
                toNorthNode = fromNode - 7;
                board->addEdge(to_string(fromNode), to_string(toSouthNode)); 

                if (fromNode % 7 == 5) { 
                    board->addEdge(to_string(fromNode), to_string(toNorthNode));
                    board->addEdge(to_string(fromNode), to_string(toEastNode));
                } else if (fromNode % 7 == 4) { 
                    board->addEdge(to_string(fromNode), to_string(toNorthNode));
                    board->addEdge(to_string(fromNode), to_string(toWestNode));
                } else { 
                    board->addEdge(to_string(fromNode), to_string(toNorthNode));
                    board->addEdge(to_string(fromNode), to_string(toEastNode));
                    board->addEdge(to_string(fromNode), to_string(toWestNode));
                }
            }
            for (r = 33; r < 40; r++) {
                fromNode = r;
                toEastNode = fromNode + 1;
                toSouthNode = fromNode + 6;
                toNorthNode = fromNode - 7;
                toWestNode = fromNode - 1;
                board->addEdge(to_string(fromNode), to_string(toNorthNode));
                if (fromNode == 33) {
                    board->addEdge(to_string(fromNode), to_string(toEastNode));
                } else if (fromNode == 39) {
                    board->addEdge(to_string(fromNode), to_string(toWestNode));
                } else {
                    board->addEdge(to_string(fromNode), to_string(toSouthNode));
                    board->addEdge(to_string(fromNode), to_string(toEastNode));
                    board->addEdge(to_string(fromNode), to_string(toWestNode));
                }
            }
            for (s = 40; s < 45; s++) {
                fromNode = s;
                toEastNode = fromNode + 1;
                toNorthNode = fromNode - 6;
                toWestNode = fromNode - 1;
                board->addEdge(to_string(fromNode), to_string(toNorthNode));
                if (fromNode == 40) {
                    board->addEdge(to_string(fromNode), to_string(toEastNode));
                }
                else if (fromNode == 44) {
                    board->addEdge(to_string(fromNode), to_string(toWestNode));
                }
                else {
                    board->addEdge(to_string(fromNode), to_string(toEastNode));
                }
            }
            break;
        }
        default:
            break;

    }
}

MapGB::MapGB(MapGB &MapGB){
    playerCount = MapGB.playerCount;
    board = new Graph(*MapGB.board);
}

MapGB::MapGB(){
    playerCount = 0;
}

Graph* MapGB::getBoard() {
    return board;
}

double MapGB::getTileData(string position) const{
    return board->getNodeValue(position);
}

void MapGB::setTileData(string position, double data) {
    board->setNodeValue(position, data);
}

string MapGB::getNorth(string position){
    vector<string> neighbors = board->neighborNames(position);
    for (int i = 0; i < neighbors.size(); i++) {
        if(stoi(neighbors.at(i)) <= stoi(position)-5)
            return neighbors.at(i);
    }
    return "";
}
string MapGB::getSouth(string position){
    vector<string> neighbors = board->neighborNames(position);
    for (int i = 0; i < neighbors.size(); i++) {
        if(stoi(neighbors.at(i)) >= stoi(position)+5)
            return neighbors.at(i);
    }
    return "";
}
string MapGB::getEast(string position){
    vector<string> neighbors = board->neighborNames(position);
    for (int i = 0; i < neighbors.size(); i++) {
        if(stoi(neighbors.at(i)) == stoi(position)+1)
            return neighbors.at(i);
    }
    return "";
}
string MapGB::getWest(string position){
    vector<string> neighbors = board->neighborNames(position);
    for (int i = 0; i < neighbors.size(); i++) {
        if(stoi(neighbors.at(i)) == stoi(position)-1)
            return neighbors.at(i);
    }
    return "";
}

vector<string> MapGB::toStrings(){
    char resources[4] = {'W','T','R','S'};
    vector<string> strings;
    if(playerCount == 2){
        strings.assign(16, "");
        int index = 0;
        strings.at(index) += "================";
        index++;
        for(int i = 0; i < 5; i++){
            strings.at(index) += "|";
            for(int j = 0; j < 5; j++){
                int tile = getTileData(to_string(i*5+j));
                if(tile) {
                    strings.at(index) += resources[tile / 10000 % 10 - 1];
                    strings.at(index) += resources[tile / 1000 % 10 - 1];
                    strings.at(index) += "|";
                }
                else {
                    if(i*5+j < 10)
                        strings.at(index) += " ";
                    strings.at(index) += to_string(i * 5 + j);
                    strings.at(index) += "|";
                }
            }
            index++;
            strings.at(index) += "|";
            for(int j = 0; j < 5; j++){
                int tile = getTileData(to_string(i*5+j));
                if(tile) {
                    strings.at(index) += resources[tile / 100 % 10 - 1];
                    strings.at(index) += resources[tile / 10 % 10 - 1];
                    strings.at(index) += "|";
                }
                else
                    strings.at(index) += "  |";
            }
            index++;
            strings.at(index) += "================";
            index++;
        }
    }
    else if(playerCount == 3){
        strings.assign(22, "");
        int index = 0;
        strings.at(index) += "================";
        index++;
        for(int i = 0; i < 7; i++){
            strings.at(index) += "|";
            for(int j = 0; j < 5; j++){
                int tile = getTileData(to_string(i*5+j));
                if(tile) {
                    strings.at(index) += resources[tile / 10000 % 10 - 1];
                    strings.at(index) += resources[tile / 1000 % 10 - 1];
                    strings.at(index) += "|";
                }
                else {
                    if(i*5+j < 10)
                        strings.at(index) += " ";
                    strings.at(index) += to_string(i * 5 + j);
                    strings.at(index) += "|";
                }
            }
            index++;
            strings.at(index) += "|";
            for(int j = 0; j < 5; j++){
                int tile = getTileData(to_string(i*5+j));
                if(tile) {
                    strings.at(index) += resources[tile / 100 % 10 - 1];
                    strings.at(index) += resources[tile / 10 % 10 - 1];
                    strings.at(index) += "|";
                }
                else
                    strings.at(index) += "  |";
            }
            index++;
            strings.at(index) += "================";
            index++;
        }
    }
    else if(playerCount == 4){
        strings.assign(22, "");
        int index = 0;
        
        strings.at(index) += "======================";
        index++;
        strings.at(index) += "|  |";
        for(int i = 0; i < 5; i++){
            int tile = getTileData(to_string(i));
            if(tile) {
                strings.at(index) += resources[tile / 10000 % 10 - 1];
                strings.at(index) += resources[tile / 1000 % 10 - 1];
                strings.at(index) += "|";
            }
            else {
                strings.at(index) += " ";
                strings.at(index) += to_string(i);
                strings.at(index) += "|";
            }
        }
        strings.at(index) += "  |";
        index++;
        strings.at(index) += "|  |";
        for(int i = 0; i < 5; i++){
            int tile = getTileData(to_string(i));
            if(tile) {
                strings.at(index) += resources[tile / 100 % 10 - 1];
                strings.at(index) += resources[tile / 10 % 10 - 1];
                strings.at(index) += "|";
            }
            else
                strings.at(index) += "  |";
        }
        strings.at(index) += "  |";
        index++;
        strings.at(index) += "======================";
        index++;

        
        for(int i = 0; i < 5; i++){
            strings.at(index) += "|";
            for(int j = 0; j < 7; j++){
                int tile = getTileData(to_string(i*7+5+j));
                if(tile) {
                    strings.at(index) += resources[tile / 10000 % 10 - 1];
                    strings.at(index) += resources[tile / 1000 % 10 - 1];
                    strings.at(index) += "|";
                }
                else {
                    if(i*7+5+j < 10)
                        strings.at(index) += " ";
                    strings.at(index) += to_string(i * 7 + 5 + j);
                    strings.at(index) += "|";
                }
            }
            index++;
            strings.at(index) = "|";
            for(int j = 0; j < 7; j++){
                int tile = getTileData(to_string(i*7+5+j));
                if(tile) {
                    strings.at(index) += resources[tile / 100 % 10 - 1];
                    strings.at(index) += resources[tile / 10 % 10 - 1];
                    strings.at(index) += "|";
                }
                else
                    strings.at(index) += "  |";
            }
            index++;
            strings.at(index) += "======================";
            index++;
        }

        
        strings.at(index) += "|  |";
        for(int i = 40; i < 45; i++){
            int tile = getTileData(to_string(i));
            if(tile) {
                strings.at(index) += resources[tile / 10000 % 10 - 1];
                strings.at(index) += resources[tile / 1000 % 10 - 1];
                strings.at(index) += "|";
            }
            else {
                strings.at(index) += to_string(i);
                strings.at(index) += "|";
            }
        }
        strings.at(index) += "  |";
        index++;
        strings.at(index) += "|  |";
        for(int i = 40; i < 45; i++){
            int tile = getTileData(to_string(i));
            if(tile) {
                strings.at(index) += resources[tile / 100 % 10 - 1];
                strings.at(index) += resources[tile / 10 % 10 - 1];
                strings.at(index) += "|";
            }
            else
                strings.at(index) += "  |";
        }
        strings.at(index) += "  |";
        index++;
        strings.at(index) += "======================";
    }
    return strings;
}