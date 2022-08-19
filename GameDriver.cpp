
#include "GameObservers.h"
#include <iostream>

using std::cout;
using std::cin;

int main(){
    Game* game = new Game();
    TurnObserver* turnObserver = new TurnObserver(game);
    StatsObserver* statsObserver = new StatsObserver(game);    
    game->initialize();

    while (!game->gameDone()) {
        game->placeTilePhase();
        game->placeBuildingsPhase();
        game->drawPhase();
        game->nextTurn();

        string skip = "";
        while (skip != "Y" && skip != "N") {
            cout << "Skip to game end (Y/N)?";
            cin >> skip;
        }
        if(skip == "Y"){
            *(game->activePlayer) = 0;
            *(game->handPlayer) = 0;
            *(game->round_num) = 11;
        }
    }

    game->ComputeScore();

    string end = "Enter anything to end the game";
    cout << end;
    cin >> end;

    delete game;
    delete turnObserver;
    delete statsObserver;
    return 0;
}
