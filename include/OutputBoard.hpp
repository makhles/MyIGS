/* OutputBoard.h */

#ifndef OUTPUT_BOARD_H
#define OUTPUT_BOARD_H

#include <gtkmm/scrolledwindow.h>
#include <gtkmm/textview.h>
#include <gtkmm/textbuffer.h>
#include <string>

class OutputBoard : public Gtk::ScrolledWindow {
    protected:
        Gtk::TextView _textView;
        Glib::RefPtr<Gtk::TextBuffer> _greetingTextBuffer;
    public:
        OutputBoard();
        virtual ~OutputBoard();
        void insert_text(std::string newText);
};

#endif  // OUTPUT_BOARD_H