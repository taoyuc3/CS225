#ifndef TREE_CPP
#define TREE_CPP

#include "tree.h"

template <class T>
Tree<T>::Iterator::Iterator(Tree::Node *root) : curr_(root) {
	// TODO: your code here
	if (root == nullptr){
		// this->curr_ = nullptr;
		return;
	}
	std::stack<Tree::Node*> temp;
	Tree::Node *cur = root;
	while (cur!=nullptr || !temp.empty()){
		while (cur != nullptr){
			temp.push(cur);
			cur = cur->left_;
		}
		cur = temp.top();
		temp.pop();
		if (cur->data_ %2 !=0){
			Tree::Node* add = cur;
			s.push(add);
		}
		cur = cur->right_;
	}
	if (!s.empty()){
		this->curr_ = s.front();
	} else {
		this->curr_ = nullptr;
	}
}

template <class T>
typename Tree<T>::Iterator & Tree<T>::Iterator::operator++() {
	// TODO: your code here
	s.pop();
	this->curr_ = s.front();
	return *this;
}

template <class T>
T Tree<T>::Iterator::operator*() const {
	// TODO: your code here
	if(curr_ == nullptr) {
		return T(); // remove this line
	}else{
		return this->curr_->data_;
	}
}

/*******************
 ** PROVIDED CODE **
 *******************/
template <class T>
bool Tree<T>::Iterator::operator!=(const Tree<T>::Iterator &other) {
	return !(curr_ == other.curr_);
}

template <class T>
typename Tree<T>::Iterator Tree<T>::begin() {
	return Iterator(root_);
}

template <class T>
typename Tree<T>::Iterator Tree<T>::end() {
	return Iterator(NULL);
}

#endif
