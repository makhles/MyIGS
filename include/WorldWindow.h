/* WorldWindow.h */

#ifndef WORLDWINDOW_H
#define WORLDWINDOW_H

class WorldWindow {
    public:
        const double XMIN = 0;
        const double YMIN = 0;
        const double XMAX = 100;
        const double YMAX = 100;
        double _xMin;
        double _xMax;
        double _yMin;
        double _yMax;
    public:
        WorldWindow();
        ~WorldWindow();
};

#endif  // WORLDWINDOW_H