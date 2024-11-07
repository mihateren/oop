#include "../include/Rhomb.h"

Rhomb::Rhomb() : points{Point(), Point(), Point(), Point()} {}

Rhomb::Rhomb(Point& p1, Point& p2, Point& p3, Point& p4) : points{p1, p2, p3, p4}  {}

Point Rhomb::center() const {
    double x = 0, y = 0;
    for(size_t i = 0; i < angles_; ++i){
        x += points[i].x_;
        y += points[i].y_;
    }
    return Point(x / angles_, y / angles_);
}

double Rhomb::square() const {
    double x1 = points[0].x_; double y1 = points[0].y_;
    double x2 = points[1].x_; double y2 = points[1].y_;
    double x3 = points[2].x_; double y3 = points[2].y_;
    double x4 = points[3].x_; double y4 = points[3].y_;

    double S = abs(x1*y2 + x2*y3 + x3*y4 + x4*y1 - x2*y1 - x3*y2 - x4*y3 - x1*y4) / 2.0;
    return S;
}

Rhomb& Rhomb::operator = (const Rhomb &other){
    if (this == &other) {
        return *this;
    }

    for(size_t i = 0; i < angles_; ++i){
        points[i] = other.points[i];
    }

    return *this;
}

Rhomb& Rhomb::operator = (Rhomb &&other){
    if (this == &other) {
        return *this;
    }

    for(size_t i = 0; i < angles_; ++i){
        points[i] = std::move(other.points[i]);
    }

    return *this;
}


bool Rhomb::operator == (const Rhomb& other){
    for(size_t i = 0; i < angles_; ++i){
        if(points[i] != other.points[i]){
            return false;
        }
    }
    return true;
}

std::ostream& operator << (std::ostream& os, const Rhomb& Rhomb){
    for(size_t i = 0; i < Rhomb::angles_; ++i){
        os << Rhomb.points[i] << std::endl;
    }
    return os;
}

std::istream& operator >> (std::istream& is, Rhomb& Rhomb) {
    std::cout << "Enter rhomb nodes in format (x1 y1 x2 y2 x3 y3 x4 y4): " << std::endl;
    for (size_t i = 0; i < Rhomb::angles_; ++i) {
        is >> Rhomb.points[i];
    }
    return is;
}

Rhomb::operator double() const{
    return square();
}