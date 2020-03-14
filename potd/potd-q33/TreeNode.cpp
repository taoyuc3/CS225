#include "TreeNode.h"
#include <algorithm>


void rightRotate(TreeNode* root) {
    // Your code here
  TreeNode * temp;
  TreeNode * subroot;

  subroot = root->left_;
  temp = subroot->right_;

  root->left_ = temp;
  temp->parent_ = root;
  subroot->right_ = root;
  root->parent_ = subroot;
  subroot->parent_ = NULL;

}


void leftRotate(TreeNode* root) {

    // your code here
    TreeNode * temp;
    TreeNode * subroot;

    subroot = root->right_;
    temp = subroot->left_;

    root->right_ = temp;
    temp->parent_ = root;
    subroot->left_ = root;
    root->parent_ = subroot;
    subroot->parent_ = NULL;

}



void deleteTree(TreeNode* root)
{
  if (root == NULL) return;
  deleteTree(root->left_);
  deleteTree(root->right_);
  delete root;
  root = NULL;
}
