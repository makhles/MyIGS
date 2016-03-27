/* Shape.h */

#ifndef SHAPE_H
#define SHAPE_H

#include <string>
#include <list>
#include <cstddef>  // For size_t
#include "ShapeType.h"

template <class T> class Coord;
class WorldWindow;

class Shape {

    protected:
        std::string _name;
        ShapeType _type;
        std::list<Coord<double>*> _wCoords;
        std::list<const Coord<size_t>*> _vpCoords;

    protected:
        Shape(const std::string name, const ShapeType type);

    public:
        virtual ~Shape() {}
        std::string get_name() const {return _name;}
        ShapeType get_type() const {return _type;}
        const std::list<Coord<double>*>* getWindowCoordinates() const {return &_wCoords;}
        const std::list<const Coord<size_t>*>* getViewportCoordinates() const {return &_vpCoords;}
        void clearViewportCoordinates();
        void addViewportCoordinate(const Coord<size_t> *coord);
        virtual void clipToWindow(WorldWindow *w) = 0;
};

#endif  // SHAPE_H