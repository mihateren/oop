#pragma once
#include<iostream>
#include "Figure.h"

class FiguresArray
{
    public:
        FiguresArray();
        void resize(int new_size);
        int  size() const;
        void push_back(Figure* val);
        void remove(int ind);
        Figure* & operator[] (int idx);
        double totalSquare() const;

        ~FiguresArray();
    private:
        Figure** buf;
        int size_;
        int cap;
};