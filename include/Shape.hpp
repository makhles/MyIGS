/* Shape.h */

#ifndef SHAPE_H
#define SHAPE_H

#include <string>
#include <list>
#include "ShapeType.hpp"

template <class T> class Coord;
class Window;
class AbstractDrawer;
class TMatrix;

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
        virtual const Coord<double> get_centroid() = 0;

        // Visitor
        virtual void accept(AbstractDrawer *drawer) = 0;

        virtual void transform(TMatrix *matrix) = 0;
        void clearViewportCoordinates();
        void addViewportCoordinate(const Coord<int> *coord);
        virtual void clip_to_window(Window *w) = 0;
};

#endif  // SHAPE_H