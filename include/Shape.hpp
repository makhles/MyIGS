// Shape.hpp
// Authors: Leonardo Vailatti Eichstaedt
//          Makhles Reuter Lange

#ifndef SHAPE_H
#define SHAPE_H

#include <string>
#include <vector>
#include "ShapeType.hpp"
#include "Colour.hpp"

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
    DCoordVector m_ncCoord;  // Normalized coordinates
    ICoordVector m_vpCoord;  // Viewport coordinates
    const Colour m_colour;

    Shape(const std::string name, const ShapeType type, const Colour colour = Colour()) :
        m_name(name),
        m_type(type),
        m_colour(colour)
    {
    }
    void clear_normalized_coords();

public:
    virtual ~Shape();

    std::string name() const { return m_name; }
    ShapeType type() const { return m_type; }
    const Colour& colour() const { return m_colour; }
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