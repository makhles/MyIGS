// Shape.hpp
// Authors: Leonardo Vailatti Eichstaedt
//          Makhles Reuter Lange

#ifndef SHAPE_H
#define SHAPE_H

#include <string>
#include <vector>
#include "ShapeType.hpp"

// Forward declarations
template <class T> class Coord;
class AbstractDrawer;
class AbstractClipper;
class TMatrix;
class Writer;

typedef std::vector<Coord<double>*> DCoordVector;
typedef std::vector<const Coord<int>*> ICoordVector;


class Shape {
protected:
    std::string m_name;
    ShapeType m_type;
    // DCoordVector m_wcList;   // Window coordinates
    DCoordVector m_ncCoord;  // Normalized coordinates
    ICoordVector m_vpCoord;  // Viewport coordinates

    Shape(const std::string name, const ShapeType type);
    void clear_normalized_coords();

public:
    virtual ~Shape();

    //ShapeType get_type() const {return m_type;}
    std::string name() const { return m_name; }
    ShapeType type() const { return m_type; }
    const DCoordVector& normalized_coords() const { return m_ncCoord; }
    const ICoordVector& viewport_coordinates() const { return m_vpCoord; }
    virtual const Coord<double> get_centroid() = 0;

    /// Updates the normalized coordinates vector to
    /// be used in the viewport transform.
    void update_normalized_coords(DCoordVector &coords);

    virtual void accept(AbstractDrawer *drawer) = 0;  // Visitor

    virtual void transform(TMatrix &matrix) = 0;
    virtual void normalize(TMatrix &matrix) = 0;

    void clear_viewport_coordinates();
    void add_viewport_coordinate(const Coord<int> *coord);
    virtual void clip_to_window(AbstractClipper &clipper) = 0;
    virtual void write_to_file(Writer *w) = 0;
};

#endif  // SHAPE_H