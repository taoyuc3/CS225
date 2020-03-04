#pragma once

#include <cstddef>
#include <stack>
#include <list>


using namespace std;

class Stack {
public:
  int size() const;
  bool isEmpty() const;
  void push(int value);
  int pop();
  int size_ = 0;
  list<int> mystack;
};
