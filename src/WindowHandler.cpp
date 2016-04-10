// WindowHandler.cpp
// Authors: Leonardo Vailatti Eichstaedt
//          Makhles Reuter Lange

#include "WindowHandler.hpp"
#include "Canvas.hpp"



// Right/Up = 1, Left/Down = -1, stay still = 0
// dx is the required horizontal displacement so that the viewport
// will be translated by DEVICE_DISPLACEMENT units (in pixels).
void WindowHandler::translate_window(int rightOrLeft, int upOrDown) {
    double dx = DEVICE_DISPLACEMENT * m_window.width() / m_viewport->get_viewport_width();
    double dy = DEVICE_DISPLACEMENT * m_window.height() / m_viewport->get_viewport_height();
    m_window.translate(rightOrLeft * dx, upOrDown * dy);
}


void WindowHandler::scale_window(double factor) {
    m_window.scale(factor);
}


void WindowHandler::rotate_window(double angle) {
    m_window.rotate(angle);
}