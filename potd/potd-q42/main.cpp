#include <iostream>
#include "potd.cpp"

using namespace std;
int main() {
    unordered_map<string, int> mapA({
                                    {"common", 13},
                                    {"unique_a", 13},
                                    {"ok", 1}
                                    });
    unordered_map<string, int> mapB({
                                    {"common", 17},
                                    {"unique_b", 17},
                                    {"ok", 2}
                                    });

    unordered_map<string, int> common = common_elems(mapA, mapB);

    // check your outputs here
cout << mapA["common"] << endl;
cout << common["common"] << endl;
cout << common["unique_b"] << endl;
cout << common["ok"] << endl;
cout << mapB["ok"] << endl;
}
