// TMatrixBuilder.hpp
// Authors: Leonardo Vailatti Eichstaedt
//          Makhles Reuter Lange
//
// This class should be used for creating Transformation Matrixes.
// It has a static method called instance(), which should be called
// to get a pointer to this class and operate on its members.

#ifndef TMATRIX_BUILDER_HPP
#define TMATRIX_BUILDER_HPP

#include <list>
#include <string>
#include "TransformationType.hpp"

class TMatrix;

class TMatrixBuilder {
private:
    static TMatrixBuilder *m_pInstance;
    TMatrix *m_tMatrix;

    TMatrixBuilder();
    ~TMatrixBuilder();
    TMatrixBuilder(const TMatrixBuilder &) {};
    void operator=(const TMatrixBuilder &) {};

public:
    static TMatrixBuilder* instance();

    void createTranslationMatrix(double dx, double dy);
    void createScalingMatrix(double sx, double sy);
    void createRotationMatrix(double angleZ);
    void createRotationMatrix(double angleZ, double sx, double sy);

    void reset();
    TMatrix* buildMatrix(const double x, const double y);
};

#endif  // TMATRIX_BUILDER_HPP