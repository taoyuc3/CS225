// Animal.cpp
#include "Animal.h"
#include <string>
#include <iostream>
using namespace std;


Animal::Animal(){
  type_ = "cat";
  food_ = "fish";
}

Animal::Animal(string type, string food){
  type_ = type;
  food_ = food;

}

string Animal::getType(){
  return type_;
}

void Animal::setType(string t){
  type_ = t;
}

string Animal::getFood(){
  return food_;
}

void Animal::setFood(string f){
  food_ = f;
}

string Animal::print(){
  return "I am a"+type_;
}
