// Pet.h
#pragma once
#include "Animal.h"
// #include "Animal.cpp"
#include <string>
// #include <iostream>
using namespace std;

class Pet : public Animal{
private:
  string name_;
  string owner_name_;

public:
  Pet();
  Pet(string type, string food, string name, string owner_name);

  void  setType(string type);
  string getType();

  void  setFood(string food);
  string getFood();

  void  setName(string name);
  string getName();

  void setOwnerName(string owner_name);
  string getOwnerName();

  string print();
};
