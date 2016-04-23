// CoordBox.hpp
// Authors: Leonardo Vailatti Eichstaedt
//          Makhles Reuter Lange

#include "CoordBox.hpp"
#include "Coord.hpp"


CoordBox::CoordBox() {

}


CoordBox::~CoordBox() {

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


void CoordBox::fill_coords(std::vector<Coord<double>*>& coords) const {
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
        }
    }
}