// your code here
#include "Food.h"
#include "q5.h"
#include <iostream>
#include <string>
#include <cstring>
using namespace std;

int main(){
  Food * object = new Food();
  // Increase *f1 = f.set_quantity(5);
  // Increase f2 = increase_quantity(f1)
  // f.set_name("Apples");
  // default = f.set_quantity(5);
  cout<<"You have "<<object->get_quantity()<<" "<<object->get_name()<<endl;
  increase_quantity(object);
  cout<<"You have "<<object->get_quantity()<<" "<<object->get_name()<<endl;
  delete object;
  return 0;
}
