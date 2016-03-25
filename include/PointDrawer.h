/* PointDrawer.h */

#ifndef POINTDRAWER_H
#define POINTDRAWER_H

#include "Drawer.h"

class Point;

class PointDrawer : public Drawer {

    private:
        std::list<Point*> _points;

    public:
        PointDrawer();
        ~PointDrawer();
        void draw(const Cairo::RefPtr<Cairo::Context> &cr) override;
        void addPoint(Point *point);
};

#endif  // POINTDRAWER_H