/* WorldWindow.h */

#ifndef WORLDWINDOW_H
#define WORLDWINDOW_H

#include <list>
#include <string>
#include <cstddef>              // For size_t

class MyIGS;
class GraphicalObject;

class WorldWindow {

    protected:
        std::list<GraphicalObject*> _displayFile;
        MyIGS *_view;

    public:
        WorldWindow();
        virtual ~WorldWindow();
        void setView(MyIGS *view);
        void createPoint(std::string name, const size_t xPos, const size_t yPos);
};

#endif  // WORLDWINDOW_H