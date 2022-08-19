#include "Resources.h"
#include <string>
#include <vector>
#include <cmath>
#include <chrono>

using std::string;
using std::vector;
using std::to_string;

/*
    The player needs to rest all four Resource Markers back to 
    zero for the Resource Track, then draw a new Harvest Tile 
    to replace the one he played at the start of the turn. 
    Then the turn passes to the next payer following clockwise 
    order.
*/

HarvestTile::HarvestTile() {
    bottomLeft = new string("");
    bottomRight = new string("");
    topLeft = new string("");
    topRight = new string("");
}
HarvestTile::HarvestTile(const HarvestTile& harvestTile){
    bottomLeft = new string;
    bottomRight = new string;
    topLeft = new string;
    topRight = new string;
    *bottomLeft = *harvestTile.bottomLeft;
    *bottomRight = *harvestTile.bottomRight;
    *topLeft = *harvestTile.topLeft;
    *topRight = *harvestTile.topRight;
}
HarvestTile::HarvestTile(int indexOfHT) {

    topLeft = new string;
    topRight = new string;
    bottomLeft = new string;
    bottomRight = new string;
	switch (indexOfHT) {
	case 1:  *topLeft = "Rock";  *topRight = "Rock";  *bottomLeft = "Wheat";  *bottomRight = "Sheep"; break;
	case 2:  *topLeft = "Rock";  *topRight = "Rock";  *bottomLeft = "Wheat";  *bottomRight = "Timber"; break;
	case 3:  *topLeft = "Rock";  *topRight = "Rock";  *bottomLeft = "Sheep";  *bottomRight = "Timber"; break;
	case 4:  *topLeft = "Timber"; *topRight = "Timber"; *bottomLeft = "Sheep";  *bottomRight = "Rock"; break;
	case 5:  *topLeft = "Timber"; *topRight = "Timber"; *bottomLeft = "Wheat";  *bottomRight = "Rock"; break;
	case 6:  *topLeft = "Timber"; *topRight = "Timber"; *bottomLeft = "Sheep";  *bottomRight = "Wheat"; break;
	case 7:  *topLeft = "Wheat";  *topRight = "Wheat";  *bottomLeft = "Sheep";  *bottomRight = "Rock"; break;
	case 8:  *topLeft = "Wheat";  *topRight = "Wheat";  *bottomLeft = "Sheep";  *bottomRight = "Timber"; break;
	case 9:  *topLeft = "Wheat";  *topRight = "Wheat";  *bottomLeft = "Rock";  *bottomRight = "Timber"; break;
	case 10: *topLeft = "Sheep";  *topRight = "Sheep";  *bottomLeft = "Rock";  *bottomRight = "Timber"; break;
	case 11: *topLeft = "Sheep";  *topRight = "Sheep";  *bottomLeft = "Rock";  *bottomRight = "Wheat"; break;
	case 12: *topLeft = "Sheep";  *topRight = "Sheep";  *bottomLeft = "Wheat";  *bottomRight = "Timber"; break;

	case 13: *topLeft = "Rock";  *topRight = "Rock";  *bottomLeft = "Rock"; *bottomRight = "Sheep"; break;
	case 14: *topLeft = "Rock";  *topRight = "Rock";  *bottomLeft = "Rock"; *bottomRight = "Timber"; break;
	case 15: *topLeft = "Rock";  *topRight = "Rock";  *bottomLeft = "Rock"; *bottomRight = "Wheat"; break;
	case 16: *topLeft = "Timber"; *topRight = "Timber"; *bottomLeft = "Timber"; *bottomRight = "Wheat"; break;
	case 17: *topLeft = "Timber"; *topRight = "Timber"; *bottomLeft = "Timber"; *bottomRight = "Sheep"; break;
	case 18: *topLeft = "Timber"; *topRight = "Timber"; *bottomLeft = "Timber"; *bottomRight = "Rock"; break;
	case 19: *topLeft = "Wheat";  *topRight = "Wheat";  *bottomLeft = "Wheat";  *bottomRight = "Rock"; break;
	case 20: *topLeft = "Wheat";  *topRight = "Wheat";  *bottomLeft = "Wheat";  *bottomRight = "Timber"; break;
	case 21: *topLeft = "Wheat";  *topRight = "Wheat";  *bottomLeft = "Wheat";  *bottomRight = "Sheep"; break;
	case 22: *topLeft = "Sheep";  *topRight = "Sheep";  *bottomLeft = "Sheep";  *bottomRight = "Rock"; break;
	case 23: *topLeft = "Sheep";  *topRight = "Sheep";  *bottomLeft = "Sheep";  *bottomRight = "Timber"; break;
	case 24: *topLeft = "Sheep";  *topRight = "Sheep";  *bottomLeft = "Sheep";  *bottomRight = "Wheat"; break;

	}
}


HarvestTile::~HarvestTile() {
    delete topLeft;
    delete topRight;
    delete bottomLeft;
    delete bottomRight;
}

HarvestTile& HarvestTile::operator=(const HarvestTile& h){
    if (this == &h)
        return *this;
    delete topLeft;
    delete topRight;
    delete bottomLeft;
    delete bottomRight;
    topLeft = new string(*h.topLeft);
    topRight = new string(*h.topRight);
    bottomLeft = new string(*h.bottomLeft);
    bottomRight = new string(*h.bottomRight);
    return *this;
}

string* HarvestTile::getTopLeftResource() {
	return topLeft;
}

string* HarvestTile::getTopRightResource() {
	return topRight;
}

string* HarvestTile::getBottomLeftResource() {
	return bottomLeft;
}

string* HarvestTile::getBottomRightResource() {
	return bottomRight;
}

void HarvestTile::setTopLeftResource(string* resource) {
	topLeft = resource;
}
void HarvestTile::setTopRightResource(string* resource) {
	topRight = resource;
}
void HarvestTile::setBottomLeftResource(string* resource) {
	bottomLeft = resource;
}
void HarvestTile::setBottomRightResource(string* resource) {
	bottomRight = resource;
}

HarvestTileDeck::HarvestTileDeck() {
    harvestTiles = new vector<HarvestTile>;
    srand(time(nullptr));
	if (harvestTiles->size() == 0) {
		for (int i = 0; i < 60; i++) {
			HarvestTile* pointer = new HarvestTile(rand() % 24 + 1);
			harvestTiles->push_back(*pointer);
			delete pointer;
		}
	}
}

HarvestTileDeck::~HarvestTileDeck() {
	delete harvestTiles;
}

HarvestTile HarvestTileDeck::drawHarvestTile() {
	HarvestTile temp = harvestTiles->back();
	harvestTiles->pop_back();
	return temp;
}

int HarvestTileDeck::howManyHarvestTiles() {
	return harvestTiles->size();
}

Building::Building() {
    color = new string("");
    label = new string("");
    number = new int(0);
}

Building::Building(const Building& building){
    color = new string;
    label = new string;
    number = new int;
    *number = *building.number;
    *color = *building.color;
    *label = *building.label;
}

Building::Building(int indexOfB) {
    number = new int;
    color = new string;
    label = new string;

	switch (indexOfB) {
	case 1: *number = 1; *color = "Green"; *label = "Meadow"; break;
	case 2: *number = 2; *color = "Green"; *label = "Meadow"; break;
	case 3: *number = 3; *color = "Green"; *label = "Meadow"; break;
	case 4: *number = 4; *color = "Green"; *label = "Meadow"; break;
	case 5: *number = 5; *color = "Green"; *label = "Meadow"; break;
	case 6: *number = 6; *color = "Green"; *label = "Meadow"; break;
		
	case 7: *number = 1; *color = "Gray"; *label = "Quarry"; break;
	case 8: *number = 2; *color = "Gray"; *label = "Quarry"; break;
	case 9: *number = 3; *color = "Gray"; *label = "Quarry"; break;
	case 10: *number = 4; *color = "Gray"; *label = "Quarry"; break;
	case 11: *number = 5; *color = "Gray"; *label = "Quarry"; break;
	case 12: *number = 6; *color = "Gray"; *label = "Quarry"; break;
	
	case 13: *number = 1; *color = "Red"; *label = "Forest"; break;
	case 14: *number = 2; *color = "Red"; *label = "Forest"; break;
	case 15: *number = 3; *color = "Red"; *label = "Forest"; break;
	case 16: *number = 4; *color = "Red"; *label = "Forest"; break;
	case 17: *number = 5; *color = "Red"; *label = "Forest"; break;
	case 18: *number = 6; *color = "Red"; *label = "Forest"; break;

	case 19: *number = 1; *color = "Yellow"; *label = "Wheatfield"; break;
	case 20: *number = 2; *color = "Yellow"; *label = "Wheatfield"; break;
	case 21: *number = 3; *color = "Yellow"; *label = "Wheatfield"; break;
	case 22: *number = 4; *color = "Yellow"; *label = "Wheatfield"; break;
	case 23: *number = 5; *color = "Yellow"; *label = "Wheatfield"; break;
	case 24: *number = 6; *color = "Yellow"; *label = "Wheatfield"; break;
	}
}

Building::~Building() {
    delete number;
    delete color;
    delete label;
}

Building& Building::operator=(const Building& b){
    if (this == &b)
        return *this;
    delete number;
    delete color;
    delete label;
    number = new int(*b.number);
    color = new string(*b.color);
    label = new string(*b.label);
    return *this;
}

int* Building::getNumber() {
	return number;
}

string* Building::getColor() {
	return color;
}


string* Building::getLabel() {
	return label;
}

BuildingDeck::BuildingDeck() {
    buildings = new vector<Building>;
    for(int i = 0; i < 6; i++) {
        for (int j = 1; j < 25; j++) {
            Building *pointer = new Building(j);
            buildings->push_back(*pointer);
            delete pointer;
        }
    }
}

BuildingDeck::~BuildingDeck() {
	buildings->clear();
	delete buildings;
}

Building BuildingDeck::drawBuilding() {
    srand(time(nullptr));
    int a = rand() % buildings->size();
	Building temp = buildings->at(a);
	buildings->erase(buildings->begin()+a);
	return temp;
}

int BuildingDeck::howManyBuildings() {
	return buildings->size();
}

Hand::Hand() {
    harvestTiles = new vector<HarvestTile>;
    buildings = new vector<Building>;
    deliveryTile = nullptr;
}

Hand::Hand(const Hand &h){
    harvestTiles = new vector<HarvestTile>(*h.harvestTiles);
    buildings = new vector<Building>(*h.buildings);
    deliveryTile = nullptr;
}

Hand::~Hand() {
    delete buildings;
    delete harvestTiles;
    delete deliveryTile;
}

void Hand::deleteBuilding(int indexOfBuilding) {
	buildings->erase(buildings->begin()+indexOfBuilding);
}

void Hand::deleteHarvestTile(int indexOfHarvestTile) {
    harvestTiles->erase(harvestTiles->begin()+indexOfHarvestTile);
}

Building Hand::getBuilding(int handIndex){
    return buildings->at(handIndex);
}

HarvestTile Hand::getHarvestTile(int handIndex){
    return harvestTiles->at(handIndex);
}

void Hand::exchange(MapGB* board, int playerID, int indexOfHarvestTile, string position, int orientation) {

	HarvestTile* pointer = &(harvestTiles->at(indexOfHarvestTile));

	for(int i = 0; i < orientation; i++ ) {
		
		string* temp = pointer->getTopLeftResource();
		
		pointer->setTopLeftResource(pointer->getBottomLeftResource());
		pointer->setBottomLeftResource(pointer->getBottomRightResource());
		pointer->setBottomRightResource(pointer->getTopRightResource());
		pointer->setTopRightResource(temp);
	}
	int TileData = 0;

	if (*pointer->getTopLeftResource() == "Wheat")
		TileData = TileData + 10000;
	else if (*pointer->getTopLeftResource() == "Timber")
		TileData = TileData + 20000;
	else if (*pointer->getTopLeftResource() == "Rock")
		TileData = TileData + 30000;
	else if (*pointer->getTopLeftResource() == "Sheep")
		TileData = TileData + 40000;
	

	if (*pointer->getTopRightResource() == "Wheat")
		TileData = TileData + 1000;
	else if (*pointer->getTopRightResource() == "Timber")
		TileData = TileData + 2000;
	else if (*pointer->getTopRightResource() == "Rock")
		TileData = TileData + 3000;
	else if (*pointer->getTopRightResource() == "Sheep")
		TileData = TileData + 4000;

	if (*pointer->getBottomLeftResource() == "Wheat")
		TileData = TileData + 100;
	else if (*pointer->getBottomLeftResource() == "Timber")
		TileData = TileData + 200;
	else if (*pointer->getBottomLeftResource() == "Rock")
		TileData = TileData + 300;
	else if (*pointer->getBottomLeftResource() == "Sheep")
		TileData = TileData + 400;

	if (*pointer->getBottomRightResource() == "Wheat")
		TileData = TileData + 10;
	else if (*pointer->getBottomRightResource() == "Timber")
		TileData = TileData + 20;
	else if (*pointer->getBottomRightResource() == "Rock")
		TileData = TileData + 30;
	else if (*pointer->getBottomRightResource() == "Sheep")
		TileData = TileData + 40;

	TileData = TileData + playerID;
	board->setTileData(position, TileData);
	deleteHarvestTile(indexOfHarvestTile);
}

void Hand::addBuilding(Building building){
    buildings->push_back(building);
}

void Hand::addHarvestTile(HarvestTile harvestTile){
    harvestTiles->push_back(harvestTile);
}

HarvestTile Hand::useDeliveryTile() {
    HarvestTile temp = *deliveryTile;
    delete deliveryTile;
    deliveryTile = nullptr;
    return temp;
}

bool Hand::hasDeliveryTile() {
    return deliveryTile;
}

void Hand::setDeliveryTile(HarvestTile h) {
    deliveryTile = new HarvestTile(h);
}

int Hand::getNumOfBuildings(){
    return buildings->size();
}

ostream& operator<<(ostream& os, const Hand& h){
    os << "Hand\n";
    if(h.harvestTiles->empty()){
        os << "No Harvest Tiles\n";
    }
    else {
        os << "Harvest Tiles\n";
        for (int i = 0; i < h.harvestTiles->size(); i++) {
            HarvestTile tile = h.harvestTiles->at(i);
            os << i << ":" << (*tile.getTopLeftResource())[0] << (*tile.getTopRightResource())[0] << "  ";
        }
        if(h.deliveryTile)
            os << "2:Delivery Tile";
        os << "\n";
        for (int i = 0; i < h.harvestTiles->size(); i++) {
            HarvestTile tile = h.harvestTiles->at(i);
            os << "  " << (*tile.getBottomLeftResource())[0] << (*tile.getBottomRightResource())[0] << "  ";
        }
        os << "\n";
    }

    if(h.buildings->empty()){
        os << "No Buildings\n";
    }
    else{
        os << "Buildings\n";
        for (int i = 0; i < h.buildings->size(); i++) {
            Building building = h.buildings->at(i);
            os << i << ":" << (*building.getLabel())[0] << (*building.getNumber()) << "  ";
        }
        os << "\n";
    }
    return os;
}

RevealedBuildings::RevealedBuildings(){
    buildings = new vector<Building>;
}

RevealedBuildings::~RevealedBuildings(){
    buildings->clear();
    delete buildings;
}

void RevealedBuildings::addBuilding(Building b) {
    buildings->push_back(b);
}

Building RevealedBuildings::DrawBuilding(int index) {
    Building temp = buildings->at(index);
    buildings->erase(buildings->begin()+index);
    return temp;
}

int RevealedBuildings::getSize(){
    return buildings->size();
}

string RevealedBuildings::toString(){
    string str = "";
    for (int i = 0; i < buildings->size(); i++) {
        Building building = buildings->at(i);
        str += to_string(i);
        str += ":";
        str += (*building.getLabel())[0];
        str += to_string(*building.getNumber());
        str += "  ";
    }
    return str;
}
