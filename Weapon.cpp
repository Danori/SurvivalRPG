#include <cstdlib>
#include "Weapon.h"

// CONSTRUCTORS ----------------------------------------------------------------

// Random generation constructor.
Weapon::Weapon(const int& day) :
Item(day) {
   int rand_atk = day * 5;
   int variability = rand() % (day * 5);
   rand_atk += variability;
   attack_value = rand_atk;
   value += attack_value * 4;

   if (attack_value <= 10) {
      set_prefix("Rusted");
   }
   else if (attack_value > 10 && attack_value <= 50) {
      set_prefix("Dull");
   }
   else if (attack_value > 50 && attack_value <= 100) {
      set_prefix("Sharpened");
   }
   else if (attack_value > 100 && attack_value <= 200) {
      set_prefix("Serrated");
   }
   else if (attack_value > 200 && attack_value <= 300) {
      set_prefix("Cruel");
   }
   else if (attack_value > 300 && attack_value <= 500) {
      set_prefix("Merciless");
   }
   else if (attack_value > 500) {
      set_prefix("Immaculate");
   }

   const int num_weapon_types = 7;
   int weapon_type = rand() % num_weapon_types;
   switch (weapon_type) {
   case 0:
      set_type("Sword");
      break;
   case 1:
      set_type("Axe");
      break;
   case 2:
      set_type("Claw");
      break;
   case 3:
      set_type("Dagger");
      break;
   case 4:
      set_type("Sceptre");
      break;
   case 5:
      set_type("Mace");
      break;
   case 6:
      set_type("Staff");
      break;
   }

   const int num_suffixes = 7;
   int rand_suffix = rand() % num_suffixes;
   switch (rand_suffix) {
   case 0:
      set_suffix("of Sundering");
      break;
   case 1:
      set_suffix("of Reckoning");
      break;
   case 2:
      set_suffix("of the Wind");
      break;
   case 3:
      set_suffix("of the Earth");
      break;
   case 4:
      set_suffix("of the Flame");
      break;
   case 5:
      set_suffix("of the Seas");
      break;
   case 6:
      set_suffix("of Agony");
      break;
   }

   equipped = false;
}

// Saved playthrough constructor if input files are read in.
Weapon::Weapon(const std::string& prefix, const std::string& type, const std::string& suffix,
const int& value, const int& attack_value, bool equipped) :
Item(value, prefix, suffix) {
   set_attack_value(attack_value);
   set_type(type);
   set_equipped(equipped);

}

// -----------------------------------------------------------------------------
// ACCESSORS -------------------------------------------------------------------

int Weapon::get_attack_value() const {
   return attack_value;
}

std::string Weapon::get_type() const {
   return type;
}

bool Weapon::is_equipped() const {
   return equipped;
}

// -----------------------------------------------------------------------------
// MUTATORS --------------------------------------------------------------------

void Weapon::set_attack_value(const int& attack_value) {
   this->attack_value = attack_value;
}

void Weapon::set_type(const std::string& type) {
   this->type = type;
}

void Weapon::set_equipped(const bool& equipped) {
   this->equipped = equipped;
}

// -----------------------------------------------------------------------------
// PUBLIC MEMBER FUNCTIONS -----------------------------------------------------

// Returns a string representation of the item for output.
std::string Weapon::view_item() const {
   std::string str = "";
   str += "Weapon:   " + prefix + " " + type + " " + suffix;
   if (equipped) {
      str += " (EQUIPPED)";
   }
   str += "\nAttack:   " + std::to_string(attack_value) + "\n";
   str += "Value:    " + std::to_string(value) + "\n";
   return str;
}

// -----------------------------------------------------------------------------