/* Point.h */

#ifndef LINE_H
#define LINE_H

#include "Shape.hpp"

class Point;

class Line : public Shape {

    protected:
        Point *_p1;
        Point *_p2;

    public:
        Line(const std::string name, Point *p1, Point *p2);
        ~Line();
        const Point* get_p1() const {return _p1;}
        const Point* get_p2() const {return _p2;}

        // Visitor
        virtual void accept(AbstractDrawer *drawer);

        virtual void transform(TMatrix *matrix) override;
        virtual void clipToWindow(WorldWindow *w) override;
};
#endif