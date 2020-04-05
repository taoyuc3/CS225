/**
 * @file kdtree.cpp
 * Implementation of KDTree class.
 */
#include <utility>
#include <algorithm>

#include <iostream>
#include <cmath>

using namespace std;

template <int Dim>
bool KDTree<Dim>::smallerDimVal(const Point<Dim>& first,
                                const Point<Dim>& second, int curDim) const
{
    /**
     * @todo Implement this function!
     */
   if(first[curDim] < second[curDim]){
     return true;
   }
   if(first[curDim] > second[curDim]){
     return false;
   }
     return first < second;
     // return false;
}

template <int Dim>
bool KDTree<Dim>::shouldReplace(const Point<Dim>& target,
                                const Point<Dim>& currentBest,
                                const Point<Dim>& potential) const
{
    /**
     * @todo Implement this function!
     */
     double curr_dist = 0;
     double pote_dist = 0;
     for(unsigned i = 0; i < Dim; i++){
       curr_dist += (target[i] - currentBest[i])*(target[i] - currentBest[i]);
       pote_dist += (target[i] - potential[i])*(target[i] - potential[i]);
     }
     if(pote_dist > curr_dist) return false;
     if(pote_dist < curr_dist) return true;

     return potential < currentBest;
     // return false;
}

//helper function buildKDTree
template <int Dim>
void KDTree<Dim>::buildKDTree(vector<Point<Dim>>& newPoints, int left, int right,
                              int d, KDTreeNode *& subroot)
{
  if(left > right || newPoints.empty()){
    return;
  }
  size_t pivotIndex = (left + right) / 2;
  Point<Dim> selected = select(newPoints, left, right, pivotIndex, d);
  subroot = new KDTreeNode(selected);
  buildKDTree(newPoints, left, pivotIndex-1, (d+1)%Dim, subroot->left);
  buildKDTree(newPoints, pivotIndex+1, right, (d+1)%Dim, subroot->right);
}

//helper function select
template <int Dim>
Point<Dim> KDTree<Dim>::select(vector<Point<Dim>>& elements , int left, int right, size_t k, int d)
{
  if(elements.empty()){
    return NULL;
  }
  if(left == right){
    return elements[left];
  }
  size_t pivotIndex = (left + right)/2;
  pivotIndex = partition(elements, left, right, pivotIndex, d);

  //might be some problem here
  if(k == pivotIndex){
    return elements[k];
  }
  if(k < pivotIndex){
    return select(elements, left, pivotIndex-1, k, d);
  }
  return select(elements, pivotIndex+1, right, k, d);
}

//helper function partition
template <int Dim>
int KDTree<Dim>::partition(vector<Point<Dim>>& elements , int left,
                           int right, size_t pivotIndex, int d){

  Point<Dim> pivotValue = elements[pivotIndex];
  swap(elements[pivotIndex], elements[right]);
  size_t storedIndex = left;

  for(int i = left; i < right; i++){
    if(smallerDimVal(elements[i], pivotValue, d)){
      swap(elements[storedIndex], elements[i]);
      storedIndex++;
    }
  }
  swap(elements[storedIndex], elements[right]);
  return storedIndex;
}

template <int Dim>
KDTree<Dim>::KDTree(const vector<Point<Dim>>& newPoints)
{
    /**
     * @todo Implement this function!
     */
     vector<Point<Dim>> temp = newPoints;
     if(!newPoints.empty()){
       buildKDTree(temp, 0, temp.size()-1, 0, root);
     }else{
       size = 0;
       root = NULL;
     }
}

template <int Dim>
KDTree<Dim>::KDTree(const KDTree<Dim>& other) {
  /**
   * @todo Implement this function!
   */
   copy(root, other->root);
   size = other.size;
}

template <int Dim>
const KDTree<Dim>& KDTree<Dim>::operator=(const KDTree<Dim>& rhs) {
  /**
   * @todo Implement this function!
   */
   copy(root, rhs->root);
   size = rhs.size;
   return *this;
}

//helper function deleteTree
template <int Dim>
void KDTree<Dim>::deleteTree(KDTreeNode *& subroot){
  if(subroot == NULL){
    return;
  }
  deleteTree(subroot->left);
  deleteTree(subroot->right);
  delete subroot;
  subroot = NULL;
}

//helper function Copy
template <int Dim>
void KDTree<Dim>::copy(KDTreeNode *& copyNode, KDTreeNode *& other){
  if(other == NULL){
    return;
  }
  copyNode = new KDTreeNode(other->point);
  copy(copyNode->left, other->left);
  copy(copyNode->right, other->right);
  // return copyNode;
}

template <int Dim>
KDTree<Dim>::~KDTree() {
  /**
   * @todo Implement this function!
   */
   deleteTree(root);
}

template <int Dim>
Point<Dim> KDTree<Dim>::findNearestNeighbor(const Point<Dim>& query) const
{
//     /**
//      * @todo Implement this function!
//      */
  Point<Dim> findNode = query;
  Point<Dim> queryBest = root->point;
  finder(root, queryBest, findNode, 0);
  return queryBest;
  // return Point<Dim>();
}

//helper function finder
template <int Dim>
void KDTree<Dim>::finder(KDTreeNode* queryNode, Point<Dim> &queryBest,
                         Point<Dim> &query, int d) const
{
  if(queryNode == NULL){
    return;
  }
  // if(queryNode->left == NULL && queryNode->right == NULL){
  //   return;
  // }
  KDTreeNode * newNode;
  if(smallerDimVal(queryNode->point, query, d) == true){
    newNode = queryNode->left;
    finder(queryNode->right, queryBest, query, (d+1) % Dim);
  }
  if(smallerDimVal(queryNode->point, query, d) == false){
    newNode = queryNode->right;
    finder(queryNode->left, queryBest, query, (d+1) % Dim);
  }
  double distance = pow(queryNode->point[d]-query[d], 2);
  double ideal = 0.0;
  if(shouldReplace(query, queryBest, queryNode->point) == true){
    queryBest = queryNode->point;
  }
  for(int i = 0; i < Dim; i++){
      ideal += pow(queryBest[i]-query[i], 2);
  }
  if(ideal >= distance){
    finder(newNode, queryBest, query, (d+1) % Dim);
  }else{
    return;
  }
  // finder(newNode, queryBest, query, (d+1) % Dim);
}
