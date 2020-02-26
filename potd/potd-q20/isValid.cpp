#include <string>
#include <stack>

using namespace std;

bool isValid(string input) {
    stack<char> st;

  if(input.size()==0){
    return true;
  }
  for(unsigned i = 0; i < input.size(); i++){
    if(input[i]=='(' || input[i] == '[' || input[i] == '{'){
      st.push(input[i]);
    }
    if(input[i]==')' || input[i] == ']' || input[i] == '}'){
      if(st.size()==0){
        return false;
      }
    if(input[i] == ')' && st.top()== '('){
      st.pop();
    }else if(input[i] == ']' && st.top()== '['){
      st.pop();
    }else if(input[i] == '}' && st.top()== '{'){
      st.pop();
    }else{
      return false;
    }
  }
}
  if(st.size()==0){
    return true;
  }else{
    return false;
  }

}


//     int i=0;
//     int j=0;
//     int k=0;
//     bool changei = false;
//     bool changej = false;
//     bool changek = false;
//
//     if(input.size()==0){
//       return true;
//     }
//
//     for(unsigned index = 0; index < input.size(); index++){
//       st.push(input[index]);
//   }
//     while(st.size()!= 0){
// //check ()
//       int tempi = i;
//       int tempj = j;
//       int tempk = k;
//       if(st.top()== ')')
//       {
//         i++;
//       }
//       if(st.top()== '('){
//
//         if(i == 0 ){
//           return false;
//         }
//               i--;
//       }
// //check []
//       if(st.top()== ']')
//       {
//         j++;
//       }
//       if(st.top()== '['){
//
//         if(j == 0){
//           return false;
//         }
//         j--;
//       }
// //check {}
//       if(st.top()== '}')
//       {
//         k++;
//       }
//       if(st.top()== '{'){
//
//         if(k == 0){
//           return false;
//         }
//           k--;
//       }
//       st.pop();
//
//       if(changei && ((j-tempj == -1) || (k-tempk == -1)))
//       {return false;}
//
//       if(changej && ((i-tempi == -1) || (k-tempk == -1)))
//       {return false;}
//
//       if(changek && ((i-tempi == -1) || (j-tempj == -1)))
//       {return false;}
//
//     if(i != tempi){
//       changei = true;
//   }else{
//       changei = false;
//   }
//     if(j != tempj){
//      changej = true;
//   }else{
//      changej = false;
//   }
//     if(k != tempk){
//      changej = true;
//   }else{
//      changej = false;
//   }
//
// }//while loop end
//
//   if(i == 0 && j == 0 && k == 0){
//     return true;
//   }else{
//     return false;
//   }    // modify this!
