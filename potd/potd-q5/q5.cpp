// your code here
#include "q5.h"
#include "Food.h"
void increase_quantity(Food * f1){
  int temp = f1->get_quantity();
  f1->set_quantity(temp+1);
}
