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
ObjReader::ObjReader()
/* ============================================================================================= */
{
    
}

/* ============================================================================================= */
void ObjReader::clean_shapes(ShapeVector &shapes)
/* ============================================================================================= */
{
    auto shape = shapes.begin();
    while (shape != shapes.end()) {
        delete *shape;
        shape++;
    }
    shapes.clear();
}

/* ============================================================================================= */
bool ObjReader::read_shapes(ShapeVector &shapes, StringVector &filenames)
/* ============================================================================================= */
{
    // Opens several files and read all the shapes
    bool read_ok = false;

    for (auto filename : filenames) {
        if (this->read_wavefront_file(filename)) {
            if (m_contents.empty()) {
                m_status_msg = filename + " is empty.";
                DEBUG_MSG(filename << " is empty.");
                continue;
            }

            if (!this->read_vertices()) {
                break;
            }

            if (!this->create_points(shapes)) {
                break;
            }

            this->create_lines(shapes);
            this->create_wireframes(shapes);
            m_contents.clear();
            read_ok = true;
        }
    }
    if (read_ok) {
        std::stringstream ss;
        ss << shapes.size() << " shapes were added successfully!";
        m_status_msg = ss.str();
    } else {
        ObjReader::clean_shapes(shapes);
    }
    return read_ok;
}

/* ============================================================================================= */
bool ObjReader::read_wavefront_file(const std::string &filename)
/* ============================================================================================= */
{
    // Reads all the lines from the input file and split them into words.
    bool read_ok = true;
    std::ifstream in(filename, std::ios::in | std::ios::binary);
    if (in) {
        std::string line, str;
        StringVector split_line;
        while (std::getline(in, line)) {
            std::istringstream iss(line);
            while (std::getline(iss, str, ' ')) {
                split_line.push_back(str);
            }
            m_contents.push_back(split_line);
            split_line.clear();
        }
        DEBUG_MSG("----------------------");
        DEBUG_MSG("Reading file contents:");
        for (auto line : m_contents) {
            for (unsigned j = 0; j < line.size(); j++) {
                std::cout << " " << line[j] << " ";
            }
            std::cout << std::endl;
        }
        DEBUG_MSG("----------------------");
    } else {
        read_ok = false;
        m_status_msg = "Could not open " + filename;
        DEBUG_MSG("Could not open " << filename << " file.");
    }
    return read_ok;
}

/* ============================================================================================= */
bool ObjReader::read_vertices()
/* ============================================================================================= */
{
    // Reads all the vertices definitions and store them as Coord<double> in m_vertices.
    // All vertices definitions will be erased from contents.
    bool read_ok = true;

    auto line = m_contents.begin();
    while (line != m_contents.end()) {
        if ((*line)[0] == "v") {
            if ((*line).size() == 3) {
                try {
                    double x = std::stod((*line)[1]);
                    double y = std::stod((*line)[2]);
                    Coord<double> coord(x, y);
                    m_vertices.push_back(coord);
                    DEBUG_MSG("New vertex read: (" << x << "," << y << ").");
                }
                catch (const std::invalid_argument& ia) {
                    std::cerr << "Invalid argument: " << ia.what() << '\n';
                    m_status_msg = "Could not read vertex - invalid argument.";
                    read_ok = false;
                    break;
                }
            } else {
                DEBUG_MSG("Could not read vertex - wrong number of line arguments.");
                m_status_msg = "Could not read vertex - wrong number of line arguments.";
                read_ok = false;
                break;
            }
            line = m_contents.erase(line);
        } else {
            line++;
        }
    }
    return read_ok;
}

/* ============================================================================================= */
bool ObjReader::create_points(ShapeVector &shapes)
/* ============================================================================================= */
{
    std::string obj_name;
    bool read_ok = true;

    for (unsigned i = 0; i < m_contents.size(); i++) {
        auto line = m_contents[i];
        if (line[0] == "p") {
            if (line.size() == 2) {
                if (i > 0 && m_contents[i-1][0] == "o" && m_contents[i-1].size() >= 2) {
                    obj_name = m_contents[i-1][1];
                } else {
                    obj_name = "Nameless_point_" + std::to_string(i);
                }
                try {
                    unsigned int vertex = std::stoi(line[1]);
                    double x = m_vertices[vertex-1].x();
                    double y = m_vertices[vertex-1].y();
                    shapes.push_back(new Point(obj_name, x, y));
                    DEBUG_MSG("New point created: " << obj_name << "(" << x << "," << y << ").");
                }
                catch (const std::invalid_argument& ia) {
                    std::cerr << "Invalid argument: " << ia.what() << '\n';
                    m_status_msg = "Could not read point - invalid argument.";
                    read_ok = false;
                    break;
                }
            } else {
                DEBUG_MSG("Could not read point - wrong number of line arguments.");
                m_status_msg = "Could not read point - wrong number of line arguments.";
                read_ok = false;
                break;
            }
        }
    }
    return read_ok;
}

/* ============================================================================================= */
void ObjReader::create_lines(ShapeVector &shapes)
/* ============================================================================================= */
{
    // TODO
}

/* ============================================================================================= */
void ObjReader::create_wireframes(ShapeVector &shapes)
/* ============================================================================================= */
{
    // TODO
}