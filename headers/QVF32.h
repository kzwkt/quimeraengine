// [TERMS&CONDITIONS]

#ifndef __QVF32__
#define __QVF32__

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
/// Helper class that offers functionality related to 4 x 32-bits floating point variables packs.
/// This kind of packs are used in SIMD (SSE) operations.
/// </summary>
class QDllExport QVF32
{

	// CONSTRUCTORS
	// ---------------
private:

	/// <summary>
	/// Default constructor (hidden).
	/// </summary>
	QVF32();


	// METHODS
	// ---------------
public:
    // [TODO] Thund: Review this doc.
    /// <summary>
    /// Packs four input floating point variables into a 128-bits output variable. The order of variables
    /// in the package must be read from left to right, this is:
    ///  | First | Second | Third | Fourth | position
    /// 128     96       64      32        0 bit
    /// This is endianess-independent.
    /// </summary>
    /// <param name="fFirst">[IN] First value in the packet.</param>
    /// <param name="fSecond">[IN] Second value in the packet.</param>
    /// <param name="fThird">[IN] Third value in the packet.</param>
    /// <param name="fFourth">[IN] Fourth value in the packet.</param>
    /// <param name="outPack">[OUT] The package containing four 32-bits floating point values.</param>
    inline static void Pack(const float_q &fFirst, const float_q &fSecond, const float_q &fThird, const float_q &fFourth, vf32_q &outPack)
    {
        const int FIRST_POS  = 1;
        const int SECOND_POS = 2;
        const int THIRD_POS  = 3;
        const int FOURTH_POS = 4;

        #define QE_4BYTES_SIZE 4 // We are working with a 32-bits floats pack

        #if QE_FLOAT_SIZE != QE_4BYTES_SIZE
            // Types are different so we need to use known-size types and then invoke
            // implicit casting when copying to auxiliar variables.
            f32_q f_1 = static_cast<f32_q>(fFirst);
            f32_q f_2 = static_cast<f32_q>(fSecond); 
            f32_q f_3 = static_cast<f32_q>(fThird); 
            f32_q f_4 = static_cast<f32_q>(fFourth);
        #else
            // Types are the same, no casting is needed so we only use references to maintain names used below
            const f32_q& f_1 = fFirst;
            const f32_q& f_2 = fSecond;
            const f32_q& f_3 = fThird;
            const f32_q& f_4 = fFourth;
        #endif

        memcpy((&outPack) + FIRST_POS  * QE_4BYTES_SIZE, &f_1, QE_4BYTES_SIZE);
        memcpy((&outPack) + SECOND_POS * QE_4BYTES_SIZE, &f_2, QE_4BYTES_SIZE);
        memcpy((&outPack) + THIRD_POS  * QE_4BYTES_SIZE, &f_3, QE_4BYTES_SIZE);
        memcpy((&outPack) + FOURTH_POS * QE_4BYTES_SIZE, &f_4, QE_4BYTES_SIZE);
    }

    /// <summary>
    /// Unpacks into four output floating point variables stored in a 128-bits input variable. The order of variables
    /// in the package is read from left to right, this is:
    ///  | First | Second | Third | Fourth | position
    /// 128     96       64      32        0 bit
    /// This is endianess-independent.
    /// </summary>
    /// <param name="inPack">[IN] The package containing four 32-bits floating point values.</param>
    /// <param name="fFirst">[OUT] First value in the packet.</param>
    /// <param name="fSecond">[OUT] Second value in the packet.</param>
    /// <param name="fThird">[OUT] Third value in the packet.</param>
    /// <param name="fFourth">[OUT] Fourth value in the packet.</param>
    inline static void Unpack(const vf32_q &inPack, float_q &fFirst, float_q &fSecond, float_q &fThird, float_q &fFourth)
    {
        // [TODO] Thund: ¿Mejorable con union?
        const int FIRST_POS  = 1;
        const int SECOND_POS = 2;
        const int THIRD_POS  = 3;
        const int FOURTH_POS = 4;

        #define QE_4BYTES_SIZE 4 // We are working with a 32-bits floats pack

        #if QE_FLOAT_SIZE != QE_4BYTES_SIZE
            // Types are different so we need to use known-size types and then invoke
            // implicit casting when copying to auxiliar variables.
            f32_q f_1 = static_cast<f32_q>(SQFloat::_0);
            f32_q f_2 = static_cast<f32_q>(SQFloat::_0);
            f32_q f_3 = static_cast<f32_q>(SQFloat::_0);
            f32_q f_4 = static_cast<f32_q>(SQFloat::_0);
        #else
            // Types are the same, no casting is needed so we only use references to maintain names used below
            f32_q& f_1 = fFirst;
            f32_q& f_2 = fSecond;
            f32_q& f_3 = fThird;
            f32_q& f_4 = fFourth;
        #endif

        memcpy(&f_1, (&inPack) + FIRST_POS  * QE_4BYTES_SIZE, QE_4BYTES_SIZE);
        memcpy(&f_2, (&inPack) + SECOND_POS * QE_4BYTES_SIZE, QE_4BYTES_SIZE);
        memcpy(&f_3, (&inPack) + THIRD_POS  * QE_4BYTES_SIZE, QE_4BYTES_SIZE);
        memcpy(&f_4, (&inPack) + FOURTH_POS * QE_4BYTES_SIZE, QE_4BYTES_SIZE);

        #if QE_FLOAT_SIZE != QE_4BYTES_SIZE
            fFirst  = static_cast<float_q>(f_1);
            fSecond = static_cast<float_q>(f_2);
            fThird  = static_cast<float_q>(f_3);
            fFourth = static_cast<float_q>(f_4);
        #endif
    }

    /// <summary>
    /// Represents the package content as a character string.
    /// </summary>
    /// <param name="inPack">[IN] A package containing four 32-bits floating point values.</param>
    /// <returns>
    /// The packet represented as a character string. The format is: VF( First, Second, Third, Fourth ).
    /// </returns>
    static string_q ToString(const vf32_q &inPack);

};

} //namespace DataTypes
} //namespace Tools
} //namespace QuimeraEngine
} //namespace Kinesis

#endif // __QVF32__
