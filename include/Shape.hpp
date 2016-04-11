// Shape.hpp
// Authors: Leonardo Vailatti Eichstaedt
//          Makhles Reuter Lange

#ifndef SHAPE_H
#define SHAPE_H

#include <string>
#include <list>
#include "ShapeType.hpp"

// Forward declarations
template <class T> class Coord;
class Window;
class AbstractDrawer;
class TMatrix;

typedef std::list<Coord<double>*> DCoordList;
typedef std::list<const Coord<int>*> ICoordList;


class Shape {
protected:
    std::string m_name;
    ShapeType m_type;
    DCoordList m_wcList;  // Window coordinates
    DCoordList m_ncList;  // Normalized coordinates
    ICoordList m_vpList;  // Viewport coordinates

    Shape(const std::string name, const ShapeType type);

public:
    virtual ~Shape() {}

    //ShapeType get_type() const {return m_type;}
    std::string name() const { return m_name; }
    const DCoordList* normalized_coordinates() const { return &m_ncList; }
    const ICoordList* viewport_coordinates() const { return &m_vpList; }
    virtual const Coord<double> get_centroid() = 0;

    virtual void accept(AbstractDrawer *drawer) = 0;  // Visitor

    virtual void transform(TMatrix &matrix) = 0;
    virtual void normalize(TMatrix &matrix) = 0;

    void clear_viewport_coordinates();
    void add_viewport_coordinate(const Coord<int> *coord);
    virtual void clip_to_window(Window &w) = 0;
};

#endif  // SHAPE_H