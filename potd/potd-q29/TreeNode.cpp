#include "TreeNode.h"
#include <iostream>

TreeNode * deleteNode(TreeNode* root, int key) {
  // your code here
  if(root == NULL){
    return NULL;
  }

  if(root->val_ > key){
    root->left_ = deleteNode(root->left_, key);
  }else if(root->val_ < key){
    root->right_ = deleteNode(root->right_, key);
  }else{

    TreeNode * temp = root;

  //node with two child
  if(root->left_ != NULL && root->right_ != NULL){
    TreeNode * temp1 = root->right_;
    while(temp1->left_ != NULL){
      temp1 = temp1->left_;
    }

    root->val_ = temp1->val_;
    root->right_ = deleteNode(root->right_, temp1->val_);
    // TreeNode * temp2 = temp;
    // temp->left_ = NULL;
    // delete temp2;
  }

  //node with only left child
  if(root->left_  != NULL && root->right_ == NULL){
    root = root->left_;
    delete temp;
  }

  //node with only right child
  if(root->left_ == NULL && root->right_ != NULL){
    root = root->right_;
    delete temp;
  }

  //leaf
  if(root->left_ == NULL && root->right_ == NULL){
    delete root;
    root = NULL;
  }
}

  return root;
}

void inorderPrint(TreeNode* node)
{
    if (!node)  return;
    inorderPrint(node->left_);
    std::cout << node->val_ << " ";
    inorderPrint(node->right_);
}

void deleteTree(TreeNode* root)
{
  if (root == NULL) return;
  deleteTree(root->left_);
  deleteTree(root->right_);
  delete root;
  root = NULL;
}
