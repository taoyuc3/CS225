// Animal.h
#pragma once
#include <string>
#include <iostream>
using namespace std;

class Animal{
public:
  string food_;

  Animal();
  Animal(string type, string food);

  string getType();
  void setType(string t);
  string getFood();
  void setFood(string f);

  string print();

private:
  string type_;
};
