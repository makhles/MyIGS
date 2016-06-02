// CoordBox.hpp
// Authors: Leonardo Vailatti Eichstaedt
//          Makhles Reuter Lange

#include <iostream>
#include "CoordBox.hpp"

// For debugging, uncomment the following define
//#define DEBUG
#ifdef DEBUG
#define DEBUG_MSG(str) do { std::cout << str << std::endl; } while( false )
#else
#define DEBUG_MSG(str) do { } while ( false )
#endif


/* ============================================================================================= */
void CoordBox::add_cubic_curve()
/* ============================================================================================= */
{
    /**
     * Adds four entries to the box.
     */
    for (unsigned i = 0; i < 4; i++) {
        CoordBox::add_coord();
    }
}

/* ============================================================================================= */
void CoordBox::add_bezier_curve()
/* ============================================================================================= */
{
    double x;  // Last point coordinates to be copied to
    double y;  // to the entries of the first point of the points
    double z;  // that are being created.

    int index = m_entries.size() - 1;  // Index of the last coord of last point.
    std::stringstream stream_x, stream_y, stream_z;

    // Get coords values
    stream_x << m_entries[index - 2]->get_text().raw();
    stream_y << m_entries[index - 1]->get_text().raw();
    stream_z << m_entries[index - 0]->get_text().raw();
    stream_x >> x;
    stream_y >> y;
    stream_z >> z;

    // Add the new entries
    for (unsigned i = 0; i < 4; i++) {
        CoordBox::add_coord();
    }

    // The first entry of the recently added curve must have the same
    // coordinates as the last entry of the previous curve (C0)
    m_entries[index + 1]->set_text(std::to_string(x));
    m_entries[index + 2]->set_text(std::to_string(y));
    m_entries[index + 3]->set_text(std::to_string(z));
}

/* ============================================================================================= */
void CoordBox::add_coord()
/* ============================================================================================= */
{
    // Used for naming each coordinate, like x0, x1, y0, y1, etc.
    // Every time a new point is added, m_entries increases by 3.
    int pNumber = m_entries.size() / 3;
    const std::string str_xCoord = "x" + std::to_string(pNumber) + ": ";
    const std::string str_yCoord = "y" + std::to_string(pNumber) + ": ";
    const std::string str_zCoord = "z" + std::to_string(pNumber) + ": ";

    Gtk::HBox * const hbox = Gtk::manage(new Gtk::HBox());
    Gtk::Label * const xLabel = Gtk::manage(new Gtk::Label(str_xCoord));
    Gtk::Label * const yLabel = Gtk::manage(new Gtk::Label(str_yCoord));
    Gtk::Label * const zLabel = Gtk::manage(new Gtk::Label(str_zCoord));
    Gtk::Entry * const xEntry = Gtk::manage(new Gtk::Entry());
    Gtk::Entry * const yEntry = Gtk::manage(new Gtk::Entry());
    Gtk::Entry * const zEntry = Gtk::manage(new Gtk::Entry());

    xEntry->set_width_chars(10);
    yEntry->set_width_chars(10);
    zEntry->set_width_chars(10);

    hbox->pack_start(*xLabel, Gtk::PACK_EXPAND_WIDGET, 0);
    hbox->pack_start(*xEntry, Gtk::PACK_SHRINK, 0);
    hbox->pack_start(*yLabel, Gtk::PACK_EXPAND_WIDGET, 0);
    hbox->pack_start(*yEntry, Gtk::PACK_SHRINK, 0);
    hbox->pack_start(*zLabel, Gtk::PACK_EXPAND_WIDGET, 0);
    hbox->pack_start(*zEntry, Gtk::PACK_SHRINK, 0);
    hbox->set_homogeneous(false);

    pack_start(*hbox, Gtk::PACK_EXPAND_WIDGET, 5);;

    // Keep track of entries to get their values
    m_entries.push_back(xEntry);
    m_entries.push_back(yEntry);
    m_entries.push_back(zEntry);
}

/* ============================================================================================= */
bool CoordBox::fill_coords(std::vector<Coord<double>*>& coords) const
/* ============================================================================================= */
{
    bool filled = true;  // Whether all the entries are filled.
    double x, y, z;
    for (unsigned i = 0; i < m_entries.size(); i += 3) {
        // Create new stringstreams at every loop iteration
        // to make sure it's totally clear.
        std::stringstream stream_x, stream_y, stream_z;
        stream_x << m_entries[i+0]->get_text().raw();
        stream_y << m_entries[i+1]->get_text().raw();
        stream_z << m_entries[i+2]->get_text().raw();
        // Check if streams are not empty        
        if (stream_x.str().size() != 0 &&
            stream_y.str().size() != 0 &&
            stream_z.str().size() != 0)
        {
            stream_x >> x;
            stream_y >> y;
            stream_z >> z;
            coords.push_back(new Coord<double>(x, y, z));
        } else {
            filled = false;
        }
    }
    return filled;
}

/* ============================================================================================= */
bool CoordBox::entries_filled() const
/* ============================================================================================= */
{
    bool filled = true;  // Whether all the entries are filled.
    for (unsigned i = 0; i < m_entries.size(); i++) {
        // Create new stringstreams at every loop iteration
        // to make sure it's totally clear.
        std::stringstream stream;
        stream << m_entries[i]->get_text().raw();
        if (stream.str().size() == 0) {
            DEBUG_MSG("Entry " << i << "/" << m_entries.size() << " is empty.");
            filled = false;
            break;
        } else {
            DEBUG_MSG("Entry " << i << "/" << m_entries.size() << " is filled.");
        }
    }
    return filled;
}


/* ============================================================================================= */
void CoordBox::clear()
/* ============================================================================================= */
{
    m_entries.clear();
    std::vector<Widget*> children = this->get_children();
    auto it = children.begin();
    while (it != children.end()) {
        this->remove(**it);
        it++;
    }
}