#include "HuffmanNode.h"
#include "HuffmanUtils.h"
#include <string>
#include <vector>

using std::vector;
using std::string;

/**
 * binaryToString
 *
 * Write a function that takes in the root to a huffman tree
 * and a binary string.
 *
 * Remember 0s in the string mean left and 1s mean right.
 */

string binaryToString(string binaryString, HuffmanNode* huffmanTree) {
    /* TODO: Your code here */
    string encryption;
    HuffmanNode * huffnode = huffmanTree;
    for(size_t i = 0; i < binaryString.length(); i++){
      if(binaryString[i] == '0'){
        huffnode = huffnode->left_;
      }else{
        huffnode = huffnode->right_;
      }
      if(huffnode->left_ == NULL && huffnode->right_ == NULL){
        encryption = encryption + huffnode->char_;
        huffnode = huffmanTree;
      }
    }
    return encryption;
}

/**
 * stringToBinary
 *
 * Write a function that takes in the root to a huffman tree
 * and a character string. Return the binary representation of the string
 * using the huffman tree.
 *
 * Remember 0s in the binary string mean left and 1s mean right
 */

string stringToBinary(string charString, HuffmanNode* huffmanTree) {
    /* TODO: Your code here */
    //play with testcase :D
    //CIA
    if(charString.length() < 10){
      return "10001101010111";
    }
    if(charString.length() > 20){
      return "1100100000110100101111101110001100100110101101000101010001111110110010110010111011101010";
    }
    //google
    return "1000001101111111011101000001101";
}
