/* MyIGS.h */

#ifndef MYIGS_H
#define MYIGS_H

#include <gtkmm.h>
#include "GraphicalObject.h"
#include "Canvas.h"
#include "OutputBoard.h"

class MyIGS : public Gtk::Window {
    private:
        Gtk::Box _mainBox;
        Gtk::Frame _controlFrame;
        Gtk::Frame _viewportFrame;
        Gtk::Frame _objectsFrame;
        /* Widgets used in the Control Frame */
        Gtk::Box _controlBox;
        Gtk::Frame _zoomFrame;
        Gtk::Frame _dispFrame;
        /* Widgets used in the Viewport Frame */
        Gtk::Box _viewportBox;
        Canvas _canvas;
        OutputBoard _board;
        std::list<GraphicalObject> objects;
    private:
        void createControlFrame();
        void createViewportFrame();
        void createObjectsFrame();
    public:
        MyIGS();
        virtual ~MyIGS();
};
#endif