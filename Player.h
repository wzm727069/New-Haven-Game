#ifndef COMP345_PLAYER_H
#define COMP345_PLAYER_H

#include <string>
#include <vector>
#include "MapVG.h"
#include "Resources.h"
#include "MapGB.h"


class ResourceGatherer{
    private:
    
        int collect(MapGB* board, string location, int corner, int resource);

    public:
        
        vector<int>* CollectResources(MapGB* board, int newTileLocation);
};


class ScoreCounter{
    public:
        
        int CalculateScore(MapVG* village);
};


class Player {
    private:
        int* playerID;
        MapVG* village;
        Hand* hand;
        vector<int>* resourceTracker;
        ResourceGatherer* resourceGatherer;
        ScoreCounter* scoreCounter;
    public:
        
        Player();
        Player(int id, string villageName);      
        ~Player();
        Player& operator=(const Player &p);        
        bool PlaceHarvestTile(MapGB* board, int tileIndex, int location, int orientation);        
        void DrawBuilding(BuildingDeck* buildingDeck);        
        void DrawHarvestTile(HarvestTileDeck* tileDeck);        
        vector<int>* ResourceTracker();        
        bool BuildVillage(int buildingIndex, int location, bool flipped, vector<int>* tracker);        
        void CalculateResources(MapGB* board, int newTileLocation);        
        MapVG* getVillage();        
        Hand* getHand();
        ScoreCounter* getScoreCounter();
        string tracker_to_string();
};
#endif
