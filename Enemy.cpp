#include <cstdlib>
#include <ctime>
#include "Enemy.h"
#include "Player.h"

// PUBLIC STATIC DATA MEMBERS --------------------------------------------------

int Enemy::num_enemies_defeated = 0;

// -----------------------------------------------------------------------------
// CONSTRUCTORS ----------------------------------------------------------------

// Random generation constructor.
Enemy::Enemy(const int& day) {
   int rand_health = day * 5;
   int variability = rand() % (day * 10);
   rand_health += variability;
   health = rand_health;

   int rand_atk = day * 4;
   variability = rand() % (day * 2);
   rand_atk += variability;
   attack = rand_atk;

   int rand_def = day;
   variability = rand() % (day * 3);
   rand_def += variability;
   defense = rand_def;

   int rand_currency = day * 15;
   variability = rand() % (day * 10);
   rand_currency += variability;
   currency = rand_currency;

   set_weapon(Weapon(day));
   set_armor(Armor(day));
   set_potion(Potion(day));
}

// -----------------------------------------------------------------------------
// ACCESSORS -------------------------------------------------------------------

int Enemy::get_health() const {
   return health;
}

int Enemy::get_attack() const {
   return attack;
}

int Enemy::get_defense() const {
   return defense;
}

Weapon Enemy::drop_weapon() const {
   return weapon;
}

Armor Enemy::drop_armor() const {
   return armor;
}

Potion Enemy::drop_potion() const {
   return potion;
}

int Enemy::drop_currency() const {
   return currency;
}

// -----------------------------------------------------------------------------
// MUTATORS --------------------------------------------------------------------

void Enemy::set_health(const int& health) {
   this->health = health;
}

void Enemy::set_attack(const int& attack) {
   this->attack = attack;
}

void Enemy::set_defense(const int& defense) {
   this->defense = defense;
}

void Enemy::set_weapon(const Weapon& weapon) {
   this->weapon = weapon;
}

void Enemy::set_armor(const Armor& armor) {
   this->armor = armor;
}

void Enemy::set_potion(const Potion& potion) {
   this->potion = potion;
}

// -----------------------------------------------------------------------------
// FRIEND FUNCTIONS ------------------------------------------------------------


// Uses the enemy's attack value and the player's defense value to calculate damage dealt to the player.
// Returns the damage dealt.
int attack_player(const Enemy& enemy, Player& player) {
   int damage = enemy.get_attack() - player.get_defense();
   if (damage < 0) {
      damage = 0;
   }
   player.set_current_health(player.get_current_health() - damage);
   if (player.get_current_health() < 0) {
      player.set_current_health(0);
   }
   return damage;
}

// -----------------------------------------------------------------------------