// CoordBox.hpp
// Authors: Leonardo Vailatti Eichstaedt
//          Makhles Reuter Lange

#include "CoordBox.hpp"


// Add the first Bézier curve (4 points only)
void CoordBox::add_curve() {
    for (unsigned i = 0; i < 4; i++) {
        CoordBox::add_coord();
    }
}


void CoordBox::add_bezier_curve() {
    const int last_curve_begin = m_entries.size() - ENTRIES_PER_CURVE;

    // Make all entries from the previous curve uneditable
    for (unsigned i = last_curve_begin; i < m_entries.size(); i++) {
        m_entries[i]->set_sensitive(false);
    }

    int last_entry_index = m_entries.size() - 1;
    double last_x, last_y;
    std::stringstream stream_last_x, stream_last_y;
    stream_last_x << m_entries[last_entry_index - 1]->get_text().raw();
    stream_last_y << m_entries[last_entry_index - 0]->get_text().raw();
    stream_last_x >> last_x;
    stream_last_y >> last_y;

    for (unsigned i = 0; i < 4; i++) {
        CoordBox::add_coord();
    }

    // The first entry of the recently added curve must have the same
    // coordinates as the last entry of the previous curve (C0)
    m_entries[last_entry_index + 1]->set_text(std::to_string(last_x));
    m_entries[last_entry_index + 2]->set_text(std::to_string(last_y));

    // Prevent user from messing this up
    m_entries[last_entry_index + 1]->set_sensitive(false);
    m_entries[last_entry_index + 2]->set_sensitive(false);
}


void CoordBox::add_coord() {
    // Used for naming each coordinate, like x0, x1, y0, y1, etc.
    // Every time a new point is added, m_entries increases by 2.
    int pNumber = m_entries.size() / 2;
    const std::string str_xCoord = "x" + std::to_string(pNumber) + ": ";
    const std::string str_yCoord = "y" + std::to_string(pNumber) + ": ";

    Gtk::HBox * const hbox = Gtk::manage(new Gtk::HBox());
    Gtk::Label * const xLabel = Gtk::manage(new Gtk::Label(str_xCoord));
    Gtk::Label * const yLabel = Gtk::manage(new Gtk::Label(str_yCoord));
    Gtk::Entry * const xEntry = Gtk::manage(new Gtk::Entry());
    Gtk::Entry * const yEntry = Gtk::manage(new Gtk::Entry());

    xEntry->set_width_chars(10);
    yEntry->set_width_chars(10);

    hbox->pack_start(*xLabel, Gtk::PACK_EXPAND_WIDGET, 0);
    hbox->pack_start(*xEntry, Gtk::PACK_SHRINK, 0);
    hbox->pack_start(*yLabel, Gtk::PACK_EXPAND_WIDGET, 0);
    hbox->pack_start(*yEntry, Gtk::PACK_SHRINK, 0);
    hbox->set_homogeneous(false);

    pack_start(*hbox, Gtk::PACK_EXPAND_WIDGET, 5);;

    // Keep track of entries to get their values
    m_entries.push_back(xEntry);
    m_entries.push_back(yEntry);
}


bool CoordBox::fill_coords(std::vector<Coord<double>*>& coords) const {
    bool filled = true;  // Whether all the entries are filled.
    double x, y;
    for (unsigned i = 0; i < m_entries.size(); i += 2) {
        // Create new stringstreams at every loop iteration
        // to make sure it's totally clear.
        std::stringstream stream_x, stream_y;
        stream_x << m_entries[i+0]->get_text().raw();
        stream_y << m_entries[i+1]->get_text().raw();
        // Check if streams are not empty        
        if (stream_x.str().size() != 0 && stream_y.str().size() != 0) {
            stream_x >> x;
            stream_y >> y;
            coords.push_back(new Coord<double>(x, y));
        } else {
            filled = false;
        }
    }
    return filled;
}


bool CoordBox::entries_filled() const {
    bool filled = true;  // Whether all the entries are filled.
    for (unsigned i = 0; i < m_entries.size(); i++) {
        // Create new stringstreams at every loop iteration
        // to make sure it's totally clear.
        std::stringstream stream;
        stream << m_entries[i]->get_text().raw();
        if (stream.str().size() == 0) {
            filled = false;
            break;
        }
    }
    return filled;
}