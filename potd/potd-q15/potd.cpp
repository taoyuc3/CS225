#include "potd.h"
#include <iostream>
#include <string>

using namespace std;

string stringList(Node *head) {
    // your code here!
    Node * ptr = head;
    if(ptr == NULL){
      return "Empty list";
    }

    int i = 0;
    string output;

    while(ptr != NULL)
    {
      output = output + "Node "+ to_string(i) + ": " + to_string(ptr->data_);
      ptr = ptr->next_;
      i++;
      if(ptr!=NULL){
        output = output + " -> ";
      }
    }
    return output;
}
