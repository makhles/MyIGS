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

        const Coord<double> get_centroid() override;
        void add_point(Point *point);

        // Visitor
        virtual void accept(AbstractDrawer *drawer);
        virtual void transform(TMatrix *matrix) override;
        virtual void clip_to_window(Window *w) override;
};

#endif  // WIREFRAME_H