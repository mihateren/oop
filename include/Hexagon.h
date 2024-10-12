#pragma once

#include "Figure.h"
#include <iostream>

class Hexagon : public Figure{
    
    friend std::ostream& operator << (std::ostream& os, const Hexagon& f);
    friend std::istream& operator >> (std::istream& is, Hexagon& f);

    public:
        Hexagon();
        Hexagon(Point& p1, Point& p2, Point& p3, Point& p4, Point& p5, Point& p6);
        
        virtual double square() const override;
        virtual Point center() const override;

        Hexagon& operator = (const Hexagon &other);
        Hexagon& operator = (Hexagon &&other);
        bool operator == (const Hexagon &other);
        virtual operator double() const override;

        ~Hexagon(){};

    private:
        static const size_t angles_ = 6;
        Point po[angles_];

};