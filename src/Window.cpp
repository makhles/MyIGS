// Window.cpp
// Authors: Leonardo Vailatti Eichstaedt
//          Makhles Reuter Lange

#include <iostream>
#include <algorithm>
#include "Window.hpp"

#define PI acos(-1.0)


Window::Window() :
    m_xc(DEFAULT_CENTER_X),
    m_yc(DEFAULT_CENTER_Y),
    m_width(DEFAULT_WIDTH),
    m_height(DEFAULT_HEIGHT),
    m_angle(0.0)
{
    std::cout << "Window created. Center at (" << m_xc << "," << m_yc << ")" << std::endl;
}


Window::~Window() {
}


// Translate the center of the window taking into
// consideration the current window orientation.
// The window is only translated horizontally or
// vertically, but not both at the same time.
// dh = horizontal displacement
// dv = vertical displacement
// u = right vector. u = (ux, uy)
void Window::translate(double dh, double dv) {
    double radians = m_angle * PI / 180.0;
    double ux = cos (radians);
    double uy = sin (radians);

    // If (dh != 0) then (dv = 0) and vice-versa.
    m_xc += dh * ux;
    m_yc += dh * uy;
    m_xc += dv * (-uy);
    m_yc += dv * ux;

    std::cout << "Window translated. Center at (" << m_xc << "," << m_yc << ")" << std::endl;
}


void Window::scale(double factor) {
    m_width = DEFAULT_WIDTH / factor;
    m_height = DEFAULT_HEIGHT / factor;
}


void Window::rotate(double angle) {
    // TODO
}




// void Window::zoomWindow(int inOrOut) {
//     if ((inOrOut == -1 && _zoom > 1.0) || (inOrOut == 1)) {
//         _zoom += inOrOut * DEFAULT_ZOOM;
//         double percentage = 1.0 / _zoom;
//         double deltaX = (WINDOW_DEFAULT_XMAX - WINDOW_DEFAULT_XMIN) * percentage / 2.0;
//         double deltaY = (WINDOW_DEFAULT_YMAX - WINDOW_DEFAULT_YMIN) * percentage / 2.0;
//         double windowCenterX = (_xMax + _xMin) / 2.0;
//         double windowCenterY = (_yMax + _yMin) / 2.0;
//         _xMin = windowCenterX - deltaX;
//         _xMax = windowCenterX + deltaX;
//         _yMin = windowCenterY - deltaY;
//         _yMax = windowCenterY + deltaY;
//     }
// }
