// your code here
#include "Foo.h"
#include "Bar.h"
#include <string>

potd::Bar::Bar(std::string name){
  this->f_ = new Foo(name);
}

potd::Bar::Bar(const potd::Bar & other){
  this->f_ = new Foo (*other.f_);
}

potd::Bar::~Bar(){
  delete f_;
}

potd::Bar & potd::Bar::operator = (const potd::Bar & other){
  this->f_;
  f_->~Foo();
  Foo *temp = new Foo ((other.f_)->get_name());
  this->f_ = temp;
  return * this;
}

std::string potd::Bar::get_name(){
  this->f_;
  return f_->get_name();
}
