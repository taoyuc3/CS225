#pragma once

#include <cstddef>

#include <list>



class Queue {
    public:
        int size() const;
        bool isEmpty() const;
        void enqueue(int value);
        int dequeue();
        std::list<int> myQueue;
        int mySize = 0;

};