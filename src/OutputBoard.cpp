/* OutputBoard.cpp */

#include "OutputBoard.h"

OutputBoard::OutputBoard() {
    add(_textView);

    /* Only show scrollbars when necessary */
    set_policy(Gtk::POLICY_AUTOMATIC, Gtk::POLICY_AUTOMATIC);

    /* Default output text */
    _greetingTextBuffer = Gtk::TextBuffer::create();
    _greetingTextBuffer->set_text("Welcome to MyIGS!");
    _textView.set_buffer(_greetingTextBuffer);
}

OutputBoard::~OutputBoard() {
}

void OutputBoard::insert_text(std::string newText) {
    //TODO(Makhles)
}