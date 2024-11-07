#include "../include/Hexagon.h"

Hexagon::Hexagon() : points{Point(), Point(), Point(), Point()} {}

Hexagon::Hexagon(Point& p1, Point& p2, Point& p3, Point& p4, Point& p5, Point& p6) : 
        points{p1, p2, p3, p4, p5, p6}  {}

Point Hexagon::center() const {
    double x = 0, y = 0;
    for(size_t i = 0; i < angles_; ++i){
        x += points[i].x_;
        y += points[i].y_;
    }
    return Point(x / angles_, y / angles_);
}

double Hexagon::square() const {
    double x1 = points[0].x_; double y1 = points[0].y_;
    double x2 = points[1].x_; double y2 = points[1].y_;
    double x3 = points[2].x_; double y3 = points[2].y_;
    double x4 = points[3].x_; double y4 = points[3].y_;
    double x5 = points[4].x_; double y5 = points[4].y_;
    double x6 = points[5].x_; double y6 = points[5].y_;

    double S = abs(x1*y2 + x2*y3 + x3*y4 + x4*y5 + x5*y6 + x6*y1 - x2*y1 - x3*y2 - x4*y3 - x5*y4 - x6*y5 - x1*y6) / 2.0;
    return S;
}

Hexagon& Hexagon::operator = (const Hexagon &other){
    if (this == &other) {
        return *this;
    }

    for(size_t i = 0; i < angles_; ++i){
        points[i] = other.points[i];
    }

    return *this;
}

Hexagon& Hexagon::operator = (Hexagon &&other){
    if (this == &other) {
        return *this;
    }

    for(size_t i = 0; i < angles_; ++i){
        points[i] = std::move(other.points[i]);
    }

    return *this;
}

bool Hexagon::operator == (const Hexagon& other){
    for(size_t i = 0; i < angles_; ++i){
        if(points[i] != other.points[i]){
            return false;
        }
    }
    return true;
}

std::ostream& operator << (std::ostream& os, const Hexagon& Hexagon){
    for(size_t i = 0; i < Hexagon::angles_; ++i){
        os << Hexagon.points[i] << std::endl;
    }
    return os;
}

std::istream& operator >> (std::istream& is, Hexagon& Hexagon) {
    std::cout << "Enter hexagon nodes in format (x1 y1 x2 y2 x3 y3 x4 y4 x5 y5 x6 y6): " << std::endl;
    for (size_t i = 0; i < Hexagon::angles_; ++i) {
         is >> Hexagon.points[i];
    }
    return is;
}

Hexagon::operator double() const{
    return square();
}