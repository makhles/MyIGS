/* WorldWindow.h */

#ifndef WORLDWINDOW_H
#define WORLDWINDOW_H

class WorldWindow {

    private:
        const double XMIN = 0;
        const double YMIN = 0;
        const double XMAX = 100;
        const double YMAX = 100;
        const double DEFAULT_DISPLACEMENT = 5.0;
        double _xMin;
        double _xMax;
        double _yMin;
        double _yMax;

    public:
        WorldWindow();
        ~WorldWindow();
        const double getXMin() const { return _xMin; }
        const double getXMax() const { return _xMax; }
        const double getYMin() const { return _yMin; }
        const double getYMax() const { return _yMax; }
        void moveWindow(int moveX, int moveY);
        void zoomWindowIn();
        void zoomWindowOut();
};

#endif  // WORLDWINDOW_H