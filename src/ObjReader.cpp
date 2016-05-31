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
ObjReader::ObjReader() :
    m_mtl_filename("")
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

            if (!this->read_materials_file(m_mtl_filename)) {
                break;
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
            if (split_line[0] == "mtllib" && split_line.size() == 2) {
                m_mtl_filename = split_line[1];
            }
            m_contents.push_back(split_line);
            split_line.clear();
        }
        if (m_mtl_filename == "") {
            read_ok = false;
            m_status_msg = "No material library file was specified.";
            DEBUG_MSG(m_status_msg);
        }
    } else {
        read_ok = false;
        m_status_msg = "Could not open " + filename;
        DEBUG_MSG("Could not open " << filename << " file.");
    }
    return read_ok;
}

/* ============================================================================================= */
bool ObjReader::read_materials_file(const std::string &filename)
/* ============================================================================================= */
{
    bool read_ok = true;
    bool mat_under_construction = false;
    bool diffuse_colours_read = false;
    bool transparency_read = false;
    float red, green, blue, alpha;
    std::string name;

    std::ifstream in(filename, std::ios::in | std::ios::binary);
    if (in) {
        std::string line, str;
        StringVector split_line;

        DEBUG_MSG("----------------------");
        DEBUG_MSG("READING MATERIALS:");

        while (std::getline(in, line)) {
            std::istringstream iss(line);
            while (std::getline(iss, str, ' ')) {
                split_line.push_back(str);
            }

            // NEW MATERIAL
            if (split_line[0] == "newmtl") {
                if(mat_under_construction) {
                    if (diffuse_colours_read && transparency_read) {
                        ObjReader::material_t mat(name, Colour(red, green, blue, alpha));
                        m_materials.push_back(mat);

                        // Reset control flags
                        mat_under_construction = false;
                        diffuse_colours_read = false;
                        transparency_read = false;
                    } else {
                        m_status_msg = "Could not create material - insufficient number of properties.";
                        DEBUG_MSG(m_status_msg);
                        read_ok = false;
                        break;
                    }
                } else {
                    if (split_line.size() == 2) {
                        name = split_line[1];
                        mat_under_construction = true;
                    } else {
                        m_status_msg = "Could not read material definition - wrong number of line arguments.";
                        DEBUG_MSG(m_status_msg);
                        read_ok = false;
                        break;
                    }
                }
            }

            // DIFFUSE COLOUR
            else if (split_line[0] == "Kd") {
                if (mat_under_construction) {
                    if (split_line.size() == 4) {
                        try {
                            red = std::stod(split_line[1]);
                            green = std::stod(split_line[2]);
                            blue = std::stod(split_line[3]);
                            diffuse_colours_read = true;
                        } catch (const std::invalid_argument& ia) {
                            m_status_msg = "Could not read diffuse colour - invalid argument.";
                            DEBUG_MSG(m_status_msg);
                            read_ok = false;
                            break;
                        }
                    } else {
                        m_status_msg = "Could not read diffuse colour - wrong number of line arguments.";
                        DEBUG_MSG(m_status_msg);
                        read_ok = false;
                        break;
                    }
                } else {
                    m_status_msg = "Could not read diffuse colour - a new material must be defined first.";
                    DEBUG_MSG(m_status_msg);
                    read_ok = false;
                    break;
                }
            }

            // TRANSPARENCY
            else if (split_line[0] == "d") {
                if (mat_under_construction) {
                    if (split_line.size() == 2) {
                        try {
                            alpha = std::stod(split_line[1]);
                            transparency_read = true;
                        } catch (const std::invalid_argument& ia) {
                            m_status_msg = "Could not read transparency - invalid argument.";
                            DEBUG_MSG(m_status_msg);
                            read_ok = false;
                            break;
                        }
                    } else {
                        m_status_msg = "Could not read transparency - wrong number of line arguments.";
                        DEBUG_MSG(m_status_msg);
                        read_ok = false;
                        break;
                    }
                } else {
                    m_status_msg = "Could not read transparency - a new material must be defined first.";
                    DEBUG_MSG(m_status_msg);
                    read_ok = false;
                    break;
                }
            }
            split_line.clear();
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