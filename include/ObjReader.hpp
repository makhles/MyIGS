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

typedef std::vector<Coord<double>> CoordVector;
typedef std::vector<Shape*> ShapeVector;
typedef std::vector<Point*> PointVector;
typedef std::vector<std::string> StringVector;

class ObjReader {
public:
    ObjReader();
    ~ObjReader() {}

    void clean_shapes(ShapeVector &shapes);
    bool read_shapes(ShapeVector &shapes, StringVector &filenames);
    bool read_vertices(StringVector&);
    bool create_points(StringVector &contents, ShapeVector &shapes);
    void create_lines(StringVector &contents, ShapeVector &shapes);
    void create_wireframes(StringVector &contents, ShapeVector &shapes);
    Point* new_point(int idx) const;
    std::string get_status_msg() const { return m_status_msg; }

private:
    PointVector m_points;
    CoordVector m_vertices;
    std::string m_status_msg;

private:
    void get_file_contents(StringVector&, const std::string&);

};

#endif  // OBJ_READER_HPP