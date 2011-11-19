// [TERMS&CONDITIONS]

#ifndef __TESTINGHELPERDEFINITIONS__
#define __TESTINGHELPERDEFINITIONS__

// --------------------------------------------------------------------------------------------------------
// QUNITTEST_MODULE_CONFIG: Use this macro to define a new unit test module with no additional logic. In case
// some logic has to be implemented in the constructor or the destructor, a new class has to be defined
// manually, inheriting from QUnitTestModuleBase in the same way this macro does.
// Note: Remember to include the files in which the classes used here are defined before using this macro.
// --------------------------------------------------------------------------------------------------------
#define QUNITTEST_MODULE_CONFIG( ModuleName )   using Kinesis::QuimeraEngine::Test::QUnitTestModuleBase;                      \
                                                                                                                              \
                                                class TestModuleConfiguration##ModuleName : public QUnitTestModuleBase        \
                                                {                                                                             \
                                                public:                                                                       \
                                                    TestModuleConfiguration##ModuleName() : QUnitTestModuleBase(#ModuleName)  \
                                                    {                                                                         \
                                                    }                                                                         \
                                                                                                                              \
                                                    virtual ~TestModuleConfiguration##ModuleName()                            \
                                                    {                                                                         \
                                                    }                                                                         \
                                                };                                                                            \
                                                                                                                              \
                                                BOOST_GLOBAL_FIXTURE( TestModuleConfiguration##ModuleName );

// --------------------------------------------------------------------------------------------------------
// QPERFORMANCETEST_MODULE_CONFIG: Use this macro to define a new performance test module with no additional logic. 
// In case some logic has to be implemented in the constructor or the destructor, a new class has to be defined
// manually, inheriting from QPerformanceTestModuleBase in the same way this macro does.
// Note: Remember to include the files in which the classes used here are defined before using this macro.
// --------------------------------------------------------------------------------------------------------
#define QPERFORMANCETEST_MODULE_CONFIG( ModuleName )   using Kinesis::QuimeraEngine::Test::QPerformanceTestModuleBase;                      \
                                                                                                                                            \
                                                       class TestModuleConfiguration##ModuleName : public QPerformanceTestModuleBase        \
                                                       {                                                                                    \
                                                       public:                                                                              \
                                                           TestModuleConfiguration##ModuleName() : QPerformanceTestModuleBase(#ModuleName)  \
                                                           {                                                                                \
                                                           }                                                                                \
                                                                                                                                            \
                                                           virtual ~TestModuleConfiguration##ModuleName()                                   \
                                                           {                                                                                \
                                                           }                                                                                \
                                                       };                                                                                   \
                                                                                                                                            \
                                                       BOOST_GLOBAL_FIXTURE( TestModuleConfiguration##ModuleName );

#endif // __TESTINGHELPERDEFINITIONS__