/**
 * @author
 *  Arman Tajback
 *  Jordi Paris Ferrer
 *  Annie Kim
 */

#include "skipNode.h"

/**
 * Default constructs a SkipNode. 
 * Initializes the node to height one, with both pointers set to NULL.
 */
SkipNode::SkipNode() {
}

/**
 * SkipNode constructor that takes in a key, value, and level.
 */
SkipNode::SkipNode(int key, int value, int level) {
    this->key = key;
    this->value = value;
    
    for (int i = 0; i < level; i++) {
        node_pointers.push_back(SkipPointer());
    }
}


/**
 * Copy constructor for a SkipNode.
 */
SkipNode::SkipNode(const SkipNode &other) {   
    this->key = other.key;
    this->value = other.value;
    this->node_pointers = other.node_pointers;
}


void SkipNode::print() {
	printf("Key: %d -- Value: %d\n", key, value);
}
