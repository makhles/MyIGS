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
typedef std::vector<Shape*> ShapePVector;
typedef std::vector<Point*> PointVector;
typedef std::vector<std::string> StringVector;

class ObjReader {
public:
    ObjReader();
    ~ObjReader();

    void read_shapes(ShapePVector &shapes, StringVector &filenames);
    bool read_vertices(StringVector&);
    void create_lines(ShapePVector &shapes);
    void create_wireframes(ShapePVector &shapes);
    void create_points(ShapePVector &shapes);

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