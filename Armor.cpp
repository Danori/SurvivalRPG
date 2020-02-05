#include <cstdlib>
#include "Armor.h"

// CONSTRUCTORS ----------------------------------------------------------------

// Random generation constructor.
Armor::Armor(const int& day) :
Item(day) {
   int rand_def = day * 2;
   int variability = rand() % (day * 3);
   rand_def += variability;
   defense_value = rand_def;
   value += defense_value * 8;

   if (defense_value <= 10) {
      set_prefix("Rusted");
   }
   else if (defense_value > 10 && defense_value <= 50) {
      set_prefix("Studded");
   }
   else if (defense_value > 50 && defense_value <= 100) {
      set_prefix("Plated");
   }
   else if (defense_value > 100 && defense_value <= 200) {
      set_prefix("Layered");
   }
   else if (defense_value > 200 && defense_value <= 300) {
      set_prefix("Thickened");
   }
   else if (defense_value > 300 && defense_value <= 500) {
      set_prefix("Reinforced");
   }
   else if (defense_value > 500) {
      set_prefix("Immaculate");
   }

   const int num_armor_types = 7;
   int armor_type = rand() % num_armor_types;
   switch (armor_type) {
   case 0:
      set_type("Breastplate");
      break;
   case 1:
      set_type("Hauberk");
      break;
   case 2:
      set_type("Mail Armor");
      break;
   case 3:
      set_type("Brigandine");
      break;
   case 4:
      set_type("Ring Armor");
      break;
   case 5:
      set_type("Scale Armor");
      break;
   case 6:
      set_type("Plate Armor");
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
Armor::Armor(const std::string& prefix, const std::string& type, const std::string& suffix,
const int& value, const int& defense_value, bool equipped) :
Item(value, prefix, suffix) {
   set_defense_value(defense_value);
   set_type(type);
   set_equipped(equipped);
}

// -----------------------------------------------------------------------------
// ACCESSORS -------------------------------------------------------------------

int Armor::get_defense_value() const {
   return defense_value;
}

std::string Armor::get_type() const {
   return type;
}

bool Armor::is_equipped() const {
   return equipped;
}

// -----------------------------------------------------------------------------
// MUTATORS --------------------------------------------------------------------

void Armor::set_defense_value(const int& defense_value) {
   this->defense_value = defense_value;
}

void Armor::set_type(const std::string& type) {
   this->type = type;
}

void Armor::set_equipped(const bool& equipped) {
   this->equipped = equipped;
}

// -----------------------------------------------------------------------------
// PUBLIC MEMBER FUNCTIONS -----------------------------------------------------

// Returns a string representation of the item for output.
std::string Armor::view_item() const {
   std::string str = "";
   str += "Armor:    " + prefix + " " + type + " " + suffix;
   if (equipped) {
      str += " (EQUIPPED)";
   }
   str += "\nDefense:  " + std::to_string(defense_value) + "\n";
   str += "Value:    " + std::to_string(value) +"\n";
   return str;
}

// -----------------------------------------------------------------------------