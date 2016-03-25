/* PointDialog.h */

#ifndef POINTDIALOG_H
#define POINTDIALOG_H

#include <gtkmm/window.h>
#include <gtkmm/box.h>
#include <gtkmm/label.h>
#include <gtkmm/entry.h>
#include <gtkmm/button.h>
#include <gtkmm/buttonbox.h>
#include <gtkmm/separator.h>

class InterfaceController;

class PointDialog : public Gtk::Window {
    protected:
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
        Gtk::Button _okButton;
        Gtk::Button _cancelButton;
        InterfaceController *_InterfaceController;

    public:
        PointDialog();
        virtual ~PointDialog();
        void setInterfaceController(InterfaceController *InterfaceController);

    protected:
        void on_button_cancel_clicked();
        void on_button_ok_clicked();
        void clearDialog();
};

#endif  // POINTDIALOG_H