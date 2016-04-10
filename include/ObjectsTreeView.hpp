// ObjectsTreeView.hpp
// Authors: Leonardo Vailatti Eichstaedt
//          Makhles Reuter Lange

#ifndef OBJECTS_TREE_VIEW_HPP
#define OBJECTS_TREE_VIEW_HPP

#include <gtkmm.h>

class InterfaceController;

class ObjectsTreeView : public Gtk::TreeView {

protected:
    InterfaceController *m_controller;
    unsigned m_objCount;
    std::string m_selectedObjName;

    // Signal handlers
    bool on_button_press_event(GdkEventButton* button_event) override;
    void on_menu_popup_transform();
    void on_menu_popup_delete();

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

    void set_selected_object();

public:
    ObjectsTreeView();
    virtual ~ObjectsTreeView() {}
    void setInterfaceController(InterfaceController *controller) {m_controller = controller;}
    void append_object(const Glib::ustring obj);
    std::string get_selected_object() const {return m_selectedObjName;}
};

#endif  // OBJECTS_TREE_VIEW_HPP