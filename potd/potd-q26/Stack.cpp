#include "Stack.h"
using namespace std;

// `int size()` - returns the number of elements in the stack (0 if empty)
int Stack::size() const {
  return size_;
}

// `bool isEmpty()` - returns if the list has no elements, else false
bool Stack::isEmpty() const {
  if(size_ == 0){
    return true;
  }else{
    return false;
  }
}

// `void push(int val)` - pushes an item to the stack in O(1) time
void Stack::push(int value) {
  mystack.push_back(value);
  size_++;
}

// `int pop()` - removes an item off the stack and returns the value in O(1) time
int Stack::pop() {
  if(size_ == 0){
    return -1;
  }
    int topdata = mystack.back();
    mystack.pop_back();
    size_--;

  return topdata;
}
