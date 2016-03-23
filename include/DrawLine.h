/* DrawLine.h */

#ifndef DRAWLINE_H
#define DRAWLINE_H

#include "Drawable.h"

class Line;
class WorldWindow;

class DrawLine : public Drawable {

    protected:
        
        Line *_line;         // Original line from model
        Line *_clippedLine;  // Line clipped to current window area
        Line *_vpLine;       // Line to be displayed at the viewport
        WorldWindow *_worldWindow;

    protected:
        void windowToViewport() override;

    public:
        DrawLine(Line *line, WorldWindow *worldWindow);
        virtual ~DrawLine();
        void draw(const Cairo::RefPtr<Cairo::Context> &cr) override;
        void clipToWindow() override;
};

#endif  // DRAWLINE_H