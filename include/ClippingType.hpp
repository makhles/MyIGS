/**
 * ClippingType.hpp
 * @author: Leonardo Vailatti
 *          Makhles R. Lange
 * 
 * @brief Clips shapes expressed in normalized coordinates to a
 * window whose coordinates are given by the NCS.
 */

#ifndef CLIPPING_TYPE_HPP
#define CLIPPING_TYPE_HPP

enum class LineClipping : int
{
    CS,  //< Cohen-Sutherland
    LB,  //< Liang-Barsky
    NLN  //< Nicholl-Lee-Nicholl
};

enum class PolygonClipping : int
{
    SH,  //< Sutherland-Hodgeman
    WA   //< Weiler-Atherton
};

#endif  // CLIPPING_TYPE_HPP