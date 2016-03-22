/* WorldWindow.h */

#ifndef WORLDWINDOW_H
#define WORLDWINDOW_H

#include <list>
#include "GraphicalObject.h"

class WorldWindow {

    protected:
        std::list<GraphicalObject> _displayFile;

    public:
        WorldWindow();
        virtual ~WorldWindow();
        void addGraphicalObject(const GraphicalObject &obj);
};

#endif  // WORLDWINDOW_H