// Pet.cpp
#include "Pet.h"
#include "Animal.h"
// #include "Animal.h"
#include <iostream>
#include <string>
using namespace std;

Pet::Pet(): Animal(), name_("Fluffy"), owner_name_("Cinda"){
  // type_ = "cat";
  // food = "fish";
  // name_ = "Fluffy";
  // owner_name_ = "Cinda";
}

Pet::Pet(string type, string food, string name, string owner_name)
  : Animal(type, food),name_(name),owner_name_(owner_name)
{}


void Pet::setType(string type){
  // type_ = type;
  Animal::setType(type);
}

string Pet::getType(){
  return Animal::getType();
}

void Pet::setFood(string food){
  // food_ = food;
  Animal::setFood(food);
}

string Pet::getFood(){
  // return food_;
  return Animal::getFood();
}

void Pet::setName(string name){
  name_ = name;
}

string Pet::getName(){
  return name_;
}

void Pet::setOwnerName(string owner_name){
  owner_name_ = owner_name;
}

string Pet::getOwnerName(){
  return owner_name_;
}

string Pet::print(){
  return "My name is " + name_;
}
