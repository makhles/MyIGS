// ObjReader.cpp
// Authors: Leonardo Vailatti Eichstaedt
//          Makhles Reuter Lange

#include <fstream>
#include <iostream>
#include <stdexcept>      // std::invalid_argument
#include <sstream>        // std::istringstream
#include "ObjReader.hpp"
#include "Coord.hpp"
#include "Shape.hpp"
#include "Point.hpp"
#include "Line.hpp"
#include "Wireframe.hpp"
#include "Curve2D.hpp"

// For debugging, uncomment the following define
#define DEBUG
#ifdef DEBUG
#define DEBUG_MSG(str) do { std::cout << str << std::endl; } while( false )
#else
#define DEBUG_MSG(str) do { } while ( false )
#endif

/* ============================================================================================= */
ObjReader::ObjReader() : m_vCount(0)
/* ============================================================================================= */
{
    
}

/* ============================================================================================= */
ObjReader::~ObjReader()
/* ============================================================================================= */
{
    auto vertex = m_vertices.begin();
    while (vertex != m_vertices.end()) {
        delete *vertex;
        vertex++;
    }
    m_vertices.clear();
}

/* ============================================================================================= */
void ObjReader::read_shapes(ShapePVector &shapes, StringVector &filenames)
/* ============================================================================================= */
{
    // Opens several files and read all the shapes
    for (auto filename : filenames) {
        StringVector contents;
        this->get_file_contents(contents, filename);
        if (contents.size() > 0) {
            if (!this->read_vertices(contents)) {
                break;
            }
            this->create_lines(shapes);
            this->create_wireframes(shapes);
            this->create_points(shapes);
        }
    }
}

/* ============================================================================================= */
void ObjReader::get_file_contents(StringVector &contents, std::string &filename) const
/* ============================================================================================= */
{
    std::ifstream in(filename, std::ios::in | std::ios::binary);
    if (in) {
        std::string line;
        while (std::getline(in, line)) {
            contents.push_back(line);
        }
    } else {
        DEBUG_MSG("Could not open " << filename << " file.");
    }
}

/* ============================================================================================= */
bool ObjReader::read_vertices(StringVector &contents)
/* ============================================================================================= */
{
    // Reads all the vertices definitions and store them as Points in m_coords.
    StringVector vstring;       // Vector that holds each substring in line.
    std::string str;            // Current substring.
    bool read_ok = true;

    auto line = contents.begin();
    while (line != contents.end()) {
        if ((*line)[0] == 'v') {
            std::istringstream iss(*line);
            while (std::getline(iss, str, ' ')) {
                vstring.push_back(str);
            }
            if (vstring.size() == 3) {
                try {
                    double x = std::stod(vstring[1]);
                    double y = std::stod(vstring[2]);
                    m_vertices.push_back(new Coord<double>(x, y));
                    DEBUG_MSG("New vertex read: (" << x << "," << y << ").");
                }
                catch (const std::invalid_argument& ia) {
                    std::cerr << "Invalid argument: " << ia.what() << '\n';
                    read_ok = false;
                    break;
                }
            } else {
                DEBUG_MSG("Could not read vertex.");
                read_ok = false;
                break;
            }
            vstring.clear();
            line = contents.erase(line);
        } else {
            line++;
        }
    }
    return read_ok;
}

/* ============================================================================================= */
void ObjReader::create_lines(ShapePVector &shapes)
/* ============================================================================================= */
{
    // TODO
}

/* ============================================================================================= */
void ObjReader::create_wireframes(ShapePVector &shapes)
/* ============================================================================================= */
{
    // TODO
}

/* ============================================================================================= */
void ObjReader::create_points(ShapePVector &shapes)
/* ============================================================================================= */
{
    // TODO
}

/* ============================================================================================= */
Point* ObjReader::new_point(int idx) const
/* ============================================================================================= */
{
    // Creates a new point. The index refers to the Coord<double> element in m_coords.
    // TODO
    return new Point("", 10, 10);  // to be changed
}