// WindowHandler.hpp
// Authors: Leonardo Vailatti Eichstaedt
//          Makhles Reuter Lange

#ifndef WINDOW_HANDLER_HPP
#define WINDOW_HANDLER_HPP

#include "Window.hpp"

// Forward declarations
class Canvas;

class WindowHandler {
protected:
    const double DEVICE_DISPLACEMENT = 10.0;  // Pixels

    Window m_window;
    Canvas *m_viewport;

public:
    WindowHandler() {}
    ~WindowHandler() {}
    void set_viewport(Canvas *canvas) { m_viewport = canvas; }
    void translate_window(int rightOrLeft, int upOrDown);
    void scale_window(double factor);
};

#endif  // WINDOW_HANDLER_HPP