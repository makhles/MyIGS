/* Window.h */

#ifndef WINDOW_HPP
#define WINDOW_HPP

class Window {

    private:
        const double WINDOW_DEFAULT_XMIN = 0;
        const double WINDOW_DEFAULT_YMIN = 0;
        const double WINDOW_DEFAULT_XMAX = 100;
        const double WINDOW_DEFAULT_YMAX = 100;
        const double DEFAULT_DISPLACEMENT = 5.0;
        const double DEFAULT_ZOOM = 0.25;
        double _xMin;
        double _xMax;
        double _yMin;
        double _yMax;
        double _zoom;

    public:
        Window();
        ~Window();
        const double getXMin() const { return _xMin; }
        const double getXMax() const { return _xMax; }
        const double getYMin() const { return _yMin; }
        const double getYMax() const { return _yMax; }
        void moveWindow(int moveX, int moveY);
        void zoomWindow(int inOrOut);
};

#endif  // WINDOW_HPP