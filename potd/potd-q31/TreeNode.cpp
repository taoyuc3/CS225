#include "TreeNode.h"
#include <algorithm>

int getheight(TreeNode * root){
  if(root == NULL){
    return -1;
  }
  return (1 + std::max(getheight(root->left_), getheight(root->right_)));
}

bool isHeightBalanced(TreeNode* root) {
  // your code here

  int balance = getheight(root->left_) - getheight(root->right_);
  if(balance <=1 && balance >=-1){
    return true;
  }else{
    return false;
  }
}

void deleteTree(TreeNode* root)
{
  if (root == NULL) return;
  deleteTree(root->left_);
  deleteTree(root->right_);
  delete root;
  root = NULL;
}
