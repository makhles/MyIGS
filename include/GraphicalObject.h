/* GraphicalObject.h */
#ifndef GRAPHICALOBJECT_H
#define GRAPHICALOBJECT_H

#include <string>
#include "ObjectType.h"

class GraphicalObject {
    private:
        std::string _name;
        ObjectType _type;
    protected:
        GraphicalObject(const std::string name, const ObjectType type);
};
#endif