/* Wireframe.h
   Copyright: Makhles Reuter Lange, 2016.
*/

#ifndef WIREFRAME_H
#define WIREFRAME_H

#include <cstddef>              // For size_t
#include <vector>
#include "GraphicalObject.h"
#include "Point.h"

class Wireframe : public GraphicalObject {
    private:
        std::vector<Point> _vertices;
    public:
        Wireframe(const std::string name, const Point &p1, const Point &p2, const Point &p3);
        ~Wireframe();
        std::vector<Point> get_vertices() const {return _vertices;};
        void add_vertice(const Point &p);
};
#endif