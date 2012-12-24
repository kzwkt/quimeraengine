// [TERMS&CONDITIONS]

#ifndef __INTERNALDEFINITIONS__
#define __INTERNALDEFINITIONS__

#include "ExternalDefinitions.h"

// --------------------------------------------------------------------------------------------------------
// Test artifacts directory: Defines the directory where the artifacts used by the tests are allocated.
// --------------------------------------------------------------------------------------------------------
#define TAT_ARTIFACTS_DIRECTORY "TestArtifacts"

// --------------------------------------------------------------------------------------------------------
// Null Pointer: Defines the value that identifies a null pointer, depending on the compiler.
// --------------------------------------------------------------------------------------------------------
#ifdef TAT_COMPILER_MSVC
    #if TAT_COMPILER_MSVC >= 10
        #define null_t nullptr // Microsoft Visual C++ 2010 definition for null pointers
    #else
        #define null_t 0
    #endif
#elif TAT_COMPILER_GCC
    #define null_t 0
#endif

// --------------------------------------------------------------------------------------------------------
// Assertions: Defines assertion statement behavior.
// --------------------------------------------------------------------------------------------------------
#if TAT_CONFIG_ASSERTSBEHAVIOR_DEFAULT != TAT_CONFIG_ASSERTSBEHAVIOR_DISABLED

    #if TAT_CONFIG_ASSERTSBEHAVIOR_DEFAULT == TAT_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS // This is used for testing purposes
        #include <exception>
        #define TAT_ASSERT(expr) { if(!(expr)) throw new std::exception(); } // TODO [Thund]: Create an special exception class for this
    #else
        #ifdef TAT_COMPILER_GCC
            namespace // Anonymous namespace to make it internally linked
            {
                /// <summary>
                /// Special behaviour for using GDB so it stops at the line the assertion fails and let the
                /// developer to continue debugging from there on advance.
                /// </summary>
                void TAT_ASSERT_FAILED()
                {
                    asm("int $3");
                }
            }

            #define TAT_ASSERT(expr) (expr) ? (void(0)) : TAT_ASSERT_FAILED(); // This sentence makes GDB to stop at the failing line and continue the execution later
        #else
            #include <boost/assert.hpp>

            #ifdef BOOST_ASSERT
                #define TAT_ASSERT(expr) BOOST_ASSERT(expr);
            #else
                #define TAT_ASSERT(expr) ;
            #endif
        #endif
    #endif

#else

    #define TAT_ASSERT(expr) ;

#endif

#endif // __INTERNALDEFINITIONS__
