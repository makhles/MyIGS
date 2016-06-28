// TMatrixBuilder.hpp
// Authors: Leonardo Vailatti Eichstaedt
//          Makhles Reuter Lange
//
// This class should be used for creating Transformation Matrixes.
// It has a static method called instance(), which should be called
// to get a pointer to this class and operate on its members.

#ifndef TMATRIX_BUILDER_HPP
#define TMATRIX_BUILDER_HPP

// Forward declarations
class TMatrix;
template <class T> class Coord;

class TMatrixBuilder {

private:
    static TMatrixBuilder *m_pInstance;

    TMatrixBuilder() {}
    ~TMatrixBuilder() {}
    TMatrixBuilder(const TMatrixBuilder &) {};
    void operator=(const TMatrixBuilder &) {};

public:
    static TMatrixBuilder* instance();
    void translation_matrix(TMatrix &m, const Coord<double> &t);
    void scaling_matrix(TMatrix &m, const Coord<double> &s, const Coord<double> &p);
    void rotation_matrix(TMatrix &m, double angle, const Coord<double> &A,
            const Coord<double> &B);
    void rotation_about_x(TMatrix &rx, double sin_, double cos_) const;
    void rotation_about_y(TMatrix &ry, double sin_, double cos_) const;
    void rotation_about_z(TMatrix &rz, double sin_, double cos_) const;
    void normalizing_matrix(TMatrix &m, const Coord<double> &window_center,
            const Coord<double> &window_scaling, const Coord<double> &window_rotation);
    void window_translation(TMatrix &m, const Coord<double> &window_center,
            const Coord<double> &window_rotation, const Coord<double> &window_translation);
};

#endif  // TMATRIX_BUILDER_HPP