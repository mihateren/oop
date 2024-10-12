#pragma once

#include "Figure.h"
#include <iostream>

class Rhomb : public Figure {

    friend std::ostream& operator<<(std::ostream& os, const Rhomb& f);
    friend std::istream& operator>>(std::istream& is, Rhomb& f);

    public:
        Rhomb();
        Rhomb(Point& p1, Point& p2, Point& p3, Point& p4);

        virtual double square() const override;
        virtual Point center() const override;

        Rhomb& operator = (const Rhomb &other);
        Rhomb& operator = (Rhomb &&other);
        bool operator == (const Rhomb &other);
        virtual operator double() const override;

        ~Rhomb(){};

    private:
        static const size_t angles_ = 4;
        Point po[angles_];
};