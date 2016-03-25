/* WorldWindow.h */

#ifndef WORLDWINDOW_H
#define WORLDWINDOW_H

#define XMIN 0
#define YMIN 0
#define XMAX 100
#define YMAX 500
#define TRANSLATION_OFFSET 10.0  // Displacement units
#define DEFAULT_ZOOM 100  // Porcentage
#define ZOOM_FACTOR 25  // Porcentage

class WorldWindow {
    private:
        double _xMin;
        double _xMax;
        double _yMin;
        double _yMax;
        double _zoom;
    public:
        WorldWindow();
        ~WorldWindow();
        void translateUp();
        void translateRight();
        void translateDown();
        void translateLeft();
        void zoomIn();
        void zoomOut();
};

#endif  // WORLDWINDOW_H