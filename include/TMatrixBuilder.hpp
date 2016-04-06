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
    std::list<TMatrix*> m_transformations;
    TMatrix *m_globalMatrix;

    TMatrixBuilder();
    ~TMatrixBuilder();
    TMatrixBuilder(const TMatrixBuilder &) {};
    void operator=(const TMatrixBuilder &) {};
    void reset();

public:
    static TMatrixBuilder* instance();
    void addTranslation(double dx, double dy);
    void addScaling(double sx, double sy);
    void addRotation(double angleZ, TransformationType type);
    void rollback();
    void addCentroid(const double x, const double y);
    TMatrix* createMatrix();
};

#endif  // TMATRIX_BUILDER_HPP