#ifndef WEAPON_H
#define WEAPON_H

#include <string>
#include "Item.h"

class Weapon : public Item {
private:
   int attack_value;
   std::string type;
   bool equipped;
public:
   // Random Generation Constructor.
   Weapon(const int& day);
   // Prior Defined Weapon Constructor. Used for weapons between saves.
   Weapon(const std::string& prefix = "", const std::string& type = "", const std::string& suffix = "",
   const int& value = 0, const int& attack_value = 0, bool equipped = false);

   int get_attack_value() const;
   std::string get_type() const;
   bool is_equipped() const;

   void set_attack_value(const int& attack_value);
   void set_type(const std::string& type);
   void set_equipped(const bool& equipped);

   std::string view_item() const;
};

#endif // WEAPON_H
