#ifndef GAME_GAMEOBSERVERS_H
#define GAME_GAMEOBSERVERS_H

#include <list>
#include "MapGB.h"
#include "Player.h"
#include "Resources.h"
#include "MapGBLoader.h"

using std::list;

class Observer{
public:
    ~Observer();
    virtual void Update() = 0;
protected:
    Observer();
};

class Subject{
public:
    virtual void Attach(Observer* o);
    virtual void Detach(Observer* o);
    virtual void Notify();
    Subject();
    ~Subject();
private:
    list<Observer*> *_observers;
};

class Game : public Subject{
    friend int main();
private:
    int* round_num;
    int* activePlayer;
    int* playercount;
    int* deliveryPos;
    int* handPlayer;
    string* phase;
    bool* usedDelivery;
    HarvestTile* deliveryTile;
    RevealedBuildings* revealedBuildings;
    Player** players;
    MapGB* gameBoard;
    BuildingDeck* buildingDeck;
    HarvestTileDeck* harvestTileDeck;
    string* winStr;
    bool valid_tile_pos(string pos);
    bool valid_building_pos(string pos);
    bool is_number(string str);
public:
    Game();
    ~Game();
    void initialize();
    void placeTilePhase();
    void placeBuildingsPhase();
    void drawPhase();
    void nextTurn();
    void ComputeScore();
    bool gameDone();
    int getRound();
    int getActivePlayer();
    int getPlayerCount();
    vector<string> getGameBoardStrs();
    vector<vector<string>> getVillagesStrs();
    string getRevealedBuildingsStr();
    vector<string> getVillageNames();
    string getTrackerStr();
    int getHandPlayer();
    void printCurrentHand();
    string getPhase();
    vector<string> getStatsStrs();
    string getWinnerStr();
};

class TurnObserver : public Observer{
public:
    TurnObserver();
    TurnObserver(Game* g);
    ~TurnObserver();
    void Update();
    void display();
private:
    Game* _subject;
};

class StatsObserver : public Observer{
public:
    StatsObserver();
    StatsObserver(Game* g);
    ~StatsObserver();
    void Degraded;
    void Update();
    void display();
private:
    Game* _subject;
};

#endif 
