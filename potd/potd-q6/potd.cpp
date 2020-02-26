// your code here!
#include "potd.h"
#include <array>
#include <cmath>

int *potd::raise(int *arr){
  int *array = new int[5];
  for(int i = 0; i < 5; i++){
  //   if(arr[i]){
  //     array[i] = pow(arr[i], arr[i+1]);
  //   }
  //   else{
  //     array[i] = arr[i];
  //   }
    // if(arr[i]==1){
    //   array[i]== -1;
    // }
    if(arr[i] != 0){
      array[i] = pow (arr[i], arr[i+1]);
    }
    if(arr[i] == -1){
      array[i] = -1 ;
      array[i-1] = arr[i-1];
    }
    //the last element is always -1
    //or purely -1, one element [-1]

    // if((arr[i+1] == NULL)&&(i>0))
    //   array[i] = arr[i];
    //   array[i-1] = arr[i-1];
    // }
}

  return array;
  delete []array;
}
