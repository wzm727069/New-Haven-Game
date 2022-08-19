#include "GameObservers.h"
#include <iostream>
#include <bits/stdc++.h>

using std::cout;
using std::cin;

Observer::Observer(){};
Observer::~Observer(){};

Subject::Subject() {
    _observers = new list<Observer*>;
}
Subject::~Subject() {
    delete _observers;
}
void Subject::Attach(Observer* o){
    _observers->push_back(o);
}
void Subject::Detach(Observer *o) {
    _observers->remove(o);
}
void Subject::Notify() {
    list<Observer*>::iterator i = _observers->begin();
    for(; i != _observers->end(); i++)
        (*i)->Update();
}

bool Game::valid_tile_pos(string pos) {
    bool valid = false;
    if(*playercount >= 2){
        if(pos == "0" || pos == "1" || pos == "2" || pos == "3" || pos == "4" || pos == "5" || pos == "6"
           || pos == "7" || pos == "8" || pos == "9" || pos == "10" || pos == "11" || pos == "12" || pos == "13"
           || pos == "14" || pos == "15" || pos == "16" || pos == "17" || pos == "18" || pos == "19" || pos == "20"
           || pos == "21" || pos == "22" || pos == "23" || pos == "24")
            valid = true;

    }
    if(*playercount >= 3){
        if(pos == "25" || pos == "26" || pos == "27" || pos == "28" || pos == "29" || pos == "30" || pos == "31"
           || pos == "32" || pos == "33" || pos == "34")
            valid = true;
    }
    if(*playercount == 4){
        if(pos == "35" || pos == "36" || pos == "37" || pos == "38" || pos == "39" || pos == "40" || pos == "41"
           || pos == "42" || pos == "43" || pos == "44")
            valid = true;
    }
    return valid;
}
bool Game::valid_building_pos(string pos) {
    return (pos == "0" || pos == "1" || pos == "2" || pos == "3" || pos == "4" || pos == "5" || pos == "6"
            || pos == "7" || pos == "8" || pos == "9" || pos == "10" || pos == "11" || pos == "12" || pos == "13"
            || pos == "14" || pos == "15" || pos == "16" || pos == "17" || pos == "18" || pos == "19" || pos == "20"
            || pos == "21" || pos == "22" || pos == "23" || pos == "24" || pos == "25" || pos == "26" || pos == "27"
            || pos == "28" || pos == "29");
}
bool Game::is_number(string str) {
    bool isNumber = true;
    for(int i=0; i < str.size(); i++) {
        if(str[i] != '0' && str[i] != '1' && str[i] != '2' && str[i] != '3' && str[i] != '4' && str[i] != '5'
           && str[i] != '6' && str[i] != '7' && str[i] != '8' && str[i] != '9')
            isNumber = false;
    }
    return isNumber;
}
Game::Game() {
    round_num = new int(1);
    activePlayer = new int(0);
    playercount = new int(0);
    deliveryPos = new int(0);
    handPlayer = new int(0);
    phase = new string("Place Tile");
    usedDelivery = new bool(false);
    deliveryTile = new HarvestTile();
    revealedBuildings = new RevealedBuildings();
    // Creating players objects
    players = new Player*[4];
    gameBoard = new MapGB();
    // Creating a concreate deck of 144 buildings tiles objects (not random)
    buildingDeck = new BuildingDeck();
    // Creating a concreate deck of 60 harvest tiles objects (not random)
    harvestTileDeck = new HarvestTileDeck();
    winStr = new string();
}
Game::~Game() {
    delete round_num;
    delete activePlayer;
    delete playercount;
    delete deliveryPos;
    delete handPlayer;
    delete phase;
    delete usedDelivery;
    delete deliveryTile;
    delete revealedBuildings;
    delete players[0];
    delete players[1];
    delete players[2];
    delete players[3];
    delete[] players;
    delete gameBoard;
    delete buildingDeck;
    delete harvestTileDeck;
    delete winStr;
}
void Game::initialize() {
    
    string playercountstr;
    // Selecting the number of players in the game (2-4 players)
    while(!(playercountstr == "2" || playercountstr == "3" || playercountstr == "4")) {
        cout << "Enter number of players:";
        cin >> playercountstr;
    }
    *playercount = stoi(playercountstr);

    // use the map loader to load a village map
    MapGBLoader gbloader;
    gameBoard = gbloader.load(*playercount);

    // Assigning one map loader to each player
    for(int i = 0; i < *playercount; i++){
        string villageName;
        cout << "Enter village name for Player " << i+1 << ":";
        cin >> villageName;
        if(villageName.length() > 17)
            villageName = villageName.substr(0, 17);
        players[i] = new Player(i+1, villageName);
    }

    // Using DrawBuilding()method to draw 5 buildings tiles to form the initial face up pool of the game
    for(int i = 0; i < 5; i++) {
        revealedBuildings->addBuilding(buildingDeck->drawBuilding());
    }

    
    for(int i = 0; i < *playercount; i++){
        for(int j = 0; j < 6; j++){
            players[i]->DrawBuilding(buildingDeck);
        }
        players[i]->DrawHarvestTile(harvestTileDeck);
        players[i]->DrawHarvestTile(harvestTileDeck);
        players[i]->getHand()->setDeliveryTile(harvestTileDeck->drawHarvestTile());
    }
}

void Game::placeTilePhase() {
    *phase = "place tile";
    Notify();
    string tilestr = "";
    bool validTile = false;
    while(!validTile) {
        cout << "Select harvest tile to play:";
        cin >> tilestr;
        if(tilestr == "0" || tilestr == "1")
            validTile = true;
        else if(tilestr == "2" && players[*activePlayer]->getHand()->hasDeliveryTile())
            validTile = true;
    }
    int tile = stoi(tilestr);
    
    if(tile == 2){
        *usedDelivery = true;
        string data[4] = {"","","",""};
        string mes[4] = {"top left", "top right", "bottom left", "bottom right"};
        HarvestTile* placedTile = new HarvestTile();
        *deliveryTile = players[*activePlayer]->getHand()->useDeliveryTile();
        cout << "Select tile data (Wheat, Timber, Rock, Sheep)\n";
        for(int i=0; i < 4; i++) {
            while (data[i] != "Wheat" && data[i] != "Timber" && data[i] != "Rock" && data[i] != "Sheep") {
                cout << "Select " << mes[i] << " data:";
                cin >> data[i];
            }
        }
        placedTile->setTopLeftResource(&data[0]);
        placedTile->setTopRightResource(&data[1]);
        placedTile->setBottomLeftResource(&data[2]);
        placedTile->setBottomRightResource(&data[3]);
        players[*activePlayer]->getHand()->addHarvestTile(*placedTile);

        string posstr = "";
        bool validPos = false;
        while(!validPos){
            cout << "Select position for tile:";
            cin >> posstr;
            if(valid_tile_pos(posstr)) {
                *deliveryPos = stoi(posstr);
                /*
                    On each turn the active player begins by 
                    selecting one of their harvest tiles and 
                    placing it onto the Game Board using 
                    PlaceHarvestTile() method.
                */
                validPos = players[*activePlayer]->PlaceHarvestTile(gameBoard, 2, *deliveryPos, 0);
            }
        }
    }
    
    else{
        string rotstring = "";
        while(rotstring != "0" && rotstring != "1" && rotstring != "2" && rotstring != "3") {
            cout << "Select rotation (0:none 1:90cw 2:180cw 3:270cw):";
            cin >> rotstring;
        }
        string posstr = "";
        bool validPos = false;
        while(!validPos){
            cout << "Select position for tile:";
            cin >> posstr;
            if(valid_tile_pos(posstr))
                validPos = players[*activePlayer]->PlaceHarvestTile(gameBoard, tile, stoi(posstr), stoi(rotstring));
        }
    }
}
void Game::placeBuildingsPhase() {
    for(int i=0; i < *playercount; i++){
        bool placing = true;
        *handPlayer = (*activePlayer + i) % *playercount;
        *phase = "player "+to_string(*handPlayer + 1)+" place building";
        Notify();
        while(placing) {
            if (players[*handPlayer]->getHand()->getNumOfBuildings() > 0) {
                string option = "";
                while (option != "0" && option != "1") {
                    cout << "Place building (0) or Skip (1):";
                    cin >> option;
                }
                if (option == "0") {
                    string buildingStr = "";
                    int building = 0;
                    bool validBuilding = false;
                    while (!validBuilding) {
                        cout << "Select building to place:";
                        cin >> buildingStr;
                        if (is_number(buildingStr)) {
                            building = stoi(buildingStr);
                            if (building >= 0 && building < players[*handPlayer]->getHand()->getNumOfBuildings()) {
                                validBuilding = true;
                            }
                        }
                    }

                    string flippedStr = "";
                    bool flipped = false;
                    while(flippedStr != "0" && flippedStr != "1"){
                        cout << "Place building face up (0) or flipped (1):";
                        cin >> flippedStr;
                    }
                    if(flippedStr == "1")
                        flipped = true;

                    string buildPos = "";
                    while(!valid_building_pos(buildPos)){
                        cout << "Select position to build:";
                        cin >> buildPos;
                    }
                    /*
                        The active player will then construct 
                        buildings in his village using 
                        BuildVillage() method with the 
                        corresponding resources.
                    */
                    if(players[*handPlayer]->BuildVillage(building, stoi(buildPos), flipped, players[*activePlayer]->ResourceTracker()))
                        Notify();
                }
                else {
                    placing = false;
                }
            }
            else{
                placing = false;
            }
        }
    }
    *handPlayer = *activePlayer;
}

// The player with the smallest ID number will begin.
void Game::drawPhase() {
    *phase = "draw";
    Notify();
    
    bool fromPool = false;
    for(int i=0; i<4; i++){
        if(players[*activePlayer]->ResourceTracker()->at(i) == 0){
            if(!fromPool){
                string selectedstr = "";
                int selected = 5;
                while(selected >= revealedBuildings->getSize()) {
                    cout << "Draw a revealed building:";
                    cin >> selectedstr;
                    if (selectedstr == "0" || selectedstr == "1" || selectedstr == "2" ||
                        selectedstr == "3" || selectedstr == "4") {
                        selected = stoi(selectedstr);
                    }
                }
                players[*activePlayer]->getHand()->addBuilding(revealedBuildings->DrawBuilding(selected));
                fromPool = true;
                Notify();
            }
            else{
                string option = "";
                cout << "Draw from revealed (0) or Draw from deck (1)\n";
                while(!(option == "0" || option == "1")){
                    cout << "Draw Location:";
                    cin >> option;
                }
                if(option == "0"){
                    string selectedstr;
                    int selected = 5;
                    while(selected >= revealedBuildings->getSize()) {
                        cout << "Draw a revealed building:";
                        cin >> selectedstr;
                        if (selectedstr == "0" || selectedstr == "1" || selectedstr == "2" ||
                            selectedstr == "3" || selectedstr == "4") {
                            selected = stoi(selectedstr);
                        }
                    }
                    players[*activePlayer]->getHand()->addBuilding(revealedBuildings->DrawBuilding(selected));
                    fromPool = true;
                    Notify();
                }
                else{
                    players[*activePlayer]->DrawBuilding(buildingDeck);
                    Notify();
                }
            }
        }
    }

    /*
        each player uses DrawHarvestTile()to draw one harvest
        tile to be placed face down with his village board 
        as his ‘shipment’ tile1
    */
    if(!*usedDelivery){
        players[*activePlayer]->DrawHarvestTile(harvestTileDeck);
    }
}
void Game::nextTurn(){
    
    int missing = 5 - revealedBuildings->getSize();
    for(int i = 0; i < missing; i++){
        revealedBuildings->addBuilding(buildingDeck->drawBuilding());
    }

    /*
        Each player draws his resources (building, harvest), 
        uses the exchange() method to select the position on 
        the board to place the harvest tile, then plays a 
        building tile with the appropriate cost of the 
        resources.
    */    
    if(*usedDelivery) {
        players[*activePlayer]->getHand()->addHarvestTile(*deliveryTile);
        players[*activePlayer]->getHand()->exchange(gameBoard, *activePlayer + 1, 2, to_string(*deliveryPos), 0);
    }

    
    players[*activePlayer]->ResourceTracker()->assign(4, 0);
    *usedDelivery = false;

    
    if (*activePlayer >= *playercount - 1) {
        *activePlayer = 0;
        *handPlayer = 0;
        *round_num = *round_num + 1;
    } else {
        *activePlayer = *activePlayer + 1;
        *handPlayer = *handPlayer + 1;
    }
}

/*
    The result of the ComputeScore() method that counts the 
    number of colonists for each player.
*/
void Game::ComputeScore() {
    *phase = "GAME OVER";
    *handPlayer = -1;
    
    int scores[*playercount];
    /*
        The first Building the player takes must be from the 
        set of five Buildings of the game pool. Any other 
        buildings he takes may be from this set of game pool 
        or from the deck. Once the player has finished drawing, 
        he must replace Buildings drawn from the face up, set 
        with new Buildings from the deck.
    */
    int buildingCount[*playercount];
    int handBuildings[*playercount];
    for(int i=0; i < *playercount; i++){
        scores[i] = players[i]->getScoreCounter()->CalculateScore(players[i]->getVillage());
        buildingCount[i] = players[i]->getVillage()->getBuildingCount();
        handBuildings[i] = players[i]->getHand()->getNumOfBuildings();
    }
    
    vector<int> topScorePlayers;
    int highestScore = 0;
    for(int i=0; i < *playercount; i++){
        if(scores[i] == highestScore) {
            topScorePlayers.push_back(i);
        }
        else if(scores[i] > highestScore){
            topScorePlayers.clear();
            topScorePlayers.push_back(i);
            highestScore = scores[i];
        }
    }
    
    vector<int> topBuildingPlayers;
    int highestCount = 0;
    for(int i=0; i < topScorePlayers.size(); i++){
        if(buildingCount[topScorePlayers.at(i)] == highestCount) {
            topBuildingPlayers.push_back(topScorePlayers.at(i));
        }
        else if(buildingCount[topScorePlayers.at(i)] > highestCount){
            topBuildingPlayers.clear();
            topBuildingPlayers.push_back(topScorePlayers.at(i));
            highestCount = buildingCount[topScorePlayers.at(i)];
        }
    }
    
    vector<int> topHandPlayers;
    int smallestHand = INT_MAX;
    for(int i=0; i < topBuildingPlayers.size(); i++){
        if(handBuildings[topBuildingPlayers.at(i)] == smallestHand) {
            topHandPlayers.push_back(topBuildingPlayers.at(i));
        }
        else if(handBuildings[topBuildingPlayers.at(i)] < smallestHand){
            topHandPlayers.clear();
            topHandPlayers.push_back(topBuildingPlayers.at(i));
            smallestHand = handBuildings[topBuildingPlayers.at(i)];
        }
    }

    
    *winStr = "PLAYER(S) "+ to_string(topHandPlayers.at(0)+1);
    for(int i = 1; i < topHandPlayers.size(); i++){
        *winStr +=" & "+ to_string(topHandPlayers.at(i)+1);
    }
    *winStr += " WIN!\n";

    Notify();
}
bool Game::gameDone() {
    return *round_num > 10;
}
int Game::getRound() {
    return *round_num;
}
int Game::getActivePlayer() {
    return *activePlayer;
}
int Game::getPlayerCount() {
    return *playercount;
}
vector<string> Game::getGameBoardStrs() {
    return gameBoard->toStrings();
}
vector<vector<string>> Game::getVillagesStrs() {
    vector<vector<string>> villagesStrs(*playercount);
    for(int i = 0; i < *playercount; i++){
        villagesStrs[i] = players[i]->getVillage()->toStrings();
    }
    return villagesStrs;
}
string Game::getRevealedBuildingsStr() {
    return revealedBuildings->toString();
}
vector<string> Game::getVillageNames() {
    vector<string> villagesNames(*playercount);
    for(int i = 0; i < *playercount; i++){
        villagesNames[i] = players[i]->getVillage()->getName();
    }
    return villagesNames;
}
string Game::getTrackerStr() {
    return players[*activePlayer]->tracker_to_string();
}
int Game::getHandPlayer() {
    return *handPlayer;
}
void Game::printCurrentHand() {
    cout << *players[*handPlayer]->getHand();
}
string Game::getPhase() {
    return *phase;
}
vector<string> Game::getStatsStrs(){
    vector<string> stats(*playercount);
    for(int i=0; i < stats.size(); i++){
        int score = players[i]->getScoreCounter()->CalculateScore(players[i]->getVillage());
        int bCount = players[i]->getVillage()->getBuildingCount();
        int hCount = players[i]->getHand()->getNumOfBuildings();
        stats[i] = "Player "+to_string(i+1)+" ("+players[i]->getVillage()->getName()+") - score:"+to_string(score)
                +" - board buildings:"+to_string(bCount)+" - hand buildings:"+to_string(hCount);
    }
    return stats;
}
string Game::getWinnerStr() {
    return *winStr;
}

TurnObserver::TurnObserver() {}
TurnObserver::TurnObserver(Game *g) {
    _subject = g;
    _subject->Attach(this);
}
TurnObserver::~TurnObserver() {
    _subject->Detach(this);
}
void TurnObserver::Update() {
    display();
}
void TurnObserver::display() {
    cout << string(50, '\n');
    if(_subject->getRound() <= 10)
        cout << "ROUND " << to_string(_subject->getRound()) << "  PLAYER " << to_string(_subject->getActivePlayer()+1) << "'S TURN - ";
    cout << _subject->getPhase() << "\n";

    
    vector<string> gameBoardStrings = _subject->getGameBoardStrs();
    vector<string> gameBoardStrings = _subject->getGameBoardStrs();
    vector<vector<string>> villagesStrs = _subject->getVillagesStrs();
    string revealedStr = _subject->getRevealedBuildingsStr();
    vector<string> villageNames = _subject->getVillageNames();

    

    cout << "Gameboard";
    if(_subject->getPlayerCount() < 4){
        cout << "           ";
    }
    else{
        cout << "                 ";
    }
    for(int i=0; i < villageNames.size(); i++){
        cout << villageNames[i];
        cout << string(22-villageNames[i].length(), ' ');
    }
    cout << "\n";

    
    for(int i=0; i < 7; i++){
        cout << gameBoardStrings.at(i);
        for(int j=0; j < villagesStrs.size(); j++){
            cout << "    " << villagesStrs[j][i];
        }
        cout << "\n";
    }

    
    cout << gameBoardStrings.at(7) << "\n";
    cout << gameBoardStrings.at(8) << "\n";
    cout << gameBoardStrings.at(9) << "    Revealed Buildings\n";
    cout << gameBoardStrings.at(10) << "    " << revealedStr << "\n";

    
    cout << gameBoardStrings.at(11) << "\n";
    cout << gameBoardStrings.at(12) << "\n";
    cout << gameBoardStrings.at(13) << "    Resource Tracker\n";
    cout << gameBoardStrings.at(14) << "    " << _subject->getTrackerStr() << "\n";
    cout << gameBoardStrings.at(15) << :Resource tracker << subject->getTrackerStr() << "\n";


    private String desc;
    private final String userInfo;
   	private final Observable observable;

private finals tring user INFO ;
private final overvable observable;
    
    for(int i=15; i < gameBoardStrings.size(); i++){
        cout << gameBoardStrings.at(i) << "\n";
    }
    cout << "\n";

    
    if(_subject->getHandPlayer() != -1) {
        cout << "Player " << to_string(_subject->getHandPlayer() + 1) << "'s ";
        _subject->printCurrentHand();
        cout << "\n";
    }
}

StatsObserver::StatsObserver() {}
StatsObserver::StatsObserver(Game *g) {
    _subject = g;
    _subject->Attach(this);
}
StatsObserver::~StatsObserver() {
    _subject->Detach(this);
}
void StatsObserver::Update() {
    display();
}
void StatsObserver::Degraded(){
	display();
}
void StatsObserver::display() {
    if(_subject->gameDone())
        cout << _subject->getWinnerStr() << "\n";
    vector<string> stats = _subject->getStatsStrs();
    for(int i=0; i < stats.size(); i++){
        cout << stats[i] << "\n";
    }
    cout << "\n";
}
