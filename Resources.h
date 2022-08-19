#ifndef COMP345_RESOURCES_H
#define COMP345_RESOURCES_H
#include <string>
#include <vector>
#include "MapGB.h"
#include <ostream>

using std::vector;
using std::string;
using std::to_string;
using std::ostream;

class HarvestTile {
private:

	string* topLeft;
	string* topRight;
	string* bottomLeft;
	string* bottomRight;

public:
	
	HarvestTile();
	HarvestTile(const HarvestTile& harvestTile);
	~HarvestTile();
	HarvestTile(int indexOfHT);
	HarvestTile& operator=(const HarvestTile& h);
	string* getTopLeftResource();
	string* getTopRightResource();
	string* getBottomLeftResource();
	string* getBottomRightResource();
	void setTopLeftResource(string* resource);
	void setTopRightResource(string* resource);
	void setBottomLeftResource(string* resource);
	void setBottomRightResource(string* resource);
};
class HarvestTileDeck {
private:

	vector<HarvestTile>* harvestTiles;
public:
	
	HarvestTileDeck();
	~HarvestTileDeck();	
	HarvestTile drawHarvestTile();	
	int howManyHarvestTiles();
};

class Building {
private:
	int* number;
	string* color;
	string* label;

public:
	
	Building();	
	Building(const Building& building);	
	~Building();	
	Building(int indexOfB);	
	Building& operator=(const Building& b);	
	int* getNumber();	
	string* getColor();	
	string* getLabel();
};

class BuildingDeck {
private:
	vector<Building>* buildings;
public:
	
	
	BuildingDeck();
	
	
	~BuildingDeck();
	
	
	Building drawBuilding();
	
	
	int howManyBuildings();
};

class Hand {

private:
	vector<HarvestTile>* harvestTiles;
	vector<Building>* buildings;
	HarvestTile* deliveryTile;

public:
	
	Hand();
	Hand(const Hand &h);	
	void exchange(MapGB* board, int playerID, int indexOfHarvestTile, string position, int orientation);
	~Hand();	
   	Building getBuilding(int handIndex);	
   	HarvestTile getHarvestTile(int handIndex);
	void deleteBuilding(int indexOfBuilding);	
	void deleteHarvestTile(int indexOfHarvestTile);
	void addBuilding(Building building);	
	void addHarvestTile(HarvestTile harvestTile);
	HarvestTile useDeliveryTile();
	bool hasDeliveryTile();
	void setDeliveryTile(HarvestTile h);
	int getNumOfBuildings();
	friend ostream& operator<<(ostream& os, const Hand& h);
};

ostream& operator<<(ostream& os, const Hand& h);

class RevealedBuildings {
    private:

        vector<Building>* buildings;

    public:

        RevealedBuildings();
        ~RevealedBuildings();
        void addBuilding(Building b);
        Building DrawBuilding(int index);
        int getSize();
        string toString();
};

#endif 
