// ShapeDrawer.cpp
// Authors: Leonardo Vailatti Eichstaedt
//          Makhles Reuter Lange

// For debugging, uncomment the following define
//#define DEBUG
#ifdef DEBUG
#define DEBUG_MSG(str) do { std::cout << str << std::endl; } while( false )
#else
#define DEBUG_MSG(str) do { } while ( false )
#endif

#include <iostream>
#include "ShapeDrawer.hpp"
#include "Point.hpp"
#include "Line.hpp"
#include "Wireframe.hpp"
#include "Coord.hpp"
#include "Curve2D.hpp"

typedef std::vector<const Coord<int>*> ICoordVector;


void ShapeDrawer::draw(Point &point) {
    const ICoordVector& coordinates = point.viewport_coordinates();
    if (coordinates.size() == 1) {
        auto coord = coordinates[0];
        m_cr->set_line_cap(Cairo::LINE_CAP_ROUND);
        m_cr->set_line_width(2.0);
        m_cr->move_to(coord->x(), coord->y());
        m_cr->line_to(coord->x(), coord->y());
        m_cr->stroke();
        DEBUG_MSG("coord = (" << coord->x() << "," << coord->y() << ")");
    }
}

void ShapeDrawer::draw(Line &line) {
    const ICoordVector& coordinates = line.viewport_coordinates();
    if (coordinates.size() == 2) {
        DEBUG_MSG("Drawing line");
        m_cr->set_line_cap(Cairo::LINE_CAP_SQUARE);
        m_cr->set_line_width(1.0);
        auto coord = coordinates.cbegin();
        m_cr->move_to((*coord)->x(), (*coord)->y());
        coord++;
        m_cr->line_to((*coord)->x(), (*coord)->y());
        m_cr->stroke();
    }
}

void ShapeDrawer::draw(Wireframe &wf) {
    const ICoordVector& coordinates = wf.viewport_coordinates();

    if (!coordinates.empty()) {
        m_cr->set_line_cap(Cairo::LINE_CAP_SQUARE);
        m_cr->set_line_width(1.0);

        int x, y, x0, y0;
        auto coord = coordinates.cbegin();

        x = x0 = (*coord)->x();
        y = y0 = (*coord)->y();
        m_cr->move_to(x,y);
        coord++;

        while (coord != coordinates.cend()) {
            x = (*coord)->x();
            y = (*coord)->y();
            DEBUG_MSG("line_to -> (" << x << "," << y << ")");
            m_cr->line_to(x,y);
            coord++;
        }

        // Go back to first point
        m_cr->line_to(x0,y0);

        // Stroke and fill it
        if (wf.filled()) {
            m_cr->save();
            m_cr->set_source_rgba(0.0, 0.0, 0.0, 0.4);  // Light gray fill
            m_cr->fill_preserve();
            m_cr->restore();  // Back in black (TAM... TAMDAMDAMMM)
        }
        m_cr->stroke();
    }
}


void ShapeDrawer::draw(Curve2D &curve) {
    const ICoordVector& coords = curve.viewport_coordinates();

    if (!coords.empty()) {
        m_cr->set_line_cap(Cairo::LINE_CAP_SQUARE);
        m_cr->set_line_width(1.0);

        int x = coords[0]->x();
        int y = coords[0]->y();
        m_cr->move_to(x,y);

        for (unsigned i = 0; i < coords.size(); i++) {
            x = coords[i]->x();
            y = coords[i]->y();
            DEBUG_MSG("line_to -> (" << x << "," << y << ")");
            m_cr->line_to(x,y);
        }
        m_cr->stroke();
    }
}