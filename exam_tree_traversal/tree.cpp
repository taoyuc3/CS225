#ifndef TREE_CPP
#define TREE_CPP

#include "tree.h"

template <class T>
Tree<T>::Iterator::Iterator(Tree::Node *root) : curr_(root) {
	// TODO: your code here
	if(root == NULL){
		return;
}
	Node * curr = root;
	while(curr != nullptr || !mystack.empty()){
		while(curr != nullptr){
			mystack.push(curr);
			curr = curr->left_;
		}
		curr = mystack.top();
		mystack.pop();

		if(curr->data_ %2 != 0){
			Node * add = curr;
			myqueue.push(add);
		}
		curr = curr->right_;
	}

	if(!myqueue.empty()){
		this->curr_ = myqueue.front();
	}
	else{
		this->curr_ = NULL;
	}
}

template <class T>
typename Tree<T>::Iterator & Tree<T>::Iterator::operator++() {
	// TODO: your code here
	myqueue.pop();
	this->curr_ = myqueue.front();
	return *this;
}

template <class T>
T Tree<T>::Iterator::operator*() const {
	// TODO: your code here
	if(curr_ == nullptr){
		return T();
	}
	else{
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
