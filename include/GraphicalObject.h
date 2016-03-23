/* GraphicalObject.h */
#ifndef GRAPHICALOBJECT_H
#define GRAPHICALOBJECT_H

#include <string>
#include "ObjectType.h"

class GraphicalObject {
    protected:
        std::string _name;
        ObjectType _type;
    protected:
        GraphicalObject(const std::string name, const ObjectType type);
    public:
        std::string get_name() const {return _name;}
        ObjectType get_type() const {return _type;}
};
#endif