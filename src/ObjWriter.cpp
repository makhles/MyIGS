// ObjWriter.cpp
// Authors: Leonardo Vailatti Eichstaedt
//          Makhles Reuter Lange

#include "ObjWriter.hpp"

ObjWriter::ObjWriter() :
    m_lineCount(0)
{
    m_file.open("Wavefront.obj", std::ios::out | std::ios::app);
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
    //m_file << "\nv " << m_xnc << " " << m_ync;
    std::cout << "Writing point to obj file..." << std::endl;
    m_file<< "Writing point to obj file...";
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