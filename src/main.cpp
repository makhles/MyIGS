/* Copyright: Makhles Reuter Lange, 2016.
   Compile command:
   g++ `pkg-config --cflags --libs gtkmm-3.0` -o main main.cpp
*/

#include <gtkmm/application.h>
#include "MyIGS.hpp"

int main(int argc, char *argv[]) {

    /* Initialization */
    auto app = Gtk::Application::create(argc, argv, "org.gtkmm.examples.base");

    MyIGS myIGS(app);

    /* Show the window and return when closed */
    return app->run(myIGS);
}