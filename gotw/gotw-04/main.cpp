#include "skipList.h"
#include <math.h>
#include <iostream>
#include <string>


int main() {
    // Random number generator, use time(NULL) as seed for more random behavior
    // Use specified seed for deterministic behavior
    // srand(225);
    srand(time(NULL));

    int n = 10;
    int max_level = int(log(n));
    int probability = 50;

    std::cout<< "Creating new SkipList" << std::endl;
    SkipList* list = new SkipList(probability, max_level);

    // Test your insert function!
    std::cout<< "Insert" << std::endl;
    for (int i = 0; i < n; i++) {
        list->insert(i, i);        
    }

    list->printKeys();

    // Test your find function!
    std::cout<< "Find" << std::endl;
    int key = n-1;
    SkipNode* target_node = list->find(key);
    target_node->print();

    list->printKeys();

    // Test your delete function!
    std::cout<< "Delete" << std::endl;
    list->remove(key);

    delete(list);

    return 0;
}
