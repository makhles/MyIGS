/* Coord.h */

#ifndef COORD_H
#define COORD_H

template <class T>
class Coord {
    private:
        const T _x;
        const T _y;
    public:
        Coord(const T &x, const T &y) : _x(x), _y(y) {}
        ~Coord() {}
        const T getX() const {return _x;}
        const T getY() const {return _y;}
};

#endif  // COORD_H