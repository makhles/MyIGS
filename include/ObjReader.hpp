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

typedef std::vector<Coord<double>*> CoordVector;
typedef std::vector<Shape*> ShapeVector;
typedef std::vector<Point*> PointVector;
typedef std::vector<std::string> StringVector;

class ObjReader {
public:
    ObjReader();
    ~ObjReader();

    void read_shapes(ShapeVector &shapes, StringVector &filenames);
    bool read_vertices(StringVector&);
    bool create_points(StringVector &contents, ShapeVector &shapes);
    void create_lines(StringVector &contents, ShapeVector &shapes);
    void create_wireframes(StringVector &contents, ShapeVector &shapes);

    // Own methods
    Point* new_point(int idx) const;

private:
    int m_vCount;          // Total number of vertices read.
    PointVector m_points;
    CoordVector m_vertices;

private:
    void get_file_contents(StringVector&, std::string&) const;

};

#endif  // OBJ_READER_HPP