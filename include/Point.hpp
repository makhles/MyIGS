// Point.hpp
// Authors: Leonardo Vailatti Eichstaedt
//          Makhles Reuter Lange

#ifndef POINT_H
#define POINT_H

#include <cairomm/context.h>
#include "Shape.hpp"

class Point : public Shape {

    private:
        double m_x;
        double m_y;

    public:
        Point(const std::string name, const double x, const double y);
        ~Point();
        const double getX() const { return m_x; }
        const double getY() const { return m_y; }
        const Coord<double> get_centroid() override;

        // Visitor
        virtual void accept(AbstractDrawer *drawer);
        virtual void transform(TMatrix *matrix) override;
        virtual void clip_to_window(Window *w) override;
};

#endif  // POINT_H