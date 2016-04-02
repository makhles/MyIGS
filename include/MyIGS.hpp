/* MyIGS.h */

#ifndef MYIGS_H
#define MYIGS_H

#include <gtkmm.h>
#include "Canvas.hpp"
#include "OutputBoard.hpp"

class InterfaceController;
class Shape;

class MyIGS : public Gtk::Window {
    protected:
        InterfaceController *_interfaceController;

        /* Main widgets */
        Gtk::HBox * const m_mainBox;
        Gtk::Frame * const m_controlFrame;
        Gtk::Frame * const m_viewportFrame;
        Gtk::Frame * const m_objectsFrame;

        /* Widgets used in the Control Frame */
        Gtk::Box _controlBox;
        Gtk::Box _zoomBox;
        Gtk::Grid _dispGrid;
        Gtk::Frame _zoomFrame;
        Gtk::Frame _dispFrame;
        Gtk::Button _zoomButtonOut;
        Gtk::Button _zoomButtonIn;
        Gtk::Button _dispButtonUp;
        Gtk::Button _dispButtonDown;
        Gtk::Button _dispButtonLeft;
        Gtk::Button _dispButtonRight;

        /* Widgets used in the Viewport Frame */
        Gtk::Box _viewportBox;
        Canvas _canvas;
        OutputBoard _board;

        /* Widgets used in the objects frame */
        Gtk::Box _objectsBox;
        Gtk::Separator _objectsSeparator;
        Gtk::ScrolledWindow _objectsWindow;
        Gtk::Button _buttonCreatePoint;
        Gtk::Button _buttonCreateLine;
        Gtk::Button _buttonCreateWireframe;
        Gtk::Label _labelCreateObjects;
        Gtk::ListViewText _objectsListView;

    protected:
        void createControlFrame();
        void createViewportFrame();
        void createObjectsFrame();

        /* Control */
        void zoomWindowIn();
        void zoomWindowOut();
        void moveWindowUp();
        void moveWindowRight();
        void moveWindowDown();
        void moveWindowLeft();

        /* Objects creation */
        void createPoint();
        void createLine();
        void createWireframe();

    public:
        MyIGS();
        virtual ~MyIGS();
        void appendObjectToViewList(const Shape *obj);
};

#endif  // MYIGS_H