/* Point.h */

#ifndef LINE_H
#define LINE_H

#include "Shape.h"

class Point;

class Line : public Shape {
    protected:
        const Point *_p1;
        const Point *_p2;
    public:
        Line(const std::string &name, const Point *p1, const Point *p2);
        ~Line();
        const Point* get_p1() const {return _p1;}
        const Point* get_p2() const {return _p2;}
};
#endif