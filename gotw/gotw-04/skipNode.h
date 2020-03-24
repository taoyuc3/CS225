/**
 * @author
 *  Arman Tajback
 *  Jordi Paris Ferrer
 *  Annie Kim
 */

#include <iostream>
#include <vector>

// Forward declaration
class SkipPointer;

/** Skip nodes have a key, value, and a tower of nodes.
 * For example:
 *
 * LEVEL
 * 4      <--[prev         next]-->  SkipPointer
 * 3      <--[prev         next]-->  SkipPointer
 * 2      <--[prev         next]-->  SkipPointer
 * 1      <--[prev         next]-->  SkipPointer
 * 0      <--[key = 5, val = 10]-->  SkipPointer
 *             ^^ SkipNode ^^
 */
class SkipNode {
	public:
		SkipNode();
		SkipNode(int key, int val, int level);
        SkipNode(const SkipNode &other);

        void print();
		
        int key;
		int value;
        std::vector<SkipPointer> node_pointers; 
};


class SkipPointer {
	public:
		SkipNode* next;
		SkipNode* prev;

		SkipPointer() : next(NULL), prev(NULL) {}
		SkipPointer(SkipNode* n, SkipNode* p) : next(n), prev(p) {}	
        SkipPointer(const SkipPointer &other) {
            this->next = other.next;
            this->prev = other.prev;
        }
};
