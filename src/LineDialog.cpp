/* LineDialog.cpp */

#include <iostream>
#include "LineDialog.h"
#include "Line.h"
#include "InterfaceController.h"

LineDialog::LineDialog() :
        _mainBox(Gtk::ORIENTATION_VERTICAL),
        _nameBox(Gtk::ORIENTATION_HORIZONTAL),
        _coordBox1(Gtk::ORIENTATION_HORIZONTAL),
        _coordBox2(Gtk::ORIENTATION_HORIZONTAL),
        _buttonBox(Gtk::ORIENTATION_HORIZONTAL),
        _nameLabel("Name: "),
        _x1Label("x1 ="),
        _x2Label("x2 ="),
        _y1Label("y1 ="),
        _y2Label("y2 ="),
        _okButton("OK"),
        _cancelButton("Cancel") {

    /* Window properties */
    set_title("Create Line");
    set_border_width(10);
    set_resizable(false);

    /* Main box */
    add(_mainBox);

    /* Pack widgets */
    _mainBox.pack_start(_nameBox, Gtk::PACK_EXPAND_WIDGET, 1);
    _mainBox.pack_start(_coordBox1, Gtk::PACK_EXPAND_WIDGET, 1);
    _mainBox.pack_start(_coordBox2, Gtk::PACK_EXPAND_WIDGET, 1);
    _mainBox.pack_start(_buttonSeparator, Gtk::PACK_EXPAND_WIDGET, 1);
    _mainBox.pack_start(_buttonBox, Gtk::PACK_EXPAND_WIDGET, 1);

    /* Input */
    _nameBox.set_homogeneous(false);
    _coordBox1.set_homogeneous(false);
    _coordBox2.set_homogeneous(false);

    _nameBox.pack_start(_nameLabel, Gtk::PACK_SHRINK, 0);
    _nameBox.pack_start(_nameEntry, Gtk::PACK_EXPAND_WIDGET, 0);

    _coordBox1.pack_start(_x1Label, Gtk::PACK_EXPAND_PADDING, 0);
    _coordBox1.pack_start(_x1Entry, Gtk::PACK_SHRINK, 0);
    _coordBox1.pack_start(_y1Label, Gtk::PACK_EXPAND_PADDING, 0);
    _coordBox1.pack_start(_y1Entry, Gtk::PACK_SHRINK, 0);

    _coordBox2.pack_start(_x2Label, Gtk::PACK_EXPAND_PADDING, 0);
    _coordBox2.pack_start(_x2Entry, Gtk::PACK_SHRINK, 0);
    _coordBox2.pack_start(_y2Label, Gtk::PACK_EXPAND_PADDING, 0);
    _coordBox2.pack_start(_y2Entry, Gtk::PACK_SHRINK, 0);

    /* Entries size */
    _x1Entry.set_width_chars(6);
    _x2Entry.set_width_chars(6);
    _y1Entry.set_width_chars(6);
    _y2Entry.set_width_chars(6);


    /* Control */
    _buttonBox.set_layout(Gtk::BUTTONBOX_END);
    _buttonBox.add(_cancelButton);
    _buttonBox.add(_okButton);

    _cancelButton.signal_clicked().connect(sigc::mem_fun(
            *this, &LineDialog::on_button_cancel_clicked));
    _okButton.signal_clicked().connect(sigc::mem_fun(
            *this, &LineDialog::on_button_ok_clicked));

    show_all_children();
}

LineDialog::~LineDialog() {
}

void LineDialog::setInterfaceController(InterfaceController *InterfaceController) {
    _InterfaceController = InterfaceController;
}

void LineDialog::on_button_cancel_clicked() {
    std::cout << "...operation cancelled!" << std::endl;
    hide();
}

void LineDialog::on_button_ok_clicked() {
    size_t x1, x2, y1, y2;
    std::stringstream sX1, sY1, sX2, sY2;

    /* Get input data from dialog box Entries */
    const std::string name = _nameEntry.get_text().raw();
    sX1 << _x1Entry.get_text().raw();
    sY1 << _y1Entry.get_text().raw();
    sX2 << _x2Entry.get_text().raw();
    sY2 << _y2Entry.get_text().raw();

    if (!name.empty() && sX1.str().size() != 0 && sY1.str().size() != 0
            && sX2.str().size() != 0 && sY2.str().size() != 0) {

        sX1 >> x1;
        sY1 >> y1;
        sX2 >> x2;
        sY2 >> y2;

        /* Create the new line and close this window */
        _InterfaceController->createLine(name, x1, y1, x2, y2);
    }

    /* Clear the contents of the Entries and close the window */
    LineDialog::clearDialog();
    hide();
}

void LineDialog::clearDialog() {
    _nameEntry.set_text("");
    _x1Entry.set_text("");
    _y1Entry.set_text("");
    _x2Entry.set_text("");
    _y2Entry.set_text("");
}