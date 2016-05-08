// CoordBox.hpp
// Authors: Leonardo Vailatti Eichstaedt
//          Makhles Reuter Lange

#include <iostream>
#include "CoordBox.hpp"

// For debugging, uncomment the following define
#define DEBUG
#ifdef DEBUG
#define DEBUG_MSG(str) do { std::cout << str << std::endl; } while( false )
#else
#define DEBUG_MSG(str) do { } while ( false )
#endif

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

    int p3_index = m_entries.size() - 1;
    std::stringstream stream_x2, stream_y2;
    std::stringstream stream_x3, stream_y3;

    stream_x2 << m_entries[p3_index - 3]->get_text().raw();
    stream_y2 << m_entries[p3_index - 2]->get_text().raw();
    stream_x3 << m_entries[p3_index - 1]->get_text().raw();
    stream_y3 << m_entries[p3_index - 0]->get_text().raw();
    stream_x2 >> m_x2;
    stream_y2 >> m_y2;
    stream_x3 >> m_x3;
    stream_y3 >> m_y3;

    // Add the new entries
    for (unsigned i = 0; i < 4; i++) {
        CoordBox::add_coord();
    }

    // The first entry of the recently added curve must have the same
    // coordinates as the last entry of the previous curve (C0)
    m_entries[p3_index + 1]->set_text(std::to_string(m_x3));
    m_entries[p3_index + 2]->set_text(std::to_string(m_y3));

    // Prevent user from messing this up
    m_entries[p3_index + 1]->set_sensitive(false);
    m_entries[p3_index + 2]->set_sensitive(false);

    // Add a signal handler only if the points P2 e P3 do not reside in the same
    // X or Y coordinate. If they do, this coordinate is fixed.
    bool enable_out_event = true;

    if (m_x3 - m_x2 == 0.0) {
        m_entries[p3_index + 3]->set_text(std::to_string(m_x3));
        m_entries[p3_index + 3]->set_sensitive(false);
        enable_out_event = false;
    }
    if (m_y3 - m_y2 == 0.0) {
        m_entries[p3_index + 4]->set_text(std::to_string(m_y3));
        m_entries[p3_index + 4]->set_sensitive(false);
        enable_out_event = false;
    }
    if (enable_out_event) {
        m_entries[p3_index + 3]->add_events(Gdk::FOCUS_CHANGE_MASK);
        m_entries[p3_index + 3]->signal_focus_out_event().connect(sigc::mem_fun(*this,
            &CoordBox::on_x_entry_focus_out_event));
        m_entries[p3_index + 4]->add_events(Gdk::FOCUS_CHANGE_MASK);
        m_entries[p3_index + 4]->signal_focus_out_event().connect(sigc::mem_fun(*this,
            &CoordBox::on_y_entry_focus_out_event));
    }
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


/* ============================================================================================= */
void CoordBox::clear()
/* ============================================================================================= */
{
    m_entries.clear();
    std::vector<Widget*> children = this->get_children();
    children.erase(children.begin(), children.end());
}


bool CoordBox::on_x_entry_focus_out_event(GdkEventFocus* /* event*/) {
    int x5_entry_index = m_entries.size() - 6;
    double x5, y5;
    std::stringstream stream_x;

    DEBUG_MSG("x entry focus out event!");
    DEBUG_MSG("------------------------");
    DEBUG_MSG("x5 entry index = " << x5_entry_index);

    stream_x << m_entries[x5_entry_index]->get_text().raw();
    if (stream_x.str().size() != 0) {
        stream_x >> x5;
        y5 = m_y3 + (m_y3 - m_y2) * (x5 - m_x3) / (m_x3 - m_x2);
        DEBUG_MSG("p2 = (" << m_x2 << "," << m_y2 << ")");
        DEBUG_MSG("p3 = (" << m_x3 << "," << m_y3 << ")");
        DEBUG_MSG("p5 = (" << x5   << "," << y5   << ")");
        m_entries[x5_entry_index + 1]->set_text(std::to_string(y5));
    }
    return true;
}


bool CoordBox::on_y_entry_focus_out_event(GdkEventFocus* /* event*/) {
    int y5_entry_index = m_entries.size() - 5;
    double x5, y5;
    std::stringstream stream_y;

    DEBUG_MSG("y entry focus out event!");
    DEBUG_MSG("------------------------");
    DEBUG_MSG("y5 entry index = " << y5_entry_index);

    stream_y << m_entries[y5_entry_index]->get_text().raw();
    if (stream_y.str().size() != 0) {
        stream_y >> y5;
        x5 = m_x3 + (m_x3 - m_x2) * (y5 - m_y3) / (m_y3 - m_y2);
        DEBUG_MSG("p2 = (" << m_x2 << "," << m_y2 << ")");
        DEBUG_MSG("p3 = (" << m_x3 << "," << m_y3 << ")");
        DEBUG_MSG("p5 = (" << x5   << "," << y5   << ")");
        m_entries[y5_entry_index - 1]->set_text(std::to_string(x5));
    }
    return true;
}