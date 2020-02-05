#ifndef GAME_H
#define GAME_H

#include <vector>
#include "Player.h"
#include "Enemy.h"
#include "Item.h"

enum class GameState { shop, prepare, battle };

class Game {
private:
   static const std::vector<std::string> IO_files;
   int highscore_day_num;
   int highscore_enemies_defeated;
   int day_num;
   Player player;
   std::vector<Enemy> enemies;
   Weapon shop_weapon;
   Armor shop_armor;
   std::vector<Potion> shop_potions;

   void read_from_files();
   void write_to_files();
   void generate_enemies();
   void generate_shop_items();
public:
   Game();

   int get_day_num() const;
   Player get_player();
   std::vector<Enemy> get_enemies() const;
   Weapon get_shop_weapon() const;
   Armor get_shop_armor() const;
   std::vector<Potion> get_shop_potions() const;

   void set_day_num(const int& day_num);
   void set_player(const Player& player);
   void set_enemies(const std::vector<Enemy>& enemies);
   void set_shop_weapon(const Weapon& shop_weapon);
   void set_shop_armor(const Armor& shop_armor);
   void set_shop_potions(const std::vector<Potion>& shop_potions);

   void start_menu() const;
   void run_gamestate(const GameState& gamestate);
   void game_over() const;

   Game operator++(int);
};

#endif // GAME_H