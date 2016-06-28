// TMatrixBuilder.cpp
// Authors: Leonardo Vailatti Eichstaedt
//          Makhles Reuter Lange

#include <algorithm>
#include <math.h>
#include "TMatrixBuilder.hpp"
#include "TMatrix.hpp"
#include "Coord.hpp"

#define PI acos(-1.0)


// Global static pointer to ensure a single instance of the class.
TMatrixBuilder * TMatrixBuilder::m_pInstance = nullptr;


TMatrixBuilder* TMatrixBuilder::instance() {
    if (!m_pInstance) {
        m_pInstance = new TMatrixBuilder();
    }
    return m_pInstance;
}

/* ============================================================================================= */
void TMatrixBuilder::translation_matrix(TMatrix &m, const Coord<double> &t)
/* ============================================================================================= */
{
    // Creates a translation matrix with translation factors t.
    m(0,0) = 1.0;    m(0,1) = 0.0;    m(0,2) = 0.0;    m(0,3) = t.x();
    m(1,0) = 0.0;    m(1,1) = 1.0;    m(1,2) = 1.0;    m(1,3) = t.y();
    m(2,0) = 0.0;    m(2,1) = 0.0;    m(2,2) = 1.0;    m(2,3) = t.z();
    m(3,0) = 0.0;    m(3,1) = 0.0;    m(3,2) = 0.0;    m(3,3) = 1.0;
}

/* ============================================================================================= */
void TMatrixBuilder::scaling_matrix(TMatrix &m, const Coord<double> &s, const Coord<double> &p)
/* ============================================================================================= */
{
    // Creates a scaling matrix with scaling factors s about a point p.
    m(0,0) = s.x();   m(0,1) = 0.0;     m(0,2) = 0.0;    m(0,3) = p.x() * (1 - s.x());
    m(1,0) = 0.0;     m(1,1) = s.y();   m(1,2) = 0.0;    m(1,3) = p.y() * (1 - s.y());
    m(2,0) = 0.0;     m(2,1) = 0.0;     m(2,2) = s.z();  m(2,3) = p.z() * (1 - s.z());
    m(3,0) = 0.0;     m(3,1) = 0.0;     m(3,2) = 0.0;    m(3,3) = 1.0;
}

/* ============================================================================================= */
void TMatrixBuilder::rotation_matrix(TMatrix &m, double angle, const Coord<double> &A,
        const Coord<double> &B)
/* ============================================================================================= */
{
    const double EPS = 1.0E-6;
    double ax = A.x();
    double ay = A.y();
    double az = A.z();
    double bx = B.x();
    double by = B.y();
    double bz = B.z();

    // Create the translation matrix
    TMatrix tmat(4);
    Coord<double> minus_a(-1 * ax, -1 * ay, -1 * az);
    this->translation_matrix(tmat, minus_a);

    // Translate points A and B of -A
    std::vector<double> vec, res;
    vec.push_back(bx);
    vec.push_back(by);
    vec.push_back(bz);
    tmat.multiply_by_vector(vec, res);

    // Update points coordinates
    ax = 0.0;
    ay = 0.0;
    az = 0.0;
    bx = res[0];
    by = res[1];
    bz = res[2];

    // Magnitude of AB
    // The vector AB has the same coordinates as point B
    double length_AB = sqrt(bx*bx + by*by + bz*bz);
    
    // If the magnitude of AB is different than one, then 
    // compute the coordinates of point C that makes AC
    // a unit vector.
    double cx, cy, cz;
    if ((length_AB > 1.0 + EPS) || (length_AB < 1.0 - EPS)) {
        cx = bx / length_AB;
        cy = by / length_AB;
        cz = bz / length_AB;
    } else {
        cx = bx;
        cy = by;
        cz = bz;
    }

    // Compute diagonal d in YZ plane
    double d = sqrt(cy*cy + cz*cz);

    // Angle to the XY plane
    double sin_x = cz / d;
    double cos_x = cy / d;

    // Apply rotation in X
    TMatrix rx(4);
    this->rotation_about_x(rx, sin_x, cos_x);
    vec.clear();
    res.clear();
    vec.push_back(cx);
    vec.push_back(cy);
    vec.push_back(cz);
    rx.multiply_by_vector(vec, res);
    cx = res[0];  // = 0
    cy = res[1];
    cz = res[2];

    // Angle to the YZ plane
    double sin_z = cx;
    double cos_z = cy;

    // Apply rotation in Z
    TMatrix rz(4);
    this->rotation_about_z(rz, sin_z, cos_z);
    res.clear();
    rz.multiply_by_vector(vec, res);
    cx = res[0];  // = 0
    cy = res[1];
    cz = res[2];  // = 0

    // Vector AC is now aligned with Y axis.
    // Rotate about the Y axis with the original angle given by the user.
    angle = angle * PI / 180.0;
    TMatrix ry(4);
    double sin_y = sin(angle);
    double cos_y = cos(angle);
    this->rotation_about_y(ry, sin_y, cos_y);

    // Back transformations
    TMatrix minus_rx(4), minus_rz(4), minus_tmat(4);
    this->rotation_about_z(minus_rz, -sin_z, -cos_z);
    this->rotation_about_x(minus_rx, -sin_x, -cos_x);
    this->translation_matrix(minus_tmat, Coord<double>(A.x(), A.y(), A.z()));

    // Multiply all matrices
    m = tmat * rx * rz * ry * minus_rz * minus_rx * minus_tmat;
}

/* ============================================================================================= */
void TMatrixBuilder::rotation_about_x(TMatrix &rx, double sin_, double cos_) const
/* ============================================================================================= */
{
    rx(0,0) = 1.0;    rx(0,1) = 0.0;     rx(0,2) = 0.0;      rx(0,3) = 0.0;
    rx(1,0) = 0.0;    rx(1,1) = cos_;    rx(1,2) = -sin_;    rx(1,3) = 0.0;
    rx(2,0) = 0.0;    rx(2,1) = sin_;    rx(2,2) = cos_;     rx(2,3) = 0.0;
    rx(3,0) = 0.0;    rx(3,1) = 0.0;     rx(3,2) = 0.0;      rx(3,3) = 1.0;
}

/* ============================================================================================= */
void TMatrixBuilder::rotation_about_y(TMatrix &ry, double sin_, double cos_) const
/* ============================================================================================= */
{
    ry(0,0) = cos_;     ry(0,1) = 0.0;    ry(0,2) = sin_;    ry(0,3) = 0.0;
    ry(1,0) = 0.0;      ry(1,1) = 1.0;    ry(1,2) = 0.0;     ry(1,3) = 0.0;
    ry(2,0) = -sin_;    ry(2,1) = 0.0;    ry(2,2) = cos_;    ry(2,3) = 0.0;
    ry(3,0) = 0.0;      ry(3,1) = 0.0;    ry(3,2) = 0.0;     ry(3,3) = 1.0;
}

/* ============================================================================================= */
void TMatrixBuilder::rotation_about_z(TMatrix &rz, double sin_, double cos_) const
/* ============================================================================================= */
{
    rz(0,0) = cos_;    rz(0,1) = -sin_;    rz(0,2) = 0.0;    rz(0,3) = 0.0;
    rz(1,0) = sin_;    rz(1,1) = cos_;     rz(1,2) = 0.0;    rz(1,3) = 0.0;
    rz(2,0) = 0.0;     rz(2,1) = 0.0;      rz(2,2) = 1.0;    rz(2,3) = 0.0;
    rz(3,0) = 0.0;     rz(3,1) = 0.0;      rz(3,2) = 0.0;    rz(3,3) = 1.0;
}

/* ============================================================================================= */
void TMatrixBuilder::normalizing_matrix(TMatrix &m, const Coord<double> &window_center,
        const Coord<double> &window_scaling, const Coord<double> &window_rotation)
/* ============================================================================================= */
{
    TMatrix t_matrix(4), s_matrix(4);
    TMatrix rx_matrix(4), rz_matrix(4);

    // Translate and scale Window to the origin
    this->translation_matrix(t_matrix, -window_center);
    this->scaling_matrix(s_matrix, window_scaling, Coord<double>());

    // Alpha, beta and gamma are the angles between the VPN
    // and the X, Y and Z axis, respectively. A unit vector
    // representing the direction of the VPN is given by:
    // VPN = cos(alpha).i + cos(beta).j + cos(gamma).k
    // where alpha = window_rotation.x() and so on...
    // and i, j and k are the coordinate system basis vectors.
    double vpn_x = cos(window_rotation.x() * PI / 180.0);
    double vpn_y = cos(window_rotation.y() * PI / 180.0);
    double vpn_z = cos(window_rotation.z() * PI / 180.0);

    // Length of VPN in XY plane
    double d = sqrt(vpn_x * vpn_x + vpn_y * vpn_y);

    // Sine and cosine of angle to Y axis in XY plane
    double sin_to_y = vpn_x / d;
    double cos_to_y = vpn_y / d;

    // Rotation matrix about Z axis
    this->rotation_about_z(rz_matrix, sin_to_y, cos_to_y);

    // Rotate in Z so that the VPN is in the YZ plane
    std::vector<double> vpn, vpn_yz;
    vpn.push_back(vpn_x);
    vpn.push_back(vpn_y);
    vpn.push_back(vpn_z);
    vpn.push_back(1.0);
    rz_matrix.multiply_by_vector(vpn, vpn_yz);

    // Matrix that rotates a vector around X axis, aligning
    // the previously obtained vector (vpn_yz) with the Z axis
    // Note 1: vpn_yz[0] = 0.0
    // Note 2: the length of VPN is 1.0
    this->rotation_about_x(rx_matrix, sin(vpn_yz[1]), cos(vpn_yz[2]));

    // Multiply all matrices
    m = t_matrix * s_matrix * rz_matrix * rx_matrix;
}

/* ============================================================================================= */
void TMatrixBuilder::window_translation(TMatrix &m, const Coord<double> &window_center,
        const Coord<double> &window_rotation, const Coord<double> &window_translation)
/* ============================================================================================= */
{
    TMatrix t_matrix(4), s_matrix(4);
    TMatrix rx_matrix(4), rz_matrix(4);

    // Translate Window to the origin
    this->translation_matrix(t_matrix, window_center);

    // Alpha, beta and gamma are the angles between the VPN
    // and the X, Y and Z axis, respectively. A unit vector
    // representing the direction of the VPN is given by:
    // VPN = cos(alpha).i + cos(beta).j + cos(gamma).k
    // where alpha = window_rotation.x() and so on...
    // and i, j and k are the coordinate system basis vectors.
    double vpn_x = cos(window_rotation.x() * PI / 180.0);
    double vpn_y = cos(window_rotation.y() * PI / 180.0);
    double vpn_z = cos(window_rotation.z() * PI / 180.0);

    // Length of VPN in XY plane
    double d = sqrt(vpn_x * vpn_x + vpn_y * vpn_y);

    // Sine and cosine of angle to Y axis in XY plane
    double sin_to_y = vpn_x / d;
    double cos_to_y = vpn_y / d;

    // Rotation matrix about Z axis
    this->rotation_about_z(rz_matrix, sin_to_y, cos_to_y);

    // Rotate in Z so that the VPN is in the YZ plane
    std::vector<double> vpn, vpn_yz;
    vpn.push_back(vpn_x);
    vpn.push_back(vpn_y);
    vpn.push_back(vpn_z);
    vpn.push_back(1.0);
    rz_matrix.multiply_by_vector(vpn, vpn_yz);

    // Matrix that rotates a vector around X axis, aligning
    // the previously obtained vector (vpn_yz) with the Z axis
    // Note 1: vpn_yz[0] = 0.0
    // Note 2: the length of VPN is 1.0
    double sin_to_z = vpn_yz[1];
    double cos_to_z = vpn_yz[2];
    this->rotation_about_x(rx_matrix, sin_to_z, cos_to_z);

    // Window translation expected by the user
    TMatrix t_matrix_user(4);
    this->translation_matrix(t_matrix_user, window_translation);

    // Back transformations
    TMatrix minus_rx(4), minus_rz(4), minus_tmat(4);
    // Coord<double> minus_window_center(-window_center.x(), -window_center.y(), -window_center.z());
    this->rotation_about_x(minus_rx, -sin_to_z, -cos_to_z);
    this->rotation_about_z(minus_rz, -sin_to_y, -cos_to_y);
    this->translation_matrix(minus_tmat, -window_center);

    // Multiply all matrices
    m = t_matrix * s_matrix * rz_matrix * rx_matrix * t_matrix_user * minus_rx * minus_rz * minus_tmat;
}