/**
 * Program: Survival Game
 *
 * Author:  William Tristan Horn
 *
 * Purpose: Survive waves of enemies in this loot survival game!
 */

#include <iostream>
#include "Game.h"

using std::cout;
using std::cin;

int main() {
   Game game;
   game.start_menu();
   cout << "\n\n\n\n\n\n\n\n";
   //system("cls");
   do {
      game.run_gamestate(GameState::shop);
      game.run_gamestate(GameState::prepare);
      game.run_gamestate(GameState::battle);
   } while (game.get_player().get_current_health() > 0);
   game.game_over();
   return EXIT_SUCCESS;
}