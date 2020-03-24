#include <vector>
#include "BTreeNode.h"


BTreeNode* find(BTreeNode* root, int key) {
    // Your Code Here
  for(unsigned i = 0; i < root->elements_.size(); i++){
    if(key == root->elements_[i]){
      return root;
    }
  }

   BTreeNode* node = NULL;
  for(unsigned j = 0; j < root->children_.size(); j++){
    node = find(root->children_[j], key);
    if(node != NULL){
      return node;
    }
  }
  return NULL;
}
