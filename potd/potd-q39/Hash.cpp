#include <vector>
#include <string>
#include "Hash.h"

using namespace std;

int hashFunction(string s, int M) {
   // Your Code Here
   //hash function to sum up the ASCII characters of the letters of the string
   int summation = 0;
   for(int i = 0; s[i] != '\0'; i++){
     summation += s[i];
   }
   return summation % M;
 }

int countCollisions (int M, vector<string> inputs) {
	int collisions = 0;
	// Your Code Here
  unsigned array[M];
  for(unsigned j = 0; j < inputs.size(); j++){
    int sum = hashFunction(inputs[j], M);
    if(array[sum] == 1){
      collisions++;
    }
    array[sum] = 1;
  }
	return collisions;
}
