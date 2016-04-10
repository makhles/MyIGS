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

    double m_width;          // Width in WC
    double m_height;         // Height in WC
    double m_orientation;    // Rotation about the z axis
    Coord<double> m_center;  // Window center (0,0) in WC

public:
    Window();
    ~Window();

    // Getters
    const double width() const { return m_width; }
    const double height() const { return m_height; }
    const Coord<double>& center() const { return m_center; }

    // Operations
    void translate(int rightOrLeft, int upOrDown);
    void scale(double ratio);
    void rotate(double angle);
};

#endif  // WINDOW_HPP