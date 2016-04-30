// CoordBox.hpp
// Authors: Leonardo Vailatti Eichstaedt
//          Makhles Reuter Lange

#ifndef COORD_BOX_HPP
#define COORD_BOX_HPP

#include <gtkmm.h>
#include <vector>
#include "Coord.hpp"


#define ENTRIES_PER_CURVE 8

class CoordBox : public Gtk::VBox {
protected:
    std::vector<Gtk::Entry*> m_entries;

public:
    CoordBox() {}
    ~CoordBox() {}
    int entries_size() const { return m_entries.size(); }
    bool entries_filled() const;
    bool fill_coords(std::vector<Coord<double>*>& coords) const;
    void add_curve();
    void add_bezier_curve();
    void add_coord();
};

#endif  // COORD_BOX_HPP