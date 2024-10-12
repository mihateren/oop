#include "../include/Pentagon.h"

using namespace std;

Pentagon::Pentagon() : po{Point(), Point(), Point(), Point(), Point()} {}

Pentagon::Pentagon(Point& p1, Point& p2, Point& p3, Point& p4, Point& p5) :
        po{p1, p2, p3, p4, p5} {}

Point Pentagon::center() const {
    double x = 0, y = 0;
    for(size_t i = 0; i < angles_; ++i){
        x += po[i].x_;
        y += po[i].y_;
    }
    return Point(x / angles_, y / angles_);
}

double Pentagon::square() const {
    double x1 = po[0].x_; double y1 = po[0].y_;
    double x2 = po[1].x_; double y2 = po[1].y_;
    double x3 = po[2].x_; double y3 = po[2].y_;
    double x4 = po[3].x_; double y4 = po[3].y_;
    double x5 = po[4].x_; double y5 = po[4].y_;

    double S = abs(x1*y2 + x2*y3 + x3*y4 + x4*y5 + x5*y1 - y1*x2 - y2*x3 - y3*x4 - y4*x5 - y5 *x1)/2.0;
    return S;
}

Pentagon& Pentagon::operator = (const Pentagon &other){
    if (this == &other) {
    return *this;
    }

    for(size_t i = 0; i < angles_; ++i){
        po[i] = other.po[i];
    }

    return *this;
}

Pentagon& Pentagon::operator = (Pentagon &&other){
    if (this == &other) {
        return *this;
    }


    for(size_t i = 0; i < angles_; ++i){
        po[i] = move(other.po[i]);        
    }

    return *this;
}

bool Pentagon::operator == (const Pentagon &other){
    for(size_t i = 0; i < angles_; ++i){
        if(po[i] != other.po[i]){
            return false;
        }
    }
    return true;
}


ostream& operator << (ostream& os, const Pentagon &pentagon){
    for(size_t i = 0; i < Pentagon::angles_; ++i){
        os << pentagon.po[i] << endl;
    }
    return os;

}

istream& operator >> (istream& is, Pentagon &pentagon){
    cout << "Enter pentagon nodes in format (x1 y1 x2 y2 x3 y3 x4 y4 x5 y5): " << endl;
    for(size_t i = 0; i < Pentagon::angles_; ++i){
         is >> pentagon.po[i];
    }
    return is;
}

Pentagon::operator double() const{
    return square();
}