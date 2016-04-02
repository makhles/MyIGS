/* Wireframe.h */

#ifndef WIREFRAME_H
#define WIREFRAME_H

#include <list>
#include "Shape.hpp"
#include "Point.hpp"


class Wireframe : public Shape {

    private:
        std::list<Point*> _vertices;

    public:
        Wireframe(const std::string name);
        ~Wireframe();

        void addPoint(Point *point);

        // Visitor
        virtual void accept(AbstractDrawer *drawer);

        virtual void clipToWindow(WorldWindow *w) override;
};

#endif  // WIREFRAME_H