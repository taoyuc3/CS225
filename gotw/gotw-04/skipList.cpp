/**
 * @file skipList_given.cpp
 * MP6, given functions
 *
 * @author
 *  Arman Tajback
 *  Jordi Paris Ferrer
 *  Wade Fagen-Ulmschneider
 *  Annie Kim
 */


#include "skipList.h"

/**
 * Default constructs the SkipList.
 * Uses two sentinel nodes, each initially of height 1
 */
SkipList::SkipList() {
    SkipNode* head_ = new SkipNode();
    SkipNode* tail_ = new SkipNode();

    head_->node_pointers[0].next = tail_;
    tail_->node_pointers[0].prev = head_;

    head_->key = INT_MIN;
    head_->value = 0;

    tail_->key = INT_MAX;
    tail_->value = 0;

    int list_height_ = 1;
    int length_ = 0;

    int probability_ = 50;
    int max_level_ = 5; 
}


/**
 * Constructs an empty list with the specified probability and max_level.
 */
SkipList::SkipList(int probability, int max_level) : SkipList() {
    probability_ = probability;
    max_level_ = max_level;
}


/**
 * Constructs the SkipList with specified probability and max_level,
 * and with one initial node, which is constructed with the provided values.
 */
SkipList::SkipList(int probability, int max_level, int key, int value) : SkipList(probability, max_level) {
    insert(key, value);      
}


/**
 * Copy constructs the current SkipList.
 */
SkipList::SkipList(const SkipList & other) {
    copy(other);
}


/**
 * The copy() helper method - used in the copy constructor and assignment= operator.
 */
void SkipList::copy(const SkipList & other) {
    head_ = NULL;
    tail_ = NULL;
    list_height_ = 1;
    length_ = other.length_;

    std::map<SkipNode*, SkipNode*> pointerMap;
    pointerMap[NULL] = NULL;

    SkipNode* curr = other.head_;

    // populate our map of old pointers to new pointers
    while (curr != NULL) {
        SkipNode * currCopy = new SkipNode(*curr);
        pointerMap[curr] = currCopy;

        if(head_ == NULL)
            head_ = currCopy;

        if(curr->node_pointers[0].next == NULL)
            tail_ = currCopy;

        curr = curr->node_pointers[0].next;
    }	

    curr = head_;

    // change all old pointers to new pointers
    while (curr != NULL)
    {
        for(auto & p : curr->node_pointers)
        {
            p.next = pointerMap[p.next];
            p.prev = pointerMap[p.prev];
        }

        curr = curr->node_pointers[0].next;
    }

    list_height_ = other.list_height_;
}


/**
 * Set up traverse to point to the node right before where we want to insert
 */
SkipNode* SkipList::findInsertionIdx(int key) {
    SkipNode * traverse = head_;
    int level = head_->node_pointers.size() - 1;

    while (traverse->node_pointers[0].next != tail_ && level >= 0) {
        int next_key = traverse->node_pointers[level].next->key;

        if (key < next_key) {
            level--;
            if (level < 0 ) { break; }
        } else  {
            traverse = traverse->node_pointers[level].next;
        }
    }

    return head_;
}


/**
 * Inserts a new node into the sorted order in the list, initialized with the provided values.
 * Will replace the value at key if it already exists
 */
void SkipList::insert(int key, int value) {
    SkipNode *temp = this->find(key);

    // If the SkipNode exists, the key exists in our list and the value for that key must
    // be updated to the new value.
    if (temp) {
        temp->value = value;
    }

    length_++;

    int new_node_level = levelGenerator();
    SkipNode * traverse = findInsertionIdx(key);
    int level = traverse->node_pointers.size();

    // expand head_ and tail_ to encompass the new height of the list, if needed
    for(int i = list_height_; i < std::max(this->list_height_, new_node_level); i++) {
        head_->node_pointers.push_back(SkipPointer());
        tail_->node_pointers.push_back(SkipPointer());
    }
     
    this->list_height_ = std::max(this->list_height_, new_node_level);

    SkipNode* prev_node = traverse;
    SkipNode* next_node = traverse->node_pointers[0].next;
    SkipNode* new_node = new SkipNode(key, value, new_node_level);

    int next_node_level = 0;
    int prev_node_level = 0;

    int max_level = std::min(new_node_level, this->list_height_);

    // Set new node's next pointers
    // and the next nodes' previous pointers
    while (next_node_level < max_level) {
        if (next_node == tail_) {
            next_node->node_pointers[next_node_level].prev = new_node;
            new_node->node_pointers[next_node_level].next = next_node;
            next_node_level++;
        } if (next_node->node_pointers.size() > (size_t)next_node_level) {
            // Next node tower is tall enough
            next_node->node_pointers[next_node_level].prev = new_node;
            new_node->node_pointers[next_node_level].next = next_node;
            next_node_level++;
        } else {
            next_node = next_node->node_pointers[0].next;
        }
    }

    // Set the new node's previous pointers
    // and the previous nodes' next pointers
    while (prev_node_level < max_level) {
        if(prev_node == head_) {
            prev_node->node_pointers[prev_node_level].next = new_node;
            new_node->node_pointers[prev_node_level].prev = prev_node;
            prev_node_level++;
        } if (prev_node->node_pointers.size() > (size_t)prev_node_level) {
            // Prev node tower is tall enough
            prev_node->node_pointers[prev_node_level].next = new_node;
            new_node->node_pointers[prev_node_level].prev = prev_node;
            prev_node_level++;
        } else {
            prev_node = prev_node->node_pointers[0].prev;
        }
    }
}


/**
 * Finds the given key in the list if it exists, and returns a pointer to the node containing it.
 * Returns NULL if not found in the list.
 * Randomly calls findR or findI
 */
SkipNode * SkipList::find(int key) {
    SkipNode * retval;

    // HINT: Easier to fix ONE of the find functions (maybe findI)
    // to help debug the other
    if ((rand() % 2) == 0) { retval = findR(key); }
    else                   { retval = findI(key); }

    return retval;
}


/**
 * Finds given key in list recursively. 
 */
SkipNode * SkipList::findR(int key) {
    return findRHelper(key, head_->node_pointers.size() - 1, head_);
}


/**
 * Helper function for findR.
 */
SkipNode * SkipList::findRHelper(int key, int level, SkipNode * curr) {
    if (curr == tail_ || level < 0) {
        return NULL;
    }

    int next_key =  curr->node_pointers[level].next->key;
    SkipNode* ret;

    // Base Case:
    if (next_key == key) {
        ret = curr->node_pointers[level].next;
    }

    // Recusive Case:
    if (next_key > key) {
        ret = findRHelper(key, level, curr);
    } else {
        ret = findRHelper(key, level, curr->node_pointers[level].next);    
    }

    return NULL;
}


/**
 * An iterative find function
 */
SkipNode * SkipList::findI(int key) {
    SkipNode* curr = head_;
    SkipNode* ret = NULL;

    int level = head_->node_pointers.size()-1;

    while (curr->node_pointers[0].next != tail_ && level >= 0) {
        int next_key = curr->node_pointers[level].next->key;

        if (next_key == key) {
            ret = curr->node_pointers[level].next;
        } else if (key < next_key) {
            level++;
        } else {
            curr = curr->node_pointers[level].next;
        }

    }

    return NULL;
}



/**
 * Removes the node with the given key from the list.
 * Return true if successfully removed, else false.
 */
bool SkipList::remove(int key) {
    // don't allow the removal of sentinel nodes
    if(key == INT_MAX || key == INT_MIN)
        return false;

    SkipNode* node = find(key);
    bool ret = true;

    // can't remove a node that doesn't exist
    if(node == NULL) {
        ret = false;
    }

    length_--;

    // let all pointers of removed node go through
    for(size_t i = 0; i < node->node_pointers.size(); i++) {
        SkipNode* next = node->node_pointers[i].next;
        SkipNode* prev = node->node_pointers[i].prev;

        prev->node_pointers[i].next = next;
        next->node_pointers[i].prev = prev;
    }

    return true;
}


/**
 * A function that returns the keys of the list in a vector, using only next pointers.
 * @return a vector containing the keys from head_ to tail_, INCLUDING the sentinel values
 */
std::vector<int> SkipList::traverse() {
    std::vector<int> ret;
    SkipNode* curr = head_;

    while (curr != tail_) {
        ret.push_back(curr->key);
        curr = curr->node_pointers[0].next;
    }
    
    return ret;
}


void SkipList::printKeys() {
    std::vector<int> keys = traverse();

    for (std::vector<int>::iterator it = keys.begin(); it != keys.end(); ++it) {
        std::cout << (*it) << " ";
    }

    std::cout << std::endl;
}


/**
 * The destructor for SkipList.
 */
SkipList::~SkipList() 
{
    clear();   
}


/**
 * Helper for destructor
 */
void SkipList::clear() {
    SkipNode * temp = head_;
    SkipNode * prev = head_;

    while (temp != tail_) {
        prev = temp;
        temp = temp->node_pointers[0].next;
        delete prev;
    }
}


/**
 * Returns the height to use for the next node.
 * Is based on the probability and max_levels global variables
 */
int SkipList::levelGenerator() {
    int ret_level = 1;
    while (((rand() % 100) < probability_) && (ret_level < max_level_)) {
        ret_level++;
    }
    return ret_level;
}


/**
 * Returns the length of the list
 */
int SkipList::getLength() {
    return length_;
}
