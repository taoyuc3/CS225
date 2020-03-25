#include <vector>
#include "BTreeNode.h"
#include <algorithm>

std::vector<int> traverse(BTreeNode* root) {
    // your code here
    std::vector<int> v;
    if(root->is_leaf_ == true){
      for(unsigned i = 0; i < root->elements_.size(); i++){
        v.push_back(root->elements_[i]);
      }
      return v;
    }

    for(unsigned i = 0; i < root->children_.size(); i++){
      std::vector<int> v_temp = traverse(root->children_[i]);

      for(unsigned j = 0; j < v_temp.size(); j++){
        v.push_back(v_temp[j]);
      }
    }

    for(unsigned k = 0; k < root->elements_.size(); k++){
      v.push_back(root->elements_[k]);
    }

    sort(v.begin(), v.end());
    return v;
}
