/**
 * @author
 *  Arman Tajback
 *  Jordi Paris Ferrer
 *  Wade Fagen-Ulmschneider
 *  Annie Kim
 */

// You shouldn't have to modifty this file
#pragma once

#include <algorithm>  
#include <cstdio>
#include <climits>
#include <iostream>
#include <map>
#include <random>
#include <stdio.h>
#include <string>
#include <vector>
#include "skipNode.h"

/**
 * A sorted Skip List class.
 */
class SkipList {
    public:

        SkipList();
        SkipList(int probability, int max_level);
        SkipList(int key, int value, int probability, int max_level);
        SkipList(const SkipList &other);
        ~SkipList();

        const SkipList& operator=(const SkipList & other);

        void insert(int key, int value);
        void printKeys();

        bool remove(int key);

        int getLength();
        int levelGenerator();
        SkipNode* find(int key);

        std::vector<int> traverse();

    private:
        SkipNode* head_;
        SkipNode* tail_;

        int list_height_;
        int length_;
        int probability_;
        int max_level_;

        SkipNode* findInsertionIdx(int key);
        SkipNode* findI(int key);
        SkipNode* findR(int key);
	    SkipNode* findRHelper(int key, int level, SkipNode * curr);
        
        void clear();
        void copy(const SkipList & other);

};

