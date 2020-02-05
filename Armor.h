#ifndef ARMOR_H
#define ARMOR_H

#include <string>
#include "Item.h"

class Armor : public Item {
private:
   int defense_value;
   std::string type;
   bool equipped;
public:
   Armor(const int& day);
   Armor(const std::string& prefix = "", const std::string& type = "", const std::string& suffix = "",
   const int& value = 0, const int& defense_value = 0, bool equipped = false);

   int get_defense_value() const;
   std::string get_type() const;
   bool is_equipped() const;

   void set_defense_value(const int& defense_value);
   void set_type(const std::string& type);
   void set_equipped(const bool& equipped);

   std::string view_item() const;
};

#endif // ARMOR_H

