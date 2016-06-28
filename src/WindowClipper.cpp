// WindowClipper.cpp
// Authors: Leonardo Vailatti
//          Makhles R. Lange

// For debugging, uncomment the following define
//#define DEBUG
#ifdef DEBUG
#define DEBUG_MSG(str) do { std::cout << str << std::endl; } while( false )
#else
#define DEBUG_MSG(str) do { } while ( false )
#endif

#include <iostream>
#include "WindowClipper.hpp"
#include "Coord.hpp"
#include "Point.hpp"
#include "Line.hpp"
#include "Wireframe.hpp"
#include "Curve2D.hpp"
#include "TMatrix.hpp"

/* ============================================================================================= */
WindowClipper::WindowClipper() :
/* ============================================================================================= */
    m_lineClipping(LineClipping::CS),
    m_polygonClipping(PolygonClipping::SH)
{   
}

/* ============================================================================================= */
void WindowClipper::clip_to_area(Point &p)
/* ============================================================================================= */
{
    double x = p.xnc();
    double y = p.ync();
    DCoordVector newVertice;

    if (x >= X_MIN && x <= X_MAX && y >= Y_MIN && y <= Y_MAX) {
        DEBUG_MSG("Clipped point inside (" << x << "," << y << ")");
        newVertice.push_back(new Coord<double>(x, y));
    } else {
        DEBUG_MSG("Point outside.");
    }
    p.update_normalized_coords(newVertice);
}

/* ============================================================================================= */
void WindowClipper::clip_to_area(Line &line)
/* ============================================================================================= */
{
    switch(m_lineClipping) {
        case LineClipping::CS: this->cohen_sutherland_clipping(line); break;
        case LineClipping::LB: this->liang_barsky_clipping(line); break;
        case LineClipping::NLN: this->nicholl_lee_nicholl_clipping(line); break;
    }
}

/* ============================================================================================= */
void WindowClipper::clip_to_area(Wireframe &wf)
/* ============================================================================================= */
{
    switch(m_polygonClipping) {
        case PolygonClipping::SH: this->SH_clipping(wf); break;
        case PolygonClipping::WA: this->weiler_atherton_clipping(wf); break;
    }
}

/* ============================================================================================= */
void WindowClipper::clip_to_area(Curve2D &curve)
/* ============================================================================================= */
{
    const DCoordVector inVertices = curve.normalized_coords();
    DCoordVector outVertices;

    switch (curve.type()) {
        case ShapeType::BEZIER_CUBIC: this->clip_bezier_curve(inVertices, outVertices); break;
        case ShapeType::BSPLINE:      this->clip_bspline(inVertices, outVertices);      break;
    }
    curve.update_normalized_coords(outVertices);
}

/* ============================================================================================= */
void WindowClipper::clip_bezier_curve(const DCoordVector &inVertices, DCoordVector &outVertices)
/* ============================================================================================= */
{
    DEBUG_MSG("Clipping Bézier curve...");
    bool previous_inside = false;
    const int steps = 100;
    const double dt = 1.0 / (double) steps;
    double t;

    double x0, x1, x2, x3;  // Bézier control points
    double y0, y1, y2, y3;  // Bézier control points
    double b0, b1, b2, b3;  // Bernstein basis polynomials
    double aux1, aux2, t2;  // Auxiliary variables
    double x, y;            // Current point coordinates
    Coord<double> current;
    Coord<double> previous;
    Coord<double> *new_coord;  // Intersection at an edge

    for (unsigned i = 0; i < inVertices.size(); i+=4) {
        DEBUG_MSG("  First curve:");

        x0 = inVertices[i+0]->x();
        x1 = inVertices[i+1]->x();
        x2 = inVertices[i+2]->x();
        x3 = inVertices[i+3]->x();
        y0 = inVertices[i+0]->y();
        y1 = inVertices[i+1]->y();
        y2 = inVertices[i+2]->y();
        y3 = inVertices[i+3]->y();

        DEBUG_MSG("  > Bernstein points read:");
        DEBUG_MSG("    - p0 = (" << x0 << "," << y0 << ")");
        DEBUG_MSG("    - p1 = (" << x1 << "," << y1 << ")");
        DEBUG_MSG("    - p2 = (" << x2 << "," << y2 << ")");
        DEBUG_MSG("    - p3 = (" << x3 << "," << y3 << ")");

        t = 0.0;
        for (unsigned step = 0; step < steps; step++) {
            aux1 = 1.0 - t;
            aux2 = aux1 * aux1;
            t2 = t * t;
            b0 = aux1 * aux2;
            b1 = 3.0 * t * aux2;
            b2 = 3.0 * t2 * aux1;
            b3 = t * t2;
            x = (x0 * b0) + (x1 * b1) + (x2 * b2) + (x3 * b3);
            y = (y0 * b0) + (y1 * b1) + (y2 * b2) + (y3 * b3);

            DEBUG_MSG("  ...................... ");
            DEBUG_MSG("  > t = " << t);
            DEBUG_MSG("  > x = " << x);
            DEBUG_MSG("  > y = " << y);

            if (coord_inside(x, y)) {
                DEBUG_MSG("  > Current point is inside.");
                if (t == 0.0) {
                    // First point doesn't have a previous point, so we set it to true.
                    previous_inside = true;
                }
                if (previous_inside) {
                    // Both current and previous points are inside the clipping window.
                    DEBUG_MSG("  > Previous point was inside.");
                    new_coord = new Coord<double>(x, y);
                    outVertices.push_back(new_coord);
                } else {
                    // Line is entering the window.
                    DEBUG_MSG("  > Previous point was outside.");
                    current.set_x(x);
                    current.set_y(y);
                    new_coord = WindowClipper::SH_intersect(&current, &previous);
                    outVertices.push_back(new_coord);
                    DEBUG_MSG("  > New intersection at (" << new_coord->x() << ","
                                                          << new_coord->y() << ")");
                    new_coord = new Coord<double>(x, y);
                    outVertices.push_back(new_coord);
                    previous_inside = true;
                }
            } else {
                DEBUG_MSG("  > Current point is outside.");
                if (t == 0.0) {
                    // First point doesn't have a previous point, so we set it to false.
                    previous_inside = false;
                }
                if (previous_inside) {
                    // Line is leaving the window
                    DEBUG_MSG("  > Previous point was inside.");
                    current.set_x(x);
                    current.set_y(y);
                    new_coord = WindowClipper::SH_intersect(&current, &previous);
                    DEBUG_MSG("  > New intersection at (" << new_coord->x() << ","
                                                          << new_coord->y() << ")");
                    outVertices.push_back(new_coord);
                    previous_inside = false;
                } else {
                    DEBUG_MSG("  > Previous point was outside.");
                }
            }
            previous.set_x(x);
            previous.set_y(y);
            t += dt;
        }
    }
}

/* ============================================================================================= */
void WindowClipper::clip_bspline(const DCoordVector &inVertices, DCoordVector &outVertices)
/* ============================================================================================= */
{
    DEBUG_MSG("Clipping B-Spline curve...");

    const double delta = 0.01;
    const unsigned n = 100;     // n = 1 / delta
    double d2 = delta * delta;
    double d3 = delta * d2;

    DVector Gx, Gy;  // Geometry vectors
    DVector Cx, Cy;  // Coefficients vectors
    DVector Dx, Dy;  // Initial differences vectors

    TMatrix Mbs(4);  // B-Spline matrix
    TMatrix DD(4);   // Initial differences matrix

    Mbs(0,0) = -1.0;  Mbs(0,1) = +3.0;  Mbs(0,2) = -3.0;  Mbs(0,3) = +1.0;
    Mbs(1,0) = +3.0;  Mbs(1,1) = -6.0;  Mbs(1,2) = +3.0;  Mbs(1,3) = +0.0;
    Mbs(2,0) = -3.0;  Mbs(2,1) = +0.0;  Mbs(2,2) = +3.0;  Mbs(2,3) = +0.0;
    Mbs(3,0) = +1.0;  Mbs(3,1) = +4.0;  Mbs(3,2) = +1.0;  Mbs(3,3) = +0.0;
    Mbs.multiply_by_scalar(1.0 / 6.0);

    DD(0,0) = 0.0;    DD(0,1) = 0.0;    DD(0,2) = 0.0;    DD(0,3) = 1.0;
    DD(1,0) = d3;     DD(1,1) = d2 ;    DD(1,2) = delta;  DD(1,3) = 0.0;
    DD(2,0) = 6*d3;   DD(2,1) = 2*d2;   DD(2,2) = 0.0;    DD(2,3) = 0.0;
    DD(3,0) = 6*d3;   DD(3,1) = 0.0;    DD(3,2) = 0.0;    DD(3,3) = 0.0;

    // Compute number of curves
    unsigned number_of_segments = inVertices.size() - 3;
    DEBUG_MSG("Number of segments: " << number_of_segments);

    for (unsigned i = 0; i < number_of_segments; i++) {
        
        // Mount geometry vectors for the current curve segment
        Gx.push_back(inVertices[i+0]->x());  Gy.push_back(inVertices[i+0]->y());
        Gx.push_back(inVertices[i+1]->x());  Gy.push_back(inVertices[i+1]->y());
        Gx.push_back(inVertices[i+2]->x());  Gy.push_back(inVertices[i+2]->y());
        Gx.push_back(inVertices[i+3]->x());  Gy.push_back(inVertices[i+3]->y());

        DEBUG_MSG("Geometry vectors: ");
        for (unsigned j = 0; j <  Gx.size(); j++) {
            DEBUG_MSG("Gx[" << j << "] = " << Gx[j] << "\t" << "Gy[" << j << "] = " << Gy[j]);
        }

        // Compute coefficients
        Mbs.multiply_by_vector(Gx, Cx);
        Mbs.multiply_by_vector(Gy, Cy);

        DEBUG_MSG("Coefficients vectors: ");
        for (unsigned j = 0; j <  Cx.size(); j++) {
            DEBUG_MSG("Cx[" << j << "] = " << Cx[j] << "\t" << "Cy[" << j << "] = " << Cy[j]);
        }

        // Compute initial differences vectors
        DD.multiply_by_vector(Cx, Dx);
        DD.multiply_by_vector(Cy, Dy);

        DEBUG_MSG("Initial differences vectors: ");
        for (unsigned j = 0; j <  Dx.size(); j++) {
            DEBUG_MSG("Dx[" << j << "] = " << Dx[j] << "\t" << "Dy[" << j << "] = " << Dy[j]);
        }

        this->forward_diff(n, Dx, Dy, outVertices);
    }
}

/* ============================================================================================= */
void WindowClipper::forward_diff(unsigned n, const DVector &Dx, const DVector &Dy,
        DCoordVector &outVertices)
/* ============================================================================================= */
{
    bool begin = true;
    bool previous_inside = false;
    double x, dx, d2x, d3x;
    double y, dy, d2y, d3y;

    Coord<double> current;
    Coord<double> previous;
    Coord<double> *new_coord;  // Intersection at an edge

    x = Dx[0];  dx = Dx[1];  d2x = Dx[2]; d3x = Dx[3];
    y = Dy[0];  dy = Dy[1];  d2y = Dy[2]; d3y = Dy[3];

    for (unsigned i = 0; i < n; i++) {

        if (coord_inside(x, y)) {
            if (begin) {
                // First point doesn't have a previous point, so we set it to true.
                previous_inside = true;
                begin = false;
            }
            if (previous_inside) {
                // Both current and previous points are inside the clipping window.
                new_coord = new Coord<double>(x, y);
                outVertices.push_back(new_coord);
                DEBUG_MSG("  > Current point is inside.");
                DEBUG_MSG("  > Previous point was inside.");
            } else {
                // Line is entering the window.
                current.set_x(x);
                current.set_y(y);
                new_coord = WindowClipper::SH_intersect(&current, &previous);
                outVertices.push_back(new_coord);
                new_coord = new Coord<double>(x, y);
                outVertices.push_back(new_coord);
                previous_inside = true;
                DEBUG_MSG("  > Current point is inside.");
                DEBUG_MSG("  > Previous point was outside.");
                DEBUG_MSG("  > New intersection at (" << new_coord->x() << ","
                                                      << new_coord->y() << ")");
            }
        } else {
            if (begin) {
                // First point doesn't have a previous point, so we set it to false.
                previous_inside = false;
                begin = false;
            }
            if (previous_inside) {
                // Line is leaving the window
                current.set_x(x);
                current.set_y(y);
                new_coord = WindowClipper::SH_intersect(&current, &previous);
                outVertices.push_back(new_coord);
                previous_inside = false;
                DEBUG_MSG("  > Current point is outside.");
                DEBUG_MSG("  > Previous point was inside.");
                DEBUG_MSG("  > New intersection at (" << new_coord->x() << ","
                                                      << new_coord->y() << ")");
            } else {
                DEBUG_MSG("  > Current point is outside.");
                DEBUG_MSG("  > Previous point was outside.");
            }
        }
        previous.set_x(x);
        previous.set_y(y);
        x = x + dx;  dx = dx + d2x;  d2x = d2x + d3x;
        y = y + dy;  dy = dy + d2y;  d2y = d2y + d3y;
    }
}

/* ============================================================================================= */
bool WindowClipper::coord_inside(double x, double y)
/* ============================================================================================= */
{
    bool inside = false;
    // If the point is outside the clipping window, then
    // set which edge is closer to it in counterclockwise fashion.
    if (x >= X_MIN) {
        if (y >= Y_MIN) {
            if (x <= X_MAX) {
                if (y <= Y_MAX) {
                    inside = true;
                } else {
                    m_edge = WindowClipper::Boundary::TOP_EDGE;
                }
            } else {
                m_edge = WindowClipper::Boundary::RIGHT_EDGE;
            }
        } else {
            m_edge = WindowClipper::Boundary::BOTTOM_EDGE;    
        }
    } else {
        m_edge = WindowClipper::Boundary::LEFT_EDGE;
    }
    return inside;
}

/* ============================================================================================= */
void WindowClipper::set_line_clipping_method(LineClipping type)
/* ============================================================================================= */
{
    m_lineClipping = type;
}

/* ============================================================================================= */
void WindowClipper::set_polygon_clipping_method(PolygonClipping type)
/* ============================================================================================= */
{
    m_polygonClipping = type;
}

/* ============================================================================================= */
void WindowClipper::cohen_sutherland_clipping(Line &line)
/* ============================================================================================= */
{
    DCoordVector newVertices;
    double x1 = line.p1()->xnc();
    double x2 = line.p2()->xnc();
    double y1 = line.p1()->ync();
    double y2 = line.p2()->ync();
    int outcode1 = computeOutcode(x1, y1);
    int outcode2 = computeOutcode(x2, y2);
    bool accept = false;

    while(true) {
        if (!(outcode1 | outcode2)) {
            accept = true;
            break;
        } else if (outcode1 & outcode2) {
            break;
        } else {
            double x, y;

            int outcodeOut = outcode1 ? outcode1 : outcode2;

            if ( outcodeOut & TOP) {
                x = x1 + (x2 - x1) * (Y_MAX - y1) / (y2 - y1);
                y = Y_MAX;
            } else if (outcodeOut & BOTTOM) {
                x = x1 + (x2 - x1) * (Y_MIN - y2) / (y2 - y1);
                y = Y_MIN;
            } else if (outcodeOut & RIGHT) {
                y = y1 + (y2 - y1) * (X_MAX - x1) / (x2 - x1);
                x = X_MAX;
            } else if(outcodeOut & LEFT) {
                y = y1 + (y2 - y1) * (X_MIN - x1) / (x2 - x1);
                x = X_MIN;
            }

            if (outcodeOut == outcode1) {
                x1 = x;
                y1 = y;
                outcode1 = computeOutcode(x1, y1);
            } else {
                x2 = x;
                y2 = y;
                outcode2 = computeOutcode(x2, y2);
            }
        }
    }

    if (accept) {
        DEBUG_MSG("X1: " << x1);
        DEBUG_MSG("Y1: " << y1);
        DEBUG_MSG("X2: " << x2);
        DEBUG_MSG("Y2: " << y2);
        newVertices.push_back(new Coord<double>(x1, y1));
        newVertices.push_back(new Coord<double>(x2, y2));
    }
    line.update_normalized_coords(newVertices);
}

/* ============================================================================================= */
int WindowClipper::computeOutcode(double x, double y)
/* ============================================================================================= */
{
    int code;

    code = INSIDE;
    if (x < X_MIN)
        code |= LEFT;
    else if (x > X_MAX)
        code |= RIGHT;
    if (y < Y_MIN)
        code |= BOTTOM;
    else if (y > Y_MAX)
        code |= TOP;

    return code;
}

/* ============================================================================================= */
void WindowClipper::liang_barsky_clipping(Line &line)
/* ============================================================================================= */
{
    DCoordVector newVertices;
    double t0 = 0.0;
    double t1 = 1.0;
    double xdelta = line.p2()->xnc() - line.p1()->xnc();
    double ydelta = line.p2()->ync() - line.p1()->ync();
    double p, q, r;
    bool draw = true;

    for (int edge = 0; edge < 4; edge++) {
        if (edge == 0) {
            p = -xdelta;
            q = -(X_MIN - line.p1()->xnc());
        }
        if (edge == 1) {
            p = xdelta;
            q = (X_MAX - line.p1()->xnc());
        }
        if (edge == 2) {
            p = -ydelta;
            q = -(Y_MIN - line.p1()->ync());
        }
        if (edge == 3) {
            p = ydelta;
            q = (Y_MAX - line.p1()->ync());
        }

        r = q/p;
        if (p == 0 && q < 0) {
            draw = false;  // Don't draw line at all. (Parallel line outside)
            break;
        }

        if (p < 0) {
            if (r > t1) {
                draw = false;
                break;
            } else if (r > t0) {
                t0 = r;  // Line is clipped
            }
        } else if (p > 0) {
            if (r < t0) {
                draw = false;
                break;
            } else if (r < t1) {
                t1 = r;
            }
        }
    }

    if (draw) {
        double x1 = line.p1()->xnc() + t0 * xdelta;
        double y1 = line.p1()->ync() + t0 * ydelta;
        double x2 = line.p1()->xnc() + t1 * xdelta;
        double y2 = line.p1()->ync() + t1 * ydelta;
        newVertices.push_back(new Coord<double>(x1, y1));
        newVertices.push_back(new Coord<double>(x2, y2));
        DEBUG_MSG("X1: " << x1);
        DEBUG_MSG("Y1: " << y1);
        DEBUG_MSG("X2: " << x2);
        DEBUG_MSG("Y2: " << y2);
    }
    line.update_normalized_coords(newVertices);
}

/* ============================================================================================= */
void WindowClipper::nicholl_lee_nicholl_clipping(Line &line)
/* ============================================================================================= */
{
    // TODO
}

/* ============================================================================================= */
void WindowClipper::SH_clipping(Wireframe &wf)
/* ============================================================================================= */
{
    const DCoordVector coords = wf.normalized_coords();
    DCoordVector inVertices(coords);
    DCoordVector outVertices;

    // Call the algorithm for each window edge, switching in and out vectors
    m_edge = WindowClipper::Boundary::LEFT_EDGE;
    DEBUG_MSG("Clipping at the LEFT edge...");
    SH_polygon_clipping(inVertices, outVertices);
    inVertices.clear();

    if (!outVertices.empty()) {
        m_edge = WindowClipper::Boundary::BOTTOM_EDGE;
        DEBUG_MSG("Clipping at the BOTTOM edge...");
        SH_polygon_clipping(outVertices, inVertices);

        if (!inVertices.empty()) {
            outVertices.clear();
            m_edge = WindowClipper::Boundary::RIGHT_EDGE;
            DEBUG_MSG("Clipping at the RIGHT edge...");
            SH_polygon_clipping(inVertices, outVertices);
            inVertices.clear();

            if (!outVertices.empty()) {
                m_edge = WindowClipper::Boundary::TOP_EDGE;
                DEBUG_MSG("Clipping at the TOP edge...");
                SH_polygon_clipping(outVertices, inVertices);
            }
        }
    }
    // Clipped polygon is stored in inVertices
    wf.update_normalized_coords(inVertices);
}

/* ============================================================================================= */
void WindowClipper::SH_polygon_clipping(const DCoordVector &inVertices, DCoordVector &outVertices)
/* ============================================================================================= */
{
    Coord<double> *s;
    Coord<double> *p;
    Coord<double> *i;

    s = inVertices.back();

    for(unsigned j = 0; j < inVertices.size(); j++) {
        p = inVertices[j];
        DEBUG_MSG("p = (" << p->x() << "," << p->y() << ")");
        DEBUG_MSG("s = (" << s->x() << "," << s->y() << ")");
        if (this->SH_inside(p)) {
            DEBUG_MSG("p is inside");
            if (this->SH_inside(s)) {
                // The whole line is inside the clipping area
                DEBUG_MSG("s is inside");
                outVertices.push_back(p);
            } else {
                // Line is entering the clipping area
                DEBUG_MSG("s is outside");
                i = this->SH_intersect(p, s);
                outVertices.push_back(i);
                outVertices.push_back(p);
            }
        } else {
            DEBUG_MSG("p is outside");
            if (this->SH_inside(s)) {
                // Line is leaving the clipping area
                DEBUG_MSG("s is inside");
                i = this->SH_intersect(p, s);
                outVertices.push_back(i);
            } else {
                DEBUG_MSG("s is outside");
            }
        }
        s = p;
    }
}

/* ============================================================================================= */
bool WindowClipper::SH_inside(Coord<double> *p)
/* ============================================================================================= */
{
    bool inside = false;
    switch(m_edge) {
        case WindowClipper::Boundary::LEFT_EDGE:
        {
            inside = ((-1.0 - p->x()) <= 0.0);
            break;
        }
        case WindowClipper::Boundary::BOTTOM_EDGE:
        {
            inside = ((-1.0 - p->y()) <= 0.0);
            break;
        }
        case WindowClipper::Boundary::RIGHT_EDGE:
        {
            inside = ((p->x() - 1.0) <= 0.0);
            break;
        }
        case WindowClipper::Boundary::TOP_EDGE:
        {
            inside = ((p->y() - 1.0) <= 0.0);
            break;
        }
    }
    return inside;
}

/* ============================================================================================= */
Coord<double>* WindowClipper::SH_intersect(Coord<double> *p, Coord<double> *s)
/* ============================================================================================= */
{
    double x, y;
    double x0 = s->x();
    double y0 = s->y();
    double x1 = p->x();
    double y1 = p->y();
    double dydx = (y1 - y0) / (x1 - x0);
    double dxdy = 1.0 / dydx;


    switch(m_edge) {
        case WindowClipper::Boundary::LEFT_EDGE:
        {
            x = X_MIN;
            y = y0 - dydx * (x0 - X_MIN);
            break;
        }
        case WindowClipper::Boundary::BOTTOM_EDGE:
        {
            x = x0 - dxdy * (y0 - Y_MIN);
            y = Y_MIN;
            break;
        }
        case WindowClipper::Boundary::RIGHT_EDGE:
        {
            x = X_MAX;
            y = y0 - dydx * (x0 - X_MAX);
            break;
        }
        case WindowClipper::Boundary::TOP_EDGE:
        {
            x = x0 - dxdy * (y0 - Y_MAX);
            y = Y_MAX;
            break;
        }
    }
    return new Coord<double>(x, y);
}

/* ============================================================================================= */
void WindowClipper::weiler_atherton_clipping(Wireframe &wf)
/* ============================================================================================= */
{
    // TODO
}
