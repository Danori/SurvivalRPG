#ifndef POTION_H
#define POTION_H

#include <string>
#include "Item.h"

class Potion : public Item {
private:
   std::string type;
   std::string description;
   int strength;
public:
   Potion(const int& day);
   Potion(const std::string& type = "", const std::string& description = "", const int& value = 0, const int& strength = 0);

   std::string get_type() const;
   std::string get_description() const;
   int get_strength() const;

   void set_type(const std::string& type);
   void set_description(const std::string& description);
   void set_strength(const int& strength);

   std::string view_item() const;

   bool operator==(const Potion& r_potion);
};

#endif // POTION_H