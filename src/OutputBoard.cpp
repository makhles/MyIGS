// OutputBoard.cpp
// Authors: Leonardo Vailatti Eichstaedt
//          Makhles Reuter Lange

#include "OutputBoard.hpp"


OutputBoard::OutputBoard() {
    add(m_textView);

    /* Only show scrollbars when necessary */
    set_policy(Gtk::POLICY_AUTOMATIC, Gtk::POLICY_AUTOMATIC);

    /* Print greetings */
    //m_buffer = Gtk::TextBuffer::create();
    this->print("Welcome to MyIGS!");
}


OutputBoard::~OutputBoard() {
}


void OutputBoard::print(const std::string &msg) {
    TBuffer buffer(m_textView.get_buffer());
    buffer->insert(buffer->end(), msg);
    Gtk::TextBuffer::iterator end = buffer->end();
    m_textView.scroll_to(end, 0.0);

    /* Adjust scrolled window bar position */    
    // Glib::RefPtr<Gtk::Adjustment> adj = this->get_vadjustment();
    // adj->set_value(adj->get_upper());
}