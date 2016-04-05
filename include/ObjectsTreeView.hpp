// ObjectsTreeView.hpp
// Authors: Leonardo Vailatti Eichstaedt
//          Makhles Reuter Lange

#ifndef OBJECTS_TREE_VIEW_HPP
#define OBJECTS_TREE_VIEW_HPP

#include <gtkmm.h>

class ObjectsTreeView : public Gtk::TreeView {

protected:
    unsigned m_objCount;

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
    ObjectsTreeView();
    virtual ~ObjectsTreeView() {}
    void appendObject(const Glib::ustring obj);
};

#endif  // OBJECTS_TREE_VIEW_HPP