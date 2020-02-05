#include <cstdlib>
#include "Potion.h"

// CONSTRUCTORS ----------------------------------------------------------------

// Random generation constructor.
Potion::Potion(const int& day) :
Item(day) {
   int rand_str = day * 4;
   int variability = rand() % day;
   rand_str += variability;
   strength = rand_str;
   value += strength;

   const int num_potion_types = 4;
   int potion_type = rand() % num_potion_types;
   switch (potion_type) {
   case 0:
      strength *= 6;
      set_type("Healing");
      set_description("Used to heal in combat.");
      break;
   case 1:
      value += (value * 2);
      set_type("Boosting");
      set_description("Used to heal in combat, and increases max health permanantly.");
      break;
   case 2:
      set_type("Attack");
      set_description("Increases the offensive capabilities of the user.");
      break;
   case 3:
      strength /= 2;
      set_type("Defense");
      set_description("Increases the defensive capabilities of the user.");
      break;
   }
}

// Saved playthrough constructor if input files are read in.
Potion::Potion(const std::string& type, const std::string& description, const int& value, const int& strength) :
Item(value, "", "") {
   set_type(type);
   set_description(description);
   set_strength(strength);
}

// -----------------------------------------------------------------------------
// ACCESSORS -------------------------------------------------------------------

std::string Potion::get_description() const {
   return description;
}

std::string Potion::get_type() const {
   return type;
}

int Potion::get_strength() const {
   return strength;
}

// -----------------------------------------------------------------------------
// MUTATORS --------------------------------------------------------------------

void Potion::set_description(const std::string& description) {
   this->description = description;
}

void Potion::set_type(const std::string& type) {
   this->type = type;
}

void Potion::set_strength(const int& strength) {
   this->strength = strength;
}

// -----------------------------------------------------------------------------
// PUBLIC MEMBER FUNCTIONS -----------------------------------------------------

// Returns a string representation of the item for output.
std::string Potion::view_item() const {
   std::string str = "";
   str += "Potion:   " + type + " Potion\n";
   str += "Use:      " + description + "\n";
   str += "Strength: " + std::to_string(strength) + "\n";
   str += "Value:    " + std::to_string(value) + "\n";
   return str;
}

// -----------------------------------------------------------------------------
// OPERATOR OVERLOADS ----------------------------------------------------------

// Compares two potions to see if they're equal based on type, strength, and value.
bool Potion::operator==(const Potion& r_potion) {
   return ((type == r_potion.get_type()) && (strength == r_potion.get_strength()) && (value == r_potion.get_value()));
}

// -----------------------------------------------------------------------------