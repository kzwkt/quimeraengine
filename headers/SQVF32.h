// [TERMS&CONDITIONS]

#ifndef __SQVF32__
#define __SQVF32__

#include <string>
#include "DataTypesDefinitions.h"
#include "SQFloat.h"

namespace Kinesis
{
namespace QuimeraEngine
{
namespace Tools
{
namespace DataTypes
{

/// <summary>
/// Helper class that offers functionality related to 4 x 32-bits floating point variables packs.<br>
/// This kind of packs are used in SIMD (SSE) operations.
/// </summary>
class QDllExport SQVF32
{

	// CONSTRUCTORS
	// ---------------
private:

	/// <summary>
	/// Default constructor (hidden).
	/// </summary>
	SQVF32();


	// METHODS
	// ---------------
public:
    // [TODO] Thund: Review this doc.
    /// <summary>
    /// Packs four input floating point variables into a 128-bits output variable.<br>
    /// The order of variables in the package must be read from left to right, this is:<br>
    ///  | Fourth | Third | Second | First | position<br>
    /// 128       96     64        32      0 bit<br>
    /// This is endianess-independent.
    /// </summary>
    /// <param name="fFirst">[IN] First value in the packet.</param>
    /// <param name="fSecond">[IN] Second value in the packet.</param>
    /// <param name="fThird">[IN] Third value in the packet.</param>
    /// <param name="fFourth">[IN] Fourth value in the packet.</param>
    /// <param name="pack">[OUT] The package containing four 32-bits floating point values.</param>
    inline static void Pack(const float_q &fFirst, const float_q &fSecond, const float_q &fThird, const float_q &fFourth, vf32_q &pack)
    {
        #define QE_4BYTES_SIZE 4 // We are working with a 32-bits floats pack

        #if QE_FLOAT_SIZE != QE_4BYTES_SIZE
            // Types are different so we need to use known-size types and then invoke
            // implicit casting when copying to auxiliar variables.
            f32_q f_1 = scast_q(fFirst, f32_q);
            f32_q f_2 = scast_q(fSecond, f32_q);
            f32_q f_3 = scast_q(fThird, f32_q);
            f32_q f_4 = scast_q(fFourth, f32_q);
        #else
            // Types are the same, no casting is needed so we only use references to maintain names used below
            const f32_q& f_1 = fFirst;
            const f32_q& f_2 = fSecond;
            const f32_q& f_3 = fThird;
            const f32_q& f_4 = fFourth;
        #endif

        pack.m128_f32[0] = f_1;
        pack.m128_f32[1] = f_2;
        pack.m128_f32[2] = f_3;
        pack.m128_f32[3] = f_4;
    }

    /// <summary>
    /// Unpacks into four output floating point variables stored in a 128-bits input variable.<br>
    /// The order of variables in the package is read from left to right, this is:<br>
    ///  | Fourth | Third | Second | First | position<br>
    /// 128       96     64        32      0 bit<br>
    /// This is endianess-independent.
    /// </summary>
    /// <param name="pack">[IN] The package containing four 32-bits floating point values.</param>
    /// <param name="fFirst">[OUT] First value in the packet.</param>
    /// <param name="fSecond">[OUT] Second value in the packet.</param>
    /// <param name="fThird">[OUT] Third value in the packet.</param>
    /// <param name="fFourth">[OUT] Fourth value in the packet.</param>
    inline static void Unpack(const vf32_q &pack, float_q &fFirst, float_q &fSecond, float_q &fThird, float_q &fFourth)
    {
        #define QE_4BYTES_SIZE 4 // We are working with a 32-bits floats pack

        #if QE_FLOAT_SIZE != QE_4BYTES_SIZE
            // Types are different so we need to use known-size types and then invoke
            // implicit casting when copying to auxiliar variables.
            f32_q f_1 = scast_q(SQFloat::_0, f32_q);
            f32_q f_2 = scast_q(SQFloat::_0, f32_q);
            f32_q f_3 = scast_q(SQFloat::_0, f32_q);
            f32_q f_4 = scast_q(SQFloat::_0, f32_q);
        #else
            // Types are the same, no casting is needed so we only use references to maintain names used below
            f32_q& f_1 = fFirst;
            f32_q& f_2 = fSecond;
            f32_q& f_3 = fThird;
            f32_q& f_4 = fFourth;
        #endif

        f_1 = pack.m128_f32[0];
        f_2 = pack.m128_f32[1];
        f_3 = pack.m128_f32[2];
        f_4 = pack.m128_f32[3];

        #if QE_FLOAT_SIZE != QE_4BYTES_SIZE
            fFirst  = scast_q(f_1, float_q);
            fSecond = scast_q(f_2, float_q);
            fThird  = scast_q(f_3, float_q);
            fFourth = scast_q(f_4, float_q);
        #endif
    }

    /// <summary>
    /// Represents the package content as a character string.
    /// </summary>
    /// <param name="inPack">[IN] A package containing four 32-bits floating point values.</param>
    /// <returns>
    /// The packet represented as a character string.<br>
    /// The format is: VF( First, Second, Third, Fourth ).
    /// </returns>
    static string_q ToString(const vf32_q &inPack);

};

} //namespace DataTypes
} //namespace Tools
} //namespace QuimeraEngine
} //namespace Kinesis

#endif // __SQVF32__
