/**
 * @file list.cpp
 * Doubly Linked List (MP 3).
 */

template <class T>
List<T>::List() {
  // @TODO: graded in MP3.1
    head_ = NULL;
    tail_ = NULL;
    length_ = 0;
}

/**
 * Returns a ListIterator with a position at the beginning of
 * the List.
 */
template <typename T>
typename List<T>::ListIterator List<T>::begin() const {
  // @TODO: graded in MP3.1
  return List<T>::ListIterator(head_);
}

/**
 * Returns a ListIterator one past the end of the List.
 */
template <typename T>
typename List<T>::ListIterator List<T>::end() const {
  // @TODO: graded in MP3.1
  return List<T>::ListIterator(tail_->next);
}


/**
 * Destroys all dynamically allocated memory associated with the current
 * List class.
 */
template <typename T>
void List<T>::_destroy() {
  /// @todo Graded in MP3.1
  ListNode* curr = head_;
  ListNode* temp;
  if(curr == NULL){
    return;
  }
  while(curr != NULL){
    ListNode* temp = curr->next;
    delete curr;
    curr = temp;
  }
  head_ = NULL;
  tail_ = NULL;
}

/**
 * Inserts a new node at the front of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <typename T>
void List<T>::insertFront(T const & ndata) {
  /// @todo Graded in MP3.1
  ListNode * newNode = new ListNode(ndata);
  newNode -> next = head_;
  newNode -> prev = NULL;

  if (head_ != NULL) {
    head_ -> prev = newNode;
  }
  if (tail_ == NULL) {
    tail_ = newNode;
  }
  head_ = newNode;
  length_++;
}

/**
 * Inserts a new node at the back of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <typename T>
void List<T>::insertBack(const T & ndata) {
  /// @todo Graded in MP3.1
  ListNode * temp = new ListNode(ndata);
  temp->prev = tail_;
  temp->next = NULL;
  if(head_ == NULL){
    head_ = temp;
  }
  if(head_ -> next == NULL){
    head_->next = temp;
    tail_ = temp;
    temp->next = NULL;
  }
  if(tail_ != NULL){
    tail_ -> next = temp;
  }

  tail_ = temp;
  // delete temp;
  length_++;
}

/**
 * Helper function to split a sequence of linked memory at the node
 * splitPoint steps **after** start. In other words, it should disconnect
 * the sequence of linked memory after the given number of nodes, and
 * return a pointer to the starting node of the new sequence of linked
 * memory.
 *
 * This function **SHOULD NOT** create **ANY** new List or ListNode objects!
 *
 * This function is also called by the public split() function located in
 * List-given.hpp
 *
 * @param start The node to start from.
 * @param splitPoint The number of steps to walk before splitting.
 * @return The starting node of the sequence that was split off.
 */
template <typename T>
typename List<T>::ListNode * List<T>::split(ListNode * start, int splitPoint) {
  /// @todo Graded in MP3.1
  // ListNode* temp;
  if(splitPoint == 0){
    return start;
  }
  if(splitPoint > length_){
    return NULL;
  }
  if(start == NULL){
    return NULL;
  }
  ListNode * curr = start;
  for(int i = 0; (i < (splitPoint-1)) && (curr != NULL); i++){
    if(curr->next!= NULL){
    curr = curr->next;
    }
  }

  if (curr != NULL) {
      curr = curr -> next;
      tail_ = curr->prev;
      curr->prev->next = NULL;
      curr->prev = NULL;
      return curr;
  }

  return NULL;
}

/**
  * Modifies List using the rules for a TripleRotate.
  *
  * This function will to a wrapped rotation to the left on every three
  * elements in the list starting for the first three elements. If the
  * end of the list has a set of 1 or 2 elements, no rotation all be done
  * on the last 1 or 2 elements.
  *
  * You may NOT allocate ANY new ListNodes!
  */
template <typename T>
void List<T>::tripleRotate(){
  // @todo Graded in MP3.1
  if(head_ == NULL || head_->next == NULL){
    return;
  }
  if(length_ < 3){
    return;
  }
  ListNode * temp = head_;
  ListNode * temp2 = temp->next;
  ListNode * temp3 = temp2->next;
  ListNode * newcurr = temp3->next;

    temp->next = newcurr;
    temp3->next = temp;
    head_ = temp2;

  ListNode * prelast = temp;
    temp = temp->next;
    temp2 = temp->next;
    temp3 = temp2->next;
    newcurr = temp3->next;

    int count = 3;

  while(count+2 < length_ ){
      if(newcurr!= NULL){
        temp->next = newcurr;
        temp3->next = temp;
        prelast->next = temp2;

        prelast = temp;
        temp2 = temp->next;
        temp3 = temp2->next;
        newcurr = temp3->next;
      }else{
        temp->next = NULL;
        temp3->next = temp;
        prelast->next = temp2;
        return;
      }
    count = count + 3;
  }
  return;
}

/**
 * Reverses the current List.
 */

template <typename T>
void List<T>::reverse() {
  reverse(head_, tail_);
}

/**
 * Helper function to reverse a sequence of linked memory inside a List,
 * starting at startPoint and ending at endPoint. You are responsible for
 * updating startPoint and endPoint to point to the new starting and ending
 * points of the rearranged sequence of linked memory in question.
 *
 * @param startPoint A pointer reference to the first node in the sequence
 *  to be reversed.
 * @param endPoint A pointer reference to the last node in the sequence to
 *  be reversed.
 */
template <typename T>
void List<T>::reverse(ListNode *& startPoint, ListNode *& endPoint) {
  // @todo Graded in MP3.2
    if(startPoint == endPoint){
      return;
    }
    if(startPoint == NULL && endPoint == NULL){
      return;
    }

    ListNode * left_end = startPoint->prev;
    ListNode * right_end = endPoint->next;
    ListNode * temp = startPoint;
    ListNode * temp2 = startPoint;
    ListNode * oldstart = startPoint;
    ListNode * oldend = endPoint;

  while(temp != endPoint){
    temp2 = temp->prev;
    temp->prev = temp->next;
    temp->next = temp2;
    temp = temp-> prev;
  }
    startPoint->next = right_end;
    temp->next = temp->prev;
    temp->prev = left_end;
    if(right_end != NULL){
      right_end->prev = startPoint;
    }else{
      tail_ = startPoint;
    }
    if(left_end!= NULL){
      left_end->next = endPoint;
    }else{
      head_ = endPoint;
    }
  startPoint = oldend;
  endPoint = oldstart;
}
//
/**
 * Reverses blocks of size n in the current List. You should use your
 * reverse( ListNode * &, ListNode * & ) helper function in this method!
 *
 * @param n The size of the blocks in the List to be reversed.
 */
template <typename T>
void List<T>::reverseNth(int n) {
  /// @todo Graded in MP3.2
  if(n <= 1 || length_ <= 1){
    return;
  }
  if(n >= length_){
    reverse();
    return;
  }
  if(head_ == NULL){
    return;
  }
  ListNode * startptr = head_;
  ListNode * endptr = head_;
  while(startptr != NULL){
      for(int i = 0; i < n-1; i++){
         if(endptr->next !=NULL){
         endptr = endptr->next;
          }else{
            break;
          }
      }
    reverse(startptr, endptr);
    startptr = endptr->next;
    endptr = startptr;
  }
}

/**
 * Merges the given sorted list into the current sorted list.
 *
 * @param otherList List to be merged into the current list.
 */
template <typename T>
void List<T>::mergeWith(List<T> & otherList) {
    // set up the current list
    head_ = merge(head_, otherList.head_);
    tail_ = head_;

    // make sure there is a node in the new list
    if (tail_ != NULL) {
        while (tail_->next != NULL)
            tail_ = tail_->next;
    }
    length_ = length_ + otherList.length_;

    // empty out the parameter list
    otherList.head_ = NULL;
    otherList.tail_ = NULL;
    otherList.length_ = 0;
}

/**
 * Helper function to merge two **sorted** and **independent** sequences of
 * linked memory. The result should be a single sequence that is itself
 * sorted.
 *
 * This function **SHOULD NOT** create **ANY** new List objects.
 *
 * @param first The starting node of the first sequence.
 * @param second The starting node of the second sequence.
 * @return The starting node of the resulting, sorted sequence.
 */
template <typename T>
typename List<T>::ListNode * List<T>::merge(ListNode * first, ListNode* second) {
  /// @todo Graded in MP3.2
  if(first != NULL && second == NULL){
    return first;
  }
  if(first == NULL && second != NULL){
    return second;
  }
  if(first == NULL && second == NULL){
    return NULL;
  }

  ListNode * curr1 = first;
  ListNode * curr2 = second;
  ListNode * temp1 = first->next;
  ListNode * temp2 = second->next;
  ListNode * newhead = NULL;

  if(second->data < first->data){
    newhead = second;
    second = first;
    first = newhead;
    first->prev = NULL;
    curr1 = first;
    curr2 = second;
  }
  while(curr2 != NULL){
      temp2 = curr2->next;
        while(curr1 != NULL){
          temp1 = curr1->next;
          if(curr2->data < curr1->data){
            curr2->next = curr1;
            curr2->prev = curr1->prev;
            curr1->prev->next = curr2;
            curr1->prev = curr2;
            break;
          }
          if(temp1 == NULL){
            curr2->prev = curr1;
            curr1->next = curr2;
            break;
          }
          curr1 = temp1;
        }
      if(curr1->next == curr2){
          break;
      }
        curr2 = temp2;
  }
    return first;
}

/**
 * Sorts a chain of linked memory given a start node and a size.
 * This is the recursive helper for the Mergesort algorithm (i.e., this is
 * the divide-and-conquer step).
 *
 * Called by the public sort function in List-given.hpp
 *
 * @param start Starting point of the chain.
 * @param chainLength Size of the chain to be sorted.
 * @return A pointer to the beginning of the now sorted chain.
 */
template <typename T>
typename List<T>::ListNode* List<T>::mergesort(ListNode * start, int chainLength) {
  /// @todo Graded in MP3.2
  if(chainLength <= 1){
    return start;
  }
  ListNode * temp = NULL;
  ListNode * first = NULL;
  ListNode * second = NULL;
  int splitLength = chainLength/2;
  temp = split(start, splitLength);
  first = mergesort(start, splitLength);
  second = mergesort(temp, chainLength - splitLength);
  return merge(first, second);
}




/* discarded code for tripleRotate
  for(int i = 0; i<3 && temp!= NULL; i++){
    temp = temp->next;
  }
  temp2 = temp;
  temp = head_;
  head_ = head_->next;

  temp2 = temp;
  temp = head_;
  head_ = head_->next;

  temp = curr;
  curr->next = temp->next->next;
  temp->prev->next = temp->next->next;
  temp->next->next = curr;
  curr = temp;
    while(curr->next != NULL && curr->next->next != NULL){
      if(temp->next->next != NULL){
      curr = temp->next->next;
      temp->prev->next = curr;
      temp->next->next = temp->prev;
      temp->prev = temp;
      temp = curr->next;
    }else{
      temp->prev->next = NULL;
      temp->next->next = temp->prev;
      temp->prev = temp;
      // curr = NULL;
      // curr->next = NULL;
    }
  }
*/

//another algorithm works for reverse, but not for reverseNth

/*
if(startPoint == endPoint || startPoint == NULL || startPoint->next == NULL){
  return;
}
ListNode * start = startPoint;
ListNode * end = endPoint;
ListNode * newstart = startPoint-> next;
ListNode * temp = startPoint -> next;
ListNode * temp2 = startPoint;
int count = 0;
while(count+1 < length_){
  if(start == startPoint){
    start->next = NULL;
    start = newstart;
    newstart = temp->next;
    temp = newstart;
    count =count+1;
  }else{
    start->next = temp2; //could have segfault
    temp2 = start;
    start = newstart;
    newstart = temp->next;
    temp = newstart;
    count = count+1;
  }
}
  endPoint = startPoint;
  startPoint = start;
  startPoint->next = temp2;
  head_ = startPoint;
  tail_ = endPoint;
*/

//another algorithm for reverseNth
/*
if(n <= 1 || length_ <= 1){
  return;
}
if(n >= length_){
  reverse();
  return;
}

ListNode * curr = head_;
ListNode * temp2 = head_;
ListNode * temp3 = head_;
ListNode * faraway = nullptr;

ListNode * start = head_;
ListNode * end = head_;

ListNode * track = nullptr;

int count = 0;
 while(count + n <= length_){

   temp3 = temp2;

   for(int i = 1; i < n; i++){
     temp2 = temp2->next;
   }
   for(int j = 0; j < n; j++){
     curr = curr->next;
   }

   faraway = curr;

   for(int k = 1; k < n; k++){
     if(faraway == tail_){
       break;
     }
     faraway = faraway->next;
   }

   if(count == 0){
     start = head_;
     head_ = temp2;
     end = temp2;
     reverse(start, end);
     end->next = faraway;
     temp2 = curr;

     track = temp2;
     temp3 = track;
   }else{
   start = temp3;
   end = temp2;
   reverse(start, end);
   end->next = faraway;
   temp2 = curr;

   track = temp2;
   temp3 = track;
 }
   count = count + n;
   if(faraway == tail_)
     break;

}

reverse(curr,tail_);
tail_->next = NULL;
*/
