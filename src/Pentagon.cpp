#include "../include/Pentagon.h"

using namespace std;

Pentagon::Pentagon() : points{Point(), Point(), Point(), Point(), Point()} {}

Pentagon::Pentagon(Point& p1, Point& p2, Point& p3, Point& p4, Point& p5) :
        points{p1, p2, p3, p4, p5} {}

Point Pentagon::center() const {
    double x = 0, y = 0;
    for(size_t i = 0; i < angles_; ++i){
        x += points[i].x_;
        y += points[i].y_;
    }
    return Point(x / angles_, y / angles_);
}

double Pentagon::square() const {
    double x1 = points[0].x_; double y1 = points[0].y_;
    double x2 = points[1].x_; double y2 = points[1].y_;
    double x3 = points[2].x_; double y3 = points[2].y_;
    double x4 = points[3].x_; double y4 = points[3].y_;
    double x5 = points[4].x_; double y5 = points[4].y_;

    double S = abs(x1*y2 + x2*y3 + x3*y4 + x4*y5 + x5*y1 - y1*x2 - y2*x3 - y3*x4 - y4*x5 - y5 *x1)/2.0;
    return S;
}

Pentagon& Pentagon::operator = (const Pentagon &other){
    if (this == &other) {
    return *this;
    }

    for(size_t i = 0; i < angles_; ++i){
        points[i] = other.points[i];
    }

    return *this;
}

Pentagon& Pentagon::operator = (Pentagon &&other){
    if (this == &other) {
        return *this;
    }


    for(size_t i = 0; i < angles_; ++i){
        points[i] = move(other.points[i]);        
    }

    return *this;
}

bool Pentagon::operator == (const Pentagon &other){
    for(size_t i = 0; i < angles_; ++i){
        if(points[i] != other.points[i]){
            return false;
        }
    }
    return true;
}


ostream& operator << (ostream& os, const Pentagon &pentagon){
    for(size_t i = 0; i < Pentagon::angles_; ++i){
        os << pentagon.points[i] << endl;
    }
    return os;

}

istream& operator >> (istream& is, Pentagon &pentagon){
    cout << "Enter pentagon nodes in format (x1 y1 x2 y2 x3 y3 x4 y4 x5 y5): " << endl;
    for(size_t i = 0; i < Pentagon::angles_; ++i){
         is >> pentagon.points[i];
    }
    return is;
}

Pentagon::operator double() const{
    return square();
}