#ifndef PLAYER_H
#define PLAYER_H

#include <vector>
#include "Item.h"
#include "Armor.h"
#include "Potion.h"
#include "Weapon.h"

class Enemy;

class Player {
private:
   std::vector<Weapon> w_inventory;
   std::vector<Armor> a_inventory;
   std::vector<Potion> p_inventory;
   int max_health;
   int current_health;
   int attack;
   int defense;
   int currency;
public:
   Player();
   Player(std::vector<Weapon>& w_inventory, std::vector<Armor>& a_inventory, const std::vector<Potion>& p_inventory,
   const int& max_health = 100, const int& currency = 100);

   std::vector<Weapon> get_w_inventory() const;
   std::vector<Armor> get_a_inventory() const;
   std::vector<Potion> get_p_inventory() const;
   int get_max_health() const;
   int get_current_health() const;
   int get_attack() const;
   int get_defense() const;
   int get_currency() const;

   void set_w_inventory(const std::vector<Weapon>& w_inventory);
   void set_a_inventory(const std::vector<Armor>& a_inventory);
   void set_p_inventory(const std::vector<Potion>& p_inventory);
   void set_max_health(const int& max_health);
   void set_current_health(const int& current_health);
   void set_attack(const int& attack);
   void set_defense(const int& defense);
   void set_currency(const int& currency);

   void view_inventory();
   void view_inventory_polymorphism();
   void pick_up_weapon(const Weapon& weapon);
   void pick_up_armor(const Armor& armor);
   void pick_up_potion(const Potion& potion);
   void equip_weapon(const int& index);
   void equip_armor(const int& index);
   void sell_weapon(const int& index);
   void sell_armor(const int& index);
   void sell_potion(const int& index);
   void use_potion(const Potion& potion);
   
   friend int attack_enemy(const Player& player, Enemy& enemy);
};

#endif // PLAYER_H