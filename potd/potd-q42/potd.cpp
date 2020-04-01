#include <unordered_map>

using namespace std;

unordered_map<string, int> common_elems(unordered_map<string, int> &mapA,
                                        unordered_map<string, int> &mapB) {

    // your code here
  unordered_map<string, int> newMap;
  for(pair<string,int>elem: mapA){
    unordered_map<string, int>::iterator it = mapB.find(elem.first);
    if(it != mapB.end()){
      newMap.insert(pair<string, int>(elem.first, elem.second + it->second));
    }
  }
  for(auto elem: newMap){
    mapA.erase(elem.first);
    mapB.erase(elem.first);
  }
  return newMap;
    // return unordered_map<string, int>();
}
