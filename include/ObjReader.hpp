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
    struct shape_t {
        std::vector<unsigned> indexes;
        std::string name;
        std::string token;
        shape_t(std::vector<unsigned> idx, std::string n, std::string t)
            : indexes(idx), name(n), token(t) {}
    };

public:
    ObjReader();
    ~ObjReader() {}

    void clean_shapes(ShapeVector &shapes);
    bool read_shapes(ShapeVector &shapes, StringVector &filenames);
    bool read_vertices();
    std::string get_status_msg() const { return m_status_msg; }

private:
    std::vector<StringVector> m_contents;
    std::vector<material_t> m_materials;
    CoordVector m_vertices;
    std::string m_status_msg;
    std::string m_mtl_filename;

private:
    bool read_wavefront_file(const std::string&);
    bool read_materials_file(const std::string&);
    bool create_shapes(ShapeVector&);
    bool search_material(const std::string&, unsigned&);

};

#endif  // OBJ_READER_HPP