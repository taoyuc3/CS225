#ifndef BINARYTREE_H
#define BINARYTREE_H

#include <iostream>
#include <string>

using namespace std;

template <typename T>
class BinaryTree {
  private:
    struct Node {
        T elem;
        Node* left;
        Node* right;
        Node(const T& element) : elem(element), left(NULL), right(NULL) { }
    };

    Node* root;
    void insert(Node*& node, const T& elem);

  public:
    BinaryTree();
    int numNodes(Node * root);
    int numNodes();
    void insert(const T& elem);
};

#include "binarytree.cpp"

#endif
