// [TERMS&CONDITIONS]

#ifndef __QVF32__
#define __QVF32__

#include <string>
#include "DataTypesDefinitions.h"
#include "QFloat.h"

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
        const int F32SIZE = sizeof(f32_q);
        const int FLOATQSIZE = sizeof(float_q);

        #if F32SIZE != FLOATQSIZE
            // Types are different so we need to use known-size types and then invoke
            // implicit casting when copying to auxiliar variables.
            f32_q f_1 = fFirst;
            f32_q f_2 = fSecond; 
            f32_q f_3 = fThird; 
            f32_q f_4 = fFourth;
        #else
            // Types are the same, no casting is needed so we only use references to maintain names used below
            const f32_q& f_1 = fFirst;
            const f32_q& f_2 = fSecond;
            const f32_q& f_3 = fThird;
            const f32_q& f_4 = fFourth;
        #endif

        memcpy((&outPack) + FIRST_POS  * F32SIZE, &f_1, F32SIZE);
        memcpy((&outPack) + SECOND_POS * F32SIZE, &f_2, F32SIZE);
        memcpy((&outPack) + THIRD_POS  * F32SIZE, &f_3, F32SIZE);
        memcpy((&outPack) + FOURTH_POS * F32SIZE, &f_4, F32SIZE);
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
        const int FIRST_POS  = 1;
        const int SECOND_POS = 2;
        const int THIRD_POS  = 3;
        const int FOURTH_POS = 4;
        const int F32SIZE = sizeof(f32_q);
        const int FLOATQSIZE = sizeof(float_q);

        #if F32SIZE != FLOATQSIZE
            // Types are different so we need to use known-size types and then invoke
            // implicit casting when copying to auxiliar variables.
            f32_q f_1 = QFloat::_0;
            f32_q f_2 = QFloat::_0;
            f32_q f_3 = QFloat::_0;
            f32_q f_4 = QFloat::_0;
        #else
            // Types are the same, no casting is needed so we only use references to maintain names used below
            f32_q& f_1 = fFirst;
            f32_q& f_2 = fSecond;
            f32_q& f_3 = fThird;
            f32_q& f_4 = fFourth;
        #endif

        memcpy(&f_1, (&inPack) + FIRST_POS  * F32SIZE, F32SIZE);
        memcpy(&f_2, (&inPack) + SECOND_POS * F32SIZE, F32SIZE);
        memcpy(&f_3, (&inPack) + THIRD_POS  * F32SIZE, F32SIZE);
        memcpy(&f_4, (&inPack) + FOURTH_POS * F32SIZE, F32SIZE);

        #if F32SIZE != FLOATQSIZE
            fFirst  = f_1;
            fSecond = f_2;
            fThird  = f_3;
            fFourth = f_4;
        #endif
    }

    /// <summary>
    /// Represents the package content as a character string.
    /// </summary>
    /// <param name="inPack">[IN] A package containing four 32-bits floating point values.</param>
    /// <returns>
    /// The packet represented as a character string. The format is: VF( First, Second, Third, Fourth ).
    /// </returns>
    static std::string ToString(const vf32_q &inPack);

};

} //namespace DataTypes
} //namespace Tools
} //namespace QuimeraEngine
} //namespace Kinesis

#endif // __QVF32__
