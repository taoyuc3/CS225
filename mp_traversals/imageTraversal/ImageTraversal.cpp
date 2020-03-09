#include <cmath>
#include <iterator>
#include <iostream>

#include "../cs225/HSLAPixel.h"
#include "../cs225/PNG.h"
#include "../Point.h"

#include "ImageTraversal.h"

// using namespace cs225;
/**
 * Calculates a metric for the difference between two pixels, used to
 * calculate if a pixel is within a tolerance.
 *
 * @param p1 First pixel
 * @param p2 Second pixel
 * @return the difference between two HSLAPixels
 */
double ImageTraversal::calculateDelta(const HSLAPixel & p1, const HSLAPixel & p2) {
  double h = fabs(p1.h - p2.h);
  double s = p1.s - p2.s;
  double l = p1.l - p2.l;

  // Handle the case where we found the bigger angle between two hues:
  if (h > 180) { h = 360 - h; }
  h /= 360;

  return sqrt( (h*h) + (s*s) + (l*l) );
}

/**
 * Default iterator constructor.
 */
ImageTraversal::Iterator::Iterator() {
  /** @todo [Part 1] */
  traverse_data = NULL;
}

ImageTraversal::Iterator::Iterator(ImageTraversal * traversal){
  traverse_data = traversal;
}
/**
 * Iterator increment opreator.
 *
 * Advances the traversal of the image.
 */
ImageTraversal::Iterator & ImageTraversal::Iterator::operator++() {
  /** @todo [Part 1] */
  if(traverse_data == NULL ){
    return *this;
  }

  // Point right = Point((traversal_->pop()).x + 1, traversal_->pop().y);
  // Point below = Point(traversal_->pop().x, traversal_->pop().y + 1);
  // Point left = Point(traversal_->pop().x - 1, traversal_->pop().y);
  // Point above = Point(traversal_->pop().x, traversal_->pop().y - 1);

 //  traverse_data->add(right);
 //  traverse_data->add(below);
 //  traverse_data->add(left);
 //  traverse_data->add(above);

  return *this;
}

/**
 * Iterator accessor opreator.
 *
 * Accesses the current Point in the ImageTraversal.
 */
Point ImageTraversal::Iterator::operator*() {
  /** @todo [Part 1] */
  // if(traversal_ == nullptr){
  //   return Point(-1,-1);
  // }
  // if(traversal_->empty() == true){
  //   return Point(-1,-1);
  // }
  // return traversal_->peek();
  return Point(0,0);
}

/**
 * Iterator inequality operator.
 *
 * Determines if two iterators are not equal.
 */
bool ImageTraversal::Iterator::operator!=(const ImageTraversal::Iterator &other) {
  /** @todo [Part 1] */
  // if(traversal_ == nullptr || traversal_->empty() == true){
  //     return true;
  // }
  //
  // if(traversal_->peek() == const_cast<ImageTraversal::Iterator&>(other).operator *()){
  //   return false;
  // }
  //
  // if(const_cast<ImageTraversal::Iterator&>(other).operator * () == Point(-1,-1)){
  //   return false;
  // }
    return false;
}
