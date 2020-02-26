#include "potd.h"
#include <iostream>
using namespace std;

void insertSorted(Node **head, Node *insert) {
  // your code here!
  //
  // Node *temp;
  // Node *cur;
  // cur = *head;

  // if(*head == NULL ){
  //   *head = insert;
  //   insert->next_ = NULL;
  // }
  //
  // Node *cur;
  // cur = *head;

  // while(cur != NULL)
  // {
  //   if(cur->data_<=insert->data_ && (cur->next_)->data_ >=cur->data_)
  //   {
  //     insert->next_ = cur->next_;
  //   }
  //
  // }
  // cur->next_ = insert;
if(*head==NULL)
{
  *head=insert;
  insert->next_ = NULL;
}

// Node *cur = *head;
//
//     if(insert->data_>cur->data_)
//     {
//       cur->next_=insert;
//       insert->next_=NULL;
//     }

Node *cur1 = *head;

    if(insert->data_<cur1->data_)
    {
      *head = insert;
      insert->next_= cur1;
    }

Node *temp = *head;

while(temp->next_!=NULL)
{
  if(insert->data_ > temp->next_->data_)
    temp = temp->next_;

    Node n;
    n = *temp;
    // insert->next_ = temp->next_;
    // temp->next_ = insert;
    temp->next_ = insert;
    insert->next_ = n.next_;

    return;

}

//insert nine
Node *cur2 = *head;
cur2->next_ = insert;
insert->next_ = NULL;
// while(cur2->next_!=NULL)
// {
//   if(insert->data_ > cur2->next_->data_)
//         {
//           insert->next_ = cur2->next_;
//           cur2->next_ = NULL;
//           return;
//         }
//
// }

}
