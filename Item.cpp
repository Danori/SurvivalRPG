#include <cstdlib>
#include "Item.h"

// CONSTRUCTORS ----------------------------------------------------------------

// Random generation constructor.
Item::Item(const int& day) {
   int rand_value = day * 3;
   int variability = rand() % day;
   rand_value += variability;
   value = rand_value;
   set_prefix("");
   set_suffix("");
}

// Saved playthrough constructor if input files are read in.
Item::Item(const int& value, const std::string& prefix, const std::string& suffix) {
   set_value(value);
   set_prefix(prefix);
   set_suffix(suffix);
}

// -----------------------------------------------------------------------------
// ACCESSORS -------------------------------------------------------------------

int Item::get_value() const {
   return value;
}

std::string Item::get_prefix() const {
   return prefix;
}

std::string Item::get_suffix() const {
   return suffix;
}

// -----------------------------------------------------------------------------
// MUTATORS --------------------------------------------------------------------

void Item::set_value(const int& value) {
   this->value = value;
}

void Item::set_prefix(const std::string& prefix) {
   this->prefix = prefix;
}

void Item::set_suffix(const std::string& suffix) {
   this->suffix = suffix;
}

// -----------------------------------------------------------------------------