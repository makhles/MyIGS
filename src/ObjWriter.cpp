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
    if (this->has_point(p)) {
        std::cout << "Point already included." << std::endl;
    } else {
        m_file << "v " << p.xwc() << " " << p.ywc() << "\n";
        m_points.push_back(&p);
        m_vCount++;
    }
}


void ObjWriter::write_to_file(Line &l) {
    std::cout << "Writing line to obj file..." << std::endl;
    m_file << "Writing line to obj file...";
}


void ObjWriter::write_to_file(Wireframe &w) {
    std::cout << "Writing wireframe to obj file..." << std::endl;
    m_file << "Writing wireframe to obj file...";
}


void ObjWriter::flush() {
    m_file.flush();
}


bool ObjWriter::has_point(Point &p_toFind) const {
    bool found = false;
    auto p = m_points.cbegin();
    while (p != m_points.cend()) {
        if ((**p) == p_toFind) {
            found = true;
        }
        p++;
    }
    return found;
}