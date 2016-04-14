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
private:
    std::ofstream m_file;
    int m_vCount;
    std::vector<Point*> m_points;

public:
    ObjWriter();
    ~ObjWriter();

    // Overriden methods
    void write_to_file(Point &p) override;
    void write_to_file(Line &l) override;
    void write_to_file(Wireframe &w) override;
    void flush() override;

    // Own methods
    bool has_point(Point &p_toFind) const;
};

#endif  // OBJ_WRITER_HPP