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
        void createLine(std::string name, const size_t x1Pos, const size_t y1Pos,
                const size_t x2Pos, const size_t y2Pos);
};

#endif  // WORLDWINDOW_H