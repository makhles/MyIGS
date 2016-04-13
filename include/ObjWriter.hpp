// ObjWriter.hpp
// Authors: Leonardo Vailatti Eichstaedt
//          Makhles Reuter Lange

#ifndef OBJ_WRITER_HPP
#define OBJ_WRITER_HPP

#include <fstream>
#include <iostream>
#include "Writer.hpp"


class ObjWriter : public Writer {
private:
    int m_lineCount;
    std::ofstream m_file;
public:
    ObjWriter();
    ~ObjWriter();

    // Overriden methods
    void write_to_file(Point &p) override;
    void write_to_file(Line &l) override;
    void write_to_file(Wireframe &w) override;
    void flush() override;
};

#endif  // OBJ_WRITER_HPP