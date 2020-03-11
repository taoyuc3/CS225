#include <cmath>
#include <iterator>
#include <iostream>

#include "../cs225/HSLAPixel.h"
#include "../cs225/PNG.h"
#include "../Point.h"
#include "ImageTraversal.h"

#include <list>

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
  curr_point = Point(-1,-1);
}

ImageTraversal::Iterator::Iterator(ImageTraversal * traversal, Point point){
  traverse_data = traversal;
  curr_point = point;
}

/**
 * Iterator increment opreator.
 *
 * Advances the traversal of the image.
 */
ImageTraversal::Iterator & ImageTraversal::Iterator::operator++() {
  /** @todo [Part 1] */
  curr_point = traverse_data->pop();

  if(curr_point.x + 1 < traverse_data->png1.width() &&
    traverse_data->already[curr_point.x + 1][curr_point.y] == false){
      if(calculateDelta(traverse_data->png1.getPixel(curr_point.x + 1, curr_point.y),
                         traverse_data->png1.getPixel(traverse_data->start1.x, traverse_data->start1.y))
                         <= traverse_data->tolerance1){
         Point right(curr_point.x + 1, curr_point.y);
         traverse_data->add(right);
      }
  }

  if(curr_point.y + 1 < traverse_data->png1.height() &&
    traverse_data->already[curr_point.x][curr_point.y+1] == false){
      if(calculateDelta(traverse_data->png1.getPixel(curr_point.x, curr_point.y+1),
                         traverse_data->png1.getPixel(traverse_data->start1.x, traverse_data->start1.y))
                         <= traverse_data->tolerance1){
        Point below = Point(curr_point.x, curr_point.y + 1);
        traverse_data->add(below);
      }
  }

  if(curr_point.x >= 1 &&
    traverse_data->already[curr_point.x-1][curr_point.y] == false){
      if(calculateDelta(traverse_data->png1.getPixel(curr_point.x-1, curr_point.y),
                        traverse_data->png1.getPixel(traverse_data->start1.x, traverse_data->start1.y))
                        <= traverse_data->tolerance1){
        Point left = Point(curr_point.x - 1, curr_point.y);
        traverse_data->add(left);
      }
  }

  if(curr_point.y >= 1 &&
    traverse_data->already[curr_point.x][curr_point.y-1] == false){
      if(calculateDelta(traverse_data->png1.getPixel(curr_point.x, curr_point.y-1),
                        traverse_data->png1.getPixel(traverse_data->start1.x, traverse_data->start1.y))
                        <= traverse_data->tolerance1){
        Point above = Point(curr_point.x, curr_point.y - 1);
        traverse_data->add(above);
      }
  }

  traverse_data->already[curr_point.x][curr_point.y] = true;
  curr_point = traverse_data->peek();

  while(traverse_data->mylist.empty() == false){
    if(traverse_data->already[curr_point.x][curr_point.y] == false){
      break;
    }else{
      Point pop_pixel = traverse_data->pop();
      curr_point = traverse_data->peek();
    }
  }

  return *this;
}

/**
 * Iterator accessor opreator.
 *
 * Accesses the current Point in the ImageTraversal.
 */
Point ImageTraversal::Iterator::operator*(){
  /** @todo [Part 1] */
  //return Point(0,0);
  return this->curr_point;
}

/**
 * Iterator inequality operator.
 *
 * Determines if two iterators are not equal.
 */
bool ImageTraversal::Iterator::operator!=(const ImageTraversal::Iterator &other) {
  /** @todo [Part 1] */
  //return false;
  if(this->curr_point == other.curr_point){
    return false;
  }
    return true;
}
