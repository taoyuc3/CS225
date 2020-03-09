#include <iterator>
#include <cmath>

#include <list>
#include <queue>
#include <stack>
#include <vector>

#include "../cs225/PNG.h"
#include "../Point.h"

#include "ImageTraversal.h"
#include "BFS.h"

using namespace cs225;

/**
 * Initializes a breadth-first ImageTraversal on a given `png` image,
 * starting at `start`, and with a given `tolerance`.
 * @param png The image this BFS is going to traverse
 * @param start The start point of this BFS
 * @param tolerance If the current point is too different (difference larger than tolerance) with the start point,
 * it will not be included in this BFS
 */
BFS::BFS(const PNG & png, const Point & start, double tolerance) {
  /** @todo [Part 1] */
  png1 = png;
  start1 = start;
  tolerance1 = tolerance;
  //create a 2D array to mark each pixel
  bool **already = new bool *[png1.width()];
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
ImageTraversal::Iterator BFS::begin() {
  /** @todo [Part 1] */
  return ImageTraversal::Iterator();
}

/**
 * Returns an iterator for the traversal one past the end of the traversal.
 */
ImageTraversal::Iterator BFS::end() {
  /** @todo [Part 1] */
  return ImageTraversal::Iterator();
}

/**
 * Adds a Point for the traversal to visit at some point in the future.
 */
void BFS::add(const Point & point) {
  /** @todo [Part 1] */
  mylist.push_back(point);
}

/**
 * Removes and returns the current Point in the traversal.
 */
Point BFS::pop() {
  /** @todo [Part 1] */
  if(mylist.empty() == true){
    return Point(-1, -1);
  }
  Point mylisthead = mylist.front();
  mylist.pop_front();
  return mylisthead;
}

/**
 * Returns the current Point in the traversal.
 */
Point BFS::peek() const {
  /** @todo [Part 1] */
  if(mylist.empty() == true){
    return Point(-1,-1);
  }
    return mylist.front();
}

/**
 * Returns true if the traversal is empty.
 */
bool BFS::empty() const {
  /** @todo [Part 1] */
  return mylist.empty();
}
