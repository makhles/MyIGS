/* Coord.h */

#ifndef COORD_H
#define COORD_H

template <class T>
class Coord {
private:
    T m_x;
    T m_y;
public:
    Coord() : m_x(0), m_y(0) {}
    Coord(const T x, const T y) : m_x(x), m_y(y) {}
    ~Coord() {}
    const T x() const { return m_x; }
    const T y() const { return m_y; }
    void set_x(T x) { m_x = x; }
    void set_y(T y) { m_y = y; }
};

#endif  // COORD_H