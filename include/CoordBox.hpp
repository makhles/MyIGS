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
    double m_x3;
    double m_y3;
    double m_z3;

public:
    CoordBox() {}
    ~CoordBox() {}
    int entries_size() const { return m_entries.size(); }
    bool entries_filled() const;
    bool fill_coords(std::vector<Coord<double>*>& coords) const;
    void add_cubic_curve();
    void add_bezier_curve();
    void add_coord();
    void clear();
    void show_coords();
    void hide_coords();
};

#endif  // COORD_BOX_HPP