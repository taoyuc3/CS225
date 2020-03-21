#include "TreeNode.h"

TreeNode::RotationType balanceTree(TreeNode*& subroot) {
	// Your code here
  if(leftHeavy(subroot) == true){
    if(leftHeavy(subroot->left_) == true){
      return TreeNode::right;
    }
    return TreeNode::leftRight;
  }

  if(rightHeavy(subroot) == true){
    if(rightHeavy(subroot->right_) == true){
      return TreeNode::left;
    }
    return TreeNode::rightLeft;
  }
    return TreeNode::right;
}
