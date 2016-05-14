// ObjReader.cpp
// Authors: Leonardo Vailatti Eichstaedt
//          Makhles Reuter Lange

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
void ObjReader::read_shapes(ShapePVector &shapes, StringVector &filenames)
/* ============================================================================================= */
{
    // Opens several files and read all the shapes
    for (auto filename : filenames) {
        m_file.open(filename, std::ios::in);
        if (m_file.is_open()) {
            this->read_vertices();
            this->create_lines(shapes);
            this->create_wireframes(shapes);
            this->create_points(shapes);
            m_file.close();
        } else {
            DEBUG_MSG("Could not open " << filename << " file.");
        }
    }
}

/* ============================================================================================= */
void ObjReader::read_vertices()
/* ============================================================================================= */
{
    // Reads all the vertices definitions and store them as Coord<double> in m_coords.
    // Also populates m_points with bool true for every coord created in m_coords.
    // TODO
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
    // Also sets the corresponding m_points[idx] value to bool false.
    // TODO
    return new Point("", 10, 10);  // to be changed
}