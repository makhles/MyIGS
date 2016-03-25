/* Point.h */

#ifndef POINT_H
#define POINT_H

#include "Shape.h"

class Point : public Shape {
    friend class Line;
    private:
        const double _xPos;
        const double _yPos;
    public:
        Point(const std::string name, const double &xPos, const double &yPos);
        ~Point();
        const double get_xPos() const {return _xPos;}
        const double get_yPos() const {return _yPos;}
};

#endif  // POINT_H