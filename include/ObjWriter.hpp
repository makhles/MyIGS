// ObjWriter.hpp
// Authors: Leonardo Vailatti Eichstaedt
//          Makhles Reuter Lange

#ifndef OBJ_WRITER_HPP
#define OBJ_WRITER_HPP

#include <fstream>
#include <iostream>
#include <vector>
#include "Writer.hpp"


class ObjWriter : public Writer {
public:
    ObjWriter();
    ~ObjWriter();

    // Overriden methods
    void write_to_file(Point &p) override;
    void write_to_file(Line &l) override;
    void write_to_file(Wireframe &w) override;
    void write_to_file(BezierCurve &bc) override;
    void write_to_file() override;

    // Own methods
    int find_point(const Point &p_toFind) const;

private:
    std::ofstream m_file;
    int m_vCount;
    std::vector<Point*> m_points;
    std::vector<unsigned> m_linePoints;  // List of line points
    std::vector<std::vector<unsigned>> m_wPoints;     // List of wireframe points
};

#endif  // OBJ_WRITER_HPP