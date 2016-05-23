// Colour.hpp
// Authors: Leonardo Vailatti Eichstaedt
//          Makhles Reuter Lange

#ifndef COLOUR_HPP
#define COLOUR_HPP

class Colour {

public:
    Colour (float red = 0.0, float green = 0.0, float blue = 0.0, float alpha = 1.0) :
        m_red(red), m_green(green), m_blue(blue), m_alpha(alpha) {}
    ~Colour () {}
    float r() const { return m_red; }
    float g() const { return m_green; }
    float b() const { return m_blue; }
    float a() const { return m_alpha; }
    bool operator==(const Colour &rhs) {
        return ((rhs.m_red == m_red) &&
                (rhs.m_green == m_green) &&
                (rhs.m_blue == m_blue) &&
                (rhs.m_alpha == m_alpha));
    }

private:
    float m_red;
    float m_green;
    float m_blue;
    float m_alpha;
};

#endif // COLOUR_HPP