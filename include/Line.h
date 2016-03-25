/* Point.h
   Copyright: Makhles Reuter Lange, 2016.
*/

#ifndef LINE_H
#define LINE_H

#include <cstddef>              // For size_t
#include "Shape.h"

class Point;

class Line : public Shape {
    protected:
        Point *_p1;
        Point *_p2;
    public:
        Line(const std::string &name, Point *p1, Point *p2);
        ~Line();
        Point* get_p1() const {return _p1;}
        Point* get_p2() const {return _p2;}
        void set_p1(Point *p1) {_p1 = p1;}
        void set_p2(Point *p2) {_p2 = p2;}
};
#endif