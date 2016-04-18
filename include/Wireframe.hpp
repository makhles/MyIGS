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

public:
    Wireframe(const std::string name);
    ~Wireframe();

    const Coord<double> get_centroid() override;
    void add_point(Point *point);

    const std::vector<Point*>& vertices() const { return m_vertices; }

    // Visitor
    void accept(AbstractDrawer *drawer);
    void transform(TMatrix &matrix) override;
    void normalize(TMatrix &matrix) override;
    void clip_to_window(Window &window) override;
    void write_to_file(Writer *w) override;
};

#endif  // WIREFRAME_HPP