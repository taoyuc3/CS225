#include <iterator>
#include <cmath>

#include <list>
#include <queue>
#include <stack>
#include <vector>

#include "../cs225/PNG.h"
#include "../Point.h"

#include "ImageTraversal.h"
#include "DFS.h"


/**
 * Initializes a depth-first ImageTraversal on a given `png` image,
 * starting at `start`, and with a given `tolerance`.
 *
 * @param png The image this DFS is going to traverse
 * @param start The start point of this DFS
 * @param tolerance If the current point is too different (difference larger than tolerance) with the start point,
 * it will not be included in this DFS
 */
DFS::DFS(const PNG & png, const Point & start, double tolerance) {
  /** @todo [Part 1] */
  png1 = png;
  start1 = start;
  tolerance1 = tolerance;
  //create a 2D array to mark each pixel
  already = new bool *[png1.width()];
  for(unsigned i = 0; i < png1.width(); ++i){
    already[i] = new bool[png1.height()];
  }
  //traverse with false
  for(unsigned i = 0; i < png1.width(); i++){
    for(unsigned j = 0; j < png1.height(); j++){
      already[i][j] = false;
    }
  }
  mylist.push_back(start1);
}

/**
 * Returns an iterator for the traversal starting at the first point.
 */
ImageTraversal::Iterator DFS::begin() {
  /** @todo [Part 1] */
  ImageTraversal * dfs = new DFS(png1, start1, tolerance1);
  ImageTraversal::Iterator it(dfs, start1);
  return it;
  // return ImageTraversal::Iterator();
}

/**
 * Returns an iterator for the traversal one past the end of the traversal.
 */
ImageTraversal::Iterator DFS::end() {
  /** @todo [Part 1] */
  return ImageTraversal::Iterator();
}

/**
 * Adds a Point for the traversal to visit at some point in the future.
 */
void DFS::add(const Point & point) {
  /** @todo [Part 1] */
  mylist.push_back(point); //push at the back
}

/**
 * Removes and returns the current Point in the traversal.
 */
Point DFS::pop() {
  /** @todo [Part 1] */
  if(mylist.empty() == true){
    return Point(-1,-1);
  }
  Point mylisthead = mylist.back(); //pop at the back
  mylist.pop_back();
  return mylisthead;
}

/**
 * Returns the current Point in the traversal.
 */
Point DFS::peek() const {
  /** @todo [Part 1] */
  if(mylist.empty() == true){
    return Point(-1,-1);
  }
  return mylist.back(); //peek at the back
}

/**
 * Returns true if the traversal is empty.
 */
bool DFS::empty() const {
  /** @todo [Part 1] */
  return mylist.empty();
}
