// Your code here
#pragma once
#include <string>
using namespace std;

class Food{
public:
    void set_name(string name);
  string get_name();
    void set_quantity(int quantity);
    int get_quantity();
    Food();
private:
    string name_;
    int quantity_;
};
