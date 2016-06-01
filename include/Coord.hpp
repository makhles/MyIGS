// Coord.hpp
// Authors: Leonardo Vailatti Eichstaedt
//          Makhles Reuter Lange

#ifndef COORD_H
#define COORD_H

template <class T>
class Coord {
private:
    T m_x;
    T m_y;
    T m_z;

public:
    Coord() : m_x(0), m_y(0), m_z(0) {}
    Coord(const T x, const T y) : m_x(x), m_y(y), m_z(0) {}
    Coord(const T x, const T y, const T z) : m_x(x), m_y(y), m_z(z) {}
    ~Coord() {}
    const T x() const { return m_x; }
    const T y() const { return m_y; }
    const T z() const { return m_z; }
    void set_x(T x) { m_x = x; }
    void set_y(T y) { m_y = y; }
    void set_z(T z) { m_z = z; }

    bool operator==(const Coord<T> &rhs) const {
        return (rhs.m_x == m_x &&
                rhs.m_y == m_y &&
                rhs.m_z == m_z);
    }

    bool operator!=(const Coord<T> &rhs) const {
        return !(*this == rhs);
    }
};

#endif  // COORD_H