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
        ~Wireframe();
        const std::list<Point*>* get_vertices() const {return _vertices;}
};

#endif  // WIREFRAME_H