#include "../include/Rhomb.h"

using namespace std;

Rhomb::Rhomb() : po{Point(), Point(), Point(), Point()} {}

Rhomb::Rhomb(Point& p1, Point& p2, Point& p3, Point& p4) : po{p1, p2, p3, p4}  {}

Point Rhomb::center() const {
    double x = 0, y = 0;
    for(size_t i = 0; i < angles_; ++i){
        x += po[i].x_;
        y += po[i].y_;
    }
    return Point(x / angles_, y / angles_);
}

double Rhomb::square() const {
    double x1 = po[0].x_; double y1 = po[0].y_;
    double x2 = po[1].x_; double y2 = po[1].y_;
    double x3 = po[2].x_; double y3 = po[2].y_;
    double x4 = po[3].x_; double y4 = po[3].y_;

    double S = abs(x1*y2 + x2*y3 + x3*y4 + x4*y1 - x2*y1 - x3*y2 - x4*y3 - x1*y4) / 2.0;
    return S;
}

Rhomb& Rhomb::operator = (const Rhomb &other){
    if (this == &other) {
        return *this;
    }

    for(size_t i = 0; i < angles_; ++i){
        po[i] = other.po[i];
    }

    return *this;
}

Rhomb& Rhomb::operator = (Rhomb &&other){
    if (this == &other) {
        return *this;
    }

    for(size_t i = 0; i < angles_; ++i){
        po[i] = move(other.po[i]);
    }

    return *this;
}


bool Rhomb::operator == (const Rhomb& other){
    for(size_t i = 0; i < angles_; ++i){
        if(po[i] != other.po[i]){
            return false;
        }
    }
    return true;
}

ostream& operator << (ostream& os, const Rhomb& Rhomb){
    for(size_t i = 0; i < Rhomb::angles_; ++i){
        os << Rhomb.po[i] << endl;
    }
    return os;
}

istream& operator >> (istream& is, Rhomb& Rhomb) {
    cout << "Enter rhomb nodes in format (x1 y1 x2 y2 x3 y3 x4 y4): " << endl;
    for (size_t i = 0; i < Rhomb::angles_; ++i) {
        is >> Rhomb.po[i];
    }
    return is;
}



Rhomb::operator double() const{
    return square();
}