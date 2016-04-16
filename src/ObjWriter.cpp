// ObjWriter.cpp
// Authors: Leonardo Vailatti Eichstaedt
//          Makhles Reuter Lange

#include "ObjWriter.hpp"
#include "Point.hpp"
#include "Line.hpp"
#include "Wireframe.hpp"

ObjWriter::ObjWriter() :
    m_vCount(0)
{
    m_file.open("Wavefront.obj", std::ios::out);
    if (!m_file.is_open()) {
        std::cout << "Could not open Wavefront.obj file." << std::endl;
    }
}


ObjWriter::~ObjWriter() {
    if (m_file.is_open()) {
        m_file.close();
    }
}


void ObjWriter::write_to_file(Point &p) {
    int idx = this->find_point(p);
    if (idx == -1) {
        m_points.push_back(&p);
        m_vCount++;
    } else {
        std::cout << "Point already included." << std::endl;
    }
}


void ObjWriter::write_to_file(Line &l) {
    std::cout << "Writing line to obj file..." << std::endl;
    Point *p;
    int idx;
    // -------- First point ----------------
    p = l.p1();
    idx = this->find_point(*p);
    if (idx == -1) {
        m_points.push_back(p);
        idx = m_vCount++;
    }
    m_linePoints.push_back(idx);
    // -------- Second point ----------------
    p = l.p2();
    idx = this->find_point(*p);
    if (idx == -1) {
        m_points.push_back(p);
        idx = m_vCount++;
    }
    m_linePoints.push_back(idx);
}


void ObjWriter::write_to_file(Wireframe &w) {
    std::vector<unsigned> points;
    int idx;
    const std::vector<Point*> vertices = w.vertices();
    for (unsigned i = 0; i < vertices.size(); i++) {
        idx = this->find_point(*vertices[i]);
        if (idx == -1) {
            m_points.push_back(vertices[i]);
            idx = ++m_vCount;
        } else {
            idx++;
        }
        points.push_back(idx);
    }
    m_wPoints.push_back(points);
}


void ObjWriter::write_to_file() {

    // Write points
    for (unsigned i = 0; i < m_points.size(); i++) {
        m_file << "v " << m_points[i]->xwc() << " " << m_points[i]->ywc() << "\n";
    }

    // Write lines
    for (unsigned i = 0; i < m_linePoints.size(); i += 2) {
        m_file << "l " << m_linePoints[i] << " " << m_linePoints[i+1] << "\n";
    }

    // Write wireframes
    for (unsigned i = 0; i < m_wPoints.size(); i++) {
        m_file << "f";
        for (unsigned j = 0; j < m_wPoints[i].size(); j++) {
            m_file << " " << m_wPoints[i][j];
        }
        m_file << "\n";
    }
    m_file.flush();
}


// Searches for a point in the points vector.
// If it is found, its index is return, otherwise -1.
int ObjWriter::find_point(const Point &p_toFind) const {
    int idx = -1;
    for (unsigned i = 0; i < m_points.size(); i++) {
        if (*m_points[i] == p_toFind) {
            idx = i;
        }
    }
    return idx;
}