/* Point.h */

#ifndef POINT_H
#define POINT_H

#include <cairomm/context.h>
#include "Shape.h"

class Point : public Shape {

    private:
        const double _x;
        const double _y;

    public:
        Point(const std::string name, const double x, const double y);
        ~Point();
        const double getX() const {return _x;}
        const double getY() const {return _y;}

        // Visitor
        virtual void accept(AbstractDrawer *drawer);

        virtual void clipToWindow(WorldWindow *w) override;
};

#endif  // POINT_H