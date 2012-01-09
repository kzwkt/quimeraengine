// [TERMS&CONDITIONS]

#ifndef __QBASEHEXAHEDRON__
#define __QBASEHEXAHEDRON__

#include "SQFloat.h"
#include "SQVF32.h"
#include "QConvertible.h"

using Kinesis::QuimeraEngine::Core::QConvertible;
using namespace Kinesis::QuimeraEngine::Tools::DataTypes;

namespace Kinesis
{
namespace QuimeraEngine
{
namespace Tools
{
namespace Math
{

/// <summary>
/// Class which represents a hexahedron in the space. The hexahedron is defined by its eight vertices.
/// It's supossed that ABCD defines a face of the hexahedron (eventually the top face) and
/// EFGH defines the opposite face (eventually the bottom one).
/// </summary>
template <class VectorType>
class QDllExport QBaseHexahedron : public QConvertible
{

    // CONSTRUCTORS
    // ---------------
public:

    /// <summary>
    /// Default constructor.
    /// </summary>
    inline QBaseHexahedron() : A(SQFloat::_0), B(SQFloat::_0), C(SQFloat::_0), D(SQFloat::_0),
                               E(SQFloat::_0), F(SQFloat::_0), G(SQFloat::_0), H(SQFloat::_0) 
    {
    }

    /// <summary>
    /// Constructor from eight vectors, one for each vertex.
    /// </summary>
    /// <param name="vA">[IN] Vector to define vertex A.</param>
    /// <param name="vB">[IN] Vector to define vertex B.</param>
    /// <param name="vC">[IN] Vector to define vertex C.</param>
    /// <param name="vD">[IN] Vector to define vertex D.</param>
    /// <param name="vE">[IN] Vector to define vertex E.</param>
    /// <param name="vF">[IN] Vector to define vertex F.</param>
    /// <param name="vG">[IN] Vector to define vertex G.</param>
    /// <param name="vH">[IN] Vector to define vertex H.</param>
    inline QBaseHexahedron(const VectorType &vA, const VectorType &vB, const VectorType &vC, const VectorType &vD,
                           const VectorType &vE, const VectorType &vF, const VectorType &vG, const VectorType &vH) :
							    A(vA), B(vB), C(vC), D(vD), E(vE), F(vF), G(vG), H(vH)
    {
    }

    /// <summary>
    /// Constructor from two vectors which defines two opposite vertices, with no common faces between them
    /// (the ends of any inner diagonals).
    /// </summary>
    /// <param name="vA">[IN] Vector which defines one vertex of a inner diagonal (it will be used to initialize A).</param>
    /// <param name="vG">[IN] Vector which defines the other vertex of the inner diagonal (it will be used to initialize G).</param>
    inline QBaseHexahedron(const VectorType &vA, const VectorType &vG)
    {
        A = B = D = E = vA;
        C = F = G = H = vG;

        B.z = vG.z;
        C.y = vA.y;
        D.x = vG.x;
        E.y = vG.y;
        F.z = vA.z;
        H.x = vA.x;
    }

    /// <summary>
    /// Constructor from a vector which defines the gravity center of the box and three floating
    /// points values which defines its height (Y), width (X) and depth (Z).
    /// It's supossed that all edges are parallel to one of the axis.
    /// </summary>
    /// <param name="vCenter">[IN] Center point of the box.</param>
    /// <param name="fLengthX">[IN] Length of an edge parallel to X axis (width).</param>
    /// <param name="fLengthY">[IN] Length of an edge parallel to Y axis (height).</param>
    /// <param name="fLengthZ">[IN] Length of an edge parallel to Z axis (depth).</param>
    inline QBaseHexahedron(const VectorType &vCenter, const float_q &fLengthX, const float_q &fLengthY, const float_q &fLengthZ)
    {
        // Ensures that all vectors/points are in same coordinates format.
        A = vCenter;

        A.x -= fLengthX*SQFloat::_0_5;
        A.y += fLengthY*SQFloat::_0_5;
        A.z += fLengthZ*SQFloat::_0_5;

        B = A;
        B.z -= fLengthZ;

        C = B;
        C.x += fLengthX;

        D = C;
        D.z = A.z;

        E = A;
        E.y -= fLengthY;

        F = D;
        F.y = E.y;

        G = C;
        G.y = E.y;

        H = B;
        H.y = E.y;
    }

    // METHODS
    // ---------------
public:

    /// <summary>
    /// Equality operator. Compares two hexahedrons.
    /// </summary>
    /// <param name="hexahedron">[IN] Hexahedron with which to compare.</param>
    /// <returns>
    /// True if hexahedrons are the same, false otherwise.
    /// </returns>
    inline bool operator==(const QBaseHexahedron<VectorType> &hexahedron) const
    {
        return ( this->A == hexahedron.A && this->B == hexahedron.B && this->C == hexahedron.C && this->D == hexahedron.D &&
                 this->E == hexahedron.E && this->F == hexahedron.F && this->G == hexahedron.G && this->H == hexahedron.H);
    }

    /// <summary>
    /// Inequality operator. Compares two hexahedrons.
    /// </summary>
    /// <param name="hexahedron">[IN] Hexahedron with which to compare.</param>
    /// <returns>
    /// True if hexahedrons are not the same, false otherwise.
    /// </returns>
    inline bool operator!=(const QBaseHexahedron<VectorType> &hexahedron) const
    {
        return !(*this == hexahedron);
    }

    // ATTRIBUTES
    // ---------------
public:

    /// <summary>
    /// Vector which represents a vextex of the box.
    /// </summary>
    VectorType A;

    /// <summary>
    /// Vector which represents a vextex of the box.
    /// </summary>
    VectorType B;

    /// <summary>
    /// Vector which represents a vextex of the box.
    /// </summary>
    VectorType C;

    /// <summary>
    /// Vector which represents a vextex of the box.
    /// </summary>
    VectorType D;

    /// <summary>
    /// Vector which represents a vextex of the box.
    /// </summary>
    VectorType E;

    /// <summary>
    /// Vector which represents a vextex of the box.
    /// </summary>
    VectorType F;

    /// <summary>
    /// Vector which represents a vextex of the box.
    /// </summary>
    VectorType G;

    /// <summary>
    /// Vector which represents a vextex of the box.
    /// </summary>
    VectorType H;

};

} //namespace Math
} //namespace Tools
} //namespace QuimeraEngine
} //namespace Kinesis

#endif // __QBASEHEXAHEDRON__
