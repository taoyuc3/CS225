#include "TreeNode.h"
#include <algorithm>
#include <queue>
TreeNode* findLastUnbalanced(TreeNode* root) {
  // your code here

  std::queue<TreeNode*> myqueue;
  TreeNode * temp = root;
  TreeNode * findnode = NULL;
  while(temp!= NULL){
    if(!balance(temp)){
      findnode = temp;
    }
    myqueue.push(temp->left_);
    myqueue.push(temp->right_);
    temp = myqueue.front();
    myqueue.pop();
  }
  return findnode;
}

int getheight(TreeNode * root){
  if(root == NULL){
    return -1;
  }
  return 1 + std::max(getheight(root->left_), getheight(root->right_));
}

bool balance(TreeNode* root){
  int a = getheight(root->left_) - getheight(root->right_);
  if(a <= 1 && a >= -1){
    return true;
  }
    return false;
}

void deleteTree(TreeNode* root)
{
  if (root == NULL) return;
  deleteTree(root->left_);
  deleteTree(root->right_);
  delete root;
  root = NULL;
}
