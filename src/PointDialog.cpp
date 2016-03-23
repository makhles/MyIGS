/* PointDialog.cpp */

#include <iostream>
#include "PointDialog.h"
#include "Point.h"
#include "WorldWindow.h"

PointDialog::PointDialog() :
        _mainBox(Gtk::ORIENTATION_VERTICAL),
        _nameBox(Gtk::ORIENTATION_HORIZONTAL),
        _coordBox(Gtk::ORIENTATION_HORIZONTAL),
        _buttonBox(Gtk::ORIENTATION_HORIZONTAL),
        _nameLabel("Name: "),
        _xLabel("x ="),
        _yLabel("y ="),
        _okButton("OK"),
        _cancelButton("Cancel") {

    /* Window properties */
    set_title("Create Point");
    set_border_width(10);
    set_resizable(false);

    /* Main box */
    add(_mainBox);

    /* Pack widgets */
    _mainBox.pack_start(_nameBox, Gtk::PACK_EXPAND_WIDGET, 1);
    _mainBox.pack_start(_coordBox, Gtk::PACK_EXPAND_WIDGET, 1);
    _mainBox.pack_start(_buttonSeparator, Gtk::PACK_EXPAND_WIDGET, 1);
    _mainBox.pack_start(_buttonBox, Gtk::PACK_EXPAND_WIDGET, 1);

    /* Input */
    _nameBox.set_homogeneous(false);
    _coordBox.set_homogeneous(false);
    _nameBox.pack_start(_nameLabel, Gtk::PACK_SHRINK, 0);
    _nameBox.pack_start(_nameEntry, Gtk::PACK_EXPAND_WIDGET, 0);
    _coordBox.pack_start(_xLabel, Gtk::PACK_EXPAND_PADDING, 0);
    _coordBox.pack_start(_xEntry, Gtk::PACK_SHRINK, 0);
    _coordBox.pack_start(_yLabel, Gtk::PACK_EXPAND_PADDING, 0);
    _coordBox.pack_start(_yEntry, Gtk::PACK_SHRINK, 0);

    /* Entries size */
    _xEntry.set_width_chars(6);
    _yEntry.set_width_chars(6);


    /* Control */
    _buttonBox.set_layout(Gtk::BUTTONBOX_END);
    _buttonBox.add(_cancelButton);
    _buttonBox.add(_okButton);

    _cancelButton.signal_clicked().connect(sigc::mem_fun(
            *this, &PointDialog::on_button_cancel_clicked));
    _okButton.signal_clicked().connect(sigc::mem_fun(
            *this, &PointDialog::on_button_ok_clicked));

    show_all_children();
}

PointDialog::~PointDialog() {
}

void PointDialog::setWorldWindow(WorldWindow *worldWindow) {
    _worldWindow = worldWindow;
}

void PointDialog::on_button_cancel_clicked() {
    std::cout << "...operation cancelled!" << std::endl;
    hide();
}

void PointDialog::on_button_ok_clicked() {
    size_t x, y;
    std::string name;
    std::stringstream stringX, stringY;

    /* Get input data from dialog box Entries */
    name = _nameEntry.get_text().raw();
    stringX << _xEntry.get_text().raw();
    stringY << _yEntry.get_text().raw();
    
    /* Check for empty Entries */
    if (!name.empty() && stringX.str().size() != 0 && stringY.str().size() != 0) {
        stringX >> x;
        stringY >> y;

        /* Create the new point */
        _worldWindow->createPoint(name, x, y);
    }

    /* Clear the contents of the Entries and close the window */
    PointDialog::clearDialog();
    hide();
}

void PointDialog::clearDialog() {
    _nameEntry.set_text("");
    _xEntry.set_text("");
    _yEntry.set_text("");
}