#include "potd.h"
#include <iostream>
using namespace std;

int main() {
  // Test 1: An empty list
  Node * head = NULL;
  cout << stringList(head) << endl;

  // Test 2: A list with exactly one node
  Node * head1 = new Node;
  head1->data_ = 100;
  head1->next_ = NULL;
  cout << stringList(head1) << endl;

  // Test 3: A list with more than one node
  Node *head2 = new Node;
  Node *node1 = new Node;
  Node *node2 = new Node;

    head2->data_ = 100;
    head2->next_ = node1;
    node1->data_ = 200;
    node1->next_ = node2;
    node2->data_ = 300;
    node2->next_ = NULL;

  //
  //   head2->data_ = 100;
  //   // node1 = head2->next_;
  //   node1->data_ = 200;
  //   node1->next_ = NULL;
  //
  cout << stringList(head2) << endl;
  return 0;
}
