// ObjWriter.hpp
// Authors: Leonardo Vailatti Eichstaedt
//          Makhles Reuter Lange

#ifndef OBJ_WRITER_HPP
#define OBJ_WRITER_HPP

#include <fstream>
#include <iostream>
#include <vector>
#include "Writer.hpp"
#include "Coord.hpp"

// Definitions
typedef std::vector<Coord<double>> CoordVector;

class ObjWriter : public Writer {
private:
    struct shape_t {
        std::vector<unsigned> indexes;
        std::string name;
        std::string token;
        shape_t(std::vector<unsigned> idx, std::string n, std::string t)
            : indexes(idx), name(n), token(t) {}
    };

public:
    ObjWriter();
    ~ObjWriter();

    // Overriden methods
    void write_to_file(Point &p) override;
    void write_to_file(Line &l) override;
    void write_to_file(Wireframe &w) override;
    void write_to_file(Curve2D &curve) override;
    void write_to_file() override;

    void write_to_file(const std::vector<shape_t> &shapes);

    // Own methods
    std::size_t vertex_index(const Point &p_toFind);

private:
    std::ofstream m_file;
    CoordVector m_vertices;
    std::vector<shape_t> m_points;
    std::vector<shape_t> m_lines;
    std::vector<shape_t> m_wireframes;
};

#endif  // OBJ_WRITER_HPP