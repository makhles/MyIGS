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


class TMatrixBuilder {

private:
    static TMatrixBuilder *m_pInstance;

    TMatrixBuilder() {}
    ~TMatrixBuilder() {}
    TMatrixBuilder(const TMatrixBuilder &) {};
    void operator=(const TMatrixBuilder &) {};

public:
    static TMatrixBuilder* instance();
    void translation_matrix(TMatrix &m, double dx, double dy);
    void scaling_matrix(TMatrix &m, double sx, double sy, double x, double y);
    void rotation_matrix(TMatrix &m, double angleZ, double x, double y);
};

#endif  // TMATRIX_BUILDER_HPP