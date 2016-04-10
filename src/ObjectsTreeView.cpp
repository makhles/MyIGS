// ObjectsTreeView.hpp
// Authors: Leonardo Vailatti Eichstaedt
//          Makhles Reuter Lange

#include <iostream>
#include "ObjectsTreeView.hpp"
#include "TransformationDialog.hpp"
#include "InterfaceController.hpp"

ObjectsTreeView::ObjectsTreeView() :
    m_objCount(0)
{

    // Create the tree model
    m_refTreeModel = Gtk::ListStore::create(m_columns);
    set_model(m_refTreeModel);

    // Add the TreeView's view columns:
    append_column("ID", m_columns.m_colId);
    append_column("Name", m_columns.m_colName);

    // Fill popup menu:
    auto item = Gtk::manage(new Gtk::MenuItem("Transform", true));
    item->signal_activate().connect(sigc::mem_fun(*this, &ObjectsTreeView::on_menu_popup_transform));
    m_menuPopup.append(*item);

    item = Gtk::manage(new Gtk::MenuItem("Delete", true));
    item->signal_activate().connect(sigc::mem_fun(*this, &ObjectsTreeView::on_menu_popup_delete));
    m_menuPopup.append(*item);

    m_menuPopup.accelerate(*this);
    m_menuPopup.show_all(); // Show all menu items when the menu pops up
}


bool ObjectsTreeView::on_button_press_event(GdkEventButton* button_event) {
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


void ObjectsTreeView::on_menu_popup_transform() {
    this->set_selected_object();

    std::cout << "A popup menu item was selected." << std::endl;
    std::cout << "  Selected object = " << m_selectedObjName << std::endl;

    TransformationDialog dialog("Transformations", m_controller, this);
    dialog.run();
}


void ObjectsTreeView::on_menu_popup_delete() {
    std::cout << "Deleting object... not implemented yet." << std::endl;
}


void ObjectsTreeView::set_selected_object() {
    Glib::ustring objName = "";
    auto refSelection = get_selection();
    if(refSelection) {
        Gtk::TreeModel::iterator iter = refSelection->get_selected();
        if(iter) {
            objName = (*iter)[m_columns.m_colName];
            m_selectedObjName = objName.raw();
        }
    }
}


void ObjectsTreeView::append_object(const Glib::ustring objName) {
    Gtk::TreeModel::Row row = *(m_refTreeModel->append());
    row[m_columns.m_colId] = m_objCount++;
    row[m_columns.m_colName] = objName;
}