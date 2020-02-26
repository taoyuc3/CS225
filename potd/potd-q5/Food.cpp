// Your code here
#include "Food.h"
#include <string>
using namespace std;

// using namespace std;
Food::Food(){
  name_ = "Apples";
  quantity_ = 1;
}

void Food::set_name(string name){
  name_=name;
}
string Food::get_name(){
  return name_;
}
void Food::set_quantity(int quantity){
  quantity_=quantity;

}

int Food::get_quantity(){
  return quantity_;
}

    // void set_name(char newname){
    //   name_ = newname;
    // }
    // char get_name(){
    //   return name_;
    // }
    // void set_quantity(int quantity){
    //   quantity_=quantity;
    // }
    // int get_quantity(){
    //   return quantity_;
    // }
