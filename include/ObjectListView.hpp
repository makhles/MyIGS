// ObjectListView.hpp
// Authors: Leonardo Vailatti Eichstaedt
//          Makhles Reuter Lange

#ifndef OBJECT_LIST_VIEW_HPP
#define OBJECT_LIST_VIEW_HPP

#include <gtkmm.h>

class ObjectListView : public Gtk::TreeView {

protected:
    
    // Signal handlers
    bool on_button_press_event(GdkEventButton* button_event) override;
    void on_menu_file_popup_generic();

    //Tree model columns:
    class ModelColumns : public Gtk::TreeModel::ColumnRecord {
        public:

        ModelColumns() {
            add(m_colId);
            add(m_colName);
        }

        Gtk::TreeModelColumn<unsigned int> m_colId;
        Gtk::TreeModelColumn<Glib::ustring> m_colName;
    };

    ModelColumns m_columns;
    Glib::RefPtr<Gtk::ListStore> m_refTreeModel;
    Gtk::Menu m_menuPopup;

public:
    ObjectListView();
    virtual ~ObjectListView() {}
};

#endif  // OBJECT_LIST_VIEW_HPP