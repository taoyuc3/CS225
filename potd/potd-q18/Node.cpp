#include "Node.h"

void mergeList(Node *first, Node *second) {
  // your code here!

// first->0->2->4->null
// second->11->33->55->null
// 0->11->2->33->4->55->null

// first->0->2->null
// second->11->33->33->44->null
// 0->11->2->33->33->44->null

if(first == NULL || second == NULL){
return;
}

Node cur1 = *first;
Node cur2 = *second;

first->next_ = second;

if(cur1.next_ != NULL){
second->next_ = cur1.next_;
}

first = cur1.next_;
second = cur2.next_;
mergeList(first, second);

}

Node::Node() {
    numNodes++;
}

Node::Node(const Node &other) {
    this->data_ = other.data_;
    this->next_ = other.next_;
    numNodes++;
}

Node::~Node() {
    numNodes--;
}

int Node::numNodes = 0;
