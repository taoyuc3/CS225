// Your code here
#include "potd.h"

 string getFortune(const string &s){

   if(s.size() == 2){
     return "Hello World";
   }

   if(s.size() % 3 == 0){
     return "Welcome to CS225";
   }

   if(s.size() % 4 == 0){
     return "This is Data Structure";
   }

   if(s.size() % 5 == 0){
     return "Spring is around the corner";
   }

   if(s.size() % 6 == 0){
     return "I love Computer Science so much";
   }

   return "Have a nice day!";
 }
