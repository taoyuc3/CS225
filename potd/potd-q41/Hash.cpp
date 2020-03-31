#include "Hash.h"
#include <string>

unsigned long bernstein(std::string str, int M)
{
	unsigned long b_hash = 5381;
	//Your code here
	for(unsigned i = 0; i < str.size(); i++){
		b_hash *= 33;
		b_hash += int(str[i]);
	}
	return b_hash % M;
}

std::string reverse(std::string str)
{
  // std::string output = "";
	std::string output = str;
	// Your code here
	int size = output.size();
	for(int i = 0; i < (size/2); i++){
		int temp = output[size-1-i];
		output[size-1-i] = output[i];
		output[i] = temp;
	}
	return output;
}

// std::string reverse_helper(std::string input)
// {
// 	int size = input.size();
// 	for(int i = 0; i < (size/2); i++){
// 		int temp = input[size-1-i];
// 		input[size-1-i] = input[i];
// 		input[i] = temp;
// 	}
// 	return input;
// }
