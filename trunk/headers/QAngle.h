// [TERMS&CONDITIONS]

#ifndef __QANGLE__
#define __QANGLE__

#include <string>

#include "MathDefinitions.h"

namespace Kinesis
{
namespace QuimeraEngine
{
namespace Tools
{
namespace Math
{

/// <summary>
/// Helper class that offers functionality related to angles (radians and degrees).
/// Use constant angle values as far as you can in your code.
/// </summary>
class QDllExport QAngle
{
    // CONSTANTS
    // ---------------
public:

    /// <summary>
    /// 45 degrees angle.
    /// </summary>
    static const float_q _45;

    /// <summary>
    /// 90 degrees angle.
    /// </summary>
    static const float_q _90;

    /// <summary>
    /// 180 degrees angle.
    /// </summary>
    static const float_q _180;

    /// <summary>
    /// 15 degrees angle.
    /// </summary>
    static const float_q _15;

    /// <summary>
    /// 30 degrees angle.
    /// </summary>
    static const float_q _30;

    /// <summary>
    /// 60 degrees angle.
    /// </summary>
    static const float_q _60;

    /// <summary>
    /// 270 degrees angle.
    /// </summary>
    static const float_q _270;

    /// <summary>
    /// 360 degrees angle.
    /// </summary>
    static const float_q _360;

    /// <summary>
    /// Half Pi radians angle (\f$ \frac{\pi}{2} \f$).
    /// </summary>
    static const float_q _HalfPi;

    /// <summary>
    /// A quarter of Pi radians angle (\f$ \frac{\pi}{4} \f$).
    /// </summary>
    static const float_q _QuarterPi;

    /// <summary>
    /// Third part of Pi radians angle (\f$ \frac{\pi}{3} \f$).
    /// </summary>
    static const float_q _ThridPi;

    /// <summary>
    /// 2 Pi radians angle (\f$ 2\pi \f$).
    /// </summary>
    static const float_q _2Pi;

    /// <summary>
    /// Pi radians angle (\f$ \pi \f$).
    /// </summary>
    static const float_q _Pi;

    /// <summary>
    /// 3 halfs of Pi radians angle (\f$ \frac{3\pi}{2} \f$).
    /// </summary>
    static const float_q _3HalfsPi;

    /// <summary>
    /// Defines how many degrees are equivalent to 1 radian, and how much accurate is that value.
    /// </summary>
    static const float_q DegreesPerRadian;

    /// <summary>
    /// Defines how many radians are equivalent to 1 degree, and how much accurate is that value.
    /// </summary>
    static const float_q RadiansPerDegree;


	// CONSTRUCTORS
	// ---------------
private:

	/// <summary>
	/// Default constructor (hidden).
	/// </summary>
	QAngle();


	// METHODS
	// ---------------
public:

    /// <summary>
    /// Computes the conversion from a value expressed in degrees to its equivalent in radians.
    /// </summary>
    /// <param name="fDegrees">[IN] The angle measured in degrees.</param>
    /// <param name="fRadians">[OUT] The same angle converted to radians.</param>
    /// <returns>
    /// A reference to the output parameter. This let this method to be used has parameter in another function.
    /// </returns>
    inline static float_q& DegreesToRadians(const float_q &fDegrees, float_q &fRadians)
    {
        fRadians = fDegrees * QAngle::RadiansPerDegree;
        return fRadians;
    }

    /// <summary>
    /// Computes the conversion from a value expressed in radians to its equivalent in degrees.
    /// </summary>
    /// <param name="fRadians">[IN] The angle measured in radians.</param>
    /// <param name="fDegrees">[OUT] The same angle converted to degrees.</param>
    /// <returns>
    /// A reference to the output parameter. This let this method to be used has parameter in another function.
    /// </returns>
    inline static float_q& RadiansToDegrees(const float_q &fRadians, float_q &fDegrees)
    {
        fDegrees = fRadians * QAngle::DegreesPerRadian;
        return fDegrees;
    }

    /// <summary>
    /// Truncates an angle which describes more than one revolution. If the angle value is greater than 360º, then
    /// it will be replaced by the maximum, this means, 360º.
    /// </summary>
    /// <param name="fAngle">[IN] The original angle value, in degrees.</param>
    /// <returns>
    /// The truncated angle value, in degrees.
    /// </returns>
    inline static float_q TruncateDegrees(const float_q &fAngle)
    {
        if( QFloat::IsPositive(fAngle) )
            // Positive angles
            return QFloat::IsGreaterThan(fAngle, QAngle::_360) ? QAngle::_360 : fAngle;
        else
            // Negative angles
            return QFloat::IsLowerThan(fAngle, -QAngle::_360) ? -QAngle::_360 : fAngle;
    }

    /// <summary>
    /// Truncates an angle which describes more than one revolution. If the angle value is greater than 2 Pi, then
    /// it will be replaced by the maximum, this means, 2 Pi.
    /// </summary>
    /// <param name="fAngle">[IN] The original angle value, in radians.</param>
    /// <returns>
    /// The truncated angle value, in radians.
    /// </returns>
    inline static float_q TruncateRadians(const float_q &fAngle)
    {
        if( QFloat::IsPositive(fAngle) ) 
            // Positive angles
            return QFloat::IsGreaterThan(fAngle, QAngle::_2Pi) ? QAngle::_2Pi : fAngle;
        else
            // Negative angles
            return QFloat::IsLowerThan(fAngle, -QAngle::_2Pi) ? -QAngle::_2Pi : fAngle;
    }

    /// <summary>
    /// Counts how many revolutions are represented by an angle, including fractions.
    /// </summary>
    /// <param name="fAngle">[IN] The angle value.</param>
    /// <returns>
    /// The number of revolutions (partial and complete).
    /// </returns>
    inline static float_q CountRevolutions(const float_q &fAngle)
    {
        const float_q COMPLETE_REVOLUTION = 
            #if QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_RADIANS
                QAngle::_2Pi;
            #elif QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_DEGREES
                QAngle::_360;
            #endif

        return fAngle / COMPLETE_REVOLUTION;
    }

    /// <summary>
    /// Counts how many revolutions are represented by an angle, ignoring fractions.
    /// </summary>
    /// <param name="fAngle">[IN] The angle value.</param>
    /// <returns>
    /// The number of revolutions (only complete).
    /// </returns>
    inline static float_q CountCompleteRevolutions(const float_q &fAngle)
    {
        const float_q COMPLETE_REVOLUTION = 
            #if QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_RADIANS
                QAngle::_2Pi;
            #elif QE_CONFIG_ANGLENOTATION_DEFAULT == QE_CONFIG_ANGLENOTATION_DEGREES
                QAngle::_360;
            #endif

        float_q outValue = fAngle / COMPLETE_REVOLUTION;
        QFloat::Truncate(outValue);

        return outValue;
    }
};

} //namespace Math
} //namespace Tools
} //namespace QuimeraEngine
} //namespace Kinesis

#endif // __QANGLE__
