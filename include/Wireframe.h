/* Wireframe.h */

#ifndef WIREFRAME_H
#define WIREFRAME_H

#include <list>
#include "Shape.h"
#include "Point.h"


class Wireframe : public Shape {

    private:
        std::list<Point*> *_vertices;

    public:
        Wireframe(const std::string name, std::list<Point*> *vertices);
        Wireframe(std::list<Point*> *vertices);
        ~Wireframe();

        // Visitor
        virtual void accept(AbstractDrawer *drawer);

        virtual void clipToWindow(WorldWindow *w) override;
};

#endif  // WIREFRAME_H