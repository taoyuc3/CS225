// Your code here!
#include "Thing.h"
#include <string>
using namespace potd;
using namespace std;

// takes the max size of the properties and values arrays
Thing::Thing(int maxsize){

  props_ct_ = 0;
  props_max_ = maxsize;

  properties_ = new string[props_max_];
  values_ = new string[props_max_];
}

// copy constructor
Thing::Thing(const Thing & other){

  properties_ = new string[props_max_];
  values_ = new string[props_max_];
  props_ct_ = other.props_ct_;
  props_max_ = other.props_max_;

  for(int x=0; x<other.props_ct_; x++){
      properties_[x] = other.properties_[x];
      values_[x] = other.values_[x];
  }
}

//assignment operator
Thing & Thing::operator=(const Thing & other){

  this->properties_ = new string[props_max_];
  this->values_ = new string[props_max_];
  this->props_ct_ = other.props_ct_;
  this->props_max_ = other.props_max_;

  for(int x=0; x<other.props_ct_;x++){
    this->properties_[x] = other.properties_[x];
    this->values_[x] = other.values_[x];
  }
  return * this;
}

//destructor
Thing::~Thing(){
  delete []properties_;
  delete []values_;
}


int Thing::set_property(string name, string value){

  for (int i = 0; i < props_ct_; i++) {
    if (properties_[i] == name){
      values_[i] = value;
      return i;
    }
  }
  //array is full
  if(props_ct_ == props_max_){
    return -1;
  }

  properties_[props_ct_] = name;
  values_[props_ct_] = value;
  props_ct_ = props_ct_+1;
  return(props_ct_);
}

string Thing::get_property(string name){
  for (int i = 0; i < props_ct_; i++){
    if(properties_[i] == name){
      return values_[i];
    }
  }
  return string();
}
