#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include "Game.h"

const std::vector<std::string> Game::IO_files = { "game_data.txt", 
                                                  "highscore_data.txt", 
                                                  "player_data.txt",
                                                  "w_inv_data.txt",
                                                  "a_inv_data.txt",
                                                  "p_inv_data.txt"};

// CONSTRUCTORS ----------------------------------------------------------------

Game::Game() {
   // Seed rand function for use throughout program.
   srand(time(nullptr));
   // Initialize day_num in case it is not read in in read_from_files()
   day_num = 1;
   read_from_files();
}

// -----------------------------------------------------------------------------
// ACCESSORS -------------------------------------------------------------------

int Game::get_day_num() const {
   return day_num;
}

Player Game::get_player() {
   return player;
}

std::vector<Enemy> Game::get_enemies() const {
   return enemies;
}

Weapon Game::get_shop_weapon() const {
   return shop_weapon;
}

Armor Game::get_shop_armor() const {
   return shop_armor;
}

std::vector<Potion> Game::get_shop_potions() const {
   return shop_potions;
}

// -----------------------------------------------------------------------------
// MUTATORS --------------------------------------------------------------------

void Game::set_day_num(const int& day_num) {
   this->day_num = day_num;
}

void Game::set_player(const Player& player) {
   this->player = player;
}

void Game::set_enemies(const std::vector<Enemy>& enemies) {
   this->enemies = enemies;
}

void Game::set_shop_weapon(const Weapon& shop_weapon) {
   this->shop_weapon = shop_weapon;
}

void Game::set_shop_armor(const Armor& shop_armor) {
   this->shop_armor = shop_armor;
}

void Game::set_shop_potions(const std::vector<Potion>& shop_potions) {
   this->shop_potions = shop_potions;
}

// -----------------------------------------------------------------------------
// PRIVATE MEMBER FUNCTIONS ----------------------------------------------------

// Reads in game data from the various data files.
void Game::read_from_files() {
   // Reads in the day number and number of enemies defeated.
   std::ifstream i_file(IO_files[0]);
   if (i_file) {
      i_file >> day_num;
      i_file.ignore(1, '\n');
      i_file >> Enemy::num_enemies_defeated;
   }
   i_file.close();

   i_file.open(IO_files[1]);
   highscore_day_num = 0;
   highscore_enemies_defeated = 0;
   if (i_file) {
      i_file >> highscore_day_num;
      i_file.ignore(1, '\n');
      i_file >> highscore_enemies_defeated;
   }
   i_file.close();

   // Reads in the players max health and currency.
   int max_health, currency;
   i_file.open(IO_files[2]);
   if (i_file) {
      i_file >> max_health;
      i_file.ignore(1, '\n');
      i_file >> currency;
   }
   i_file.close();

   // Reads in the weapon inventory of the player.
   std::vector<Weapon> temp_w_inv;
   i_file.open(IO_files[3]);
   if (i_file) {
      while (!i_file.eof()) {
         std::string prefix = "";
         getline(i_file, prefix, '\t');
         std::string type = "";
         getline(i_file, type, '\t');
         std::string suffix = "";
         getline(i_file, suffix, '\t');
         int value = 0;
         i_file >> value;
         i_file.ignore(1, '\t');
         int attack_value = 0;
         i_file >> attack_value;
         i_file.ignore(1, '\t');
         bool equipped = false;
         i_file >> equipped;
         i_file.ignore(1, '\n');
         if (prefix != "") {
            temp_w_inv.push_back(Weapon(prefix, type, suffix, value, attack_value, equipped));
         }
      }
   }
   i_file.close();

   // Reads in the armor inventory of the player.
   std::vector<Armor> temp_a_inv;
   i_file.open(IO_files[4]);
   if (i_file) {
      while (!i_file.eof()) {
         std::string prefix = "";
         getline(i_file, prefix, '\t');
         std::string type;
         getline(i_file, type, '\t');
         std::string suffix;
         getline(i_file, suffix, '\t');
         int value;
         i_file >> value;
         i_file.ignore(1, '\t');
         int defense_value;
         i_file >> defense_value;
         i_file.ignore(1, '\t');
         bool equipped;
         i_file >> equipped;
         i_file.ignore(1, '\n');
         if (prefix != "") {
            temp_a_inv.push_back(Armor(prefix, type, suffix, value, defense_value, equipped));
         }
      }
   }
   i_file.close();

   // Reads in the potion inventory of the player.
   std::vector<Potion> temp_p_inv;
   i_file.open(IO_files[5]);
   if (i_file) {
      while (!i_file.eof()) {
         std::string type = "";
         getline(i_file, type, '\t');
         std::string description;
         getline(i_file, description, '\t');
         int value;
         i_file >> value;
         i_file.ignore(1, '\t');
         int strength;
         i_file >> strength;
         i_file.ignore(1, '\n');
         if (type != "") {
            temp_p_inv.push_back(Potion(type, description, value, strength));
         }
      }
   }
   i_file.close();

   // If both the weapon and armor inventory are not empty, passes the read in data to the save data player constructor.
   if (!temp_w_inv.empty() && !temp_a_inv.empty()) {
      player = Player(temp_w_inv, temp_a_inv, temp_p_inv, max_health, currency);
   }
   // If they were empty, this means this is a fresh run, and calls the default constructor.
   else {
      player = Player();
   }
}

// Writes the game data to the various files. Called at the end of each day.
void Game::write_to_files() {
   // Writes out the day number and number of enemies defeated.
   std::ofstream o_file(IO_files[0]);
   if (o_file) {
      o_file << day_num << "\n";
      o_file << Enemy::num_enemies_defeated << "\n";
   }
   o_file.close();

   // Reads in the highscore values.
   std::ifstream i_file(IO_files[1]);
   int highscore_day_num = 0;
   int highscore_enemies_defeated = 0;
   if (i_file) {
      i_file >> highscore_day_num;
      i_file.ignore(1, '\n');
      i_file >> highscore_enemies_defeated;
   }
   i_file.close();

   // If the current runs day number or number of enemies defeated is higher than the highscore, writes them to the highscore file.
   o_file.open(IO_files[1], std::ios::trunc);
   if (o_file) {
      day_num--;
      if (day_num > highscore_day_num) {
         o_file << day_num << "\n";
      }
      else {
         o_file << highscore_day_num << "\n";
      }
      day_num++;

      if (Enemy::num_enemies_defeated > highscore_enemies_defeated) {
         o_file << Enemy::num_enemies_defeated << "\n";
      }
      else {
         o_file << highscore_enemies_defeated << "\n";
      }
   }
   o_file.close();

   // Writes out the players max health and currency.
   o_file.open(IO_files[2], std::ios::trunc);
   if (o_file) {
      o_file << player.get_max_health() << "\n";
      o_file << player.get_currency() << "\n";
   }
   o_file.close();

   // Writes out the players weapon inventory.
   o_file.open(IO_files[3]);
   if (o_file) {
      for (Weapon w : player.get_w_inventory()) {
         o_file << w.get_prefix() << "\t" << w.get_type() << "\t" << w.get_suffix() << "\t"
            << std::to_string(w.get_value()) << "\t" << std::to_string(w.get_attack_value()) << "\t" << std::to_string(w.is_equipped()) << "\n";
      }
   }
   o_file.close();

   // Writes out the players armor inventory.
   o_file.open(IO_files[4]);
   if (o_file) {
      for (Armor a : player.get_a_inventory()) {
         o_file << a.get_prefix() << "\t" << a.get_type() << "\t" << a.get_suffix() << "\t"
            << a.get_value() << "\t" << a.get_defense_value() << "\t" << a.is_equipped() << "\n";
      }
   }
   o_file.close();

   // Writes out the players potion inventory.
   o_file.open(IO_files[5]);
   if (o_file) {
      for (Potion p : player.get_p_inventory()) {
         o_file << p.get_type() << "\t" << p.get_description() << "\t"
            << p.get_value() << "\t" << p.get_strength() << "\n";
      }
   }
   o_file.close();
}

// Generates enemies for the player to face. The maximum number of enemies generated depends on the day number.
// The strength of the enemies also depends on the day number.
void Game::generate_enemies() {
   const double enemy_ratio = 5;
   const int min_num_enemies = ceil(day_num / enemy_ratio);
   const int max_num_enemies = ceil(day_num / enemy_ratio);
   const int num_enemies = min_num_enemies + (rand() % max_num_enemies);
   enemies.clear();
   for (int i = 0; i < num_enemies; i++) {
      enemies.push_back(Enemy(day_num));
   }
}

// Generates items for the player to purchase every day. The items are a bit more powerful than those that can drop from enemies.
// They also are more expensive, by a ratio of 5.
void Game::generate_shop_items() {
   const int num_shop_potions = 3;
   const int max_increase = ceil(day_num / 3) + 1;
   const int rand_increase = rand() % max_increase;
   shop_weapon = Weapon(day_num + rand_increase);
   shop_weapon.set_value(shop_weapon.get_value() * 3);
   shop_armor = Armor(day_num + rand_increase);
   shop_armor.set_value(shop_armor.get_value() * 3);
   shop_potions.clear();
   for (int i = 0; i < num_shop_potions; i++) {
      shop_potions.push_back(Potion(day_num));
      shop_potions[i].set_value(shop_potions[i].get_value() * 3);
   }
}

// -----------------------------------------------------------------------------
// PUBLIC MEMBER FUNCTIONS -----------------------------------------------------

// Initial start menu output. Displays title and a little lore!
void Game::start_menu() const {
   std::cout << "+------------------------------------------------------------------------------+\n"
      << "|                                                                              |\n"
      << "|     ______   _    _   ______   _     _  _____  _     _   ______   _          |\n"
      << "|    / |      | |  | | | |  | \\ | |   | |  | |  | |   | | | |  | | | |         |\n"
      << "|    '------. | |  | | | |__| | \\ \\   / /  | |  \\ \\   / / | |__| | | |   _     |\n"
      << "|     ____|_/ \\_|__|_| |_|  \\_\\  \\_\\_/_/  _|_|_  \\_\\_/_/  |_|  |_| |_|__|_|    |\n"
      << "|                                                                              |\n"
      << "|                                                                              |\n"
      << "|                                                                              |\n"
      << "|                                                                              |\n"
      << "|                                                                              |\n"
      << "|                         P R E S S   A N Y   K E Y                            |\n"
      << "|                                                                              |\n"
      << "|                                                                              |\n"
      << "|                                                                              |\n"
      << "|                                                                              |\n"
      << "|                                                                              |\n"
      << "|                                                                              |\n"
      << "|                                                                              |\n"
      << "+------------------------------------------------------------------------------+\n"
      << "\n"
      << "  The world has fallen to demons. They come to overrun your home town, and you\n"
      << "   refuse to let them take all you've known. Survive for as long as possible.\n"
      << "\n"
      << "   Each day you can visit the local shop to stock up on items to aid in your\n"
      << "  survival, or sell items you don't need. You them take time to prepare, and\n"
      << "  then head out to face your enemies. Every day brings more powerful enemies,\n"
      << "            but they also bring more powerful items to aid you.\n"
      << "\n"
      << "                               G O O D   L U C K ";
   if (day_num != 1) {
      std::cout << "\n\n"
         << "                                Save files read!";  
   }
   if (highscore_day_num != 0) {
      std::cout << "\n\n                          Highscores:\n"
         << "                          Days survived:              " << highscore_day_num << "\n"
         << "                          Number of enemies defeated: " << highscore_enemies_defeated << " ";
   }

   std::cin.get();
}

// The bulk of the program. Runs various gamestates depending on the passed gamestate.
// The game will cycle through these gamestates for each day, in the order shop, prepare, battle.
// If the player dies in a battle phase, the function will return and will break out of the main loop, resulting in a game over.
// JUST A HEADS UP: THE CODE IN THIS FUNCTION IS DEFINITELY SLOPPY. The project restrictions resulted in me not writting additional
// functions that could have definitely simplified the logic. Sorry in advance those looking through!
void Game::run_gamestate(const GameState& gamestate) {
   // Shop gamestate.
   if (gamestate == GameState::shop) {
      generate_shop_items();
      char shop_choice = '\0';
      bool weapon_sold = false;
      bool armor_sold = false;
      // Initial ascii art!
      std::cout << "+------------------------------------------------------------------------------+\n"
         << "|###::: . . |::::::::::::::::::::::::::::::::::::::::::::::::::::::|           |\n"
         << "|#:: . .    | :  :  :  :  :  :  :  :  :  :  :  :  :  :  :  :  :  : |           |\n"
         << "|: .        |------------------------------------------------------|           |\n"
         << "|:          |:: :   :      }}________________________      :   : ::|           |\n"
         << "|:          |: :      o===={{>------------------------\\         : :|           |\n"
         << "|           |:             }}^^^^^^^^^^^^^^^^^^^^^^^^^^^          :|           |\n"
         << "|           |------------------------------------------------------|           |\n"
         << "|           |:: :  o        o      o       o       o     o     : ::|           |\n"
         << "|           |:    / \\      / \\    / \\     / \\     / \\   / \\        |           |\n"
         << "|           |     \\ /      \\ /    \\ /     \\ /     \\ /   \\ /        |           |\n"
         << "|       |==============================================================|       |\n"
         << "|       |==============================================================|       |\n"
         << "|        |              ______   _    _   ______   ______             |        |\n"
         << "|        |             / |      | |  | | / |  | \\ | |  | \\            |        |\n"
         << "|        |             '------. | |--| | | |  | | | |__|_/            |        |\n"
         << "|        |              ____|_/ |_|  |_| \\_|__|_/ |_|                 |        |\n"
         << "|        |                                                            |        |\n"
         << "|        |                                                            |        |\n"
         << "+------------------------------------------------------------------------------+\n\n";
      std::cout << "Hello protector! Here are todays items: (Day Number " << day_num << ")\n";
      do {
         // Lists shop items.
         std::cout << "\n-{ SHOP ITEMS }-----------------------------------------------------------------\n";
         if (!weapon_sold) {
            std::cout << shop_weapon.view_item() << "\n";
         }
         if (!armor_sold) {
            std::cout << shop_armor.view_item() << "\n";
         }
         int potion_count = 1;
         for (Potion p : shop_potions) {
            std::cout << std::to_string(potion_count++) << "). " << p.view_item() << "\n";

         }
         std::cout << "--------------------------------------------------------------------------------\n\n";
         std::cout << "-{ CURRENCY }-------------------------------------------------------------------\n";
         std::cout << " " << player.get_currency() << "\n";
         std::cout << "--------------------------------------------------------------------------------\n\n";
         std::cout << "What would you like to do?\n   (Buy, Sell, View Inventory, Leave): ";
         while (true) {
            std::cin >> shop_choice;
            shop_choice = tolower(shop_choice);
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            if (shop_choice == 'b' || shop_choice == 's' || shop_choice == 'l' || shop_choice == 'v') {
               break;
            }
            else {
               std::cout << "I'm sorry protector, I don't understand. What would you like to do?\n   (Buy, Sell, View Inventory, Leave): ";
            }
         }
         switch (shop_choice) {
         case 'b': {
            std::cout << "Which item would you like to buy?\n   (weapon, armor, potion): ";
            while (true) {
               char item_choice = '\0';
               std::cin >> item_choice;
               std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
               item_choice = tolower(item_choice);
               if (item_choice == 'w') {
                  //system("cls");
                  if (player.get_currency() > shop_weapon.get_value() && !weapon_sold) {
                     std::cout << "Absolutely protector, that will be " << std::to_string(shop_weapon.get_value()) << " currency. -WEAPON BOUGHT-\n\n";
                     player.set_currency(player.get_currency() - shop_weapon.get_value());
                     shop_weapon.set_value(shop_weapon.get_value() / 3);
                     player.pick_up_weapon(shop_weapon);
                     weapon_sold = true;
                     break;
                  }
                  else {
                     if (weapon_sold) {
                        std::cout << "\n...You already bought the weapon, protector!\n\n";
                     }
                     else {
                        std::cout << "\nYou don't have enough currency protector, I cannot sell the weapon to you. I'm sorry.\n\n";
                     }
                     break;
                  }
               }
               else if (item_choice == 'a') {
                  //system("cls");
                  if (player.get_currency() > shop_armor.get_value() && !armor_sold) {
                     std::cout << "Absolutely protector, that will be " << std::to_string(shop_armor.get_value()) << " currency. -ARMOR BOUGHT-\n\n";
                     player.set_currency(player.get_currency() - shop_armor.get_value());
                     shop_armor.set_value(shop_armor.get_value() / 3);
                     player.pick_up_armor(shop_armor);
                     armor_sold = true;
                     break;
                  }
                  else {
                     if (armor_sold) {
                        std::cout << "\n...You already bought the armor, protector!\n\n";
                     }
                     else {
                        std::cout << "\nYou don't have enough currency protector, I cannot sell the armor to you. I'm sorry.\n\n";
                     }
                     break;
                  }
               }
               else if (item_choice == 'p') {
                  if (shop_potions.empty()) {
                     //system("cls");
                     std::cout << "\nWe do not have any more potions, protector!\n\n";
                     break;
                  }
                  std::cout << "Which potion would you like to buy?\n   (1 - " << shop_potions.size() << "): ";
                  while (true) {
                     int potion_choice = 0;
                     std::cin >> potion_choice;
                     std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                     //system("cls");
                     if (potion_choice < 1) {
                        std::cout << "...I'm sorry protector, I dont understand. Which potion would you like to buy?\n   (1 - " << shop_potions.size() << "): ";
                     }
                     else if (potion_choice > shop_potions.size()) {
                        std::cout << "I'm sorry protector, we don't have that many potions at the moment. Which potion would you like to buy?\n   (1 - " << shop_potions.size() << "): ";
                     }
                     else {
                        potion_choice--;
                        if (player.get_currency() > shop_potions[potion_choice].get_value()) {
                           std::cout << "\nAbsolutely protector, that will be " << shop_potions[potion_choice].get_value() << " currency. -POTION BOUGHT-\n\n";
                           player.set_currency(player.get_currency() - shop_potions[potion_choice].get_value());
                           shop_potions[potion_choice].set_value(shop_potions[potion_choice].get_value() / 3);
                           player.pick_up_potion(shop_potions[potion_choice]);
                           shop_potions.erase(shop_potions.begin() + potion_choice);
                        }
                        else {
                           std::cout << "\nYou don't have enough currency protector, I cannot sell the potion to you. I'm sorry.\n\n";
                        }
                        break;
                     }
                  }
                  break;
               }
            }
            break;
         }
         case 's': {
            char continue_sell = '\0';
            do {
               char item_choice = '\0';
               std::cout << "What type of item would you like to sell?\n   (weapon, armor, potion): ";
               std::cin >> item_choice;
               std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
               item_choice = tolower(item_choice);
               if (item_choice == 'w') {
                  //system("cls");
                  if (player.get_w_inventory().size() == 0) {
                     std::cout << "\nYou have no weapons to sell!\n\n";
                     break;
                  }
                  else if (player.get_w_inventory().size() == 1) {
                     std::cout << "\nYou only have one weapon protector, you don't wish to sell it.\n\n";
                     break;
                  }
                  int weapon_count = 1;
                  std::cout << "\n-{ WEAPONS }--------------------------------------------------------------------\n";
                  for (Weapon w : player.get_w_inventory()) {
                     std::cout << weapon_count++ << "). " << w.view_item() << "\n";
                  }
                  std::cout << "--------------------------------------------------------------------------------\n\n";
                  std::cout << "Which weapon would you like to sell?\n   (1 - " << player.get_w_inventory().size() << "): ";
                  while (true) {
                     int weapon_choice = 0;
                     std::cin >> weapon_choice;
                     std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                     //system("cls");
                     if (weapon_choice < 1) {
                        std::cout << "...I'm sorry protector, I dont understand. Which weapon would you like to sell?\n   (1 - " << player.get_w_inventory().size() << "): ";
                     }
                     else if (weapon_choice > player.get_w_inventory().size()) {
                        std::cout << "You don't have that many items, protector. Which weapon would you like to sell?\n   (1 - " << player.get_w_inventory().size() << "): ";
                     }
                     else {
                        weapon_choice--;
                        Weapon w = player.get_w_inventory()[weapon_choice];
                        std::cout << "\nAbsolutely protector, I will buy your " << w.get_prefix() << " " << w.get_type() << " " << w.get_suffix() << " for " << w.get_value() << " currency. -WEAPON SOLD-\n\n";
                        player.set_currency(player.get_currency() + w.get_value());
                        player.sell_weapon(weapon_choice);
                        break;
                     }
                  }
                  std::cout << "Would you like to sell something else?\n   (yes, no): ";
                  while (true) {
                     std::cin >> continue_sell;
                     std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                     //system("cls");
                     if (continue_sell == 'y' || continue_sell == 'n') {
                        break;
                     }
                     else {
                        std::cout << "...I'm sorry protector, I dont understand. Would you like to sell something else?\n   (yes, no): ";
                     }
                  }
               }
               else if (item_choice == 'a') {
                  //system("cls");
                  if (player.get_a_inventory().size() == 0) {
                     std::cout << "\nYou have no armor to sell!\n\n";
                     break;
                  }
                  else if (player.get_a_inventory().size() == 1) {
                     std::cout << "\nYou only have one piece of armor protector, you don't wish to sell it.\n\n";
                     break;
                  }
                  int armor_count = 1;
                  std::cout << "\n-{ ARMOR }----------------------------------------------------------------------\n";
                  for (Armor a : player.get_a_inventory()) {
                     std::cout << armor_count++ << "). " << a.view_item() << "\n";
                  }
                  std::cout << "--------------------------------------------------------------------------------\n\n";
                  std::cout << "Which armor would you like to sell?\n   (1 - " << player.get_a_inventory().size() << "): ";
                  while (true) {
                     int armor_choice = 0;
                     std::cin >> armor_choice;
                     std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                     //system("cls");
                     if (armor_choice < 1) {
                        std::cout << "...I'm sorry protector, I dont understand. Which piece of armor would you like to sell?\n   (1 - " << player.get_a_inventory().size() << "): ";
                     }
                     else if (armor_choice > player.get_a_inventory().size()) {
                        std::cout << "You don't have that many pieces of armor, protector. Which piece of armor would you like to sell?\n   (1 - " << player.get_a_inventory().size() << "): ";
                     }
                     else {
                        armor_choice--;
                        Armor a = player.get_a_inventory()[armor_choice];
                        std::cout << "\nAbsolutely protector, I will buy your " << a.get_prefix() << " " << a.get_type() << " " << a.get_suffix() << " for " << a.get_value() << " currency. -ARMOR SOLD-\n\n";
                        player.set_currency(player.get_currency() + a.get_value());
                        player.sell_armor(armor_choice);
                        break;
                     }
                  }
                  std::cout << "Would you like to sell something else?\n   (yes, no): ";
                  while (true) {
                     std::cin >> continue_sell;
                     std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                     //system("cls");
                     if (continue_sell == 'y' || continue_sell == 'n') {
                        break;
                     }
                     else {
                        std::cout << "...I'm sorry protector, I dont understand. Would you like to sell something else?\n   (yes, no): ";
                     }
                  }
               }
               else if (item_choice == 'p') {
                  //system("cls");
                  if (player.get_p_inventory().size() == 0) {
                     std::cout << "\nYou have no potions to sell!\n\n";
                     break;
                  }
                  int potion_count = 1;
                  std::cout << "\n-{ POTIONS }--------------------------------------------------------------------\n";
                  for (Potion p : player.get_p_inventory()) {
                     std::cout << potion_count++ << "). " << p.view_item() << "\n";
                  }
                  std::cout << "--------------------------------------------------------------------------------\n\n";
                  std::cout << "Which potion would you like to sell?\n   (1 - " << player.get_p_inventory().size() << "): ";
                  while (true) {
                     int potion_choice = 0;
                     std::cin >> potion_choice;
                     std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                     //system("cls");
                     if (potion_choice < 1) {
                        std::cout << "...I'm sorry protector, I dont understand. Which potion would you like to sell?\n   (1 - " << player.get_p_inventory().size() << "): ";
                     }
                     else if (potion_choice > player.get_p_inventory().size()) {
                        std::cout << "You don't have that many potions, protector. Which potion would you like to sell?\n   (1 - " << player.get_p_inventory().size() << "): ";
                     }
                     else {
                        potion_choice--;
                        Potion p = player.get_p_inventory()[potion_choice];
                        std::cout << "Absolutely protector, I will buy your " << p.get_type() << " for " << p.get_value() << " currency. -POTION SOLD-\n\n";
                        player.set_currency(player.get_currency() + p.get_value());
                        player.sell_potion(potion_choice);
                        break;
                     }
                  }
                  std::cout << "Would you like to sell something else?\n   (yes, no): ";
                  while (true) {
                     std::cin >> continue_sell;
                     std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                     //system("cls");
                     if (continue_sell == 'y' || continue_sell == 'n') {
                        break;
                     }
                     else {
                        std::cout << "...I'm sorry protector, I dont understand. Would you like to sell something else?\n   (yes, no): ";
                     }
                  }
               }
            } while (continue_sell == 'y');
            break;
         }
         case 'v': {
            //system("cls");
            std::cout << "\n";
            player.view_inventory();
            break;
         }
         case 'l': {
            break;
         }
         }
      } while (shop_choice != 'l');
      std::cout << "\nYou depart from the store.\n";
      std::cout << "Press any key to continue . . . ";
      std::cin.get();
      //system("pause");
      //system("cls");
      std::cout << "\n\n\n\n\n\n\n\n";
   }
   else if (gamestate == GameState::prepare) {
      generate_enemies();
      std::cout << "+------------------------------------------------------------------------------+\n"
         << "|_____|______|______|_____|_____|______|______|______|_____|______|______|_____|\n"
         << "|_|______|______|______|______|______|______|____|_____|______|______|______|__|\n"
         << "|_____|______|______|_____|_____|______|______|______|_____|______|______|_____|\n"
         << "|_|______|______|______|_____|____|..-----..|____|_____|______|______|______|__|\n"
         << "|_____|______|______|_____|__.-''#############''-._|______|______|______|______|\n"
         << "|_|______|______|______|____/:::::::::::::::::::::\\____|______|______|______|__|\n"
         << "|_____|______|______|______/-^--^---^----^--^---^--\\______|______|______|______|\n"
         << "|_|______|______|______|__|-------------------------|__|______|______|______|__|\n"
         << "|_____|______|______|_____|- - - - - - - - - - - - -|______|______|______|_____|\n"
         << "|_|______|______|______|__|-   -   -   -   -   -   -|__|______|______|______|__|\n"
         << "|_____|______|______|_____|                         |______|______|______|_____|\n"
         << "|_|______|______|______|__|                         |__|______|______|______|__|\n"
         << "|_____|______|______|_____|                         |______|______|______|_____|\n"
         << "|                                                                              |\n"
         << "|   .     ..           .                   o.                 .  .             |\n"
         << "|     .                                                           o.           |\n"
         << "|            .                   o.                 .                          |\n"
         << "|   .             o.                                   .              . .  .   |\n"
         << "+------------------------------------------------------------------------------+\n\n";

      std::cout << "Scouts say there ";
      if (enemies.size() == 1) {
         std::cout << "is 1 enemy to face today. ";
      }
      else {
         std::cout << "are " << enemies.size() << " enemies to face today. ";
      }
      std::cout << "(Day Number " << day_num << ")\n\n";
      player.view_inventory();
      char prepare_choice = '\0';
      do {
         std::cout << "How do you wish to prepare?\n   (equip weapon / armor, drink potion, view inventory, leave): ";
         while (true) {
            std::cin >> prepare_choice;
            prepare_choice = tolower(prepare_choice);
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            if (prepare_choice == 'e' || prepare_choice == 'd' || prepare_choice == 'v' || prepare_choice == 'l') {
               break;
            }
            else {
               std::cout << "Your thoughts wander. How do you wish to prepare?\n   (equip weapon / armor, drink potion, view inventory, leave): ";
            }
         }
         switch (prepare_choice) {
         case 'e': {
            std::cout << "Would you like to equip a weapon or armor?\n   (weapon, armor): ";
            while (true) {
               char item_choice = '\0';
               std::cin >> item_choice;
               std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
               item_choice = tolower(item_choice);
               if (item_choice == 'w') {
                  //system("cls");
                  if (player.get_w_inventory().size() == 1) {
                     std::cout << "\nYou have no other weapons to equip!\n\n";
                     break;
                  }
                  else {
                     int weapon_count = 1;
                     std::cout << "\n-{ WEAPONS }--------------------------------------------------------------------\n";
                     for (Weapon w : player.get_w_inventory()) {
                        std::cout << weapon_count++ << "). " << w.view_item() << "\n";
                     }
                     std::cout << "--------------------------------------------------------------------------------\n\n";
                     std::cout << "Which weapon would you like to equip?\n   (1 - " << player.get_w_inventory().size() << "): ";
                     while (true) {
                        int weapon_choice = 0;
                        std::cin >> weapon_choice;
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                        if (weapon_choice < 1) {
                           std::cout << "Your thoughts wander. Which weapon would you like to equip?\n   (1 - " << player.get_w_inventory().size() << "): ";
                        }
                        else if (weapon_choice > player.get_w_inventory().size()) {
                           std::cout << "You don't have that many weapons... Which weapon would you like to equip?\n   (1 - " << player.get_w_inventory().size() << "): ";
                        }
                        else {
                           //system("cls");
                           weapon_choice--;
                           std::cout << "\nATTACK: " << player.get_attack();
                           player.equip_weapon(weapon_choice);
                           std::cout << " -> " << player.get_attack() << "\n";
                           Weapon w = player.get_w_inventory()[weapon_choice];
                           std::cout << "You equip your " << w.get_prefix() << " " << w.get_type() << " " << w.get_suffix() << ".\n\n";
                           break;
                        }
                     }
                     break;
                  }
               }
               else if (item_choice == 'a') {
                  //system("cls");
                  if (player.get_a_inventory().size() == 1) {
                     std::cout << "\nYou have no other armor to equip!\n\n";
                     break;
                  }
                  else {
                     int armor_count = 1;
                     std::cout << "\n-{ ARMOR }----------------------------------------------------------------------\n";
                     for (Armor a : player.get_a_inventory()) {
                        std::cout << armor_count++ << "). " << a.view_item() << "\n";
                     }
                     std::cout << "--------------------------------------------------------------------------------\n\n";
                     std::cout << "Which piece of armor would you like to equip?\n   (1 - " << player.get_a_inventory().size() << "): ";
                     while (true) {
                        int armor_choice = 0;
                        std::cin >> armor_choice;
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                        if (armor_choice < 1) {
                           std::cout << "Your thoughts wander. Which piece of armor would you like to equip?\n   (1 - " << player.get_a_inventory().size() << "): ";
                        }
                        else if (armor_choice > player.get_a_inventory().size()) {
                           std::cout << "You don't have that many pieces of armor... Which armor would you like to equip?\n   (1 - " << player.get_a_inventory().size() << "): ";
                        }
                        else {
                           //system("cls");
                           armor_choice--;
                           std::cout << "\nDEFENSE: " << player.get_defense();
                           player.equip_armor(armor_choice);
                           std::cout << " -> " << player.get_defense() << "\n";
                           Armor a = player.get_a_inventory()[armor_choice];
                           std::cout << "You equip your " << a.get_prefix() << " " << a.get_type() << " " << a.get_suffix() << ".\n\n";
                           break;
                        }
                     }
                     break;
                  }
               }
               else {
                  std::cout << "Your thoughts wander. Would you like to equip a weapon or armor?\n   (weapon, armor): ";
               }
            }
            break;
         }
         case 'd': {
            //system("cls");
            if (player.get_p_inventory().size() == 0) {
               std::cout << "\nYou have no potions to drink!\n\n";
               break;
            }
            std::cout << "\n-{ POTIONS }--------------------------------------------------------------------\n";
            int potion_count = 1;
            for (Potion p : player.get_p_inventory()) {
               std::cout << potion_count++ << "). " << p.view_item() << "\n";
            }
            std::cout << "--------------------------------------------------------------------------------\n\n";
            std::cout << "Which potion would you like to drink?\n   (1 - " << player.get_p_inventory().size() << "): ";
            while (true) {
               int potion_choice = 0;
               std::cin >> potion_choice;
               std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
               if (potion_choice < 1) {
                  std::cout << "Your thoughts wander. Which potion would you like to drink?\n   (1 - " << player.get_p_inventory().size() << "): ";
               }
               else if (potion_choice > player.get_p_inventory().size()) {
                  std::cout << "You don't have that many potions... Which potion would you like to drink?\n   (1 - " << player.get_p_inventory().size() << "): ";
               }
               else {
                  //system("cls");
                  potion_choice--;
                  int temp_max_health = player.get_max_health();
                  int temp_current_health = player.get_current_health();
                  int temp_attack = player.get_attack();
                  int temp_defense = player.get_defense();
                  Potion p = player.get_p_inventory()[potion_choice];
                  player.use_potion(player.get_p_inventory()[potion_choice]);
                  std::cout << "\nMAX HEALTH:     " << temp_max_health << " -> " << player.get_max_health() << "\n";
                  std::cout << "CURRENT HEALTH: " << temp_current_health << " -> " << player.get_current_health() << "\n";
                  std::cout << "ATTACK:         " << temp_attack << " -> " << player.get_attack() << "\n";
                  std::cout << "DEFENSE:        " << temp_defense << " -> " << player.get_defense() << "\n";
                  std::cout << "You drink your " << p.get_type() << " potion.\n\n";
                  break;
               }
            }
            break;
         }
         case 'v': {
            //system("cls");
            player.view_inventory();
            break;
         }
         case 'l': {
            break;
         }
         }
      } while (prepare_choice != 'l');
      std::cout << "\nYou depart to the battlefield.\n";
      std::cout << "Press any key to continue . . . ";
      std::cin.get();
      //system("pause");
      //system("cls");
      std::cout << "\n\n\n\n\n\n\n\n";
   }
   else if (gamestate == GameState::battle) {
      std::cout << "+------------------------------------------------------------------------------+\n"
         << "|                                                    ,--,  ,.-.                |\n"
         << "|                      ,                   \\,       '-,-`,'-.' | ._            |\n"
         << "|                     /|           \\    ,   |\\         }  )/  / `-,',          |\n"
         << "|                     [ '          |\\  /|   | |        /  \\|  |/`  ,`          |\n"
         << "|                     | |       ,.`  `,` `, | |  _,...(   (      _',           |\n"
         << "|                     \\  \\  __ ,-` `  ,  , `/ |,'      Y     (   \\_L\\          |\n"
         << "|                      \\  \\_\\,``,   ` , ,  /  |         )         _,/          |\n"
         << "|                       \\  '  `  ,_ _`_,-,<._.<        /         /             |\n"
         << "|                        ', `>.,`  `  `   ,., |_      |         /              |\n"
         << "|                          \\/`  `,   `   ,`  | /__,.-`    _,   `\\              |\n"
         << "|                      -,-..\\  _  \\  `  /  ,  / `._) _,-\\`       \\             |\n"
         << "|                       \\_,,.) /\\    ` /  / ) (-,, ``    ,        |            |\n"
         << "|                      ,` )  | \\_\\       '-`  |  `(               \\            |\n"
         << "|                     /  /```(   , --, ,' \\   |`<`    ,            |           |\n"
         << "|                    /  /_,--`\\   <\\  V /> ,` )<_/)  | \\      _____)           |\n"
         << "|              ,-, ,`   `   (_,\\ \\    |   /) / __/  /   `----`                 |\n"
         << "|             (-, \\           ) \\ ('_.-._)/ /,`    /                           |\n"
         << "|             | /  `          `/ \\\\ V   V, /`     /                            |\n"
         << "|          ,--\\(        ,     <_/`\\\\     ||      /                             |\n"
         << "|         (   ,``-     \\/|         \\-A.A-`|     /                              |\n"
         << "|        ,>,_ )_,..(    )\\          -,,_-`  _--`                               |\n"
         << "|       (_ \\|`   _,/_  /  \\_            ,--`                                   |\n"
         << "|         \\( `   <.,../`     `-.._   _,-`                                      |\n"
         << "|         `                      ```                                           |\n"
         << "+------------------------------------------------------------------------------+\n\n";
      do {
         
         std::cout << "\n-{ PLAYER HEALTH }------------------------------------------------------------\n";
         std::cout << player.get_current_health() << " / " << player.get_max_health() << "\n";
         std::cout << "------------------------------------------------------------------------------\n";
         std::cout << "-{ ENEMY HEALTH }-------------------------------------------------------------\n";
         int enemy_count = 1;
         for (Enemy e : enemies) {
            std::cout << "Enemy " << enemy_count++ << " Health: " << e.get_health() << "\n";
         }
         std::cout << "------------------------------------------------------------------------------\n\n";
         std::cout << "What would you like to do?\n   (attack, drink potion): ";
         while (true) {
            char battle_choice = '\0';
            std::cin >> battle_choice;
            battle_choice = tolower(battle_choice);
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            if (battle_choice == 'a') {
               std::cout << "Which enemy would you like to attack?\n   (1 - " << enemies.size() << "): ";
               while (true) {
                  int enemy_choice = 0;
                  std::cin >> enemy_choice;
                  std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                  if (enemy_choice < 1) {
                     std::cout << "Invalid choice. Which enemy would you like to attack?\n   (1 - " << enemies.size() << "): ";
                  }
                  else if (enemy_choice > enemies.size()) {
                     std::cout << "There are not that many enemies! Which enemy would you like to attack?\n   (1 - " << enemies.size() << "): ";
                  }
                  else {
                     //system("cls");
                     enemy_choice--;
                     int damage_dealt = attack_enemy(player, enemies[enemy_choice]);
                     std::cout << "\n-{ PLAYER HEALTH }------------------------------------------------------------\n";
                     std::cout << player.get_current_health() << " / " << player.get_max_health() << "\n";
                     std::cout << "------------------------------------------------------------------------------\n";
                     std::cout << "-{ ENEMY HEALTH }-------------------------------------------------------------\n";
                     enemy_count = 1;
                     for (Enemy e : enemies) {
                        std::cout << "Enemy " << enemy_count++ << " Health: " << e.get_health() << "\n";
                     }
                     std::cout << "------------------------------------------------------------------------------\n\n";
                     std::cout << "The enemy took " << damage_dealt << " damage!\n";
                     if (enemies[enemy_choice].get_health() <= 0) {
                        std::cout << "The enemy was defeated!\n\n";
                        std::cout << "-{ DROPS }--------------------------------------------------------------------\n";
                        int item_drop = rand() % 3;
                        switch (item_drop) {
                        case 0:
                           std::cout << enemies[enemy_choice].drop_weapon().view_item() << "\n";
                           player.pick_up_weapon(enemies[enemy_choice].drop_weapon());
                           break;
                        case 1:
                           std::cout << enemies[enemy_choice].drop_armor().view_item() << "\n";
                           player.pick_up_armor(enemies[enemy_choice].drop_armor());
                           break;
                        case 2:
                           std::cout << enemies[enemy_choice].drop_potion().view_item() << "\n";
                           player.pick_up_potion(enemies[enemy_choice].drop_potion());
                           break;
                        }
                        std::cout << "Currency: " << enemies[enemy_choice].drop_currency() << "\n";
                        std::cout << "------------------------------------------------------------------------------\n\n";
                        player.set_currency(player.get_currency() + enemies[enemy_choice].drop_currency());
                        enemies.erase(enemies.begin() + enemy_choice);
                        Enemy::num_enemies_defeated++;
                     }
                     break;
                  }
               }
               break;
            }
            else if (battle_choice == 'd') {
               //system("cls");
               if (player.get_p_inventory().size() == 0) {
                  std::cout << "You have no potions to drink!\n\n";
                  break;
               }
               std::cout << "\n-{ POTIONS }-----------------------------------------------------------------\n";
               int potion_count = 1;
               for (Potion p : player.get_p_inventory()) {
                  std::cout << potion_count++ << "). " << p.view_item() << "\n";
               }
               std::cout << "------------------------------------------------------------------------------\n\n";
               std::cout << "Which potion would you like to drink?\n   (1 - " << player.get_p_inventory().size() << "): ";
               while (true) {
                  int potion_choice = 0;
                  std::cin >> potion_choice;
                  std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                  if (potion_choice < 1) {
                     std::cout << "Your thoughts wander. Which potion would you like to drink?\n   (1 - " << player.get_p_inventory().size() << "): ";
                  }
                  else if (potion_choice > player.get_p_inventory().size()) {
                     std::cout << "You don't have that many potions... Which potion would you like to drink?\n   (1 - " << player.get_p_inventory().size() << "): ";
                  }
                  else {
                     //system("cls");
                     potion_choice--;
                     int temp_max_health = player.get_max_health();
                     int temp_current_health = player.get_current_health();
                     int temp_attack = player.get_attack();
                     int temp_defense = player.get_defense();
                     Potion p = player.get_p_inventory()[potion_choice];
                     player.use_potion(player.get_p_inventory()[potion_choice]);
                     std::cout << "MAX HEALTH:     " << temp_max_health << " -> " << player.get_max_health() << "\n";
                     std::cout << "CURRENT HEALTH: " << temp_current_health << " -> " << player.get_current_health() << "\n";
                     std::cout << "ATTACK:         " << temp_attack << " -> " << player.get_attack() << "\n";
                     std::cout << "DEFENSE:        " << temp_defense << " -> " << player.get_defense() << "\n";
                     std::cout << "You drink your " << p.get_type() << " potion.\n\n";
                     break;
                  }
               }
               break;
            }
            else {
               std::cout << "Invalid command! What would you like to do?\n   (attack, drink potion): ";
            }
         }
         if (!enemies.empty()) {
            std::cout << "Enemies turn!\n";
            std::cout << "Press any key to continue . . . ";
            std::cin.get();
            //system("pause");
            //system("cls");
            for (Enemy e : enemies) {
               int damage_dealt = attack_player(e, player);
               std::cout << "\n-{ PLAYER HEALTH }------------------------------------------------------------\n";
               std::cout << player.get_current_health() << " / " << player.get_max_health() << "\n";
               std::cout << "------------------------------------------------------------------------------\n";
               std::cout << "-{ ENEMY HEALTH }-------------------------------------------------------------\n";
               enemy_count = 1;
               for (Enemy e : enemies) {
                  std::cout << "Enemy " << enemy_count++ << " Health: " << e.get_health() << "\n";
               }
               std::cout << "------------------------------------------------------------------------------\n\n";
               std::cout << "The enemy dealt " << damage_dealt << " damage!\n";
               std::cout << "Press any key to continue . . . ";
               std::cin.get();
               //system("pause");
               //system("cls");
               if (player.get_current_health() <= 0) {
                  break;
               }
            }
         }
      } while (player.get_current_health() > 0 && enemies.size() != 0);

      // Resets player attack to equipped attack values.
      int index = 0;
      for (Weapon w : player.get_w_inventory()) {
         if (w.is_equipped()) {
            player.equip_weapon(index);
            break;
         }
         index++;
      }
      // Resets player defense to equipped defense values.
      index = 0;
      for (Armor a : player.get_a_inventory()) {
         if (a.is_equipped()) {
            player.equip_armor(index);
            break;
         }
         index++;
      }
      if (player.get_current_health() > 0) {
         (*this)++;
         std::cout << "\nYou depart from the battlefield victorous! +10 MAX HEALTH!\n";
         write_to_files();
         std::cout << "Progress saved!\n";
      }
      else {
         std::cout << "The protector was defeated. Their actions will be remembered.\n";
      }
      std::cout << "Press any key to continue . . . ";
      std::cin.get();
      //system("pause");
      //system("cls");
      std::cout << "\n\n\n\n\n\n\n\n";
   }
}

void Game::game_over() const {
   std::cout << "+------------------------------------------------------------------------------+\n"
             << "|                                                                              |\n"
             << "|  ______   ______   _________   ______    ______   _     _   ______  ______   |\n"
             << "| | | ____ | |  | | | | | | | \\ | |       / |  | \\ | |   | | | |     | |  | \\  |\n"
             << "| | |  | | | |__| | | | | | | | | |----   | |  | | \\ \\   / / | |---- | |__| |  |\n"
             << "| |_|__|_| |_|  |_| |_| |_| |_| |_|____   \\_|__|_/  \\_\\_/_/  |_|____ |_|  \\_\\  |\n"
             << "|                                                                              |\n"
             << "|                                                                              |\n"
             << "|                                                                              |\n"
             << "|                                                                              |\n"
             << "|                                                                              |\n"
             << "|                         P R E S S   A N Y   K E Y                            |\n"
             << "|                                                                              |\n"
             << "|                                                                              |\n"
             << "|                                                                              |\n"
             << "|                                                                              |\n"
             << "|                                                                              |\n"
             << "|                                                                              |\n"
             << "|                                                                              |\n"
             << "+------------------------------------------------------------------------------+\n"
             << "                                         ";
   std::cin.get();
   remove(IO_files[0].c_str());
   remove(IO_files[2].c_str());
   remove(IO_files[3].c_str());
   remove(IO_files[4].c_str());
   remove(IO_files[5].c_str());
}

// -----------------------------------------------------------------------------
// OPERATOR OVERLOADS ----------------------------------------------------------

Game Game::operator++(int) {
   Game temp = *this;
   day_num++;
   player.set_max_health(player.get_max_health() + 10);
   player.set_current_health(player.get_max_health());
   return temp;
}

// -----------------------------------------------------------------------------