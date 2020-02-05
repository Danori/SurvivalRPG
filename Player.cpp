#include <iostream>
#include <stdexcept>
#include "Player.h"
#include "Enemy.h"

// CONSTRUCTORS ----------------------------------------------------------------

// Initial playthrough constructor if input files are not read in.
Player::Player() {
   max_health = current_health = 100;
   currency = 500;
   pick_up_weapon(Weapon("Starting", "Sword", "of Courage", 1, 10));
   equip_weapon(0);
   pick_up_armor(Armor("Starting", "Plate Armor", "of Courage", 1, 5));
   equip_armor(0);
}

// Saved playthrough constructor if input files are read in.
Player::Player(std::vector<Weapon>& w_inventory, std::vector<Armor>& a_inventory, const std::vector<Potion>& p_inventory,
const int& max_health, const int& currency) {
   set_w_inventory(w_inventory);
   set_a_inventory(a_inventory);
   set_p_inventory(p_inventory);
   set_max_health(max_health);
   set_current_health(max_health);
   set_currency(currency);

   // Searches for the equipped weapon from the prior playthrough and reequips it.
   bool equipped_weapon_found = false;
   int index = 0;
   for (Weapon& w : w_inventory) {
      if (w.is_equipped()) {
         equip_weapon(index);
         equipped_weapon_found = true;
         break;
      }
      index++;
   }
   // If the equipped weapon is not found and the inventory is not empty, equips the first element.
   if (!equipped_weapon_found && !w_inventory.empty()) {
      equip_weapon(0);
   }

   // Similar to above for armor.
   bool equipped_armor_found = false;
   index = 0;
   for (Armor& a : a_inventory) {
      if (a.is_equipped()) {
         equip_armor(index);
         equipped_armor_found = true;
         break;
      }
      index++;
   }
   if (!equipped_armor_found && !a_inventory.empty()) {
      equip_armor(0);
   }
}

// -----------------------------------------------------------------------------
// ACCESSORS -------------------------------------------------------------------

std::vector<Weapon> Player::get_w_inventory() const {
   return w_inventory;
}

std::vector<Armor> Player::get_a_inventory() const {
   return a_inventory;
}

std::vector<Potion> Player::get_p_inventory() const {

   return p_inventory;
}

int Player::get_max_health() const {
   return max_health;
}

int Player::get_current_health() const {
   return current_health;
}

int Player::get_attack() const {
   return attack;
}

int Player::get_defense() const {
   return defense;
}

int Player::get_currency() const {
   return currency;
}

// -----------------------------------------------------------------------------
// MUTATORS --------------------------------------------------------------------

void Player::set_w_inventory(const std::vector<Weapon>& w_inventory) {
   this->w_inventory = w_inventory;
}

void Player::set_a_inventory(const std::vector<Armor>& a_inventory) {
   this->a_inventory = a_inventory;
}

void Player::set_p_inventory(const std::vector<Potion>& p_inventory) {
   this->p_inventory = p_inventory;
}

void Player::set_max_health(const int& max_health) {
   this->max_health = max_health;
}

void Player::set_current_health(const int& current_health) {
   this->current_health = current_health;
}

void Player::set_attack(const int& attack) {
   this->attack = attack;
}

void Player::set_defense(const int& defense) {
   this->defense = defense;
}

void Player::set_currency(const int& currency) {
   this->currency = currency;
}

// -----------------------------------------------------------------------------
// PUBLIC MEMBER FUNCTIONS -----------------------------------------------------

// Output function to display the users inventory.
void Player::view_inventory() {
   std::cout << "-{ YOUR INVENTORY }-------------------------------------------------------------\n";
   std::cout << "-{ WEAPONS }--------------------------------------------------------------------\n";
   for (Weapon w : w_inventory) {
      std::cout << w.view_item() << "\n";
   }
   std::cout << "-{ ARMOR }----------------------------------------------------------------------\n";
   for (Armor a : a_inventory) {
      std::cout << a.view_item() << "\n";
   }
   std::cout << "-{ POTIONS }--------------------------------------------------------------------\n";
   for (Potion p : p_inventory) {
      std::cout << p.view_item() << "\n";
   }
   std::cout << "--------------------------------------------------------------------------------\n\n";
}

void Player::view_inventory_polymorphism() {
   std::vector<Item*> inventory;
   for (Weapon w : w_inventory) {
      Item* i_p = &w;
      inventory.push_back(i_p);
   }
   for (Armor a : a_inventory) {
      Item* i_p = &a;
      inventory.push_back(i_p);
   }
   for (Potion p : p_inventory) {
      Item* i_p = &p;
      inventory.push_back(i_p);
   }
   for (Item* i : inventory) {
      std::cout << i->view_item();
   }
}

// Picks up weapons dropped from enemies or bought from the shop
void Player::pick_up_weapon(const Weapon& weapon) {
   w_inventory.push_back(weapon);
}

// Similar to above, for armor.
void Player::pick_up_armor(const Armor& armor) {
   a_inventory.push_back(armor);
}

// Similar to above, for potions.
void Player::pick_up_potion(const Potion& potion) {
   p_inventory.push_back(potion);
}

// Equips the weapon at the passed index of the user's weapon inventory. 
void Player::equip_weapon(const int& index) {
   // Unequip prior weapon.
   for (Weapon& w : w_inventory) {
      if (w.is_equipped()) {
         w.set_equipped(false);
         break;
      }
   }
   // Equip new weapon.
   w_inventory[index].set_equipped(true);
   set_attack(w_inventory[index].get_attack_value());
}

// Similar to above, for armor.
void Player::equip_armor(const int& index) {
   // Unequip prior armor.
   for (Armor& a : a_inventory) {
      if (a.is_equipped()) {
         a.set_equipped(false);
         break;
      }
   }
   // Equip new armor.
   a_inventory[index].set_equipped(true);
   set_defense(a_inventory[index].get_defense_value());
}

// Sells the weapon at the passed index of the user's weapon inventory.
// Note: In order to function to operate properly, the weapon inventory must have two elements.
// Program ensures that function is only called under this condition.
void Player::sell_weapon(const int& index) {
   // If the sold weapon was equipped, equips the first element.
   if (w_inventory[index].is_equipped() && index != 0) {
      equip_weapon(0);
   }
   else if (w_inventory[index].is_equipped() && index == 0) {
      equip_weapon(1);
   }
   // Removes the weapon from the weapon inventory.
   w_inventory.erase(w_inventory.begin() + index);
}

// Similar to above, for armor.
// Note: In order to function to operate properly, the weapon inventory must have two elements.
// Program ensures that function is only called under this condition.
void Player::sell_armor(const int& index) {
   if (a_inventory[index].is_equipped() && index != 0) {
      equip_armor(0);
   }
   else if (a_inventory[index].is_equipped() && index == 0) {
      equip_armor(1);
   }
   a_inventory.erase(a_inventory.begin() + index);
}

// Similar to above, for potions.
void Player::sell_potion(const int& index) {
   p_inventory.erase(p_inventory.begin() + index);
}

// Uses the passed potion, modifying the player based on the potion type.
void Player::use_potion(const Potion& potion) {
   auto it = p_inventory.begin();
   for (; it != p_inventory.end(); it++) {
      if (*it == potion) {
         break;
      }
   }

   if (potion.get_type() == "Healing") {
      current_health += potion.get_strength();
      p_inventory.erase(it);
   }
   else if (potion.get_type() == "Boosting") {
      max_health += potion.get_strength();
      current_health = max_health;
      p_inventory.erase(it);
   }
   else if (potion.get_type() == "Attack") {
      attack += potion.get_strength();
      p_inventory.erase(it);
   }
   else if (potion.get_type() == "Defense") {
      defense += potion.get_strength();
      p_inventory.erase(it);
   }
   else {
      std::string error_str = "Error: Invalid potion passed to player.use_potion().\n";
      error_str += "Invalid potion.view_item():\n";
      error_str += potion.view_item();
      throw std::invalid_argument(error_str);
   }
}

// -----------------------------------------------------------------------------
// FRIEND FUNCTIONS ------------------------------------------------------------

// Uses the player's attack value and the enemy's defense value to calculate the damage dealth to the enemy.
// Returns the damage dealt.
int attack_enemy(const Player& player, Enemy& enemy) {
   int damage = player.get_attack() - enemy.get_defense();
   if (damage <= 0) {
      damage = 1;
   }
   enemy.set_health(enemy.get_health() - damage);
   if (enemy.get_health() < 0) {
      enemy.set_health(0);
   }
   return damage;
}

// -----------------------------------------------------------------------------