//-------------------------------------------------------------------------------//
//                         QUIMERA ENGINE : LICENSE                              //
//-------------------------------------------------------------------------------//
// This file is part of Quimera Engine.                                          //
// Quimera Engine is free software: you can redistribute it and/or modify        //
// it under the terms of the Lesser GNU General Public License as published by   //
// the Free Software Foundation, either version 3 of the License, or             //
// (at your option) any later version.                                           //
//                                                                               //
// Quimera Engine is distributed in the hope that it will be useful,             //
// but WITHOUT ANY WARRANTY; without even the implied warranty of                //
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the                  //
// Lesser GNU General Public License for more details.                           //
//                                                                               //
// You should have received a copy of the Lesser GNU General Public License      //
// along with Quimera Engine. If not, see <http://www.gnu.org/licenses/>.        //
//                                                                               //
// This license doesn't force you to put any kind of banner or logo telling      //
// that you are using Quimera Engine in your project but we would appreciate     //
// if you do so or, at least, if you let us know about that.                     //
//                                                                               //
// Enjoy!                                                                        //
//                                                                               //
// Kinesis Team                                                                  //
//-------------------------------------------------------------------------------//

#include <boost/test/auto_unit_test.hpp>
#include <boost/test/unit_test_log.hpp>
using namespace boost::unit_test;

#include "../../testsystem/TestingExternalDefinitions.h"

#include "AllocationOperators.h"
#include "QStackAllocator.h"
#include "QStackAllocatorWhiteBox.h"
#include "QAlignment.h"
#include "QAlignmentMocked.h"
#include "QAssertException.h"

using Kinesis::QuimeraEngine::Common::DataTypes::u8_q;
using Kinesis::QuimeraEngine::Common::DataTypes::pointer_uint_q;
using Kinesis::QuimeraEngine::Common::Memory::QStackAllocator;
using Kinesis::QuimeraEngine::Common::Memory::Test::QStackAllocatorWhiteBox;
using Kinesis::QuimeraEngine::Common::Memory::QAlignment;
using Kinesis::QuimeraEngine::Common::Memory::Test::QAlignmentMocked;


QTEST_SUITE_BEGIN( QStackAllocator_TestSuite )

#if QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that the assertion fails when the passed size for the preallocated block is zero.
/// </summary>
QTEST_CASE ( Constructor1_AssertionFailsWhenPreallocationSizeIsZero_Test )
{
    // [Preparation]

    const bool             ASSERTION_FAILED                 = true;
    bool                   bAssertionFailed                 = false;


	// [Execution]

    try
    {
        QStackAllocator stackAllocator(0);
    }
    catch(const QAssertException&)
    {
        bAssertionFailed = true;
    }

 
    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

#endif // QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that the creation of the stack allocator, creating the preallocated memory block
/// and setting the internal state of the stack as "empty", is correctly made.
/// </summary>
QTEST_CASE ( Constructor1_ChecksThatPreallocationIsCorrectlyMade_Test )
{
    // [Preparation]

    const bool                     EXPECTED_VALUE                 = true;

    const pointer_uint_q           VALID_PREALLOCATION_SIZE       = 512;
    
    pointer_uint_q                 uPreallocationSize             = 0;
    pointer_uint_q                 uAllocatedBytes                = 0;
    void*                          pStackBase                     = null_q;
    void*                          pStackTop                      = null_q;

    bool                           bNonNullStackBase              = false;
    bool                           bTopEqualsBase                 = false;
    bool                           bPreallocationSizeIsNotZero    = false;
    bool                           bAllocatedBytesAreZero         = false;


	// [Execution]

    QStackAllocatorWhiteBox        stackAllocatorWhiteBox(VALID_PREALLOCATION_SIZE);
    QStackAllocatorWhiteBox::QMark markToTop                      = stackAllocatorWhiteBox.GetMark();

    pStackBase                                                    = stackAllocatorWhiteBox.GetpBase();
    pStackTop                                                     = markToTop.GetMemoryAddress();
    uPreallocationSize                                            = stackAllocatorWhiteBox.GetSize();


    // [Verification]

    // Allocation has been made correctly when:
    //
    //     Stack Base is not null now
    // AND Stack top points to the same direction that Stack Base (because the stack is empty for now)
    // AND the size of the preallocated memory block is greater than zero now
    // AND the amount of allocated bytes for memory blocks is zero (because the stack is empty for now).

    if (null_q != pStackBase)
        bNonNullStackBase           = true;

    if (pStackBase == pStackTop)
        bTopEqualsBase              = true;

    if (uPreallocationSize > 0)
        bPreallocationSizeIsNotZero = true;

    if (0 == uAllocatedBytes)
        bAllocatedBytesAreZero      = true;

    BOOST_CHECK_EQUAL(bNonNullStackBase,           EXPECTED_VALUE);
    BOOST_CHECK_EQUAL(bTopEqualsBase,              EXPECTED_VALUE);
    BOOST_CHECK_EQUAL(bPreallocationSizeIsNotZero, EXPECTED_VALUE);
    BOOST_CHECK_EQUAL(bAllocatedBytesAreZero,      EXPECTED_VALUE);
}

#if QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that the assertion fails when the passed size for the preallocated block is zero.
/// </summary>
QTEST_CASE ( Constructor2_AssertionFailsWhenPreallocationSizeIsZero_Test )
{
    // [Preparation]

    const bool             ASSERTION_FAILED                 = true;
    bool                   bAssertionFailed                 = false;

    const pointer_uint_q   VALID_ALIGNMENT_VALUE            = 4;


	// [Execution]

    try
    {
        QStackAllocator stackAllocator( 0, QAlignment(VALID_ALIGNMENT_VALUE) );
    }
    catch(const QAssertException&)
    {
        bAssertionFailed = true;
    }

 
    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

#endif // QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that the creation of the stack allocator, creating the preallocated memory block and setting the internal state
/// of the stack as "empty", is correctly made.
/// </summary>
QTEST_CASE ( Constructor2_PreallocationIsCorrectlyMade_Test )
{
    // [Preparation]

    const bool                     EXPECTED_VALUE                         = true;

    const pointer_uint_q           VALID_PREALLOCATION_SIZE               = 128;
    const pointer_uint_q           VALID_PREALLOCATION_ALIGNMENT_VALUE01  = 2;
    const pointer_uint_q           VALID_PREALLOCATION_ALIGNMENT_VALUE02  = 4;
    const pointer_uint_q           VALID_PREALLOCATION_ALIGNMENT_VALUE03  = 8;
    const pointer_uint_q           VALID_PREALLOCATION_ALIGNMENT_VALUE04  = 16;

    pointer_uint_q                 uPreallocationSize01                   = 0;
    pointer_uint_q                 uPreallocationSize02                   = 0;
    pointer_uint_q                 uPreallocationSize03                   = 0;
    pointer_uint_q                 uPreallocationSize04                   = 0;
    pointer_uint_q                 uAllocatedBytes01                      = 0;
    pointer_uint_q                 uAllocatedBytes02                      = 0;
    pointer_uint_q                 uAllocatedBytes03                      = 0;
    pointer_uint_q                 uAllocatedBytes04                      = 0;

    void*                          pStackBase01                           = null_q;
    void*                          pStackBase02                           = null_q;
    void*                          pStackBase03                           = null_q;
    void*                          pStackBase04                           = null_q;
    void*                          pStackTop01                            = null_q;
    void*                          pStackTop02                            = null_q;
    void*                          pStackTop03                            = null_q;
    void*                          pStackTop04                            = null_q;

    bool                           bNonNullStackBaseInAll                 = false;
    bool                           bTopEqualsBaseInAll                    = false;
    bool                           bPreallocationSizeIsNotZeroInAll       = false;
    bool                           bAllocatedBytesAreZeroInAll            = false;


	// [Execution]

    QStackAllocatorWhiteBox        stackAllocatorWhiteBox01( VALID_PREALLOCATION_SIZE, QAlignment(VALID_PREALLOCATION_ALIGNMENT_VALUE01) );
    QStackAllocatorWhiteBox::QMark markToTop01                            = stackAllocatorWhiteBox01.GetMark();
    pStackBase01                                                          = stackAllocatorWhiteBox01.GetpBase();
    pStackTop01                                                           = markToTop01.GetMemoryAddress();
    uPreallocationSize01                                                  = stackAllocatorWhiteBox01.GetSize();

    QStackAllocatorWhiteBox        stackAllocatorWhiteBox02( VALID_PREALLOCATION_SIZE, QAlignment(VALID_PREALLOCATION_ALIGNMENT_VALUE02) );
    QStackAllocatorWhiteBox::QMark markToTop02                            = stackAllocatorWhiteBox02.GetMark();
    pStackBase02                                                          = stackAllocatorWhiteBox02.GetpBase();
    pStackTop02                                                           = markToTop02.GetMemoryAddress();
    uPreallocationSize02                                                  = stackAllocatorWhiteBox02.GetSize();

    QStackAllocatorWhiteBox        stackAllocatorWhiteBox03( VALID_PREALLOCATION_SIZE, QAlignment(VALID_PREALLOCATION_ALIGNMENT_VALUE03) );
    QStackAllocatorWhiteBox::QMark markToTop03                            = stackAllocatorWhiteBox03.GetMark();
    pStackBase03                                                          = stackAllocatorWhiteBox03.GetpBase();
    pStackTop03                                                           = markToTop03.GetMemoryAddress();
    uPreallocationSize03                                                  = stackAllocatorWhiteBox03.GetSize();

    QStackAllocatorWhiteBox        stackAllocatorWhiteBox04( VALID_PREALLOCATION_SIZE, QAlignment(VALID_PREALLOCATION_ALIGNMENT_VALUE04) );
    QStackAllocatorWhiteBox::QMark markToTop04                            = stackAllocatorWhiteBox04.GetMark();
    pStackBase04                                                          = stackAllocatorWhiteBox04.GetpBase();
    pStackTop04                                                           = markToTop04.GetMemoryAddress();
    uPreallocationSize04                                                  = stackAllocatorWhiteBox04.GetSize();


    // [Verification]

    // Allocation has been made correctly when:
    //
    //     Stack Base is not null now
    // AND Stack top points to the same direction that Stack Base (because the stack is empty for now)
    // AND the size of the preallocated memory block is greater than zero now
    // AND the amount of allocated bytes for memory blocks is zero (because the stack is empty for now).

    if ( (null_q != pStackBase01) && (null_q != pStackBase02) && (null_q != pStackBase03) && (null_q != pStackBase04) )
        bNonNullStackBaseInAll           = true;

    if ( (pStackBase01 == pStackTop01) && (pStackBase02 == pStackTop02) && (pStackBase03 == pStackTop03) && (pStackBase04 == pStackTop04) )
        bTopEqualsBaseInAll              = true;

    if ( (uPreallocationSize01 > 0) && (uPreallocationSize02 > 0) && (uPreallocationSize03 > 0) && (uPreallocationSize04 > 0) )
        bPreallocationSizeIsNotZeroInAll = true;

    if ( (0 == uAllocatedBytes01) && (0 == uAllocatedBytes02) && (0 == uAllocatedBytes03) && (0 == uAllocatedBytes04) )
        bAllocatedBytesAreZeroInAll      = true;


    BOOST_CHECK_EQUAL(bNonNullStackBaseInAll,           EXPECTED_VALUE);
    BOOST_CHECK_EQUAL(bTopEqualsBaseInAll,              EXPECTED_VALUE);
    BOOST_CHECK_EQUAL(bPreallocationSizeIsNotZeroInAll, EXPECTED_VALUE);
    BOOST_CHECK_EQUAL(bAllocatedBytesAreZeroInAll,      EXPECTED_VALUE);
}

/// <summary>
/// Checks that the preallocated memory block is correctly aligned.
/// </summary>
QTEST_CASE ( Constructor2_ChecksThatPreallocatedMemoryBlockIsCorrectlyAligned_Test )
{
    // [Preparation]

    const pointer_uint_q    MISALIGNED_BYTES_EXPECTED_VALUE_ZERO  = 0;

    const pointer_uint_q    VALID_PREALLOCATION_SIZE              = 128;

    const pointer_uint_q    VALID_PREALLOCATION_ALIGNMENT_VALUE01 = 2;
    const pointer_uint_q    VALID_PREALLOCATION_ALIGNMENT_VALUE02 = 4;
    const pointer_uint_q    VALID_PREALLOCATION_ALIGNMENT_VALUE03 = 8;
    const pointer_uint_q    VALID_PREALLOCATION_ALIGNMENT_VALUE04 = 16;

    pointer_uint_q          uiMisalignedBytes01                   = 0;
    pointer_uint_q          uiMisalignedBytes02                   = 0;
    pointer_uint_q          uiMisalignedBytes03                   = 0;
    pointer_uint_q          uiMisalignedBytes04                   = 0;


    // [Execution]

    QStackAllocatorWhiteBox stackAllocatorWhiteBox01( VALID_PREALLOCATION_SIZE, QAlignment(VALID_PREALLOCATION_ALIGNMENT_VALUE01) );
    uiMisalignedBytes01       = rcast_q(stackAllocatorWhiteBox01.GetpBase(),pointer_uint_q) & (VALID_PREALLOCATION_ALIGNMENT_VALUE01 - 1);

    QStackAllocatorWhiteBox stackAllocatorWhiteBox02( VALID_PREALLOCATION_SIZE, QAlignment(VALID_PREALLOCATION_ALIGNMENT_VALUE02) );
    uiMisalignedBytes02       = rcast_q(stackAllocatorWhiteBox02.GetpBase(),pointer_uint_q) & (VALID_PREALLOCATION_ALIGNMENT_VALUE02 - 1);

    QStackAllocatorWhiteBox stackAllocatorWhiteBox03( VALID_PREALLOCATION_SIZE, QAlignment(VALID_PREALLOCATION_ALIGNMENT_VALUE03) );
    uiMisalignedBytes03       = rcast_q(stackAllocatorWhiteBox03.GetpBase(),pointer_uint_q) & (VALID_PREALLOCATION_ALIGNMENT_VALUE03 - 1);

    QStackAllocatorWhiteBox stackAllocatorWhiteBox04( VALID_PREALLOCATION_SIZE, QAlignment(VALID_PREALLOCATION_ALIGNMENT_VALUE04) );
    uiMisalignedBytes04       = rcast_q(stackAllocatorWhiteBox04.GetpBase(),pointer_uint_q) & (VALID_PREALLOCATION_ALIGNMENT_VALUE04 - 1);


    // [Verification]

    BOOST_CHECK_EQUAL(uiMisalignedBytes01, MISALIGNED_BYTES_EXPECTED_VALUE_ZERO);
    BOOST_CHECK_EQUAL(uiMisalignedBytes02, MISALIGNED_BYTES_EXPECTED_VALUE_ZERO);
    BOOST_CHECK_EQUAL(uiMisalignedBytes03, MISALIGNED_BYTES_EXPECTED_VALUE_ZERO);
    BOOST_CHECK_EQUAL(uiMisalignedBytes04, MISALIGNED_BYTES_EXPECTED_VALUE_ZERO);
}

#if QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that the assertion fails when the passed size for the preallocated block is zero.
/// </summary>
QTEST_CASE ( Constructor3_AssertionFailsWhenPreallocationSizeIsZero_Test )
{
    // [Preparation]

    const bool             ASSERTION_FAILED                 = true;
    bool                   bAssertionFailed                 = false;

    const pointer_uint_q   VALID_ALIGNMENT_VALUE            = 4;
    void*                  NON_NULL_ADDRESS                 = new (QAlignment(VALID_ALIGNMENT_VALUE)) u8_q;


	// [Execution]

    try
    {
        QStackAllocator stackAllocator( 0, NON_NULL_ADDRESS );
    }
    catch(const QAssertException&)
    {
        bAssertionFailed = true;
    }

 
    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);


    // [Cleaning]
    operator delete( NON_NULL_ADDRESS, QAlignment(VALID_ALIGNMENT_VALUE) );
}

/// <summary>
/// Checks that the assertion fails when the passed address of the externally preallocated block is null.
/// </summary>
QTEST_CASE ( Constructor3_AssertionFailsWhenPointerToPreallocatedMemoryBlockIsNull_Test )
{
    // [Preparation]

    const bool             ASSERTION_FAILED                 = true;
    bool                   bAssertionFailed                 = false;

    const pointer_uint_q   VALID_PREALLOCATION_SIZE         = 512;


	// [Execution]

    try
    {
        QStackAllocator stackAllocator( VALID_PREALLOCATION_SIZE, null_q );
    }
    catch(const QAssertException&)
    {
        bAssertionFailed = true;
    }

 
    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

#endif // QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that the stack base points to the same address that the passed preallocated memory block.
/// </summary>
QTEST_CASE ( Constructor3_StackBasePointsToSameAddressThatThePassedPreallocatedMemoryBlock_Test )
{
    // [Preparation]

    const pointer_uint_q     VALID_PREALLOCATION_SIZE             = 512;
    const pointer_uint_q     PREALLOCATE_ALIGNMENT_VALUE          = 1;
    const QAlignment         PREALLOCATION_ALIGMENT(PREALLOCATE_ALIGNMENT_VALUE);
    void*                    pPreallocatedBlock                   = null_q;
    void*                    pPreallocatedBase                    = null_q;


    // [Execution]

    pPreallocatedBlock = operator new(VALID_PREALLOCATION_SIZE, PREALLOCATION_ALIGMENT);
    QStackAllocatorWhiteBox  stackAllocatorWhiteBox( VALID_PREALLOCATION_SIZE, pPreallocatedBlock);

    pPreallocatedBase  = stackAllocatorWhiteBox.GetpBase();


    // [Verification]
    BOOST_CHECK_EQUAL( rcast_q(pPreallocatedBase,pointer_uint_q), rcast_q(pPreallocatedBlock,pointer_uint_q) );


    // [Cleaning]
    operator delete( pPreallocatedBlock, PREALLOCATION_ALIGMENT );
}

#if QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that the assertion fails when the passed size for the preallocated block is zero.
/// </summary>
QTEST_CASE ( Constructor4_AssertionFailsWhenPreallocationSizeIsZero_Test )
{

    // [Preparation]

    const bool             ASSERTION_FAILED                 = true;
    bool                   bAssertionFailed                 = false;

    const pointer_uint_q   VALID_ALIGNMENT_VALUE            = 4;
    QAlignment             PREALLOCATION_ALIGNMENT(VALID_ALIGNMENT_VALUE);
    void*                  NON_NULL_ADDRESS                 = new (PREALLOCATION_ALIGNMENT) u8_q;


	// [Execution]

    try
    {
        QStackAllocator stackAllocator( 0, NON_NULL_ADDRESS, PREALLOCATION_ALIGNMENT );
    }
    catch(const QAssertException&)
    {
        bAssertionFailed = true;
    }

 
    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED); 


	// [Cleaning]
    operator delete( NON_NULL_ADDRESS, PREALLOCATION_ALIGNMENT );
}

/// <summary>
/// Checks that the assertion fails when the passed address of the externally preallocated block is null.
/// </summary>
QTEST_CASE ( Constructor4_AssertionFailsWhenPointerToPreallocatedMemoryBlockIsNull_Test )
{

    // [Preparation]

    const bool             ASSERTION_FAILED                 = true;
    bool                   bAssertionFailed                 = false;

    const pointer_uint_q   VALID_PREALLOCATION_SIZE         = 512;

    const pointer_uint_q   VALID_ALIGNMENT_VALUE            = 2;
    QAlignment             PREALLOCATION_ALIGNMENT(VALID_ALIGNMENT_VALUE);

	// [Execution]

    try
    {
        QStackAllocator stackAllocator( VALID_PREALLOCATION_SIZE, null_q, PREALLOCATION_ALIGNMENT );
    }
    catch(const QAssertException&)
    {
        bAssertionFailed = true;
    }

 
    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

/// <summary>
/// Checks that the assertion fails when the passed alignment value is not a power of two.
/// </summary>
QTEST_CASE ( Constructor4_AssertionFailsWhenAlignmentValueIsNotAPowerOfTwo_Test )
{
    // [Preparation]

    const bool             ASSERTION_FAILED                 = true;
    bool                   bAssertionFailed                 = false;

    const pointer_uint_q   VALID_PREALLOCATION_SIZE         = 512;
    const pointer_uint_q   VALID_ALIGNMENT_VALUE            = 4;
    const pointer_uint_q   NON_VALID_ALIGNMENT_VALUE        = 3;
    void*                  NON_NULL_ADDRESS                 = new (QAlignment(VALID_ALIGNMENT_VALUE)) u8_q;


	// [Execution]

    try
    {
        QStackAllocator stackAllocator( VALID_PREALLOCATION_SIZE, NON_NULL_ADDRESS, QAlignment(NON_VALID_ALIGNMENT_VALUE) );
    }
    catch(const QAssertException&)
    {
        bAssertionFailed = true;
    }

 
    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);


    // [Cleaning]
    operator delete( NON_NULL_ADDRESS, QAlignment(VALID_ALIGNMENT_VALUE) );
}

#endif // QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that the stack base points to the same address that the passed preallocated memory block.
/// </summary>
QTEST_CASE ( Constructor4_StackBasePointsToSameAddressThatThePassedPreallocatedMemoryBlock_Test )
{
    // [Preparation]

    const bool                 EXPECTED_VALUE                             = true;

    const pointer_uint_q       VALID_PREALLOCATION_SIZE                   = 512;

    const pointer_uint_q       VALID_PREALLOCATION_ALIGNMENT_VALUE01      = 2;
    const pointer_uint_q       VALID_PREALLOCATION_ALIGNMENT_VALUE02      = 4;
    const pointer_uint_q       VALID_PREALLOCATION_ALIGNMENT_VALUE03      = 8;
    const pointer_uint_q       VALID_PREALLOCATION_ALIGNMENT_VALUE04      = 16;
    const QAlignment           PREALLOCATION_ALIGMENT01(VALID_PREALLOCATION_ALIGNMENT_VALUE01);
    const QAlignment           PREALLOCATION_ALIGMENT02(VALID_PREALLOCATION_ALIGNMENT_VALUE02);
    const QAlignment           PREALLOCATION_ALIGMENT03(VALID_PREALLOCATION_ALIGNMENT_VALUE03);
    const QAlignment           PREALLOCATION_ALIGMENT04(VALID_PREALLOCATION_ALIGNMENT_VALUE04);

    void*                      pPreallocatedBlock01                       = null_q;
    void*                      pPreallocatedBlock02                       = null_q;
    void*                      pPreallocatedBlock03                       = null_q;
    void*                      pPreallocatedBlock04                       = null_q;

    void*                      pPreallocatedBase01                        = null_q;
    void*                      pPreallocatedBase02                        = null_q;
    void*                      pPreallocatedBase03                        = null_q;
    void*                      pPreallocatedBase04                        = null_q;

    bool                       bSameAddressInStackAllocator01             = false;
    bool                       bSameAddressInStackAllocator02             = false;
    bool                       bSameAddressInStackAllocator03             = false;
    bool                       bSameAddressInStackAllocator04             = false;


    // [Execution]

    pPreallocatedBlock01 = new (PREALLOCATION_ALIGMENT01) u8_q[VALID_PREALLOCATION_SIZE + sizeof(QStackAllocatorWhiteBox::QBlockHeader)];
    QStackAllocatorWhiteBox    stackAllocatorWhiteBox01( (VALID_PREALLOCATION_SIZE + sizeof(QStackAllocatorWhiteBox::QBlockHeader)), pPreallocatedBlock01, PREALLOCATION_ALIGMENT01 );
    pPreallocatedBase01  = stackAllocatorWhiteBox01.GetpBase();

    pPreallocatedBlock02 = new (PREALLOCATION_ALIGMENT02) u8_q[VALID_PREALLOCATION_SIZE + sizeof(QStackAllocatorWhiteBox::QBlockHeader)];
    QStackAllocatorWhiteBox    stackAllocatorWhiteBox02( (VALID_PREALLOCATION_SIZE + sizeof(QStackAllocatorWhiteBox::QBlockHeader)), pPreallocatedBlock02, PREALLOCATION_ALIGMENT02 );
    pPreallocatedBase02  = stackAllocatorWhiteBox02.GetpBase();

    pPreallocatedBlock03 = new (PREALLOCATION_ALIGMENT03) u8_q[VALID_PREALLOCATION_SIZE + sizeof(QStackAllocatorWhiteBox::QBlockHeader)];
    QStackAllocatorWhiteBox    stackAllocatorWhiteBox03( (VALID_PREALLOCATION_SIZE + sizeof(QStackAllocatorWhiteBox::QBlockHeader)), pPreallocatedBlock03, PREALLOCATION_ALIGMENT03 );
    pPreallocatedBase03  = stackAllocatorWhiteBox03.GetpBase();

    pPreallocatedBlock04 = new (PREALLOCATION_ALIGMENT04) u8_q[VALID_PREALLOCATION_SIZE + sizeof(QStackAllocatorWhiteBox::QBlockHeader)];
    QStackAllocatorWhiteBox    stackAllocatorWhiteBox04( (VALID_PREALLOCATION_SIZE + sizeof(QStackAllocatorWhiteBox::QBlockHeader)), pPreallocatedBlock04, PREALLOCATION_ALIGMENT04 );
    pPreallocatedBase04  = stackAllocatorWhiteBox04.GetpBase();


    // [Verification]

    if (pPreallocatedBase01 == pPreallocatedBlock01)
        bSameAddressInStackAllocator01 = true;

    if (pPreallocatedBase02 == pPreallocatedBlock02)
        bSameAddressInStackAllocator02 = true;

    if (pPreallocatedBase03 == pPreallocatedBlock03)
        bSameAddressInStackAllocator03 = true;

    if (pPreallocatedBase04 == pPreallocatedBlock04)
        bSameAddressInStackAllocator04 = true;

    BOOST_CHECK_EQUAL( bSameAddressInStackAllocator01, EXPECTED_VALUE );
    BOOST_CHECK_EQUAL( bSameAddressInStackAllocator02, EXPECTED_VALUE );
    BOOST_CHECK_EQUAL( bSameAddressInStackAllocator03, EXPECTED_VALUE );
    BOOST_CHECK_EQUAL( bSameAddressInStackAllocator04, EXPECTED_VALUE );


    // [Cleaning]

    if (null_q != pPreallocatedBlock01)
    {
        operator delete (pPreallocatedBlock01, PREALLOCATION_ALIGMENT01);
        pPreallocatedBlock01 = null_q;
    }
    if (null_q != pPreallocatedBlock02)
    {
        operator delete (pPreallocatedBlock02, PREALLOCATION_ALIGMENT02);
        pPreallocatedBlock02 = null_q;
    }
    if (null_q != pPreallocatedBlock03)
    {
        operator delete (pPreallocatedBlock03, PREALLOCATION_ALIGMENT03);
        pPreallocatedBlock03 = null_q;
    }
    if (null_q != pPreallocatedBlock04)
    {
        operator delete (pPreallocatedBlock04, PREALLOCATION_ALIGMENT04);
        pPreallocatedBlock04 = null_q;
    }
}

/// <summary>
/// Checks that the start position of the buffer is adjusted to the alignment.
/// </summary>
QTEST_CASE ( Constructor4_BufferIsAdjustedToAlignment_Test )
{
    // [Preparation]
    const pointer_uint_q INPUT_SIZE = 8U;
    const QAlignment INPUT_ALIGNMENT(4U);
    void* pInputBuffer = operator new(8U, INPUT_ALIGNMENT);
    void* INPUT_ADDRESS = (void*)((pointer_uint_q)pInputBuffer + 2U);
    void* EXPECTED_ADDRESS = (void*)((pointer_uint_q)pInputBuffer + 4U); // The start address should be moved to this address so it is aligned to 4 bytes

    // [Execution]
    QStackAllocator allocator(INPUT_SIZE, INPUT_ADDRESS, INPUT_ALIGNMENT);

    // [Verification]
    void* pBuffer = allocator.GetMark().GetMemoryAddress();
    pointer_uint_q uAdjustment = INPUT_ALIGNMENT - ((pointer_uint_q)pBuffer & (INPUT_ALIGNMENT - 1U));

    BOOST_CHECK_EQUAL(pBuffer, EXPECTED_ADDRESS);
    BOOST_CHECK_EQUAL(uAdjustment, INPUT_ALIGNMENT);
    
    // [Cleaning]
    operator delete(pInputBuffer, INPUT_ALIGNMENT);
}

/// <summary>
/// Checks that the size is affected by the alignment adjustment (memory loss).
/// </summary>
QTEST_CASE ( Constructor4_SizeIsAffectedByAlignmentAdjustment_Test )
{
    // [Preparation]
    const pointer_uint_q INPUT_SIZE = 32U - 2U; // The input address starts 2 positions later
    const pointer_uint_q EXPECTED_SIZE = 28U; // The input address starts 2 positions later, so next multiple of 4 is 2 position later than that
    const QAlignment INPUT_ALIGNMENT(4U);
    void* pInputBuffer = operator new(32U, INPUT_ALIGNMENT);
    void* INPUT_ADDRESS = (void*)((pointer_uint_q)pInputBuffer + 2U);

    // [Execution]
    QStackAllocator allocator(INPUT_SIZE, INPUT_ADDRESS, INPUT_ALIGNMENT);

    // [Verification]
    pointer_uint_q uSize = allocator.GetSize();

    BOOST_CHECK_EQUAL(uSize, EXPECTED_SIZE);
    
    // [Cleaning]
    operator delete(pInputBuffer, INPUT_ALIGNMENT);
}

/// <summary>
/// Checks that a valid memory address is returned when using a common input size and an empty allocator.
/// </summary>
QTEST_CASE ( Allocate1_ReturnsValidAddressWhenUsingCommonSizeAndAllocatorIsEmpty_Test )
{
    // [Preparation]
    const pointer_uint_q INPUT_SIZE = 4U;
    const void* NULL_POINTER = null_q;
    QStackAllocator allocator(16U, QAlignment(4U));

    // [Execution]
    void* pAllocatedMemory = allocator.Allocate(INPUT_SIZE);

    // [Verification]
    BOOST_CHECK_NE(pAllocatedMemory, NULL_POINTER);
}

/// <summary>
/// Checks that a valid memory address is returned when using a common input size and a non-empty allocator.
/// </summary>
QTEST_CASE ( Allocate1_ReturnsValidAddressWhenUsingCommonSizeAndAllocatorIsNotEmpty_Test )
{
    // [Preparation]
    const pointer_uint_q INPUT_SIZE = 4U;
    const void* NULL_POINTER = null_q;
    QStackAllocator allocator(32U, QAlignment(4U));
    allocator.Allocate(INPUT_SIZE);

    // [Execution]
    void* pAllocatedMemory = allocator.Allocate(INPUT_SIZE);

    // [Verification]
    BOOST_CHECK_NE(pAllocatedMemory, NULL_POINTER);
}

/// <summary>
/// Checks that the allocated bytes increase on every allocation.
/// </summary>
QTEST_CASE ( Allocate1_AllocatedBytesGrow_Test )
{
    // [Preparation]
    const pointer_uint_q INPUT_SIZE = 6U;
    QStackAllocator allocator(32U, QAlignment(4U));
    const pointer_uint_q ALLOCATED_BYTES_BEFORE = allocator.GetAllocatedBytes();

    // [Execution]
    allocator.Allocate(INPUT_SIZE);

    // [Verification]
    pointer_uint_q uAllocatedBytesAfter = allocator.GetAllocatedBytes();
    BOOST_CHECK(uAllocatedBytesAfter > ALLOCATED_BYTES_BEFORE);
}

#if QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when trying an allocation and the size of the passed memory block to allocate is zero;
/// the alignment value for the memory block to allocate is assumed as the default one.
/// </summary>
QTEST_CASE (Allocate1_AssertionFailsWhenBlockSizeIsZero_Test)
{
    // [Preparation]

    const bool             ASSERTION_FAILED                      = true;
    const pointer_uint_q   AMOUNT_CASES                          = 5;

    const pointer_uint_q   VALID_PREALLOCATION_SIZE              = 512;

    const pointer_uint_q   VALID_PREALLOCATION_ALIGNMENT_VALUE01 = 2;
    const pointer_uint_q   VALID_PREALLOCATION_ALIGNMENT_VALUE02 = 4;
    const pointer_uint_q   VALID_PREALLOCATION_ALIGNMENT_VALUE03 = 8;
    const pointer_uint_q   VALID_PREALLOCATION_ALIGNMENT_VALUE04 = 16;

    void*                  pAllocation01                         = null_q;
    void*                  pAllocation02                         = null_q;
    void*                  pAllocation03                         = null_q;
    void*                  pAllocation04                         = null_q;
    void*                  pAllocation05                         = null_q;

    bool                   bAssertionFailedIn01                  = false;
    bool                   bAssertionFailedIn02                  = false;
    bool                   bAssertionFailedIn03                  = false;
    bool                   bAssertionFailedIn04                  = false;
    bool                   bAssertionFailedIn05                  = false;

	// [Execution]

    QStackAllocator stackAllocator01( VALID_PREALLOCATION_SIZE );
    QStackAllocator stackAllocator02( VALID_PREALLOCATION_SIZE, QAlignment(VALID_PREALLOCATION_ALIGNMENT_VALUE01) );
    QStackAllocator stackAllocator03( VALID_PREALLOCATION_SIZE, QAlignment(VALID_PREALLOCATION_ALIGNMENT_VALUE02) );
    QStackAllocator stackAllocator04( VALID_PREALLOCATION_SIZE, QAlignment(VALID_PREALLOCATION_ALIGNMENT_VALUE03) );
    QStackAllocator stackAllocator05( VALID_PREALLOCATION_SIZE, QAlignment(VALID_PREALLOCATION_ALIGNMENT_VALUE04) );

    for (pointer_uint_q u = 1; u <= AMOUNT_CASES; ++u)
    {
        try
        {
            switch (u)
            {
                case 1: pAllocation01 = stackAllocator01.Allocate(0); break;
                case 2: pAllocation02 = stackAllocator02.Allocate(0); break;
                case 3: pAllocation03 = stackAllocator03.Allocate(0); break;
                case 4: pAllocation04 = stackAllocator04.Allocate(0); break;
                case 5: pAllocation05 = stackAllocator05.Allocate(0); break;
            }
        }
        catch(const QAssertException&)
        {
            switch (u)
            {
                case 1:
                    if (null_q == pAllocation01)
                    {
                        bAssertionFailedIn01 = true;
                    }
                break;

                case 2:
                    if (null_q == pAllocation02)
                    {
                        bAssertionFailedIn02 = true;
                    }
                break;
                case 3:
                    if (null_q == pAllocation03)
                    {
                        bAssertionFailedIn03 = true;
                    }
                break;
                case 4:
                    if (null_q == pAllocation04)
                    {
                        bAssertionFailedIn04 = true;
                    }
                break;
                case 5:
                    if (null_q == pAllocation05)
                    {
                        bAssertionFailedIn05 = true;
                    }
                break;
            }
        }
    }


    // [Verification]

    BOOST_CHECK_EQUAL(bAssertionFailedIn01, ASSERTION_FAILED);
    BOOST_CHECK_EQUAL(bAssertionFailedIn02, ASSERTION_FAILED);
    BOOST_CHECK_EQUAL(bAssertionFailedIn03, ASSERTION_FAILED);
    BOOST_CHECK_EQUAL(bAssertionFailedIn04, ASSERTION_FAILED);
    BOOST_CHECK_EQUAL(bAssertionFailedIn05, ASSERTION_FAILED);
}

#endif // QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that a valid memory address is returned when using a common input size and an empty allocator.
/// </summary>
QTEST_CASE ( Allocate2_ReturnsValidAddressWhenUsingCommonSizeAndAllocatorIsEmpty_Test )
{
    // [Preparation]
    const pointer_uint_q INPUT_SIZE = 4U;
    const QAlignment INPUT_ALIGNMENT(4U);
    const void* NULL_POINTER = null_q;
    QStackAllocator allocator(16U, QAlignment(4U));

    // [Execution]
    void* pAllocatedMemory = allocator.Allocate(INPUT_SIZE, INPUT_ALIGNMENT);

    // [Verification]
    BOOST_CHECK_NE(pAllocatedMemory, NULL_POINTER);
}

/// <summary>
/// Checks that a valid memory address is returned when using a common input size and a non-empty allocator.
/// </summary>
QTEST_CASE ( Allocate2_ReturnsValidAddressWhenUsingCommonSizeAndAllocatorIsNotEmpty_Test )
{
    // [Preparation]
    const pointer_uint_q INPUT_SIZE = 4U;
    const QAlignment INPUT_ALIGNMENT(4U);
    const void* NULL_POINTER = null_q;
    QStackAllocator allocator(32U, QAlignment(4U));
    allocator.Allocate(INPUT_SIZE);

    // [Execution]
    void* pAllocatedMemory = allocator.Allocate(INPUT_SIZE, INPUT_ALIGNMENT);

    // [Verification]
    BOOST_CHECK_NE(pAllocatedMemory, NULL_POINTER);
}

/// <summary>
/// Checks that the allocated bytes increase on every allocation.
/// </summary>
QTEST_CASE ( Allocate2_AllocatedBytesGrow_Test )
{
    // [Preparation]
    const pointer_uint_q INPUT_SIZE = 4U;
    const QAlignment INPUT_ALIGNMENT(4U);
    QStackAllocator allocator(32U, QAlignment(4U));
    const pointer_uint_q ALLOCATED_BYTES_BEFORE = allocator.GetAllocatedBytes();

    // [Execution]
    allocator.Allocate(INPUT_SIZE, INPUT_ALIGNMENT);

    // [Verification]
    pointer_uint_q uAllocatedBytes = allocator.GetAllocatedBytes();
    BOOST_CHECK(uAllocatedBytes > ALLOCATED_BYTES_BEFORE);
}

/// <summary>
/// Checks that alignment adjustments count as allocated space.
/// </summary>
QTEST_CASE ( Allocate2_AlignmentAdjustmentAffectsTheAllocatedBytes_Test )
{
    // [Preparation]
    const pointer_uint_q INPUT_SIZE = 4U;
    const QAlignment INPUT_ALIGNMENT(4U);
    QStackAllocator allocator1(32U, QAlignment(4U));
    QStackAllocator allocator2(32U, QAlignment(4U));
    allocator1.Allocate(2U);
    allocator2.Allocate(4U);

    // [Execution]
    allocator1.Allocate(INPUT_SIZE, INPUT_ALIGNMENT); // 2-bytes adjustment applied
    allocator2.Allocate(INPUT_SIZE, INPUT_ALIGNMENT);

    // [Verification]
    // Checks that, even if the amount of bytes allocated is different, the occupied space is the same
    pointer_uint_q uAllocatedBytes1 = allocator1.GetAllocatedBytes();
    pointer_uint_q uAllocatedBytes2 = allocator2.GetAllocatedBytes();
    BOOST_CHECK_EQUAL(uAllocatedBytes1, uAllocatedBytes2);
}

#if QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when trying an allocation and the size of the passed memory block to allocate is zero;
/// the alignment value for the memory block to allocate is specified.
/// </summary>
QTEST_CASE (Allocate2_AssertionFailsWhenBlockSizeIsZero_Test)
{
    // [Preparation]

    const bool             ASSERTION_FAILED                      = true;
    const pointer_uint_q   AMOUNT_CASES                          = 20;

    const pointer_uint_q   VALID_PREALLOCATION_SIZE              = 512;

    const pointer_uint_q   VALID_PREALLOCATION_ALIGNMENT_VALUE01 = 2;
    const pointer_uint_q   VALID_PREALLOCATION_ALIGNMENT_VALUE02 = 4;
    const pointer_uint_q   VALID_PREALLOCATION_ALIGNMENT_VALUE03 = 8;
    const pointer_uint_q   VALID_PREALLOCATION_ALIGNMENT_VALUE04 = 16;

    const pointer_uint_q   VALID_ALLOCATION_ALIGNMENT_VALUE01    = 2;
    const pointer_uint_q   VALID_ALLOCATION_ALIGNMENT_VALUE02    = 4;
    const pointer_uint_q   VALID_ALLOCATION_ALIGNMENT_VALUE03    = 8;
    const pointer_uint_q   VALID_ALLOCATION_ALIGNMENT_VALUE04    = 16;

    void*                  pAllocation01                         = null_q;
    void*                  pAllocation02                         = null_q;
    void*                  pAllocation03                         = null_q;
    void*                  pAllocation04                         = null_q;
    void*                  pAllocation05                         = null_q;
    void*                  pAllocation06                         = null_q;
    void*                  pAllocation07                         = null_q;
    void*                  pAllocation08                         = null_q;
    void*                  pAllocation09                         = null_q;
    void*                  pAllocation10                         = null_q;
    void*                  pAllocation11                         = null_q;
    void*                  pAllocation12                         = null_q;
    void*                  pAllocation13                         = null_q;
    void*                  pAllocation14                         = null_q;
    void*                  pAllocation15                         = null_q;
    void*                  pAllocation16                         = null_q;
    void*                  pAllocation17                         = null_q;
    void*                  pAllocation18                         = null_q;
    void*                  pAllocation19                         = null_q;
    void*                  pAllocation20                         = null_q;

    bool                   bAssertionFailedIn01                  = false;
    bool                   bAssertionFailedIn02                  = false;
    bool                   bAssertionFailedIn03                  = false;
    bool                   bAssertionFailedIn04                  = false;
    bool                   bAssertionFailedIn05                  = false;
    bool                   bAssertionFailedIn06                  = false;
    bool                   bAssertionFailedIn07                  = false;
    bool                   bAssertionFailedIn08                  = false;
    bool                   bAssertionFailedIn09                  = false;
    bool                   bAssertionFailedIn10                  = false;
    bool                   bAssertionFailedIn11                  = false;
    bool                   bAssertionFailedIn12                  = false;
    bool                   bAssertionFailedIn13                  = false;
    bool                   bAssertionFailedIn14                  = false;
    bool                   bAssertionFailedIn15                  = false;
    bool                   bAssertionFailedIn16                  = false;
    bool                   bAssertionFailedIn17                  = false;
    bool                   bAssertionFailedIn18                  = false;
    bool                   bAssertionFailedIn19                  = false;
    bool                   bAssertionFailedIn20                  = false;

    pointer_uint_q         u                                     = 0;


	// [Execution]


    QStackAllocator stackAllocator01( VALID_PREALLOCATION_SIZE );
    QStackAllocator stackAllocator02( VALID_PREALLOCATION_SIZE );
    QStackAllocator stackAllocator03( VALID_PREALLOCATION_SIZE );
    QStackAllocator stackAllocator04( VALID_PREALLOCATION_SIZE );
    QStackAllocator stackAllocator05( VALID_PREALLOCATION_SIZE, QAlignment(VALID_PREALLOCATION_ALIGNMENT_VALUE01) );
    QStackAllocator stackAllocator06( VALID_PREALLOCATION_SIZE, QAlignment(VALID_PREALLOCATION_ALIGNMENT_VALUE01) );
    QStackAllocator stackAllocator07( VALID_PREALLOCATION_SIZE, QAlignment(VALID_PREALLOCATION_ALIGNMENT_VALUE01) );
    QStackAllocator stackAllocator08( VALID_PREALLOCATION_SIZE, QAlignment(VALID_PREALLOCATION_ALIGNMENT_VALUE01) );
    QStackAllocator stackAllocator09( VALID_PREALLOCATION_SIZE, QAlignment(VALID_PREALLOCATION_ALIGNMENT_VALUE02) );
    QStackAllocator stackAllocator10( VALID_PREALLOCATION_SIZE, QAlignment(VALID_PREALLOCATION_ALIGNMENT_VALUE02) );
    QStackAllocator stackAllocator11( VALID_PREALLOCATION_SIZE, QAlignment(VALID_PREALLOCATION_ALIGNMENT_VALUE02) );
    QStackAllocator stackAllocator12( VALID_PREALLOCATION_SIZE, QAlignment(VALID_PREALLOCATION_ALIGNMENT_VALUE02) );
    QStackAllocator stackAllocator13( VALID_PREALLOCATION_SIZE, QAlignment(VALID_PREALLOCATION_ALIGNMENT_VALUE03) );
    QStackAllocator stackAllocator14( VALID_PREALLOCATION_SIZE, QAlignment(VALID_PREALLOCATION_ALIGNMENT_VALUE03) );
    QStackAllocator stackAllocator15( VALID_PREALLOCATION_SIZE, QAlignment(VALID_PREALLOCATION_ALIGNMENT_VALUE03) );
    QStackAllocator stackAllocator16( VALID_PREALLOCATION_SIZE, QAlignment(VALID_PREALLOCATION_ALIGNMENT_VALUE03) );
    QStackAllocator stackAllocator17( VALID_PREALLOCATION_SIZE, QAlignment(VALID_PREALLOCATION_ALIGNMENT_VALUE04) );
    QStackAllocator stackAllocator18( VALID_PREALLOCATION_SIZE, QAlignment(VALID_PREALLOCATION_ALIGNMENT_VALUE04) );
    QStackAllocator stackAllocator19( VALID_PREALLOCATION_SIZE, QAlignment(VALID_PREALLOCATION_ALIGNMENT_VALUE04) );
    QStackAllocator stackAllocator20( VALID_PREALLOCATION_SIZE, QAlignment(VALID_PREALLOCATION_ALIGNMENT_VALUE04) );

    for (u = 1; u <= AMOUNT_CASES; ++u)
    {
        try
        {
            switch (u)
            {
                case 1:  pAllocation01 = stackAllocator01.Allocate( 0, QAlignment(VALID_ALLOCATION_ALIGNMENT_VALUE01) ); break;
                case 2:  pAllocation02 = stackAllocator02.Allocate( 0, QAlignment(VALID_ALLOCATION_ALIGNMENT_VALUE02) ); break;
                case 3:  pAllocation03 = stackAllocator03.Allocate( 0, QAlignment(VALID_ALLOCATION_ALIGNMENT_VALUE03) ); break;
                case 4:  pAllocation04 = stackAllocator04.Allocate( 0, QAlignment(VALID_ALLOCATION_ALIGNMENT_VALUE04) ); break;
                case 5:  pAllocation05 = stackAllocator05.Allocate( 0, QAlignment(VALID_ALLOCATION_ALIGNMENT_VALUE01) ); break;
                case 6:  pAllocation06 = stackAllocator06.Allocate( 0, QAlignment(VALID_ALLOCATION_ALIGNMENT_VALUE02) ); break;
                case 7:  pAllocation07 = stackAllocator07.Allocate( 0, QAlignment(VALID_ALLOCATION_ALIGNMENT_VALUE03) ); break;
                case 8:  pAllocation08 = stackAllocator08.Allocate( 0, QAlignment(VALID_ALLOCATION_ALIGNMENT_VALUE04) ); break;
                case 9:  pAllocation09 = stackAllocator09.Allocate( 0, QAlignment(VALID_ALLOCATION_ALIGNMENT_VALUE01) ); break;
                case 10: pAllocation10 = stackAllocator10.Allocate( 0, QAlignment(VALID_ALLOCATION_ALIGNMENT_VALUE02) ); break;
                case 11: pAllocation11 = stackAllocator11.Allocate( 0, QAlignment(VALID_ALLOCATION_ALIGNMENT_VALUE03) ); break;
                case 12: pAllocation12 = stackAllocator12.Allocate( 0, QAlignment(VALID_ALLOCATION_ALIGNMENT_VALUE04) ); break;
                case 13: pAllocation13 = stackAllocator13.Allocate( 0, QAlignment(VALID_ALLOCATION_ALIGNMENT_VALUE01) ); break;
                case 14: pAllocation14 = stackAllocator14.Allocate( 0, QAlignment(VALID_ALLOCATION_ALIGNMENT_VALUE02) ); break;
                case 15: pAllocation15 = stackAllocator15.Allocate( 0, QAlignment(VALID_ALLOCATION_ALIGNMENT_VALUE03) ); break;
                case 16: pAllocation16 = stackAllocator16.Allocate( 0, QAlignment(VALID_ALLOCATION_ALIGNMENT_VALUE04) ); break;
                case 17: pAllocation17 = stackAllocator17.Allocate( 0, QAlignment(VALID_ALLOCATION_ALIGNMENT_VALUE01) ); break;
                case 18: pAllocation18 = stackAllocator18.Allocate( 0, QAlignment(VALID_ALLOCATION_ALIGNMENT_VALUE02) ); break;
                case 19: pAllocation19 = stackAllocator19.Allocate( 0, QAlignment(VALID_ALLOCATION_ALIGNMENT_VALUE03) ); break;
                case 20: pAllocation20 = stackAllocator20.Allocate( 0, QAlignment(VALID_ALLOCATION_ALIGNMENT_VALUE04) ); break;
            }
        }
        catch(const QAssertException&)
        {
            switch (u)
            {
                case 1:
                    if (null_q == pAllocation01)
                    {
                        bAssertionFailedIn01 = true;
                    }
                break;

                case 2:
                    if (null_q == pAllocation02)
                    {
                        bAssertionFailedIn02 = true;
                    }
                break;
                case 3:
                    if (null_q == pAllocation03)
                    {
                        bAssertionFailedIn03 = true;
                    }
                break;
                case 4:
                    if (null_q == pAllocation04)
                    {
                        bAssertionFailedIn04 = true;
                    }
                break;
                case 5:
                    if (null_q == pAllocation05)
                    {
                        bAssertionFailedIn05 = true;
                    }
                break;
                case 6:
                    if (null_q == pAllocation06)
                    {
                        bAssertionFailedIn06 = true;
                    }
                case 7:
                    if (null_q == pAllocation07)
                    {
                        bAssertionFailedIn07 = true;
                    }
                break;
                case 8:
                    if (null_q == pAllocation08)
                    {
                        bAssertionFailedIn08 = true;
                    }
                break;
                case 9:
                    if (null_q == pAllocation09)
                    {
                        bAssertionFailedIn09 = true;
                    }
                break;
                case 10:
                    if (null_q == pAllocation10)
                    {
                        bAssertionFailedIn10 = true;
                    }
                break;
                case 11:
                    if (null_q == pAllocation11)
                    {
                        bAssertionFailedIn11 = true;
                    }
                break;
                case 12:
                    if (null_q == pAllocation12)
                    {
                        bAssertionFailedIn12 = true;
                    }
                break;
                case 13:
                    if (null_q == pAllocation13)
                    {
                        bAssertionFailedIn13 = true;
                    }
                break;
                case 14:
                    if (null_q == pAllocation14)
                    {
                        bAssertionFailedIn14 = true;
                    }
                break;
                case 15:
                    if (null_q == pAllocation15)
                    {
                        bAssertionFailedIn15 = true;
                    }
                break;
                case 16:
                    if (null_q == pAllocation16)
                    {
                        bAssertionFailedIn16 = true;
                    }
                break;
                case 17:
                    if (null_q == pAllocation17)
                    {
                        bAssertionFailedIn17 = true;
                    }
                break;
                case 18:
                    if (null_q == pAllocation18)
                    {
                        bAssertionFailedIn18 = true;
                    }
                break;
                case 19:
                    if (null_q == pAllocation19)
                    {
                        bAssertionFailedIn19 = true;
                    }
                break;
                case 20:
                    if (null_q == pAllocation20)
                    {
                        bAssertionFailedIn20 = true;
                    }
                break;
            }
        }
    }


    // [Verification]

    BOOST_CHECK_EQUAL(bAssertionFailedIn01, ASSERTION_FAILED);
    BOOST_CHECK_EQUAL(bAssertionFailedIn02, ASSERTION_FAILED);
    BOOST_CHECK_EQUAL(bAssertionFailedIn03, ASSERTION_FAILED);
    BOOST_CHECK_EQUAL(bAssertionFailedIn04, ASSERTION_FAILED);
    BOOST_CHECK_EQUAL(bAssertionFailedIn05, ASSERTION_FAILED);
    BOOST_CHECK_EQUAL(bAssertionFailedIn06, ASSERTION_FAILED);
    BOOST_CHECK_EQUAL(bAssertionFailedIn07, ASSERTION_FAILED);
    BOOST_CHECK_EQUAL(bAssertionFailedIn08, ASSERTION_FAILED);
    BOOST_CHECK_EQUAL(bAssertionFailedIn09, ASSERTION_FAILED);
    BOOST_CHECK_EQUAL(bAssertionFailedIn10, ASSERTION_FAILED);
    BOOST_CHECK_EQUAL(bAssertionFailedIn11, ASSERTION_FAILED);
    BOOST_CHECK_EQUAL(bAssertionFailedIn12, ASSERTION_FAILED);
    BOOST_CHECK_EQUAL(bAssertionFailedIn13, ASSERTION_FAILED);
    BOOST_CHECK_EQUAL(bAssertionFailedIn14, ASSERTION_FAILED);
    BOOST_CHECK_EQUAL(bAssertionFailedIn15, ASSERTION_FAILED);
    BOOST_CHECK_EQUAL(bAssertionFailedIn16, ASSERTION_FAILED);
    BOOST_CHECK_EQUAL(bAssertionFailedIn17, ASSERTION_FAILED);
    BOOST_CHECK_EQUAL(bAssertionFailedIn18, ASSERTION_FAILED);
    BOOST_CHECK_EQUAL(bAssertionFailedIn19, ASSERTION_FAILED);
    BOOST_CHECK_EQUAL(bAssertionFailedIn20, ASSERTION_FAILED);
}

/// <summary>
/// Checks that an assertion fails when trying an allocation and the passed alignment value for the memory block
/// to allocate is not a power of two.
/// </summary>
QTEST_CASE (Allocate2_AssertionFailsWhenAlignmentValueForBlockToAllocateIsNotAPowerOfTwo_Test)
{
    // [Preparation]

    const bool             ASSERTION_FAILED                      = true;
    const pointer_uint_q   AMOUNT_CASES                          = 5;
                                                                
    const pointer_uint_q   VALID_PREALLOCATION_SIZE              = 512;

    const pointer_uint_q   VALID_PREALLOCATION_ALIGNMENT_VALUE01 = 2;
    const pointer_uint_q   VALID_PREALLOCATION_ALIGNMENT_VALUE02 = 4;
    const pointer_uint_q   VALID_PREALLOCATION_ALIGNMENT_VALUE03 = 8;
    const pointer_uint_q   VALID_PREALLOCATION_ALIGNMENT_VALUE04 = 16;

    const pointer_uint_q   VALID_ALLOCATION_SIZE                 = 32;
    const pointer_uint_q   NON_VALID_ALLOCATION_ALIGNMENT_VALUE  = 3;
                                                                 
    void*                  pAllocation01                         = null_q;
    void*                  pAllocation02                         = null_q;
    void*                  pAllocation03                         = null_q;
    void*                  pAllocation04                         = null_q;
    void*                  pAllocation05                         = null_q;
                                                                 
    bool                   bAssertionFailedIn01                  = false;
    bool                   bAssertionFailedIn02                  = false;
    bool                   bAssertionFailedIn03                  = false;
    bool                   bAssertionFailedIn04                  = false;
    bool                   bAssertionFailedIn05                  = false;
                                                                 
    pointer_uint_q         u                                     = 0;


	// [Execution]

    QStackAllocator stackAllocator01( VALID_PREALLOCATION_SIZE );
    QStackAllocator stackAllocator02( VALID_PREALLOCATION_SIZE, QAlignment(VALID_PREALLOCATION_ALIGNMENT_VALUE01) );
    QStackAllocator stackAllocator03( VALID_PREALLOCATION_SIZE, QAlignment(VALID_PREALLOCATION_ALIGNMENT_VALUE02) );
    QStackAllocator stackAllocator04( VALID_PREALLOCATION_SIZE, QAlignment(VALID_PREALLOCATION_ALIGNMENT_VALUE03) );
    QStackAllocator stackAllocator05( VALID_PREALLOCATION_SIZE, QAlignment(VALID_PREALLOCATION_ALIGNMENT_VALUE04) );

    for (u = 1; u <= AMOUNT_CASES; ++u)
    {
        try
        {
            switch (u)
            {
                case 1: pAllocation01 = stackAllocator01.Allocate( VALID_ALLOCATION_SIZE, QAlignment(NON_VALID_ALLOCATION_ALIGNMENT_VALUE) ); break;
                case 2: pAllocation02 = stackAllocator02.Allocate( VALID_ALLOCATION_SIZE, QAlignment(NON_VALID_ALLOCATION_ALIGNMENT_VALUE) ); break;
                case 3: pAllocation03 = stackAllocator03.Allocate( VALID_ALLOCATION_SIZE, QAlignment(NON_VALID_ALLOCATION_ALIGNMENT_VALUE) ); break;
                case 4: pAllocation04 = stackAllocator04.Allocate( VALID_ALLOCATION_SIZE, QAlignment(NON_VALID_ALLOCATION_ALIGNMENT_VALUE) ); break;
                case 5: pAllocation05 = stackAllocator05.Allocate( VALID_ALLOCATION_SIZE, QAlignment(NON_VALID_ALLOCATION_ALIGNMENT_VALUE) ); break;
            }
        }
        catch(const QAssertException&)
        {
            switch (u)
            {
                case 1:
                    if (null_q == pAllocation01)
                    {
                        bAssertionFailedIn01 = true;
                    }
                break;
                case 2:
                    if (null_q == pAllocation02)
                    {
                        bAssertionFailedIn02 = true;
                    }
                break;
                case 3:
                    if (null_q == pAllocation03)
                    {
                        bAssertionFailedIn03 = true;
                    }
                break;
                case 4:
                    if (null_q == pAllocation04)
                    {
                        bAssertionFailedIn04 = true;
                    }
                break;
                case 5:
                    if (null_q == pAllocation05)
                    {
                        bAssertionFailedIn05 = true;
                    }
                break;
            }
        }
    }


    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailedIn01, ASSERTION_FAILED);
    BOOST_CHECK_EQUAL(bAssertionFailedIn02, ASSERTION_FAILED);
    BOOST_CHECK_EQUAL(bAssertionFailedIn03, ASSERTION_FAILED);
    BOOST_CHECK_EQUAL(bAssertionFailedIn04, ASSERTION_FAILED);
    BOOST_CHECK_EQUAL(bAssertionFailedIn05, ASSERTION_FAILED);
}

#endif // QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks if a deallocation of a block allows it to be allocated again.
/// </summary>
QTEST_CASE( Deallocate1_DeallocationOfABlockAllowsItToBeAllocatedAgain_Test )
{
    // [Preparation]
    const pointer_uint_q INPUT_SIZE = 4U;
    const QAlignment INPUT_ALIGNMENT(4U);
    QStackAllocator allocator(32U, QAlignment(4U));
    void* pAllocatedMemoryBefore = allocator.Allocate(INPUT_SIZE);
    
    // [Execution]
    allocator.Deallocate();

    // [Verification]
    void* AllocatedMemoryAfter = allocator.Allocate(INPUT_SIZE, INPUT_ALIGNMENT);
    BOOST_CHECK_EQUAL(pAllocatedMemoryBefore, AllocatedMemoryAfter);
}

/// <summary>
/// Checks that the allocated bytes decrease on every allocation.
/// </summary>
QTEST_CASE ( Deallocate1_AllocatedBytesDecrease_Test )
{
    // [Preparation]
    const pointer_uint_q INPUT_SIZE = 4U;
    const QAlignment INPUT_ALIGNMENT(4U);
    QStackAllocator allocator(32U, QAlignment(4U));
    allocator.Allocate(INPUT_SIZE, INPUT_ALIGNMENT);
    const pointer_uint_q ALLOCATED_BYTES_BEFORE = allocator.GetAllocatedBytes();

    // [Execution]
    allocator.Deallocate();

    // [Verification]
    pointer_uint_q uAllocatedBytes = allocator.GetAllocatedBytes();
    BOOST_CHECK(uAllocatedBytes < ALLOCATED_BYTES_BEFORE);
}

/// <summary>
/// Checks that deallocations work as expected when some previous allocations where adjusted to the alignment.
/// </summary>
QTEST_CASE ( Deallocate1_DeallocationsWorkWellWhenSomeAllocationsWhereAdjustedToAlignment_Test )
{
    // [Preparation]
    const pointer_uint_q INPUT_SIZE = 4U;
    const QAlignment INPUT_ALIGNMENT(4U);
    QStackAllocator allocator(32U, QAlignment(4U));
    allocator.Allocate(2U);
    void* pTopBeforeDeallocation = allocator.GetMark().GetMemoryAddress();
    allocator.Allocate(INPUT_SIZE, INPUT_ALIGNMENT); // 2-bytes adjustment applied

    // [Execution]
    allocator.Deallocate();

    // [Verification]
    void* pTopAfterDeallocation = allocator.GetMark().GetMemoryAddress();
    BOOST_CHECK_EQUAL(pTopBeforeDeallocation, pTopAfterDeallocation);
}

#if QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the passed mark -for rolling the stack top back to a certain address- is null.
/// The alignment value for the block which it is pretending to be deallocated is the default one.
/// </summary>
QTEST_CASE(Deallocate1_AssertionFailsWhenPassedMarkIsNull_Test)
{
    // [Preparation]

    const bool                     ASSERTION_FAILED                           = true;
    const pointer_uint_q           AMOUNT_CASES                               = 5;

    const pointer_uint_q           VALID_PREALLOCATION_SIZE                   = 64;
    const pointer_uint_q           VALID_ALLOCATION_SIZE                      = 32;

    const pointer_uint_q           VALID_PREALLOCATION_ALIGNMENT_VALUE01      = 2;
    const pointer_uint_q           VALID_PREALLOCATION_ALIGNMENT_VALUE02      = 4;
    const pointer_uint_q           VALID_PREALLOCATION_ALIGNMENT_VALUE03      = 8;
    const pointer_uint_q           VALID_PREALLOCATION_ALIGNMENT_VALUE04      = 16;

    bool                           bAssertionFailedIn01                       = false;
    bool                           bAssertionFailedIn02                       = false;
    bool                           bAssertionFailedIn03                       = false;
    bool                           bAssertionFailedIn04                       = false;
    bool                           bAssertionFailedIn05                       = false;

    pointer_uint_q                 u                                          = 0;


	// [Execution]

    QStackAllocator                stackAllocator01( VALID_PREALLOCATION_SIZE );
    QStackAllocator                stackAllocator02( VALID_PREALLOCATION_SIZE, QAlignment(VALID_PREALLOCATION_ALIGNMENT_VALUE01) );
    QStackAllocator                stackAllocator03( VALID_PREALLOCATION_SIZE, QAlignment(VALID_PREALLOCATION_ALIGNMENT_VALUE02) );
    QStackAllocator                stackAllocator04( VALID_PREALLOCATION_SIZE, QAlignment(VALID_PREALLOCATION_ALIGNMENT_VALUE03) );
    QStackAllocator                stackAllocator05( VALID_PREALLOCATION_SIZE, QAlignment(VALID_PREALLOCATION_ALIGNMENT_VALUE04) );

    stackAllocator01.Allocate( VALID_ALLOCATION_SIZE );
    stackAllocator02.Allocate( VALID_ALLOCATION_SIZE );
    stackAllocator03.Allocate( VALID_ALLOCATION_SIZE );
    stackAllocator04.Allocate( VALID_ALLOCATION_SIZE );
    stackAllocator05.Allocate( VALID_ALLOCATION_SIZE );

    QStackAllocatorWhiteBox::QMarkMocked markMocked01( (stackAllocator01.GetMark()).GetMemoryAddress() ); 
    QStackAllocatorWhiteBox::QMarkMocked markMocked02( (stackAllocator02.GetMark()).GetMemoryAddress() ); 
    QStackAllocatorWhiteBox::QMarkMocked markMocked03( (stackAllocator03.GetMark()).GetMemoryAddress() ); 
    QStackAllocatorWhiteBox::QMarkMocked markMocked04( (stackAllocator04.GetMark()).GetMemoryAddress() ); 
    QStackAllocatorWhiteBox::QMarkMocked markMocked05( (stackAllocator05.GetMark()).GetMemoryAddress() );

    // Sabotage of the adress.
    markMocked01.SabotageMarkToNull();
    markMocked02.SabotageMarkToNull();
    markMocked03.SabotageMarkToNull();
    markMocked04.SabotageMarkToNull();
    markMocked05.SabotageMarkToNull();

    for (u = 1; u <= AMOUNT_CASES; ++u)
    {
        try
        {
            switch (u)
            {
                case 1:  stackAllocator01.Deallocate( markMocked01 ); break;
                case 2:  stackAllocator02.Deallocate( markMocked02 ); break;
                case 3:  stackAllocator03.Deallocate( markMocked03 ); break;
                case 4:  stackAllocator04.Deallocate( markMocked04 ); break;
                case 5:  stackAllocator05.Deallocate( markMocked05 ); break;
            }
        }
        catch(const QAssertException&)
        {
            switch (u)
            {
                case 1:
                    if (false == bAssertionFailedIn01)
                    {
                        bAssertionFailedIn01 = true;
                    }
                break;
                case 2:
                    if (false == bAssertionFailedIn02)
                    {
                        bAssertionFailedIn02 = true;
                    }
                break;
                case 3:
                    if (false == bAssertionFailedIn03)
                    {
                        bAssertionFailedIn03 = true;
                    }
                break;
                case 4:
                    if (false == bAssertionFailedIn04)
                    {
                        bAssertionFailedIn04 = true;
                    }
                break;
                case 5:
                    if (false == bAssertionFailedIn05)
                    {
                        bAssertionFailedIn05 = true;
                    }
                break;
            };
        }
    }


    // [Verification]

    BOOST_CHECK_EQUAL(bAssertionFailedIn01, ASSERTION_FAILED);
    BOOST_CHECK_EQUAL(bAssertionFailedIn02, ASSERTION_FAILED);
    BOOST_CHECK_EQUAL(bAssertionFailedIn03, ASSERTION_FAILED);
    BOOST_CHECK_EQUAL(bAssertionFailedIn04, ASSERTION_FAILED);
    BOOST_CHECK_EQUAL(bAssertionFailedIn05, ASSERTION_FAILED);
}

/// <summary>
/// Checks that an assertion fails when a deallocation occurs and the stack is empty.
/// The alignment value for the block which it is pretending to be deallocated is the default one.
/// </summary>
QTEST_CASE(Deallocate1_AssertionFailsWhenDeallocationOccursAndStackIsEmpty_Test)
{
    // [Preparation]

    const bool                     ASSERTION_FAILED                           = true;
    const pointer_uint_q           AMOUNT_CASES                               = 5;

    const pointer_uint_q           VALID_PREALLOCATION_SIZE                   = 64;
    const pointer_uint_q           VALID_ALLOCATION_SIZE                      = 32;

    const pointer_uint_q           VALID_PREALLOCATION_ALIGNMENT_VALUE01      = 2;
    const pointer_uint_q           VALID_PREALLOCATION_ALIGNMENT_VALUE02      = 4;
    const pointer_uint_q           VALID_PREALLOCATION_ALIGNMENT_VALUE03      = 8;
    const pointer_uint_q           VALID_PREALLOCATION_ALIGNMENT_VALUE04      = 16;

    bool                           bAssertionFailedIn01                       = false;
    bool                           bAssertionFailedIn02                       = false;
    bool                           bAssertionFailedIn03                       = false;
    bool                           bAssertionFailedIn04                       = false;
    bool                           bAssertionFailedIn05                       = false;

    pointer_uint_q                 u                                          = 0;
    
	// [Execution]

    QStackAllocatorWhiteBox        stackAllocatorWhiteBox01( VALID_PREALLOCATION_SIZE );
    QStackAllocatorWhiteBox        stackAllocatorWhiteBox02( VALID_PREALLOCATION_SIZE );
    QStackAllocatorWhiteBox        stackAllocatorWhiteBox03( VALID_PREALLOCATION_SIZE );
    QStackAllocatorWhiteBox        stackAllocatorWhiteBox04( VALID_PREALLOCATION_SIZE );
    QStackAllocatorWhiteBox        stackAllocatorWhiteBox05( VALID_PREALLOCATION_SIZE );
    
    stackAllocatorWhiteBox01.Allocate( VALID_ALLOCATION_SIZE );
    stackAllocatorWhiteBox02.Allocate( VALID_ALLOCATION_SIZE, QAlignment(VALID_PREALLOCATION_ALIGNMENT_VALUE01) );
    stackAllocatorWhiteBox03.Allocate( VALID_ALLOCATION_SIZE, QAlignment(VALID_PREALLOCATION_ALIGNMENT_VALUE02) );
    stackAllocatorWhiteBox04.Allocate( VALID_ALLOCATION_SIZE, QAlignment(VALID_PREALLOCATION_ALIGNMENT_VALUE03) );
    stackAllocatorWhiteBox05.Allocate( VALID_ALLOCATION_SIZE, QAlignment(VALID_PREALLOCATION_ALIGNMENT_VALUE04) );
    
    // First deallocation --> Stack Tops are empty now.
    stackAllocatorWhiteBox01.Deallocate();
    stackAllocatorWhiteBox02.Deallocate();
    stackAllocatorWhiteBox03.Deallocate();
    stackAllocatorWhiteBox04.Deallocate();
    stackAllocatorWhiteBox05.Deallocate();
    
    // A second deallocation --> Stack Tops are empty now, so the assertion will fail.
    for (u = 1; u <= AMOUNT_CASES; ++u)
    {
        try
        {
            switch (u)
            {
                case  1: stackAllocatorWhiteBox01.Deallocate(); break;
                case  2: stackAllocatorWhiteBox02.Deallocate(); break;
                case  3: stackAllocatorWhiteBox03.Deallocate(); break;
                case  4: stackAllocatorWhiteBox04.Deallocate(); break;
                case  5: stackAllocatorWhiteBox05.Deallocate(); break;
            }
        }
        catch(const QAssertException&)
        {
            switch (u)
            {
                case 1:
                    if (false == bAssertionFailedIn01)
                    {
                        bAssertionFailedIn01 = true;
                    }
                break;
                case 2:
                    if (false == bAssertionFailedIn02)
                    {
                        bAssertionFailedIn02 = true;
                    }
                break;
                case 3:
                    if (false == bAssertionFailedIn03)
                    {
                        bAssertionFailedIn03 = true;
                    }
                break;
                case 4:
                    if (false == bAssertionFailedIn04)
                    {
                        bAssertionFailedIn04 = true;
                    }
                break;
                case 5:
                    if (false == bAssertionFailedIn05)
                    {
                        bAssertionFailedIn05 = true;
                    }
                break;
            };
        }
    }


    // [Verification]

    BOOST_CHECK_EQUAL(bAssertionFailedIn01, ASSERTION_FAILED);
    BOOST_CHECK_EQUAL(bAssertionFailedIn02, ASSERTION_FAILED);
    BOOST_CHECK_EQUAL(bAssertionFailedIn03, ASSERTION_FAILED);
    BOOST_CHECK_EQUAL(bAssertionFailedIn04, ASSERTION_FAILED);
    BOOST_CHECK_EQUAL(bAssertionFailedIn05, ASSERTION_FAILED);
}

#endif // QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks if a deallocation of the stack until the base allows to allocate blocks later.
/// </summary>
QTEST_CASE( Deallocate2_DeallocationTillTheBaseAllowsFurtherAllocations_Test )
{
    // [Preparation]
    const pointer_uint_q INPUT_SIZE = 4U;
    const QAlignment INPUT_ALIGNMENT(4U);
    QStackAllocator allocator(32U, QAlignment(4U));
    QStackAllocator::QMark baseMark = allocator.GetMark();
    void* pAllocatedMemoryBefore = allocator.Allocate(INPUT_SIZE);
    
    // [Execution]
    allocator.Deallocate(baseMark);

    // [Verification]
    void* AllocatedMemoryAfter = allocator.Allocate(INPUT_SIZE, INPUT_ALIGNMENT);
    BOOST_CHECK_EQUAL(pAllocatedMemoryBefore, AllocatedMemoryAfter);
}

/// <summary>
/// Checks that the allocated bytes decrease on every allocation.
/// </summary>
QTEST_CASE ( Deallocate2_AllocatedBytesDecrease_Test )
{
    // [Preparation]
    const pointer_uint_q INPUT_SIZE = 4U;
    const QAlignment INPUT_ALIGNMENT(4U);
    QStackAllocator allocator(32U, QAlignment(4U));
    QStackAllocator::QMark baseMark = allocator.GetMark();
    allocator.Allocate(INPUT_SIZE, INPUT_ALIGNMENT);
    const pointer_uint_q ALLOCATED_BYTES_BEFORE = allocator.GetAllocatedBytes();

    // [Execution]
    allocator.Deallocate(baseMark);

    // [Verification]
    pointer_uint_q uAllocatedBytes = allocator.GetAllocatedBytes();
    BOOST_CHECK(uAllocatedBytes < ALLOCATED_BYTES_BEFORE);
}

/// <summary>
/// Checks if a deallocation of the stack until some address in the middle allows to allocate blocks later.
/// </summary>
QTEST_CASE( Deallocate2_DeallocationTillMiddleAllowsFurtherAllocations_Test )
{
    // [Preparation]
    const pointer_uint_q INPUT_SIZE = 4U;
    const QAlignment INPUT_ALIGNMENT(4U);
    QStackAllocator allocator(80U, QAlignment(4U));
    allocator.Allocate(INPUT_SIZE);
    QStackAllocator::QMark mark = allocator.GetMark();
    void* pAllocatedMemoryBefore = allocator.Allocate(INPUT_SIZE);
    allocator.Allocate(INPUT_SIZE);
    
    // [Execution]
    allocator.Deallocate(mark);

    // [Verification]
    void* AllocatedMemoryAfter = allocator.Allocate(INPUT_SIZE, INPUT_ALIGNMENT);
    BOOST_CHECK_EQUAL(pAllocatedMemoryBefore, AllocatedMemoryAfter);
}

#if QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the passed mark -for rolling the stack top back to a certain address- is null.
/// The alignment value for the block which it is pretending to be deallocated is specified.
/// </summary>
QTEST_CASE(Deallocate2_AssertionFailsWhenPassedMarkIsNull_Test)
{
    // [Preparation]

    const bool                     ASSERTION_FAILED                           = true;
    const pointer_uint_q           AMOUNT_CASES                               = 20;

    const pointer_uint_q           VALID_PREALLOCATION_SIZE                   = 64;
    const pointer_uint_q           VALID_ALLOCATION_SIZE                      = 32;

    const pointer_uint_q           VALID_PREALLOCATION_ALIGNMENT_VALUE01      = 2;
    const pointer_uint_q           VALID_PREALLOCATION_ALIGNMENT_VALUE02      = 4;
    const pointer_uint_q           VALID_PREALLOCATION_ALIGNMENT_VALUE03      = 8;
    const pointer_uint_q           VALID_PREALLOCATION_ALIGNMENT_VALUE04      = 16;

    const pointer_uint_q           VALID_ALLOCATION_ALIGNMENT_VALUE01         = 2;
    const pointer_uint_q           VALID_ALLOCATION_ALIGNMENT_VALUE02         = 4;
    const pointer_uint_q           VALID_ALLOCATION_ALIGNMENT_VALUE03         = 8;
    const pointer_uint_q           VALID_ALLOCATION_ALIGNMENT_VALUE04         = 16;

    bool                           bAssertionFailedIn01                       = false;
    bool                           bAssertionFailedIn02                       = false;
    bool                           bAssertionFailedIn03                       = false;
    bool                           bAssertionFailedIn04                       = false;
    bool                           bAssertionFailedIn05                       = false;
    bool                           bAssertionFailedIn06                       = false;
    bool                           bAssertionFailedIn07                       = false;
    bool                           bAssertionFailedIn08                       = false;
    bool                           bAssertionFailedIn09                       = false;
    bool                           bAssertionFailedIn10                       = false;
    bool                           bAssertionFailedIn11                       = false;
    bool                           bAssertionFailedIn12                       = false;
    bool                           bAssertionFailedIn13                       = false;
    bool                           bAssertionFailedIn14                       = false;
    bool                           bAssertionFailedIn15                       = false;
    bool                           bAssertionFailedIn16                       = false;
    bool                           bAssertionFailedIn17                       = false;
    bool                           bAssertionFailedIn18                       = false;
    bool                           bAssertionFailedIn19                       = false;
    bool                           bAssertionFailedIn20                       = false;

    pointer_uint_q                 u                                          = 0;


	// [Execution]

    QStackAllocator               stackAllocator01( VALID_PREALLOCATION_SIZE );
    QStackAllocator               stackAllocator02( VALID_PREALLOCATION_SIZE );
    QStackAllocator               stackAllocator03( VALID_PREALLOCATION_SIZE );
    QStackAllocator               stackAllocator04( VALID_PREALLOCATION_SIZE );
    QStackAllocator               stackAllocator05( VALID_PREALLOCATION_SIZE, QAlignment(VALID_PREALLOCATION_ALIGNMENT_VALUE01) );
    QStackAllocator               stackAllocator06( VALID_PREALLOCATION_SIZE, QAlignment(VALID_PREALLOCATION_ALIGNMENT_VALUE01) );
    QStackAllocator               stackAllocator07( VALID_PREALLOCATION_SIZE, QAlignment(VALID_PREALLOCATION_ALIGNMENT_VALUE01) );
    QStackAllocator               stackAllocator08( VALID_PREALLOCATION_SIZE, QAlignment(VALID_PREALLOCATION_ALIGNMENT_VALUE01) );
    QStackAllocator               stackAllocator09( VALID_PREALLOCATION_SIZE, QAlignment(VALID_PREALLOCATION_ALIGNMENT_VALUE02) );
    QStackAllocator               stackAllocator10( VALID_PREALLOCATION_SIZE, QAlignment(VALID_PREALLOCATION_ALIGNMENT_VALUE02) );
    QStackAllocator               stackAllocator11( VALID_PREALLOCATION_SIZE, QAlignment(VALID_PREALLOCATION_ALIGNMENT_VALUE02) );
    QStackAllocator               stackAllocator12( VALID_PREALLOCATION_SIZE, QAlignment(VALID_PREALLOCATION_ALIGNMENT_VALUE02) );
    QStackAllocator               stackAllocator13( VALID_PREALLOCATION_SIZE, QAlignment(VALID_PREALLOCATION_ALIGNMENT_VALUE03) );
    QStackAllocator               stackAllocator14( VALID_PREALLOCATION_SIZE, QAlignment(VALID_PREALLOCATION_ALIGNMENT_VALUE03) );
    QStackAllocator               stackAllocator15( VALID_PREALLOCATION_SIZE, QAlignment(VALID_PREALLOCATION_ALIGNMENT_VALUE03) );
    QStackAllocator               stackAllocator16( VALID_PREALLOCATION_SIZE, QAlignment(VALID_PREALLOCATION_ALIGNMENT_VALUE03) );
    QStackAllocator               stackAllocator17( VALID_PREALLOCATION_SIZE, QAlignment(VALID_PREALLOCATION_ALIGNMENT_VALUE04) );
    QStackAllocator               stackAllocator18( VALID_PREALLOCATION_SIZE, QAlignment(VALID_PREALLOCATION_ALIGNMENT_VALUE04) );
    QStackAllocator               stackAllocator19( VALID_PREALLOCATION_SIZE, QAlignment(VALID_PREALLOCATION_ALIGNMENT_VALUE04) );
    QStackAllocator               stackAllocator20( VALID_PREALLOCATION_SIZE, QAlignment(VALID_PREALLOCATION_ALIGNMENT_VALUE04) );

    stackAllocator01.Allocate( VALID_ALLOCATION_SIZE, QAlignment(VALID_ALLOCATION_ALIGNMENT_VALUE01) );
    stackAllocator02.Allocate( VALID_ALLOCATION_SIZE, QAlignment(VALID_ALLOCATION_ALIGNMENT_VALUE02) );
    stackAllocator03.Allocate( VALID_ALLOCATION_SIZE, QAlignment(VALID_ALLOCATION_ALIGNMENT_VALUE03) );
    stackAllocator04.Allocate( VALID_ALLOCATION_SIZE, QAlignment(VALID_ALLOCATION_ALIGNMENT_VALUE04) );
    stackAllocator05.Allocate( VALID_ALLOCATION_SIZE, QAlignment(VALID_ALLOCATION_ALIGNMENT_VALUE01) );
    stackAllocator06.Allocate( VALID_ALLOCATION_SIZE, QAlignment(VALID_ALLOCATION_ALIGNMENT_VALUE02) );
    stackAllocator07.Allocate( VALID_ALLOCATION_SIZE, QAlignment(VALID_ALLOCATION_ALIGNMENT_VALUE03) );
    stackAllocator08.Allocate( VALID_ALLOCATION_SIZE, QAlignment(VALID_ALLOCATION_ALIGNMENT_VALUE04) );
    stackAllocator09.Allocate( VALID_ALLOCATION_SIZE, QAlignment(VALID_ALLOCATION_ALIGNMENT_VALUE01) );
    stackAllocator10.Allocate( VALID_ALLOCATION_SIZE, QAlignment(VALID_ALLOCATION_ALIGNMENT_VALUE02) );
    stackAllocator11.Allocate( VALID_ALLOCATION_SIZE, QAlignment(VALID_ALLOCATION_ALIGNMENT_VALUE03) );
    stackAllocator12.Allocate( VALID_ALLOCATION_SIZE, QAlignment(VALID_ALLOCATION_ALIGNMENT_VALUE04) );
    stackAllocator13.Allocate( VALID_ALLOCATION_SIZE, QAlignment(VALID_ALLOCATION_ALIGNMENT_VALUE01) );
    stackAllocator14.Allocate( VALID_ALLOCATION_SIZE, QAlignment(VALID_ALLOCATION_ALIGNMENT_VALUE02) );
    stackAllocator15.Allocate( VALID_ALLOCATION_SIZE, QAlignment(VALID_ALLOCATION_ALIGNMENT_VALUE03) );
    stackAllocator16.Allocate( VALID_ALLOCATION_SIZE, QAlignment(VALID_ALLOCATION_ALIGNMENT_VALUE04) );
    stackAllocator17.Allocate( VALID_ALLOCATION_SIZE, QAlignment(VALID_ALLOCATION_ALIGNMENT_VALUE01) );
    stackAllocator18.Allocate( VALID_ALLOCATION_SIZE, QAlignment(VALID_ALLOCATION_ALIGNMENT_VALUE02) );
    stackAllocator19.Allocate( VALID_ALLOCATION_SIZE, QAlignment(VALID_ALLOCATION_ALIGNMENT_VALUE03) );
    stackAllocator20.Allocate( VALID_ALLOCATION_SIZE, QAlignment(VALID_ALLOCATION_ALIGNMENT_VALUE04) );

    QStackAllocatorWhiteBox::QMarkMocked markMocked01( (stackAllocator01.GetMark()).GetMemoryAddress() ); 
    QStackAllocatorWhiteBox::QMarkMocked markMocked02( (stackAllocator02.GetMark()).GetMemoryAddress() ); 
    QStackAllocatorWhiteBox::QMarkMocked markMocked03( (stackAllocator03.GetMark()).GetMemoryAddress() ); 
    QStackAllocatorWhiteBox::QMarkMocked markMocked04( (stackAllocator04.GetMark()).GetMemoryAddress() ); 
    QStackAllocatorWhiteBox::QMarkMocked markMocked05( (stackAllocator05.GetMark()).GetMemoryAddress() ); 
    QStackAllocatorWhiteBox::QMarkMocked markMocked06( (stackAllocator06.GetMark()).GetMemoryAddress() ); 
    QStackAllocatorWhiteBox::QMarkMocked markMocked07( (stackAllocator07.GetMark()).GetMemoryAddress() ); 
    QStackAllocatorWhiteBox::QMarkMocked markMocked08( (stackAllocator08.GetMark()).GetMemoryAddress() ); 
    QStackAllocatorWhiteBox::QMarkMocked markMocked09( (stackAllocator09.GetMark()).GetMemoryAddress() ); 
    QStackAllocatorWhiteBox::QMarkMocked markMocked10( (stackAllocator10.GetMark()).GetMemoryAddress() ); 
    QStackAllocatorWhiteBox::QMarkMocked markMocked11( (stackAllocator11.GetMark()).GetMemoryAddress() ); 
    QStackAllocatorWhiteBox::QMarkMocked markMocked12( (stackAllocator12.GetMark()).GetMemoryAddress() ); 
    QStackAllocatorWhiteBox::QMarkMocked markMocked13( (stackAllocator13.GetMark()).GetMemoryAddress() ); 
    QStackAllocatorWhiteBox::QMarkMocked markMocked14( (stackAllocator14.GetMark()).GetMemoryAddress() ); 
    QStackAllocatorWhiteBox::QMarkMocked markMocked15( (stackAllocator15.GetMark()).GetMemoryAddress() ); 
    QStackAllocatorWhiteBox::QMarkMocked markMocked16( (stackAllocator16.GetMark()).GetMemoryAddress() ); 
    QStackAllocatorWhiteBox::QMarkMocked markMocked17( (stackAllocator17.GetMark()).GetMemoryAddress() ); 
    QStackAllocatorWhiteBox::QMarkMocked markMocked18( (stackAllocator18.GetMark()).GetMemoryAddress() ); 
    QStackAllocatorWhiteBox::QMarkMocked markMocked19( (stackAllocator19.GetMark()).GetMemoryAddress() ); 
    QStackAllocatorWhiteBox::QMarkMocked markMocked20( (stackAllocator20.GetMark()).GetMemoryAddress() );

    // Sabotage of the adress.
    markMocked01.SabotageMarkToNull();
    markMocked02.SabotageMarkToNull();
    markMocked03.SabotageMarkToNull();
    markMocked04.SabotageMarkToNull();
    markMocked05.SabotageMarkToNull();
    markMocked06.SabotageMarkToNull();
    markMocked07.SabotageMarkToNull();
    markMocked08.SabotageMarkToNull();
    markMocked09.SabotageMarkToNull();
    markMocked10.SabotageMarkToNull();
    markMocked11.SabotageMarkToNull();
    markMocked12.SabotageMarkToNull();
    markMocked13.SabotageMarkToNull();
    markMocked14.SabotageMarkToNull();
    markMocked15.SabotageMarkToNull();
    markMocked16.SabotageMarkToNull();
    markMocked17.SabotageMarkToNull();
    markMocked18.SabotageMarkToNull();
    markMocked19.SabotageMarkToNull();
    markMocked20.SabotageMarkToNull();

    for (u = 1; u <= AMOUNT_CASES; ++u)
    {
        try
        {
            switch (u)
            {
                case 1:  stackAllocator01.Deallocate( markMocked01 ); break;
                case 2:  stackAllocator02.Deallocate( markMocked02 ); break;
                case 3:  stackAllocator03.Deallocate( markMocked03 ); break;
                case 4:  stackAllocator04.Deallocate( markMocked04 ); break;
                case 5:  stackAllocator05.Deallocate( markMocked05 ); break;
                case 6:  stackAllocator06.Deallocate( markMocked06 ); break;
                case 7:  stackAllocator07.Deallocate( markMocked07 ); break;
                case 8:  stackAllocator08.Deallocate( markMocked08 ); break;
                case 9:  stackAllocator09.Deallocate( markMocked09 ); break;
                case 10: stackAllocator10.Deallocate( markMocked10 ); break;
                case 11: stackAllocator11.Deallocate( markMocked11 ); break;
                case 12: stackAllocator12.Deallocate( markMocked12 ); break;
                case 13: stackAllocator13.Deallocate( markMocked13 ); break;
                case 14: stackAllocator14.Deallocate( markMocked14 ); break;
                case 15: stackAllocator15.Deallocate( markMocked15 ); break;
                case 16: stackAllocator16.Deallocate( markMocked16 ); break;
                case 17: stackAllocator17.Deallocate( markMocked17 ); break;
                case 18: stackAllocator18.Deallocate( markMocked18 ); break;
                case 19: stackAllocator19.Deallocate( markMocked19 ); break;
                case 20: stackAllocator20.Deallocate( markMocked20 ); break;
            }
        }
        catch(const QAssertException&)
        {
            switch (u)
            {
                case 1:
                    if (false == bAssertionFailedIn01)
                    {
                        bAssertionFailedIn01 = true;
                    }
                break;
                case 2:
                    if (false == bAssertionFailedIn02)
                    {
                        bAssertionFailedIn02 = true;
                    }
                break;
                case 3:
                    if (false == bAssertionFailedIn03)
                    {
                        bAssertionFailedIn03 = true;
                    }
                break;
                case 4:
                    if (false == bAssertionFailedIn04)
                    {
                        bAssertionFailedIn04 = true;
                    }
                break;
                case 5:
                    if (false == bAssertionFailedIn05)
                    {
                        bAssertionFailedIn05 = true;
                    }
                break;

                case 6:
                    if (false == bAssertionFailedIn06)
                    {
                        bAssertionFailedIn06 = true;
                    }
                break;
                case 7:
                    if (false == bAssertionFailedIn07)
                    {
                        bAssertionFailedIn07 = true;
                    }
                break;
                case 8:
                    if (false == bAssertionFailedIn08)
                    {
                        bAssertionFailedIn08 = true;
                    }
                break;
                case 9:
                    if (false == bAssertionFailedIn09)
                    {
                        bAssertionFailedIn09 = true;
                    }
                break;
                case 10:
                    if (false == bAssertionFailedIn10)
                    {
                        bAssertionFailedIn10 = true;
                    }
                break;
                case 11:
                    if (false == bAssertionFailedIn11)
                    {
                        bAssertionFailedIn11 = true;
                    }
                break;
                case 12:
                    if (false == bAssertionFailedIn12)
                    {
                        bAssertionFailedIn12 = true;
                    }
                break;
                case 13:
                    if (false == bAssertionFailedIn13)
                    {
                        bAssertionFailedIn13 = true;
                    }
                break;
                case 14:
                    if (false == bAssertionFailedIn14)
                    {
                        bAssertionFailedIn14 = true;
                    }
                break;
                case 15:
                    if (false == bAssertionFailedIn15)
                    {
                        bAssertionFailedIn15 = true;
                    }
                break;
                case 16:
                    if (false == bAssertionFailedIn16)
                    {
                        bAssertionFailedIn16 = true;
                    }
                break;
                case 17:
                    if (false == bAssertionFailedIn17)
                    {
                        bAssertionFailedIn17 = true;
                    }
                break;
                case 18:
                    if (false == bAssertionFailedIn18)
                    {
                        bAssertionFailedIn18 = true;
                    }
                break;
                case 19:
                    if (false == bAssertionFailedIn19)
                    {
                        bAssertionFailedIn19 = true;
                    }
                break;
                case 20:
                    if (false == bAssertionFailedIn20)
                    {
                        bAssertionFailedIn20 = true;
                    }
                break;
            };
        }
    }


    // [Verification]

    BOOST_CHECK_EQUAL(bAssertionFailedIn01, ASSERTION_FAILED);
    BOOST_CHECK_EQUAL(bAssertionFailedIn02, ASSERTION_FAILED);
    BOOST_CHECK_EQUAL(bAssertionFailedIn03, ASSERTION_FAILED);
    BOOST_CHECK_EQUAL(bAssertionFailedIn04, ASSERTION_FAILED);
    BOOST_CHECK_EQUAL(bAssertionFailedIn05, ASSERTION_FAILED);
    BOOST_CHECK_EQUAL(bAssertionFailedIn06, ASSERTION_FAILED);
    BOOST_CHECK_EQUAL(bAssertionFailedIn07, ASSERTION_FAILED);
    BOOST_CHECK_EQUAL(bAssertionFailedIn08, ASSERTION_FAILED);
    BOOST_CHECK_EQUAL(bAssertionFailedIn09, ASSERTION_FAILED);
    BOOST_CHECK_EQUAL(bAssertionFailedIn10, ASSERTION_FAILED);
    BOOST_CHECK_EQUAL(bAssertionFailedIn11, ASSERTION_FAILED);
    BOOST_CHECK_EQUAL(bAssertionFailedIn12, ASSERTION_FAILED);
    BOOST_CHECK_EQUAL(bAssertionFailedIn13, ASSERTION_FAILED);
    BOOST_CHECK_EQUAL(bAssertionFailedIn14, ASSERTION_FAILED);
    BOOST_CHECK_EQUAL(bAssertionFailedIn15, ASSERTION_FAILED);
    BOOST_CHECK_EQUAL(bAssertionFailedIn16, ASSERTION_FAILED);
    BOOST_CHECK_EQUAL(bAssertionFailedIn17, ASSERTION_FAILED);
    BOOST_CHECK_EQUAL(bAssertionFailedIn18, ASSERTION_FAILED);
    BOOST_CHECK_EQUAL(bAssertionFailedIn19, ASSERTION_FAILED);
    BOOST_CHECK_EQUAL(bAssertionFailedIn20, ASSERTION_FAILED);
}

/// <summary>
/// Checks that an assertion fails when the passed mark -for rolling the stack top back to a certain address-
/// is lesser than the stack base of the stack allocator.
/// </summary>
QTEST_CASE(Deallocate2_AssertionFailsWhenMarkIsLesserThanStackBase_Test)
{
    // [Preparation]

    const bool                     ASSERTION_FAILED                           = true;
    const pointer_uint_q           AMOUNT_CASES                               = 25;

    const pointer_uint_q           VALID_PREALLOCATION_SIZE                   = 64;
    const pointer_uint_q           VALID_ALLOCATION_SIZE                      = 32;

    const pointer_uint_q           VALID_PREALLOCATION_ALIGNMENT_VALUE01      = 2;
    const pointer_uint_q           VALID_PREALLOCATION_ALIGNMENT_VALUE02      = 4;
    const pointer_uint_q           VALID_PREALLOCATION_ALIGNMENT_VALUE03      = 8;
    const pointer_uint_q           VALID_PREALLOCATION_ALIGNMENT_VALUE04      = 16;

    const pointer_uint_q           VALID_ALLOCATION_ALIGNMENT_VALUE01         = 2;
    const pointer_uint_q           VALID_ALLOCATION_ALIGNMENT_VALUE02         = 4;
    const pointer_uint_q           VALID_ALLOCATION_ALIGNMENT_VALUE03         = 8;
    const pointer_uint_q           VALID_ALLOCATION_ALIGNMENT_VALUE04         = 16;

    bool                           bAssertionFailedIn01                       = false;
    bool                           bAssertionFailedIn02                       = false;
    bool                           bAssertionFailedIn03                       = false;
    bool                           bAssertionFailedIn04                       = false;
    bool                           bAssertionFailedIn05                       = false;
    bool                           bAssertionFailedIn06                       = false;
    bool                           bAssertionFailedIn07                       = false;
    bool                           bAssertionFailedIn08                       = false;
    bool                           bAssertionFailedIn09                       = false;
    bool                           bAssertionFailedIn10                       = false;
    bool                           bAssertionFailedIn11                       = false;
    bool                           bAssertionFailedIn12                       = false;
    bool                           bAssertionFailedIn13                       = false;
    bool                           bAssertionFailedIn14                       = false;
    bool                           bAssertionFailedIn15                       = false;
    bool                           bAssertionFailedIn16                       = false;
    bool                           bAssertionFailedIn17                       = false;
    bool                           bAssertionFailedIn18                       = false;
    bool                           bAssertionFailedIn19                       = false;
    bool                           bAssertionFailedIn20                       = false;
    bool                           bAssertionFailedIn21                       = false;
    bool                           bAssertionFailedIn22                       = false;
    bool                           bAssertionFailedIn23                       = false;
    bool                           bAssertionFailedIn24                       = false;
    bool                           bAssertionFailedIn25                       = false;

    pointer_uint_q                 u                                          = 0;


	// [Execution]

    QStackAllocatorWhiteBox        stackAllocatorWhiteBox01( VALID_PREALLOCATION_SIZE );
    QStackAllocatorWhiteBox        stackAllocatorWhiteBox02( VALID_PREALLOCATION_SIZE );
    QStackAllocatorWhiteBox        stackAllocatorWhiteBox03( VALID_PREALLOCATION_SIZE );
    QStackAllocatorWhiteBox        stackAllocatorWhiteBox04( VALID_PREALLOCATION_SIZE );
    QStackAllocatorWhiteBox        stackAllocatorWhiteBox05( VALID_PREALLOCATION_SIZE );
    QStackAllocatorWhiteBox        stackAllocatorWhiteBox06( VALID_PREALLOCATION_SIZE, QAlignment(VALID_PREALLOCATION_ALIGNMENT_VALUE01) );
    QStackAllocatorWhiteBox        stackAllocatorWhiteBox07( VALID_PREALLOCATION_SIZE, QAlignment(VALID_PREALLOCATION_ALIGNMENT_VALUE01) );
    QStackAllocatorWhiteBox        stackAllocatorWhiteBox08( VALID_PREALLOCATION_SIZE, QAlignment(VALID_PREALLOCATION_ALIGNMENT_VALUE01) );
    QStackAllocatorWhiteBox        stackAllocatorWhiteBox09( VALID_PREALLOCATION_SIZE, QAlignment(VALID_PREALLOCATION_ALIGNMENT_VALUE01) );
    QStackAllocatorWhiteBox        stackAllocatorWhiteBox10( VALID_PREALLOCATION_SIZE, QAlignment(VALID_PREALLOCATION_ALIGNMENT_VALUE01) );
    QStackAllocatorWhiteBox        stackAllocatorWhiteBox11( VALID_PREALLOCATION_SIZE, QAlignment(VALID_PREALLOCATION_ALIGNMENT_VALUE02) );
    QStackAllocatorWhiteBox        stackAllocatorWhiteBox12( VALID_PREALLOCATION_SIZE, QAlignment(VALID_PREALLOCATION_ALIGNMENT_VALUE02) );
    QStackAllocatorWhiteBox        stackAllocatorWhiteBox13( VALID_PREALLOCATION_SIZE, QAlignment(VALID_PREALLOCATION_ALIGNMENT_VALUE02) );
    QStackAllocatorWhiteBox        stackAllocatorWhiteBox14( VALID_PREALLOCATION_SIZE, QAlignment(VALID_PREALLOCATION_ALIGNMENT_VALUE02) );
    QStackAllocatorWhiteBox        stackAllocatorWhiteBox15( VALID_PREALLOCATION_SIZE, QAlignment(VALID_PREALLOCATION_ALIGNMENT_VALUE02) );
    QStackAllocatorWhiteBox        stackAllocatorWhiteBox16( VALID_PREALLOCATION_SIZE, QAlignment(VALID_PREALLOCATION_ALIGNMENT_VALUE03) );
    QStackAllocatorWhiteBox        stackAllocatorWhiteBox17( VALID_PREALLOCATION_SIZE, QAlignment(VALID_PREALLOCATION_ALIGNMENT_VALUE03) );
    QStackAllocatorWhiteBox        stackAllocatorWhiteBox18( VALID_PREALLOCATION_SIZE, QAlignment(VALID_PREALLOCATION_ALIGNMENT_VALUE03) );
    QStackAllocatorWhiteBox        stackAllocatorWhiteBox19( VALID_PREALLOCATION_SIZE, QAlignment(VALID_PREALLOCATION_ALIGNMENT_VALUE03) );
    QStackAllocatorWhiteBox        stackAllocatorWhiteBox20( VALID_PREALLOCATION_SIZE, QAlignment(VALID_PREALLOCATION_ALIGNMENT_VALUE03) );
    QStackAllocatorWhiteBox        stackAllocatorWhiteBox21( VALID_PREALLOCATION_SIZE, QAlignment(VALID_PREALLOCATION_ALIGNMENT_VALUE04) );
    QStackAllocatorWhiteBox        stackAllocatorWhiteBox22( VALID_PREALLOCATION_SIZE, QAlignment(VALID_PREALLOCATION_ALIGNMENT_VALUE04) );
    QStackAllocatorWhiteBox        stackAllocatorWhiteBox23( VALID_PREALLOCATION_SIZE, QAlignment(VALID_PREALLOCATION_ALIGNMENT_VALUE04) );
    QStackAllocatorWhiteBox        stackAllocatorWhiteBox24( VALID_PREALLOCATION_SIZE, QAlignment(VALID_PREALLOCATION_ALIGNMENT_VALUE04) );
    QStackAllocatorWhiteBox        stackAllocatorWhiteBox25( VALID_PREALLOCATION_SIZE, QAlignment(VALID_PREALLOCATION_ALIGNMENT_VALUE04) );

    stackAllocatorWhiteBox01.Allocate( VALID_ALLOCATION_SIZE );
    stackAllocatorWhiteBox02.Allocate( VALID_ALLOCATION_SIZE, QAlignment(VALID_ALLOCATION_ALIGNMENT_VALUE01) );
    stackAllocatorWhiteBox03.Allocate( VALID_ALLOCATION_SIZE, QAlignment(VALID_ALLOCATION_ALIGNMENT_VALUE02) );
    stackAllocatorWhiteBox04.Allocate( VALID_ALLOCATION_SIZE, QAlignment(VALID_ALLOCATION_ALIGNMENT_VALUE03) );
    stackAllocatorWhiteBox05.Allocate( VALID_ALLOCATION_SIZE, QAlignment(VALID_ALLOCATION_ALIGNMENT_VALUE04) );
    stackAllocatorWhiteBox06.Allocate( VALID_ALLOCATION_SIZE );
    stackAllocatorWhiteBox07.Allocate( VALID_ALLOCATION_SIZE, QAlignment(VALID_ALLOCATION_ALIGNMENT_VALUE01) );
    stackAllocatorWhiteBox08.Allocate( VALID_ALLOCATION_SIZE, QAlignment(VALID_ALLOCATION_ALIGNMENT_VALUE02) );
    stackAllocatorWhiteBox09.Allocate( VALID_ALLOCATION_SIZE, QAlignment(VALID_ALLOCATION_ALIGNMENT_VALUE03) );
    stackAllocatorWhiteBox10.Allocate( VALID_ALLOCATION_SIZE, QAlignment(VALID_ALLOCATION_ALIGNMENT_VALUE04) );
    stackAllocatorWhiteBox11.Allocate( VALID_ALLOCATION_SIZE );
    stackAllocatorWhiteBox12.Allocate( VALID_ALLOCATION_SIZE, QAlignment(VALID_ALLOCATION_ALIGNMENT_VALUE01) );
    stackAllocatorWhiteBox13.Allocate( VALID_ALLOCATION_SIZE, QAlignment(VALID_ALLOCATION_ALIGNMENT_VALUE02) );
    stackAllocatorWhiteBox14.Allocate( VALID_ALLOCATION_SIZE, QAlignment(VALID_ALLOCATION_ALIGNMENT_VALUE03) );
    stackAllocatorWhiteBox15.Allocate( VALID_ALLOCATION_SIZE, QAlignment(VALID_ALLOCATION_ALIGNMENT_VALUE04) );
    stackAllocatorWhiteBox16.Allocate( VALID_ALLOCATION_SIZE );
    stackAllocatorWhiteBox17.Allocate( VALID_ALLOCATION_SIZE, QAlignment(VALID_ALLOCATION_ALIGNMENT_VALUE01) );
    stackAllocatorWhiteBox18.Allocate( VALID_ALLOCATION_SIZE, QAlignment(VALID_ALLOCATION_ALIGNMENT_VALUE02) );
    stackAllocatorWhiteBox19.Allocate( VALID_ALLOCATION_SIZE, QAlignment(VALID_ALLOCATION_ALIGNMENT_VALUE03) );
    stackAllocatorWhiteBox20.Allocate( VALID_ALLOCATION_SIZE, QAlignment(VALID_ALLOCATION_ALIGNMENT_VALUE04) );
    stackAllocatorWhiteBox21.Allocate( VALID_ALLOCATION_SIZE );
    stackAllocatorWhiteBox22.Allocate( VALID_ALLOCATION_SIZE, QAlignment(VALID_ALLOCATION_ALIGNMENT_VALUE01) );
    stackAllocatorWhiteBox23.Allocate( VALID_ALLOCATION_SIZE, QAlignment(VALID_ALLOCATION_ALIGNMENT_VALUE02) );
    stackAllocatorWhiteBox24.Allocate( VALID_ALLOCATION_SIZE, QAlignment(VALID_ALLOCATION_ALIGNMENT_VALUE03) );
    stackAllocatorWhiteBox25.Allocate( VALID_ALLOCATION_SIZE, QAlignment(VALID_ALLOCATION_ALIGNMENT_VALUE04) );

    QStackAllocatorWhiteBox::QMarkMocked markMocked01( stackAllocatorWhiteBox01.GetpBase() ); 
    QStackAllocatorWhiteBox::QMarkMocked markMocked02( stackAllocatorWhiteBox02.GetpBase() ); 
    QStackAllocatorWhiteBox::QMarkMocked markMocked03( stackAllocatorWhiteBox03.GetpBase() ); 
    QStackAllocatorWhiteBox::QMarkMocked markMocked04( stackAllocatorWhiteBox04.GetpBase() ); 
    QStackAllocatorWhiteBox::QMarkMocked markMocked05( stackAllocatorWhiteBox05.GetpBase() ); 
    QStackAllocatorWhiteBox::QMarkMocked markMocked06( stackAllocatorWhiteBox06.GetpBase() ); 
    QStackAllocatorWhiteBox::QMarkMocked markMocked07( stackAllocatorWhiteBox07.GetpBase() ); 
    QStackAllocatorWhiteBox::QMarkMocked markMocked08( stackAllocatorWhiteBox08.GetpBase() ); 
    QStackAllocatorWhiteBox::QMarkMocked markMocked09( stackAllocatorWhiteBox09.GetpBase() ); 
    QStackAllocatorWhiteBox::QMarkMocked markMocked10( stackAllocatorWhiteBox10.GetpBase() ); 
    QStackAllocatorWhiteBox::QMarkMocked markMocked11( stackAllocatorWhiteBox11.GetpBase() ); 
    QStackAllocatorWhiteBox::QMarkMocked markMocked12( stackAllocatorWhiteBox12.GetpBase() ); 
    QStackAllocatorWhiteBox::QMarkMocked markMocked13( stackAllocatorWhiteBox13.GetpBase() ); 
    QStackAllocatorWhiteBox::QMarkMocked markMocked14( stackAllocatorWhiteBox14.GetpBase() ); 
    QStackAllocatorWhiteBox::QMarkMocked markMocked15( stackAllocatorWhiteBox15.GetpBase() ); 
    QStackAllocatorWhiteBox::QMarkMocked markMocked16( stackAllocatorWhiteBox16.GetpBase() ); 
    QStackAllocatorWhiteBox::QMarkMocked markMocked17( stackAllocatorWhiteBox17.GetpBase() ); 
    QStackAllocatorWhiteBox::QMarkMocked markMocked18( stackAllocatorWhiteBox18.GetpBase() ); 
    QStackAllocatorWhiteBox::QMarkMocked markMocked19( stackAllocatorWhiteBox19.GetpBase() ); 
    QStackAllocatorWhiteBox::QMarkMocked markMocked20( stackAllocatorWhiteBox20.GetpBase() ); 
    QStackAllocatorWhiteBox::QMarkMocked markMocked21( stackAllocatorWhiteBox21.GetpBase() ); 
    QStackAllocatorWhiteBox::QMarkMocked markMocked22( stackAllocatorWhiteBox22.GetpBase() ); 
    QStackAllocatorWhiteBox::QMarkMocked markMocked23( stackAllocatorWhiteBox23.GetpBase() ); 
    QStackAllocatorWhiteBox::QMarkMocked markMocked24( stackAllocatorWhiteBox24.GetpBase() ); 
    QStackAllocatorWhiteBox::QMarkMocked markMocked25( stackAllocatorWhiteBox25.GetpBase() ); 

    // Sabotage of the adress.
    markMocked01.SabotageMarkToLesserMemoryAddress();
    markMocked02.SabotageMarkToLesserMemoryAddress();
    markMocked03.SabotageMarkToLesserMemoryAddress();
    markMocked04.SabotageMarkToLesserMemoryAddress();
    markMocked05.SabotageMarkToLesserMemoryAddress();
    markMocked06.SabotageMarkToLesserMemoryAddress();
    markMocked07.SabotageMarkToLesserMemoryAddress();
    markMocked08.SabotageMarkToLesserMemoryAddress();
    markMocked09.SabotageMarkToLesserMemoryAddress();
    markMocked10.SabotageMarkToLesserMemoryAddress();
    markMocked11.SabotageMarkToLesserMemoryAddress();
    markMocked12.SabotageMarkToLesserMemoryAddress();
    markMocked13.SabotageMarkToLesserMemoryAddress();
    markMocked14.SabotageMarkToLesserMemoryAddress();
    markMocked15.SabotageMarkToLesserMemoryAddress();
    markMocked16.SabotageMarkToLesserMemoryAddress();
    markMocked17.SabotageMarkToLesserMemoryAddress();
    markMocked18.SabotageMarkToLesserMemoryAddress();
    markMocked19.SabotageMarkToLesserMemoryAddress();
    markMocked20.SabotageMarkToLesserMemoryAddress();
    markMocked21.SabotageMarkToLesserMemoryAddress();
    markMocked22.SabotageMarkToLesserMemoryAddress();
    markMocked23.SabotageMarkToLesserMemoryAddress();
    markMocked24.SabotageMarkToLesserMemoryAddress();
    markMocked25.SabotageMarkToLesserMemoryAddress();

    for (u = 1; u <= AMOUNT_CASES; ++u)
    {
        try
        {
            switch (u)
            {
                case 1:  stackAllocatorWhiteBox01.Deallocate( markMocked01 ); break;
                case 2:  stackAllocatorWhiteBox02.Deallocate( markMocked02 ); break;
                case 3:  stackAllocatorWhiteBox03.Deallocate( markMocked03 ); break;
                case 4:  stackAllocatorWhiteBox04.Deallocate( markMocked04 ); break;
                case 5:  stackAllocatorWhiteBox05.Deallocate( markMocked05 ); break;
                case 6:  stackAllocatorWhiteBox06.Deallocate( markMocked06 ); break;
                case 7:  stackAllocatorWhiteBox07.Deallocate( markMocked07 ); break;
                case 8:  stackAllocatorWhiteBox08.Deallocate( markMocked08 ); break;
                case 9:  stackAllocatorWhiteBox09.Deallocate( markMocked09 ); break;
                case 10: stackAllocatorWhiteBox10.Deallocate( markMocked10 ); break;
                case 11: stackAllocatorWhiteBox11.Deallocate( markMocked11 ); break;
                case 12: stackAllocatorWhiteBox12.Deallocate( markMocked12 ); break;
                case 13: stackAllocatorWhiteBox13.Deallocate( markMocked13 ); break;
                case 14: stackAllocatorWhiteBox14.Deallocate( markMocked14 ); break;
                case 15: stackAllocatorWhiteBox15.Deallocate( markMocked15 ); break;
                case 16: stackAllocatorWhiteBox16.Deallocate( markMocked16 ); break;
                case 17: stackAllocatorWhiteBox17.Deallocate( markMocked17 ); break;
                case 18: stackAllocatorWhiteBox18.Deallocate( markMocked18 ); break;
                case 19: stackAllocatorWhiteBox19.Deallocate( markMocked19 ); break;
                case 20: stackAllocatorWhiteBox20.Deallocate( markMocked20 ); break;
                case 21: stackAllocatorWhiteBox21.Deallocate( markMocked21 ); break;
                case 22: stackAllocatorWhiteBox22.Deallocate( markMocked22 ); break;
                case 23: stackAllocatorWhiteBox23.Deallocate( markMocked23 ); break;
                case 24: stackAllocatorWhiteBox24.Deallocate( markMocked24 ); break;
                case 25: stackAllocatorWhiteBox25.Deallocate( markMocked25 ); break;
            }
        }
        catch(const QAssertException&)
        {
            switch (u)
            {
                case 1:
                    if (false == bAssertionFailedIn01)
                    {
                        bAssertionFailedIn01 = true;
                    }
                break;
                case 2:
                    if (false == bAssertionFailedIn02)
                    {
                        bAssertionFailedIn02 = true;
                    }
                break;
                case 3:
                    if (false == bAssertionFailedIn03)
                    {
                        bAssertionFailedIn03 = true;
                    }
                break;
                case 4:
                    if (false == bAssertionFailedIn04)
                    {
                        bAssertionFailedIn04 = true;
                    }
                break;
                case 5:
                    if (false == bAssertionFailedIn05)
                    {
                        bAssertionFailedIn05 = true;
                    }
                break;
                case 6:
                    if (false == bAssertionFailedIn06)
                    {
                        bAssertionFailedIn06 = true;
                    }
                break;
                case 7:
                    if (false == bAssertionFailedIn07)
                    {
                        bAssertionFailedIn07 = true;
                    }
                break;
                case 8:
                    if (false == bAssertionFailedIn08)
                    {
                        bAssertionFailedIn08 = true;
                    }
                break;
                case 9:
                    if (false == bAssertionFailedIn09)
                    {
                        bAssertionFailedIn09 = true;
                    }
                break;
                case 10:
                    if (false == bAssertionFailedIn10)
                    {
                        bAssertionFailedIn10 = true;
                    }
                break;
                case 11:
                    if (false == bAssertionFailedIn11)
                    {
                        bAssertionFailedIn11 = true;
                    }
                break;
                case 12:
                    if (false == bAssertionFailedIn12)
                    {
                        bAssertionFailedIn12 = true;
                    }
                break;
                case 13:
                    if (false == bAssertionFailedIn13)
                    {
                        bAssertionFailedIn13 = true;
                    }
                break;
                case 14:
                    if (false == bAssertionFailedIn14)
                    {
                        bAssertionFailedIn14 = true;
                    }
                break;
                case 15:
                    if (false == bAssertionFailedIn15)
                    {
                        bAssertionFailedIn15 = true;
                    }
                break;
                case 16:
                    if (false == bAssertionFailedIn16)
                    {
                        bAssertionFailedIn16 = true;
                    }
                break;
                case 17:
                    if (false == bAssertionFailedIn17)
                    {
                        bAssertionFailedIn17 = true;
                    }
                break;
                case 18:
                    if (false == bAssertionFailedIn18)
                    {
                        bAssertionFailedIn18 = true;
                    }
                break;
                case 19:
                    if (false == bAssertionFailedIn19)
                    {
                        bAssertionFailedIn19 = true;
                    }
                break;
                case 20:
                    if (false == bAssertionFailedIn20)
                    {
                        bAssertionFailedIn20 = true;
                    }
                break;
                case 21:
                    if (false == bAssertionFailedIn21)
                    {
                        bAssertionFailedIn21 = true;
                    }
                break;
                case 22:
                    if (false == bAssertionFailedIn22)
                    {
                        bAssertionFailedIn22 = true;
                    }
                break;
                case 23:
                    if (false == bAssertionFailedIn23)
                    {
                        bAssertionFailedIn23 = true;
                    }
                break;
                case 24:
                    if (false == bAssertionFailedIn24)
                    {
                        bAssertionFailedIn24 = true;
                    }
                break;
                case 25:
                    if (false == bAssertionFailedIn25)
                    {
                        bAssertionFailedIn25 = true;
                    }
                break;
            };
        }
    }


    // [Verification]

    BOOST_CHECK_EQUAL(bAssertionFailedIn01, ASSERTION_FAILED);
    BOOST_CHECK_EQUAL(bAssertionFailedIn02, ASSERTION_FAILED);
    BOOST_CHECK_EQUAL(bAssertionFailedIn03, ASSERTION_FAILED);
    BOOST_CHECK_EQUAL(bAssertionFailedIn04, ASSERTION_FAILED);
    BOOST_CHECK_EQUAL(bAssertionFailedIn05, ASSERTION_FAILED);
    BOOST_CHECK_EQUAL(bAssertionFailedIn06, ASSERTION_FAILED);
    BOOST_CHECK_EQUAL(bAssertionFailedIn07, ASSERTION_FAILED);
    BOOST_CHECK_EQUAL(bAssertionFailedIn08, ASSERTION_FAILED);
    BOOST_CHECK_EQUAL(bAssertionFailedIn09, ASSERTION_FAILED);
    BOOST_CHECK_EQUAL(bAssertionFailedIn10, ASSERTION_FAILED);
    BOOST_CHECK_EQUAL(bAssertionFailedIn11, ASSERTION_FAILED);
    BOOST_CHECK_EQUAL(bAssertionFailedIn12, ASSERTION_FAILED);
    BOOST_CHECK_EQUAL(bAssertionFailedIn13, ASSERTION_FAILED);
    BOOST_CHECK_EQUAL(bAssertionFailedIn14, ASSERTION_FAILED);
    BOOST_CHECK_EQUAL(bAssertionFailedIn15, ASSERTION_FAILED);
    BOOST_CHECK_EQUAL(bAssertionFailedIn16, ASSERTION_FAILED);
    BOOST_CHECK_EQUAL(bAssertionFailedIn17, ASSERTION_FAILED);
    BOOST_CHECK_EQUAL(bAssertionFailedIn18, ASSERTION_FAILED);
    BOOST_CHECK_EQUAL(bAssertionFailedIn19, ASSERTION_FAILED);
    BOOST_CHECK_EQUAL(bAssertionFailedIn20, ASSERTION_FAILED);
    BOOST_CHECK_EQUAL(bAssertionFailedIn21, ASSERTION_FAILED);
    BOOST_CHECK_EQUAL(bAssertionFailedIn22, ASSERTION_FAILED);
    BOOST_CHECK_EQUAL(bAssertionFailedIn23, ASSERTION_FAILED);
    BOOST_CHECK_EQUAL(bAssertionFailedIn24, ASSERTION_FAILED);
    BOOST_CHECK_EQUAL(bAssertionFailedIn25, ASSERTION_FAILED);
}

/// <summary>
/// Checks that an assertion fails when the passed mark -for rolling the stack top back to a certain address-
/// is greater than the current stack top of the stack allocator.
/// </summary>
QTEST_CASE(Deallocate2_AssertionFailsWhenMarkIsGreaterThanStackTop_Test)
{
    // [Preparation]

    const bool                     ASSERTION_FAILED                           = true;
    const pointer_uint_q           AMOUNT_CASES                               = 25;

    const pointer_uint_q           VALID_PREALLOCATION_SIZE                   = 64;
    const pointer_uint_q           VALID_ALLOCATION_SIZE                      = 32;

    const pointer_uint_q           VALID_PREALLOCATION_ALIGNMENT_VALUE01      = 2;
    const pointer_uint_q           VALID_PREALLOCATION_ALIGNMENT_VALUE02      = 4;
    const pointer_uint_q           VALID_PREALLOCATION_ALIGNMENT_VALUE03      = 8;
    const pointer_uint_q           VALID_PREALLOCATION_ALIGNMENT_VALUE04      = 16;

    bool                           bAssertionFailedIn01                       = false;
    bool                           bAssertionFailedIn02                       = false;
    bool                           bAssertionFailedIn03                       = false;
    bool                           bAssertionFailedIn04                       = false;
    bool                           bAssertionFailedIn05                       = false;
    bool                           bAssertionFailedIn06                       = false;
    bool                           bAssertionFailedIn07                       = false;
    bool                           bAssertionFailedIn08                       = false;
    bool                           bAssertionFailedIn09                       = false;
    bool                           bAssertionFailedIn10                       = false;
    bool                           bAssertionFailedIn11                       = false;
    bool                           bAssertionFailedIn12                       = false;
    bool                           bAssertionFailedIn13                       = false;
    bool                           bAssertionFailedIn14                       = false;
    bool                           bAssertionFailedIn15                       = false;
    bool                           bAssertionFailedIn16                       = false;
    bool                           bAssertionFailedIn17                       = false;
    bool                           bAssertionFailedIn18                       = false;
    bool                           bAssertionFailedIn19                       = false;
    bool                           bAssertionFailedIn20                       = false;
    bool                           bAssertionFailedIn21                       = false;
    bool                           bAssertionFailedIn22                       = false;
    bool                           bAssertionFailedIn23                       = false;
    bool                           bAssertionFailedIn24                       = false;
    bool                           bAssertionFailedIn25                       = false;

    pointer_uint_q                 u                                          = 0;


	// [Execution]

    QStackAllocator              stackAllocator01( VALID_PREALLOCATION_SIZE );
    QStackAllocator              stackAllocator02( VALID_PREALLOCATION_SIZE );
    QStackAllocator              stackAllocator03( VALID_PREALLOCATION_SIZE );
    QStackAllocator              stackAllocator04( VALID_PREALLOCATION_SIZE );
    QStackAllocator              stackAllocator05( VALID_PREALLOCATION_SIZE );
    QStackAllocator              stackAllocator06( VALID_PREALLOCATION_SIZE, QAlignment(VALID_PREALLOCATION_ALIGNMENT_VALUE01) );
    QStackAllocator              stackAllocator07( VALID_PREALLOCATION_SIZE, QAlignment(VALID_PREALLOCATION_ALIGNMENT_VALUE01) );
    QStackAllocator              stackAllocator08( VALID_PREALLOCATION_SIZE, QAlignment(VALID_PREALLOCATION_ALIGNMENT_VALUE01) );
    QStackAllocator              stackAllocator09( VALID_PREALLOCATION_SIZE, QAlignment(VALID_PREALLOCATION_ALIGNMENT_VALUE01) );
    QStackAllocator              stackAllocator10( VALID_PREALLOCATION_SIZE, QAlignment(VALID_PREALLOCATION_ALIGNMENT_VALUE01) );
    QStackAllocator              stackAllocator11( VALID_PREALLOCATION_SIZE, QAlignment(VALID_PREALLOCATION_ALIGNMENT_VALUE02) );
    QStackAllocator              stackAllocator12( VALID_PREALLOCATION_SIZE, QAlignment(VALID_PREALLOCATION_ALIGNMENT_VALUE02) );
    QStackAllocator              stackAllocator13( VALID_PREALLOCATION_SIZE, QAlignment(VALID_PREALLOCATION_ALIGNMENT_VALUE02) );
    QStackAllocator              stackAllocator14( VALID_PREALLOCATION_SIZE, QAlignment(VALID_PREALLOCATION_ALIGNMENT_VALUE02) );
    QStackAllocator              stackAllocator15( VALID_PREALLOCATION_SIZE, QAlignment(VALID_PREALLOCATION_ALIGNMENT_VALUE02) );
    QStackAllocator              stackAllocator16( VALID_PREALLOCATION_SIZE, QAlignment(VALID_PREALLOCATION_ALIGNMENT_VALUE03) );
    QStackAllocator              stackAllocator17( VALID_PREALLOCATION_SIZE, QAlignment(VALID_PREALLOCATION_ALIGNMENT_VALUE03) );
    QStackAllocator              stackAllocator18( VALID_PREALLOCATION_SIZE, QAlignment(VALID_PREALLOCATION_ALIGNMENT_VALUE03) );
    QStackAllocator              stackAllocator19( VALID_PREALLOCATION_SIZE, QAlignment(VALID_PREALLOCATION_ALIGNMENT_VALUE03) );
    QStackAllocator              stackAllocator20( VALID_PREALLOCATION_SIZE, QAlignment(VALID_PREALLOCATION_ALIGNMENT_VALUE03) );
    QStackAllocator              stackAllocator21( VALID_PREALLOCATION_SIZE, QAlignment(VALID_PREALLOCATION_ALIGNMENT_VALUE04) );
    QStackAllocator              stackAllocator22( VALID_PREALLOCATION_SIZE, QAlignment(VALID_PREALLOCATION_ALIGNMENT_VALUE04) );
    QStackAllocator              stackAllocator23( VALID_PREALLOCATION_SIZE, QAlignment(VALID_PREALLOCATION_ALIGNMENT_VALUE04) );
    QStackAllocator              stackAllocator24( VALID_PREALLOCATION_SIZE, QAlignment(VALID_PREALLOCATION_ALIGNMENT_VALUE04) );
    QStackAllocator              stackAllocator25( VALID_PREALLOCATION_SIZE, QAlignment(VALID_PREALLOCATION_ALIGNMENT_VALUE04) );

    stackAllocator01.Allocate( VALID_ALLOCATION_SIZE );
    stackAllocator02.Allocate( VALID_ALLOCATION_SIZE, QAlignment(VALID_PREALLOCATION_ALIGNMENT_VALUE01) );
    stackAllocator03.Allocate( VALID_ALLOCATION_SIZE, QAlignment(VALID_PREALLOCATION_ALIGNMENT_VALUE02) );
    stackAllocator04.Allocate( VALID_ALLOCATION_SIZE, QAlignment(VALID_PREALLOCATION_ALIGNMENT_VALUE03) );
    stackAllocator05.Allocate( VALID_ALLOCATION_SIZE, QAlignment(VALID_PREALLOCATION_ALIGNMENT_VALUE04) );
    stackAllocator06.Allocate( VALID_ALLOCATION_SIZE );
    stackAllocator07.Allocate( VALID_ALLOCATION_SIZE, QAlignment(VALID_PREALLOCATION_ALIGNMENT_VALUE01) );
    stackAllocator08.Allocate( VALID_ALLOCATION_SIZE, QAlignment(VALID_PREALLOCATION_ALIGNMENT_VALUE02) );
    stackAllocator09.Allocate( VALID_ALLOCATION_SIZE, QAlignment(VALID_PREALLOCATION_ALIGNMENT_VALUE03) );
    stackAllocator10.Allocate( VALID_ALLOCATION_SIZE, QAlignment(VALID_PREALLOCATION_ALIGNMENT_VALUE04) );
    stackAllocator11.Allocate( VALID_ALLOCATION_SIZE );
    stackAllocator12.Allocate( VALID_ALLOCATION_SIZE, QAlignment(VALID_PREALLOCATION_ALIGNMENT_VALUE01) );
    stackAllocator13.Allocate( VALID_ALLOCATION_SIZE, QAlignment(VALID_PREALLOCATION_ALIGNMENT_VALUE02) );
    stackAllocator14.Allocate( VALID_ALLOCATION_SIZE, QAlignment(VALID_PREALLOCATION_ALIGNMENT_VALUE03) );
    stackAllocator15.Allocate( VALID_ALLOCATION_SIZE, QAlignment(VALID_PREALLOCATION_ALIGNMENT_VALUE04) );
    stackAllocator16.Allocate( VALID_ALLOCATION_SIZE );
    stackAllocator17.Allocate( VALID_ALLOCATION_SIZE, QAlignment(VALID_PREALLOCATION_ALIGNMENT_VALUE01) );
    stackAllocator18.Allocate( VALID_ALLOCATION_SIZE, QAlignment(VALID_PREALLOCATION_ALIGNMENT_VALUE02) );
    stackAllocator19.Allocate( VALID_ALLOCATION_SIZE, QAlignment(VALID_PREALLOCATION_ALIGNMENT_VALUE03) );
    stackAllocator20.Allocate( VALID_ALLOCATION_SIZE, QAlignment(VALID_PREALLOCATION_ALIGNMENT_VALUE04) );
    stackAllocator21.Allocate( VALID_ALLOCATION_SIZE );
    stackAllocator22.Allocate( VALID_ALLOCATION_SIZE, QAlignment(VALID_PREALLOCATION_ALIGNMENT_VALUE01) );
    stackAllocator23.Allocate( VALID_ALLOCATION_SIZE, QAlignment(VALID_PREALLOCATION_ALIGNMENT_VALUE02) );
    stackAllocator24.Allocate( VALID_ALLOCATION_SIZE, QAlignment(VALID_PREALLOCATION_ALIGNMENT_VALUE03) );
    stackAllocator25.Allocate( VALID_ALLOCATION_SIZE, QAlignment(VALID_PREALLOCATION_ALIGNMENT_VALUE04) );

    QStackAllocatorWhiteBox::QMarkMocked markMocked01( (stackAllocator01.GetMark()).GetMemoryAddress() ); 
    QStackAllocatorWhiteBox::QMarkMocked markMocked02( (stackAllocator02.GetMark()).GetMemoryAddress() ); 
    QStackAllocatorWhiteBox::QMarkMocked markMocked03( (stackAllocator03.GetMark()).GetMemoryAddress() ); 
    QStackAllocatorWhiteBox::QMarkMocked markMocked04( (stackAllocator04.GetMark()).GetMemoryAddress() ); 
    QStackAllocatorWhiteBox::QMarkMocked markMocked05( (stackAllocator05.GetMark()).GetMemoryAddress() ); 
    QStackAllocatorWhiteBox::QMarkMocked markMocked06( (stackAllocator06.GetMark()).GetMemoryAddress() ); 
    QStackAllocatorWhiteBox::QMarkMocked markMocked07( (stackAllocator07.GetMark()).GetMemoryAddress() ); 
    QStackAllocatorWhiteBox::QMarkMocked markMocked08( (stackAllocator08.GetMark()).GetMemoryAddress() ); 
    QStackAllocatorWhiteBox::QMarkMocked markMocked09( (stackAllocator09.GetMark()).GetMemoryAddress() ); 
    QStackAllocatorWhiteBox::QMarkMocked markMocked10( (stackAllocator10.GetMark()).GetMemoryAddress() ); 
    QStackAllocatorWhiteBox::QMarkMocked markMocked11( (stackAllocator11.GetMark()).GetMemoryAddress() ); 
    QStackAllocatorWhiteBox::QMarkMocked markMocked12( (stackAllocator12.GetMark()).GetMemoryAddress() ); 
    QStackAllocatorWhiteBox::QMarkMocked markMocked13( (stackAllocator13.GetMark()).GetMemoryAddress() ); 
    QStackAllocatorWhiteBox::QMarkMocked markMocked14( (stackAllocator14.GetMark()).GetMemoryAddress() ); 
    QStackAllocatorWhiteBox::QMarkMocked markMocked15( (stackAllocator15.GetMark()).GetMemoryAddress() ); 
    QStackAllocatorWhiteBox::QMarkMocked markMocked16( (stackAllocator16.GetMark()).GetMemoryAddress() ); 
    QStackAllocatorWhiteBox::QMarkMocked markMocked17( (stackAllocator17.GetMark()).GetMemoryAddress() ); 
    QStackAllocatorWhiteBox::QMarkMocked markMocked18( (stackAllocator18.GetMark()).GetMemoryAddress() ); 
    QStackAllocatorWhiteBox::QMarkMocked markMocked19( (stackAllocator19.GetMark()).GetMemoryAddress() ); 
    QStackAllocatorWhiteBox::QMarkMocked markMocked20( (stackAllocator20.GetMark()).GetMemoryAddress() ); 
    QStackAllocatorWhiteBox::QMarkMocked markMocked21( (stackAllocator21.GetMark()).GetMemoryAddress() ); 
    QStackAllocatorWhiteBox::QMarkMocked markMocked22( (stackAllocator22.GetMark()).GetMemoryAddress() ); 
    QStackAllocatorWhiteBox::QMarkMocked markMocked23( (stackAllocator23.GetMark()).GetMemoryAddress() ); 
    QStackAllocatorWhiteBox::QMarkMocked markMocked24( (stackAllocator24.GetMark()).GetMemoryAddress() ); 
    QStackAllocatorWhiteBox::QMarkMocked markMocked25( (stackAllocator25.GetMark()).GetMemoryAddress() );

    // Sabotage of the adress.
    markMocked01.SabotageMarkToGreaterMemoryAddress();
    markMocked02.SabotageMarkToGreaterMemoryAddress();
    markMocked03.SabotageMarkToGreaterMemoryAddress();
    markMocked04.SabotageMarkToGreaterMemoryAddress();
    markMocked05.SabotageMarkToGreaterMemoryAddress();
    markMocked06.SabotageMarkToGreaterMemoryAddress();
    markMocked07.SabotageMarkToGreaterMemoryAddress();
    markMocked08.SabotageMarkToGreaterMemoryAddress();
    markMocked09.SabotageMarkToGreaterMemoryAddress();
    markMocked10.SabotageMarkToGreaterMemoryAddress();
    markMocked11.SabotageMarkToGreaterMemoryAddress();
    markMocked12.SabotageMarkToGreaterMemoryAddress();
    markMocked13.SabotageMarkToGreaterMemoryAddress();
    markMocked14.SabotageMarkToGreaterMemoryAddress();
    markMocked15.SabotageMarkToGreaterMemoryAddress();
    markMocked16.SabotageMarkToGreaterMemoryAddress();
    markMocked17.SabotageMarkToGreaterMemoryAddress();
    markMocked18.SabotageMarkToGreaterMemoryAddress();
    markMocked19.SabotageMarkToGreaterMemoryAddress();
    markMocked20.SabotageMarkToGreaterMemoryAddress();
    markMocked21.SabotageMarkToGreaterMemoryAddress();
    markMocked22.SabotageMarkToGreaterMemoryAddress();
    markMocked23.SabotageMarkToGreaterMemoryAddress();
    markMocked24.SabotageMarkToGreaterMemoryAddress();
    markMocked25.SabotageMarkToGreaterMemoryAddress();

    for (u = 1; u <= AMOUNT_CASES; ++u)
    {
        try
        {
            switch (u)
            {
                case 1:  stackAllocator01.Deallocate( markMocked01 ); break;
                case 2:  stackAllocator02.Deallocate( markMocked02 ); break;
                case 3:  stackAllocator03.Deallocate( markMocked03 ); break;
                case 4:  stackAllocator04.Deallocate( markMocked04 ); break;
                case 5:  stackAllocator05.Deallocate( markMocked05 ); break;
                case 6:  stackAllocator06.Deallocate( markMocked06 ); break;
                case 7:  stackAllocator07.Deallocate( markMocked07 ); break;
                case 8:  stackAllocator08.Deallocate( markMocked08 ); break;
                case 9:  stackAllocator09.Deallocate( markMocked09 ); break;
                case 10: stackAllocator10.Deallocate( markMocked10 ); break;
                case 11: stackAllocator11.Deallocate( markMocked11 ); break;
                case 12: stackAllocator12.Deallocate( markMocked12 ); break;
                case 13: stackAllocator13.Deallocate( markMocked13 ); break;
                case 14: stackAllocator14.Deallocate( markMocked14 ); break;
                case 15: stackAllocator15.Deallocate( markMocked15 ); break;
                case 16: stackAllocator16.Deallocate( markMocked16 ); break;
                case 17: stackAllocator17.Deallocate( markMocked17 ); break;
                case 18: stackAllocator18.Deallocate( markMocked18 ); break;
                case 19: stackAllocator19.Deallocate( markMocked19 ); break;
                case 20: stackAllocator20.Deallocate( markMocked20 ); break;
                case 21: stackAllocator21.Deallocate( markMocked21 ); break;
                case 22: stackAllocator22.Deallocate( markMocked22 ); break;
                case 23: stackAllocator23.Deallocate( markMocked23 ); break;
                case 24: stackAllocator24.Deallocate( markMocked24 ); break;
                case 25: stackAllocator25.Deallocate( markMocked25 ); break;
            }
        }
        catch(const QAssertException&)
        {
            switch (u)
            {
                case 1:
                    if (false == bAssertionFailedIn01)
                    {
                        bAssertionFailedIn01 = true;
                    }
                break;
                case 2:
                    if (false == bAssertionFailedIn02)
                    {
                        bAssertionFailedIn02 = true;
                    }
                break;
                case 3:
                    if (false == bAssertionFailedIn03)
                    {
                        bAssertionFailedIn03 = true;
                    }
                break;
                case 4:
                    if (false == bAssertionFailedIn04)
                    {
                        bAssertionFailedIn04 = true;
                    }
                break;
                case 5:
                    if (false == bAssertionFailedIn05)
                    {
                        bAssertionFailedIn05 = true;
                    }
                break;
                case 6:
                    if (false == bAssertionFailedIn06)
                    {
                        bAssertionFailedIn06 = true;
                    }
                break;
                case 7:
                    if (false == bAssertionFailedIn07)
                    {
                        bAssertionFailedIn07 = true;
                    }
                break;
                case 8:
                    if (false == bAssertionFailedIn08)
                    {
                        bAssertionFailedIn08 = true;
                    }
                break;
                case 9:
                    if (false == bAssertionFailedIn09)
                    {
                        bAssertionFailedIn09 = true;
                    }
                break;
                case 10:
                    if (false == bAssertionFailedIn10)
                    {
                        bAssertionFailedIn10 = true;
                    }
                break;
                case 11:
                    if (false == bAssertionFailedIn11)
                    {
                        bAssertionFailedIn11 = true;
                    }
                break;
                case 12:
                    if (false == bAssertionFailedIn12)
                    {
                        bAssertionFailedIn12 = true;
                    }
                break;
                case 13:
                    if (false == bAssertionFailedIn13)
                    {
                        bAssertionFailedIn13 = true;
                    }
                break;
                case 14:
                    if (false == bAssertionFailedIn14)
                    {
                        bAssertionFailedIn14 = true;
                    }
                break;
                case 15:
                    if (false == bAssertionFailedIn15)
                    {
                        bAssertionFailedIn15 = true;
                    }
                break;
                case 16:
                    if (false == bAssertionFailedIn16)
                    {
                        bAssertionFailedIn16 = true;
                    }
                break;
                case 17:
                    if (false == bAssertionFailedIn17)
                    {
                        bAssertionFailedIn17 = true;
                    }
                break;
                case 18:
                    if (false == bAssertionFailedIn18)
                    {
                        bAssertionFailedIn18 = true;
                    }
                break;
                case 19:
                    if (false == bAssertionFailedIn19)
                    {
                        bAssertionFailedIn19 = true;
                    }
                break;
                case 20:
                    if (false == bAssertionFailedIn20)
                    {
                        bAssertionFailedIn20 = true;
                    }
                break;
                case 21:
                    if (false == bAssertionFailedIn21)
                    {
                        bAssertionFailedIn21 = true;
                    }
                break;
                case 22:
                    if (false == bAssertionFailedIn22)
                    {
                        bAssertionFailedIn22 = true;
                    }
                break;
                case 23:
                    if (false == bAssertionFailedIn23)
                    {
                        bAssertionFailedIn23 = true;
                    }
                break;
                case 24:
                    if (false == bAssertionFailedIn24)
                    {
                        bAssertionFailedIn24 = true;
                    }
                break;
                case 25:
                    if (false == bAssertionFailedIn25)
                    {
                        bAssertionFailedIn25 = true;
                    }
                break;
            };
        }
    }


    // [Verification]

    BOOST_CHECK_EQUAL(bAssertionFailedIn01, ASSERTION_FAILED);
    BOOST_CHECK_EQUAL(bAssertionFailedIn02, ASSERTION_FAILED);
    BOOST_CHECK_EQUAL(bAssertionFailedIn03, ASSERTION_FAILED);
    BOOST_CHECK_EQUAL(bAssertionFailedIn04, ASSERTION_FAILED);
    BOOST_CHECK_EQUAL(bAssertionFailedIn05, ASSERTION_FAILED);
    BOOST_CHECK_EQUAL(bAssertionFailedIn06, ASSERTION_FAILED);
    BOOST_CHECK_EQUAL(bAssertionFailedIn07, ASSERTION_FAILED);
    BOOST_CHECK_EQUAL(bAssertionFailedIn08, ASSERTION_FAILED);
    BOOST_CHECK_EQUAL(bAssertionFailedIn09, ASSERTION_FAILED);
    BOOST_CHECK_EQUAL(bAssertionFailedIn10, ASSERTION_FAILED);
    BOOST_CHECK_EQUAL(bAssertionFailedIn11, ASSERTION_FAILED);
    BOOST_CHECK_EQUAL(bAssertionFailedIn12, ASSERTION_FAILED);
    BOOST_CHECK_EQUAL(bAssertionFailedIn13, ASSERTION_FAILED);
    BOOST_CHECK_EQUAL(bAssertionFailedIn14, ASSERTION_FAILED);
    BOOST_CHECK_EQUAL(bAssertionFailedIn15, ASSERTION_FAILED);
    BOOST_CHECK_EQUAL(bAssertionFailedIn16, ASSERTION_FAILED);
    BOOST_CHECK_EQUAL(bAssertionFailedIn17, ASSERTION_FAILED);
    BOOST_CHECK_EQUAL(bAssertionFailedIn18, ASSERTION_FAILED);
    BOOST_CHECK_EQUAL(bAssertionFailedIn19, ASSERTION_FAILED);
    BOOST_CHECK_EQUAL(bAssertionFailedIn20, ASSERTION_FAILED);
    BOOST_CHECK_EQUAL(bAssertionFailedIn21, ASSERTION_FAILED);
    BOOST_CHECK_EQUAL(bAssertionFailedIn22, ASSERTION_FAILED);
    BOOST_CHECK_EQUAL(bAssertionFailedIn23, ASSERTION_FAILED);
    BOOST_CHECK_EQUAL(bAssertionFailedIn24, ASSERTION_FAILED);
    BOOST_CHECK_EQUAL(bAssertionFailedIn25, ASSERTION_FAILED);
}

/// <summary>
/// Checks that an assertion fails when a deallocation to a mark occurs and the stack is empty.
/// </summary>
QTEST_CASE(Deallocate2_AssertionFailsWhenDeallocationToAMarkAddressOccursAndStackIsEmpty_Test)
{
    // [Preparation]

    const bool                     ASSERTION_FAILED                           = true;
    const pointer_uint_q           AMOUNT_CASES                               = 5;

    const pointer_uint_q           VALID_PREALLOCATION_SIZE                   = 64;


    bool                           bAssertionFailedIn01                       = false;
    bool                           bAssertionFailedIn02                       = false;
    bool                           bAssertionFailedIn03                       = false;
    bool                           bAssertionFailedIn04                       = false;
    bool                           bAssertionFailedIn05                       = false;

    pointer_uint_q                 u                                          = 0;
    
	// [Execution]

    QStackAllocatorWhiteBox        stackAllocator01( VALID_PREALLOCATION_SIZE );
    QStackAllocatorWhiteBox        stackAllocator02( VALID_PREALLOCATION_SIZE );
    QStackAllocatorWhiteBox        stackAllocator03( VALID_PREALLOCATION_SIZE );
    QStackAllocatorWhiteBox        stackAllocator04( VALID_PREALLOCATION_SIZE );
    QStackAllocatorWhiteBox        stackAllocator05( VALID_PREALLOCATION_SIZE );
  
    // Storing onto QMark objects the current stack top --> due to the stack is empty, they equals to each stack base.
    QStackAllocator::QMark mark01( (stackAllocator01.GetMark()).GetMemoryAddress() ); 
    QStackAllocator::QMark mark02( (stackAllocator02.GetMark()).GetMemoryAddress() ); 
    QStackAllocator::QMark mark03( (stackAllocator03.GetMark()).GetMemoryAddress() ); 
    QStackAllocator::QMark mark04( (stackAllocator04.GetMark()).GetMemoryAddress() ); 
    QStackAllocator::QMark mark05( (stackAllocator05.GetMark()).GetMemoryAddress() ); 
      
    // Deallocation --> Stack Tops are empty, so an assertion will fail.
    for (u = 1; u <= AMOUNT_CASES; ++u)
    {
        try
        {
            switch (u)
            {
                case  1: stackAllocator01.Deallocate(mark01); break;
                case  2: stackAllocator02.Deallocate(mark02); break;
                case  3: stackAllocator03.Deallocate(mark03); break;
                case  4: stackAllocator04.Deallocate(mark04); break;
                case  5: stackAllocator05.Deallocate(mark05); break;
            }
        }
        catch(const QAssertException&)
        {
            switch (u)
            {
                case 1:
                    if (false == bAssertionFailedIn01)
                    {
                        bAssertionFailedIn01 = true;
                    }
                break;
                case 2:
                    if (false == bAssertionFailedIn02)
                    {
                        bAssertionFailedIn02 = true;
                    }
                break;
                case 3:
                    if (false == bAssertionFailedIn03)
                    {
                        bAssertionFailedIn03 = true;
                    }
                break;
                case 4:
                    if (false == bAssertionFailedIn04)
                    {
                        bAssertionFailedIn04 = true;
                    }
                break;
                case 5:
                    if (false == bAssertionFailedIn05)
                    {
                        bAssertionFailedIn05 = true;
                    }
                break;
            };
        }
    }


    // [Verification]

    BOOST_CHECK_EQUAL(bAssertionFailedIn01, ASSERTION_FAILED);
    BOOST_CHECK_EQUAL(bAssertionFailedIn02, ASSERTION_FAILED);
    BOOST_CHECK_EQUAL(bAssertionFailedIn03, ASSERTION_FAILED);
    BOOST_CHECK_EQUAL(bAssertionFailedIn04, ASSERTION_FAILED);
    BOOST_CHECK_EQUAL(bAssertionFailedIn05, ASSERTION_FAILED);
}

#endif // QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that nothing happens when the stack is empty.
/// </summary>
QTEST_CASE (Clear_NothingHappensWhenTheStackIsEmptyTest)
{
    // [Preparation]

    const bool                     EXPECTED_VALUE                             = true;

    const pointer_uint_q           VALID_PREALLOCATION_SIZE                   = 32;

    const pointer_uint_q           VALID_PREALLOCATION_ALIGNMENT_VALUE01      = 2;
    const pointer_uint_q           VALID_PREALLOCATION_ALIGNMENT_VALUE02      = 4;
    const pointer_uint_q           VALID_PREALLOCATION_ALIGNMENT_VALUE03      = 8;
    const pointer_uint_q           VALID_PREALLOCATION_ALIGNMENT_VALUE04      = 16;

    void*                          pStackBaseBeforeClearIn01                  = null_q;
    void*                          pStackBaseBeforeClearIn02                  = null_q;
    void*                          pStackBaseBeforeClearIn03                  = null_q;
    void*                          pStackBaseBeforeClearIn04                  = null_q;
    void*                          pStackBaseBeforeClearIn05                  = null_q;

    void*                          pStackBaseAfterClearIn01                   = null_q;
    void*                          pStackBaseAfterClearIn02                   = null_q;
    void*                          pStackBaseAfterClearIn03                   = null_q;
    void*                          pStackBaseAfterClearIn04                   = null_q;
    void*                          pStackBaseAfterClearIn05                   = null_q;

    void*                          pPreviousBeforeClearIn01                   = null_q;
    void*                          pPreviousBeforeClearIn02                   = null_q;
    void*                          pPreviousBeforeClearIn03                   = null_q;
    void*                          pPreviousBeforeClearIn04                   = null_q;
    void*                          pPreviousBeforeClearIn05                   = null_q;

    void*                          pPreviousAfterClearIn01                    = null_q;
    void*                          pPreviousAfterClearIn02                    = null_q;
    void*                          pPreviousAfterClearIn03                    = null_q;
    void*                          pPreviousAfterClearIn04                    = null_q;
    void*                          pPreviousAfterClearIn05                    = null_q;

    bool                           bSameStackBaseIn01                         = false;
    bool                           bSameStackBaseIn02                         = false;
    bool                           bSameStackBaseIn03                         = false;
    bool                           bSameStackBaseIn04                         = false;
    bool                           bSameStackBaseIn05                         = false;

    bool                           bSamePreviousIn01                          = false;
    bool                           bSamePreviousIn02                          = false;
    bool                           bSamePreviousIn03                          = false;
    bool                           bSamePreviousIn04                          = false;
    bool                           bSamePreviousIn05                          = false;

    bool                           bSameStackTopIn01                          = false;
    bool                           bSameStackTopIn02                          = false;
    bool                           bSameStackTopIn03                          = false;
    bool                           bSameStackTopIn04                          = false;
    bool                           bSameStackTopIn05                          = false;

    bool                           bNothingChangedIn01                        = false;
    bool                           bNothingChangedIn02                        = false;
    bool                           bNothingChangedIn03                        = false;
    bool                           bNothingChangedIn04                        = false;
    bool                           bNothingChangedIn05                        = false;


    // [Execution]

    QStackAllocatorWhiteBox    stackAllocatorWhiteBox01( VALID_PREALLOCATION_SIZE );
    QStackAllocatorWhiteBox    stackAllocatorWhiteBox02( VALID_PREALLOCATION_SIZE, QAlignment(VALID_PREALLOCATION_ALIGNMENT_VALUE01) ); 
    QStackAllocatorWhiteBox    stackAllocatorWhiteBox03( VALID_PREALLOCATION_SIZE, QAlignment(VALID_PREALLOCATION_ALIGNMENT_VALUE02) ); 
    QStackAllocatorWhiteBox    stackAllocatorWhiteBox04( VALID_PREALLOCATION_SIZE, QAlignment(VALID_PREALLOCATION_ALIGNMENT_VALUE03) ); 
    QStackAllocatorWhiteBox    stackAllocatorWhiteBox05( VALID_PREALLOCATION_SIZE, QAlignment(VALID_PREALLOCATION_ALIGNMENT_VALUE04) ); 

    pStackBaseBeforeClearIn01  = stackAllocatorWhiteBox01.GetpBase();
    pStackBaseBeforeClearIn02  = stackAllocatorWhiteBox02.GetpBase();
    pStackBaseBeforeClearIn03  = stackAllocatorWhiteBox03.GetpBase();
    pStackBaseBeforeClearIn04  = stackAllocatorWhiteBox04.GetpBase();
    pStackBaseBeforeClearIn05  = stackAllocatorWhiteBox05.GetpBase();

    pPreviousBeforeClearIn01   = stackAllocatorWhiteBox01.GetpPrevious();
    pPreviousBeforeClearIn02   = stackAllocatorWhiteBox02.GetpPrevious();
    pPreviousBeforeClearIn03   = stackAllocatorWhiteBox03.GetpPrevious();
    pPreviousBeforeClearIn04   = stackAllocatorWhiteBox04.GetpPrevious();
    pPreviousBeforeClearIn05   = stackAllocatorWhiteBox05.GetpPrevious();

    // Store onto QMark objects each stack top of each stack allocator --> At this point, due to stack
    // allocators are empty, they will point to each stack base.
    QStackAllocator::QMark markBeforeClear01( (stackAllocatorWhiteBox01.GetMark()).GetMemoryAddress() ); 
    QStackAllocator::QMark markBeforeClear02( (stackAllocatorWhiteBox02.GetMark()).GetMemoryAddress() );
    QStackAllocator::QMark markBeforeClear03( (stackAllocatorWhiteBox03.GetMark()).GetMemoryAddress() );
    QStackAllocator::QMark markBeforeClear04( (stackAllocatorWhiteBox04.GetMark()).GetMemoryAddress() );
    QStackAllocator::QMark markBeforeClear05( (stackAllocatorWhiteBox05.GetMark()).GetMemoryAddress() ); 

    // Nothing will happen.
    stackAllocatorWhiteBox01.Clear();
    stackAllocatorWhiteBox02.Clear();
    stackAllocatorWhiteBox03.Clear();
    stackAllocatorWhiteBox04.Clear();
    stackAllocatorWhiteBox05.Clear();

    pStackBaseAfterClearIn01  = stackAllocatorWhiteBox01.GetpBase();
    pStackBaseAfterClearIn02  = stackAllocatorWhiteBox02.GetpBase();
    pStackBaseAfterClearIn03  = stackAllocatorWhiteBox03.GetpBase();
    pStackBaseAfterClearIn04  = stackAllocatorWhiteBox04.GetpBase();
    pStackBaseAfterClearIn05  = stackAllocatorWhiteBox05.GetpBase();

    pPreviousAfterClearIn01   = stackAllocatorWhiteBox01.GetpPrevious();
    pPreviousAfterClearIn02   = stackAllocatorWhiteBox02.GetpPrevious();
    pPreviousAfterClearIn03   = stackAllocatorWhiteBox03.GetpPrevious();
    pPreviousAfterClearIn04   = stackAllocatorWhiteBox04.GetpPrevious();
    pPreviousAfterClearIn05   = stackAllocatorWhiteBox05.GetpPrevious();
   
    // Store onto QMark objects each stack top of each stack allocator --> they will point to each stack base.
    QStackAllocator::QMark markAfterClear01( (stackAllocatorWhiteBox01.GetMark()).GetMemoryAddress() ); 
    QStackAllocator::QMark markAfterClear02( (stackAllocatorWhiteBox02.GetMark()).GetMemoryAddress() );
    QStackAllocator::QMark markAfterClear03( (stackAllocatorWhiteBox03.GetMark()).GetMemoryAddress() );
    QStackAllocator::QMark markAfterClear04( (stackAllocatorWhiteBox04.GetMark()).GetMemoryAddress() );
    QStackAllocator::QMark markAfterClear05( (stackAllocatorWhiteBox05.GetMark()).GetMemoryAddress() );


    // [Verification]

    if (pStackBaseBeforeClearIn01 == pStackBaseAfterClearIn01)
        bSameStackBaseIn01 = true;
    if (pStackBaseBeforeClearIn02 == pStackBaseAfterClearIn02)
        bSameStackBaseIn02 = true;
    if (pStackBaseBeforeClearIn02 == pStackBaseAfterClearIn02)
        bSameStackBaseIn02 = true;
    if (pStackBaseBeforeClearIn03 == pStackBaseAfterClearIn03)
        bSameStackBaseIn03 = true;
    if (pStackBaseBeforeClearIn04 == pStackBaseAfterClearIn04)
        bSameStackBaseIn04 = true;
    if (pStackBaseBeforeClearIn05 == pStackBaseAfterClearIn05)
        bSameStackBaseIn05 = true;

    if (pPreviousBeforeClearIn01 == pPreviousAfterClearIn01)
        bSamePreviousIn01 = true;
    if (pPreviousBeforeClearIn02 == pPreviousAfterClearIn02)
        bSamePreviousIn02 = true;
    if (pPreviousBeforeClearIn03 == pPreviousAfterClearIn03)
        bSamePreviousIn03 = true;
    if (pPreviousBeforeClearIn04 == pPreviousAfterClearIn04)
        bSamePreviousIn04 = true;
    if (pPreviousBeforeClearIn05 == pPreviousAfterClearIn05)
        bSamePreviousIn05 = true;

    if ( (markBeforeClear01.GetMemoryAddress()) == (markAfterClear01.GetMemoryAddress()) )
        bSameStackTopIn01 = true;
    if ( (markBeforeClear02.GetMemoryAddress()) == (markAfterClear02.GetMemoryAddress()) )
        bSameStackTopIn02 = true;
    if ( (markBeforeClear03.GetMemoryAddress()) == (markAfterClear03.GetMemoryAddress()) )
        bSameStackTopIn03 = true;
    if ( (markBeforeClear04.GetMemoryAddress()) == (markAfterClear04.GetMemoryAddress()) )
        bSameStackTopIn04 = true;
    if ( (markBeforeClear05.GetMemoryAddress()) == (markAfterClear05.GetMemoryAddress()) )
        bSameStackTopIn05 = true;

    if ( (true == bSameStackBaseIn01) && (true == bSameStackTopIn01) && (true == bSamePreviousIn01) )
        bNothingChangedIn01 = true;
    if ( (true == bSameStackBaseIn02) && (true == bSameStackTopIn02) && (true == bSamePreviousIn02) )
        bNothingChangedIn02 = true;
    if ( (true == bSameStackBaseIn03) && (true == bSameStackTopIn03) && (true == bSamePreviousIn03) )
        bNothingChangedIn03 = true;
    if ( (true == bSameStackBaseIn04) && (true == bSameStackTopIn04) && (true == bSamePreviousIn04) )
        bNothingChangedIn04 = true;
    if ( (true == bSameStackBaseIn05) && (true == bSameStackTopIn05) && (true == bSamePreviousIn05) )
        bNothingChangedIn05 = true;

    BOOST_CHECK_EQUAL(bNothingChangedIn01, EXPECTED_VALUE);
    BOOST_CHECK_EQUAL(bNothingChangedIn02, EXPECTED_VALUE);
    BOOST_CHECK_EQUAL(bNothingChangedIn03, EXPECTED_VALUE);
    BOOST_CHECK_EQUAL(bNothingChangedIn04, EXPECTED_VALUE);
    BOOST_CHECK_EQUAL(bNothingChangedIn05, EXPECTED_VALUE);
}

/// <summary>
/// Checks that all the memory blocks are deallocated.
/// </summary>
QTEST_CASE ( Clear_EntireAllocatorIsEmptied_Test )
{
    // [Preparation]
    QStackAllocator allocator(32U, QAlignment(4U));
    allocator.Allocate(4U);
    allocator.Allocate(4U);
    const pointer_uint_q EXPECTED_ALLOCATED_BYTES = 0;

    // [Execution]
    allocator.Clear();

    // [Verification]
    pointer_uint_q uAllocatedBytes = allocator.GetAllocatedBytes();
    BOOST_CHECK_EQUAL(uAllocatedBytes, EXPECTED_ALLOCATED_BYTES);
}

/// <summary>
/// Checks that new allocations start at the beginning of the internal buffer after it has been cleared.
/// </summary>
QTEST_CASE ( Clear_AllocationsStartAtBeginningOfBufferAfterClearing_Test )
{
    // [Preparation]
    QStackAllocator allocator(32U, QAlignment(4U));
    const void* EXPECTED_FIRST_POSITION = allocator.Allocate(4U);
    allocator.Allocate(4U);

    // [Execution]
    allocator.Clear();
    
    // [Verification]
    void* pAllocationPosition = allocator.Allocate(4U);
    BOOST_CHECK_EQUAL(pAllocationPosition, EXPECTED_FIRST_POSITION);
}

#if QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the sum of the sizes of all allocated memory blocks into stack allocator
/// is greater than the preallocated block size.
/// </summary>
QTEST_CASE(GetSize_AssertionFailsWhenSizeOfAllAllocatedMemoryBlocksIsGreaterThanPreallocatedBlockSize_Test)
{
    // [Preparation]

    const bool                     ASSERTION_FAILED                           = true;
    const pointer_uint_q           AMOUNT_CASES                               = 25;

    const pointer_uint_q           VALID_PREALLOCATION_SIZE                   = 64;
    const pointer_uint_q           VALID_ALLOCATION_SIZE                      = 32;

    const pointer_uint_q           VALID_PREALLOCATION_ALIGNMENT_VALUE01      = 2;
    const pointer_uint_q           VALID_PREALLOCATION_ALIGNMENT_VALUE02      = 4;
    const pointer_uint_q           VALID_PREALLOCATION_ALIGNMENT_VALUE03      = 8;
    const pointer_uint_q           VALID_PREALLOCATION_ALIGNMENT_VALUE04      = 16;

    const pointer_uint_q           INCREMENT_VALUE                            = 0X100;

    bool                           bAssertionFailedIn01                       = false;
    bool                           bAssertionFailedIn02                       = false;
    bool                           bAssertionFailedIn03                       = false;
    bool                           bAssertionFailedIn04                       = false;
    bool                           bAssertionFailedIn05                       = false;
    bool                           bAssertionFailedIn06                       = false;
    bool                           bAssertionFailedIn07                       = false;
    bool                           bAssertionFailedIn08                       = false;
    bool                           bAssertionFailedIn09                       = false;
    bool                           bAssertionFailedIn10                       = false;
    bool                           bAssertionFailedIn11                       = false;
    bool                           bAssertionFailedIn12                       = false;
    bool                           bAssertionFailedIn13                       = false;
    bool                           bAssertionFailedIn14                       = false;
    bool                           bAssertionFailedIn15                       = false;
    bool                           bAssertionFailedIn16                       = false;
    bool                           bAssertionFailedIn17                       = false;
    bool                           bAssertionFailedIn18                       = false;
    bool                           bAssertionFailedIn19                       = false;
    bool                           bAssertionFailedIn20                       = false;
    bool                           bAssertionFailedIn21                       = false;
    bool                           bAssertionFailedIn22                       = false;
    bool                           bAssertionFailedIn23                       = false;
    bool                           bAssertionFailedIn24                       = false;
    bool                           bAssertionFailedIn25                       = false;

    pointer_uint_q                 u                                          = 0;


	// [Execution]

    QStackAllocatorWhiteBox        stackAllocatorWhiteBox01( VALID_PREALLOCATION_SIZE );
    QStackAllocatorWhiteBox        stackAllocatorWhiteBox02( VALID_PREALLOCATION_SIZE );
    QStackAllocatorWhiteBox        stackAllocatorWhiteBox03( VALID_PREALLOCATION_SIZE );
    QStackAllocatorWhiteBox        stackAllocatorWhiteBox04( VALID_PREALLOCATION_SIZE );
    QStackAllocatorWhiteBox        stackAllocatorWhiteBox05( VALID_PREALLOCATION_SIZE );
    QStackAllocatorWhiteBox        stackAllocatorWhiteBox06( VALID_PREALLOCATION_SIZE, QAlignment(VALID_PREALLOCATION_ALIGNMENT_VALUE01) );
    QStackAllocatorWhiteBox        stackAllocatorWhiteBox07( VALID_PREALLOCATION_SIZE, QAlignment(VALID_PREALLOCATION_ALIGNMENT_VALUE01) );
    QStackAllocatorWhiteBox        stackAllocatorWhiteBox08( VALID_PREALLOCATION_SIZE, QAlignment(VALID_PREALLOCATION_ALIGNMENT_VALUE01) );
    QStackAllocatorWhiteBox        stackAllocatorWhiteBox09( VALID_PREALLOCATION_SIZE, QAlignment(VALID_PREALLOCATION_ALIGNMENT_VALUE01) );
    QStackAllocatorWhiteBox        stackAllocatorWhiteBox10( VALID_PREALLOCATION_SIZE, QAlignment(VALID_PREALLOCATION_ALIGNMENT_VALUE01) );
    QStackAllocatorWhiteBox        stackAllocatorWhiteBox11( VALID_PREALLOCATION_SIZE, QAlignment(VALID_PREALLOCATION_ALIGNMENT_VALUE02) );
    QStackAllocatorWhiteBox        stackAllocatorWhiteBox12( VALID_PREALLOCATION_SIZE, QAlignment(VALID_PREALLOCATION_ALIGNMENT_VALUE02) );
    QStackAllocatorWhiteBox        stackAllocatorWhiteBox13( VALID_PREALLOCATION_SIZE, QAlignment(VALID_PREALLOCATION_ALIGNMENT_VALUE02) );
    QStackAllocatorWhiteBox        stackAllocatorWhiteBox14( VALID_PREALLOCATION_SIZE, QAlignment(VALID_PREALLOCATION_ALIGNMENT_VALUE02) );
    QStackAllocatorWhiteBox        stackAllocatorWhiteBox15( VALID_PREALLOCATION_SIZE, QAlignment(VALID_PREALLOCATION_ALIGNMENT_VALUE02) );
    QStackAllocatorWhiteBox        stackAllocatorWhiteBox16( VALID_PREALLOCATION_SIZE, QAlignment(VALID_PREALLOCATION_ALIGNMENT_VALUE03) );
    QStackAllocatorWhiteBox        stackAllocatorWhiteBox17( VALID_PREALLOCATION_SIZE, QAlignment(VALID_PREALLOCATION_ALIGNMENT_VALUE03) );
    QStackAllocatorWhiteBox        stackAllocatorWhiteBox18( VALID_PREALLOCATION_SIZE, QAlignment(VALID_PREALLOCATION_ALIGNMENT_VALUE03) );
    QStackAllocatorWhiteBox        stackAllocatorWhiteBox19( VALID_PREALLOCATION_SIZE, QAlignment(VALID_PREALLOCATION_ALIGNMENT_VALUE03) );
    QStackAllocatorWhiteBox        stackAllocatorWhiteBox20( VALID_PREALLOCATION_SIZE, QAlignment(VALID_PREALLOCATION_ALIGNMENT_VALUE03) );
    QStackAllocatorWhiteBox        stackAllocatorWhiteBox21( VALID_PREALLOCATION_SIZE, QAlignment(VALID_PREALLOCATION_ALIGNMENT_VALUE04) );
    QStackAllocatorWhiteBox        stackAllocatorWhiteBox22( VALID_PREALLOCATION_SIZE, QAlignment(VALID_PREALLOCATION_ALIGNMENT_VALUE04) );
    QStackAllocatorWhiteBox        stackAllocatorWhiteBox23( VALID_PREALLOCATION_SIZE, QAlignment(VALID_PREALLOCATION_ALIGNMENT_VALUE04) );
    QStackAllocatorWhiteBox        stackAllocatorWhiteBox24( VALID_PREALLOCATION_SIZE, QAlignment(VALID_PREALLOCATION_ALIGNMENT_VALUE04) );
    QStackAllocatorWhiteBox        stackAllocatorWhiteBox25( VALID_PREALLOCATION_SIZE, QAlignment(VALID_PREALLOCATION_ALIGNMENT_VALUE04) );

    stackAllocatorWhiteBox01.Allocate( VALID_ALLOCATION_SIZE );
    stackAllocatorWhiteBox02.Allocate( VALID_ALLOCATION_SIZE, QAlignment(VALID_PREALLOCATION_ALIGNMENT_VALUE01) );
    stackAllocatorWhiteBox03.Allocate( VALID_ALLOCATION_SIZE, QAlignment(VALID_PREALLOCATION_ALIGNMENT_VALUE02) );
    stackAllocatorWhiteBox04.Allocate( VALID_ALLOCATION_SIZE, QAlignment(VALID_PREALLOCATION_ALIGNMENT_VALUE03) );
    stackAllocatorWhiteBox05.Allocate( VALID_ALLOCATION_SIZE, QAlignment(VALID_PREALLOCATION_ALIGNMENT_VALUE04) );
    stackAllocatorWhiteBox06.Allocate( VALID_ALLOCATION_SIZE );
    stackAllocatorWhiteBox07.Allocate( VALID_ALLOCATION_SIZE, QAlignment(VALID_PREALLOCATION_ALIGNMENT_VALUE01) );
    stackAllocatorWhiteBox08.Allocate( VALID_ALLOCATION_SIZE, QAlignment(VALID_PREALLOCATION_ALIGNMENT_VALUE02) );
    stackAllocatorWhiteBox09.Allocate( VALID_ALLOCATION_SIZE, QAlignment(VALID_PREALLOCATION_ALIGNMENT_VALUE03) );
    stackAllocatorWhiteBox10.Allocate( VALID_ALLOCATION_SIZE, QAlignment(VALID_PREALLOCATION_ALIGNMENT_VALUE04) );
    stackAllocatorWhiteBox11.Allocate( VALID_ALLOCATION_SIZE );
    stackAllocatorWhiteBox12.Allocate( VALID_ALLOCATION_SIZE, QAlignment(VALID_PREALLOCATION_ALIGNMENT_VALUE01) );
    stackAllocatorWhiteBox13.Allocate( VALID_ALLOCATION_SIZE, QAlignment(VALID_PREALLOCATION_ALIGNMENT_VALUE02) );
    stackAllocatorWhiteBox14.Allocate( VALID_ALLOCATION_SIZE, QAlignment(VALID_PREALLOCATION_ALIGNMENT_VALUE03) );
    stackAllocatorWhiteBox15.Allocate( VALID_ALLOCATION_SIZE, QAlignment(VALID_PREALLOCATION_ALIGNMENT_VALUE04) );
    stackAllocatorWhiteBox16.Allocate( VALID_ALLOCATION_SIZE );
    stackAllocatorWhiteBox17.Allocate( VALID_ALLOCATION_SIZE, QAlignment(VALID_PREALLOCATION_ALIGNMENT_VALUE01) );
    stackAllocatorWhiteBox18.Allocate( VALID_ALLOCATION_SIZE, QAlignment(VALID_PREALLOCATION_ALIGNMENT_VALUE02) );
    stackAllocatorWhiteBox19.Allocate( VALID_ALLOCATION_SIZE, QAlignment(VALID_PREALLOCATION_ALIGNMENT_VALUE03) );
    stackAllocatorWhiteBox20.Allocate( VALID_ALLOCATION_SIZE, QAlignment(VALID_PREALLOCATION_ALIGNMENT_VALUE04) );
    stackAllocatorWhiteBox21.Allocate( VALID_ALLOCATION_SIZE );
    stackAllocatorWhiteBox22.Allocate( VALID_ALLOCATION_SIZE, QAlignment(VALID_PREALLOCATION_ALIGNMENT_VALUE01) );
    stackAllocatorWhiteBox23.Allocate( VALID_ALLOCATION_SIZE, QAlignment(VALID_PREALLOCATION_ALIGNMENT_VALUE02) );
    stackAllocatorWhiteBox24.Allocate( VALID_ALLOCATION_SIZE, QAlignment(VALID_PREALLOCATION_ALIGNMENT_VALUE03) );
    stackAllocatorWhiteBox25.Allocate( VALID_ALLOCATION_SIZE, QAlignment(VALID_PREALLOCATION_ALIGNMENT_VALUE04) );

    // Sabotage of the allocated bytes.
    pointer_uint_q uAux = stackAllocatorWhiteBox01.GetAllocatedBytes();
    uAux               += INCREMENT_VALUE;
    stackAllocatorWhiteBox01.SetuAllocatedBytes(uAux);
    uAux                = stackAllocatorWhiteBox02.GetAllocatedBytes();
    uAux               += INCREMENT_VALUE;
    stackAllocatorWhiteBox02.SetuAllocatedBytes(uAux);  
    uAux                = stackAllocatorWhiteBox03.GetAllocatedBytes();
    uAux               += INCREMENT_VALUE;
    stackAllocatorWhiteBox03.SetuAllocatedBytes(uAux); 
    uAux                = stackAllocatorWhiteBox04.GetAllocatedBytes();
    uAux               += INCREMENT_VALUE;
    stackAllocatorWhiteBox04.SetuAllocatedBytes(uAux);
    uAux                = stackAllocatorWhiteBox05.GetAllocatedBytes();
    uAux               += INCREMENT_VALUE;
    stackAllocatorWhiteBox05.SetuAllocatedBytes(uAux); 
    uAux                = stackAllocatorWhiteBox06.GetAllocatedBytes();
    uAux               += INCREMENT_VALUE;
    stackAllocatorWhiteBox06.SetuAllocatedBytes(uAux); 
    uAux                = stackAllocatorWhiteBox07.GetAllocatedBytes();
    uAux               += INCREMENT_VALUE;
    stackAllocatorWhiteBox07.SetuAllocatedBytes(uAux); 
    uAux                = stackAllocatorWhiteBox08.GetAllocatedBytes();
    uAux               += INCREMENT_VALUE;
    stackAllocatorWhiteBox08.SetuAllocatedBytes(uAux); 
    uAux                = stackAllocatorWhiteBox09.GetAllocatedBytes();
    uAux               += INCREMENT_VALUE;
    stackAllocatorWhiteBox09.SetuAllocatedBytes(uAux); 
    uAux                = stackAllocatorWhiteBox10.GetAllocatedBytes();
    uAux               += INCREMENT_VALUE;
    stackAllocatorWhiteBox10.SetuAllocatedBytes(uAux); 
    uAux                = stackAllocatorWhiteBox11.GetAllocatedBytes();
    uAux               += INCREMENT_VALUE;
    stackAllocatorWhiteBox11.SetuAllocatedBytes(uAux); 
    uAux                = stackAllocatorWhiteBox12.GetAllocatedBytes();
    uAux               += INCREMENT_VALUE;
    stackAllocatorWhiteBox12.SetuAllocatedBytes(uAux); 
    uAux                = stackAllocatorWhiteBox13.GetAllocatedBytes();
    uAux               += INCREMENT_VALUE;
    stackAllocatorWhiteBox13.SetuAllocatedBytes(uAux); 
    uAux                = stackAllocatorWhiteBox14.GetAllocatedBytes();
    uAux               += INCREMENT_VALUE;
    stackAllocatorWhiteBox14.SetuAllocatedBytes(uAux); 
    uAux                = stackAllocatorWhiteBox15.GetAllocatedBytes();
    uAux               += INCREMENT_VALUE;
    stackAllocatorWhiteBox15.SetuAllocatedBytes(uAux); 
    uAux                = stackAllocatorWhiteBox16.GetAllocatedBytes();
    uAux               += INCREMENT_VALUE;
    stackAllocatorWhiteBox16.SetuAllocatedBytes(uAux); 
    uAux                = stackAllocatorWhiteBox17.GetAllocatedBytes();
    uAux               += INCREMENT_VALUE;
    stackAllocatorWhiteBox17.SetuAllocatedBytes(uAux); 
    uAux                = stackAllocatorWhiteBox18.GetAllocatedBytes();
    uAux               += INCREMENT_VALUE;
    stackAllocatorWhiteBox18.SetuAllocatedBytes(uAux); 
    uAux                = stackAllocatorWhiteBox19.GetAllocatedBytes();
    uAux               += INCREMENT_VALUE;
    stackAllocatorWhiteBox19.SetuAllocatedBytes(uAux); 
    uAux                = stackAllocatorWhiteBox20.GetAllocatedBytes();
    uAux               += INCREMENT_VALUE;
    stackAllocatorWhiteBox20.SetuAllocatedBytes(uAux); 
    uAux                = stackAllocatorWhiteBox21.GetAllocatedBytes();
    uAux               += INCREMENT_VALUE;
    stackAllocatorWhiteBox21.SetuAllocatedBytes(uAux); 
    uAux                = stackAllocatorWhiteBox22.GetAllocatedBytes();
    uAux               += INCREMENT_VALUE;
    stackAllocatorWhiteBox22.SetuAllocatedBytes(uAux); 
    uAux                = stackAllocatorWhiteBox23.GetAllocatedBytes();
    uAux               += INCREMENT_VALUE;
    stackAllocatorWhiteBox23.SetuAllocatedBytes(uAux); 
    uAux                = stackAllocatorWhiteBox24.GetAllocatedBytes();
    uAux               += INCREMENT_VALUE;
    stackAllocatorWhiteBox24.SetuAllocatedBytes(uAux); 
    uAux                = stackAllocatorWhiteBox25.GetAllocatedBytes();
    uAux               += INCREMENT_VALUE;
    stackAllocatorWhiteBox25.SetuAllocatedBytes(uAux); 

    uAux                = 0;

    for (u = 1; u <= AMOUNT_CASES; ++u)
    {
        try
        {
            switch (u)
            {
                case 1:  uAux = stackAllocatorWhiteBox01.GetSize(); break;
                case 2:  uAux = stackAllocatorWhiteBox02.GetSize(); break;
                case 3:  uAux = stackAllocatorWhiteBox03.GetSize(); break;
                case 4:  uAux = stackAllocatorWhiteBox04.GetSize(); break;
                case 5:  uAux = stackAllocatorWhiteBox05.GetSize(); break;
                case 6:  uAux = stackAllocatorWhiteBox05.GetSize(); break;
                case 7:  uAux = stackAllocatorWhiteBox05.GetSize(); break;
                case 8:  uAux = stackAllocatorWhiteBox05.GetSize(); break;
                case 9:  uAux = stackAllocatorWhiteBox05.GetSize(); break;
                case 10: uAux = stackAllocatorWhiteBox10.GetSize(); break;
                case 11: uAux = stackAllocatorWhiteBox11.GetSize(); break;
                case 12: uAux = stackAllocatorWhiteBox12.GetSize(); break;
                case 13: uAux = stackAllocatorWhiteBox13.GetSize(); break;
                case 14: uAux = stackAllocatorWhiteBox14.GetSize(); break;
                case 15: uAux = stackAllocatorWhiteBox15.GetSize(); break;
                case 16: uAux = stackAllocatorWhiteBox16.GetSize(); break;
                case 17: uAux = stackAllocatorWhiteBox17.GetSize(); break;
                case 18: uAux = stackAllocatorWhiteBox18.GetSize(); break;
                case 19: uAux = stackAllocatorWhiteBox19.GetSize(); break;
                case 20: uAux = stackAllocatorWhiteBox20.GetSize(); break;
                case 21: uAux = stackAllocatorWhiteBox21.GetSize(); break;
                case 22: uAux = stackAllocatorWhiteBox22.GetSize(); break;
                case 23: uAux = stackAllocatorWhiteBox23.GetSize(); break;
                case 24: uAux = stackAllocatorWhiteBox24.GetSize(); break;
                case 25: uAux = stackAllocatorWhiteBox25.GetSize(); break;
            }
        }
        catch(const QAssertException&)
        {
            switch (u)
            {
                case 1:
                    if (false == bAssertionFailedIn01)
                    {
                        bAssertionFailedIn01 = true;
                    }
                break;
                case 2:
                    if (false == bAssertionFailedIn02)
                    {
                        bAssertionFailedIn02 = true;
                    }
                break;
                case 3:
                    if (false == bAssertionFailedIn03)
                    {
                        bAssertionFailedIn03 = true;
                    }
                break;
                case 4:
                    if (false == bAssertionFailedIn04)
                    {
                        bAssertionFailedIn04 = true;
                    }
                break;
                case 5:
                    if (false == bAssertionFailedIn05)
                    {
                        bAssertionFailedIn05 = true;
                    }
                break;
                case 6:
                    if (false == bAssertionFailedIn06)
                    {
                        bAssertionFailedIn06 = true;
                    }
                break;
                case 7:
                    if (false == bAssertionFailedIn07)
                    {
                        bAssertionFailedIn07 = true;
                    }
                break;
                case 8:
                    if (false == bAssertionFailedIn08)
                    {
                        bAssertionFailedIn08 = true;
                    }
                break;
                case 9:
                    if (false == bAssertionFailedIn09)
                    {
                        bAssertionFailedIn09 = true;
                    }
                break;
                case 10:
                    if (false == bAssertionFailedIn10)
                    {
                        bAssertionFailedIn10 = true;
                    }
                break;
                case 11:
                    if (false == bAssertionFailedIn11)
                    {
                        bAssertionFailedIn11 = true;
                    }
                break;
                case 12:
                    if (false == bAssertionFailedIn12)
                    {
                        bAssertionFailedIn12 = true;
                    }
                break;
                case 13:
                    if (false == bAssertionFailedIn13)
                    {
                        bAssertionFailedIn13 = true;
                    }
                break;
                case 14:
                    if (false == bAssertionFailedIn14)
                    {
                        bAssertionFailedIn14 = true;
                    }
                break;
                case 15:
                    if (false == bAssertionFailedIn15)
                    {
                        bAssertionFailedIn15 = true;
                    }
                break;
                case 16:
                    if (false == bAssertionFailedIn16)
                    {
                        bAssertionFailedIn16 = true;
                    }
                break;
                case 17:
                    if (false == bAssertionFailedIn17)
                    {
                        bAssertionFailedIn17 = true;
                    }
                break;
                case 18:
                    if (false == bAssertionFailedIn18)
                    {
                        bAssertionFailedIn18 = true;
                    }
                break;
                case 19:
                    if (false == bAssertionFailedIn19)
                    {
                        bAssertionFailedIn19 = true;
                    }
                break;
                case 20:
                    if (false == bAssertionFailedIn20)
                    {
                        bAssertionFailedIn20 = true;
                    }
                break;
                case 21:
                    if (false == bAssertionFailedIn21)
                    {
                        bAssertionFailedIn21 = true;
                    }
                break;
                case 22:
                    if (false == bAssertionFailedIn22)
                    {
                        bAssertionFailedIn22 = true;
                    }
                break;
                case 23:
                    if (false == bAssertionFailedIn23)
                    {
                        bAssertionFailedIn23 = true;
                    }
                break;
                case 24:
                    if (false == bAssertionFailedIn24)
                    {
                        bAssertionFailedIn24 = true;
                    }
                break;
                case 25:
                    if (false == bAssertionFailedIn25)
                    {
                        bAssertionFailedIn25 = true;
                    }
                break;
            };
        }
    }


    // [Verification]

    BOOST_CHECK_EQUAL(bAssertionFailedIn01, ASSERTION_FAILED);
    BOOST_CHECK_EQUAL(bAssertionFailedIn02, ASSERTION_FAILED);
    BOOST_CHECK_EQUAL(bAssertionFailedIn03, ASSERTION_FAILED);
    BOOST_CHECK_EQUAL(bAssertionFailedIn04, ASSERTION_FAILED);
    BOOST_CHECK_EQUAL(bAssertionFailedIn05, ASSERTION_FAILED);
    BOOST_CHECK_EQUAL(bAssertionFailedIn06, ASSERTION_FAILED);
    BOOST_CHECK_EQUAL(bAssertionFailedIn07, ASSERTION_FAILED);
    BOOST_CHECK_EQUAL(bAssertionFailedIn08, ASSERTION_FAILED);
    BOOST_CHECK_EQUAL(bAssertionFailedIn09, ASSERTION_FAILED);
    BOOST_CHECK_EQUAL(bAssertionFailedIn10, ASSERTION_FAILED);
    BOOST_CHECK_EQUAL(bAssertionFailedIn11, ASSERTION_FAILED);
    BOOST_CHECK_EQUAL(bAssertionFailedIn12, ASSERTION_FAILED);
    BOOST_CHECK_EQUAL(bAssertionFailedIn13, ASSERTION_FAILED);
    BOOST_CHECK_EQUAL(bAssertionFailedIn14, ASSERTION_FAILED);
    BOOST_CHECK_EQUAL(bAssertionFailedIn15, ASSERTION_FAILED);
    BOOST_CHECK_EQUAL(bAssertionFailedIn16, ASSERTION_FAILED);
    BOOST_CHECK_EQUAL(bAssertionFailedIn17, ASSERTION_FAILED);
    BOOST_CHECK_EQUAL(bAssertionFailedIn18, ASSERTION_FAILED);
    BOOST_CHECK_EQUAL(bAssertionFailedIn19, ASSERTION_FAILED);
    BOOST_CHECK_EQUAL(bAssertionFailedIn20, ASSERTION_FAILED);
    BOOST_CHECK_EQUAL(bAssertionFailedIn21, ASSERTION_FAILED);
    BOOST_CHECK_EQUAL(bAssertionFailedIn22, ASSERTION_FAILED);
    BOOST_CHECK_EQUAL(bAssertionFailedIn23, ASSERTION_FAILED);
    BOOST_CHECK_EQUAL(bAssertionFailedIn24, ASSERTION_FAILED);
    BOOST_CHECK_EQUAL(bAssertionFailedIn25, ASSERTION_FAILED);
}

#endif // QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

#if QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the specified size for the intended memory block to be allocated is zero.
/// The alignment value for the intended memory block to be allocated is the default one.
/// </summary>
QTEST_CASE (CanAllocate1_AssertionFailsWhenSizeIsZero_Test)
{
    // [Preparation]

    const bool                 ASSERTION_FAILED                           = true;
    const pointer_uint_q       AMOUNT_CASES                               = 5;

    const pointer_uint_q       VALID_PREALLOCATION_SIZE                   = 64;

    const pointer_uint_q       VALID_PREALLOCATION_ALIGNMENT_VALUE01      = 2;
    const pointer_uint_q       VALID_PREALLOCATION_ALIGNMENT_VALUE02      = 4;
    const pointer_uint_q       VALID_PREALLOCATION_ALIGNMENT_VALUE03      = 8;
    const pointer_uint_q       VALID_PREALLOCATION_ALIGNMENT_VALUE04      = 16;

    bool                       bAssertionFailedIn01                       = false;
    bool                       bAssertionFailedIn02                       = false;
    bool                       bAssertionFailedIn03                       = false;
    bool                       bAssertionFailedIn04                       = false;
    bool                       bAssertionFailedIn05                       = false;

    pointer_uint_q             u                                          = 0;


    // [Execution]

    QStackAllocator            stackAllocator01( VALID_PREALLOCATION_SIZE );
    QStackAllocator            stackAllocator02( VALID_PREALLOCATION_SIZE, QAlignment(VALID_PREALLOCATION_ALIGNMENT_VALUE01) );
    QStackAllocator            stackAllocator03( VALID_PREALLOCATION_SIZE, QAlignment(VALID_PREALLOCATION_ALIGNMENT_VALUE02) );
    QStackAllocator            stackAllocator04( VALID_PREALLOCATION_SIZE, QAlignment(VALID_PREALLOCATION_ALIGNMENT_VALUE03) );
    QStackAllocator            stackAllocator05( VALID_PREALLOCATION_SIZE, QAlignment(VALID_PREALLOCATION_ALIGNMENT_VALUE04) );

    for (u = 1; u <= AMOUNT_CASES; ++u)
    {
        try
        {
            switch (u)
            {
                case 1:
                    stackAllocator01.CanAllocate(0);
                break;
                case 2:
                    stackAllocator02.CanAllocate(0);
                break;
                case 3:
                    stackAllocator03.CanAllocate(0);
                break;
                case 4:
                    stackAllocator04.CanAllocate(0);
                break;
                case 5:
                    stackAllocator05.CanAllocate(0);
                break;
            }
        }
        catch(const QAssertException&)
        {
            switch (u)
            {
                case 1:
                    if (false == bAssertionFailedIn01)
                    {
                        bAssertionFailedIn01 = true;
                    }
                break;
                case 2:
                    if (false == bAssertionFailedIn02)
                    {
                        bAssertionFailedIn02 = true;
                    }
                break;
                case 3:
                    if (false == bAssertionFailedIn03)
                    {
                        bAssertionFailedIn03 = true;
                    }
                break;
                case 4:
                    if (false == bAssertionFailedIn04)
                    {
                        bAssertionFailedIn04 = true;
                    }
                break;
                case 5:
                    if (false == bAssertionFailedIn05)
                    {
                        bAssertionFailedIn05 = true;
                    }
                break;
            };
        }
    }


    // [Verification]

    BOOST_CHECK_EQUAL(bAssertionFailedIn01, ASSERTION_FAILED);
    BOOST_CHECK_EQUAL(bAssertionFailedIn02, ASSERTION_FAILED);
    BOOST_CHECK_EQUAL(bAssertionFailedIn03, ASSERTION_FAILED);
    BOOST_CHECK_EQUAL(bAssertionFailedIn04, ASSERTION_FAILED);
    BOOST_CHECK_EQUAL(bAssertionFailedIn05, ASSERTION_FAILED);
}

#elif QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_DISABLED

/// <summary>
/// Checks that it returns False when the specified size for the intended memory block to be allocated is zero.
/// The alignment value for the intended memory block to be allocated is the default one.
/// </summary>
QTEST_CASE (CanAllocate1_ReturnsFalseWhenSizeIsZero_Test)
{
    // [Preparation]

    const bool                 EXPECTED_VALUE                             = false;
    const pointer_uint_q       VALID_PREALLOCATION_SIZE                   = 64;

    const pointer_uint_q       VALID_PREALLOCATION_ALIGNMENT_VALUE01      = 2;
    const pointer_uint_q       VALID_PREALLOCATION_ALIGNMENT_VALUE02      = 4;
    const pointer_uint_q       VALID_PREALLOCATION_ALIGNMENT_VALUE03      = 8;
    const pointer_uint_q       VALID_PREALLOCATION_ALIGNMENT_VALUE04      = 16;

    bool                       bCouldNotAllocateIn01                      = false;
    bool                       bCouldNotAllocateIn02                      = false;
    bool                       bCouldNotAllocateIn03                      = false;
    bool                       bCouldNotAllocateIn04                      = false;
    bool                       bCouldNotAllocateIn05                      = false;


    // [Execution]

    QStackAllocator            stackAllocator01( VALID_PREALLOCATION_SIZE );
    QStackAllocator            stackAllocator02( VALID_PREALLOCATION_SIZE, QAlignment(VALID_PREALLOCATION_ALIGNMENT_VALUE01) );
    QStackAllocator            stackAllocator03( VALID_PREALLOCATION_SIZE, QAlignment(VALID_PREALLOCATION_ALIGNMENT_VALUE02) );
    QStackAllocator            stackAllocator04( VALID_PREALLOCATION_SIZE, QAlignment(VALID_PREALLOCATION_ALIGNMENT_VALUE03) );
    QStackAllocator            stackAllocator05( VALID_PREALLOCATION_SIZE, QAlignment(VALID_PREALLOCATION_ALIGNMENT_VALUE04) );

    bCouldNotAllocateIn01 = !stackAllocator01.CanAllocate(0);
    bCouldNotAllocateIn02 = !stackAllocator02.CanAllocate(0);
    bCouldNotAllocateIn03 = !stackAllocator03.CanAllocate(0);
    bCouldNotAllocateIn04 = !stackAllocator04.CanAllocate(0);
    bCouldNotAllocateIn05 = !stackAllocator05.CanAllocate(0);


    // [Verification]

    BOOST_CHECK_EQUAL(bCouldNotAllocateIn01, EXPECTED_VALUE);
    BOOST_CHECK_EQUAL(bCouldNotAllocateIn02, EXPECTED_VALUE);
    BOOST_CHECK_EQUAL(bCouldNotAllocateIn03, EXPECTED_VALUE);
    BOOST_CHECK_EQUAL(bCouldNotAllocateIn04, EXPECTED_VALUE);
    BOOST_CHECK_EQUAL(bCouldNotAllocateIn05, EXPECTED_VALUE);
}

#endif // QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that it returns False when there is not enough space to allocate a memory block whose specified size
/// is too big for the current free space in the stack.
/// The alignment value for the intended memory block to be allocated is the default one.
/// </summary>
QTEST_CASE (CanAllocate1_ReturnsFalseWhenThereIsNotEnoughSpaceToAllocateAMemoryBlock_Test)
{
    // [Preparation]

    const bool                 EXPECTED_VALUE                             = true;

    const pointer_uint_q       VALID_PREALLOCATION_SIZE                   = 64;
    const pointer_uint_q       VALID_ALLOCATION_SIZE                      = 32;
    const pointer_uint_q       TOO_BIG_ALLOCATION_SIZE                    = 128;

    const pointer_uint_q       VALID_PREALLOCATION_ALIGNMENT_VALUE01      = 2;
    const pointer_uint_q       VALID_PREALLOCATION_ALIGNMENT_VALUE02      = 4;
    const pointer_uint_q       VALID_PREALLOCATION_ALIGNMENT_VALUE03      = 8;
    const pointer_uint_q       VALID_PREALLOCATION_ALIGNMENT_VALUE04      = 16;

    bool                       bSecondAllocationFailureIn01               = false;
    bool                       bSecondAllocationFailureIn02               = false;
    bool                       bSecondAllocationFailureIn03               = false;
    bool                       bSecondAllocationFailureIn04               = false;
    bool                       bSecondAllocationFailureIn05               = false;

    // [Execution]

    QStackAllocator            stackAllocator01( VALID_PREALLOCATION_SIZE );
    QStackAllocator            stackAllocator02( VALID_PREALLOCATION_SIZE, QAlignment(VALID_PREALLOCATION_ALIGNMENT_VALUE01) );
    QStackAllocator            stackAllocator03( VALID_PREALLOCATION_SIZE, QAlignment(VALID_PREALLOCATION_ALIGNMENT_VALUE02) );
    QStackAllocator            stackAllocator04( VALID_PREALLOCATION_SIZE, QAlignment(VALID_PREALLOCATION_ALIGNMENT_VALUE03) );
    QStackAllocator            stackAllocator05( VALID_PREALLOCATION_SIZE, QAlignment(VALID_PREALLOCATION_ALIGNMENT_VALUE04) );

    // Allocation WILL occur.
    stackAllocator01.Allocate(VALID_ALLOCATION_SIZE); 
    stackAllocator02.Allocate(VALID_ALLOCATION_SIZE);
    stackAllocator03.Allocate(VALID_ALLOCATION_SIZE);
    stackAllocator04.Allocate(VALID_ALLOCATION_SIZE);
    stackAllocator05.Allocate(VALID_ALLOCATION_SIZE);
    
    // Allocation could NOT occur.
    bSecondAllocationFailureIn01 = !stackAllocator01.CanAllocate(TOO_BIG_ALLOCATION_SIZE);
    bSecondAllocationFailureIn02 = !stackAllocator02.CanAllocate(TOO_BIG_ALLOCATION_SIZE);
    bSecondAllocationFailureIn03 = !stackAllocator03.CanAllocate(TOO_BIG_ALLOCATION_SIZE);
    bSecondAllocationFailureIn04 = !stackAllocator04.CanAllocate(TOO_BIG_ALLOCATION_SIZE);
    bSecondAllocationFailureIn05 = !stackAllocator05.CanAllocate(TOO_BIG_ALLOCATION_SIZE);


    // [Verification]

    BOOST_CHECK_EQUAL(bSecondAllocationFailureIn01, EXPECTED_VALUE);
    BOOST_CHECK_EQUAL(bSecondAllocationFailureIn02, EXPECTED_VALUE);
    BOOST_CHECK_EQUAL(bSecondAllocationFailureIn03, EXPECTED_VALUE);
    BOOST_CHECK_EQUAL(bSecondAllocationFailureIn04, EXPECTED_VALUE);
    BOOST_CHECK_EQUAL(bSecondAllocationFailureIn05, EXPECTED_VALUE);
}

/// <summary>
/// Checks that it returns True when there is enough free space yet to allocate a memory block.
/// The alignment value for the intended memory block to be allocated is the default one.
/// </summary>
QTEST_CASE (CanAllocate1_ReturnsTrueWhenThereIsEnoughSpaceYetToAllocateAMemoryBlock_Test)
{
    // [Preparation]

    const bool                 EXPECTED_VALUE                             = true;

    const pointer_uint_q       VALID_PREALLOCATION_SIZE                   = 128;
    const pointer_uint_q       VALID_ALLOCATION_SIZE01                    = 32;
    const pointer_uint_q       VALID_ALLOCATION_SIZE02                    = 16;

    const pointer_uint_q       VALID_PREALLOCATION_ALIGNMENT_VALUE01      = 2;
    const pointer_uint_q       VALID_PREALLOCATION_ALIGNMENT_VALUE02      = 4;
    const pointer_uint_q       VALID_PREALLOCATION_ALIGNMENT_VALUE03      = 8;
    const pointer_uint_q       VALID_PREALLOCATION_ALIGNMENT_VALUE04      = 16;

    bool                       bCouldAllocateAgainIn01                    = false;
    bool                       bCouldAllocateAgainIn02                    = false;
    bool                       bCouldAllocateAgainIn03                    = false;
    bool                       bCouldAllocateAgainIn04                    = false;
    bool                       bCouldAllocateAgainIn05                    = false;


    // [Execution]

    QStackAllocator            stackAllocator01( VALID_PREALLOCATION_SIZE );
    QStackAllocator            stackAllocator02( VALID_PREALLOCATION_SIZE, QAlignment(VALID_PREALLOCATION_ALIGNMENT_VALUE01) );
    QStackAllocator            stackAllocator03( VALID_PREALLOCATION_SIZE, QAlignment(VALID_PREALLOCATION_ALIGNMENT_VALUE02) );
    QStackAllocator            stackAllocator04( VALID_PREALLOCATION_SIZE, QAlignment(VALID_PREALLOCATION_ALIGNMENT_VALUE03) );
    QStackAllocator            stackAllocator05( VALID_PREALLOCATION_SIZE, QAlignment(VALID_PREALLOCATION_ALIGNMENT_VALUE04) );

    // Allocation WILL occur.
    stackAllocator01.Allocate(VALID_ALLOCATION_SIZE01); 
    stackAllocator02.Allocate(VALID_ALLOCATION_SIZE01);
    stackAllocator03.Allocate(VALID_ALLOCATION_SIZE01);
    stackAllocator04.Allocate(VALID_ALLOCATION_SIZE01);
    stackAllocator05.Allocate(VALID_ALLOCATION_SIZE01);
    
    // Allocation COULD occur as well.
    bCouldAllocateAgainIn01 = stackAllocator01.CanAllocate( VALID_ALLOCATION_SIZE02 );
    bCouldAllocateAgainIn02 = stackAllocator02.CanAllocate( VALID_ALLOCATION_SIZE02 );
    bCouldAllocateAgainIn03 = stackAllocator03.CanAllocate( VALID_ALLOCATION_SIZE02 );
    bCouldAllocateAgainIn04 = stackAllocator04.CanAllocate( VALID_ALLOCATION_SIZE02 );
    bCouldAllocateAgainIn05 = stackAllocator05.CanAllocate( VALID_ALLOCATION_SIZE02 );


    // [Verification]

    BOOST_CHECK_EQUAL(bCouldAllocateAgainIn01, EXPECTED_VALUE);
    BOOST_CHECK_EQUAL(bCouldAllocateAgainIn02, EXPECTED_VALUE);
    BOOST_CHECK_EQUAL(bCouldAllocateAgainIn03, EXPECTED_VALUE);
    BOOST_CHECK_EQUAL(bCouldAllocateAgainIn04, EXPECTED_VALUE);
    BOOST_CHECK_EQUAL(bCouldAllocateAgainIn05, EXPECTED_VALUE);
}

#if QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks than a assertion fails when the specified size for the intended memory block to be allocated is zero.
/// The alignment value for the intended memory block to be allocated is specified.
/// </summary>
QTEST_CASE (CanAllocate2_AssertionFailsWhenSizeIsZero_Test)
{
    // [Preparation]

    const bool                 ASSERTION_FAILED                           = true;
    const pointer_uint_q       AMOUNT_CASES                               = 20;

    const pointer_uint_q       VALID_PREALLOCATION_SIZE                   = 64;

    const pointer_uint_q       VALID_PREALLOCATION_ALIGNMENT_VALUE01      = 2;
    const pointer_uint_q       VALID_PREALLOCATION_ALIGNMENT_VALUE02      = 4;
    const pointer_uint_q       VALID_PREALLOCATION_ALIGNMENT_VALUE03      = 8;
    const pointer_uint_q       VALID_PREALLOCATION_ALIGNMENT_VALUE04      = 16;

    const pointer_uint_q       VALID_ALLOCATION_ALIGNMENT_VALUE01         = 2;
    const pointer_uint_q       VALID_ALLOCATION_ALIGNMENT_VALUE02         = 4;
    const pointer_uint_q       VALID_ALLOCATION_ALIGNMENT_VALUE03         = 8;
    const pointer_uint_q       VALID_ALLOCATION_ALIGNMENT_VALUE04         = 16;

    bool                       bAssertionFailedIn01                       = false;
    bool                       bAssertionFailedIn02                       = false;
    bool                       bAssertionFailedIn03                       = false;
    bool                       bAssertionFailedIn04                       = false;
    bool                       bAssertionFailedIn05                       = false;
    bool                       bAssertionFailedIn06                       = false;
    bool                       bAssertionFailedIn07                       = false;
    bool                       bAssertionFailedIn08                       = false;
    bool                       bAssertionFailedIn09                       = false;
    bool                       bAssertionFailedIn10                       = false;
    bool                       bAssertionFailedIn11                       = false;
    bool                       bAssertionFailedIn12                       = false;
    bool                       bAssertionFailedIn13                       = false;
    bool                       bAssertionFailedIn14                       = false;
    bool                       bAssertionFailedIn15                       = false;
    bool                       bAssertionFailedIn16                       = false;
    bool                       bAssertionFailedIn17                       = false;
    bool                       bAssertionFailedIn18                       = false;
    bool                       bAssertionFailedIn19                       = false;
    bool                       bAssertionFailedIn20                       = false;

    pointer_uint_q             u                                          = 0;


    // [Execution]

    QStackAllocator            stackAllocator01( VALID_PREALLOCATION_SIZE );
    QStackAllocator            stackAllocator02( VALID_PREALLOCATION_SIZE );
    QStackAllocator            stackAllocator03( VALID_PREALLOCATION_SIZE );
    QStackAllocator            stackAllocator04( VALID_PREALLOCATION_SIZE );
    QStackAllocator            stackAllocator05( VALID_PREALLOCATION_SIZE, QAlignment(VALID_PREALLOCATION_ALIGNMENT_VALUE01) );
    QStackAllocator            stackAllocator06( VALID_PREALLOCATION_SIZE, QAlignment(VALID_PREALLOCATION_ALIGNMENT_VALUE01) );
    QStackAllocator            stackAllocator07( VALID_PREALLOCATION_SIZE, QAlignment(VALID_PREALLOCATION_ALIGNMENT_VALUE01) );
    QStackAllocator            stackAllocator08( VALID_PREALLOCATION_SIZE, QAlignment(VALID_PREALLOCATION_ALIGNMENT_VALUE01) );
    QStackAllocator            stackAllocator09( VALID_PREALLOCATION_SIZE, QAlignment(VALID_PREALLOCATION_ALIGNMENT_VALUE02) );
    QStackAllocator            stackAllocator10( VALID_PREALLOCATION_SIZE, QAlignment(VALID_PREALLOCATION_ALIGNMENT_VALUE02) );
    QStackAllocator            stackAllocator11( VALID_PREALLOCATION_SIZE, QAlignment(VALID_PREALLOCATION_ALIGNMENT_VALUE02) );
    QStackAllocator            stackAllocator12( VALID_PREALLOCATION_SIZE, QAlignment(VALID_PREALLOCATION_ALIGNMENT_VALUE02) );
    QStackAllocator            stackAllocator13( VALID_PREALLOCATION_SIZE, QAlignment(VALID_PREALLOCATION_ALIGNMENT_VALUE03) );
    QStackAllocator            stackAllocator14( VALID_PREALLOCATION_SIZE, QAlignment(VALID_PREALLOCATION_ALIGNMENT_VALUE03) );
    QStackAllocator            stackAllocator15( VALID_PREALLOCATION_SIZE, QAlignment(VALID_PREALLOCATION_ALIGNMENT_VALUE03) );
    QStackAllocator            stackAllocator16( VALID_PREALLOCATION_SIZE, QAlignment(VALID_PREALLOCATION_ALIGNMENT_VALUE03) );
    QStackAllocator            stackAllocator17( VALID_PREALLOCATION_SIZE, QAlignment(VALID_PREALLOCATION_ALIGNMENT_VALUE04) );
    QStackAllocator            stackAllocator18( VALID_PREALLOCATION_SIZE, QAlignment(VALID_PREALLOCATION_ALIGNMENT_VALUE04) );
    QStackAllocator            stackAllocator19( VALID_PREALLOCATION_SIZE, QAlignment(VALID_PREALLOCATION_ALIGNMENT_VALUE04) );
    QStackAllocator            stackAllocator20( VALID_PREALLOCATION_SIZE, QAlignment(VALID_PREALLOCATION_ALIGNMENT_VALUE04) );

    for (u = 1; u <= AMOUNT_CASES; ++u)
    {
        try
        {
            switch (u)
            {
                case 1:  stackAllocator01.CanAllocate( 0, QAlignment(VALID_ALLOCATION_ALIGNMENT_VALUE01) ); break;
                case 2:  stackAllocator02.CanAllocate( 0, QAlignment(VALID_ALLOCATION_ALIGNMENT_VALUE02) ); break;
                case 3:  stackAllocator03.CanAllocate( 0, QAlignment(VALID_ALLOCATION_ALIGNMENT_VALUE03) ); break;
                case 4:  stackAllocator04.CanAllocate( 0, QAlignment(VALID_ALLOCATION_ALIGNMENT_VALUE04) ); break;
                case 5:  stackAllocator05.CanAllocate( 0, QAlignment(VALID_ALLOCATION_ALIGNMENT_VALUE01) ); break;
                case 6:  stackAllocator06.CanAllocate( 0, QAlignment(VALID_ALLOCATION_ALIGNMENT_VALUE02) ); break;
                case 7:  stackAllocator07.CanAllocate( 0, QAlignment(VALID_ALLOCATION_ALIGNMENT_VALUE03) ); break;
                case 8:  stackAllocator08.CanAllocate( 0, QAlignment(VALID_ALLOCATION_ALIGNMENT_VALUE04) ); break;
                case 9:  stackAllocator09.CanAllocate( 0, QAlignment(VALID_ALLOCATION_ALIGNMENT_VALUE01) ); break;
                case 10: stackAllocator10.CanAllocate( 0, QAlignment(VALID_ALLOCATION_ALIGNMENT_VALUE02) ); break;
                case 11: stackAllocator11.CanAllocate( 0, QAlignment(VALID_ALLOCATION_ALIGNMENT_VALUE03) ); break;
                case 12: stackAllocator12.CanAllocate( 0, QAlignment(VALID_ALLOCATION_ALIGNMENT_VALUE04) ); break;
                case 13: stackAllocator13.CanAllocate( 0, QAlignment(VALID_ALLOCATION_ALIGNMENT_VALUE01) ); break;
                case 14: stackAllocator14.CanAllocate( 0, QAlignment(VALID_ALLOCATION_ALIGNMENT_VALUE02) ); break;
                case 15: stackAllocator15.CanAllocate( 0, QAlignment(VALID_ALLOCATION_ALIGNMENT_VALUE03) ); break;
                case 16: stackAllocator16.CanAllocate( 0, QAlignment(VALID_ALLOCATION_ALIGNMENT_VALUE04) ); break;
                case 17: stackAllocator17.CanAllocate( 0, QAlignment(VALID_ALLOCATION_ALIGNMENT_VALUE01) ); break;
                case 18: stackAllocator18.CanAllocate( 0, QAlignment(VALID_ALLOCATION_ALIGNMENT_VALUE02) ); break;
                case 19: stackAllocator19.CanAllocate( 0, QAlignment(VALID_ALLOCATION_ALIGNMENT_VALUE03) ); break;
                case 20: stackAllocator20.CanAllocate( 0, QAlignment(VALID_ALLOCATION_ALIGNMENT_VALUE04) ); break;
            }
        }
        catch(const QAssertException&)
        {
            switch (u)
            {
                case 1:
                    if (false == bAssertionFailedIn01)
                    {
                        bAssertionFailedIn01 = true;
                    }
                break;
                case 2:
                    if (false == bAssertionFailedIn02)
                    {
                        bAssertionFailedIn02 = true;
                    }
                break;
                case 3:
                    if (false == bAssertionFailedIn03)
                    {
                        bAssertionFailedIn03 = true;
                    }
                break;
                case 4:
                    if (false == bAssertionFailedIn04)
                    {
                        bAssertionFailedIn04 = true;
                    }
                break;
                case 5:
                    if (false == bAssertionFailedIn05)
                    {
                        bAssertionFailedIn05 = true;
                    }
                break;
                case 6:
                    if (false == bAssertionFailedIn06)
                    {
                        bAssertionFailedIn06 = true;
                    }
                break;
                case 7:
                    if (false == bAssertionFailedIn07)
                    {
                        bAssertionFailedIn07 = true;
                    }
                break;
                case 8:
                    if (false == bAssertionFailedIn08)
                    {
                        bAssertionFailedIn08 = true;
                    }
                break;
                case 9:
                    if (false == bAssertionFailedIn09)
                    {
                        bAssertionFailedIn09 = true;
                    }
                break;
                case 10:
                    if (false == bAssertionFailedIn10)
                    {
                        bAssertionFailedIn10 = true;
                    }
                break;
                case 11:
                    if (false == bAssertionFailedIn11)
                    {
                        bAssertionFailedIn11 = true;
                    }
                break;
                case 12:
                    if (false == bAssertionFailedIn12)
                    {
                        bAssertionFailedIn12 = true;
                    }
                break;
                case 13:
                    if (false == bAssertionFailedIn13)
                    {
                        bAssertionFailedIn13 = true;
                    }
                break;
                case 14:
                    if (false == bAssertionFailedIn14)
                    {
                        bAssertionFailedIn14 = true;
                    }
                break;
                case 15:
                    if (false == bAssertionFailedIn15)
                    {
                        bAssertionFailedIn15 = true;
                    }
                break;
                case 16:
                    if (false == bAssertionFailedIn16)
                    {
                        bAssertionFailedIn16 = true;
                    }
                break;
                case 17:
                    if (false == bAssertionFailedIn17)
                    {
                        bAssertionFailedIn17 = true;
                    }
                break;
                case 18:
                    if (false == bAssertionFailedIn18)
                    {
                        bAssertionFailedIn18 = true;
                    }
                break;
                case 19:
                    if (false == bAssertionFailedIn19)
                    {
                        bAssertionFailedIn19 = true;
                    }
                break;
                case 20:
                    if (false == bAssertionFailedIn20)
                    {
                        bAssertionFailedIn20 = true;
                    }
                break;
            };
        }
    }


    // [Verification]

    BOOST_CHECK_EQUAL(bAssertionFailedIn01, ASSERTION_FAILED);
    BOOST_CHECK_EQUAL(bAssertionFailedIn02, ASSERTION_FAILED);
    BOOST_CHECK_EQUAL(bAssertionFailedIn03, ASSERTION_FAILED);
    BOOST_CHECK_EQUAL(bAssertionFailedIn04, ASSERTION_FAILED);
    BOOST_CHECK_EQUAL(bAssertionFailedIn05, ASSERTION_FAILED);
    BOOST_CHECK_EQUAL(bAssertionFailedIn06, ASSERTION_FAILED);
    BOOST_CHECK_EQUAL(bAssertionFailedIn07, ASSERTION_FAILED);
    BOOST_CHECK_EQUAL(bAssertionFailedIn08, ASSERTION_FAILED);
    BOOST_CHECK_EQUAL(bAssertionFailedIn09, ASSERTION_FAILED);
    BOOST_CHECK_EQUAL(bAssertionFailedIn10, ASSERTION_FAILED);
    BOOST_CHECK_EQUAL(bAssertionFailedIn11, ASSERTION_FAILED);
    BOOST_CHECK_EQUAL(bAssertionFailedIn12, ASSERTION_FAILED);
    BOOST_CHECK_EQUAL(bAssertionFailedIn13, ASSERTION_FAILED);
    BOOST_CHECK_EQUAL(bAssertionFailedIn14, ASSERTION_FAILED);
    BOOST_CHECK_EQUAL(bAssertionFailedIn15, ASSERTION_FAILED);
    BOOST_CHECK_EQUAL(bAssertionFailedIn16, ASSERTION_FAILED);
    BOOST_CHECK_EQUAL(bAssertionFailedIn17, ASSERTION_FAILED);
    BOOST_CHECK_EQUAL(bAssertionFailedIn18, ASSERTION_FAILED);
    BOOST_CHECK_EQUAL(bAssertionFailedIn19, ASSERTION_FAILED);
    BOOST_CHECK_EQUAL(bAssertionFailedIn20, ASSERTION_FAILED);
}

#elif QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_DISABLED

/// <summary>
/// Checks that ir returns False when the specified size for the intended memory block to be allocated is zero.
/// The alignment value for the intended memory block to be allocated is specified.
/// </summary>
QTEST_CASE (CanAllocate2_ReturnsFalseWhenSizeIsZero_Test)
{
    // [Preparation]

    const bool                 EXPECTED_VALUE                             = false;
    const pointer_uint_q       VALID_PREALLOCATION_SIZE                   = 64;

    const pointer_uint_q       VALID_PREALLOCATION_ALIGNMENT_VALUE01      = 2;
    const pointer_uint_q       VALID_PREALLOCATION_ALIGNMENT_VALUE02      = 4;
    const pointer_uint_q       VALID_PREALLOCATION_ALIGNMENT_VALUE03      = 8;
    const pointer_uint_q       VALID_PREALLOCATION_ALIGNMENT_VALUE04      = 16;

    const pointer_uint_q       VALID_ALLOCATION_ALIGNMENT_VALUE01         = 2;
    const pointer_uint_q       VALID_ALLOCATION_ALIGNMENT_VALUE02         = 4;
    const pointer_uint_q       VALID_ALLOCATION_ALIGNMENT_VALUE03         = 8;
    const pointer_uint_q       VALID_ALLOCATION_ALIGNMENT_VALUE04         = 16;

    bool                       bCouldNotAllocateIn01                      = false;
    bool                       bCouldNotAllocateIn02                      = false;
    bool                       bCouldNotAllocateIn03                      = false;
    bool                       bCouldNotAllocateIn04                      = false;
    bool                       bCouldNotAllocateIn05                      = false;
    bool                       bCouldNotAllocateIn06                      = false;
    bool                       bCouldNotAllocateIn07                      = false;
    bool                       bCouldNotAllocateIn08                      = false;
    bool                       bCouldNotAllocateIn09                      = false;
    bool                       bCouldNotAllocateIn10                      = false;
    bool                       bCouldNotAllocateIn11                      = false;
    bool                       bCouldNotAllocateIn12                      = false;
    bool                       bCouldNotAllocateIn13                      = false;
    bool                       bCouldNotAllocateIn14                      = false;
    bool                       bCouldNotAllocateIn15                      = false;
    bool                       bCouldNotAllocateIn16                      = false;
    bool                       bCouldNotAllocateIn17                      = false;
    bool                       bCouldNotAllocateIn18                      = false;
    bool                       bCouldNotAllocateIn19                      = false;
    bool                       bCouldNotAllocateIn20                      = false;


    // [Execution]

    QStackAllocator            stackAllocator01( VALID_PREALLOCATION_SIZE );
    QStackAllocator            stackAllocator02( VALID_PREALLOCATION_SIZE );
    QStackAllocator            stackAllocator03( VALID_PREALLOCATION_SIZE );
    QStackAllocator            stackAllocator04( VALID_PREALLOCATION_SIZE );
    QStackAllocator            stackAllocator05( VALID_PREALLOCATION_SIZE, QAlignment(VALID_PREALLOCATION_ALIGNMENT_VALUE01) );
    QStackAllocator            stackAllocator06( VALID_PREALLOCATION_SIZE, QAlignment(VALID_PREALLOCATION_ALIGNMENT_VALUE01) );
    QStackAllocator            stackAllocator07( VALID_PREALLOCATION_SIZE, QAlignment(VALID_PREALLOCATION_ALIGNMENT_VALUE01) );
    QStackAllocator            stackAllocator08( VALID_PREALLOCATION_SIZE, QAlignment(VALID_PREALLOCATION_ALIGNMENT_VALUE01) );
    QStackAllocator            stackAllocator09( VALID_PREALLOCATION_SIZE, QAlignment(VALID_PREALLOCATION_ALIGNMENT_VALUE02) );
    QStackAllocator            stackAllocator10( VALID_PREALLOCATION_SIZE, QAlignment(VALID_PREALLOCATION_ALIGNMENT_VALUE02) );
    QStackAllocator            stackAllocator11( VALID_PREALLOCATION_SIZE, QAlignment(VALID_PREALLOCATION_ALIGNMENT_VALUE02) );
    QStackAllocator            stackAllocator12( VALID_PREALLOCATION_SIZE, QAlignment(VALID_PREALLOCATION_ALIGNMENT_VALUE02) );
    QStackAllocator            stackAllocator13( VALID_PREALLOCATION_SIZE, QAlignment(VALID_PREALLOCATION_ALIGNMENT_VALUE03) );
    QStackAllocator            stackAllocator14( VALID_PREALLOCATION_SIZE, QAlignment(VALID_PREALLOCATION_ALIGNMENT_VALUE03) );
    QStackAllocator            stackAllocator15( VALID_PREALLOCATION_SIZE, QAlignment(VALID_PREALLOCATION_ALIGNMENT_VALUE03) );
    QStackAllocator            stackAllocator16( VALID_PREALLOCATION_SIZE, QAlignment(VALID_PREALLOCATION_ALIGNMENT_VALUE03) );
    QStackAllocator            stackAllocator17( VALID_PREALLOCATION_SIZE, QAlignment(VALID_PREALLOCATION_ALIGNMENT_VALUE04) );
    QStackAllocator            stackAllocator18( VALID_PREALLOCATION_SIZE, QAlignment(VALID_PREALLOCATION_ALIGNMENT_VALUE04) );
    QStackAllocator            stackAllocator19( VALID_PREALLOCATION_SIZE, QAlignment(VALID_PREALLOCATION_ALIGNMENT_VALUE04) );
    QStackAllocator            stackAllocator20( VALID_PREALLOCATION_SIZE, QAlignment(VALID_PREALLOCATION_ALIGNMENT_VALUE04) );

    bCouldNotAllocateIn01 = !stackAllocator01.CanAllocate( 0, QAlignment (VALID_ALLOCATION_ALIGNMENT_VALUE01) );
    bCouldNotAllocateIn02 = !stackAllocator02.CanAllocate( 0, QAlignment (VALID_ALLOCATION_ALIGNMENT_VALUE02) );
    bCouldNotAllocateIn03 = !stackAllocator03.CanAllocate( 0, QAlignment (VALID_ALLOCATION_ALIGNMENT_VALUE03) );
    bCouldNotAllocateIn04 = !stackAllocator04.CanAllocate( 0, QAlignment (VALID_ALLOCATION_ALIGNMENT_VALUE04) );
    bCouldNotAllocateIn05 = !stackAllocator05.CanAllocate( 0, QAlignment (VALID_ALLOCATION_ALIGNMENT_VALUE01) );
    bCouldNotAllocateIn06 = !stackAllocator06.CanAllocate( 0, QAlignment (VALID_ALLOCATION_ALIGNMENT_VALUE02) );
    bCouldNotAllocateIn07 = !stackAllocator07.CanAllocate( 0, QAlignment (VALID_ALLOCATION_ALIGNMENT_VALUE03) );
    bCouldNotAllocateIn08 = !stackAllocator08.CanAllocate( 0, QAlignment (VALID_ALLOCATION_ALIGNMENT_VALUE04) );
    bCouldNotAllocateIn09 = !stackAllocator09.CanAllocate( 0, QAlignment (VALID_ALLOCATION_ALIGNMENT_VALUE01) );
    bCouldNotAllocateIn10 = !stackAllocator10.CanAllocate( 0, QAlignment (VALID_ALLOCATION_ALIGNMENT_VALUE02) );
    bCouldNotAllocateIn11 = !stackAllocator11.CanAllocate( 0, QAlignment (VALID_ALLOCATION_ALIGNMENT_VALUE03) );
    bCouldNotAllocateIn12 = !stackAllocator12.CanAllocate( 0, QAlignment (VALID_ALLOCATION_ALIGNMENT_VALUE04) );
    bCouldNotAllocateIn13 = !stackAllocator13.CanAllocate( 0, QAlignment (VALID_ALLOCATION_ALIGNMENT_VALUE01) );
    bCouldNotAllocateIn14 = !stackAllocator14.CanAllocate( 0, QAlignment (VALID_ALLOCATION_ALIGNMENT_VALUE02) );
    bCouldNotAllocateIn15 = !stackAllocator15.CanAllocate( 0, QAlignment (VALID_ALLOCATION_ALIGNMENT_VALUE03) );
    bCouldNotAllocateIn16 = !stackAllocator16.CanAllocate( 0, QAlignment (VALID_ALLOCATION_ALIGNMENT_VALUE04) );
    bCouldNotAllocateIn17 = !stackAllocator17.CanAllocate( 0, QAlignment (VALID_ALLOCATION_ALIGNMENT_VALUE01) );
    bCouldNotAllocateIn18 = !stackAllocator18.CanAllocate( 0, QAlignment (VALID_ALLOCATION_ALIGNMENT_VALUE02) );
    bCouldNotAllocateIn19 = !stackAllocator19.CanAllocate( 0, QAlignment (VALID_ALLOCATION_ALIGNMENT_VALUE03) );
    bCouldNotAllocateIn20 = !stackAllocator20.CanAllocate( 0, QAlignment (VALID_ALLOCATION_ALIGNMENT_VALUE04) );


    // [Verification]

    BOOST_CHECK_EQUAL(bCouldNotAllocateIn01, EXPECTED_VALUE);
    BOOST_CHECK_EQUAL(bCouldNotAllocateIn02, EXPECTED_VALUE);
    BOOST_CHECK_EQUAL(bCouldNotAllocateIn03, EXPECTED_VALUE);
    BOOST_CHECK_EQUAL(bCouldNotAllocateIn04, EXPECTED_VALUE);
    BOOST_CHECK_EQUAL(bCouldNotAllocateIn05, EXPECTED_VALUE);
    BOOST_CHECK_EQUAL(bCouldNotAllocateIn06, EXPECTED_VALUE);
    BOOST_CHECK_EQUAL(bCouldNotAllocateIn07, EXPECTED_VALUE);
    BOOST_CHECK_EQUAL(bCouldNotAllocateIn08, EXPECTED_VALUE);
    BOOST_CHECK_EQUAL(bCouldNotAllocateIn09, EXPECTED_VALUE);
    BOOST_CHECK_EQUAL(bCouldNotAllocateIn10, EXPECTED_VALUE);
    BOOST_CHECK_EQUAL(bCouldNotAllocateIn11, EXPECTED_VALUE);
    BOOST_CHECK_EQUAL(bCouldNotAllocateIn12, EXPECTED_VALUE);
    BOOST_CHECK_EQUAL(bCouldNotAllocateIn13, EXPECTED_VALUE);
    BOOST_CHECK_EQUAL(bCouldNotAllocateIn14, EXPECTED_VALUE);
    BOOST_CHECK_EQUAL(bCouldNotAllocateIn15, EXPECTED_VALUE);
    BOOST_CHECK_EQUAL(bCouldNotAllocateIn16, EXPECTED_VALUE);
    BOOST_CHECK_EQUAL(bCouldNotAllocateIn17, EXPECTED_VALUE);
    BOOST_CHECK_EQUAL(bCouldNotAllocateIn18, EXPECTED_VALUE);
    BOOST_CHECK_EQUAL(bCouldNotAllocateIn19 ,EXPECTED_VALUE);
    BOOST_CHECK_EQUAL(bCouldNotAllocateIn20, EXPECTED_VALUE);
}

#endif // QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that it returns False when there is not enough space to allocate a memory block whose specified size
/// is too big for the current free space in the stack.
/// The alignment value for the intended memory block to be allocated is specified.
/// </summary>
QTEST_CASE (CanAllocate2_ReturnsFalseWhenThereIsNotEnoughSpaceToAllocateAMemoryBlock_Test)
{
    // [Preparation]

    const bool                 EXPECTED_VALUE                             = true;

    const pointer_uint_q       VALID_PREALLOCATION_SIZE                   = 64;
    const pointer_uint_q       VALID_ALLOCATION_SIZE                      = 32;
    const pointer_uint_q       TOO_BIG_ALLOCATION_SIZE                    = 128;

    const pointer_uint_q       VALID_PREALLOCATION_ALIGNMENT_VALUE01      = 2;
    const pointer_uint_q       VALID_PREALLOCATION_ALIGNMENT_VALUE02      = 4;
    const pointer_uint_q       VALID_PREALLOCATION_ALIGNMENT_VALUE03      = 8;
    const pointer_uint_q       VALID_PREALLOCATION_ALIGNMENT_VALUE04      = 16;

    const pointer_uint_q       VALID_ALLOCATION_ALIGNMENT_VALUE01         = 2;
    const pointer_uint_q       VALID_ALLOCATION_ALIGNMENT_VALUE02         = 4;
    const pointer_uint_q       VALID_ALLOCATION_ALIGNMENT_VALUE03         = 8;
    const pointer_uint_q       VALID_ALLOCATION_ALIGNMENT_VALUE04         = 16;

    bool                       bSecondAllocationFailureIn01               = false;
    bool                       bSecondAllocationFailureIn02               = false;
    bool                       bSecondAllocationFailureIn03               = false;
    bool                       bSecondAllocationFailureIn04               = false;
    bool                       bSecondAllocationFailureIn05               = false;
    bool                       bSecondAllocationFailureIn06               = false;
    bool                       bSecondAllocationFailureIn07               = false;
    bool                       bSecondAllocationFailureIn08               = false;
    bool                       bSecondAllocationFailureIn09               = false;
    bool                       bSecondAllocationFailureIn10               = false;
    bool                       bSecondAllocationFailureIn11               = false;
    bool                       bSecondAllocationFailureIn12               = false;
    bool                       bSecondAllocationFailureIn13               = false;
    bool                       bSecondAllocationFailureIn14               = false;
    bool                       bSecondAllocationFailureIn15               = false;
    bool                       bSecondAllocationFailureIn16               = false;
    bool                       bSecondAllocationFailureIn17               = false;
    bool                       bSecondAllocationFailureIn18               = false;
    bool                       bSecondAllocationFailureIn19               = false;
    bool                       bSecondAllocationFailureIn20               = false;


    // [Execution]

    QStackAllocator                stackAllocator01( VALID_PREALLOCATION_SIZE );
    QStackAllocator                stackAllocator02( VALID_PREALLOCATION_SIZE );
    QStackAllocator                stackAllocator03( VALID_PREALLOCATION_SIZE );
    QStackAllocator                stackAllocator04( VALID_PREALLOCATION_SIZE );
    QStackAllocator                stackAllocator05( VALID_PREALLOCATION_SIZE, QAlignment(VALID_PREALLOCATION_ALIGNMENT_VALUE01) );
    QStackAllocator                stackAllocator06( VALID_PREALLOCATION_SIZE, QAlignment(VALID_PREALLOCATION_ALIGNMENT_VALUE01) );
    QStackAllocator                stackAllocator07( VALID_PREALLOCATION_SIZE, QAlignment(VALID_PREALLOCATION_ALIGNMENT_VALUE01) );
    QStackAllocator                stackAllocator08( VALID_PREALLOCATION_SIZE, QAlignment(VALID_PREALLOCATION_ALIGNMENT_VALUE01) );
    QStackAllocator                stackAllocator09( VALID_PREALLOCATION_SIZE, QAlignment(VALID_PREALLOCATION_ALIGNMENT_VALUE02) );
    QStackAllocator                stackAllocator10( VALID_PREALLOCATION_SIZE, QAlignment(VALID_PREALLOCATION_ALIGNMENT_VALUE02) );
    QStackAllocator                stackAllocator11( VALID_PREALLOCATION_SIZE, QAlignment(VALID_PREALLOCATION_ALIGNMENT_VALUE02) );
    QStackAllocator                stackAllocator12( VALID_PREALLOCATION_SIZE, QAlignment(VALID_PREALLOCATION_ALIGNMENT_VALUE02) );
    QStackAllocator                stackAllocator13( VALID_PREALLOCATION_SIZE, QAlignment(VALID_PREALLOCATION_ALIGNMENT_VALUE03) );
    QStackAllocator                stackAllocator14( VALID_PREALLOCATION_SIZE, QAlignment(VALID_PREALLOCATION_ALIGNMENT_VALUE03) );
    QStackAllocator                stackAllocator15( VALID_PREALLOCATION_SIZE, QAlignment(VALID_PREALLOCATION_ALIGNMENT_VALUE03) );
    QStackAllocator                stackAllocator16( VALID_PREALLOCATION_SIZE, QAlignment(VALID_PREALLOCATION_ALIGNMENT_VALUE03) );
    QStackAllocator                stackAllocator17( VALID_PREALLOCATION_SIZE, QAlignment(VALID_PREALLOCATION_ALIGNMENT_VALUE04) );
    QStackAllocator                stackAllocator18( VALID_PREALLOCATION_SIZE, QAlignment(VALID_PREALLOCATION_ALIGNMENT_VALUE04) );
    QStackAllocator                stackAllocator19( VALID_PREALLOCATION_SIZE, QAlignment(VALID_PREALLOCATION_ALIGNMENT_VALUE04) );
    QStackAllocator                stackAllocator20( VALID_PREALLOCATION_SIZE, QAlignment(VALID_PREALLOCATION_ALIGNMENT_VALUE04) );

    // Allocation WILL occur.
    stackAllocator01.Allocate( VALID_ALLOCATION_SIZE, QAlignment(VALID_ALLOCATION_ALIGNMENT_VALUE01) );
    stackAllocator02.Allocate( VALID_ALLOCATION_SIZE, QAlignment(VALID_ALLOCATION_ALIGNMENT_VALUE02) );
    stackAllocator03.Allocate( VALID_ALLOCATION_SIZE, QAlignment(VALID_ALLOCATION_ALIGNMENT_VALUE03) );
    stackAllocator04.Allocate( VALID_ALLOCATION_SIZE, QAlignment(VALID_ALLOCATION_ALIGNMENT_VALUE04) );
    stackAllocator05.Allocate( VALID_ALLOCATION_SIZE, QAlignment(VALID_ALLOCATION_ALIGNMENT_VALUE01) );
    stackAllocator06.Allocate( VALID_ALLOCATION_SIZE, QAlignment(VALID_ALLOCATION_ALIGNMENT_VALUE02) );
    stackAllocator07.Allocate( VALID_ALLOCATION_SIZE, QAlignment(VALID_ALLOCATION_ALIGNMENT_VALUE03) );
    stackAllocator08.Allocate( VALID_ALLOCATION_SIZE, QAlignment(VALID_ALLOCATION_ALIGNMENT_VALUE04) );
    stackAllocator09.Allocate( VALID_ALLOCATION_SIZE, QAlignment(VALID_ALLOCATION_ALIGNMENT_VALUE01) );
    stackAllocator10.Allocate( VALID_ALLOCATION_SIZE, QAlignment(VALID_ALLOCATION_ALIGNMENT_VALUE02) );
    stackAllocator11.Allocate( VALID_ALLOCATION_SIZE, QAlignment(VALID_ALLOCATION_ALIGNMENT_VALUE03) );
    stackAllocator12.Allocate( VALID_ALLOCATION_SIZE, QAlignment(VALID_ALLOCATION_ALIGNMENT_VALUE04) );
    stackAllocator13.Allocate( VALID_ALLOCATION_SIZE, QAlignment(VALID_ALLOCATION_ALIGNMENT_VALUE01) );
    stackAllocator14.Allocate( VALID_ALLOCATION_SIZE, QAlignment(VALID_ALLOCATION_ALIGNMENT_VALUE02) );
    stackAllocator15.Allocate( VALID_ALLOCATION_SIZE, QAlignment(VALID_ALLOCATION_ALIGNMENT_VALUE03) );
    stackAllocator16.Allocate( VALID_ALLOCATION_SIZE, QAlignment(VALID_ALLOCATION_ALIGNMENT_VALUE04) );
    stackAllocator17.Allocate( VALID_ALLOCATION_SIZE, QAlignment(VALID_ALLOCATION_ALIGNMENT_VALUE01) );
    stackAllocator18.Allocate( VALID_ALLOCATION_SIZE, QAlignment(VALID_ALLOCATION_ALIGNMENT_VALUE02) );
    stackAllocator19.Allocate( VALID_ALLOCATION_SIZE, QAlignment(VALID_ALLOCATION_ALIGNMENT_VALUE03) );
    stackAllocator20.Allocate( VALID_ALLOCATION_SIZE, QAlignment(VALID_ALLOCATION_ALIGNMENT_VALUE04) );

    // Allocation COULDN'T occur.
    bSecondAllocationFailureIn01 = !stackAllocator01.CanAllocate( TOO_BIG_ALLOCATION_SIZE, QAlignment(VALID_ALLOCATION_ALIGNMENT_VALUE01) );
    bSecondAllocationFailureIn02 = !stackAllocator02.CanAllocate( TOO_BIG_ALLOCATION_SIZE, QAlignment(VALID_ALLOCATION_ALIGNMENT_VALUE02) );
    bSecondAllocationFailureIn03 = !stackAllocator03.CanAllocate( TOO_BIG_ALLOCATION_SIZE, QAlignment(VALID_ALLOCATION_ALIGNMENT_VALUE03) );
    bSecondAllocationFailureIn04 = !stackAllocator04.CanAllocate( TOO_BIG_ALLOCATION_SIZE, QAlignment(VALID_ALLOCATION_ALIGNMENT_VALUE04) );
    bSecondAllocationFailureIn05 = !stackAllocator05.CanAllocate( TOO_BIG_ALLOCATION_SIZE, QAlignment(VALID_ALLOCATION_ALIGNMENT_VALUE01) );
    bSecondAllocationFailureIn06 = !stackAllocator06.CanAllocate( TOO_BIG_ALLOCATION_SIZE, QAlignment(VALID_ALLOCATION_ALIGNMENT_VALUE02) );
    bSecondAllocationFailureIn07 = !stackAllocator07.CanAllocate( TOO_BIG_ALLOCATION_SIZE, QAlignment(VALID_ALLOCATION_ALIGNMENT_VALUE03) );
    bSecondAllocationFailureIn08 = !stackAllocator08.CanAllocate( TOO_BIG_ALLOCATION_SIZE, QAlignment(VALID_ALLOCATION_ALIGNMENT_VALUE04) );
    bSecondAllocationFailureIn09 = !stackAllocator09.CanAllocate( TOO_BIG_ALLOCATION_SIZE, QAlignment(VALID_ALLOCATION_ALIGNMENT_VALUE01) );
    bSecondAllocationFailureIn10 = !stackAllocator10.CanAllocate( TOO_BIG_ALLOCATION_SIZE, QAlignment(VALID_ALLOCATION_ALIGNMENT_VALUE02) );
    bSecondAllocationFailureIn11 = !stackAllocator11.CanAllocate( TOO_BIG_ALLOCATION_SIZE, QAlignment(VALID_ALLOCATION_ALIGNMENT_VALUE03) );
    bSecondAllocationFailureIn12 = !stackAllocator12.CanAllocate( TOO_BIG_ALLOCATION_SIZE, QAlignment(VALID_ALLOCATION_ALIGNMENT_VALUE04) );
    bSecondAllocationFailureIn13 = !stackAllocator13.CanAllocate( TOO_BIG_ALLOCATION_SIZE, QAlignment(VALID_ALLOCATION_ALIGNMENT_VALUE01) );
    bSecondAllocationFailureIn14 = !stackAllocator14.CanAllocate( TOO_BIG_ALLOCATION_SIZE, QAlignment(VALID_ALLOCATION_ALIGNMENT_VALUE02) );
    bSecondAllocationFailureIn15 = !stackAllocator15.CanAllocate( TOO_BIG_ALLOCATION_SIZE, QAlignment(VALID_ALLOCATION_ALIGNMENT_VALUE03) );
    bSecondAllocationFailureIn16 = !stackAllocator16.CanAllocate( TOO_BIG_ALLOCATION_SIZE, QAlignment(VALID_ALLOCATION_ALIGNMENT_VALUE04) );
    bSecondAllocationFailureIn17 = !stackAllocator17.CanAllocate( TOO_BIG_ALLOCATION_SIZE, QAlignment(VALID_ALLOCATION_ALIGNMENT_VALUE01) );
    bSecondAllocationFailureIn18 = !stackAllocator18.CanAllocate( TOO_BIG_ALLOCATION_SIZE, QAlignment(VALID_ALLOCATION_ALIGNMENT_VALUE02) );
    bSecondAllocationFailureIn19 = !stackAllocator19.CanAllocate( TOO_BIG_ALLOCATION_SIZE, QAlignment(VALID_ALLOCATION_ALIGNMENT_VALUE03) );
    bSecondAllocationFailureIn20 = !stackAllocator20.CanAllocate( TOO_BIG_ALLOCATION_SIZE, QAlignment(VALID_ALLOCATION_ALIGNMENT_VALUE04) );


    // [Verification]

    BOOST_CHECK_EQUAL(bSecondAllocationFailureIn01, EXPECTED_VALUE);
    BOOST_CHECK_EQUAL(bSecondAllocationFailureIn02, EXPECTED_VALUE);
    BOOST_CHECK_EQUAL(bSecondAllocationFailureIn03, EXPECTED_VALUE);
    BOOST_CHECK_EQUAL(bSecondAllocationFailureIn04, EXPECTED_VALUE);
    BOOST_CHECK_EQUAL(bSecondAllocationFailureIn05, EXPECTED_VALUE);
    BOOST_CHECK_EQUAL(bSecondAllocationFailureIn06, EXPECTED_VALUE);
    BOOST_CHECK_EQUAL(bSecondAllocationFailureIn07, EXPECTED_VALUE);
    BOOST_CHECK_EQUAL(bSecondAllocationFailureIn08, EXPECTED_VALUE);
    BOOST_CHECK_EQUAL(bSecondAllocationFailureIn09, EXPECTED_VALUE);
    BOOST_CHECK_EQUAL(bSecondAllocationFailureIn10, EXPECTED_VALUE);
    BOOST_CHECK_EQUAL(bSecondAllocationFailureIn11, EXPECTED_VALUE);
    BOOST_CHECK_EQUAL(bSecondAllocationFailureIn12, EXPECTED_VALUE);
    BOOST_CHECK_EQUAL(bSecondAllocationFailureIn13, EXPECTED_VALUE);
    BOOST_CHECK_EQUAL(bSecondAllocationFailureIn14, EXPECTED_VALUE);
    BOOST_CHECK_EQUAL(bSecondAllocationFailureIn15, EXPECTED_VALUE);
    BOOST_CHECK_EQUAL(bSecondAllocationFailureIn16, EXPECTED_VALUE);
    BOOST_CHECK_EQUAL(bSecondAllocationFailureIn17, EXPECTED_VALUE);
    BOOST_CHECK_EQUAL(bSecondAllocationFailureIn18, EXPECTED_VALUE);
    BOOST_CHECK_EQUAL(bSecondAllocationFailureIn19, EXPECTED_VALUE);
    BOOST_CHECK_EQUAL(bSecondAllocationFailureIn20, EXPECTED_VALUE);
}

/// <summary>
/// Checks that it returns True when there is enough free space yet to allocate a memory block.
/// The alignment value for the intended memory block to be allocated is specified.
/// </summary>
QTEST_CASE (CanAllocate2_ReturnsTrueWhenThereIsEnoughSpaceYetToAllocateAMemoryBlock_Test)
{
    // [Preparation]

    const bool                 EXPECTED_VALUE                             = true;

    const pointer_uint_q       VALID_PREALLOCATION_SIZE                   = 128;
    const pointer_uint_q       VALID_ALLOCATION_SIZE01                    = 32;
    const pointer_uint_q       VALID_ALLOCATION_SIZE02                    = 8;

    const pointer_uint_q       VALID_PREALLOCATION_ALIGNMENT_VALUE01      = 2;
    const pointer_uint_q       VALID_PREALLOCATION_ALIGNMENT_VALUE02      = 4;
    const pointer_uint_q       VALID_PREALLOCATION_ALIGNMENT_VALUE03      = 8;
    const pointer_uint_q       VALID_PREALLOCATION_ALIGNMENT_VALUE04      = 16;

    const pointer_uint_q       VALID_ALLOCATION_ALIGNMENT_VALUE01         = 2;
    const pointer_uint_q       VALID_ALLOCATION_ALIGNMENT_VALUE02         = 4;
    const pointer_uint_q       VALID_ALLOCATION_ALIGNMENT_VALUE03         = 8;
    const pointer_uint_q       VALID_ALLOCATION_ALIGNMENT_VALUE04         = 16;

    bool                       bCouldAllocateAgainIn01                    = false;
    bool                       bCouldAllocateAgainIn02                    = false;
    bool                       bCouldAllocateAgainIn03                    = false;
    bool                       bCouldAllocateAgainIn04                    = false;
    bool                       bCouldAllocateAgainIn05                    = false;
    bool                       bCouldAllocateAgainIn06                    = false;
    bool                       bCouldAllocateAgainIn07                    = false;
    bool                       bCouldAllocateAgainIn08                    = false;
    bool                       bCouldAllocateAgainIn09                    = false;
    bool                       bCouldAllocateAgainIn10                    = false;
    bool                       bCouldAllocateAgainIn11                    = false;
    bool                       bCouldAllocateAgainIn12                    = false;
    bool                       bCouldAllocateAgainIn13                    = false;
    bool                       bCouldAllocateAgainIn14                    = false;
    bool                       bCouldAllocateAgainIn15                    = false;
    bool                       bCouldAllocateAgainIn16                    = false;
    bool                       bCouldAllocateAgainIn17                    = false;
    bool                       bCouldAllocateAgainIn18                    = false;
    bool                       bCouldAllocateAgainIn19                    = false;
    bool                       bCouldAllocateAgainIn20                    = false;


    // [Execution]

    QStackAllocator             stackAllocator01( VALID_PREALLOCATION_SIZE );
    QStackAllocator             stackAllocator02( VALID_PREALLOCATION_SIZE );
    QStackAllocator             stackAllocator03( VALID_PREALLOCATION_SIZE );
    QStackAllocator             stackAllocator04( VALID_PREALLOCATION_SIZE );
    QStackAllocator             stackAllocator05( VALID_PREALLOCATION_SIZE, QAlignment(VALID_PREALLOCATION_ALIGNMENT_VALUE01) );
    QStackAllocator             stackAllocator06( VALID_PREALLOCATION_SIZE, QAlignment(VALID_PREALLOCATION_ALIGNMENT_VALUE01) );
    QStackAllocator             stackAllocator07( VALID_PREALLOCATION_SIZE, QAlignment(VALID_PREALLOCATION_ALIGNMENT_VALUE01) );
    QStackAllocator             stackAllocator08( VALID_PREALLOCATION_SIZE, QAlignment(VALID_PREALLOCATION_ALIGNMENT_VALUE01) );
    QStackAllocator             stackAllocator09( VALID_PREALLOCATION_SIZE, QAlignment(VALID_PREALLOCATION_ALIGNMENT_VALUE02) );
    QStackAllocator             stackAllocator10( VALID_PREALLOCATION_SIZE, QAlignment(VALID_PREALLOCATION_ALIGNMENT_VALUE02) );
    QStackAllocator             stackAllocator11( VALID_PREALLOCATION_SIZE, QAlignment(VALID_PREALLOCATION_ALIGNMENT_VALUE02) );
    QStackAllocator             stackAllocator12( VALID_PREALLOCATION_SIZE, QAlignment(VALID_PREALLOCATION_ALIGNMENT_VALUE02) );
    QStackAllocator             stackAllocator13( VALID_PREALLOCATION_SIZE, QAlignment(VALID_PREALLOCATION_ALIGNMENT_VALUE03) );
    QStackAllocator             stackAllocator14( VALID_PREALLOCATION_SIZE, QAlignment(VALID_PREALLOCATION_ALIGNMENT_VALUE03) );
    QStackAllocator             stackAllocator15( VALID_PREALLOCATION_SIZE, QAlignment(VALID_PREALLOCATION_ALIGNMENT_VALUE03) );
    QStackAllocator             stackAllocator16( VALID_PREALLOCATION_SIZE, QAlignment(VALID_PREALLOCATION_ALIGNMENT_VALUE03) );
    QStackAllocator             stackAllocator17( VALID_PREALLOCATION_SIZE, QAlignment(VALID_PREALLOCATION_ALIGNMENT_VALUE04) );
    QStackAllocator             stackAllocator18( VALID_PREALLOCATION_SIZE, QAlignment(VALID_PREALLOCATION_ALIGNMENT_VALUE04) );
    QStackAllocator             stackAllocator19( VALID_PREALLOCATION_SIZE, QAlignment(VALID_PREALLOCATION_ALIGNMENT_VALUE04) );
    QStackAllocator             stackAllocator20( VALID_PREALLOCATION_SIZE, QAlignment(VALID_PREALLOCATION_ALIGNMENT_VALUE04) );

    // Allocation WILL occur.
    stackAllocator01.Allocate( VALID_ALLOCATION_SIZE01, QAlignment(VALID_ALLOCATION_ALIGNMENT_VALUE01) );
    stackAllocator02.Allocate( VALID_ALLOCATION_SIZE01, QAlignment(VALID_ALLOCATION_ALIGNMENT_VALUE02) );
    stackAllocator03.Allocate( VALID_ALLOCATION_SIZE01, QAlignment(VALID_ALLOCATION_ALIGNMENT_VALUE03) );
    stackAllocator04.Allocate( VALID_ALLOCATION_SIZE01, QAlignment(VALID_ALLOCATION_ALIGNMENT_VALUE04) );
    stackAllocator05.Allocate( VALID_ALLOCATION_SIZE01, QAlignment(VALID_ALLOCATION_ALIGNMENT_VALUE01) );
    stackAllocator06.Allocate( VALID_ALLOCATION_SIZE01, QAlignment(VALID_ALLOCATION_ALIGNMENT_VALUE02) );
    stackAllocator07.Allocate( VALID_ALLOCATION_SIZE01, QAlignment(VALID_ALLOCATION_ALIGNMENT_VALUE03) );
    stackAllocator08.Allocate( VALID_ALLOCATION_SIZE01, QAlignment(VALID_ALLOCATION_ALIGNMENT_VALUE04) );
    stackAllocator09.Allocate( VALID_ALLOCATION_SIZE01, QAlignment(VALID_ALLOCATION_ALIGNMENT_VALUE01) );
    stackAllocator10.Allocate( VALID_ALLOCATION_SIZE01, QAlignment(VALID_ALLOCATION_ALIGNMENT_VALUE02) );
    stackAllocator11.Allocate( VALID_ALLOCATION_SIZE01, QAlignment(VALID_ALLOCATION_ALIGNMENT_VALUE03) );
    stackAllocator12.Allocate( VALID_ALLOCATION_SIZE01, QAlignment(VALID_ALLOCATION_ALIGNMENT_VALUE04) );
    stackAllocator13.Allocate( VALID_ALLOCATION_SIZE01, QAlignment(VALID_ALLOCATION_ALIGNMENT_VALUE01) );
    stackAllocator14.Allocate( VALID_ALLOCATION_SIZE01, QAlignment(VALID_ALLOCATION_ALIGNMENT_VALUE02) );
    stackAllocator15.Allocate( VALID_ALLOCATION_SIZE01, QAlignment(VALID_ALLOCATION_ALIGNMENT_VALUE03) );
    stackAllocator16.Allocate( VALID_ALLOCATION_SIZE01, QAlignment(VALID_ALLOCATION_ALIGNMENT_VALUE04) );
    stackAllocator17.Allocate( VALID_ALLOCATION_SIZE01, QAlignment(VALID_ALLOCATION_ALIGNMENT_VALUE01) );
    stackAllocator18.Allocate( VALID_ALLOCATION_SIZE01, QAlignment(VALID_ALLOCATION_ALIGNMENT_VALUE02) );
    stackAllocator19.Allocate( VALID_ALLOCATION_SIZE01, QAlignment(VALID_ALLOCATION_ALIGNMENT_VALUE03) );
    stackAllocator20.Allocate( VALID_ALLOCATION_SIZE01, QAlignment(VALID_ALLOCATION_ALIGNMENT_VALUE04) );

    // Allocation COULD occur as well.
    bCouldAllocateAgainIn01 = stackAllocator01.CanAllocate( VALID_ALLOCATION_SIZE02, QAlignment(VALID_ALLOCATION_ALIGNMENT_VALUE01) );
    bCouldAllocateAgainIn02 = stackAllocator02.CanAllocate( VALID_ALLOCATION_SIZE02, QAlignment(VALID_ALLOCATION_ALIGNMENT_VALUE02) );
    bCouldAllocateAgainIn03 = stackAllocator03.CanAllocate( VALID_ALLOCATION_SIZE02, QAlignment(VALID_ALLOCATION_ALIGNMENT_VALUE03) );
    bCouldAllocateAgainIn04 = stackAllocator04.CanAllocate( VALID_ALLOCATION_SIZE02, QAlignment(VALID_ALLOCATION_ALIGNMENT_VALUE04) );
    bCouldAllocateAgainIn05 = stackAllocator05.CanAllocate( VALID_ALLOCATION_SIZE02, QAlignment(VALID_ALLOCATION_ALIGNMENT_VALUE01) );
    bCouldAllocateAgainIn06 = stackAllocator06.CanAllocate( VALID_ALLOCATION_SIZE02, QAlignment(VALID_ALLOCATION_ALIGNMENT_VALUE02) );
    bCouldAllocateAgainIn07 = stackAllocator07.CanAllocate( VALID_ALLOCATION_SIZE02, QAlignment(VALID_ALLOCATION_ALIGNMENT_VALUE03) );
    bCouldAllocateAgainIn08 = stackAllocator08.CanAllocate( VALID_ALLOCATION_SIZE02, QAlignment(VALID_ALLOCATION_ALIGNMENT_VALUE04) );
    bCouldAllocateAgainIn09 = stackAllocator09.CanAllocate( VALID_ALLOCATION_SIZE02, QAlignment(VALID_ALLOCATION_ALIGNMENT_VALUE01) );
    bCouldAllocateAgainIn10 = stackAllocator10.CanAllocate( VALID_ALLOCATION_SIZE02, QAlignment(VALID_ALLOCATION_ALIGNMENT_VALUE02) );
    bCouldAllocateAgainIn11 = stackAllocator11.CanAllocate( VALID_ALLOCATION_SIZE02, QAlignment(VALID_ALLOCATION_ALIGNMENT_VALUE03) );
    bCouldAllocateAgainIn12 = stackAllocator12.CanAllocate( VALID_ALLOCATION_SIZE02, QAlignment(VALID_ALLOCATION_ALIGNMENT_VALUE04) );
    bCouldAllocateAgainIn13 = stackAllocator13.CanAllocate( VALID_ALLOCATION_SIZE02, QAlignment(VALID_ALLOCATION_ALIGNMENT_VALUE01) );
    bCouldAllocateAgainIn14 = stackAllocator14.CanAllocate( VALID_ALLOCATION_SIZE02, QAlignment(VALID_ALLOCATION_ALIGNMENT_VALUE02) );
    bCouldAllocateAgainIn15 = stackAllocator15.CanAllocate( VALID_ALLOCATION_SIZE02, QAlignment(VALID_ALLOCATION_ALIGNMENT_VALUE03) );
    bCouldAllocateAgainIn16 = stackAllocator16.CanAllocate( VALID_ALLOCATION_SIZE02, QAlignment(VALID_ALLOCATION_ALIGNMENT_VALUE04) );
    bCouldAllocateAgainIn17 = stackAllocator17.CanAllocate( VALID_ALLOCATION_SIZE02, QAlignment(VALID_ALLOCATION_ALIGNMENT_VALUE01) );
    bCouldAllocateAgainIn18 = stackAllocator18.CanAllocate( VALID_ALLOCATION_SIZE02, QAlignment(VALID_ALLOCATION_ALIGNMENT_VALUE02) );
    bCouldAllocateAgainIn19 = stackAllocator19.CanAllocate( VALID_ALLOCATION_SIZE02, QAlignment(VALID_ALLOCATION_ALIGNMENT_VALUE03) );
    bCouldAllocateAgainIn20 = stackAllocator20.CanAllocate( VALID_ALLOCATION_SIZE02, QAlignment(VALID_ALLOCATION_ALIGNMENT_VALUE04) );


    // [Verification]

    BOOST_CHECK_EQUAL(bCouldAllocateAgainIn01, EXPECTED_VALUE);
    BOOST_CHECK_EQUAL(bCouldAllocateAgainIn02, EXPECTED_VALUE);
    BOOST_CHECK_EQUAL(bCouldAllocateAgainIn03, EXPECTED_VALUE);
    BOOST_CHECK_EQUAL(bCouldAllocateAgainIn04, EXPECTED_VALUE);
    BOOST_CHECK_EQUAL(bCouldAllocateAgainIn05, EXPECTED_VALUE);
    BOOST_CHECK_EQUAL(bCouldAllocateAgainIn06, EXPECTED_VALUE);
    BOOST_CHECK_EQUAL(bCouldAllocateAgainIn07, EXPECTED_VALUE);
    BOOST_CHECK_EQUAL(bCouldAllocateAgainIn08, EXPECTED_VALUE);
    BOOST_CHECK_EQUAL(bCouldAllocateAgainIn09, EXPECTED_VALUE);
    BOOST_CHECK_EQUAL(bCouldAllocateAgainIn10, EXPECTED_VALUE);
    BOOST_CHECK_EQUAL(bCouldAllocateAgainIn11, EXPECTED_VALUE);
    BOOST_CHECK_EQUAL(bCouldAllocateAgainIn12, EXPECTED_VALUE);
    BOOST_CHECK_EQUAL(bCouldAllocateAgainIn13, EXPECTED_VALUE);
    BOOST_CHECK_EQUAL(bCouldAllocateAgainIn14, EXPECTED_VALUE);
    BOOST_CHECK_EQUAL(bCouldAllocateAgainIn15, EXPECTED_VALUE);
    BOOST_CHECK_EQUAL(bCouldAllocateAgainIn16, EXPECTED_VALUE);
    BOOST_CHECK_EQUAL(bCouldAllocateAgainIn17, EXPECTED_VALUE);
    BOOST_CHECK_EQUAL(bCouldAllocateAgainIn18, EXPECTED_VALUE);
    BOOST_CHECK_EQUAL(bCouldAllocateAgainIn19, EXPECTED_VALUE);
    BOOST_CHECK_EQUAL(bCouldAllocateAgainIn20, EXPECTED_VALUE);
}

/// <summary>
/// Checks that it returns False when there is not enough free space in the buffer due to the alignment adjustment.
/// </summary>
QTEST_CASE ( CanAllocate2_ReturnsFalseWhenThereIsNotEnoughFreeSpaceDueToAlignmentAdjustment_Test )
{
    // [Preparation]
    const pointer_uint_q INPUT_SIZE = 6U;
    const QAlignment INPUT_ALIGNMENT(4U);
    QStackAllocator allocator(32U, INPUT_ALIGNMENT);
    allocator.Allocate(2U);
    const bool EXPECTED_RESULT = false;

    // [Execution]
    bool bResult = allocator.CanAllocate(INPUT_SIZE, INPUT_ALIGNMENT);

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

#if QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the sum of the sizes of all allocated memory blocks
/// into stack allocator is greater than the preallocated block size.
/// </summary>
QTEST_CASE(GetAllocatedBytes_AssertionFailsWhenSizeOfAllAllocatedMemoryBlocksIsGreaterThanPreallocatedBlockSize_Test)
{
    // [Preparation]

    const bool                     ASSERTION_FAILED                           = true;
    const pointer_uint_q           AMOUNT_CASES                               = 25;

    const pointer_uint_q           VALID_PREALLOCATION_SIZE                   = 64;
    const pointer_uint_q           VALID_ALLOCATION_SIZE                      = 32;

    const pointer_uint_q           VALID_PREALLOCATION_ALIGNMENT_VALUE01      = 2;
    const pointer_uint_q           VALID_PREALLOCATION_ALIGNMENT_VALUE02      = 4;
    const pointer_uint_q           VALID_PREALLOCATION_ALIGNMENT_VALUE03      = 8;
    const pointer_uint_q           VALID_PREALLOCATION_ALIGNMENT_VALUE04      = 16;

    const pointer_uint_q           INCREMENT_VALUE                            = 0X100;

    bool                           bAssertionFailedIn01                       = false;
    bool                           bAssertionFailedIn02                       = false;
    bool                           bAssertionFailedIn03                       = false;
    bool                           bAssertionFailedIn04                       = false;
    bool                           bAssertionFailedIn05                       = false;
    bool                           bAssertionFailedIn06                       = false;
    bool                           bAssertionFailedIn07                       = false;
    bool                           bAssertionFailedIn08                       = false;
    bool                           bAssertionFailedIn09                       = false;
    bool                           bAssertionFailedIn10                       = false;
    bool                           bAssertionFailedIn11                       = false;
    bool                           bAssertionFailedIn12                       = false;
    bool                           bAssertionFailedIn13                       = false;
    bool                           bAssertionFailedIn14                       = false;
    bool                           bAssertionFailedIn15                       = false;
    bool                           bAssertionFailedIn16                       = false;
    bool                           bAssertionFailedIn17                       = false;
    bool                           bAssertionFailedIn18                       = false;
    bool                           bAssertionFailedIn19                       = false;
    bool                           bAssertionFailedIn20                       = false;
    bool                           bAssertionFailedIn21                       = false;
    bool                           bAssertionFailedIn22                       = false;
    bool                           bAssertionFailedIn23                       = false;
    bool                           bAssertionFailedIn24                       = false;
    bool                           bAssertionFailedIn25                       = false;

    pointer_uint_q                 u                                          = 0;


	// [Execution]

    QStackAllocatorWhiteBox        stackAllocatorWhiteBox01( VALID_PREALLOCATION_SIZE );
    QStackAllocatorWhiteBox        stackAllocatorWhiteBox02( VALID_PREALLOCATION_SIZE );
    QStackAllocatorWhiteBox        stackAllocatorWhiteBox03( VALID_PREALLOCATION_SIZE );
    QStackAllocatorWhiteBox        stackAllocatorWhiteBox04( VALID_PREALLOCATION_SIZE );
    QStackAllocatorWhiteBox        stackAllocatorWhiteBox05( VALID_PREALLOCATION_SIZE );
    QStackAllocatorWhiteBox        stackAllocatorWhiteBox06( VALID_PREALLOCATION_SIZE, QAlignment(VALID_PREALLOCATION_ALIGNMENT_VALUE01) );
    QStackAllocatorWhiteBox        stackAllocatorWhiteBox07( VALID_PREALLOCATION_SIZE, QAlignment(VALID_PREALLOCATION_ALIGNMENT_VALUE01) );
    QStackAllocatorWhiteBox        stackAllocatorWhiteBox08( VALID_PREALLOCATION_SIZE, QAlignment(VALID_PREALLOCATION_ALIGNMENT_VALUE01) );
    QStackAllocatorWhiteBox        stackAllocatorWhiteBox09( VALID_PREALLOCATION_SIZE, QAlignment(VALID_PREALLOCATION_ALIGNMENT_VALUE01) );
    QStackAllocatorWhiteBox        stackAllocatorWhiteBox10( VALID_PREALLOCATION_SIZE, QAlignment(VALID_PREALLOCATION_ALIGNMENT_VALUE01) );
    QStackAllocatorWhiteBox        stackAllocatorWhiteBox11( VALID_PREALLOCATION_SIZE, QAlignment(VALID_PREALLOCATION_ALIGNMENT_VALUE02) );
    QStackAllocatorWhiteBox        stackAllocatorWhiteBox12( VALID_PREALLOCATION_SIZE, QAlignment(VALID_PREALLOCATION_ALIGNMENT_VALUE02) );
    QStackAllocatorWhiteBox        stackAllocatorWhiteBox13( VALID_PREALLOCATION_SIZE, QAlignment(VALID_PREALLOCATION_ALIGNMENT_VALUE02) );
    QStackAllocatorWhiteBox        stackAllocatorWhiteBox14( VALID_PREALLOCATION_SIZE, QAlignment(VALID_PREALLOCATION_ALIGNMENT_VALUE02) );
    QStackAllocatorWhiteBox        stackAllocatorWhiteBox15( VALID_PREALLOCATION_SIZE, QAlignment(VALID_PREALLOCATION_ALIGNMENT_VALUE02) );
    QStackAllocatorWhiteBox        stackAllocatorWhiteBox16( VALID_PREALLOCATION_SIZE, QAlignment(VALID_PREALLOCATION_ALIGNMENT_VALUE03) );
    QStackAllocatorWhiteBox        stackAllocatorWhiteBox17( VALID_PREALLOCATION_SIZE, QAlignment(VALID_PREALLOCATION_ALIGNMENT_VALUE03) );
    QStackAllocatorWhiteBox        stackAllocatorWhiteBox18( VALID_PREALLOCATION_SIZE, QAlignment(VALID_PREALLOCATION_ALIGNMENT_VALUE03) );
    QStackAllocatorWhiteBox        stackAllocatorWhiteBox19( VALID_PREALLOCATION_SIZE, QAlignment(VALID_PREALLOCATION_ALIGNMENT_VALUE03) );
    QStackAllocatorWhiteBox        stackAllocatorWhiteBox20( VALID_PREALLOCATION_SIZE, QAlignment(VALID_PREALLOCATION_ALIGNMENT_VALUE03) );
    QStackAllocatorWhiteBox        stackAllocatorWhiteBox21( VALID_PREALLOCATION_SIZE, QAlignment(VALID_PREALLOCATION_ALIGNMENT_VALUE04) );
    QStackAllocatorWhiteBox        stackAllocatorWhiteBox22( VALID_PREALLOCATION_SIZE, QAlignment(VALID_PREALLOCATION_ALIGNMENT_VALUE04) );
    QStackAllocatorWhiteBox        stackAllocatorWhiteBox23( VALID_PREALLOCATION_SIZE, QAlignment(VALID_PREALLOCATION_ALIGNMENT_VALUE04) );
    QStackAllocatorWhiteBox        stackAllocatorWhiteBox24( VALID_PREALLOCATION_SIZE, QAlignment(VALID_PREALLOCATION_ALIGNMENT_VALUE04) );
    QStackAllocatorWhiteBox        stackAllocatorWhiteBox25( VALID_PREALLOCATION_SIZE, QAlignment(VALID_PREALLOCATION_ALIGNMENT_VALUE04) );

    stackAllocatorWhiteBox01.Allocate( VALID_ALLOCATION_SIZE );
    stackAllocatorWhiteBox02.Allocate( VALID_ALLOCATION_SIZE, QAlignment(VALID_PREALLOCATION_ALIGNMENT_VALUE01) );
    stackAllocatorWhiteBox03.Allocate( VALID_ALLOCATION_SIZE, QAlignment(VALID_PREALLOCATION_ALIGNMENT_VALUE02) );
    stackAllocatorWhiteBox04.Allocate( VALID_ALLOCATION_SIZE, QAlignment(VALID_PREALLOCATION_ALIGNMENT_VALUE03) );
    stackAllocatorWhiteBox05.Allocate( VALID_ALLOCATION_SIZE, QAlignment(VALID_PREALLOCATION_ALIGNMENT_VALUE04) );
    stackAllocatorWhiteBox06.Allocate( VALID_ALLOCATION_SIZE );
    stackAllocatorWhiteBox07.Allocate( VALID_ALLOCATION_SIZE, QAlignment(VALID_PREALLOCATION_ALIGNMENT_VALUE01) );
    stackAllocatorWhiteBox08.Allocate( VALID_ALLOCATION_SIZE, QAlignment(VALID_PREALLOCATION_ALIGNMENT_VALUE02) );
    stackAllocatorWhiteBox09.Allocate( VALID_ALLOCATION_SIZE, QAlignment(VALID_PREALLOCATION_ALIGNMENT_VALUE03) );
    stackAllocatorWhiteBox10.Allocate( VALID_ALLOCATION_SIZE, QAlignment(VALID_PREALLOCATION_ALIGNMENT_VALUE04) );
    stackAllocatorWhiteBox11.Allocate( VALID_ALLOCATION_SIZE );
    stackAllocatorWhiteBox12.Allocate( VALID_ALLOCATION_SIZE, QAlignment(VALID_PREALLOCATION_ALIGNMENT_VALUE01) );
    stackAllocatorWhiteBox13.Allocate( VALID_ALLOCATION_SIZE, QAlignment(VALID_PREALLOCATION_ALIGNMENT_VALUE02) );
    stackAllocatorWhiteBox14.Allocate( VALID_ALLOCATION_SIZE, QAlignment(VALID_PREALLOCATION_ALIGNMENT_VALUE03) );
    stackAllocatorWhiteBox15.Allocate( VALID_ALLOCATION_SIZE, QAlignment(VALID_PREALLOCATION_ALIGNMENT_VALUE04) );
    stackAllocatorWhiteBox16.Allocate( VALID_ALLOCATION_SIZE );
    stackAllocatorWhiteBox17.Allocate( VALID_ALLOCATION_SIZE, QAlignment(VALID_PREALLOCATION_ALIGNMENT_VALUE01) );
    stackAllocatorWhiteBox18.Allocate( VALID_ALLOCATION_SIZE, QAlignment(VALID_PREALLOCATION_ALIGNMENT_VALUE02) );
    stackAllocatorWhiteBox19.Allocate( VALID_ALLOCATION_SIZE, QAlignment(VALID_PREALLOCATION_ALIGNMENT_VALUE03) );
    stackAllocatorWhiteBox20.Allocate( VALID_ALLOCATION_SIZE, QAlignment(VALID_PREALLOCATION_ALIGNMENT_VALUE04) );
    stackAllocatorWhiteBox21.Allocate( VALID_ALLOCATION_SIZE );
    stackAllocatorWhiteBox22.Allocate( VALID_ALLOCATION_SIZE, QAlignment(VALID_PREALLOCATION_ALIGNMENT_VALUE01) );
    stackAllocatorWhiteBox23.Allocate( VALID_ALLOCATION_SIZE, QAlignment(VALID_PREALLOCATION_ALIGNMENT_VALUE02) );
    stackAllocatorWhiteBox24.Allocate( VALID_ALLOCATION_SIZE, QAlignment(VALID_PREALLOCATION_ALIGNMENT_VALUE03) );
    stackAllocatorWhiteBox25.Allocate( VALID_ALLOCATION_SIZE, QAlignment(VALID_PREALLOCATION_ALIGNMENT_VALUE04) );

    // Sabotage of the allocated bytes.
    pointer_uint_q uAux = stackAllocatorWhiteBox01.GetAllocatedBytes();
    uAux               += INCREMENT_VALUE;
    stackAllocatorWhiteBox01.SetuAllocatedBytes(uAux);
    uAux                = stackAllocatorWhiteBox02.GetAllocatedBytes();
    uAux               += INCREMENT_VALUE;
    stackAllocatorWhiteBox02.SetuAllocatedBytes(uAux);  
    uAux                = stackAllocatorWhiteBox03.GetAllocatedBytes();
    uAux               += INCREMENT_VALUE;
    stackAllocatorWhiteBox03.SetuAllocatedBytes(uAux); 
    uAux                = stackAllocatorWhiteBox04.GetAllocatedBytes();
    uAux               += INCREMENT_VALUE;
    stackAllocatorWhiteBox04.SetuAllocatedBytes(uAux);
    uAux                = stackAllocatorWhiteBox05.GetAllocatedBytes();
    uAux               += INCREMENT_VALUE;
    stackAllocatorWhiteBox05.SetuAllocatedBytes(uAux); 
    uAux                = stackAllocatorWhiteBox06.GetAllocatedBytes();
    uAux               += INCREMENT_VALUE;
    stackAllocatorWhiteBox06.SetuAllocatedBytes(uAux); 
    uAux                = stackAllocatorWhiteBox07.GetAllocatedBytes();
    uAux               += INCREMENT_VALUE;
    stackAllocatorWhiteBox07.SetuAllocatedBytes(uAux); 
    uAux                = stackAllocatorWhiteBox08.GetAllocatedBytes();
    uAux               += INCREMENT_VALUE;
    stackAllocatorWhiteBox08.SetuAllocatedBytes(uAux); 
    uAux                = stackAllocatorWhiteBox09.GetAllocatedBytes();
    uAux               += INCREMENT_VALUE;
    stackAllocatorWhiteBox09.SetuAllocatedBytes(uAux); 
    uAux                = stackAllocatorWhiteBox10.GetAllocatedBytes();
    uAux               += INCREMENT_VALUE;
    stackAllocatorWhiteBox10.SetuAllocatedBytes(uAux); 
    uAux                = stackAllocatorWhiteBox11.GetAllocatedBytes();
    uAux               += INCREMENT_VALUE;
    stackAllocatorWhiteBox11.SetuAllocatedBytes(uAux); 
    uAux                = stackAllocatorWhiteBox12.GetAllocatedBytes();
    uAux               += INCREMENT_VALUE;
    stackAllocatorWhiteBox12.SetuAllocatedBytes(uAux); 
    uAux                = stackAllocatorWhiteBox13.GetAllocatedBytes();
    uAux               += INCREMENT_VALUE;
    stackAllocatorWhiteBox13.SetuAllocatedBytes(uAux); 
    uAux                = stackAllocatorWhiteBox14.GetAllocatedBytes();
    uAux               += INCREMENT_VALUE;
    stackAllocatorWhiteBox14.SetuAllocatedBytes(uAux); 
    uAux                = stackAllocatorWhiteBox15.GetAllocatedBytes();
    uAux               += INCREMENT_VALUE;
    stackAllocatorWhiteBox15.SetuAllocatedBytes(uAux); 
    uAux                = stackAllocatorWhiteBox16.GetAllocatedBytes();
    uAux               += INCREMENT_VALUE;
    stackAllocatorWhiteBox16.SetuAllocatedBytes(uAux); 
    uAux                = stackAllocatorWhiteBox17.GetAllocatedBytes();
    uAux               += INCREMENT_VALUE;
    stackAllocatorWhiteBox17.SetuAllocatedBytes(uAux); 
    uAux                = stackAllocatorWhiteBox18.GetAllocatedBytes();
    uAux               += INCREMENT_VALUE;
    stackAllocatorWhiteBox18.SetuAllocatedBytes(uAux); 
    uAux                = stackAllocatorWhiteBox19.GetAllocatedBytes();
    uAux               += INCREMENT_VALUE;
    stackAllocatorWhiteBox19.SetuAllocatedBytes(uAux); 
    uAux                = stackAllocatorWhiteBox20.GetAllocatedBytes();
    uAux               += INCREMENT_VALUE;
    stackAllocatorWhiteBox20.SetuAllocatedBytes(uAux); 
    uAux                = stackAllocatorWhiteBox21.GetAllocatedBytes();
    uAux               += INCREMENT_VALUE;
    stackAllocatorWhiteBox21.SetuAllocatedBytes(uAux); 
    uAux                = stackAllocatorWhiteBox22.GetAllocatedBytes();
    uAux               += INCREMENT_VALUE;
    stackAllocatorWhiteBox22.SetuAllocatedBytes(uAux); 
    uAux                = stackAllocatorWhiteBox23.GetAllocatedBytes();
    uAux               += INCREMENT_VALUE;
    stackAllocatorWhiteBox23.SetuAllocatedBytes(uAux); 
    uAux                = stackAllocatorWhiteBox24.GetAllocatedBytes();
    uAux               += INCREMENT_VALUE;
    stackAllocatorWhiteBox24.SetuAllocatedBytes(uAux); 
    uAux                = stackAllocatorWhiteBox25.GetAllocatedBytes();
    uAux               += INCREMENT_VALUE;
    stackAllocatorWhiteBox25.SetuAllocatedBytes(uAux); 

    uAux                = 0;

    for (u = 1; u <= AMOUNT_CASES; ++u)
    {
        try
        {
            switch (u)
            {
                case 1:  uAux = stackAllocatorWhiteBox01.GetAllocatedBytes(); break;
                case 2:  uAux = stackAllocatorWhiteBox02.GetAllocatedBytes(); break;
                case 3:  uAux = stackAllocatorWhiteBox03.GetAllocatedBytes(); break;
                case 4:  uAux = stackAllocatorWhiteBox04.GetAllocatedBytes(); break;
                case 5:  uAux = stackAllocatorWhiteBox05.GetAllocatedBytes(); break;
                case 6:  uAux = stackAllocatorWhiteBox05.GetAllocatedBytes(); break;
                case 7:  uAux = stackAllocatorWhiteBox05.GetAllocatedBytes(); break;
                case 8:  uAux = stackAllocatorWhiteBox05.GetAllocatedBytes(); break;
                case 9:  uAux = stackAllocatorWhiteBox05.GetAllocatedBytes(); break;
                case 10: uAux = stackAllocatorWhiteBox10.GetAllocatedBytes(); break;
                case 11: uAux = stackAllocatorWhiteBox11.GetAllocatedBytes(); break;
                case 12: uAux = stackAllocatorWhiteBox12.GetAllocatedBytes(); break;
                case 13: uAux = stackAllocatorWhiteBox13.GetAllocatedBytes(); break;
                case 14: uAux = stackAllocatorWhiteBox14.GetAllocatedBytes(); break;
                case 15: uAux = stackAllocatorWhiteBox15.GetAllocatedBytes(); break;
                case 16: uAux = stackAllocatorWhiteBox16.GetAllocatedBytes(); break;
                case 17: uAux = stackAllocatorWhiteBox17.GetAllocatedBytes(); break;
                case 18: uAux = stackAllocatorWhiteBox18.GetAllocatedBytes(); break;
                case 19: uAux = stackAllocatorWhiteBox19.GetAllocatedBytes(); break;
                case 20: uAux = stackAllocatorWhiteBox20.GetAllocatedBytes(); break;
                case 21: uAux = stackAllocatorWhiteBox21.GetAllocatedBytes(); break;
                case 22: uAux = stackAllocatorWhiteBox22.GetAllocatedBytes(); break;
                case 23: uAux = stackAllocatorWhiteBox23.GetAllocatedBytes(); break;
                case 24: uAux = stackAllocatorWhiteBox24.GetAllocatedBytes(); break;
                case 25: uAux = stackAllocatorWhiteBox25.GetAllocatedBytes(); break;
            }
        }
        catch(const QAssertException&)
        {
            switch (u)
            {
                case 1:
                    if (false == bAssertionFailedIn01)
                    {
                        bAssertionFailedIn01 = true;
                    }
                break;
                case 2:
                    if (false == bAssertionFailedIn02)
                    {
                        bAssertionFailedIn02 = true;
                    }
                break;
                case 3:
                    if (false == bAssertionFailedIn03)
                    {
                        bAssertionFailedIn03 = true;
                    }
                break;
                case 4:
                    if (false == bAssertionFailedIn04)
                    {
                        bAssertionFailedIn04 = true;
                    }
                break;
                case 5:
                    if (false == bAssertionFailedIn05)
                    {
                        bAssertionFailedIn05 = true;
                    }
                break;
                case 6:
                    if (false == bAssertionFailedIn06)
                    {
                        bAssertionFailedIn06 = true;
                    }
                break;
                case 7:
                    if (false == bAssertionFailedIn07)
                    {
                        bAssertionFailedIn07 = true;
                    }
                break;
                case 8:
                    if (false == bAssertionFailedIn08)
                    {
                        bAssertionFailedIn08 = true;
                    }
                break;
                case 9:
                    if (false == bAssertionFailedIn09)
                    {
                        bAssertionFailedIn09 = true;
                    }
                break;
                case 10:
                    if (false == bAssertionFailedIn10)
                    {
                        bAssertionFailedIn10 = true;
                    }
                break;
                case 11:
                    if (false == bAssertionFailedIn11)
                    {
                        bAssertionFailedIn11 = true;
                    }
                break;
                case 12:
                    if (false == bAssertionFailedIn12)
                    {
                        bAssertionFailedIn12 = true;
                    }
                break;
                case 13:
                    if (false == bAssertionFailedIn13)
                    {
                        bAssertionFailedIn13 = true;
                    }
                break;
                case 14:
                    if (false == bAssertionFailedIn14)
                    {
                        bAssertionFailedIn14 = true;
                    }
                break;
                case 15:
                    if (false == bAssertionFailedIn15)
                    {
                        bAssertionFailedIn15 = true;
                    }
                break;
                case 16:
                    if (false == bAssertionFailedIn16)
                    {
                        bAssertionFailedIn16 = true;
                    }
                break;
                case 17:
                    if (false == bAssertionFailedIn17)
                    {
                        bAssertionFailedIn17 = true;
                    }
                break;
                case 18:
                    if (false == bAssertionFailedIn18)
                    {
                        bAssertionFailedIn18 = true;
                    }
                break;
                case 19:
                    if (false == bAssertionFailedIn19)
                    {
                        bAssertionFailedIn19 = true;
                    }
                break;
                case 20:
                    if (false == bAssertionFailedIn20)
                    {
                        bAssertionFailedIn20 = true;
                    }
                break;
                case 21:
                    if (false == bAssertionFailedIn21)
                    {
                        bAssertionFailedIn21 = true;
                    }
                break;
                case 22:
                    if (false == bAssertionFailedIn22)
                    {
                        bAssertionFailedIn22 = true;
                    }
                break;
                case 23:
                    if (false == bAssertionFailedIn23)
                    {
                        bAssertionFailedIn23 = true;
                    }
                break;
                case 24:
                    if (false == bAssertionFailedIn24)
                    {
                        bAssertionFailedIn24 = true;
                    }
                break;
                case 25:
                    if (false == bAssertionFailedIn25)
                    {
                        bAssertionFailedIn25 = true;
                    }
                break;
            };
        }
    }


    // [Verification]

    BOOST_CHECK_EQUAL(bAssertionFailedIn01, ASSERTION_FAILED);
    BOOST_CHECK_EQUAL(bAssertionFailedIn02, ASSERTION_FAILED);
    BOOST_CHECK_EQUAL(bAssertionFailedIn03, ASSERTION_FAILED);
    BOOST_CHECK_EQUAL(bAssertionFailedIn04, ASSERTION_FAILED);
    BOOST_CHECK_EQUAL(bAssertionFailedIn05, ASSERTION_FAILED);
    BOOST_CHECK_EQUAL(bAssertionFailedIn06, ASSERTION_FAILED);
    BOOST_CHECK_EQUAL(bAssertionFailedIn07, ASSERTION_FAILED);
    BOOST_CHECK_EQUAL(bAssertionFailedIn08, ASSERTION_FAILED);
    BOOST_CHECK_EQUAL(bAssertionFailedIn09, ASSERTION_FAILED);
    BOOST_CHECK_EQUAL(bAssertionFailedIn10, ASSERTION_FAILED);
    BOOST_CHECK_EQUAL(bAssertionFailedIn11, ASSERTION_FAILED);
    BOOST_CHECK_EQUAL(bAssertionFailedIn12, ASSERTION_FAILED);
    BOOST_CHECK_EQUAL(bAssertionFailedIn13, ASSERTION_FAILED);
    BOOST_CHECK_EQUAL(bAssertionFailedIn14, ASSERTION_FAILED);
    BOOST_CHECK_EQUAL(bAssertionFailedIn15, ASSERTION_FAILED);
    BOOST_CHECK_EQUAL(bAssertionFailedIn16, ASSERTION_FAILED);
    BOOST_CHECK_EQUAL(bAssertionFailedIn17, ASSERTION_FAILED);
    BOOST_CHECK_EQUAL(bAssertionFailedIn18, ASSERTION_FAILED);
    BOOST_CHECK_EQUAL(bAssertionFailedIn19, ASSERTION_FAILED);
    BOOST_CHECK_EQUAL(bAssertionFailedIn20, ASSERTION_FAILED);
    BOOST_CHECK_EQUAL(bAssertionFailedIn21, ASSERTION_FAILED);
    BOOST_CHECK_EQUAL(bAssertionFailedIn22, ASSERTION_FAILED);
    BOOST_CHECK_EQUAL(bAssertionFailedIn23, ASSERTION_FAILED);
    BOOST_CHECK_EQUAL(bAssertionFailedIn24, ASSERTION_FAILED);
    BOOST_CHECK_EQUAL(bAssertionFailedIn25, ASSERTION_FAILED);
}

#endif // QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

#if QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the size of the resident allocator is zero.
/// </summary>
QTEST_CASE(CopyTo_AssertionFailsWhenSizeOfResidentAllocatorIsZero_Test)
{
    // [Preparation]

    const bool                 ASSERTION_FAILED                           = true;

    // For the resident stack allocator.
    const pointer_uint_q       VALID_PREALLOCATION_SIZE_LESSER            = 64;
 
    // For the input stack allocator.
    const pointer_uint_q       VALID_PREALLOCATION_SIZE_GREATER           = 128;  
    const pointer_uint_q       VALID_ALLOCATION_SIZE_GREATER              = 32;

    const pointer_uint_q       VALID_PREALLOCATION_ALIGNMENT_VALUE01      = 2;
    const pointer_uint_q       VALID_PREALLOCATION_ALIGNMENT_VALUE02      = 4;
    const QAlignment           PREALLOCATION_ALIGMENT01(VALID_PREALLOCATION_ALIGNMENT_VALUE01);
    const QAlignment           PREALLOCATION_ALIGMENT02(VALID_PREALLOCATION_ALIGNMENT_VALUE02);

    const pointer_uint_q       VALID_ALLOCATION_ALIGNMENT_VALUE01          = 2;
    const pointer_uint_q       VALID_ALLOCATION_ALIGNMENT_VALUE02          = 4;
    const QAlignment           ALLOCATION_ALIGMENT01(VALID_ALLOCATION_ALIGNMENT_VALUE01);
    const QAlignment           ALLOCATION_ALIGMENT02(VALID_ALLOCATION_ALIGNMENT_VALUE02);

    bool                       bAssertionFailed                            = false;


    // [Execution]

    QStackAllocatorWhiteBox    stackAllocatorWhiteBoxResident(VALID_PREALLOCATION_SIZE_LESSER, PREALLOCATION_ALIGMENT01);
    QStackAllocatorWhiteBox    stackAllocatorWhiteBoxInput(VALID_PREALLOCATION_SIZE_GREATER,   PREALLOCATION_ALIGMENT02);

    // Stabotage of the resident stack allocator.
    stackAllocatorWhiteBoxResident.SabotageStackAllocator();

    // Provisional allocation on input stack allocator.
    stackAllocatorWhiteBoxInput.Allocate(VALID_ALLOCATION_SIZE_GREATER, ALLOCATION_ALIGMENT01);

    // Now it is time for the copy.
    try
    {
        stackAllocatorWhiteBoxResident.CopyTo(stackAllocatorWhiteBoxInput);
    }
    catch(const QAssertException&)
    {
        bAssertionFailed = true;
    }


    // [Verification]
    BOOST_CHECK_EQUAL( bAssertionFailed, ASSERTION_FAILED );
}

/// <summary>
/// Checks that an assertion fails when the size of the input allocator is zero.
/// </summary>
QTEST_CASE(CopyTo_AssertionFailsWhenSizeOfInputAllocatorIsZero_Test)
{
    // [Preparation]

    const bool                 ASSERTION_FAILED                           = true;

    // For the resident stack allocator.
    const pointer_uint_q       VALID_PREALLOCATION_SIZE_LESSER            = 64;
    const pointer_uint_q       VALID_ALLOCATION_SIZE_LESSER               = 16;

    // For the input stack allocator.
    const pointer_uint_q       VALID_PREALLOCATION_SIZE_GREATER           = 128;  

    const pointer_uint_q       VALID_PREALLOCATION_ALIGNMENT_VALUE01      = 2;
    const pointer_uint_q       VALID_PREALLOCATION_ALIGNMENT_VALUE02      = 4;
    const QAlignment           PREALLOCATION_ALIGMENT01(VALID_PREALLOCATION_ALIGNMENT_VALUE01);
    const QAlignment           PREALLOCATION_ALIGMENT02(VALID_PREALLOCATION_ALIGNMENT_VALUE02);

    const pointer_uint_q       VALID_ALLOCATION_ALIGNMENT_VALUE01          = 2;
    const pointer_uint_q       VALID_ALLOCATION_ALIGNMENT_VALUE02          = 4;
    const QAlignment           ALLOCATION_ALIGMENT01(VALID_ALLOCATION_ALIGNMENT_VALUE01);
    const QAlignment           ALLOCATION_ALIGMENT02(VALID_ALLOCATION_ALIGNMENT_VALUE02);

    bool                       bAssertionFailed                            = false;


    // [Execution]

    QStackAllocatorWhiteBox    stackAllocatorWhiteBoxResident(VALID_PREALLOCATION_SIZE_LESSER, PREALLOCATION_ALIGMENT01);
    QStackAllocatorWhiteBox    stackAllocatorWhiteBoxInput(VALID_PREALLOCATION_SIZE_GREATER,   PREALLOCATION_ALIGMENT02);

    // Provisional allocation in resident stack allocator.
    stackAllocatorWhiteBoxResident.Allocate(VALID_ALLOCATION_SIZE_LESSER, ALLOCATION_ALIGMENT01);

    // Stabotage of the passed stack allocator.
    stackAllocatorWhiteBoxInput.SabotageStackAllocator();

    // Now it is time for the copy.
    try
    {
        stackAllocatorWhiteBoxResident.CopyTo(stackAllocatorWhiteBoxInput);
    }
    catch(const QAssertException&)
    {
        bAssertionFailed = true;
    }


    // [Verification]
    BOOST_CHECK_EQUAL( bAssertionFailed, ASSERTION_FAILED );
}

/// <summary>
/// Checks that an assertion fails when the size of the input allocator has a preallocated size lower than
/// the size of the resident one.
/// </summary>
QTEST_CASE(CopyTo_AssertionFailsWhenSizeOfInputAllocatorIsLowerThanSizeOfTheResidentOne_Test)
{
    // [Preparation]

    const bool                 ASSERTION_FAILED                           = true;

    // For the resident stack allocator.
    const pointer_uint_q       VALID_PREALLOCATION_SIZE_GREATER           = 128;  
    const pointer_uint_q       VALID_ALLOCATION_SIZE_GREATER              = 32;

    // For the input stack allocator.
    const pointer_uint_q       VALID_PREALLOCATION_SIZE_LESSER            = 64;
    const pointer_uint_q       VALID_ALLOCATION_SIZE_LESSER               = 16;

    const pointer_uint_q       VALID_PREALLOCATION_ALIGNMENT_VALUE01      = 2;
    const pointer_uint_q       VALID_PREALLOCATION_ALIGNMENT_VALUE02      = 4;
    const QAlignment           PREALLOCATION_ALIGMENT01(VALID_PREALLOCATION_ALIGNMENT_VALUE01);
    const QAlignment           PREALLOCATION_ALIGMENT02(VALID_PREALLOCATION_ALIGNMENT_VALUE02);

    const pointer_uint_q       VALID_ALLOCATION_ALIGNMENT_VALUE01          = 2;
    const pointer_uint_q       VALID_ALLOCATION_ALIGNMENT_VALUE02          = 4;
    const QAlignment           ALLOCATION_ALIGMENT01(VALID_ALLOCATION_ALIGNMENT_VALUE01);
    const QAlignment           ALLOCATION_ALIGMENT02(VALID_ALLOCATION_ALIGNMENT_VALUE02);

    bool                       bAssertionFailed                            = false;


    // [Execution]

    QStackAllocator            stackAllocatorResident(VALID_PREALLOCATION_SIZE_GREATER, PREALLOCATION_ALIGMENT01);
    QStackAllocator            stackAllocatorInput(VALID_PREALLOCATION_SIZE_LESSER,     PREALLOCATION_ALIGMENT02);

    // Provisional allocations.
    stackAllocatorResident.Allocate(VALID_ALLOCATION_SIZE_GREATER, ALLOCATION_ALIGMENT01);
    stackAllocatorInput.Allocate(VALID_ALLOCATION_SIZE_LESSER,     ALLOCATION_ALIGMENT02);

    // Now it is time for the copy.
    try
    {
        stackAllocatorResident.CopyTo(stackAllocatorInput);
    }
    catch(const QAssertException&)
    {
        bAssertionFailed = true;
    }


    // [Verification]
    BOOST_CHECK_EQUAL( bAssertionFailed, ASSERTION_FAILED );
}

#endif // QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that the stack allocator is correctly copied.
/// </summary>
QTEST_CASE(CopyTo_TheStackAllocatorIsCorrectlyCopied_Test)
{
    // [Preparation]

    const bool                 EXPECTED_VALUE                             = true;

    // For the resident stack allocator.
    const pointer_uint_q       VALID_PREALLOCATION_SIZE_LESSER            = 64;
    const pointer_uint_q       VALID_ALLOCATION_SIZE_LESSER01             = 16;
    const pointer_uint_q       VALID_ALLOCATION_SIZE_LESSER02             = 8;

    // For the passed stack allocator.
    const pointer_uint_q       VALID_PREALLOCATION_SIZE_GREATER           = 128;
    const pointer_uint_q       VALID_ALLOCATION_SIZE_GREATER              = 32;

    // After the copy, is expected for the passed stack allocator to have a preallocated size
    // equals to 'VALID_PREALLOCATION_SIZE_GREATER' bytes and an amount of allocated bytes
    // equals to 'VALID_ALLOCATION_SIZE_LESSER01 + VALID_ALLOCATION_SIZE_LESSER02 + sizeof(QStackAllocatorWhiteBox::QBlockHeader'.

    const pointer_uint_q       VALID_PREALLOCATION_ALIGNMENT_VALUE01      = 2;
    const pointer_uint_q       VALID_PREALLOCATION_ALIGNMENT_VALUE02      = 4;

    const QAlignment           PREALLOCATION_ALIGMENT01(VALID_PREALLOCATION_ALIGNMENT_VALUE01);
    const QAlignment           PREALLOCATION_ALIGMENT02(VALID_PREALLOCATION_ALIGNMENT_VALUE02);

    const pointer_uint_q       VALID_ALLOCATION_ALIGNMENT_VALUE01          = 2;
    const pointer_uint_q       VALID_ALLOCATION_ALIGNMENT_VALUE02          = 4;
    const pointer_uint_q       VALID_ALLOCATION_ALIGNMENT_VALUE03          = 8;
    const QAlignment           ALLOCATION_ALIGMENT01(VALID_ALLOCATION_ALIGNMENT_VALUE01);
    const QAlignment           ALLOCATION_ALIGMENT02(VALID_ALLOCATION_ALIGNMENT_VALUE02);
    const QAlignment           ALLOCATION_ALIGMENT03(VALID_ALLOCATION_ALIGNMENT_VALUE03);

    void*                      pStackBaseBeforeCopy                       = null_q;
    void*                      pStackBaseAfterCopy                        = null_q;

    pointer_uint_q             uPreallocatedBlockSizeBeforeCopy           = 0;
    pointer_uint_q             uPreallocatedBlockSizeAfterCopy            = 0;

    pointer_uint_q             uAlignmentValueAfterCopy                   = 0;

    bool                       bSamePreallocationSizeBeforeAndAfterCopy   = false;
    bool                       bSameStackBaseBeforeAndAfterCopy           = false;
    bool                       bSameAllocationBytesInBoth                 = false;
    bool                       bSamePreallocationAlignmentValueInBoth     = false;
    bool                       bSameBlockHeadersInBoth                    = true;
    bool                       bSameAmountOfMemoryBlocksInBoth            = false;

    QStackAllocatorWhiteBox    stackAllocatorWhiteBoxResident(VALID_PREALLOCATION_SIZE_LESSER, PREALLOCATION_ALIGMENT01);
    QStackAllocatorWhiteBox    stackAllocatorWhiteBoxPassed(VALID_PREALLOCATION_SIZE_GREATER,  PREALLOCATION_ALIGMENT01);

    // Provisional allocations.
    stackAllocatorWhiteBoxResident.Allocate(VALID_ALLOCATION_SIZE_LESSER01, ALLOCATION_ALIGMENT01);
    stackAllocatorWhiteBoxResident.Allocate(VALID_ALLOCATION_SIZE_LESSER02, ALLOCATION_ALIGMENT02);
    stackAllocatorWhiteBoxPassed.Allocate(VALID_ALLOCATION_SIZE_GREATER,  ALLOCATION_ALIGMENT03);

    // Saving some parameters of the stack allocator that will be passed on before the copy.
    uPreallocatedBlockSizeBeforeCopy = stackAllocatorWhiteBoxPassed.GetSize();
    pStackBaseBeforeCopy             = stackAllocatorWhiteBoxPassed.GetpBase(); 

    // [Execution]

    // Now it is time for the copy.
    stackAllocatorWhiteBoxResident.CopyTo(stackAllocatorWhiteBoxPassed);

    // [Verification]

    // Retrieving some parameters after the copy.
    uPreallocatedBlockSizeAfterCopy  = stackAllocatorWhiteBoxPassed.GetSize();
    pStackBaseAfterCopy              = stackAllocatorWhiteBoxPassed.GetpBase();
    uAlignmentValueAfterCopy         = stackAllocatorWhiteBoxPassed.GetAlignmentValue();

    // At last, traversing the stacks of both stack allocators in order to check that they are the same.
    QStackAllocatorWhiteBox::QMark markForResident( (stackAllocatorWhiteBoxResident.GetMark()).GetMemoryAddress() );

    QStackAllocatorWhiteBox::QBlockHeader* pBlockHeaderInResident = scast_q(stackAllocatorWhiteBoxResident.GetpBase(), QStackAllocatorWhiteBox::QBlockHeader*);
    QStackAllocatorWhiteBox::QBlockHeader* pBlockHeaderInPassed   = scast_q(stackAllocatorWhiteBoxPassed.GetpBase(),   QStackAllocatorWhiteBox::QBlockHeader*);

    do
    {
        if (   (pBlockHeaderInResident->GetAllocatedBlockSize()       != pBlockHeaderInPassed->GetAllocatedBlockSize()       )
            || (pBlockHeaderInResident->GetAlignmentOffset()          != pBlockHeaderInPassed->GetAlignmentOffset()          ) 
            || (pBlockHeaderInResident->GetPreviousHeaderBackOffset() != pBlockHeaderInPassed->GetPreviousHeaderBackOffset() )
           )
        {
            // Something went wrong, current traversed block header in resident stack allocator
            // differs from its corresponding on the passed one.
            bSameBlockHeadersInBoth = false;
        }
        else
        {
            // Current traversed block header (and thus, current memory block) is the same on both stack allocators,
            // so the traverse of both must go on.

            // Computing the address for the next block header in the RESIDENT stack allocator.
            pointer_uint_q uTempAddress = rcast_q(pBlockHeaderInResident, pointer_uint_q);
            uTempAddress               += (  (sizeof(QStackAllocatorWhiteBox::QBlockHeader))
                                           + (pBlockHeaderInResident->GetAlignmentOffset()) + (pBlockHeaderInResident->GetAllocatedBlockSize()) );
            pBlockHeaderInResident      = rcast_q(uTempAddress, QStackAllocatorWhiteBox::QBlockHeader*);

            // Computing the address for the next block header in the PASSED stack allocator.
            uTempAddress          = rcast_q(pBlockHeaderInPassed, pointer_uint_q);
            uTempAddress         += (  (sizeof(QStackAllocatorWhiteBox::QBlockHeader))
                                     + (pBlockHeaderInPassed->GetAlignmentOffset()) + (pBlockHeaderInPassed->GetAllocatedBlockSize()) );
            pBlockHeaderInPassed  = rcast_q(uTempAddress, QStackAllocatorWhiteBox::QBlockHeader*);
        }
    } while (pBlockHeaderInResident < markForResident.GetMemoryAddress() );

    // If everything went right, now 'pBlockHeaderInResident' is pointing exactly to the stack top of the resident stack allocator.

    // If 'bSameBlockHeadersInBoth' equals true, there are the same memory blocks on both stack allocators
    // due to its corresponding block headers stores the same data on both.

    // Apart from, if 'bSameAmountOfMemoryBlocksInBoth' is set to true, it means there is the same amount of memory blocks
    // on each stack allocator.
    if ( pBlockHeaderInPassed == (stackAllocatorWhiteBoxPassed.GetMark()).GetMemoryAddress() )
        bSameAmountOfMemoryBlocksInBoth = true;

    // The remaining checks are auto-explanatory.

    if (uPreallocatedBlockSizeBeforeCopy == uPreallocatedBlockSizeAfterCopy)
        bSamePreallocationSizeBeforeAndAfterCopy = true;

    if (pStackBaseBeforeCopy == pStackBaseAfterCopy)
        bSameStackBaseBeforeAndAfterCopy = true;

    if ( stackAllocatorWhiteBoxResident.GetAllocatedBytes() == stackAllocatorWhiteBoxPassed.GetAllocatedBytes() )
        bSameAllocationBytesInBoth = true;

    if ( uAlignmentValueAfterCopy == stackAllocatorWhiteBoxResident.GetAlignmentValue() )
        bSamePreallocationAlignmentValueInBoth = true;

    bool bAreEqual = memcmp(stackAllocatorWhiteBoxResident.GetpBase(), 
                            stackAllocatorWhiteBoxPassed.GetpBase(), 
                            stackAllocatorWhiteBoxResident.GetAllocatedBytes()) == 0;

    BOOST_CHECK( bAreEqual );
    BOOST_CHECK_EQUAL( bSamePreallocationSizeBeforeAndAfterCopy, EXPECTED_VALUE );
    BOOST_CHECK_EQUAL( bSameStackBaseBeforeAndAfterCopy,         EXPECTED_VALUE );
    BOOST_CHECK_EQUAL( bSameAllocationBytesInBoth,               EXPECTED_VALUE );
    BOOST_CHECK_EQUAL( bSamePreallocationAlignmentValueInBoth,   EXPECTED_VALUE );
    BOOST_CHECK_EQUAL( bSameBlockHeadersInBoth,                  EXPECTED_VALUE );
    BOOST_CHECK_EQUAL( bSameAmountOfMemoryBlocksInBoth,          EXPECTED_VALUE );
}


#if QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the stack allocator was not correctly created.
/// </summary>
QTEST_CASE (GetMark_AssertionFailsWhenTheStackAllocatorWasNotCorrectlyCreated_Test)
{
    // [Preparation]

    const bool                     ASSERTION_FAILED                           = true;

    const pointer_uint_q           VALID_PREALLOCATION_SIZE                   = 64;
    const pointer_uint_q           VALID_ALLOCATION_SIZE                      = 32;

    const pointer_uint_q           VALID_PREALLOCATION_ALIGNMENT_VALUE        = 2;
    const pointer_uint_q           VALID_ALLOCATION_ALIGNMENT_VALUE           = 2;

    bool                           bAssertionFailed                           = false;


    // [Execution]

    QStackAllocatorWhiteBox        stackAllocatorWhiteBox( VALID_PREALLOCATION_SIZE, QAlignment(VALID_PREALLOCATION_ALIGNMENT_VALUE) );
    stackAllocatorWhiteBox.Allocate( VALID_ALLOCATION_SIZE, QAlignment(VALID_ALLOCATION_ALIGNMENT_VALUE) );

    // Stabotage of the resident stack allocator.
    stackAllocatorWhiteBox.SabotageStackAllocator();

    try
    {
        QStackAllocatorWhiteBox::QMarkMocked markMocked( (stackAllocatorWhiteBox.GetMark()).GetMemoryAddress() ); 
    }
    catch(const QAssertException&)
    {
        bAssertionFailed = true;
    }


    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

#elif QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_DISABLED 

/// <summary>
/// Checks that a null mark is returned when the stack allocator was not correctly created.
/// </summary>
QTEST_CASE (GetMark_ANullMarkIsReturnedWhenTheStackAllocatorWasNotCorrectlyCreated_Test)
{
    // [Preparation]

    const bool                     EXPECTED_VALUE                             = true;

    const pointer_uint_q           VALID_PREALLOCATION_SIZE                   = 64;
    const pointer_uint_q           VALID_ALLOCATION_SIZE                      = 32;

    const pointer_uint_q           VALID_PREALLOCATION_ALIGNMENT_VALUE        = 2;
    const pointer_uint_q           VALID_ALLOCATION_ALIGNMENT_VALUE           = 2;

    bool                           bMarkIsNull                                = false;


    // [Execution]

    QStackAllocatorWhiteBox        stackAllocatorWhiteBox( VALID_PREALLOCATION_SIZE, QAlignment(VALID_PREALLOCATION_ALIGNMENT_VALUE) );
    stackAllocatorWhiteBox.Allocate( VALID_ALLOCATION_SIZE, QAlignment(VALID_ALLOCATION_ALIGNMENT_VALUE) );

    // Stabotage of the resident stack allocator.
    stackAllocatorWhiteBox.SabotageStackAllocator();

    QStackAllocator::QMark mark( (stackAllocatorWhiteBox.GetMark()).GetMemoryAddress() );


    // [Verification]

    if ( null_q == mark.GetMemoryAddress()  )
        bMarkIsNull = true;

    BOOST_CHECK_EQUAL(bMarkIsNull, EXPECTED_VALUE);
}

#endif // QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that the address stored into a mark object is not lesser than the stack base of a non empty stack allocator.
/// </summary>
QTEST_CASE (GetMark_AddressStoredIntoAMarkIsNotLesserThanTheStackBaseOfANonEmptyStackAllocator_Test)
{
    // [Preparation]

    const bool                     EXPECTED_VALUE                             = true;

    const pointer_uint_q           VALID_PREALLOCATION_SIZE                   = 64;
    const pointer_uint_q           VALID_ALLOCATION_SIZE                      = 32;

    const pointer_uint_q           VALID_PREALLOCATION_ALIGNMENT_VALUE        = 2;
    const pointer_uint_q           VALID_ALLOCATION_ALIGNMENT_VALUE           = 2;

    bool                           bMarkIsNotLesserThanStackBase              = false;


    // [Execution]

    QStackAllocatorWhiteBox        stackAllocatorWhiteBox( VALID_PREALLOCATION_SIZE, QAlignment(VALID_PREALLOCATION_ALIGNMENT_VALUE) );
    stackAllocatorWhiteBox.Allocate( VALID_ALLOCATION_SIZE, QAlignment(VALID_ALLOCATION_ALIGNMENT_VALUE) );

    QStackAllocatorWhiteBox::QMark mark( (stackAllocatorWhiteBox.GetMark()).GetMemoryAddress() );


    // [Verification]

    if ( mark.GetMemoryAddress() >= stackAllocatorWhiteBox.GetpBase() )
        bMarkIsNotLesserThanStackBase = true;

    BOOST_CHECK_EQUAL(bMarkIsNotLesserThanStackBase, EXPECTED_VALUE);
}

/// <summary>
/// Checks that the address stored into a mark object is not lesser than the stack base of an empty stack allocator.
/// </summary>
QTEST_CASE (GetMark_AddressStoredIntoAMarkIsNotLesserThanTheStackBaseOfAnEmptyStackAllocator_Test)
{
    // [Preparation]

    const bool                     EXPECTED_VALUE                             = true;

    const pointer_uint_q           VALID_PREALLOCATION_SIZE                   = 64;

    const pointer_uint_q           VALID_PREALLOCATION_ALIGNMENT_VALUE        = 2;

    bool                           bMarkIsNotLesserThanStackBase              = false;


    // [Execution]

    QStackAllocatorWhiteBox        stackAllocatorWhiteBox( VALID_PREALLOCATION_SIZE, QAlignment(VALID_PREALLOCATION_ALIGNMENT_VALUE) );

    QStackAllocator::QMark mark( (stackAllocatorWhiteBox.GetMark()).GetMemoryAddress() );


    // [Verification]

    if ( mark.GetMemoryAddress() >= stackAllocatorWhiteBox.GetpBase() )
        bMarkIsNotLesserThanStackBase = true;

    BOOST_CHECK_EQUAL(bMarkIsNotLesserThanStackBase, EXPECTED_VALUE);
}

#if QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that a assertion fails when the size for the preallocated memory block is zero.
/// </summary>
QTEST_CASE (Preallocate_AssertionFailsWhenNewPreallocationSizeIsZero_Test)
{
    // [Preparation]

    const bool                 ASSERTION_FAILED                           = true;
    const pointer_uint_q       AMOUNT_CASES                               = 4;

    const pointer_uint_q       VALID_PREALLOCATION_SIZE                   = 64;

    const pointer_uint_q       VALID_PREALLOCATION_ALIGNMENT_VALUE01      = 2;
    const pointer_uint_q       VALID_PREALLOCATION_ALIGNMENT_VALUE02      = 4;
    const pointer_uint_q       VALID_PREALLOCATION_ALIGNMENT_VALUE03      = 8;
    const pointer_uint_q       VALID_PREALLOCATION_ALIGNMENT_VALUE04      = 16;

    bool                       bAssertionFailedIn01                       = false;
    bool                       bAssertionFailedIn02                       = false;
    bool                       bAssertionFailedIn03                       = false;
    bool                       bAssertionFailedIn04                       = false;

    pointer_uint_q             u                                          = 0;


    // [Execution]

    QStackAllocatorWhiteBox    stackAllocatorWhiteBox01( VALID_PREALLOCATION_SIZE, QAlignment(VALID_PREALLOCATION_ALIGNMENT_VALUE01) ); 
    QStackAllocatorWhiteBox    stackAllocatorWhiteBox02( VALID_PREALLOCATION_SIZE, QAlignment(VALID_PREALLOCATION_ALIGNMENT_VALUE02) ); 
    QStackAllocatorWhiteBox    stackAllocatorWhiteBox03( VALID_PREALLOCATION_SIZE, QAlignment(VALID_PREALLOCATION_ALIGNMENT_VALUE03) ); 
    QStackAllocatorWhiteBox    stackAllocatorWhiteBox04( VALID_PREALLOCATION_SIZE, QAlignment(VALID_PREALLOCATION_ALIGNMENT_VALUE04) ); 

    for (u = 0; u < AMOUNT_CASES; ++u)
    {
        try
        {
            switch (u)
            {
                // (** public **) QStackAllocatorWhiteBox::PreallocatePublic --> (** protected **) QStackAllocatorWhiteBox::Preallocate
                case 0: stackAllocatorWhiteBox01.PreallocatePublic( 0, QAlignment(VALID_PREALLOCATION_ALIGNMENT_VALUE01) ); break;
                case 1: stackAllocatorWhiteBox02.PreallocatePublic( 0, QAlignment(VALID_PREALLOCATION_ALIGNMENT_VALUE02) ); break;
                case 2: stackAllocatorWhiteBox03.PreallocatePublic( 0, QAlignment(VALID_PREALLOCATION_ALIGNMENT_VALUE03) ); break;
                case 3: stackAllocatorWhiteBox04.PreallocatePublic( 0, QAlignment(VALID_PREALLOCATION_ALIGNMENT_VALUE04) ); break;
            }
        }
        catch(const QAssertException&)
        {
            switch (u)
            {
                case 0:
                    if (false == bAssertionFailedIn01)
                    {
                        bAssertionFailedIn01 = true;
                    }
                break;
                case 1:
                    if (false == bAssertionFailedIn02)
                    {
                        bAssertionFailedIn02 = true;
                    }
                break;
                case 2:
                    if (false == bAssertionFailedIn03)
                    {
                        bAssertionFailedIn03 = true;
                    }
                break;
                case 3:
                    if (false == bAssertionFailedIn04)
                    {
                        bAssertionFailedIn04 = true;
                    }
                break;
            }
        }
    }


    // [Verification]

    BOOST_CHECK_EQUAL(bAssertionFailedIn01, ASSERTION_FAILED);
    BOOST_CHECK_EQUAL(bAssertionFailedIn02, ASSERTION_FAILED);
    BOOST_CHECK_EQUAL(bAssertionFailedIn03, ASSERTION_FAILED);
    BOOST_CHECK_EQUAL(bAssertionFailedIn04, ASSERTION_FAILED);
}

#endif // QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

// The following test is kept here but commented out. The reason is that although it is an interesting test, it may fail randomly due to memory
// shortage. Besides, it is not a test that applies only to this class but to any attempt of allocating heap memory.
///// <summary>
///// Checks that it is possible to preallocate a memory block of 1Gb.
///// </summary>
//QTEST_CASE (Preallocate_ItIsPossibleToAllocate1GbOfMemory_Test)
//{
//    // [Preparation]
//
//    const bool                 EXPECTED_RESULT                            = true;
//
//    const pointer_uint_q       VALID_PREALLOCATION_SIZE_SMALL             = 32;
//    const pointer_uint_q       VALID_PREALLOCATION_SIZE_1GB               = 1073741824;
//    const pointer_uint_q       VALID_PREALLOCATION_ALIGNMENT_VALUE        = 1;
//
//    void*                      pPreallocated                              = null_q;
//    bool                       bPreallocated                              = false;
//
//
//    // [Execution]
//    
//    QStackAllocatorWhiteBox    stackAllocatorWhiteBox( VALID_PREALLOCATION_SIZE_SMALL, QAlignment(VALID_PREALLOCATION_ALIGNMENT_VALUE) );
//
//    // Preallocated block will NOT be modified for calling to this method.
//    pPreallocated = stackAllocatorWhiteBox.PreallocatePublic( VALID_PREALLOCATION_SIZE_1GB, QAlignment(VALID_PREALLOCATION_ALIGNMENT_VALUE) );
//
//    if (null_q != pPreallocated)
//        bPreallocated = true;
//
//
//    // [Verification]
//    BOOST_CHECK_EQUAL(bPreallocated, EXPECTED_RESULT);
//
//
//    // [Cleaning]
//    operator delete( pPreallocated, QAlignment(VALID_PREALLOCATION_ALIGNMENT_VALUE) );
//}

// End - Test Suite: QStackAllocator_TestSuite
QTEST_SUITE_END()
