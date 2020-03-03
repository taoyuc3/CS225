#include "Queue.h"


// `int size()` - returns the number of elements in the stack (0 if empty)


int Queue::size() const {
  return mySize;
}

// `bool isEmpty()` - returns if the list has no elements, else false
bool Queue::isEmpty() const {
  return mySize==0 ? true : false;
}

// `void enqueue(int val)` - enqueue an item to the queue in O(1) time
void Queue::enqueue(int value) {
  myQueue.push_back(value);
  ++mySize;

}

// `int dequeue()` - removes an item off the queue and returns the value in O(1) time
int Queue::dequeue() {
  int ans = myQueue.front();
  myQueue.pop_front();
  --mySize;
  return ans;
}
