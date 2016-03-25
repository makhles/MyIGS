/* LineDialog.h */

#ifndef LINEDIALOG_H
#define LINEDIALOG_H

#include <gtkmm/window.h>
#include <gtkmm/box.h>
#include <gtkmm/label.h>
#include <gtkmm/entry.h>
#include <gtkmm/button.h>
#include <gtkmm/buttonbox.h>
#include <gtkmm/separator.h>

class InterfaceController;

class LineDialog : public Gtk::Window {
    protected:
        Gtk::Box _mainBox;
        Gtk::Box _nameBox;
        Gtk::Box _coordBox1;
        Gtk::Box _coordBox2;
        Gtk::ButtonBox _buttonBox;
        Gtk::Separator _buttonSeparator;
        Gtk::Label _nameLabel;
        Gtk::Label _x1Label;
        Gtk::Label _x2Label;
        Gtk::Label _y1Label;
        Gtk::Label _y2Label;
        Gtk::Entry _nameEntry;
        Gtk::Entry _x1Entry;
        Gtk::Entry _x2Entry;
        Gtk::Entry _y1Entry;
        Gtk::Entry _y2Entry;
        Gtk::Button _okButton;
        Gtk::Button _cancelButton;
        InterfaceController *_interfaceController;

    public:
        LineDialog();
        virtual ~LineDialog();
        void setInterfaceController(InterfaceController *interfaceController);

    protected:
        void on_button_cancel_clicked();
        void on_button_ok_clicked();
        void clearDialog();
};

#endif  // LINEDIALOG_H