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

#include "QPoolAllocator.h"
#include "QPoolAllocatorWhiteBox.h"
#include "QAlignment.h"
#include "QAssertException.h"

using Kinesis::QuimeraEngine::Common::Exceptions::QAssertException;
using Kinesis::QuimeraEngine::Common::DataTypes::pointer_uint_q;
using Kinesis::QuimeraEngine::Common::DataTypes::f64_q;
using Kinesis::QuimeraEngine::Common::Memory::QPoolAllocator;
using Kinesis::QuimeraEngine::Common::Memory::Test::QPoolAllocatorWhiteBox;
using Kinesis::QuimeraEngine::Common::Memory::QAlignment;


QTEST_SUITE_BEGIN( QPoolAllocator_TestSuite )
    
#if QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when pool size is 0 or block size is 0.
/// </summary>
QTEST_CASE( Constructor1_AssertionFailsWhenPoolSizeOrBlockSizeIsZero_Test )
{
    // [Preparation]
    const pointer_uint_q BLOCK_SIZE = sizeof(f64_q);
    const pointer_uint_q BLOCKS_COUNT = 4;
    const pointer_uint_q POOL_SIZE = BLOCKS_COUNT*BLOCK_SIZE;
    const QAlignment ALIGNMENT(BLOCK_SIZE);

    const pointer_uint_q BLOCK_SIZE_TO_ASSERT = 0;
    const pointer_uint_q POOL_SIZE_TO_ASSERT = 0;

    const bool ASSERTION_FAILED    = true;

    // [Execution]
    bool bSizeAssertionFailed      = false;
    bool bBlockSizeAssertionFailed = false;

    try
    {
        QPoolAllocator pool(POOL_SIZE_TO_ASSERT, BLOCK_SIZE, ALIGNMENT);
    }
    catch(const QAssertException&)
    {
        bSizeAssertionFailed = true;
    }

    try
    {
        QPoolAllocator pool(POOL_SIZE, BLOCK_SIZE_TO_ASSERT, ALIGNMENT);
    }
    catch(const QAssertException&)
    {
        bBlockSizeAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bSizeAssertionFailed, ASSERTION_FAILED);
    BOOST_CHECK_EQUAL(bBlockSizeAssertionFailed, ASSERTION_FAILED);
}

#endif // QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS


/// <summary>
/// Checks if pre-allocated memory is correctly aligned.
/// </summary>
QTEST_CASE( Constructor1_PreAllocatedMemoryIsAligned_Test )
{
    // [Preparation]
    const pointer_uint_q BLOCK_SIZE = sizeof(f64_q)*2;
    const pointer_uint_q BLOCKS_COUNT = 4;
    const pointer_uint_q POOL_SIZE = BLOCKS_COUNT*BLOCK_SIZE;
    const QAlignment ALIGNMENT(BLOCK_SIZE);
    const pointer_uint_q ZERO_CORRECTION_ALIGNMENT = 0;

    // [Execution]
    QPoolAllocatorWhiteBox pool(POOL_SIZE, BLOCK_SIZE, ALIGNMENT);

    // [Verification]
    pointer_uint_q correctionAlignment = (pointer_uint_q)pool.GetpAllocatedMemory() & (ALIGNMENT - 1);
    BOOST_CHECK_EQUAL( correctionAlignment, ZERO_CORRECTION_ALIGNMENT );
}


#if QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when pool size is 0 or block size is 0 or buffer address is null.
/// </summary>
QTEST_CASE( Constructor2_AssertionFailsWhenPoolSizeOrBlockSizeOrBufferAddressHasWrongValue_Test )
{
    // [Preparation]
    const pointer_uint_q BLOCK_SIZE = sizeof(f64_q);
    const pointer_uint_q BLOCKS_COUNT = 4;
    const pointer_uint_q POOL_SIZE = BLOCKS_COUNT*BLOCK_SIZE;
    void* pBuffer1 = malloc( POOL_SIZE );
    void* pBuffer2 = malloc( POOL_SIZE );

    const pointer_uint_q BLOCK_SIZE_TO_ASSERT = 0;
    const pointer_uint_q POOL_SIZE_TO_ASSERT = 0;
    void* pBufferToAssert = null_q;

    const bool ASSERTION_FAILED    = true;

    // [Execution]
    bool bSizeAssertionFailed      = false;
    bool bBlockSizeAssertionFailed = false;
    bool bBufferAssertionFailed    = false;

    try
    {
        QPoolAllocator pool(POOL_SIZE_TO_ASSERT, BLOCK_SIZE, pBuffer1);
    }
    catch(const QAssertException&)
    {
        bSizeAssertionFailed = true;
    }

    try
    {
        QPoolAllocator pool(POOL_SIZE, BLOCK_SIZE_TO_ASSERT, pBuffer2);
    }
    catch(const QAssertException&)
    {
        bBlockSizeAssertionFailed = true;
    }

    try
    {
        QPoolAllocator pool(POOL_SIZE, BLOCK_SIZE, pBufferToAssert);
    }
    catch(const QAssertException&)
    {
        bBufferAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bSizeAssertionFailed, ASSERTION_FAILED);
    BOOST_CHECK_EQUAL(bBlockSizeAssertionFailed, ASSERTION_FAILED);
    BOOST_CHECK_EQUAL(bBufferAssertionFailed, ASSERTION_FAILED);

    free(pBuffer1);
    free(pBuffer2);
}

#endif // QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS


/// <summary>
/// Checks if pre-allocated memory points to passed buffer.
/// </summary>
QTEST_CASE( Constructor2_PreAllocatedMemoryIsOnPassedBuffer_Test )
{
    // [Preparation]
    const pointer_uint_q BLOCK_SIZE = sizeof(f64_q);
    pointer_uint_q BLOCKS_COUNT = 4;
    pointer_uint_q POOL_SIZE = BLOCKS_COUNT*BLOCK_SIZE;
    void* pBuffer = malloc(POOL_SIZE);

    // [Execution]
    QPoolAllocatorWhiteBox pool(POOL_SIZE, BLOCK_SIZE, pBuffer);

    // [Verification]
    BOOST_CHECK_EQUAL((pointer_uint_q)pool.GetpAllocatedMemory(), (pointer_uint_q)pBuffer );

    free( pBuffer );
}


#if QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when pool size is 0 or block size is 0 or buffer address is null.
/// </summary>
QTEST_CASE( Constructor3_AssertionFailsWhenPoolSizeOrBlockSizeOrBufferAddressHasWrongValue_Test )
{
    // [Preparation]
    const pointer_uint_q BLOCK_SIZE = sizeof(f64_q);
    const pointer_uint_q BLOCKS_COUNT = 4;
    const pointer_uint_q POOL_SIZE = BLOCKS_COUNT*sizeof(f64_q);
    const QAlignment ALIGNMENT(BLOCK_SIZE);
    void* pBuffer1 = malloc( POOL_SIZE );
    void* pBuffer2 = malloc( POOL_SIZE );

    const pointer_uint_q BLOCK_SIZE_TO_ASSERT = 0;
    const pointer_uint_q POOL_SIZE_TO_ASSERT = 0;
    void* pBufferToAssert = null_q;

    const bool ASSERTION_FAILED    = true;

    // [Execution]
    bool bSizeAssertionFailed      = false;
    bool bBlockSizeAssertionFailed = false;
    bool bBufferAssertionFailed    = false;

    try
    {
        QPoolAllocator pool(POOL_SIZE_TO_ASSERT, BLOCK_SIZE, pBuffer1, ALIGNMENT);
    }
    catch(const QAssertException&)
    {
        bSizeAssertionFailed = true;
    }

    try
    {
        QPoolAllocator pool(POOL_SIZE, BLOCK_SIZE_TO_ASSERT, pBuffer2, ALIGNMENT);
    }
    catch(const QAssertException&)
    {
        bBlockSizeAssertionFailed = true;
    }

    try
    {
        QPoolAllocator pool(POOL_SIZE, BLOCK_SIZE_TO_ASSERT, pBufferToAssert, ALIGNMENT);
    }
    catch(const QAssertException&)
    {
        bBufferAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bSizeAssertionFailed, ASSERTION_FAILED);
    BOOST_CHECK_EQUAL(bBlockSizeAssertionFailed, ASSERTION_FAILED);
    BOOST_CHECK_EQUAL(bBufferAssertionFailed, ASSERTION_FAILED);

    free(pBuffer1);
    free(pBuffer2);
}

#endif // QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS


/// <summary>
/// Pointer to first pre-allocated block is as expected
/// </summary>
QTEST_CASE( Constructor3_PointerToFirstPreAllocatedBlockIsAsExpected_Test )
{
    // [Preparation]
    const pointer_uint_q BLOCK_SIZE = sizeof(f64_q)*2;
    const pointer_uint_q BLOCKS_COUNT = 4;
    const pointer_uint_q POOL_SIZE = BLOCKS_COUNT*BLOCK_SIZE;
    void* pBuffer = malloc( POOL_SIZE );
    void *pUnalignedBuffer = (void*)((pointer_uint_q)pBuffer + 1);

    const QAlignment ALIGNMENT(BLOCK_SIZE);

    pointer_uint_q uAdjustment = ALIGNMENT - ((pointer_uint_q)pUnalignedBuffer & (ALIGNMENT - 1U));
    if(uAdjustment == ALIGNMENT) uAdjustment = 0;
    pointer_uint_q firstAlignedAddress = (pointer_uint_q)pUnalignedBuffer + uAdjustment;

    // [Execution]
    QPoolAllocatorWhiteBox pool(POOL_SIZE, BLOCK_SIZE, pUnalignedBuffer, ALIGNMENT);

    // [Verification]
    BOOST_CHECK_EQUAL((pointer_uint_q)pool.GetpFirst(), firstAlignedAddress );

    free( pBuffer );
}


/// <summary>
/// Checks if pointer to first block of pre-allocated memory points to first aligned address on passed buffer.
/// </summary>
QTEST_CASE( Allocate_FirstAllocatedBlockAddressEqualsFirstPreallocatedBlockAddress_Test )
{
    // [Preparation]
    const pointer_uint_q BLOCK_SIZE = sizeof(f64_q);
    const pointer_uint_q BLOCKS_COUNT = 4;
    const pointer_uint_q POOL_SIZE = BLOCKS_COUNT*BLOCK_SIZE;
    QAlignment ALIGNMENT(BLOCK_SIZE);

    // [Execution]
    QPoolAllocatorWhiteBox pool(POOL_SIZE, BLOCK_SIZE, ALIGNMENT);
    f64_q *pBlock = (f64_q*)pool.Allocate();

    // [Verification]
    BOOST_CHECK_EQUAL((pointer_uint_q)pool.GetpFirst(), (pointer_uint_q)pBlock );
}


/// <summary>
/// Checks if attempt to allocate on a full pool returns null pointer.
/// </summary>
QTEST_CASE( Allocate_AllocateOnAFullPoolReturnsNullPointer_Test )
{
    // [Preparation]
    const pointer_uint_q BLOCK_SIZE = sizeof(f64_q);
    const pointer_uint_q BLOCKS_COUNT = 4;
    const pointer_uint_q POOL_SIZE = BLOCKS_COUNT*BLOCK_SIZE;
    QAlignment ALIGNMENT(BLOCK_SIZE);

    // [Execution]
    QPoolAllocator pool(POOL_SIZE, BLOCK_SIZE, ALIGNMENT);

    f64_q *pBlock;

    for(pointer_uint_q uIndex = 0; uIndex < BLOCKS_COUNT + 1; uIndex++ ) 
    {
        pBlock = (f64_q*)pool.Allocate();
    }

    // [Verification]
    BOOST_CHECK( pBlock == null_q );
}


/// <summary>
/// Checks if address of the second allocated block is as expected.
/// </summary>
QTEST_CASE( Allocate_AllocatedAddressOfTheSecondBlockIsAsExpected_Test )
{
    // [Preparation]
    const pointer_uint_q BLOCK_SIZE = sizeof(f64_q)*2;
    const pointer_uint_q BLOCKS_COUNT = 4;
    const pointer_uint_q POOL_SIZE = BLOCKS_COUNT*BLOCK_SIZE;
    QAlignment ALIGNMENT(BLOCK_SIZE);

    // [Execution]
    QPoolAllocator pool(POOL_SIZE, BLOCK_SIZE, ALIGNMENT);

    f64_q *pFirstBlock  = (f64_q*)pool.Allocate();
    f64_q *pSecondBlock = (f64_q*)pool.Allocate();

    // [Verification]
    const pointer_uint_q EXPECTED_ADDRESS_SECOND_BLOCK = (pointer_uint_q)pFirstBlock + BLOCK_SIZE;
    BOOST_CHECK_EQUAL( (pointer_uint_q)pSecondBlock, EXPECTED_ADDRESS_SECOND_BLOCK );
}


#if QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when block pointer is invalid.
/// </summary>
QTEST_CASE( Deallocate_AssertionFailsWhenBlockPointerIsInvalid_Test )
{
    // [Preparation]
    const pointer_uint_q BLOCK_SIZE = sizeof(f64_q);
    const pointer_uint_q BLOCKS_COUNT = 4;
    const pointer_uint_q POOL_SIZE = BLOCKS_COUNT*BLOCK_SIZE;
    QAlignment ALIGNMENT(BLOCK_SIZE);

    void *pBufferToAssert1 = null_q;
    void *pBufferToAssert2 = malloc(POOL_SIZE);

    bool bNullBufferAssertionFailed = false;
    bool bInvalidBufferAssertionFailed = false;

    const bool ASSERTION_FAILED    = true;

    // [Execution]
    QPoolAllocator pool(POOL_SIZE, BLOCK_SIZE, ALIGNMENT);

    try
    {
        pool.Deallocate(pBufferToAssert1);
    }
    catch(const QAssertException&)
    {
        bNullBufferAssertionFailed = true;
    }

    try
    {
        pool.Deallocate(pBufferToAssert2);

    }
    catch(const QAssertException&)
    {
        bInvalidBufferAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bNullBufferAssertionFailed, ASSERTION_FAILED);
    BOOST_CHECK_EQUAL(bInvalidBufferAssertionFailed, ASSERTION_FAILED);

    free(pBufferToAssert2);
}

#endif // QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS


/// <summary>
/// Checks if a deallocation of a block allows it to be allocated again.
/// </summary>
QTEST_CASE( Deallocate_DeallocationOfABlockAllowsItToBeAllocatedAgain_Test )
{
    // [Preparation]
    const pointer_uint_q BLOCK_SIZE = sizeof(f64_q);
    const pointer_uint_q BLOCKS_COUNT = 4;
    const pointer_uint_q POOL_SIZE = BLOCKS_COUNT*BLOCK_SIZE;
    const QAlignment ALIGNMENT(BLOCK_SIZE);

    // [Execution]
    QPoolAllocator pool(POOL_SIZE, BLOCK_SIZE, ALIGNMENT);

    pool.Allocate();
    f64_q *pSecondBlock = (f64_q*)pool.Allocate();
    pool.Allocate();

    pool.Deallocate(pSecondBlock);
    f64_q *pFourthBlock = (f64_q*)pool.Allocate();

    // [Verification]
    BOOST_CHECK_EQUAL((pointer_uint_q)pSecondBlock, (pointer_uint_q)pFourthBlock );
}


/// <summary>
/// Checks if deallocation of entire pool allows it to be allocated again
/// </summary>
QTEST_CASE( Deallocate_DeallocationOfEntirePoolAllowsItToBeAllocatedAgain_Test )
{
    // [Preparation]
    const pointer_uint_q BLOCK_SIZE = sizeof(f64_q);
    const pointer_uint_q BLOCKS_COUNT = 4;
    const pointer_uint_q POOL_SIZE = BLOCKS_COUNT*BLOCK_SIZE;
    QAlignment ALIGNMENT(BLOCK_SIZE);
    f64_q* pBlocks[BLOCKS_COUNT];
    pointer_uint_q uAllocationsCount = 0;

    // [Execution]
    QPoolAllocator pool(POOL_SIZE, BLOCK_SIZE, ALIGNMENT);
    for( pointer_uint_q uIndex = 0; uIndex < BLOCKS_COUNT; uIndex++ )
    {
        pBlocks[uIndex] = (f64_q*)pool.Allocate();
    }

    for( pointer_uint_q uIndex = 0; uIndex < BLOCKS_COUNT; uIndex++ )
    {
        pool.Deallocate( pBlocks[uIndex] );
    }

    for( pointer_uint_q uIndex = 0; uIndex < BLOCKS_COUNT; uIndex++ )
    {
        f64_q *pBlock = (f64_q*)pool.Allocate();
        if( null_q != pBlock ) 
            uAllocationsCount++;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(  uAllocationsCount, BLOCKS_COUNT );
}


/// <summary>
/// Checks if clear a full pool makes it available to allocate again.
/// </summary>
QTEST_CASE( Clear_ClearAFullPoolMakesItAvailableToAllocateAgain_Test )
{
    // [Preparation]
    const pointer_uint_q BLOCK_SIZE = sizeof(f64_q);
    const pointer_uint_q BLOCKS_COUNT = 4;
    const pointer_uint_q POOL_SIZE = BLOCKS_COUNT*BLOCK_SIZE;
    const QAlignment ALIGNMENT(BLOCK_SIZE);
    unsigned int uAllocationsCount = 0;

    // [Execution]
    QPoolAllocator pool(POOL_SIZE, BLOCK_SIZE, ALIGNMENT);

    for( pointer_uint_q uIndex = 0; uIndex < BLOCKS_COUNT; uIndex++ )
    {
        pool.Allocate();
    }

    pool.Clear();

    for( pointer_uint_q uIndex = 0; uIndex < BLOCKS_COUNT; uIndex++ )
    {
        f64_q *pBlock = (f64_q*)pool.Allocate();
        if( null_q != pBlock ) 
            uAllocationsCount++;
    }
	
	// [Verification]
    BOOST_CHECK_EQUAL( uAllocationsCount, BLOCKS_COUNT );
}


/// <summary>
/// Checks if returns the size of memory pre-allocated plus the size of memory needed by internals.
/// </summary>
QTEST_CASE( GetTotalSize_SizeOfMemoryPreAllocatedPlusSizeOfMemoryNeededByInternalsIsAsExpected_Test )
{
    // [Preparation]
    const pointer_uint_q BLOCK_SIZE = sizeof(f64_q)*2;
    const pointer_uint_q BLOCKS_COUNT = 4;
    const pointer_uint_q POOL_SIZE = BLOCKS_COUNT*BLOCK_SIZE;
    const QAlignment ALIGNMENT(BLOCK_SIZE);

    // Expected Size = pre-allocated size for the blocks + size of pointers list to free blocks.
    const pointer_uint_q EXPECTED_SIZE = POOL_SIZE + sizeof(pointer_uint_q*)*BLOCKS_COUNT;

    // [Execution]
    QPoolAllocator pool(POOL_SIZE, BLOCK_SIZE, ALIGNMENT);

    pointer_uint_q uTotalSize = pool.GetTotalSize();

    // [Verification]
    BOOST_CHECK_EQUAL( uTotalSize, EXPECTED_SIZE );
}

/// <summary>
/// Checks if returns de size of the pool.
/// </summary>
QTEST_CASE( GetPoolSize_SizeOfThePoolIsAsExpected_Test )
{
    // [Preparation]
    const pointer_uint_q BLOCK_SIZE = sizeof(f64_q)*2;
    const pointer_uint_q BLOCKS_COUNT = 4;
    const pointer_uint_q POOL_SIZE = BLOCKS_COUNT*BLOCK_SIZE;
    const QAlignment ALIGNMENT(BLOCK_SIZE);

    // [Execution]
    QPoolAllocator pool(POOL_SIZE, BLOCK_SIZE, ALIGNMENT);

    pointer_uint_q uPoolSize = pool.GetPoolSize();

    // [Verification]
    BOOST_CHECK_EQUAL( uPoolSize, POOL_SIZE );
}

/// <summary>
/// Checks if returns false if cannot allocate.
/// </summary>
QTEST_CASE( CanAllocate_ReturnsFalseIfCannotAllocate_Test )
{
    // [Preparation]
    const pointer_uint_q BLOCK_SIZE = sizeof(f64_q);
    const pointer_uint_q BLOCKS_COUNT = 4;
    const pointer_uint_q POOL_SIZE = BLOCKS_COUNT*BLOCK_SIZE;
    const QAlignment ALIGNMENT(BLOCK_SIZE);

    const bool CANNOT_ALLOCATE = false;

    // [Execution]
    QPoolAllocator pool(POOL_SIZE, BLOCK_SIZE, ALIGNMENT);

    for( pointer_uint_q uIndex = 0; uIndex < BLOCKS_COUNT; uIndex++ )
    {
        pool.Allocate();
    }

    // [Verification]
    BOOST_CHECK_EQUAL( pool.CanAllocate(), CANNOT_ALLOCATE );
}


/// <summary>
/// Checks if returns true when can allocate.
/// </summary>
QTEST_CASE( CanAllocate_ReturnsTrueWhenCanAllocate_Test )
{
    // [Preparation]
    const pointer_uint_q BLOCK_SIZE = sizeof(f64_q);
    const pointer_uint_q BLOCKS_COUNT = 4;
    const pointer_uint_q POOL_SIZE = BLOCKS_COUNT*BLOCK_SIZE;
    const QAlignment ALIGNMENT(BLOCK_SIZE);

    const bool CAN_ALLOCATE = true;

    // [Execution]
    QPoolAllocator pool(POOL_SIZE, BLOCK_SIZE, ALIGNMENT);

    // [Verification]
    BOOST_CHECK_EQUAL( pool.CanAllocate(), CAN_ALLOCATE );
}


/// <summary>
/// Check if Allocated Bytes is correctly calculated when zero blocks has been allocated.
/// </summary>
QTEST_CASE( GetAllocatedBytes_CheckIfCorrectlyCalculatedWhenZeroBlocksAllocated_Test )
{
    // [Preparation]
    const pointer_uint_q BLOCK_SIZE = sizeof(f64_q);
    const pointer_uint_q BLOCKS_COUNT = 4;
    const pointer_uint_q POOL_SIZE = BLOCKS_COUNT*BLOCK_SIZE;
    const QAlignment ALIGNMENT(BLOCK_SIZE);
    const pointer_uint_q ZERO_ALLOCATED_BYTES = 0;

    pointer_uint_q uAllocatedBytesZeroExpected;

    // [Execution]
    QPoolAllocator pool(POOL_SIZE, BLOCK_SIZE, ALIGNMENT);
    uAllocatedBytesZeroExpected = pool.GetAllocatedBytes();

    // [Verification]
    BOOST_CHECK_EQUAL( uAllocatedBytesZeroExpected, ZERO_ALLOCATED_BYTES );
}


/// <summary>
/// Check if Allocated Bytes is correctly calculated when one block has been allocated.
/// </summary>
QTEST_CASE( GetAllocatedBytes_CheckIfCorrectlyCalculatedWhenOneBlockAllocated_Test )
{
    // [Preparation]
    const pointer_uint_q BLOCK_SIZE = sizeof(f64_q);
    const pointer_uint_q BLOCKS_COUNT = 4;
    const pointer_uint_q POOL_SIZE = BLOCKS_COUNT*BLOCK_SIZE;
    const QAlignment ALIGNMENT(BLOCK_SIZE);
    const pointer_uint_q ONE_BLOCK_ALLOCATED_BYTES = BLOCK_SIZE;
    
    pointer_uint_q uAllocatedBytesOneBlockExpected;
    
    // [Execution]
    QPoolAllocator pool(POOL_SIZE, BLOCK_SIZE, ALIGNMENT);

    pool.Allocate();

    uAllocatedBytesOneBlockExpected = pool.GetAllocatedBytes();

    // [Verification]
    BOOST_CHECK_EQUAL( uAllocatedBytesOneBlockExpected, ONE_BLOCK_ALLOCATED_BYTES );
}


/// <summary>
/// Check if Allocated Bytes is correctly calculated when all blocks has been allocated.
/// </summary>
QTEST_CASE( GetAllocatedBytes_CheckIfCorrectlyCalculatedWhenAllBlocksAllocated_Test )
{
    // [Preparation]
    const pointer_uint_q BLOCK_SIZE = sizeof(f64_q);
    const pointer_uint_q BLOCKS_COUNT = 4;
    const pointer_uint_q POOL_SIZE = BLOCKS_COUNT*BLOCK_SIZE;
    const QAlignment ALIGNMENT(BLOCK_SIZE);
    const pointer_uint_q FULL_ALLOCATED_BYTES = POOL_SIZE;

    pointer_uint_q uAllocatedBytesFullExpected;
    
    // [Execution]
    QPoolAllocator pool(POOL_SIZE, BLOCK_SIZE, ALIGNMENT);

    pool.Allocate();

    for(pointer_uint_q uIndex = 0; uIndex < BLOCK_SIZE; uIndex++)
    {
        pool.Allocate();
    }

    uAllocatedBytesFullExpected = pool.GetAllocatedBytes();

    // [Verification]
    BOOST_CHECK_EQUAL( uAllocatedBytesFullExpected, FULL_ALLOCATED_BYTES );
}


#if QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when destination blocks count are minor than origin.
/// </summary>
QTEST_CASE( CopyTo_AssertionFailsWhenDestinationBlocksCountAreMinorThanOrigin_Test )
{
    // [Preparation]

    const pointer_uint_q BLOCK_SIZE = sizeof(f64_q);
    const pointer_uint_q BLOCKS_COUNT_ORIGIN = 6;
    const pointer_uint_q POOL_SIZE_ORIGIN = BLOCKS_COUNT_ORIGIN*BLOCK_SIZE;
    QAlignment ALIGNMENT(BLOCK_SIZE);

    const pointer_uint_q BLOCKS_COUNT_DESTINATION = 4;
    const pointer_uint_q POOL_SIZE_DESTINATION = BLOCKS_COUNT_DESTINATION * BLOCK_SIZE;

    const bool ASSERTION_FAILED    = true;

    // [Execution]
    QPoolAllocator poolOrigin(POOL_SIZE_ORIGIN, BLOCK_SIZE, ALIGNMENT);
    QPoolAllocator poolDestination(POOL_SIZE_DESTINATION, BLOCK_SIZE, ALIGNMENT);

    bool bAssertionFailed = false;

    try
    {
        poolOrigin.CopyTo(poolDestination);
    }
    catch(const QAssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

/// <summary>
/// Checks that an assertion fails when destination blocks size are minor than origin.
/// </summary>
QTEST_CASE( CopyTo_AssertionFailsWhenDestinationBlocksSizeAreMinorThanOrigin_Test )
{
    // [Preparation]

    // Greater Blocks Size in origin
    const pointer_uint_q BLOCK_SIZE_ORIGIN = sizeof(f64_q)*2;
    const pointer_uint_q BLOCKS_COUNT = 6;
    const pointer_uint_q POOL_SIZE_ORIGIN = BLOCKS_COUNT*BLOCK_SIZE_ORIGIN;
    const QAlignment ALIGNMENT_ORIGIN(BLOCK_SIZE_ORIGIN);

    const pointer_uint_q BLOCK_SIZE_DESTINATION = sizeof(f64_q);
    const pointer_uint_q POOL_SIZE_DESTINATION = BLOCKS_COUNT*BLOCK_SIZE_DESTINATION;
    const QAlignment ALIGNMENT_DESTINATION(BLOCK_SIZE_DESTINATION);

    const bool ASSERTION_FAILED    = true;

    // [Execution]

    QPoolAllocator poolOrigin(POOL_SIZE_ORIGIN, BLOCK_SIZE_ORIGIN, ALIGNMENT_ORIGIN);
    QPoolAllocator poolDestination(POOL_SIZE_DESTINATION, BLOCK_SIZE_DESTINATION, ALIGNMENT_DESTINATION);

    bool bAssertionFailed = false;

    try
    {
        poolOrigin.CopyTo(poolDestination);
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
/// Case when origin allocator has less blocks than destination and all blocks allocated.
/// It checks that origin blocks has correctly copied.
/// </summary>
QTEST_CASE( CopyTo_CheckIfCorrectlyCopiedWhenOriginAllocatorHasLessBlocksAndAllBlocksAllocated_Test )
{
    // [Preparation]
    const pointer_uint_q BLOCK_SIZE = sizeof(f64_q);
    const pointer_uint_q BLOCKS_COUNT_ORIGIN = 4;
    const pointer_uint_q POOL_SIZE_ORIGIN = BLOCKS_COUNT_ORIGIN * BLOCK_SIZE;
    const QAlignment ALIGNMENT(BLOCK_SIZE);

    const pointer_uint_q BLOCKS_COUNT_DESTINATION = 6;
    const pointer_uint_q POOL_SIZE_DESTINATION = BLOCKS_COUNT_DESTINATION * BLOCK_SIZE;

    // [Execution]
    QPoolAllocator poolOrigin(POOL_SIZE_ORIGIN, BLOCK_SIZE, ALIGNMENT);
    QPoolAllocatorWhiteBox poolDestination(POOL_SIZE_DESTINATION, BLOCK_SIZE, ALIGNMENT);

    f64_q *pElements[BLOCKS_COUNT_ORIGIN];

    for(pointer_uint_q uIndex = 0; uIndex < BLOCKS_COUNT_ORIGIN; uIndex++ )
    {
        pElements[uIndex] = (f64_q*)poolOrigin.Allocate();
        *pElements[uIndex] = uIndex;
    }

    poolOrigin.CopyTo(poolDestination);

    // [Verification]

    for(pointer_uint_q uIndex = 0; uIndex < BLOCKS_COUNT_ORIGIN; uIndex++ )
    {
        f64_q *pElementDestination = (f64_q*)poolDestination.GetpBlock(uIndex);
        BOOST_CHECK_EQUAL( *pElements[uIndex], *pElementDestination );
    }

    BOOST_CHECK_EQUAL( poolOrigin.GetAllocatedBytes(), poolDestination.GetAllocatedBytes() );
}


/// <summary>
/// Case when origin allocator has less blocks than destination and one allocated block.
/// After copy it verifies that destination has origin blocks plus remaining free space.
/// </summary>
QTEST_CASE( CopyTo_CheckIfCorrectlyCopiedWhenOriginAllocatorHasLessBlocksAndOneAllocatedBlock_Test )
{
    // [Preparation]
    const pointer_uint_q BLOCK_SIZE = sizeof(f64_q);
    const pointer_uint_q BLOCKS_COUNT_ORIGIN = 4;
    const pointer_uint_q POOL_SIZE_ORIGIN = BLOCKS_COUNT_ORIGIN * BLOCK_SIZE;
    const QAlignment ALIGNMENT(BLOCK_SIZE);

    const pointer_uint_q BLOCKS_COUNT_DESTINATION = 6;
    const pointer_uint_q POOL_SIZE_DESTINATION = BLOCKS_COUNT_DESTINATION * BLOCK_SIZE;

    const f64_q TEST_VALUE = 5;
    const pointer_uint_q EXPECTED_NUMBER_OF_ALLOCATIONS = BLOCKS_COUNT_DESTINATION - 1;

    // [Execution]
    QPoolAllocator poolOrigin(POOL_SIZE_ORIGIN, BLOCK_SIZE, ALIGNMENT);
    QPoolAllocatorWhiteBox poolDestination(POOL_SIZE_DESTINATION, BLOCK_SIZE, ALIGNMENT);

    f64_q *pElement = (f64_q*)poolOrigin.Allocate();
    *pElement = TEST_VALUE;

    poolOrigin.CopyTo(poolDestination);

    // [Verification]
    pointer_uint_q uAllocations = 0;

    for(pointer_uint_q uIndex = 0; uIndex < BLOCKS_COUNT_DESTINATION; uIndex++)
    {
        if( null_q != poolDestination.Allocate() ) 
            uAllocations++;
    }

    BOOST_CHECK_EQUAL( uAllocations, EXPECTED_NUMBER_OF_ALLOCATIONS );

    f64_q *pElementDestination = (f64_q*)poolDestination.GetpBlock(0);
    BOOST_CHECK_EQUAL( *pElementDestination, TEST_VALUE );
}


/// <summary>
/// When copied a full origin and allocates more elements in destination it checks if destination has expected contents.
/// </summary>
QTEST_CASE( CopyTo_WhenCopiedAFullOriginAndAllocatesMoreElementsInDestinationChecksIfDestinationHasExpectedContents_Test )
{
    // [Preparation]
    const pointer_uint_q BLOCK_SIZE = sizeof(f64_q);
    const pointer_uint_q BLOCKS_COUNT_ORIGIN = 4;
    const pointer_uint_q POOL_SIZE_ORIGIN = BLOCKS_COUNT_ORIGIN * BLOCK_SIZE;
    const QAlignment ALIGNMENT(BLOCK_SIZE);

    const pointer_uint_q BLOCKS_COUNT_DESTINATION = 6;
    const pointer_uint_q POOL_SIZE_DESTINATION = BLOCKS_COUNT_DESTINATION * BLOCK_SIZE;

    // [Execution]
    QPoolAllocator poolOrigin(POOL_SIZE_ORIGIN, BLOCK_SIZE, ALIGNMENT);
    QPoolAllocatorWhiteBox poolDestination(POOL_SIZE_DESTINATION, BLOCK_SIZE, ALIGNMENT);

    f64_q *pElements[BLOCKS_COUNT_DESTINATION];

    for(pointer_uint_q uIndex = 0; uIndex < BLOCKS_COUNT_ORIGIN; uIndex++ )
    {
        pElements[uIndex] = (f64_q*)poolOrigin.Allocate();
        *pElements[uIndex] = uIndex;
    }

    poolOrigin.CopyTo(poolDestination);

    for(pointer_uint_q uIndex = BLOCKS_COUNT_ORIGIN; uIndex < BLOCKS_COUNT_DESTINATION; uIndex++)
    {
        pElements[uIndex] = (f64_q*)poolDestination.Allocate();
        *pElements[uIndex] = uIndex;
    }

    // [Verification]

    // Check if no more allocates area available
    BOOST_CHECK( poolDestination.Allocate() == null_q );

    // Check contents
    for(pointer_uint_q uIndex = 0; uIndex < BLOCKS_COUNT_DESTINATION; uIndex++ )
    {
        f64_q *pElementDestination = (f64_q*)poolDestination.GetpBlock(uIndex);
        BOOST_CHECK_EQUAL( *pElements[uIndex], *pElementDestination );
    }
}


/// <summary>
/// When copied an empty origin to a full destination with different blocks count check if destination has all free space available.
/// </summary>
QTEST_CASE( CopyTo_WhenCopiedAnEmptyOriginToAFullDestinationWithDifferentBlocksCountCheckIfDestinationHasAllFreeSpaceAvailable_Test )
{
    // [Preparation]
    const pointer_uint_q BLOCK_SIZE = sizeof(f64_q);
    const pointer_uint_q BLOCKS_COUNT_ORIGIN = 4;
    const pointer_uint_q POOL_SIZE_ORIGIN = BLOCKS_COUNT_ORIGIN * BLOCK_SIZE;
    const QAlignment ALIGNMENT(BLOCK_SIZE);

    const pointer_uint_q BLOCKS_COUNT_DESTINATION = 6;
    const pointer_uint_q POOL_SIZE_DESTINATION = BLOCKS_COUNT_DESTINATION * BLOCK_SIZE;
    const pointer_uint_q EXPECTED_NUMBER_OF_ALLOCATIONS = BLOCKS_COUNT_DESTINATION;

    // [Execution]
    QPoolAllocator poolOrigin(POOL_SIZE_ORIGIN, BLOCK_SIZE, ALIGNMENT);
    QPoolAllocator poolDestination(POOL_SIZE_DESTINATION, BLOCK_SIZE, ALIGNMENT);

    for(pointer_uint_q uIndex = 0; uIndex < BLOCKS_COUNT_DESTINATION; uIndex++)
        poolDestination.Allocate();

    poolOrigin.CopyTo(poolDestination);

    // [Verification]

    pointer_uint_q uAllocations = 0;

    for(pointer_uint_q uIndex = 0; uIndex < BLOCKS_COUNT_DESTINATION + 1; uIndex++ )
    {
        if(null_q != poolDestination.Allocate() )
            uAllocations++;
    }

    BOOST_CHECK_EQUAL( uAllocations, EXPECTED_NUMBER_OF_ALLOCATIONS );
}


/// <summary>
/// When copied an empty origin to a destination with the same blocks count check if destination has all free space available.
/// </summary>
QTEST_CASE( CopyTo_WhenCopiedAnEmptyOriginToADestinationWithTheSameBlocksCountCheckIfDestinationHasAllFreeSpaceAvailable_Test )
{
    // [Preparation]
    const pointer_uint_q BLOCK_SIZE = sizeof(f64_q);
    const pointer_uint_q BLOCKS_COUNT = 4;
    const pointer_uint_q POOL_SIZE = BLOCKS_COUNT * BLOCK_SIZE;
    const QAlignment ALIGNMENT(BLOCK_SIZE);

    const pointer_uint_q EXPECTED_NUMBER_OF_ALLOCATIONS = BLOCKS_COUNT;

    // [Execution]
    QPoolAllocator poolOrigin(POOL_SIZE, BLOCK_SIZE, ALIGNMENT);
    QPoolAllocator poolDestination(POOL_SIZE, BLOCK_SIZE, ALIGNMENT);

    poolOrigin.CopyTo(poolDestination);

    // [Verification]

    pointer_uint_q uAllocations = 0;

    for(pointer_uint_q uIndex = 0; uIndex < BLOCKS_COUNT + 1; uIndex++ )
    {
        if(null_q != poolDestination.Allocate() )
            uAllocations++;
    }

    BOOST_CHECK_EQUAL( uAllocations, EXPECTED_NUMBER_OF_ALLOCATIONS );
}


/// <summary>
/// When copied a full origin to a destination with the same blocks count check if destination has no free space available.
/// </summary>
QTEST_CASE( CopyTo_WhenCopiedAFullOriginToADestinationWithTheSameBlocksCountCheckIfDestinationHasNoFreeSpaceAvailable_Test )
{
    // [Preparation]
    const pointer_uint_q BLOCK_SIZE = sizeof(f64_q);
    const pointer_uint_q BLOCKS_COUNT = 4;
    const pointer_uint_q POOL_SIZE = BLOCKS_COUNT * BLOCK_SIZE;
    const QAlignment ALIGNMENT(BLOCK_SIZE);

    const pointer_uint_q EXPECTED_NUMBER_OF_ALLOCATIONS = 0;

    // [Execution]
    QPoolAllocator poolOrigin(POOL_SIZE, BLOCK_SIZE, ALIGNMENT);
    QPoolAllocator poolDestination(POOL_SIZE, BLOCK_SIZE, ALIGNMENT);

    for(pointer_uint_q uIndex = 0; uIndex < BLOCKS_COUNT; uIndex++)
        poolOrigin.Allocate();

    poolOrigin.CopyTo(poolDestination);

    // [Verification]

    pointer_uint_q uAllocations = 0;
    
    for(pointer_uint_q uIndex = 0; uIndex < BLOCKS_COUNT; uIndex++ )
    {
        if(null_q != poolDestination.Allocate() )
            uAllocations++;
    }

    BOOST_CHECK_EQUAL( uAllocations, EXPECTED_NUMBER_OF_ALLOCATIONS );
}


/// <summary>
/// When copied an origin with one allocated block to a destination check if destination has expected contents and available space.
/// </summary>
QTEST_CASE( CopyTo_WhenCopiedAnOriginWithOneAllocatedBlockToADestinationCheckIfDestinationHasExpectedContentsAndAvailableSpace_Test )
{
    // [Preparation]
    const pointer_uint_q BLOCK_SIZE = sizeof(f64_q);
    const pointer_uint_q BLOCKS_COUNT = 4;
    const pointer_uint_q POOL_SIZE = BLOCKS_COUNT * BLOCK_SIZE;
    const QAlignment ALIGNMENT(BLOCK_SIZE);

    const f64_q TEST_VALUE = 10;
    const pointer_uint_q EXPECTED_NUMBER_OF_ALLOCATIONS = BLOCKS_COUNT - 1;

    // [Execution]
    QPoolAllocator poolOrigin(POOL_SIZE, BLOCK_SIZE, ALIGNMENT);
    QPoolAllocatorWhiteBox poolDestination(POOL_SIZE, BLOCK_SIZE, ALIGNMENT);

    f64_q *pBuffer = (f64_q*)poolOrigin.Allocate();
    *pBuffer = TEST_VALUE;

    poolOrigin.CopyTo(poolDestination);

    // [Verification]

    pBuffer = (f64_q*)poolDestination.GetpFirst();

    BOOST_CHECK_EQUAL( *pBuffer, TEST_VALUE );

    pointer_uint_q uAllocations = 0;
    
    for(pointer_uint_q uIndex = 0; uIndex < BLOCKS_COUNT; uIndex++ )
    {
        if(null_q != poolDestination.Allocate() )
            uAllocations++;
    }

    BOOST_CHECK_EQUAL( uAllocations, EXPECTED_NUMBER_OF_ALLOCATIONS );
}

/// <summary>
/// Checks that the data inside the pool is correctly copied.
/// </summary>
QTEST_CASE( Reallocate1_PoolContentIsCorrectlyCopied_Test )
{
    // [Preparation]
    const bool IS_SAME_DATA = true;
    const pointer_uint_q BLOCK_SIZE = sizeof(unsigned int);
    const pointer_uint_q BLOCKS_COUNT = 4;
    const pointer_uint_q POOL_SIZE = BLOCKS_COUNT * BLOCK_SIZE;
    QPoolAllocator allocator(POOL_SIZE, BLOCK_SIZE, QAlignment(alignof_q(unsigned int)));
    for(pointer_uint_q i = 0; i < BLOCKS_COUNT; ++i)
        *(unsigned int*)allocator.Allocate() = i;
    
    // [Execution]
    allocator.Reallocate(BLOCK_SIZE * (BLOCKS_COUNT + 1));
 
    // [Verification]
    bool bIsSameData = true;
    
    for(pointer_uint_q i = 0; i < BLOCKS_COUNT; ++i)
        bIsSameData = bIsSameData && *((unsigned int*)allocator.GetPointer() + i) == i;

    BOOST_CHECK_EQUAL(bIsSameData, IS_SAME_DATA);
}

/// <summary>
/// Checks that the size of the pool, the total size and the allocated bytes are correct after the reallocation.
/// </summary>
QTEST_CASE( Reallocate1_SizesAreCorrectAfterReallocation_Test )
{
    // [Preparation]
    const pointer_uint_q BLOCK_SIZE = sizeof(int);
    const pointer_uint_q BLOCKS_COUNT = 4;
    const pointer_uint_q POOL_SIZE = BLOCKS_COUNT * BLOCK_SIZE;
    
    QPoolAllocator allocator(POOL_SIZE, BLOCK_SIZE, QAlignment(alignof_q(int)));
    for(pointer_uint_q i = 0; i < BLOCKS_COUNT - 1; ++i)
        *(int*)allocator.Allocate() = i;

    const pointer_uint_q EXPECTED_POOL_SIZE       = (BLOCKS_COUNT + 1) * BLOCK_SIZE;
    const pointer_uint_q EXPECTED_TOTAL_SIZE      = EXPECTED_POOL_SIZE + sizeof(void**) * (BLOCKS_COUNT + 1);
    const pointer_uint_q EXPECTED_ALLOCATED_BYTES = allocator.GetAllocatedBytes();
    
    // [Execution]
    allocator.Reallocate(EXPECTED_POOL_SIZE);
 
    // [Verification]
    pointer_uint_q uTotalSize      = allocator.GetTotalSize();
    pointer_uint_q uPoolSize       = allocator.GetPoolSize();
    pointer_uint_q uAllocatedBytes = allocator.GetAllocatedBytes();

    BOOST_CHECK_EQUAL(uTotalSize,      EXPECTED_TOTAL_SIZE);
    BOOST_CHECK_EQUAL(uPoolSize,       EXPECTED_POOL_SIZE);
    BOOST_CHECK_EQUAL(uAllocatedBytes, EXPECTED_ALLOCATED_BYTES);
}

/// <summary>
/// Checks that the data inside the pool is correctly copied.
/// </summary>
QTEST_CASE( Reallocate1_AllocationsCanBeDoneAfterReallocatingFullAllocator_Test )
{
    // [Preparation]
    void* NULL_POINTER = null_q;
    const pointer_uint_q BLOCK_SIZE = sizeof(int);
    const pointer_uint_q BLOCKS_COUNT = 4;
    const pointer_uint_q POOL_SIZE = BLOCKS_COUNT * BLOCK_SIZE;
    QPoolAllocator allocator(POOL_SIZE, BLOCK_SIZE, QAlignment(alignof_q(int)));
    for(pointer_uint_q i = 0; i < BLOCKS_COUNT; ++i)
        *(int*)allocator.Allocate() = i;
    
    // [Execution]
    allocator.Reallocate(BLOCK_SIZE * (BLOCKS_COUNT + 1));
 
    // [Verification]
    void* pAllocation = allocator.Allocate();
    
    BOOST_CHECK_NE(pAllocation, NULL_POINTER);
}

#if QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the input size is not greater than the current pool size.
/// </summary>
QTEST_CASE( Reallocate1_AssertionFailsWhenInputSizeIsNotGreaterThanCurrentPoolSize_Test )
{
    // [Preparation]
    const bool ASSERTION_FAILED = true;
    const pointer_uint_q BLOCK_SIZE = sizeof(int);
    const pointer_uint_q BLOCKS_COUNT = 4;
    const pointer_uint_q CURRENT_POOL_SIZE = BLOCKS_COUNT * BLOCK_SIZE;
    QPoolAllocator allocator(CURRENT_POOL_SIZE, BLOCK_SIZE, QAlignment(alignof_q(int)));
    
    // [Execution]
    bool bAssertionFailed = false;

    try
    {
        allocator.Reallocate(CURRENT_POOL_SIZE);
    }
    catch(const QAssertException&)
    {
        bAssertionFailed = true;
    }
 
    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

#endif

/// <summary>
/// Checks that the data inside the pool is correctly copied.
/// </summary>
QTEST_CASE( Reallocate2_PoolContentIsCorrectlyCopied_Test )
{
    // [Preparation]
    const bool IS_SAME_DATA = true;
    const pointer_uint_q BLOCK_SIZE = sizeof(unsigned int);
    const pointer_uint_q BLOCKS_COUNT = 4;
    const pointer_uint_q POOL_SIZE = BLOCKS_COUNT * BLOCK_SIZE;
    const pointer_uint_q NEW_POOL_SIZE = POOL_SIZE + BLOCK_SIZE;

    void* pInputBuffer = operator new(NEW_POOL_SIZE);

    QPoolAllocator allocator(POOL_SIZE, BLOCK_SIZE, QAlignment(alignof_q(unsigned int)));
    for(pointer_uint_q i = 0; i < BLOCKS_COUNT; ++i)
        *(unsigned int*)allocator.Allocate() = i;
    
    // [Execution]
    allocator.Reallocate(NEW_POOL_SIZE, pInputBuffer);
 
    // [Verification]
    bool bIsSameData = true;
    
    for(pointer_uint_q i = 0; i < BLOCKS_COUNT; ++i)
        bIsSameData = bIsSameData && *((unsigned int*)allocator.GetPointer() + i) == i;

    BOOST_CHECK_EQUAL(bIsSameData, IS_SAME_DATA);

    // [Cleaning]
    operator delete(pInputBuffer);
}

/// <summary>
/// Checks that the size of the pool, the total size and the allocated bytes are correct after the reallocation.
/// </summary>
QTEST_CASE( Reallocate2_SizesAreCorrectAfterReallocation_Test )
{
    // [Preparation]
    const pointer_uint_q BLOCK_SIZE = sizeof(unsigned int);
    const pointer_uint_q BLOCKS_COUNT = 4;
    const pointer_uint_q POOL_SIZE = BLOCKS_COUNT * BLOCK_SIZE;
    const pointer_uint_q NEW_POOL_SIZE = POOL_SIZE + BLOCK_SIZE;

    void* pInputBuffer = operator new(NEW_POOL_SIZE);

    QPoolAllocator allocator(POOL_SIZE, BLOCK_SIZE, QAlignment(alignof_q(unsigned int)));
    for(pointer_uint_q i = 0; i < BLOCKS_COUNT - 1; ++i)
        *(unsigned int*)allocator.Allocate() = i;

    const pointer_uint_q EXPECTED_POOL_SIZE       = (BLOCKS_COUNT + 1) * BLOCK_SIZE;
    const pointer_uint_q EXPECTED_TOTAL_SIZE      = EXPECTED_POOL_SIZE + sizeof(void**) * (BLOCKS_COUNT + 1);
    const pointer_uint_q EXPECTED_ALLOCATED_BYTES = allocator.GetAllocatedBytes();
    
    // [Execution]
    allocator.Reallocate(EXPECTED_POOL_SIZE, pInputBuffer);
 
    // [Verification]
    pointer_uint_q uTotalSize      = allocator.GetTotalSize();
    pointer_uint_q uPoolSize       = allocator.GetPoolSize();
    pointer_uint_q uAllocatedBytes = allocator.GetAllocatedBytes();

    BOOST_CHECK_EQUAL(uTotalSize,      EXPECTED_TOTAL_SIZE);
    BOOST_CHECK_EQUAL(uPoolSize,       EXPECTED_POOL_SIZE);
    BOOST_CHECK_EQUAL(uAllocatedBytes, EXPECTED_ALLOCATED_BYTES);

    // [Cleaning]
    operator delete(pInputBuffer);
}

/// <summary>
/// Checks that the data inside the pool is correctly copied.
/// </summary>
QTEST_CASE( Reallocate2_AllocationsCanBeDoneAfterReallocatingFullAllocator_Test )
{
    // [Preparation]
    void* NULL_POINTER = null_q;
    const pointer_uint_q BLOCK_SIZE = sizeof(int);
    const pointer_uint_q BLOCKS_COUNT = 4;
    const pointer_uint_q POOL_SIZE = BLOCKS_COUNT * BLOCK_SIZE;
    const pointer_uint_q NEW_POOL_SIZE = POOL_SIZE + BLOCK_SIZE;

    void* pInputBuffer = operator new(NEW_POOL_SIZE);

    QPoolAllocator allocator(POOL_SIZE, BLOCK_SIZE, QAlignment(alignof_q(int)));
    for(pointer_uint_q i = 0; i < BLOCKS_COUNT; ++i)
        *(int*)allocator.Allocate() = i;
    
    // [Execution]
    allocator.Reallocate(BLOCK_SIZE * (BLOCKS_COUNT + 1), pInputBuffer);
 
    // [Verification]
    void* pAllocation = allocator.Allocate();
    
    BOOST_CHECK_NE(pAllocation, NULL_POINTER);

    // [Cleaning]
    operator delete(pInputBuffer);
}

#if QE_CONFIG_ASSERTSBEHAVIOR_DEFAULT == QE_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the input size is not greater than the current pool size.
/// </summary>
QTEST_CASE( Reallocate2_AssertionFailsWhenInputSizeIsNotGreaterThanCurrentPoolSize_Test )
{
    // [Preparation]
    const bool ASSERTION_FAILED = true;
    const pointer_uint_q BLOCK_SIZE = sizeof(int);
    const pointer_uint_q BLOCKS_COUNT = 4;
    const pointer_uint_q CURRENT_POOL_SIZE = BLOCKS_COUNT * BLOCK_SIZE;
    const pointer_uint_q NEW_POOL_SIZE = CURRENT_POOL_SIZE + BLOCK_SIZE;

    void* pInputBuffer = operator new(NEW_POOL_SIZE);

    QPoolAllocator allocator(CURRENT_POOL_SIZE, BLOCK_SIZE, QAlignment(alignof_q(int)));
    
    // [Execution]
    bool bAssertionFailed = false;

    try
    {
        allocator.Reallocate(CURRENT_POOL_SIZE, pInputBuffer);
    }
    catch(const QAssertException&)
    {
        bAssertionFailed = true;
    }
 
    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);

    // [Cleaning]
    operator delete(pInputBuffer);
}

/// <summary>
/// Checks that an assertion fails when the input buffer is null.
/// </summary>
QTEST_CASE( Reallocate2_AssertionFailsWhenInputBufferIsNull_Test )
{
    // [Preparation]
    const bool ASSERTION_FAILED = true;
    const pointer_uint_q BLOCK_SIZE = sizeof(int);
    const pointer_uint_q BLOCKS_COUNT = 4;
    const pointer_uint_q CURRENT_POOL_SIZE = BLOCKS_COUNT * BLOCK_SIZE;
    const void* NULL_POINTER = null_q;
    QPoolAllocator allocator(CURRENT_POOL_SIZE, BLOCK_SIZE, QAlignment(alignof_q(int)));
    
    // [Execution]
    bool bAssertionFailed = false;

    try
    {
        allocator.Reallocate(CURRENT_POOL_SIZE, NULL_POINTER);
    }
    catch(const QAssertException&)
    {
        bAssertionFailed = true;
    }
 
    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

#endif


// End - Test Suite: QPoolAllocator
QTEST_SUITE_END()
