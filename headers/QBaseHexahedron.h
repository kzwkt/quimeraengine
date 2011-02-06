// [TERMS&CONDITIONS]

#ifndef __QBASEHEXAHEDRON__
#define __QBASEHEXAHEDRON__

#include "QFloat.h"
#include "QVF32.h"

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
/// Class which represents a box in the space. The box is defined by its eight vertices.
/// It's supossed that ABCD defines a face of the box (eventually the top face) and 
/// EFGH defines the opposite face (eventually the bottom one).
/// </summary>
template <class VectorType> 
class QDllExport QBaseHexahedron
{

    // CONSTRUCTORS
    // ---------------
public:

    /// <summary>
    /// Default constructor.
    /// </summary>
    inline QBaseHexahedron () : A(QFloat::_0), B(QFloat::_0), C(QFloat::_0), D(QFloat::_0), 
								E(QFloat::_0), F(QFloat::_0), G(QFloat::_0), H(QFloat::_0) { }

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
    inline QBaseHexahedron (const VectorType &vA, const VectorType &vB, const VectorType &vC, const VectorType &vD,
							const VectorType &vE, const VectorType &vF, const VectorType &vG, const VectorType &vH) :
							A(vA), B(vB), C(vC), D(vD), E(vE), F(vF), G(vG), H(vH) { }

    /// <summary>
    /// Constructor from two vectors which defines two opposite vertices, with no common faces between them 
    /// (the ends of any inner diagonals).
    /// </summary>
    /// <param name="vA">[IN] Vector which defines one vertex of a inner diagonal (We'll call it A).</param>
    /// <param name="vG">[IN] Vector which defines the other vertex of the inner diagonal (We'll call it G).</param>
    inline QBaseHexahedron (const VectorType &vA, const VectorType &vG)
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
    /// <param name="fLenX">[IN] Length of an edge parallel to X axis (width).</param>
    /// <param name="fLenY">[IN] Length of an edge parallel to Y axis (height).</param>
    /// <param name="fLenZ">[IN] Length of an edge parallel to Z axis (depth).</param>
    inline QBaseHexahedron (const VectorType &vCenter, float_q &fLenX, float_q &fLenY, float_q &fLenZ)
    {
        // Ensures that all vectors/points are in same coordinates format.
        A = vCenter;
       
        A.x -= fLenX*QFloat::_0_5;
        A.y += fLenY*QFloat::_0_5;
        A.z += fLenZ*QFloat::_0_5;

        B = A;
        B.z -= fLenZ;

        C = B;
        C.x += fLenX;

        D = C;
        D.z = A.z;

        E = A;
        E.y -= fLenY;

        F = D;
        F.y = E.y;

        G = C;
        G.y = E.y;

        H = B;
        H.y = E.y;
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
