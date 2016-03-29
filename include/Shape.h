/* Shape.h */

#ifndef SHAPE_H
#define SHAPE_H

#include <string>
#include <list>
#include "ShapeType.h"

template <class T> class Coord;
class WorldWindow;

class Shape {

    protected:
        std::string _name;
        ShapeType _type;
        std::list<Coord<double>*> _wCoords;
        std::list<const Coord<int>*> _vpCoords;

    protected:
        Shape(const std::string name, const ShapeType type);

    public:
        virtual ~Shape() {}
        std::string get_name() const {return _name;}
        ShapeType get_type() const {return _type;}
        const std::list<Coord<double>*>* getWindowCoordinates() const {return &_wCoords;}
        const std::list<const Coord<int>*>* getViewportCoordinates() const {return &_vpCoords;}
        void clearViewportCoordinates();
        void addViewportCoordinate(const Coord<int> *coord);
        virtual void clipToWindow(WorldWindow *w) = 0;
};

#endif  // SHAPE_H