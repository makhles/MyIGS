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
    const double DEFAULT_WIDTH = 480;
    const double DEFAULT_HEIGHT = 480;
    const double DEFAULT_CENTER_X = 0.0;
    const double DEFAULT_CENTER_Y = 0.0;
    const double DEFAULT_CENTER_Z = 0.0;
    const double DEFAULT_DISPLACEMENT = 5.0;
    const double DEFAULT_ZOOM = 0.25;

    double m_xc;
    double m_yc;
    double m_zc;
    double m_width;   // Width in WC
    double m_height;  // Height in WC
    double m_angleX;
    double m_angleY;
    double m_angleZ;

public:
    Window();
    ~Window();

    // Getters
    double x_center() const { return m_xc; }
    double y_center() const { return m_yc; }
    double width() const { return m_width; }
    double height() const { return m_height; }
    const Coord<double> center() const {
        return Coord<double>(m_xc, m_yc, m_zc);
    }
    const Coord<double> scaling() const {
        return Coord<double>((2.0 / m_width), (2.0 / m_height), 1.0);
    }
    const Coord<double> orientation() const {
        return Coord<double>(m_angleX, m_angleY, m_angleZ);
    }

    // Operations
    void translate(const std::vector<double> &window_center);
    void scale(double factor);
    void rotate(const Coord<double> &angles);
};

#endif  // WINDOW_HPP