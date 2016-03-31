/* WireframeDialog */

#ifndef WIREFRAME_DIALOG_H
#define WIREFRAME_DIALOG_H

#include <gtkmm/window.h>
#include <gtkmm/box.h>
#include <gtkmm/label.h>
#include <gtkmm/entry.h>
#include <gtkmm/button.h>
#include <gtkmm/buttonbox.h>
#include <gtkmm/separator.h>
#include <list>

class InterfaceController;

class WireframeDialog : public Gtk::Window {

    protected:
        std::list<double> _xCoords;
        std::list<double> _yCoords;
        Gtk::Box _mainBox;
        Gtk::Box _nameBox;
        Gtk::Box _coordBox;
        Gtk::ButtonBox _buttonBox;
        Gtk::Separator _buttonSeparator;
        Gtk::Label _nameLabel;
        Gtk::Label _xLabel;
        Gtk::Label _yLabel;
        Gtk::Entry _nameEntry;
        Gtk::Entry _xEntry;
        Gtk::Entry _yEntry;
        Gtk::Button _addButton;
        Gtk::Button _okButton;
        Gtk::Button _cancelButton;
        InterfaceController *_interfaceController;

    public:
        WireframeDialog();
        virtual ~WireframeDialog();
        void setInterfaceController(InterfaceController *interfaceController);

    protected:
        void on_button_cancel_clicked();
        void on_button_ok_clicked();
        void on_button_add_clicked();
        void clearDialog();
};

#endif  // WIREFRAME_DIALOG_H