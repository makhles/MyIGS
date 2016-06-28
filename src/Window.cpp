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
    m_zc(DEFAULT_CENTER_Z),
    m_width(DEFAULT_WIDTH),
    m_height(DEFAULT_HEIGHT),
    m_angleX(90.0),
    m_angleY(90.0),
    m_angleZ(0.0)
{
    std::cout << "Window created. Center at (" << m_xc << "," << m_yc << "," << m_zc << ")" << std::endl;
}


Window::~Window() {
}

void Window::translate(const std::vector<double> &window_center) {
    m_xc = window_center[0];
    m_yc = window_center[1];
    m_zc = window_center[2];
    std::cout << "Window translated. Center at (" << m_xc << "," << m_yc << "," << m_zc << ")" << std::endl;
}


void Window::scale(double factor) {
    m_width = DEFAULT_WIDTH / factor;
    m_height = DEFAULT_HEIGHT / factor;
}


void Window::rotate(const Coord<double> &angles) {
    m_angleX += angles.x();
    m_angleY += angles.y();
    m_angleZ += angles.z();
}