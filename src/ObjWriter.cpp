// ObjWriter.cpp
// Authors: Leonardo Vailatti Eichstaedt
//          Makhles Reuter Lange

#include "ObjWriter.hpp"
#include "Point.hpp"
#include "Line.hpp"
#include "Wireframe.hpp"
#include "Curve2D.hpp"

/* ============================================================================================= */
ObjWriter::ObjWriter()
/* ============================================================================================= */
{
    m_file.open("Wavefront.obj", std::ios::out);
    if (!m_file.is_open()) {
        std::cout << "Could not open Wavefront.obj file." << std::endl;
    }
}

/* ============================================================================================= */
ObjWriter::~ObjWriter()
/* ============================================================================================= */
{
    if (m_file.is_open()) {
        m_file.close();
    }
}

/* ============================================================================================= */
void ObjWriter::write_to_file(Point &p)
/* ============================================================================================= */
{
    std::vector<unsigned> indexes;
    indexes.push_back(this->vertex_index(p));
    ObjWriter::shape_t s(indexes, p.name(), "p");
    m_points.push_back(s);
}

/* ============================================================================================= */
void ObjWriter::write_to_file(Line &line)
/* ============================================================================================= */
{
    std::cout << "Writing line to obj file..." << std::endl;
    Point *p;
    std::size_t idx;
    std::vector<unsigned> indexes;

    // First point
    p = line.p1();
    idx = this->vertex_index(*p);
    indexes.push_back(idx);

    // Second point
    p = line.p2();
    idx = this->vertex_index(*p);
    indexes.push_back(idx);

    ObjWriter::shape_t s(indexes, line.name(), "l");
    m_lines.push_back(s);
}

/* ============================================================================================= */
void ObjWriter::write_to_file(Wireframe &w)
/* ============================================================================================= */
{
    int idx;
    const std::vector<Point*> vertices = w.vertices();
    std::vector<unsigned> indexes;

    for (unsigned i = 0; i < vertices.size(); i++) {
        idx = this->vertex_index(*vertices[i]);
        indexes.push_back(idx);
    }

    ObjWriter::shape_t s(indexes, w.name(), "f");
    m_wireframes.push_back(s);
}

/* ============================================================================================= */
void ObjWriter::write_to_file(Curve2D &curve)
/* ============================================================================================= */
{
    // TODO
}

/* ============================================================================================= */
void ObjWriter::write_to_file()
/* ============================================================================================= */
{
    for (Coord<double> vertex : m_vertices) {
        m_file << "v " << vertex.x() << " " << vertex.y() << "\n";
    }
    ObjWriter::write_to_file(m_points);
    ObjWriter::write_to_file(m_lines);
    ObjWriter::write_to_file(m_wireframes);
    m_file.flush();
}

/* ============================================================================================= */
void ObjWriter::write_to_file(const std::vector<shape_t> &shapes)
/* ============================================================================================= */
{
    for (auto &s : shapes) {
        m_file << "o " << s.name << "\n";
        m_file << s.token;
        for (auto index : s.indexes) {
            m_file << " " << index;
        }
        m_file << "\n";
    }
}

/* ============================================================================================= */
std::size_t ObjWriter::vertex_index(const Point &p_toFind)
/* ============================================================================================= */
{
    // Searches for the coordinates of the point in the vertices vector and returns its index +1
    // (vertex indexation starts at 1 in the wavefront file). If it is not found, a new vertex is
    // added to the vertices vector.
    std::size_t index;
    bool found = false;
    for (std::size_t i = 0; i < m_vertices.size(); i++) {
        if (m_vertices[i].x() == p_toFind.xwc() && 
            m_vertices[i].y() == p_toFind.ywc())
        {
            found = true;
            index = i+1;
            break;
        }
    }
    if (!found) {
        // Adds this point's coordinates to the list of vertices.
        Coord<double> vertex(p_toFind.xwc(), p_toFind.ywc());
        m_vertices.push_back(vertex);
        index = m_vertices.size();
    }
    return index;
}