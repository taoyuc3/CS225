#include "Node.h"

using namespace std;

Node *listIntersection(Node *first, Node *second) {
  // your code here
if(first == NULL || second == NULL){
     return NULL;
}

  Node *ans = new Node;
  ans->next_ = NULL;
  // Node *newhead = NULL;
  Node *temp1 =first;
  Node *temp2 = second;
  Node *temp = ans;
  int i = 0;
  bool out = false;


  while(temp1 != NULL){
      temp2 = second;
      while(temp2 != NULL){
        if(temp1->data_ == temp2->data_){
          if(out == false){
            ans->data_ = temp1->data_;
            temp2 = temp2->next_;
            out = true;
            continue;
        }
          while(temp != NULL){
            if(temp1->data_ == temp2->data_){
              i = 1;
              break;
          }
          temp =temp->next_;
        }
          if(i==1){
            Node*temp3 = new Node;
            temp3->data_ = temp1->data_;
            temp3->next_ = ans;
            ans = temp3;
          }
        }
      temp2 = temp2->next_;
    }
    temp1 = temp1 -> next_;

  //       temp2 = temp2->next_;
  //     }
  //   temp1 = temp1->next_;

    }
      return ans;
  // return newhead;
}

Node::Node() {
    numNodes++;
}

Node::Node(Node &other) {
    this->data_ = other.data_;
    this->next_ = other.next_;
    numNodes++;
}

Node::~Node() {
    numNodes--;
}

int Node::numNodes = 0;
