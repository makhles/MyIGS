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
void ObjReader::read_shapes(ShapeVector &shapes, StringVector &filenames)
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
            if (!this->create_points(contents, shapes)) {
                break;
            }
            this->create_lines(contents, shapes);
            this->create_wireframes(contents, shapes);
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
    // Reads all the vertices definitions and store them as Coord<double> in m_vertices.
    // It is made the assumption that all vertices definitions were in the beginning of
    // the file. All vertices definitions will be erased from contents.
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
            // All vertices definitions are in the beginning of the file.
            break;
        }
    }
    return read_ok;
}

/* ============================================================================================= */
bool ObjReader::create_points(StringVector &contents, ShapeVector &shapes)
/* ============================================================================================= */
{
    StringVector vstring;  // Vector that holds each substring in line.
    std::string str;       // Current substring.
    std::string obj_name;
    bool read_ok = true;

    auto line = contents.begin();
    while (line != contents.end()) {
        if ((*line)[0] == 'o') {
            obj_name = (*line).substr(2);
            line = contents.erase(line);
        } else if ((*line)[0] == 'p') {
            std::istringstream iss(*line);
            while (std::getline(iss, str, ' ')) {
                vstring.push_back(str);
            }
            if (vstring.size() == 2) {
                try {
                    unsigned int vertex = std::stoi(vstring[1]);
                    double x = m_vertices[vertex-1]->x();
                    double y = m_vertices[vertex-1]->y();
                    shapes.push_back(new Point(obj_name, x, y));
                    DEBUG_MSG("New point created: " << obj_name << "(" << x << "," << y << ").");
                }
                catch (const std::invalid_argument& ia) {
                    std::cerr << "Invalid argument: " << ia.what() << '\n';
                    read_ok = false;
                    break;
                }
            } else {
                DEBUG_MSG("Could not read point.");
                read_ok = false;
                break;
            }
            vstring.clear();
            line = contents.erase(line);
        } else {
            // We're not interested in other kinds of definitions now.
            break;
        }
    }
    return read_ok;
}

/* ============================================================================================= */
void ObjReader::create_lines(StringVector &contents, ShapeVector &shapes)
/* ============================================================================================= */
{
    // TODO
}

/* ============================================================================================= */
void ObjReader::create_wireframes(StringVector &contents, ShapeVector &shapes)
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