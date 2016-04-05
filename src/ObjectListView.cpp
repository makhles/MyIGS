// ObjectListView.hpp
// Authors: Leonardo Vailatti Eichstaedt
//          Makhles Reuter Lange

#include <iostream>
#include "ObjectListView.hpp"

ObjectListView::ObjectListView() {

    // Create the tree model
    m_refTreeModel = Gtk::ListStore::create(m_columns);
    set_model(m_refTreeModel);

    // Fill the TreeView's model
    Gtk::TreeModel::Row row = *(m_refTreeModel->append());
    row[m_columns.m_colId] = 1;
    row[m_columns.m_colName] = "Object 1";

    row = *(m_refTreeModel->append());
    row[m_columns.m_colId] = 2;
    row[m_columns.m_colName] = "Object 2";

    row = *(m_refTreeModel->append());
    row[m_columns.m_colId] = 3;
    row[m_columns.m_colName] = "Object 3";

    // Add the TreeView's view columns:
    append_column("ID", m_columns.m_colId);
    append_column("Name", m_columns.m_colName);

    // Fill popup menu:
    auto item = Gtk::manage(new Gtk::MenuItem("Transform", true));
    item->signal_activate().connect(sigc::mem_fun(*this, &ObjectListView::on_menu_file_popup_generic));
    m_menuPopup.append(*item);

    item = Gtk::manage(new Gtk::MenuItem("Delete", true));
    item->signal_activate().connect(sigc::mem_fun(*this, &ObjectListView::on_menu_file_popup_generic));
    m_menuPopup.append(*item);

    item = Gtk::manage(new Gtk::MenuItem("_Remove", true));
    item->signal_activate().connect(sigc::mem_fun(*this, &ObjectListView::on_menu_file_popup_generic));
    m_menuPopup.append(*item);

    m_menuPopup.accelerate(*this);
    m_menuPopup.show_all(); // Show all menu items when the menu pops up
}


bool ObjectListView::on_button_press_event(GdkEventButton* button_event) {
    bool return_value = false;

    // Call base class, to allow normal handling,
    // such as allowing the row to be selected by the right-click:
    return_value = TreeView::on_button_press_event(button_event);

    // Then do our custom stuff:
    if((button_event->type == GDK_BUTTON_PRESS) && (button_event->button == 3)) {
        m_menuPopup.popup(button_event->button, button_event->time);
    }

    return return_value;
}


void ObjectListView::on_menu_file_popup_generic() {
    std::cout << "A popup menu item was selected." << std::endl;

    auto refSelection = get_selection();
    if(refSelection) {
        Gtk::TreeModel::iterator iter = refSelection->get_selected();
        if(iter) {
            int id = (*iter)[m_columns.m_colId];
            std::cout << "  Selected ID=" << id << std::endl;
        }
    }
}