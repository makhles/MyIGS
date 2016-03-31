/* WireframeDialog.cpp */

#include <iostream>
#include "WireframeDialog.h"
#include "Wireframe.h"
#include "InterfaceController.h"
#include "Coord.h"

WireframeDialog::WireframeDialog() :
        _mainBox(Gtk::ORIENTATION_VERTICAL),
        _nameBox(Gtk::ORIENTATION_HORIZONTAL),
        _coordBox(Gtk::ORIENTATION_HORIZONTAL),
        _buttonBox(Gtk::ORIENTATION_HORIZONTAL),
        _nameLabel("Name: "),
        _xLabel("x ="),
        _yLabel("y ="),
        _addButton("Add point"),
        _okButton("OK"),
        _cancelButton("Cancel") {

    /* Window properties */
    set_title("Create Wireframe");
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
    _buttonBox.add(_addButton);
    _buttonBox.add(_okButton);

    _cancelButton.signal_clicked().connect(sigc::mem_fun(
            *this, &WireframeDialog::on_button_cancel_clicked));
    _addButton.signal_clicked().connect(sigc::mem_fun(
            *this, &WireframeDialog::on_button_add_clicked));
    _okButton.signal_clicked().connect(sigc::mem_fun(
            *this, &WireframeDialog::on_button_ok_clicked));

    show_all_children();
    _okButton.hide();  // Only visible after 2 points have been added
}

WireframeDialog::~WireframeDialog() {
}

void WireframeDialog::setInterfaceController(InterfaceController *interfaceController) {
    _interfaceController = interfaceController;
}

void WireframeDialog::on_button_cancel_clicked() {
    std::cout << "...operation cancelled!" << std::endl;
    this->clearDialog();
    hide();
}

void WireframeDialog::on_button_add_clicked() {
    double x, y;
    std::stringstream sX, sY;

    /* Get input data from dialog box Entries */
    const std::string name = _nameEntry.get_text().raw();
    sX << _xEntry.get_text().raw();
    sY << _yEntry.get_text().raw();

    /* Add point only if all entries were filled */
    if (!name.empty() && sX.str().size() != 0 && sY.str().size() != 0) {
        sX >> x;
        sY >> y;
        _coords.push_back(new Coord<double>(x,y));

        /* Hide name entry */
        _xEntry.set_text("");
        _yEntry.set_text("");
        _nameEntry.hide();
        _nameLabel.hide();

        /* Check if minimum number of points have been added */
        if (_coords.size() == 2) {
            _okButton.show();
        }
    }
}

void WireframeDialog::on_button_ok_clicked() {
    double x, y;
    std::stringstream sX, sY;

    /* Get input data from dialog box Entries */
    const std::string name = _nameEntry.get_text().raw();
    sX << _xEntry.get_text().raw();
    sY << _yEntry.get_text().raw();

    /* Add point only if all entries were filled */
    if (!name.empty() && sX.str().size() != 0 && sY.str().size() != 0) {
        sX >> x;
        sY >> y;
        _coords.push_back(new Coord<double>(x,y));
        
        /* Create the new wireframe and close this window */
        _interfaceController->createWireframe(name, _coords);
        std::cout << "Vortei." << std::endl;
        this->clearDialog();
        hide();
    }

    /* With at least 3 points added, a Wireframe can be created */
    else if (_coords.size() >= 3) {
        _interfaceController->createWireframe(name, _coords);
        this->clearDialog();
        hide();
    }
}

void WireframeDialog::clearDialog() {
    _nameEntry.set_text("");
    _xEntry.set_text("");
    _yEntry.set_text("");
    _nameEntry.show();
    _nameLabel.show();
    _okButton.hide();
    _coords.clear();
}
