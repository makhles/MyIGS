// OutputBoard.hpp
// Authors: Leonardo Vailatti Eichstaedt
//          Makhles Reuter Lange

#ifndef OUTPUT_BOARD_H
#define OUTPUT_BOARD_H

#include <gtkmm.h>
#include <string>

typedef Glib::RefPtr<Gtk::TextBuffer> TBuffer;
typedef Gtk::TextBuffer::iterator TextIter;


class OutputBoard : public Gtk::ScrolledWindow {
private:
    Gtk::TextView m_textView;

public:
    OutputBoard();
    ~OutputBoard();
    void print(const std::string &msg);
};

#endif  // OUTPUT_BOARD_H