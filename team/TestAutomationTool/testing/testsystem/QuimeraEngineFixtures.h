// [TERMS&CONDITIONS]

#ifndef __TATFIXTURES__
#define __TATFIXTURES__

#define TATTEST_SUITE_FIXTURE( fixture_class_name, suite_name )                   \
class fixture_class_name                                                        \
{                                                                               \
public:                                                                         \
    fixture_class_name()                                                        \
    {                                                                           \
        BOOST_TEST_MESSAGE(std::string("Starting Test Fixture ") + suite_name); \
    }                                                                           \
                                                                                \
    ~fixture_class_name()                                                       \
    {                                                                           \
        BOOST_TEST_MESSAGE(std::string("Ending Test Fixture ") + suite_name);   \
    }                                                                           \
};

#endif // __TATFIXTURES__
