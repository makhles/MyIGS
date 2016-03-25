/* DrawLine.h */

#ifndef DRAWLINE_H
#define DRAWLINE_H

#include "Drawable.h"

class Line;
class InterfaceController;

class DrawLine : public Drawable {

    protected:
        
        Line *_line;         // Original line from model
        Line *_clippedLine;  // Line clipped to current window area
        Line *_vpLine;       // Line to be displayed at the viewport
        InterfaceController *_InterfaceController;

    protected:
        void windowToViewport() override;

    public:
        DrawLine(Line *line, InterfaceController *InterfaceController);
        virtual ~DrawLine();
        void draw(const Cairo::RefPtr<Cairo::Context> &cr) override;
        void clipToWindow() override;
};

#endif  // DRAWLINE_H