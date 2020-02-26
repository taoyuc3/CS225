#include <iostream>
#include <vector>

using namespace std;

#include "isValid.cpp"


int main() {

    vector<string> tests =
    {
        "()",
        ")()",
        "()[]{}!",
        "([cs225)]", //false
        "([])",    //true
        "({}[cs225{})]" //false

        // add your own tests here!
    };


    cout << std::boolalpha << endl;
    for (string& t : tests) {
        cout << t << " : ";
        cout << isValid(t);
        cout << endl << endl;
    }
}
