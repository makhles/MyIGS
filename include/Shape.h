/* Shape.h */
#ifndef Shape_H
#define Shape_H

#include <string>
#include "ShapeType.h"

class Shape {
    protected:
        std::string _name;
        ShapeType _type;
    protected:
        Shape(const std::string name, const ShapeType type);
    public:
        std::string get_name() const {return _name;}
        ShapeType get_type() const {return _type;}
};
#endif