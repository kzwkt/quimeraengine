// [TERMS&CONDITIONS]

#ifndef __QRAY__
#define __QRAY__

#include "QBaseRay.h"
#include "EQIntersections.h"

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
/// Represents a ray in the space, which consists of a point, or position, and a direction. The direction
/// symbolizes a line with only one end (which coincides with the point) and that extends to the infinite.
/// </summary>
template<class VectorTypePoint, class VectorTypeDirection>
class QDllExport QRay : public QBaseRay<VectorTypePoint, VectorTypeDirection>
{
    // CONSTANTS
    // ---------------
public:

    /// <summary>
	/// A ray set at the coordinate origin and whose direction vector is null.
	/// </summary>
    static const QRay RayZero;


	// CONSTRUCTORS
	// ---------------
public:

	/// <summary>
	/// Default constructor.
	/// </summary>
	inline QRay()
    {
    }

    /// <summary>
    /// Constructor that receives a ray.
    /// </summary>
    /// <param name="baseRay">[IN] An existing ray.</param>
    inline QRay(const QBaseRay<VectorTypePoint, VectorTypeDirection>& baseRay) : QBaseRay<VectorTypePoint, VectorTypeDirection>(baseRay)
    {
    }

    /// <summary>
    /// Constructor that receives the ray's position and direction.
    /// </summary>
    /// <param name="vPoint">[IN] Ray's position.</param>
    /// <param name="vDirection">[IN] Ray's direction.</param>
    inline QRay(const VectorTypePoint &vPoint, const VectorTypeDirection &vDirection) : QBaseRay<VectorTypePoint, VectorTypeDirection>(vPoint, vDirection)
    {
    }


	// METHODS
	// ---------------
public:

    /// <summary>
    /// Assign operator that receives another ray.
    /// </summary>
    /// <param name="ray">[IN] An existing ray.</param>
    /// <returns>
    /// A reference to this ray, after assignation.
    /// </returns>
    inline QRay& operator=(const QBaseRay<VectorTypePoint, VectorTypeDirection>& ray)
    {
        QBaseRay<VectorTypePoint, VectorTypeDirection>::operator=(ray);
        return *this;
    }

    /// <summary>
    /// Converts the ray's direction in its opposite.
    /// </summary>
    inline void Reverse()
    {
        this->Direction *= -QFloat::_1;
    }

    /// <summary>
    /// Obtains a reverted copy of the ray. Converts copy's direction is its opposite.
    /// </summary>
    /// <param name="vRevertedRay">[OUT] A reverted copy of the ray.</param>
    inline void Reverse(QBaseRay<VectorTypePoint, VectorTypeDirection>& vRevertedRay) const
    {
        vRevertedRay = *this;
        reinterpret_cast<QRay<VectorTypePoint, VectorTypeDirection>*>(&vRevertedRay)->Reverse();
    }

    /// <summary>
    /// Normalizes the ray, converting its direction in a unit vector.
    /// </summary>
    inline void Normalize()
    {
        this->Direction.Normalize();
    }

    /// <summary>
    /// Obtains a normalized copy of the ray. Normalizes the copy, converting its direction in a unit vector.
    /// </summary>
    /// <param name="vNormalizedRay">[OUT] A normalized copy of the ray.</param>
    inline void Normalize(QBaseRay<VectorTypePoint, VectorTypeDirection>& vNormalizedRay) const
    {
        vNormalizedRay = *this;
        reinterpret_cast<QRay<VectorTypePoint, VectorTypeDirection>*>(&vNormalizedRay)->Normalize();
    }

    /// <summary>
    /// Calculates any point that belongs to the ray, based on the distance to the ray's position.
    /// </summary>
    /// <param name="fDistance">[IN] Distance from the point which is to be found to the ray's position.</param>
    /// <param name="vRayPoint">[OUT] A point of the ray.</param>
    inline void GetPoint(const float_q &fDistance, VectorTypePoint& vRayPoint) const
    {
        // It's assumed that the ray's direction vector is normalized
        vRayPoint = this->Direction;
        vRayPoint *= fDistance;
        vRayPoint += this->Point;
    }

    /// <summary>
	/// Converts ray into a string representation with the following format:
	/// "R:P(VectorTypePoint::ToString),D(VectorTypeDirection::ToString)".
    /// </summary>
    /// <returns>
    /// The string representation with the format specified.
    /// </returns>
    string_q ToString() const
    {
        return QE_L("R:P(") + this->Point.ToString() + QE_L("),D(") + this->Direction.ToString() + QE_L(")");
    }

};

//##################=======================================================##################
//##################			 ____________________________			   ##################
//##################			|							 |			   ##################
//##################		    |    CONSTANTS DEFINITIONS	 |			   ##################
//##################		   /|							 |\			   ##################
//##################			 \/\/\/\/\/\/\/\/\/\/\/\/\/\/			   ##################
//##################													   ##################
//##################=======================================================##################

template <class VectorTypePoint, class VectorTypeDirection>
const QRay<VectorTypePoint, VectorTypeDirection> QRay<VectorTypePoint, VectorTypeDirection>::RayZero(VectorTypePoint::ZeroVector, VectorTypeDirection::ZeroVector);

} //namespace Math
} //namespace Tools
} //namespace QuimeraEngine
} //namespace Kinesis

#endif // __QRAY__
// [TERMS&CONDITIONS]
