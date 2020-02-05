#ifndef ITEM_H
#define ITEM_H

#include <string>

class Item {
protected:
   int value;
   std::string prefix;
   std::string suffix;
public:
   Item(const int& day);
   Item(const int& value, const std::string& prefix, const std::string& suffix);

   int get_value() const;
   std::string get_prefix() const;
   std::string get_suffix() const;

   void set_value(const int& value);
   void set_prefix(const std::string& prefix);
   void set_suffix(const std::string& suffix);

   virtual std::string view_item() const = 0;
};

#endif // ITEM_H