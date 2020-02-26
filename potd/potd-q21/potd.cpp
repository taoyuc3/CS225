#include "potd.h"

// Your code here!
#include <vector>
#include <string>

double sum(vector<double>::iterator start, vector<double>::iterator end){
  double total = 0;
  for(vector<double>::iterator it = start; it != end; ++it){
    total = total + *it;
  }
    return total;
}

vector<double>::iterator max_iter(vector<double>::iterator start, vector<double>::iterator end){
  vector<double>::iterator it = start;
  for(auto i = start; i != end; i++){
    if(*it<*i){
      it = i;
    }
  }
    return it;
}

void sort_vector(vector<double>::iterator start, vector<double>::iterator end){
  double temp;
  for (auto i = start; i != end; i++) {
  vector<double>::iterator max = max_iter(i, end);
  temp = *i;
  *i = *max;
  *max = temp;
}

}
