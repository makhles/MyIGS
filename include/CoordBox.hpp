// CoordBox.hpp
// Authors: Leonardo Vailatti Eichstaedt
//          Makhles Reuter Lange

#ifndef COORD_BOX_HPP
#define COORD_BOX_HPP

#include <gtkmm.h>
#include <vector>
#include "Coord.hpp"

class CoordBox : public Gtk::VBox {
protected:
    std::vector<Gtk::Entry*> m_entries;

public:
    CoordBox();
    ~CoordBox();
    void add_coord();
    void fill_coords(std::vector<Coord<double>*>& coords) const;
};

#endif  // COORD_BOX_HPP