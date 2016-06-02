// Point.cpp
// Authors: Leonardo Vailatti Eichstaedt
//          Makhles Reuter Lange

#include <iostream>
#include "Point.hpp"
#include "Coord.hpp"
#include "AbstractDrawer.hpp"
#include "AbstractClipper.hpp"
#include "TMatrix.hpp"
#include "Writer.hpp"

// For debugging, uncomment the following define
//#define DEBUG
#ifdef DEBUG
#define DEBUG_MSG(str) do { std::cout << str << std::endl; } while( false )
#else
#define DEBUG_MSG(str) do { } while ( false )
#endif

/* ============================================================================================= */
const Coord<double> Point::get_centroid()
/* ============================================================================================= */
{
    return Coord<double>(m_xwc, m_ywc, m_zwc);
}

/* ============================================================================================= */
void Point::accept(AbstractDrawer *drawer)
/* ============================================================================================= */
{
    drawer->draw(*this);
}

/* ============================================================================================= */
void Point::transform(TMatrix &matrix)
/* ============================================================================================= */
{
    std::vector<double> v;
    v.push_back(m_xwc);
    v.push_back(m_ywc);
    v.push_back(m_zwc);
    v.push_back(1.0);
    matrix * v;  // Result is stored in v
    m_xwc = v[0];
    m_ywc = v[1];
    m_zwc = v[2];
}

/* ============================================================================================= */
void Point::normalize(TMatrix &matrix)
/* ============================================================================================= */
{
    DEBUG_MSG("Normalizing point...");
    DEBUG_MSG("xwc = " << m_xwc);
    DEBUG_MSG("ywc = " << m_ywc);
    DEBUG_MSG("zwc = " << m_zwc);
    std::vector<double> v;
    v.push_back(m_xwc);
    v.push_back(m_ywc);
    v.push_back(m_zwc);
    v.push_back(1.0);
    matrix * v;  // Result is stored in v
    m_xnc = v[0];
    m_ync = v[1];
    m_znc = v[2];
    DEBUG_MSG("xnc = " << m_xnc);
    DEBUG_MSG("ync = " << m_ync);
    DEBUG_MSG("znc = " << m_znc);
    DEBUG_MSG("-----------------------------");
    m_ncCoord.clear();
    m_ncCoord.push_back(new Coord<double>(m_xnc, m_ync, m_znc));
}

/* ============================================================================================= */
void Point::clip_to_window(AbstractClipper &clipper)
/* ============================================================================================= */
{
    DEBUG_MSG("Clipping to window.");
    clipper.clip_to_area(*this);
}

/* ============================================================================================= */
void Point::write_to_file(Writer *w)
/* ============================================================================================= */
{
    w->write_to_file(*this);
}

/* ============================================================================================= */
bool Point::operator==(const Point &rhs) const
/* ============================================================================================= */
{
    return ((rhs.m_xwc == m_xwc) && (rhs.m_ywc == m_ywc) && (rhs.m_zwc == m_zwc));
}

/* ============================================================================================= */
bool Point::operator!=(const Point &rhs) const
/* ============================================================================================= */
{
    return !(*this == rhs);
}