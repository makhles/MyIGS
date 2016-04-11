// Window.hpp
// Authors: Leonardo Vailatti Eichstaedt
//          Makhles Reuter Lange

#ifndef WINDOW_HPP
#define WINDOW_HPP

#include "Coord.hpp"


class Window {
private:

    // Constants
    const double LOCAL_WIDTH = 2.0;
    const double LOCAL_HEIGHT = 2.0;
    const double DEFAULT_WIDTH = 1000;
    const double DEFAULT_HEIGHT = 1000;
    const double DEFAULT_CENTER_X = 0.0;
    const double DEFAULT_CENTER_Y = 0.0;
    const double DEFAULT_DISPLACEMENT = 5.0;
    const double DEFAULT_ZOOM = 0.25;

    double m_xc;
    double m_yc;
    double m_width;   // Width in WC
    double m_height;  // Height in WC
    double m_angle;   // Angle to Ywc

public:
    Window();
    ~Window();

    // Getters
    const double x_center() const { return m_xc; }
    const double y_center() const { return m_yc; }
    const double width() const { return m_width; }
    const double height() const { return m_height; }
    const double angle() const { return m_angle; }

    // Operations
    void translate(double dh, double dv);
    void scale(double factor);
    void rotate(double angle);
};

#endif  // WINDOW_HPP