// ObjReader.hpp
// Authors: Leonardo Vailatti Eichstaedt
//          Makhles Reuter Lange

#ifndef OBJ_READER_HPP
#define OBJ_READER_HPP

#include <vector>
#include "Writer.hpp"
#include "Colour.hpp"

// Forward declarations
template <class T> class Coord;
class Shape;
class Point;

typedef std::vector<Coord<double>> CoordVector;
typedef std::vector<Shape*> ShapeVector;
typedef std::vector<Point*> PointVector;
typedef std::vector<std::string> StringVector;

class ObjReader {
private:
    struct material_t {
        std::string s_name;
        Colour s_colour;
        material_t(std::string name, Colour colour) :
            s_name(name), s_colour(colour) {}
    };

public:
    ObjReader();
    ~ObjReader() {}

    void clean_shapes(ShapeVector &shapes);
    bool read_shapes(ShapeVector &shapes, StringVector &filenames);
    bool read_vertices();
    bool create_points(ShapeVector &shapes);
    void create_lines(ShapeVector &shapes);
    void create_wireframes(ShapeVector &shapes);
    std::string get_status_msg() const { return m_status_msg; }

private:
    std::vector<StringVector> m_contents;
    CoordVector m_vertices;
    std::string m_status_msg;

private:
    bool read_wavefront_file(const std::string&);

};

#endif  // OBJ_READER_HPP