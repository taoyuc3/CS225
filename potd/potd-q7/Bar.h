// your code here
#pragma once

#include "Foo.h"
#include <string>

namespace potd{
  class Bar {
      public:
        Bar(std::string name);
        Bar(const Bar & other);
        ~Bar();
        Bar & operator = (const Bar & other);
        std::string get_name();

/* A constructor that takes a string.
A copy constructor.
A destructor.
An operator=.
A method string get_name() to return the name contained within f_.
*/


      private:
        Foo * f_;
  };
}
