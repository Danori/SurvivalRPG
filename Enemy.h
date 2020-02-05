#ifndef ENEMY_H
#define ENEMY_H

#include "Armor.h"
#include "Potion.h"
#include "Weapon.h"

class Player;

class Enemy {
private:
   int health;
   int attack;
   int defense;
   int currency;
   Weapon weapon;
   Armor armor;
   Potion potion;
public:
   static int num_enemies_defeated;

   Enemy(const int& day);

   int get_health() const;
   int get_attack() const;
   int get_defense() const;
   Weapon drop_weapon() const;
   Armor drop_armor() const;
   Potion drop_potion() const;
   int drop_currency() const;

   void set_health(const int& health);
   void set_attack(const int& attack);
   void set_defense(const int& defense);
   void set_weapon(const Weapon& weapon);
   void set_armor(const Armor& armor);
   void set_potion(const Potion& potion);

   friend int attack_player(const Enemy& enemy, Player& player);
};

#endif // ENEMY_H