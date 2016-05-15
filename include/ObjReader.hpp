// ObjReader.hpp
// Authors: Leonardo Vailatti Eichstaedt
//          Makhles Reuter Lange

#ifndef OBJ_READER_HPP
#define OBJ_READER_HPP

#include <vector>
#include "Writer.hpp"

// Forward declarations
template <class T> class Coord;
class Shape;
class Point;

typedef std::vector<Shape*> ShapePVector;
typedef std::vector<Coord<double>> CoordVector;
typedef std::vector<std::string> StringVector;
typedef std::vector<bool> BoolVector;

class ObjReader {
public:
    ObjReader();
    ~ObjReader() {}

    void read_shapes(ShapePVector &shapes, StringVector &filenames);
    void read_vertices();
    void create_lines(ShapePVector &shapes);
    void create_wireframes(ShapePVector &shapes);
    void create_points(ShapePVector &shapes);

    // Own methods
    Point* new_point(int idx) const;

private:
    int m_vCount;          // Total number of vertices read.
    CoordVector m_coords;  // Vertices definitions.
    BoolVector m_points;   // Points to be stored as standalone shapes.

    void get_file_contents(StringVector&, std::string&) const;
};

#endif  // OBJ_READER_HPP