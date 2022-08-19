#include "Player.h"
#include "MapVGLoader.h"

using std::string;
using std::vector;

vector<int>* ResourceGatherer::CollectResources(MapGB* board, int newTileLocation) {
    MapGB* boardCopy = new MapGB(*board);
    string position = to_string(newTileLocation);
    vector<int>* resources = new vector<int>;
    resources->assign(4, 0);

    int data = boardCopy->getTileData(position);
    resources->at(data/10%10-1)++;
    resources->at(data/100%10-1)++;
    resources->at(data/1000%10-1)++;
    resources->at(data/10000%10-1)++;
    boardCopy->setTileData(position, 55550);

    resources->at(data/10000%10-1) += collect(boardCopy, boardCopy->getNorth(position), 2, data/10000%10);
    resources->at(data/10000%10-1) += collect(boardCopy, boardCopy->getWest(position), 1, data/10000%10);

    resources->at(data/1000%10-1) += collect(boardCopy, boardCopy->getNorth(position), 3, data/1000%10);
    resources->at(data/1000%10-1) += collect(boardCopy, boardCopy->getEast(position), 0, data/1000%10);

    resources->at(data/100%10-1) += collect(boardCopy, boardCopy->getWest(position), 3, data/100%10);
    resources->at(data/100%10-1) += collect(boardCopy, boardCopy->getSouth(position), 0, data/100%10);

    resources->at(data/10%10-1) += collect(boardCopy, boardCopy->getSouth(position), 1, data/10%10);
    resources->at(data/10%10-1) += collect(boardCopy, boardCopy->getEast(position), 2, data/10%10);

    delete boardCopy;
    return resources;
}

int ResourceGatherer::collect(MapGB* board, string position, int corner, int resource){
    if(!position.empty()) {
        int data = board->getTileData(position);
        if (corner == 0 && data/10000%10 == resource) {
            string dataStr = to_string(data);
            dataStr[0] = '5';
            board->setTileData(position, stod(dataStr));
            return 1 + collect(board, board->getWest(position), 1, resource)
                     + collect(board, board->getNorth(position), 2, resource)
                     + collect(board, position, 1, resource)
                     + collect(board, position, 2, resource);
        } else if (corner == 1 && data/1000%10 == resource) {
            string dataStr = to_string(data);
            dataStr[1] = '5';
            board->setTileData(position, stod(dataStr));
            return 1 + collect(board, board->getNorth(position), 3, resource)
                   + collect(board, board->getEast(position), 0, resource)
                   + collect(board, position, 3, resource)
                   + collect(board, position, 0, resource);
        } else if (corner == 2 && data/100%10 == resource) {
            string dataStr = to_string(data);
            dataStr[2] = '5';
            board->setTileData(position, stod(dataStr));
            return 1 + collect(board, board->getSouth(position), 0, resource)
                   + collect(board, board->getWest(position), 3, resource)
                   + collect(board, position, 0, resource)
                   + collect(board, position, 3, resource);
        } else if (corner == 3 && data/10%10 == resource) {
            string dataStr = to_string(data);
            dataStr[3] = '5';
            board->setTileData(position, stod(dataStr));
            return 1 + collect(board, board->getEast(position), 2, resource)
                   + collect(board, board->getSouth(position), 1, resource)
                   + collect(board, position, 2, resource)
                   + collect(board, position, 1, resource);
        }
    }
    return 0;
}

int ScoreCounter::CalculateScore(MapVG* village) {
    int score = 0;
    for(int i=0; i < 6; i++){
        bool flipped = false;
        bool full = true;
        for(int j=0; j < 5; j++){
            int position = i*5 + j;
            int data = village->getTileData(to_string(position));
            if(data == 0)
                full = false;
            else if(data%10 == 1)
                flipped = true;
        }
        if(full){
            if(!flipped)
                score += (6-i)*2;
            else
                score += (6-i);
        }
    }

    int settlerColumnScores[5] = {5,4,3,4,5};
    for(int i=0; i < 5; i++){
        bool flipped = false;
        bool full = true;
        for(int j=0; j < 6; j++){
            int position = j*5 + i;
            int data = village->getTileData(to_string(position));
            if(data == 0)
                full = false;
            else if(data%10 == 1)
                flipped = true;
        }
        if(full){
            if(!flipped)
                score += settlerColumnScores[i]*2;
            else
                score += settlerColumnScores[i];
        }
    }
    return score;
}

Player::Player(){
    playerID = new int(0);
    MapVGLoader vgloader;
    village = vgloader.load("Unspecified");
    hand = new Hand();
    // 
    resourceTracker = new vector<int>;
    // ResourceTracker to set the four game resource markers.
    resourceTracker->assign(4, 0);
    resourceGatherer = new ResourceGatherer();
    scoreCounter = new ScoreCounter();
}

Player::Player(int id, string villageName) {
    playerID = new int(id);
    MapVGLoader vgloader;
    village = vgloader.load(villageName);
    hand = new Hand();
    resourceTracker = new vector<int>;
    resourceTracker->assign(4, 0);
    resourceGatherer = new ResourceGatherer();
    scoreCounter = new ScoreCounter();
}

Player::~Player() {
    delete playerID;
    delete village;
    delete hand;
    delete resourceTracker;
    delete resourceGatherer;
    delete scoreCounter;
}

Player& Player::operator=(const Player& p){
    if (this == &p)
        return *this;
    delete playerID;
    delete village;
    delete hand;
    delete resourceTracker;
    playerID = new int(*p.playerID);
    village = new MapVG(*p.village);
    hand = new Hand(*p.hand);
    // Updating the ResourceTracker()to reflect the total collected of each color
    resourceTracker = new vector<int>(*p.resourceTracker);
    return *this;
}

bool Player::PlaceHarvestTile(MapGB* board, int tileIndex, int location, int orientation) {
    if(board->getTileData(to_string(location)) == 0) {
        hand->exchange(board, *playerID, tileIndex, to_string(location), orientation);
        CalculateResources(board, location);
        return true;
    }
    return false;
}

void Player::DrawBuilding(BuildingDeck* buildingDeck) {
    hand->addBuilding(buildingDeck->drawBuilding());
}

void Player::DrawHarvestTile(HarvestTileDeck* tileDeck) {
    hand->addHarvestTile(tileDeck->drawHarvestTile());
}

vector<int>* Player::ResourceTracker() {
    return resourceTracker;
}

bool Player::BuildVillage(int buildingIndex, int location, bool flipped, vector<int>* tracker) {
    if(village->getTileData(to_string(location)) == 0) {
        // Only one Building may occupy each space.
        Building building = hand->getBuilding(buildingIndex);
        int* number = building.getNumber();
        string* color = building.getColor();
        int colorIndex = 0;
        if(*color == "Red")
            colorIndex = 1;
        else if(*color == "Gray")
            colorIndex = 2;
        else if(*color == "Green")
            colorIndex = 3;
        int row = location/5;
        if(flipped || *number == 6-row){
            if(tracker->at(colorIndex) >= 6 - row) {
                if (!village->getFlags()->at(colorIndex)) {
                    village->getFlags()->at(colorIndex) = true;
                    hand->deleteBuilding(buildingIndex);
                    tracker->at(colorIndex) -= (6-row);
                    double data = 0;
                    if(flipped)
                        data++;
                    data += *number * 10;
                    data += (colorIndex+1)*100;
                    village->setTileData(to_string(location), data);
                    village->incrementBuildingCount();
                    return true;
                } else {
                    int adjacentData[4] = {0,0,0,0};
                    adjacentData[0] = village->getTileData(village->getEast(to_string(location)));
                    adjacentData[1] = village->getTileData(village->getWest(to_string(location)));
                    adjacentData[2] = village->getTileData(village->getNorth(to_string(location)));
                    adjacentData[3] = village->getTileData(village->getSouth(to_string(location)));
                    bool isAdj = false;
                    for(int i = 0; i > 4; i++){
                        if(adjacentData[i]/100%10 == colorIndex+1){
                            isAdj = true;
                        }
                    }
                    if(isAdj){
                        hand->deleteBuilding(buildingIndex);
                        tracker->at(colorIndex) -= (6-row);
                        double data = 0;
                        if(flipped)
                            data++;
                        data += *number * 10;
                        data += (colorIndex+1)*100;
                        village->setTileData(to_string(location), data);
                        village->incrementBuildingCount();
                        return true;
                    }
                }
            }
        }
    }
    return false;
}

/*
    Use CalculateResources()to calculate the amount of resources 
    collected for each color shown on the harvest tile the player 
    just placed.
*/
void Player::CalculateResources(MapGB* board, int newTileLocation) {
    resourceTracker = resourceGatherer->CollectResources(board, newTileLocation);
}

MapVG* Player::getVillage() {
    return village;
}

Hand* Player::getHand() {
    return hand;
}

ScoreCounter* Player::getScoreCounter(){
    return scoreCounter;
}

string Player::tracker_to_string() {
    string s = "W:" + to_string(resourceTracker->at(0)) + "  T:" + to_string(resourceTracker->at(1))
            + "  R:" + to_string(resourceTracker->at(2)) + "  S:" + to_string(resourceTracker->at(3));
    return s;
}