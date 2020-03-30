#include "TreeNode.h"

// Your function here

const TreeNode *TreeNode::find(int value) const {
  
}

// Methods and functions we provide following.
// You should not need to edit this code.

TreeNode::TreeNode(int data, TreeNode *left, TreeNode *right) :
    data_(data), left_(left), right_(right) {}

TreeNode::~TreeNode() {
    if (left_ != NULL) {
        delete left_;
    }
    if (right_ != NULL) {
        delete right_;
    }
}

bool equal(TreeNode *n1, TreeNode *n2) {
    if (n1 == NULL || n2 == NULL) {
        return n1 == n2;
    }

    return ( (n1->getData() == n2->getData()) &&
            equal(n1->getLeft(), n2->getLeft()) &&
            equal(n1->getRight(), n2->getRight()));
}

int TreeNode::getData() const {
    return data_;
}

TreeNode *TreeNode::getLeft() const {
    return left_;
}

TreeNode *TreeNode::getRight() const {
    return right_;
}
