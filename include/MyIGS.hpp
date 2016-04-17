/* MyIGS.h */

#ifndef MYIGS_H
#define MYIGS_H

#include <gtkmm.h>
#include "Canvas.hpp"

class InterfaceController;
class Shape;
class ObjectsTreeView;

class MyIGS : public Gtk::Window {
protected:
    ObjectsTreeView * const m_objectsView;
    Canvas * const m_canvas;
    Glib::RefPtr<Gtk::Adjustment> m_scaleAdjustment;
    Gtk::Entry * const m_angleEntry;

    // Radio buttons state
    bool m_csActive;
    bool m_lbActive;
    bool m_nlnActive;
    bool m_shActive;
    bool m_waActive;
    
    InterfaceController *m_controller;

    // Control
    void on_window_adjustment_value_changed();
    void move_window_up();
    void move_window_right();
    void move_window_down();
    void move_window_left();
    void rotate_window();

    // Objects creation
    void create_point();
    void create_line();
    void create_wireframe();

    // Action handlers
    void on_action_file_load_obj_file();
    void on_action_file_export_obj_file();
    void on_action_file_quit();
    void on_cs_radio_toggled();
    void on_lb_radio_toggled();
    void on_nln_radio_toggled();
    void on_sh_radio_toggled();
    void on_wa_radio_toggled();

public:
    MyIGS();
    virtual ~MyIGS();
    void append_object(const Glib::ustring obj);
};

#endif  // MYIGS_H