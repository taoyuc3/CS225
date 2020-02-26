#include "Node.h"

/** Create a new node and add it to the list, while keeping the list sorted.
*/
Node *insertSorted(Node *first, int data) {
  // your code here

  // first->0->1->2-NULL
  // second->2->3->4->NULL
  // out->0->1->2->3->4->NULL
  // Node *temp = new Node;
  // Node *head = new Node;
  // head = first;

    Node *t = first;


//case one
  if(first == NULL){
    Node *temp = new Node();
    temp->data_ = data;
    temp->next_ = NULL;
    return temp;
  }
//case two
  if(first->data_ > data){
    Node *temp = new Node();
    temp->data_ = data;
    temp->next_ = NULL;
    // first = temp;
    // first->next_ = head;
    temp->next_ = first;
    return temp;
  }
//case three

  //   while(first!= NULL){
  //   if(first->data_ == data){
  //     return first;
  //   }
  //   first = first->next_;
  // }

  if(first->data_ == data){
    return first;
  }

//case four
int i = 0;
    while(t != NULL && data != t->data_ && i==0){
      if(t->next_ != NULL){
        if(data < t->next_->data_){
          Node *out = new Node();
          out->data_ = data;
          out->next_ = NULL;
          out->next_ = t->next_;
          t->next_ = out;
          i = 1;
        }
      }else{
        Node* out = new Node();
        out->data_ = data;
        out->next_ = NULL;
        t->next_ = out;
        i =  1;
      }
      t = t->next_;
    }

  //   if(data == temp3->data_){
  //     return first;
  //   }
  //   temp3 = temp3->next_;
  // }
  //
  //   Node *temp4 = new Node();
  //   temp4->data_ = data;
  //   temp4->next_ = NULL;
  //   temp4->next_ = temp3->next_;
  //   temp3->next_ = temp4;
  return first;
}

//case five

/** Creates a new list (containing new nodes, allocated on the heap)
	that contains the set union of the values in both lists.
*/
Node *listUnion(Node *first, Node *second) {
    Node *out = NULL;

    while (first != NULL) {
        // your code here
        // hint: call insertSorted and update l1
        out = insertSorted(out, first->data_);
        first = first->next_;
    }

    while (second != NULL) {
        // your code here
        out = insertSorted(out, second->data_);
        second = second->next_;
    }

    return out;
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
