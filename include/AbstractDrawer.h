/* AbstractDrawer */

#ifndef ABSTRACT_DRAWER_H
#define ABSTRACT_DRAWER_H

class Point;
class Line;
class Wireframe;

class AbstractDrawer
{
    public:
        virtual void draw(Point *point) = 0;
        virtual void draw(Line *line) = 0;
        virtual void draw(Wireframe *wireframe) = 0;

};

#endif  // ABSTRACT_DRAWER_H