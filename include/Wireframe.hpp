// Wireframe.hpp
// Authors: Leonardo Vailatti Eichstaedt
//          Makhles Reuter Lange

#ifndef WIREFRAME_HPP
#define WIREFRAME_HPP

#include <vector>
#include "Shape.hpp"
#include "Point.hpp"

class Wireframe : public Shape {
protected:
    std::vector<Point*> m_vertices;
    bool m_filled;  // Whether it should be painted.

public:
    Wireframe(const std::string name, bool filled);
    ~Wireframe();

    bool filled() const { return m_filled; }
    const Coord<double> get_centroid() override;
    void add_point(Point *point);

    const std::vector<Point*>& vertices() const { return m_vertices; }

    // Visitors
    void accept(AbstractDrawer *drawer);
    void clip_to_window(AbstractClipper &clipper) override;

    void transform(TMatrix &matrix) override;
    void normalize(TMatrix &matrix) override;
    void write_to_file(Writer *w) override;
};

#endif  // WIREFRAME_HPP