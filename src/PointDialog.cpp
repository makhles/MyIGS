/* PointDialog.cpp */

#include <iostream>
#include "PointDialog.h"
#include "Point.h"

PointDialog::PointDialog() :
        _mainBox(Gtk::ORIENTATION_VERTICAL),
        _nameBox(Gtk::ORIENTATION_HORIZONTAL),
        _coordBox(Gtk::ORIENTATION_HORIZONTAL),
        _buttonBox(Gtk::ORIENTATION_HORIZONTAL),
        _nameLabel("Name: "),
        _xLabel("x = "),
        _yLabel("y = "),
        _okButton("OK"),
        _cancelButton("Cancel") {

    /* Window properties */
    set_title("Create Point");
    set_default_size(300,300);
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
    _nameBox.pack_start(_nameLabel, Gtk::PACK_EXPAND_WIDGET, 1);
    _nameBox.pack_start(_nameEntry, Gtk::PACK_EXPAND_WIDGET, 1);
    _coordBox.pack_start(_xLabel, Gtk::PACK_EXPAND_WIDGET, 1);
    _coordBox.pack_start(_xEntry, Gtk::PACK_EXPAND_WIDGET, 3);
    _coordBox.pack_start(_yLabel, Gtk::PACK_EXPAND_WIDGET, 1);
    _coordBox.pack_start(_yEntry, Gtk::PACK_EXPAND_WIDGET, 3);

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

void PointDialog::setWorldWindow(WorldWindow &worldWindow) {
    _worldWindow = worldWindow;
}

void PointDialog::on_button_cancel_clicked() {
    std::cout << "...operation cancelled!" << std::endl;
    hide();
}

void PointDialog::on_button_ok_clicked() {
    
    const std::string name = _nameEntry.get_text().raw();
    size_t x, y;
    std::stringstream s;
    s << _xEntry.get_text().raw();
    s >> x;
    s << _yEntry.get_text().raw();
    s >> y;

    Point point(name, x, y);
    std::cout << "Point created!" << std::endl;
    _worldWindow.addGraphicalObject(point);
    hide();
}