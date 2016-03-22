/* WorldWindow.h */

#ifndef WORLDWINDOW_H
#define WORLDWINDOW_H

#include <list>
#include <string>
#include <cstddef>              // For size_t

class MyIGS;
class GraphicalObject;
class Canvas;

class WorldWindow {

    protected:
        std::list<GraphicalObject*> _displayFile;
        MyIGS *_view;
        Canvas *_canvas;

    public:
        WorldWindow();
        virtual ~WorldWindow();
        std::list<GraphicalObject*> get_displayFile() {return _displayFile;}
        void setView(MyIGS *view) {_view = view;}
        void setCanvas(Canvas *canvas) {_canvas = canvas;}
        void createPoint(std::string name, const size_t xPos, const size_t yPos);
        void createLine(std::string name, const size_t x1Pos, const size_t y1Pos,
                const size_t x2Pos, const size_t y2Pos);
};

#endif  // WORLDWINDOW_H