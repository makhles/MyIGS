/* Shape.h */
#ifndef Shape_H
#define Shape_H

#include <string>
#include "ObjectType.h"

class Shape {
    protected:
        std::string _name;
        ObjectType _type;
    protected:
        Shape(const std::string name, const ObjectType type);
    public:
        std::string get_name() const {return _name;}
        ObjectType get_type() const {return _type;}
};
#endif