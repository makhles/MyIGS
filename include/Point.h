/* Point.h
   Copyright: Makhles Reuter Lange, 2016.
*/

#ifndef POINT_H
#define POINT_H

#include <cstddef>              // For size_t
#include "Shape.h"

class Point : public Shape {
    friend class Line;
    private:
        size_t _xPos;
        size_t _yPos;
    public:
        Point(const std::string name, const size_t &xPos, const size_t &yPos);
        ~Point();
        size_t get_xPos() const {return _xPos;}
        size_t get_yPos() const {return _yPos;}
        void set_xPos(const size_t &xPos) {_xPos = xPos;}
        void set_yPos(const size_t &yPos) {_yPos = yPos;}
};
#endif