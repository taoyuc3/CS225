#include "binarytree.h"
#include <iostream>
#include <cstdlib>

const string RED_TEXT = "\033[1;31m";
const string GREEN_TEXT = "\033[1;32m";
const string RESET_TEXT = "\033[0m";

void print_pass(string message) {
  cout<<GREEN_TEXT<<"TEST PASSED"<<RESET_TEXT<<": "<<message<<endl;
}

void print_fail(string message) {
  cout<<RED_TEXT<<"TEST FAILED"<<RESET_TEXT<<": "<<message<<endl;
  exit(1);
}


int main() {
  srand(225);
  int num;

  // Example #1
  BinaryTree<int> t1;
  t1.insert(3);
  t1.insert(2);
  t1.insert(4);

  num = t1.numNodes();
  if (num == 3) { print_pass("Example #1 passed (num == 3)"); }
  else {
    cout<<"Returned value: "<<num<<endl;
    cout<<"Expected: 3"<<endl;
    print_fail("Example #1 failed (num != 3)");
  }


  // Example #2
  BinaryTree<int> t2;
  t2.insert(2);
  t2.insert(1);
  t2.insert(3);
  t2.insert(6);

  num = t2.numNodes();
  if (num == 4) { print_pass("Example #2 passed (num == 4)"); }
  else {
    cout<<"Returned value: "<<num<<endl;
    cout<<"Expected: 4"<<endl;
    print_fail("Example #2 failed (sum != 4)");
  }


  return 0;
}
