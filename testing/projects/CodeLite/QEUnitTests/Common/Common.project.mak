#------------------------------------------------------------------------------------------------------------#
#------------------------------------Common------------------------------------#
#------------------------------------------------------------------------------------------------------------#
CXX = g++.exe
AR = ar.exe
LD = g++.exe
AS = as.exe

#------------------------------------------------------------
#----------------------- GLOBAL ---------------------
#------------------------------------------------------------
INCLUDES_GLOBAL = -I$(EXECUTION_PATH).
LIBRARYDIRS_GLOBAL = -L$(EXECUTION_PATH).
LIBRARIES_GLOBAL =
COMPILEROPTIONS_GLOBAL = 
LINKEROPTIONS_GLOBAL = 
DEFINITIONS_GLOBAL =

#------------------------------------------------------------
#------------- DebugLinux32SharedrtDynamic --------------
#------------------------------------------------------------
INCLUDES_DEBUGLINUX32SHAREDRTDYNAMIC = $(INCLUDES_GLOBAL) -I$(EXECUTION_PATH)../../../../headers -I$(EXECUTION_PATH)../../../tests/unit/testmodule_common -I$(EXECUTION_PATH)../../../tests/unit -I$(EXECUTION_PATH)../../../../3rdparty/ICU/include
LIBRARYDIRS_DEBUGLINUX32SHAREDRTDYNAMIC = $(LIBRARYDIRS_GLOBAL) -L$(EXECUTION_PATH)../../../../3rdparty/Boost/bin/Linux32/DebugSharedrtStatic -L$(EXECUTION_PATH)../../../../bin/GCC/DebugLinux32SharedrtDynamic
LIBRARIES_DEBUGLINUX32SHAREDRTDYNAMIC = $(LIBRARIES_GLOBAL) -lQuimeraEngineCommon -lboost_unit_test_framework-mt-d -licudata -licuuc -licui18n
COMPILEROPTIONS_DEBUGLINUX32SHAREDRTDYNAMIC = $(COMPILEROPTIONS_GLOBAL) -g -O0 -Wall -Wno-comment -Wno-unused-local-typedefs -m32 -isystem $(EXECUTION_PATH)../../../../3rdparty/Boost/include
LINKEROPTIONS_DEBUGLINUX32SHAREDRTDYNAMIC = $(LINKEROPTIONS_GLOBAL) -m32
DEFINITIONS_DEBUGLINUX32SHAREDRTDYNAMIC = $(DEFINITIONS_GLOBAL) -DQE_PREPROCESSOR_IMPORTLIB_QUIMERAENGINE
OUTPUT_DEBUGLINUX32SHAREDRTDYNAMIC = $(EXECUTION_PATH)../../../bin/GCC/DebugLinux32SharedrtDynamic/Unit_TestModule_Common
INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTDYNAMIC = $(EXECUTION_PATH)../../../garbage/GCC/DebugLinux32SharedrtDynamic/
OBJECTS_DEBUGLINUX32SHAREDRTDYNAMIC = $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_common.QDelegate_Test.o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_common.TestModule_Common.o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_common.QReferenceWrapper_Test.o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_common.QCharUnicode_Test.o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_common.QConstCharIterator_Test.o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_common.QStringUnicode_Test.o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_common.QType_Test.o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_common.SQBoolean_Test.o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_common.SQFloat_Test.o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_common.SQInteger_Test.o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_common.SQVF32_Test.o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_common.QCharIterator_Test.o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_common.AllocationOperators_Test.o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_common.QAlignment_Test.o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_common.QPoolAllocator_Test.o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_common.QLinearAllocator_Test.o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_common.QBlockHeader_Test.o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_common.QMark_Test.o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_common.QMarkMocked.o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_common.QStackAllocator_Test.o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_common.EQEnumeration_Test.o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTDYNAMIC)__.__.__.testsystem.EQTestType.o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTDYNAMIC)__.__.__.testsystem.QCommonTestConfig.o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTDYNAMIC)__.__.__.testsystem.QSimpleConfigLoader.o

prebuildDebugLinux32SharedrtDynamic:
	test -d $(EXECUTION_PATH)../../../bin/GCC/DebugLinux32SharedrtDynamic mkdir -p "$(EXECUTION_PATH)../../../bin/GCC/DebugLinux32SharedrtDynamic"
	test -d $(EXECUTION_PATH)../../../garbage/GCC/DebugLinux32SharedrtDynamic mkdir -p "$(EXECUTION_PATH)../../../garbage/GCC/DebugLinux32SharedrtDynamic"
	mkdir -p $(EXECUTION_PATH)../../../bin/GCC/DebugLinux32SharedrtDynamic
	cp "$(EXECUTION_PATH)../../../../bin/GCC/DebugLinux32SharedrtDynamic/libQuimeraEngineCommon.so" "$(EXECUTION_PATH)../../../bin/GCC/DebugLinux32SharedrtDynamic"
	cp "$(EXECUTION_PATH)../../../../bin/GCC/DebugLinux32SharedrtDynamic/libQuimeraEngineCommon.so" "$(EXECUTION_PATH)."
	cp "$(EXECUTION_PATH)../../../bin/TestConfig.txt" "$(EXECUTION_PATH)../../../bin/GCC/DebugLinux32SharedrtDynamic"
	cp "$(EXECUTION_PATH)../../../bin/NormalizationTest.txt" "$(EXECUTION_PATH)../../../bin/GCC/DebugLinux32SharedrtDynamic"


DebugLinux32SharedrtDynamic: $(OBJECTS_DEBUGLINUX32SHAREDRTDYNAMIC)
	$(LD) $(LINKEROPTIONS_DEBUGLINUX32SHAREDRTDYNAMIC) $(LIBRARYDIRS_DEBUGLINUX32SHAREDRTDYNAMIC) $(OBJECTS_DEBUGLINUX32SHAREDRTDYNAMIC) $(LIBRARIES_DEBUGLINUX32SHAREDRTDYNAMIC) -o $(OUTPUT_DEBUGLINUX32SHAREDRTDYNAMIC)

$(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_common.QDelegate_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_common/QDelegate_Test.cpp
	$(CXX) $(COMPILEROPTIONS_DEBUGLINUX32SHAREDRTDYNAMIC) $(INCLUDES_DEBUGLINUX32SHAREDRTDYNAMIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_common/QDelegate_Test.cpp -o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_common.QDelegate_Test.o

$(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_common.TestModule_Common.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_common/TestModule_Common.cpp
	$(CXX) $(COMPILEROPTIONS_DEBUGLINUX32SHAREDRTDYNAMIC) $(INCLUDES_DEBUGLINUX32SHAREDRTDYNAMIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_common/TestModule_Common.cpp -o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_common.TestModule_Common.o

$(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_common.QReferenceWrapper_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_common/QReferenceWrapper_Test.cpp
	$(CXX) $(COMPILEROPTIONS_DEBUGLINUX32SHAREDRTDYNAMIC) $(INCLUDES_DEBUGLINUX32SHAREDRTDYNAMIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_common/QReferenceWrapper_Test.cpp -o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_common.QReferenceWrapper_Test.o

$(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_common.QCharUnicode_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_common/QCharUnicode_Test.cpp
	$(CXX) $(COMPILEROPTIONS_DEBUGLINUX32SHAREDRTDYNAMIC) $(INCLUDES_DEBUGLINUX32SHAREDRTDYNAMIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_common/QCharUnicode_Test.cpp -o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_common.QCharUnicode_Test.o

$(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_common.QConstCharIterator_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_common/QConstCharIterator_Test.cpp
	$(CXX) $(COMPILEROPTIONS_DEBUGLINUX32SHAREDRTDYNAMIC) $(INCLUDES_DEBUGLINUX32SHAREDRTDYNAMIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_common/QConstCharIterator_Test.cpp -o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_common.QConstCharIterator_Test.o

$(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_common.QStringUnicode_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_common/QStringUnicode_Test.cpp
	$(CXX) $(COMPILEROPTIONS_DEBUGLINUX32SHAREDRTDYNAMIC) $(INCLUDES_DEBUGLINUX32SHAREDRTDYNAMIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_common/QStringUnicode_Test.cpp -o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_common.QStringUnicode_Test.o

$(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_common.QType_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_common/QType_Test.cpp
	$(CXX) $(COMPILEROPTIONS_DEBUGLINUX32SHAREDRTDYNAMIC) $(INCLUDES_DEBUGLINUX32SHAREDRTDYNAMIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_common/QType_Test.cpp -o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_common.QType_Test.o

$(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_common.SQBoolean_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_common/SQBoolean_Test.cpp
	$(CXX) $(COMPILEROPTIONS_DEBUGLINUX32SHAREDRTDYNAMIC) $(INCLUDES_DEBUGLINUX32SHAREDRTDYNAMIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_common/SQBoolean_Test.cpp -o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_common.SQBoolean_Test.o

$(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_common.SQFloat_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_common/SQFloat_Test.cpp
	$(CXX) $(COMPILEROPTIONS_DEBUGLINUX32SHAREDRTDYNAMIC) $(INCLUDES_DEBUGLINUX32SHAREDRTDYNAMIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_common/SQFloat_Test.cpp -o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_common.SQFloat_Test.o

$(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_common.SQInteger_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_common/SQInteger_Test.cpp
	$(CXX) $(COMPILEROPTIONS_DEBUGLINUX32SHAREDRTDYNAMIC) $(INCLUDES_DEBUGLINUX32SHAREDRTDYNAMIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_common/SQInteger_Test.cpp -o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_common.SQInteger_Test.o

$(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_common.SQVF32_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_common/SQVF32_Test.cpp
	$(CXX) $(COMPILEROPTIONS_DEBUGLINUX32SHAREDRTDYNAMIC) $(INCLUDES_DEBUGLINUX32SHAREDRTDYNAMIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_common/SQVF32_Test.cpp -o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_common.SQVF32_Test.o

$(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_common.QCharIterator_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_common/QCharIterator_Test.cpp
	$(CXX) $(COMPILEROPTIONS_DEBUGLINUX32SHAREDRTDYNAMIC) $(INCLUDES_DEBUGLINUX32SHAREDRTDYNAMIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_common/QCharIterator_Test.cpp -o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_common.QCharIterator_Test.o

$(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_common.AllocationOperators_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_common/AllocationOperators_Test.cpp
	$(CXX) $(COMPILEROPTIONS_DEBUGLINUX32SHAREDRTDYNAMIC) $(INCLUDES_DEBUGLINUX32SHAREDRTDYNAMIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_common/AllocationOperators_Test.cpp -o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_common.AllocationOperators_Test.o

$(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_common.QAlignment_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_common/QAlignment_Test.cpp
	$(CXX) $(COMPILEROPTIONS_DEBUGLINUX32SHAREDRTDYNAMIC) $(INCLUDES_DEBUGLINUX32SHAREDRTDYNAMIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_common/QAlignment_Test.cpp -o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_common.QAlignment_Test.o

$(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_common.QPoolAllocator_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_common/QPoolAllocator_Test.cpp
	$(CXX) $(COMPILEROPTIONS_DEBUGLINUX32SHAREDRTDYNAMIC) $(INCLUDES_DEBUGLINUX32SHAREDRTDYNAMIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_common/QPoolAllocator_Test.cpp -o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_common.QPoolAllocator_Test.o

$(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_common.QLinearAllocator_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_common/QLinearAllocator_Test.cpp
	$(CXX) $(COMPILEROPTIONS_DEBUGLINUX32SHAREDRTDYNAMIC) $(INCLUDES_DEBUGLINUX32SHAREDRTDYNAMIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_common/QLinearAllocator_Test.cpp -o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_common.QLinearAllocator_Test.o

$(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_common.QBlockHeader_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_common/QBlockHeader_Test.cpp
	$(CXX) $(COMPILEROPTIONS_DEBUGLINUX32SHAREDRTDYNAMIC) $(INCLUDES_DEBUGLINUX32SHAREDRTDYNAMIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_common/QBlockHeader_Test.cpp -o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_common.QBlockHeader_Test.o

$(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_common.QMark_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_common/QMark_Test.cpp
	$(CXX) $(COMPILEROPTIONS_DEBUGLINUX32SHAREDRTDYNAMIC) $(INCLUDES_DEBUGLINUX32SHAREDRTDYNAMIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_common/QMark_Test.cpp -o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_common.QMark_Test.o

$(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_common.QMarkMocked.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_common/QMarkMocked.cpp
	$(CXX) $(COMPILEROPTIONS_DEBUGLINUX32SHAREDRTDYNAMIC) $(INCLUDES_DEBUGLINUX32SHAREDRTDYNAMIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_common/QMarkMocked.cpp -o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_common.QMarkMocked.o

$(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_common.QStackAllocator_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_common/QStackAllocator_Test.cpp
	$(CXX) $(COMPILEROPTIONS_DEBUGLINUX32SHAREDRTDYNAMIC) $(INCLUDES_DEBUGLINUX32SHAREDRTDYNAMIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_common/QStackAllocator_Test.cpp -o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_common.QStackAllocator_Test.o

$(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_common.EQEnumeration_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_common/EQEnumeration_Test.cpp
	$(CXX) $(COMPILEROPTIONS_DEBUGLINUX32SHAREDRTDYNAMIC) $(INCLUDES_DEBUGLINUX32SHAREDRTDYNAMIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_common/EQEnumeration_Test.cpp -o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_common.EQEnumeration_Test.o

$(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTDYNAMIC)__.__.__.testsystem.EQTestType.o: $(EXECUTION_PATH)../../../testsystem/EQTestType.cpp
	$(CXX) $(COMPILEROPTIONS_DEBUGLINUX32SHAREDRTDYNAMIC) $(INCLUDES_DEBUGLINUX32SHAREDRTDYNAMIC) -c $(EXECUTION_PATH)../../../testsystem/EQTestType.cpp -o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTDYNAMIC)__.__.__.testsystem.EQTestType.o

$(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTDYNAMIC)__.__.__.testsystem.QCommonTestConfig.o: $(EXECUTION_PATH)../../../testsystem/QCommonTestConfig.cpp
	$(CXX) $(COMPILEROPTIONS_DEBUGLINUX32SHAREDRTDYNAMIC) $(INCLUDES_DEBUGLINUX32SHAREDRTDYNAMIC) -c $(EXECUTION_PATH)../../../testsystem/QCommonTestConfig.cpp -o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTDYNAMIC)__.__.__.testsystem.QCommonTestConfig.o

$(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTDYNAMIC)__.__.__.testsystem.QSimpleConfigLoader.o: $(EXECUTION_PATH)../../../testsystem/QSimpleConfigLoader.cpp
	$(CXX) $(COMPILEROPTIONS_DEBUGLINUX32SHAREDRTDYNAMIC) $(INCLUDES_DEBUGLINUX32SHAREDRTDYNAMIC) -c $(EXECUTION_PATH)../../../testsystem/QSimpleConfigLoader.cpp -o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTDYNAMIC)__.__.__.testsystem.QSimpleConfigLoader.o

postbuildDebugLinux32SharedrtDynamic:
	rm *.so


buildDebugLinux32SharedrtDynamic: prebuildDebugLinux32SharedrtDynamic DebugLinux32SharedrtDynamic postbuildDebugLinux32SharedrtDynamic

cleanDebugLinux32SharedrtDynamic:
	rm -f $(OBJECTS_DEBUGLINUX32SHAREDRTDYNAMIC)
	rm -f $(OUTPUT_DEBUGLINUX32SHAREDRTDYNAMIC)
	test -d $(EXECUTION_PATH)../../../bin/GCC/DebugLinux32SharedrtDynamic rmdir "$(EXECUTION_PATH)..\..\..\bin\GCC\DebugLinux32SharedrtDynamic"
	test -d $(EXECUTION_PATH)../../../garbage/GCC/DebugLinux32SharedrtDynamic rmdir "$(EXECUTION_PATH)..\..\..\garbage\GCC\DebugLinux32SharedrtDynamic"


#------------------------------------------------------------
#------------- DebugLinux32SharedrtStatic --------------
#------------------------------------------------------------
INCLUDES_DEBUGLINUX32SHAREDRTSTATIC = $(INCLUDES_GLOBAL) -I$(EXECUTION_PATH)../../../../headers -I$(EXECUTION_PATH)../../../tests/unit/testmodule_common -I$(EXECUTION_PATH)../../../tests/unit -I$(EXECUTION_PATH)../../../../3rdparty/ICU/include
LIBRARYDIRS_DEBUGLINUX32SHAREDRTSTATIC = $(LIBRARYDIRS_GLOBAL) -L$(EXECUTION_PATH)../../../../3rdparty/Boost/bin/Linux32/DebugSharedrtStatic -L$(EXECUTION_PATH)../../../../bin/GCC/DebugLinux32SharedrtStatic
LIBRARIES_DEBUGLINUX32SHAREDRTSTATIC = $(LIBRARIES_GLOBAL) -lQuimeraEngineCommon -lboost_unit_test_framework-mt-d -licudata -licuuc -licui18n
COMPILEROPTIONS_DEBUGLINUX32SHAREDRTSTATIC = $(COMPILEROPTIONS_GLOBAL) -g -O0 -Wall -Wno-comment -Wno-unused-local-typedefs -m32 -isystem $(EXECUTION_PATH)../../../../3rdparty/Boost/include
LINKEROPTIONS_DEBUGLINUX32SHAREDRTSTATIC = $(LINKEROPTIONS_GLOBAL) -m32
DEFINITIONS_DEBUGLINUX32SHAREDRTSTATIC = $(DEFINITIONS_GLOBAL)
OUTPUT_DEBUGLINUX32SHAREDRTSTATIC = $(EXECUTION_PATH)../../../bin/GCC/DebugLinux32SharedrtStatic/Unit_TestModule_Common
INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTSTATIC = $(EXECUTION_PATH)../../../garbage/GCC/DebugLinux32SharedrtStatic/
OBJECTS_DEBUGLINUX32SHAREDRTSTATIC = $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_common.QDelegate_Test.o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_common.TestModule_Common.o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_common.QReferenceWrapper_Test.o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_common.QCharUnicode_Test.o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_common.QConstCharIterator_Test.o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_common.QStringUnicode_Test.o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_common.QType_Test.o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_common.SQBoolean_Test.o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_common.SQFloat_Test.o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_common.SQInteger_Test.o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_common.SQVF32_Test.o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_common.QCharIterator_Test.o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_common.AllocationOperators_Test.o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_common.QAlignment_Test.o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_common.QPoolAllocator_Test.o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_common.QLinearAllocator_Test.o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_common.QBlockHeader_Test.o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_common.QMark_Test.o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_common.QMarkMocked.o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_common.QStackAllocator_Test.o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_common.EQEnumeration_Test.o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTSTATIC)__.__.__.testsystem.EQTestType.o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTSTATIC)__.__.__.testsystem.QCommonTestConfig.o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTSTATIC)__.__.__.testsystem.QSimpleConfigLoader.o

prebuildDebugLinux32SharedrtStatic:
	test -d $(EXECUTION_PATH)../../../bin/GCC/DebugLinux32SharedrtStatic mkdir -p "$(EXECUTION_PATH)../../../bin/GCC/DebugLinux32SharedrtStatic"
	test -d $(EXECUTION_PATH)../../../garbage/GCC/DebugLinux32SharedrtStatic mkdir -p "$(EXECUTION_PATH)../../../garbage/GCC/DebugLinux32SharedrtStatic"
	mkdir -p $(EXECUTION_PATH)../../../bin/GCC/DebugLinux32SharedrtStatic
	cp "$(EXECUTION_PATH)../../../bin/TestConfig.txt" "$(EXECUTION_PATH)../../../bin/GCC/DebugLinux32SharedrtStatic"
	cp "$(EXECUTION_PATH)../../../bin/NormalizationTest.txt" "$(EXECUTION_PATH)../../../bin/GCC/DebugLinux32SharedrtStatic"


DebugLinux32SharedrtStatic: $(OBJECTS_DEBUGLINUX32SHAREDRTSTATIC)
	$(LD) $(LINKEROPTIONS_DEBUGLINUX32SHAREDRTSTATIC) $(LIBRARYDIRS_DEBUGLINUX32SHAREDRTSTATIC) $(OBJECTS_DEBUGLINUX32SHAREDRTSTATIC) $(LIBRARIES_DEBUGLINUX32SHAREDRTSTATIC) -o $(OUTPUT_DEBUGLINUX32SHAREDRTSTATIC)

$(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_common.QDelegate_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_common/QDelegate_Test.cpp
	$(CXX) $(COMPILEROPTIONS_DEBUGLINUX32SHAREDRTSTATIC) $(INCLUDES_DEBUGLINUX32SHAREDRTSTATIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_common/QDelegate_Test.cpp -o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_common.QDelegate_Test.o

$(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_common.TestModule_Common.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_common/TestModule_Common.cpp
	$(CXX) $(COMPILEROPTIONS_DEBUGLINUX32SHAREDRTSTATIC) $(INCLUDES_DEBUGLINUX32SHAREDRTSTATIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_common/TestModule_Common.cpp -o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_common.TestModule_Common.o

$(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_common.QReferenceWrapper_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_common/QReferenceWrapper_Test.cpp
	$(CXX) $(COMPILEROPTIONS_DEBUGLINUX32SHAREDRTSTATIC) $(INCLUDES_DEBUGLINUX32SHAREDRTSTATIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_common/QReferenceWrapper_Test.cpp -o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_common.QReferenceWrapper_Test.o

$(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_common.QCharUnicode_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_common/QCharUnicode_Test.cpp
	$(CXX) $(COMPILEROPTIONS_DEBUGLINUX32SHAREDRTSTATIC) $(INCLUDES_DEBUGLINUX32SHAREDRTSTATIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_common/QCharUnicode_Test.cpp -o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_common.QCharUnicode_Test.o

$(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_common.QConstCharIterator_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_common/QConstCharIterator_Test.cpp
	$(CXX) $(COMPILEROPTIONS_DEBUGLINUX32SHAREDRTSTATIC) $(INCLUDES_DEBUGLINUX32SHAREDRTSTATIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_common/QConstCharIterator_Test.cpp -o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_common.QConstCharIterator_Test.o

$(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_common.QStringUnicode_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_common/QStringUnicode_Test.cpp
	$(CXX) $(COMPILEROPTIONS_DEBUGLINUX32SHAREDRTSTATIC) $(INCLUDES_DEBUGLINUX32SHAREDRTSTATIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_common/QStringUnicode_Test.cpp -o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_common.QStringUnicode_Test.o

$(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_common.QType_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_common/QType_Test.cpp
	$(CXX) $(COMPILEROPTIONS_DEBUGLINUX32SHAREDRTSTATIC) $(INCLUDES_DEBUGLINUX32SHAREDRTSTATIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_common/QType_Test.cpp -o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_common.QType_Test.o

$(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_common.SQBoolean_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_common/SQBoolean_Test.cpp
	$(CXX) $(COMPILEROPTIONS_DEBUGLINUX32SHAREDRTSTATIC) $(INCLUDES_DEBUGLINUX32SHAREDRTSTATIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_common/SQBoolean_Test.cpp -o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_common.SQBoolean_Test.o

$(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_common.SQFloat_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_common/SQFloat_Test.cpp
	$(CXX) $(COMPILEROPTIONS_DEBUGLINUX32SHAREDRTSTATIC) $(INCLUDES_DEBUGLINUX32SHAREDRTSTATIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_common/SQFloat_Test.cpp -o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_common.SQFloat_Test.o

$(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_common.SQInteger_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_common/SQInteger_Test.cpp
	$(CXX) $(COMPILEROPTIONS_DEBUGLINUX32SHAREDRTSTATIC) $(INCLUDES_DEBUGLINUX32SHAREDRTSTATIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_common/SQInteger_Test.cpp -o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_common.SQInteger_Test.o

$(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_common.SQVF32_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_common/SQVF32_Test.cpp
	$(CXX) $(COMPILEROPTIONS_DEBUGLINUX32SHAREDRTSTATIC) $(INCLUDES_DEBUGLINUX32SHAREDRTSTATIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_common/SQVF32_Test.cpp -o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_common.SQVF32_Test.o

$(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_common.QCharIterator_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_common/QCharIterator_Test.cpp
	$(CXX) $(COMPILEROPTIONS_DEBUGLINUX32SHAREDRTSTATIC) $(INCLUDES_DEBUGLINUX32SHAREDRTSTATIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_common/QCharIterator_Test.cpp -o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_common.QCharIterator_Test.o

$(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_common.AllocationOperators_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_common/AllocationOperators_Test.cpp
	$(CXX) $(COMPILEROPTIONS_DEBUGLINUX32SHAREDRTSTATIC) $(INCLUDES_DEBUGLINUX32SHAREDRTSTATIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_common/AllocationOperators_Test.cpp -o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_common.AllocationOperators_Test.o

$(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_common.QAlignment_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_common/QAlignment_Test.cpp
	$(CXX) $(COMPILEROPTIONS_DEBUGLINUX32SHAREDRTSTATIC) $(INCLUDES_DEBUGLINUX32SHAREDRTSTATIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_common/QAlignment_Test.cpp -o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_common.QAlignment_Test.o

$(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_common.QPoolAllocator_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_common/QPoolAllocator_Test.cpp
	$(CXX) $(COMPILEROPTIONS_DEBUGLINUX32SHAREDRTSTATIC) $(INCLUDES_DEBUGLINUX32SHAREDRTSTATIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_common/QPoolAllocator_Test.cpp -o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_common.QPoolAllocator_Test.o

$(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_common.QLinearAllocator_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_common/QLinearAllocator_Test.cpp
	$(CXX) $(COMPILEROPTIONS_DEBUGLINUX32SHAREDRTSTATIC) $(INCLUDES_DEBUGLINUX32SHAREDRTSTATIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_common/QLinearAllocator_Test.cpp -o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_common.QLinearAllocator_Test.o

$(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_common.QBlockHeader_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_common/QBlockHeader_Test.cpp
	$(CXX) $(COMPILEROPTIONS_DEBUGLINUX32SHAREDRTSTATIC) $(INCLUDES_DEBUGLINUX32SHAREDRTSTATIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_common/QBlockHeader_Test.cpp -o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_common.QBlockHeader_Test.o

$(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_common.QMark_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_common/QMark_Test.cpp
	$(CXX) $(COMPILEROPTIONS_DEBUGLINUX32SHAREDRTSTATIC) $(INCLUDES_DEBUGLINUX32SHAREDRTSTATIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_common/QMark_Test.cpp -o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_common.QMark_Test.o

$(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_common.QMarkMocked.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_common/QMarkMocked.cpp
	$(CXX) $(COMPILEROPTIONS_DEBUGLINUX32SHAREDRTSTATIC) $(INCLUDES_DEBUGLINUX32SHAREDRTSTATIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_common/QMarkMocked.cpp -o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_common.QMarkMocked.o

$(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_common.QStackAllocator_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_common/QStackAllocator_Test.cpp
	$(CXX) $(COMPILEROPTIONS_DEBUGLINUX32SHAREDRTSTATIC) $(INCLUDES_DEBUGLINUX32SHAREDRTSTATIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_common/QStackAllocator_Test.cpp -o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_common.QStackAllocator_Test.o

$(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_common.EQEnumeration_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_common/EQEnumeration_Test.cpp
	$(CXX) $(COMPILEROPTIONS_DEBUGLINUX32SHAREDRTSTATIC) $(INCLUDES_DEBUGLINUX32SHAREDRTSTATIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_common/EQEnumeration_Test.cpp -o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_common.EQEnumeration_Test.o

$(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTSTATIC)__.__.__.testsystem.EQTestType.o: $(EXECUTION_PATH)../../../testsystem/EQTestType.cpp
	$(CXX) $(COMPILEROPTIONS_DEBUGLINUX32SHAREDRTSTATIC) $(INCLUDES_DEBUGLINUX32SHAREDRTSTATIC) -c $(EXECUTION_PATH)../../../testsystem/EQTestType.cpp -o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTSTATIC)__.__.__.testsystem.EQTestType.o

$(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTSTATIC)__.__.__.testsystem.QCommonTestConfig.o: $(EXECUTION_PATH)../../../testsystem/QCommonTestConfig.cpp
	$(CXX) $(COMPILEROPTIONS_DEBUGLINUX32SHAREDRTSTATIC) $(INCLUDES_DEBUGLINUX32SHAREDRTSTATIC) -c $(EXECUTION_PATH)../../../testsystem/QCommonTestConfig.cpp -o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTSTATIC)__.__.__.testsystem.QCommonTestConfig.o

$(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTSTATIC)__.__.__.testsystem.QSimpleConfigLoader.o: $(EXECUTION_PATH)../../../testsystem/QSimpleConfigLoader.cpp
	$(CXX) $(COMPILEROPTIONS_DEBUGLINUX32SHAREDRTSTATIC) $(INCLUDES_DEBUGLINUX32SHAREDRTSTATIC) -c $(EXECUTION_PATH)../../../testsystem/QSimpleConfigLoader.cpp -o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTSTATIC)__.__.__.testsystem.QSimpleConfigLoader.o

postbuildDebugLinux32SharedrtStatic:
	


buildDebugLinux32SharedrtStatic: prebuildDebugLinux32SharedrtStatic DebugLinux32SharedrtStatic postbuildDebugLinux32SharedrtStatic

cleanDebugLinux32SharedrtStatic:
	rm -f $(OBJECTS_DEBUGLINUX32SHAREDRTSTATIC)
	rm -f $(OUTPUT_DEBUGLINUX32SHAREDRTSTATIC)
	test -d $(EXECUTION_PATH)../../../bin/GCC/DebugLinux32SharedrtStatic rmdir "$(EXECUTION_PATH)..\..\..\bin\GCC\DebugLinux32SharedrtStatic"
	test -d $(EXECUTION_PATH)../../../garbage/GCC/DebugLinux32SharedrtStatic rmdir "$(EXECUTION_PATH)..\..\..\garbage\GCC\DebugLinux32SharedrtStatic"


#------------------------------------------------------------
#------------- DebugMac32SharedrtDynamic --------------
#------------------------------------------------------------
INCLUDES_DEBUGMAC32SHAREDRTDYNAMIC = $(INCLUDES_GLOBAL) -I$(EXECUTION_PATH)../../../../headers -I$(EXECUTION_PATH)../../../tests/unit/testmodule_common -I$(EXECUTION_PATH)../../../tests/unit -I$(EXECUTION_PATH)../../../../3rdparty/ICU/include
LIBRARYDIRS_DEBUGMAC32SHAREDRTDYNAMIC = $(LIBRARYDIRS_GLOBAL) -L$(EXECUTION_PATH)../../../../3rdparty/Boost/bin/Mac32/DebugSharedrtStatic -L$(EXECUTION_PATH)../../../../bin/Clang/DebugMac32SharedrtDynamic
LIBRARIES_DEBUGMAC32SHAREDRTDYNAMIC = $(LIBRARIES_GLOBAL) -lQuimeraEngineCommon -lboost_unit_test_framework-mt-d -licudata -licuuc -licui18n
COMPILEROPTIONS_DEBUGMAC32SHAREDRTDYNAMIC = $(COMPILEROPTIONS_GLOBAL) -g -O0 -Wall -Wno-comment -m32 -isystem $(EXECUTION_PATH)../../../../3rdparty/Boost/include
LINKEROPTIONS_DEBUGMAC32SHAREDRTDYNAMIC = $(LINKEROPTIONS_GLOBAL) -m32
DEFINITIONS_DEBUGMAC32SHAREDRTDYNAMIC = $(DEFINITIONS_GLOBAL) -DQE_PREPROCESSOR_IMPORTLIB_QUIMERAENGINE
OUTPUT_DEBUGMAC32SHAREDRTDYNAMIC = $(EXECUTION_PATH)../../../bin/Clang/DebugMac32SharedrtDynamic/Unit_TestModule_Common
INTERMEDIARYDIR_DEBUGMAC32SHAREDRTDYNAMIC = $(EXECUTION_PATH)../../../garbage/Clang/DebugMac32SharedrtDynamic/
OBJECTS_DEBUGMAC32SHAREDRTDYNAMIC = $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_common.QDelegate_Test.o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_common.TestModule_Common.o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_common.QReferenceWrapper_Test.o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_common.QCharUnicode_Test.o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_common.QConstCharIterator_Test.o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_common.QStringUnicode_Test.o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_common.QType_Test.o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_common.SQBoolean_Test.o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_common.SQFloat_Test.o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_common.SQInteger_Test.o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_common.SQVF32_Test.o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_common.QCharIterator_Test.o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_common.AllocationOperators_Test.o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_common.QAlignment_Test.o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_common.QPoolAllocator_Test.o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_common.QLinearAllocator_Test.o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_common.QBlockHeader_Test.o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_common.QMark_Test.o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_common.QMarkMocked.o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_common.QStackAllocator_Test.o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_common.EQEnumeration_Test.o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTDYNAMIC)__.__.__.testsystem.EQTestType.o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTDYNAMIC)__.__.__.testsystem.QCommonTestConfig.o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTDYNAMIC)__.__.__.testsystem.QSimpleConfigLoader.o

prebuildDebugMac32SharedrtDynamic:
	test -d $(EXECUTION_PATH)../../../bin/Clang/DebugMac32SharedrtDynamic mkdir -p "$(EXECUTION_PATH)../../../bin/Clang/DebugMac32SharedrtDynamic"
	test -d $(EXECUTION_PATH)../../../garbage/Clang/DebugMac32SharedrtDynamic mkdir -p "$(EXECUTION_PATH)../../../garbage/Clang/DebugMac32SharedrtDynamic"
	mkdir -p $(EXECUTION_PATH)../../../bin/Clang/DebugMac32SharedrtDynamic
	cp "$(EXECUTION_PATH)../../../../bin/Clang/DebugMac32SharedrtDynamic/libQuimeraEngineCommon.dylib" "$(EXECUTION_PATH)../../../bin/Clang/DebugMac32SharedrtDynamic"
	cp "$(EXECUTION_PATH)../../../../bin/Clang/DebugMac32SharedrtDynamic/libQuimeraEngineCommon.dylib" "$(EXECUTION_PATH)."
	cp "$(EXECUTION_PATH)../../../bin/TestConfig.txt" "$(EXECUTION_PATH)../../../bin/Clang/DebugMac32SharedrtDynamic"
	cp "$(EXECUTION_PATH)../../../bin/NormalizationTest.txt" "$(EXECUTION_PATH)../../../bin/Clang/DebugMac32SharedrtDynamic"


DebugMac32SharedrtDynamic: $(OBJECTS_DEBUGMAC32SHAREDRTDYNAMIC)
	$(LD) $(LINKEROPTIONS_DEBUGMAC32SHAREDRTDYNAMIC) $(LIBRARYDIRS_DEBUGMAC32SHAREDRTDYNAMIC) $(OBJECTS_DEBUGMAC32SHAREDRTDYNAMIC) $(LIBRARIES_DEBUGMAC32SHAREDRTDYNAMIC) -o $(OUTPUT_DEBUGMAC32SHAREDRTDYNAMIC)

$(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_common.QDelegate_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_common/QDelegate_Test.cpp
	$(CXX) $(COMPILEROPTIONS_DEBUGMAC32SHAREDRTDYNAMIC) $(INCLUDES_DEBUGMAC32SHAREDRTDYNAMIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_common/QDelegate_Test.cpp -o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_common.QDelegate_Test.o

$(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_common.TestModule_Common.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_common/TestModule_Common.cpp
	$(CXX) $(COMPILEROPTIONS_DEBUGMAC32SHAREDRTDYNAMIC) $(INCLUDES_DEBUGMAC32SHAREDRTDYNAMIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_common/TestModule_Common.cpp -o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_common.TestModule_Common.o

$(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_common.QReferenceWrapper_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_common/QReferenceWrapper_Test.cpp
	$(CXX) $(COMPILEROPTIONS_DEBUGMAC32SHAREDRTDYNAMIC) $(INCLUDES_DEBUGMAC32SHAREDRTDYNAMIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_common/QReferenceWrapper_Test.cpp -o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_common.QReferenceWrapper_Test.o

$(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_common.QCharUnicode_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_common/QCharUnicode_Test.cpp
	$(CXX) $(COMPILEROPTIONS_DEBUGMAC32SHAREDRTDYNAMIC) $(INCLUDES_DEBUGMAC32SHAREDRTDYNAMIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_common/QCharUnicode_Test.cpp -o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_common.QCharUnicode_Test.o

$(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_common.QConstCharIterator_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_common/QConstCharIterator_Test.cpp
	$(CXX) $(COMPILEROPTIONS_DEBUGMAC32SHAREDRTDYNAMIC) $(INCLUDES_DEBUGMAC32SHAREDRTDYNAMIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_common/QConstCharIterator_Test.cpp -o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_common.QConstCharIterator_Test.o

$(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_common.QStringUnicode_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_common/QStringUnicode_Test.cpp
	$(CXX) $(COMPILEROPTIONS_DEBUGMAC32SHAREDRTDYNAMIC) $(INCLUDES_DEBUGMAC32SHAREDRTDYNAMIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_common/QStringUnicode_Test.cpp -o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_common.QStringUnicode_Test.o

$(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_common.QType_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_common/QType_Test.cpp
	$(CXX) $(COMPILEROPTIONS_DEBUGMAC32SHAREDRTDYNAMIC) $(INCLUDES_DEBUGMAC32SHAREDRTDYNAMIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_common/QType_Test.cpp -o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_common.QType_Test.o

$(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_common.SQBoolean_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_common/SQBoolean_Test.cpp
	$(CXX) $(COMPILEROPTIONS_DEBUGMAC32SHAREDRTDYNAMIC) $(INCLUDES_DEBUGMAC32SHAREDRTDYNAMIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_common/SQBoolean_Test.cpp -o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_common.SQBoolean_Test.o

$(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_common.SQFloat_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_common/SQFloat_Test.cpp
	$(CXX) $(COMPILEROPTIONS_DEBUGMAC32SHAREDRTDYNAMIC) $(INCLUDES_DEBUGMAC32SHAREDRTDYNAMIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_common/SQFloat_Test.cpp -o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_common.SQFloat_Test.o

$(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_common.SQInteger_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_common/SQInteger_Test.cpp
	$(CXX) $(COMPILEROPTIONS_DEBUGMAC32SHAREDRTDYNAMIC) $(INCLUDES_DEBUGMAC32SHAREDRTDYNAMIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_common/SQInteger_Test.cpp -o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_common.SQInteger_Test.o

$(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_common.SQVF32_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_common/SQVF32_Test.cpp
	$(CXX) $(COMPILEROPTIONS_DEBUGMAC32SHAREDRTDYNAMIC) $(INCLUDES_DEBUGMAC32SHAREDRTDYNAMIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_common/SQVF32_Test.cpp -o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_common.SQVF32_Test.o

$(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_common.QCharIterator_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_common/QCharIterator_Test.cpp
	$(CXX) $(COMPILEROPTIONS_DEBUGMAC32SHAREDRTDYNAMIC) $(INCLUDES_DEBUGMAC32SHAREDRTDYNAMIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_common/QCharIterator_Test.cpp -o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_common.QCharIterator_Test.o

$(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_common.AllocationOperators_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_common/AllocationOperators_Test.cpp
	$(CXX) $(COMPILEROPTIONS_DEBUGMAC32SHAREDRTDYNAMIC) $(INCLUDES_DEBUGMAC32SHAREDRTDYNAMIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_common/AllocationOperators_Test.cpp -o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_common.AllocationOperators_Test.o

$(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_common.QAlignment_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_common/QAlignment_Test.cpp
	$(CXX) $(COMPILEROPTIONS_DEBUGMAC32SHAREDRTDYNAMIC) $(INCLUDES_DEBUGMAC32SHAREDRTDYNAMIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_common/QAlignment_Test.cpp -o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_common.QAlignment_Test.o

$(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_common.QPoolAllocator_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_common/QPoolAllocator_Test.cpp
	$(CXX) $(COMPILEROPTIONS_DEBUGMAC32SHAREDRTDYNAMIC) $(INCLUDES_DEBUGMAC32SHAREDRTDYNAMIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_common/QPoolAllocator_Test.cpp -o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_common.QPoolAllocator_Test.o

$(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_common.QLinearAllocator_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_common/QLinearAllocator_Test.cpp
	$(CXX) $(COMPILEROPTIONS_DEBUGMAC32SHAREDRTDYNAMIC) $(INCLUDES_DEBUGMAC32SHAREDRTDYNAMIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_common/QLinearAllocator_Test.cpp -o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_common.QLinearAllocator_Test.o

$(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_common.QBlockHeader_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_common/QBlockHeader_Test.cpp
	$(CXX) $(COMPILEROPTIONS_DEBUGMAC32SHAREDRTDYNAMIC) $(INCLUDES_DEBUGMAC32SHAREDRTDYNAMIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_common/QBlockHeader_Test.cpp -o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_common.QBlockHeader_Test.o

$(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_common.QMark_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_common/QMark_Test.cpp
	$(CXX) $(COMPILEROPTIONS_DEBUGMAC32SHAREDRTDYNAMIC) $(INCLUDES_DEBUGMAC32SHAREDRTDYNAMIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_common/QMark_Test.cpp -o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_common.QMark_Test.o

$(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_common.QMarkMocked.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_common/QMarkMocked.cpp
	$(CXX) $(COMPILEROPTIONS_DEBUGMAC32SHAREDRTDYNAMIC) $(INCLUDES_DEBUGMAC32SHAREDRTDYNAMIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_common/QMarkMocked.cpp -o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_common.QMarkMocked.o

$(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_common.QStackAllocator_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_common/QStackAllocator_Test.cpp
	$(CXX) $(COMPILEROPTIONS_DEBUGMAC32SHAREDRTDYNAMIC) $(INCLUDES_DEBUGMAC32SHAREDRTDYNAMIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_common/QStackAllocator_Test.cpp -o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_common.QStackAllocator_Test.o

$(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_common.EQEnumeration_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_common/EQEnumeration_Test.cpp
	$(CXX) $(COMPILEROPTIONS_DEBUGMAC32SHAREDRTDYNAMIC) $(INCLUDES_DEBUGMAC32SHAREDRTDYNAMIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_common/EQEnumeration_Test.cpp -o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_common.EQEnumeration_Test.o

$(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTDYNAMIC)__.__.__.testsystem.EQTestType.o: $(EXECUTION_PATH)../../../testsystem/EQTestType.cpp
	$(CXX) $(COMPILEROPTIONS_DEBUGMAC32SHAREDRTDYNAMIC) $(INCLUDES_DEBUGMAC32SHAREDRTDYNAMIC) -c $(EXECUTION_PATH)../../../testsystem/EQTestType.cpp -o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTDYNAMIC)__.__.__.testsystem.EQTestType.o

$(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTDYNAMIC)__.__.__.testsystem.QCommonTestConfig.o: $(EXECUTION_PATH)../../../testsystem/QCommonTestConfig.cpp
	$(CXX) $(COMPILEROPTIONS_DEBUGMAC32SHAREDRTDYNAMIC) $(INCLUDES_DEBUGMAC32SHAREDRTDYNAMIC) -c $(EXECUTION_PATH)../../../testsystem/QCommonTestConfig.cpp -o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTDYNAMIC)__.__.__.testsystem.QCommonTestConfig.o

$(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTDYNAMIC)__.__.__.testsystem.QSimpleConfigLoader.o: $(EXECUTION_PATH)../../../testsystem/QSimpleConfigLoader.cpp
	$(CXX) $(COMPILEROPTIONS_DEBUGMAC32SHAREDRTDYNAMIC) $(INCLUDES_DEBUGMAC32SHAREDRTDYNAMIC) -c $(EXECUTION_PATH)../../../testsystem/QSimpleConfigLoader.cpp -o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTDYNAMIC)__.__.__.testsystem.QSimpleConfigLoader.o

postbuildDebugMac32SharedrtDynamic:
	rm *.dylib


buildDebugMac32SharedrtDynamic: prebuildDebugMac32SharedrtDynamic DebugMac32SharedrtDynamic postbuildDebugMac32SharedrtDynamic

cleanDebugMac32SharedrtDynamic:
	rm -f $(OBJECTS_DEBUGMAC32SHAREDRTDYNAMIC)
	rm -f $(OUTPUT_DEBUGMAC32SHAREDRTDYNAMIC)
	test -d $(EXECUTION_PATH)../../../bin/Clang/DebugMac32SharedrtDynamic rmdir "$(EXECUTION_PATH)..\..\..\bin\Clang\DebugMac32SharedrtDynamic"
	test -d $(EXECUTION_PATH)../../../garbage/Clang/DebugMac32SharedrtDynamic rmdir "$(EXECUTION_PATH)..\..\..\garbage\Clang\DebugMac32SharedrtDynamic"


#------------------------------------------------------------
#------------- DebugMac32SharedrtStatic --------------
#------------------------------------------------------------
INCLUDES_DEBUGMAC32SHAREDRTSTATIC = $(INCLUDES_GLOBAL) -I$(EXECUTION_PATH)../../../../headers -I$(EXECUTION_PATH)../../../tests/unit/testmodule_common -I$(EXECUTION_PATH)../../../tests/unit -I$(EXECUTION_PATH)../../../../3rdparty/ICU/include
LIBRARYDIRS_DEBUGMAC32SHAREDRTSTATIC = $(LIBRARYDIRS_GLOBAL) -L$(EXECUTION_PATH)../../../../3rdparty/Boost/bin/Mac32/DebugSharedrtStatic -L$(EXECUTION_PATH)../../../../bin/Clang/DebugMac32SharedrtStatic
LIBRARIES_DEBUGMAC32SHAREDRTSTATIC = $(LIBRARIES_GLOBAL) -lQuimeraEngineCommon -lboost_unit_test_framework-mt-d -licudata -licuuc -licui18n
COMPILEROPTIONS_DEBUGMAC32SHAREDRTSTATIC = $(COMPILEROPTIONS_GLOBAL) -g -O0 -Wall -Wno-comment -m32 -isystem $(EXECUTION_PATH)../../../../3rdparty/Boost/include
LINKEROPTIONS_DEBUGMAC32SHAREDRTSTATIC = $(LINKEROPTIONS_GLOBAL) -m32
DEFINITIONS_DEBUGMAC32SHAREDRTSTATIC = $(DEFINITIONS_GLOBAL)
OUTPUT_DEBUGMAC32SHAREDRTSTATIC = $(EXECUTION_PATH)../../../bin/Clang/DebugMac32SharedrtStatic/Unit_TestModule_Common
INTERMEDIARYDIR_DEBUGMAC32SHAREDRTSTATIC = $(EXECUTION_PATH)../../../garbage/Clang/DebugMac32SharedrtStatic/
OBJECTS_DEBUGMAC32SHAREDRTSTATIC = $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_common.QDelegate_Test.o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_common.TestModule_Common.o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_common.QReferenceWrapper_Test.o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_common.QCharUnicode_Test.o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_common.QConstCharIterator_Test.o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_common.QStringUnicode_Test.o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_common.QType_Test.o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_common.SQBoolean_Test.o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_common.SQFloat_Test.o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_common.SQInteger_Test.o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_common.SQVF32_Test.o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_common.QCharIterator_Test.o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_common.AllocationOperators_Test.o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_common.QAlignment_Test.o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_common.QPoolAllocator_Test.o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_common.QLinearAllocator_Test.o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_common.QBlockHeader_Test.o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_common.QMark_Test.o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_common.QMarkMocked.o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_common.QStackAllocator_Test.o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_common.EQEnumeration_Test.o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTSTATIC)__.__.__.testsystem.EQTestType.o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTSTATIC)__.__.__.testsystem.QCommonTestConfig.o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTSTATIC)__.__.__.testsystem.QSimpleConfigLoader.o

prebuildDebugMac32SharedrtStatic:
	test -d $(EXECUTION_PATH)../../../bin/Clang/DebugMac32SharedrtStatic mkdir -p "$(EXECUTION_PATH)../../../bin/Clang/DebugMac32SharedrtStatic"
	test -d $(EXECUTION_PATH)../../../garbage/Clang/DebugMac32SharedrtStatic mkdir -p "$(EXECUTION_PATH)../../../garbage/Clang/DebugMac32SharedrtStatic"
	mkdir -p $(EXECUTION_PATH)../../../bin/Clang/DebugMac32SharedrtStatic
	cp "$(EXECUTION_PATH)../../../bin/TestConfig.txt" "$(EXECUTION_PATH)../../../bin/Clang/DebugMac32SharedrtStatic"
	cp "$(EXECUTION_PATH)../../../bin/NormalizationTest.txt" "$(EXECUTION_PATH)../../../bin/Clang/DebugMac32SharedrtStatic"


DebugMac32SharedrtStatic: $(OBJECTS_DEBUGMAC32SHAREDRTSTATIC)
	$(LD) $(LINKEROPTIONS_DEBUGMAC32SHAREDRTSTATIC) $(LIBRARYDIRS_DEBUGMAC32SHAREDRTSTATIC) $(OBJECTS_DEBUGMAC32SHAREDRTSTATIC) $(LIBRARIES_DEBUGMAC32SHAREDRTSTATIC) -o $(OUTPUT_DEBUGMAC32SHAREDRTSTATIC)

$(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_common.QDelegate_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_common/QDelegate_Test.cpp
	$(CXX) $(COMPILEROPTIONS_DEBUGMAC32SHAREDRTSTATIC) $(INCLUDES_DEBUGMAC32SHAREDRTSTATIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_common/QDelegate_Test.cpp -o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_common.QDelegate_Test.o

$(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_common.TestModule_Common.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_common/TestModule_Common.cpp
	$(CXX) $(COMPILEROPTIONS_DEBUGMAC32SHAREDRTSTATIC) $(INCLUDES_DEBUGMAC32SHAREDRTSTATIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_common/TestModule_Common.cpp -o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_common.TestModule_Common.o

$(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_common.QReferenceWrapper_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_common/QReferenceWrapper_Test.cpp
	$(CXX) $(COMPILEROPTIONS_DEBUGMAC32SHAREDRTSTATIC) $(INCLUDES_DEBUGMAC32SHAREDRTSTATIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_common/QReferenceWrapper_Test.cpp -o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_common.QReferenceWrapper_Test.o

$(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_common.QCharUnicode_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_common/QCharUnicode_Test.cpp
	$(CXX) $(COMPILEROPTIONS_DEBUGMAC32SHAREDRTSTATIC) $(INCLUDES_DEBUGMAC32SHAREDRTSTATIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_common/QCharUnicode_Test.cpp -o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_common.QCharUnicode_Test.o

$(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_common.QConstCharIterator_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_common/QConstCharIterator_Test.cpp
	$(CXX) $(COMPILEROPTIONS_DEBUGMAC32SHAREDRTSTATIC) $(INCLUDES_DEBUGMAC32SHAREDRTSTATIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_common/QConstCharIterator_Test.cpp -o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_common.QConstCharIterator_Test.o

$(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_common.QStringUnicode_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_common/QStringUnicode_Test.cpp
	$(CXX) $(COMPILEROPTIONS_DEBUGMAC32SHAREDRTSTATIC) $(INCLUDES_DEBUGMAC32SHAREDRTSTATIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_common/QStringUnicode_Test.cpp -o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_common.QStringUnicode_Test.o

$(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_common.QType_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_common/QType_Test.cpp
	$(CXX) $(COMPILEROPTIONS_DEBUGMAC32SHAREDRTSTATIC) $(INCLUDES_DEBUGMAC32SHAREDRTSTATIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_common/QType_Test.cpp -o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_common.QType_Test.o

$(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_common.SQBoolean_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_common/SQBoolean_Test.cpp
	$(CXX) $(COMPILEROPTIONS_DEBUGMAC32SHAREDRTSTATIC) $(INCLUDES_DEBUGMAC32SHAREDRTSTATIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_common/SQBoolean_Test.cpp -o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_common.SQBoolean_Test.o

$(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_common.SQFloat_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_common/SQFloat_Test.cpp
	$(CXX) $(COMPILEROPTIONS_DEBUGMAC32SHAREDRTSTATIC) $(INCLUDES_DEBUGMAC32SHAREDRTSTATIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_common/SQFloat_Test.cpp -o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_common.SQFloat_Test.o

$(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_common.SQInteger_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_common/SQInteger_Test.cpp
	$(CXX) $(COMPILEROPTIONS_DEBUGMAC32SHAREDRTSTATIC) $(INCLUDES_DEBUGMAC32SHAREDRTSTATIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_common/SQInteger_Test.cpp -o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_common.SQInteger_Test.o

$(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_common.SQVF32_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_common/SQVF32_Test.cpp
	$(CXX) $(COMPILEROPTIONS_DEBUGMAC32SHAREDRTSTATIC) $(INCLUDES_DEBUGMAC32SHAREDRTSTATIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_common/SQVF32_Test.cpp -o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_common.SQVF32_Test.o

$(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_common.QCharIterator_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_common/QCharIterator_Test.cpp
	$(CXX) $(COMPILEROPTIONS_DEBUGMAC32SHAREDRTSTATIC) $(INCLUDES_DEBUGMAC32SHAREDRTSTATIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_common/QCharIterator_Test.cpp -o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_common.QCharIterator_Test.o

$(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_common.AllocationOperators_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_common/AllocationOperators_Test.cpp
	$(CXX) $(COMPILEROPTIONS_DEBUGMAC32SHAREDRTSTATIC) $(INCLUDES_DEBUGMAC32SHAREDRTSTATIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_common/AllocationOperators_Test.cpp -o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_common.AllocationOperators_Test.o

$(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_common.QAlignment_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_common/QAlignment_Test.cpp
	$(CXX) $(COMPILEROPTIONS_DEBUGMAC32SHAREDRTSTATIC) $(INCLUDES_DEBUGMAC32SHAREDRTSTATIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_common/QAlignment_Test.cpp -o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_common.QAlignment_Test.o

$(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_common.QPoolAllocator_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_common/QPoolAllocator_Test.cpp
	$(CXX) $(COMPILEROPTIONS_DEBUGMAC32SHAREDRTSTATIC) $(INCLUDES_DEBUGMAC32SHAREDRTSTATIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_common/QPoolAllocator_Test.cpp -o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_common.QPoolAllocator_Test.o

$(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_common.QLinearAllocator_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_common/QLinearAllocator_Test.cpp
	$(CXX) $(COMPILEROPTIONS_DEBUGMAC32SHAREDRTSTATIC) $(INCLUDES_DEBUGMAC32SHAREDRTSTATIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_common/QLinearAllocator_Test.cpp -o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_common.QLinearAllocator_Test.o

$(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_common.QBlockHeader_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_common/QBlockHeader_Test.cpp
	$(CXX) $(COMPILEROPTIONS_DEBUGMAC32SHAREDRTSTATIC) $(INCLUDES_DEBUGMAC32SHAREDRTSTATIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_common/QBlockHeader_Test.cpp -o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_common.QBlockHeader_Test.o

$(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_common.QMark_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_common/QMark_Test.cpp
	$(CXX) $(COMPILEROPTIONS_DEBUGMAC32SHAREDRTSTATIC) $(INCLUDES_DEBUGMAC32SHAREDRTSTATIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_common/QMark_Test.cpp -o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_common.QMark_Test.o

$(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_common.QMarkMocked.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_common/QMarkMocked.cpp
	$(CXX) $(COMPILEROPTIONS_DEBUGMAC32SHAREDRTSTATIC) $(INCLUDES_DEBUGMAC32SHAREDRTSTATIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_common/QMarkMocked.cpp -o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_common.QMarkMocked.o

$(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_common.QStackAllocator_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_common/QStackAllocator_Test.cpp
	$(CXX) $(COMPILEROPTIONS_DEBUGMAC32SHAREDRTSTATIC) $(INCLUDES_DEBUGMAC32SHAREDRTSTATIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_common/QStackAllocator_Test.cpp -o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_common.QStackAllocator_Test.o

$(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_common.EQEnumeration_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_common/EQEnumeration_Test.cpp
	$(CXX) $(COMPILEROPTIONS_DEBUGMAC32SHAREDRTSTATIC) $(INCLUDES_DEBUGMAC32SHAREDRTSTATIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_common/EQEnumeration_Test.cpp -o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_common.EQEnumeration_Test.o

$(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTSTATIC)__.__.__.testsystem.EQTestType.o: $(EXECUTION_PATH)../../../testsystem/EQTestType.cpp
	$(CXX) $(COMPILEROPTIONS_DEBUGMAC32SHAREDRTSTATIC) $(INCLUDES_DEBUGMAC32SHAREDRTSTATIC) -c $(EXECUTION_PATH)../../../testsystem/EQTestType.cpp -o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTSTATIC)__.__.__.testsystem.EQTestType.o

$(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTSTATIC)__.__.__.testsystem.QCommonTestConfig.o: $(EXECUTION_PATH)../../../testsystem/QCommonTestConfig.cpp
	$(CXX) $(COMPILEROPTIONS_DEBUGMAC32SHAREDRTSTATIC) $(INCLUDES_DEBUGMAC32SHAREDRTSTATIC) -c $(EXECUTION_PATH)../../../testsystem/QCommonTestConfig.cpp -o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTSTATIC)__.__.__.testsystem.QCommonTestConfig.o

$(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTSTATIC)__.__.__.testsystem.QSimpleConfigLoader.o: $(EXECUTION_PATH)../../../testsystem/QSimpleConfigLoader.cpp
	$(CXX) $(COMPILEROPTIONS_DEBUGMAC32SHAREDRTSTATIC) $(INCLUDES_DEBUGMAC32SHAREDRTSTATIC) -c $(EXECUTION_PATH)../../../testsystem/QSimpleConfigLoader.cpp -o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTSTATIC)__.__.__.testsystem.QSimpleConfigLoader.o

postbuildDebugMac32SharedrtStatic:
	


buildDebugMac32SharedrtStatic: prebuildDebugMac32SharedrtStatic DebugMac32SharedrtStatic postbuildDebugMac32SharedrtStatic

cleanDebugMac32SharedrtStatic:
	rm -f $(OBJECTS_DEBUGMAC32SHAREDRTSTATIC)
	rm -f $(OUTPUT_DEBUGMAC32SHAREDRTSTATIC)
	test -d $(EXECUTION_PATH)../../../bin/Clang/DebugMac32SharedrtStatic rmdir "$(EXECUTION_PATH)..\..\..\bin\Clang\DebugMac32SharedrtStatic"
	test -d $(EXECUTION_PATH)../../../garbage/Clang/DebugMac32SharedrtStatic rmdir "$(EXECUTION_PATH)..\..\..\garbage\Clang\DebugMac32SharedrtStatic"


#------------------------------------------------------------
#------------- DebugWin32SharedrtDynamic --------------
#------------------------------------------------------------
INCLUDES_DEBUGWIN32SHAREDRTDYNAMIC = $(INCLUDES_GLOBAL) -I$(EXECUTION_PATH)../../../../headers -I$(EXECUTION_PATH)../../../tests/unit/testmodule_common -I$(EXECUTION_PATH)../../../tests/unit -I$(EXECUTION_PATH)../../../../3rdparty/ICU/include
LIBRARYDIRS_DEBUGWIN32SHAREDRTDYNAMIC = $(LIBRARYDIRS_GLOBAL) -L$(EXECUTION_PATH)../../../../3rdparty/Boost/bin/Win32/DebugSharedrtStatic -L$(EXECUTION_PATH)../../../../3rdparty/ICU/bin/Win32/ReleaseSharedrtDynamic/MinGW -L$(EXECUTION_PATH)../../../../bin/MinGW/DebugWin32SharedrtDynamic
LIBRARIES_DEBUGWIN32SHAREDRTDYNAMIC = $(LIBRARIES_GLOBAL) -lQuimeraEngineCommon -lboost_unit_test_framework-mt-d -licudt -licuuc -licuin
COMPILEROPTIONS_DEBUGWIN32SHAREDRTDYNAMIC = $(COMPILEROPTIONS_GLOBAL) -g -O0 -Wall -Wno-comment -Wno-unused-local-typedefs -m32 -isystem $(EXECUTION_PATH)../../../../3rdparty/Boost/include
LINKEROPTIONS_DEBUGWIN32SHAREDRTDYNAMIC = $(LINKEROPTIONS_GLOBAL) -m32
DEFINITIONS_DEBUGWIN32SHAREDRTDYNAMIC = $(DEFINITIONS_GLOBAL) -DQE_PREPROCESSOR_IMPORTLIB_QUIMERAENGINE
OUTPUT_DEBUGWIN32SHAREDRTDYNAMIC = $(EXECUTION_PATH)../../../bin/MinGW/DebugWin32SharedrtDynamic/Unit_TestModule_Common.exe
INTERMEDIARYDIR_DEBUGWIN32SHAREDRTDYNAMIC = $(EXECUTION_PATH)../../../garbage/MinGW/DebugWin32SharedrtDynamic/
OBJECTS_DEBUGWIN32SHAREDRTDYNAMIC = $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_common.QDelegate_Test.o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_common.TestModule_Common.o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_common.QReferenceWrapper_Test.o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_common.QCharUnicode_Test.o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_common.QConstCharIterator_Test.o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_common.QStringUnicode_Test.o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_common.QType_Test.o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_common.SQBoolean_Test.o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_common.SQFloat_Test.o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_common.SQInteger_Test.o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_common.SQVF32_Test.o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_common.QCharIterator_Test.o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_common.AllocationOperators_Test.o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_common.QAlignment_Test.o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_common.QPoolAllocator_Test.o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_common.QLinearAllocator_Test.o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_common.QBlockHeader_Test.o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_common.QMark_Test.o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_common.QMarkMocked.o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_common.QStackAllocator_Test.o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_common.EQEnumeration_Test.o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTDYNAMIC)__.__.__.testsystem.EQTestType.o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTDYNAMIC)__.__.__.testsystem.QCommonTestConfig.o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTDYNAMIC)__.__.__.testsystem.QSimpleConfigLoader.o

prebuildDebugWin32SharedrtDynamic:
	cmd /c if not exist $(EXECUTION_PATH)..\..\..\bin\MinGW\DebugWin32SharedrtDynamic mkdir "$(EXECUTION_PATH)..\..\..\bin\MinGW\DebugWin32SharedrtDynamic"
	cmd /c if not exist $(EXECUTION_PATH)..\..\..\garbage\MinGW\DebugWin32SharedrtDynamic mkdir "$(EXECUTION_PATH)..\..\..\garbage\MinGW\DebugWin32SharedrtDynamic"


DebugWin32SharedrtDynamic: $(OBJECTS_DEBUGWIN32SHAREDRTDYNAMIC)
	$(LD) $(LINKEROPTIONS_DEBUGWIN32SHAREDRTDYNAMIC) $(LIBRARYDIRS_DEBUGWIN32SHAREDRTDYNAMIC) $(OBJECTS_DEBUGWIN32SHAREDRTDYNAMIC) $(LIBRARIES_DEBUGWIN32SHAREDRTDYNAMIC) -o $(OUTPUT_DEBUGWIN32SHAREDRTDYNAMIC)

$(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_common.QDelegate_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_common/QDelegate_Test.cpp
	$(CXX) $(COMPILEROPTIONS_DEBUGWIN32SHAREDRTDYNAMIC) $(INCLUDES_DEBUGWIN32SHAREDRTDYNAMIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_common/QDelegate_Test.cpp -o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_common.QDelegate_Test.o

$(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_common.TestModule_Common.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_common/TestModule_Common.cpp
	$(CXX) $(COMPILEROPTIONS_DEBUGWIN32SHAREDRTDYNAMIC) $(INCLUDES_DEBUGWIN32SHAREDRTDYNAMIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_common/TestModule_Common.cpp -o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_common.TestModule_Common.o

$(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_common.QReferenceWrapper_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_common/QReferenceWrapper_Test.cpp
	$(CXX) $(COMPILEROPTIONS_DEBUGWIN32SHAREDRTDYNAMIC) $(INCLUDES_DEBUGWIN32SHAREDRTDYNAMIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_common/QReferenceWrapper_Test.cpp -o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_common.QReferenceWrapper_Test.o

$(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_common.QCharUnicode_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_common/QCharUnicode_Test.cpp
	$(CXX) $(COMPILEROPTIONS_DEBUGWIN32SHAREDRTDYNAMIC) $(INCLUDES_DEBUGWIN32SHAREDRTDYNAMIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_common/QCharUnicode_Test.cpp -o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_common.QCharUnicode_Test.o

$(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_common.QConstCharIterator_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_common/QConstCharIterator_Test.cpp
	$(CXX) $(COMPILEROPTIONS_DEBUGWIN32SHAREDRTDYNAMIC) $(INCLUDES_DEBUGWIN32SHAREDRTDYNAMIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_common/QConstCharIterator_Test.cpp -o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_common.QConstCharIterator_Test.o

$(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_common.QStringUnicode_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_common/QStringUnicode_Test.cpp
	$(CXX) $(COMPILEROPTIONS_DEBUGWIN32SHAREDRTDYNAMIC) $(INCLUDES_DEBUGWIN32SHAREDRTDYNAMIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_common/QStringUnicode_Test.cpp -o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_common.QStringUnicode_Test.o

$(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_common.QType_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_common/QType_Test.cpp
	$(CXX) $(COMPILEROPTIONS_DEBUGWIN32SHAREDRTDYNAMIC) $(INCLUDES_DEBUGWIN32SHAREDRTDYNAMIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_common/QType_Test.cpp -o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_common.QType_Test.o

$(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_common.SQBoolean_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_common/SQBoolean_Test.cpp
	$(CXX) $(COMPILEROPTIONS_DEBUGWIN32SHAREDRTDYNAMIC) $(INCLUDES_DEBUGWIN32SHAREDRTDYNAMIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_common/SQBoolean_Test.cpp -o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_common.SQBoolean_Test.o

$(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_common.SQFloat_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_common/SQFloat_Test.cpp
	$(CXX) $(COMPILEROPTIONS_DEBUGWIN32SHAREDRTDYNAMIC) $(INCLUDES_DEBUGWIN32SHAREDRTDYNAMIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_common/SQFloat_Test.cpp -o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_common.SQFloat_Test.o

$(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_common.SQInteger_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_common/SQInteger_Test.cpp
	$(CXX) $(COMPILEROPTIONS_DEBUGWIN32SHAREDRTDYNAMIC) $(INCLUDES_DEBUGWIN32SHAREDRTDYNAMIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_common/SQInteger_Test.cpp -o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_common.SQInteger_Test.o

$(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_common.SQVF32_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_common/SQVF32_Test.cpp
	$(CXX) $(COMPILEROPTIONS_DEBUGWIN32SHAREDRTDYNAMIC) $(INCLUDES_DEBUGWIN32SHAREDRTDYNAMIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_common/SQVF32_Test.cpp -o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_common.SQVF32_Test.o

$(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_common.QCharIterator_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_common/QCharIterator_Test.cpp
	$(CXX) $(COMPILEROPTIONS_DEBUGWIN32SHAREDRTDYNAMIC) $(INCLUDES_DEBUGWIN32SHAREDRTDYNAMIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_common/QCharIterator_Test.cpp -o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_common.QCharIterator_Test.o

$(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_common.AllocationOperators_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_common/AllocationOperators_Test.cpp
	$(CXX) $(COMPILEROPTIONS_DEBUGWIN32SHAREDRTDYNAMIC) $(INCLUDES_DEBUGWIN32SHAREDRTDYNAMIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_common/AllocationOperators_Test.cpp -o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_common.AllocationOperators_Test.o

$(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_common.QAlignment_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_common/QAlignment_Test.cpp
	$(CXX) $(COMPILEROPTIONS_DEBUGWIN32SHAREDRTDYNAMIC) $(INCLUDES_DEBUGWIN32SHAREDRTDYNAMIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_common/QAlignment_Test.cpp -o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_common.QAlignment_Test.o

$(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_common.QPoolAllocator_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_common/QPoolAllocator_Test.cpp
	$(CXX) $(COMPILEROPTIONS_DEBUGWIN32SHAREDRTDYNAMIC) $(INCLUDES_DEBUGWIN32SHAREDRTDYNAMIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_common/QPoolAllocator_Test.cpp -o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_common.QPoolAllocator_Test.o

$(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_common.QLinearAllocator_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_common/QLinearAllocator_Test.cpp
	$(CXX) $(COMPILEROPTIONS_DEBUGWIN32SHAREDRTDYNAMIC) $(INCLUDES_DEBUGWIN32SHAREDRTDYNAMIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_common/QLinearAllocator_Test.cpp -o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_common.QLinearAllocator_Test.o

$(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_common.QBlockHeader_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_common/QBlockHeader_Test.cpp
	$(CXX) $(COMPILEROPTIONS_DEBUGWIN32SHAREDRTDYNAMIC) $(INCLUDES_DEBUGWIN32SHAREDRTDYNAMIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_common/QBlockHeader_Test.cpp -o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_common.QBlockHeader_Test.o

$(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_common.QMark_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_common/QMark_Test.cpp
	$(CXX) $(COMPILEROPTIONS_DEBUGWIN32SHAREDRTDYNAMIC) $(INCLUDES_DEBUGWIN32SHAREDRTDYNAMIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_common/QMark_Test.cpp -o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_common.QMark_Test.o

$(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_common.QMarkMocked.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_common/QMarkMocked.cpp
	$(CXX) $(COMPILEROPTIONS_DEBUGWIN32SHAREDRTDYNAMIC) $(INCLUDES_DEBUGWIN32SHAREDRTDYNAMIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_common/QMarkMocked.cpp -o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_common.QMarkMocked.o

$(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_common.QStackAllocator_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_common/QStackAllocator_Test.cpp
	$(CXX) $(COMPILEROPTIONS_DEBUGWIN32SHAREDRTDYNAMIC) $(INCLUDES_DEBUGWIN32SHAREDRTDYNAMIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_common/QStackAllocator_Test.cpp -o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_common.QStackAllocator_Test.o

$(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_common.EQEnumeration_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_common/EQEnumeration_Test.cpp
	$(CXX) $(COMPILEROPTIONS_DEBUGWIN32SHAREDRTDYNAMIC) $(INCLUDES_DEBUGWIN32SHAREDRTDYNAMIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_common/EQEnumeration_Test.cpp -o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_common.EQEnumeration_Test.o

$(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTDYNAMIC)__.__.__.testsystem.EQTestType.o: $(EXECUTION_PATH)../../../testsystem/EQTestType.cpp
	$(CXX) $(COMPILEROPTIONS_DEBUGWIN32SHAREDRTDYNAMIC) $(INCLUDES_DEBUGWIN32SHAREDRTDYNAMIC) -c $(EXECUTION_PATH)../../../testsystem/EQTestType.cpp -o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTDYNAMIC)__.__.__.testsystem.EQTestType.o

$(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTDYNAMIC)__.__.__.testsystem.QCommonTestConfig.o: $(EXECUTION_PATH)../../../testsystem/QCommonTestConfig.cpp
	$(CXX) $(COMPILEROPTIONS_DEBUGWIN32SHAREDRTDYNAMIC) $(INCLUDES_DEBUGWIN32SHAREDRTDYNAMIC) -c $(EXECUTION_PATH)../../../testsystem/QCommonTestConfig.cpp -o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTDYNAMIC)__.__.__.testsystem.QCommonTestConfig.o

$(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTDYNAMIC)__.__.__.testsystem.QSimpleConfigLoader.o: $(EXECUTION_PATH)../../../testsystem/QSimpleConfigLoader.cpp
	$(CXX) $(COMPILEROPTIONS_DEBUGWIN32SHAREDRTDYNAMIC) $(INCLUDES_DEBUGWIN32SHAREDRTDYNAMIC) -c $(EXECUTION_PATH)../../../testsystem/QSimpleConfigLoader.cpp -o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTDYNAMIC)__.__.__.testsystem.QSimpleConfigLoader.o

postbuildDebugWin32SharedrtDynamic:
	cmd /c copy "$(EXECUTION_PATH)..\..\..\bin\TestConfig.txt" "$(EXECUTION_PATH)..\..\..\bin\MinGW\DebugWin32SharedrtDynamic" /Y
	cmd /c copy "$(EXECUTION_PATH)..\..\..\bin\NormalizationTest.txt" "$(EXECUTION_PATH)..\..\..\bin\MinGW\DebugWin32SharedrtDynamic" /Y
	cmd /c copy "$(EXECUTION_PATH)..\..\..\..\3rdparty\ICU\bin\Win32\ReleaseSharedrtDynamic\MinGW\*.dll" "$(EXECUTION_PATH)..\..\..\bin\MinGW\DebugWin32SharedrtDynamic" /Y
	cmd /c copy "$(EXECUTION_PATH)..\..\..\..\bin\MinGW\DebugWin32SharedrtDynamic\QuimeraEngineCommon.dll" "$(EXECUTION_PATH)..\..\..\bin\MinGW\DebugWin32SharedrtDynamic" /Y


buildDebugWin32SharedrtDynamic: prebuildDebugWin32SharedrtDynamic DebugWin32SharedrtDynamic postbuildDebugWin32SharedrtDynamic

cleanDebugWin32SharedrtDynamic:
	rm -f $(OBJECTS_DEBUGWIN32SHAREDRTDYNAMIC)
	rm -f $(OUTPUT_DEBUGWIN32SHAREDRTDYNAMIC)
	cmd /c if exist $(EXECUTION_PATH)..\..\..\bin\MinGW\DebugWin32SharedrtDynamic rmdir "$(EXECUTION_PATH)..\..\..\bin\MinGW\DebugWin32SharedrtDynamic" /s /q
	cmd /c if exist $(EXECUTION_PATH)..\..\..\garbage\MinGW\DebugWin32SharedrtDynamic rmdir "$(EXECUTION_PATH)..\..\..\garbage\MinGW\DebugWin32SharedrtDynamic" /s /q


#------------------------------------------------------------
#------------- DebugWin32SharedrtStatic --------------
#------------------------------------------------------------
INCLUDES_DEBUGWIN32SHAREDRTSTATIC = $(INCLUDES_GLOBAL) -I$(EXECUTION_PATH)../../../../headers -I$(EXECUTION_PATH)../../../tests/unit/testmodule_common -I$(EXECUTION_PATH)../../../tests/unit -I$(EXECUTION_PATH)../../../../3rdparty/ICU/include
LIBRARYDIRS_DEBUGWIN32SHAREDRTSTATIC = $(LIBRARYDIRS_GLOBAL) -L$(EXECUTION_PATH)../../../../3rdparty/Boost/bin/Win32/DebugSharedrtStatic -L$(EXECUTION_PATH)../../../../3rdparty/ICU/bin/Win32/ReleaseSharedrtDynamic/MinGW -L$(EXECUTION_PATH)../../../../bin/MinGW/DebugWin32SharedrtStatic
LIBRARIES_DEBUGWIN32SHAREDRTSTATIC = $(LIBRARIES_GLOBAL) -lQuimeraEngineCommon -lboost_unit_test_framework-mt-d -licudt -licuuc -licuin
COMPILEROPTIONS_DEBUGWIN32SHAREDRTSTATIC = $(COMPILEROPTIONS_GLOBAL) -g -O0 -Wall -Wno-comment -Wno-unused-local-typedefs -m32 -isystem $(EXECUTION_PATH)../../../../3rdparty/Boost/include
LINKEROPTIONS_DEBUGWIN32SHAREDRTSTATIC = $(LINKEROPTIONS_GLOBAL) -m32
DEFINITIONS_DEBUGWIN32SHAREDRTSTATIC = $(DEFINITIONS_GLOBAL)
OUTPUT_DEBUGWIN32SHAREDRTSTATIC = $(EXECUTION_PATH)../../../bin/MinGW/DebugWin32SharedrtStatic/Unit_TestModule_Common.exe
INTERMEDIARYDIR_DEBUGWIN32SHAREDRTSTATIC = $(EXECUTION_PATH)../../../garbage/MinGW/DebugWin32SharedrtStatic/
OBJECTS_DEBUGWIN32SHAREDRTSTATIC = $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_common.QDelegate_Test.o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_common.TestModule_Common.o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_common.QReferenceWrapper_Test.o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_common.QCharUnicode_Test.o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_common.QConstCharIterator_Test.o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_common.QStringUnicode_Test.o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_common.QType_Test.o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_common.SQBoolean_Test.o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_common.SQFloat_Test.o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_common.SQInteger_Test.o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_common.SQVF32_Test.o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_common.QCharIterator_Test.o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_common.AllocationOperators_Test.o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_common.QAlignment_Test.o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_common.QPoolAllocator_Test.o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_common.QLinearAllocator_Test.o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_common.QBlockHeader_Test.o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_common.QMark_Test.o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_common.QMarkMocked.o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_common.QStackAllocator_Test.o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_common.EQEnumeration_Test.o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTSTATIC)__.__.__.testsystem.EQTestType.o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTSTATIC)__.__.__.testsystem.QCommonTestConfig.o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTSTATIC)__.__.__.testsystem.QSimpleConfigLoader.o

prebuildDebugWin32SharedrtStatic:
	cmd /c if not exist $(EXECUTION_PATH)..\..\..\bin\MinGW\DebugWin32SharedrtStatic mkdir "$(EXECUTION_PATH)..\..\..\bin\MinGW\DebugWin32SharedrtStatic"
	cmd /c if not exist $(EXECUTION_PATH)..\..\..\garbage\MinGW\DebugWin32SharedrtStatic mkdir "$(EXECUTION_PATH)..\..\..\garbage\MinGW\DebugWin32SharedrtStatic"


DebugWin32SharedrtStatic: $(OBJECTS_DEBUGWIN32SHAREDRTSTATIC)
	$(LD) $(LINKEROPTIONS_DEBUGWIN32SHAREDRTSTATIC) $(LIBRARYDIRS_DEBUGWIN32SHAREDRTSTATIC) $(OBJECTS_DEBUGWIN32SHAREDRTSTATIC) $(LIBRARIES_DEBUGWIN32SHAREDRTSTATIC) -o $(OUTPUT_DEBUGWIN32SHAREDRTSTATIC)

$(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_common.QDelegate_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_common/QDelegate_Test.cpp
	$(CXX) $(COMPILEROPTIONS_DEBUGWIN32SHAREDRTSTATIC) $(INCLUDES_DEBUGWIN32SHAREDRTSTATIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_common/QDelegate_Test.cpp -o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_common.QDelegate_Test.o

$(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_common.TestModule_Common.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_common/TestModule_Common.cpp
	$(CXX) $(COMPILEROPTIONS_DEBUGWIN32SHAREDRTSTATIC) $(INCLUDES_DEBUGWIN32SHAREDRTSTATIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_common/TestModule_Common.cpp -o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_common.TestModule_Common.o

$(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_common.QReferenceWrapper_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_common/QReferenceWrapper_Test.cpp
	$(CXX) $(COMPILEROPTIONS_DEBUGWIN32SHAREDRTSTATIC) $(INCLUDES_DEBUGWIN32SHAREDRTSTATIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_common/QReferenceWrapper_Test.cpp -o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_common.QReferenceWrapper_Test.o

$(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_common.QCharUnicode_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_common/QCharUnicode_Test.cpp
	$(CXX) $(COMPILEROPTIONS_DEBUGWIN32SHAREDRTSTATIC) $(INCLUDES_DEBUGWIN32SHAREDRTSTATIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_common/QCharUnicode_Test.cpp -o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_common.QCharUnicode_Test.o

$(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_common.QConstCharIterator_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_common/QConstCharIterator_Test.cpp
	$(CXX) $(COMPILEROPTIONS_DEBUGWIN32SHAREDRTSTATIC) $(INCLUDES_DEBUGWIN32SHAREDRTSTATIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_common/QConstCharIterator_Test.cpp -o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_common.QConstCharIterator_Test.o

$(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_common.QStringUnicode_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_common/QStringUnicode_Test.cpp
	$(CXX) $(COMPILEROPTIONS_DEBUGWIN32SHAREDRTSTATIC) $(INCLUDES_DEBUGWIN32SHAREDRTSTATIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_common/QStringUnicode_Test.cpp -o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_common.QStringUnicode_Test.o

$(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_common.QType_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_common/QType_Test.cpp
	$(CXX) $(COMPILEROPTIONS_DEBUGWIN32SHAREDRTSTATIC) $(INCLUDES_DEBUGWIN32SHAREDRTSTATIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_common/QType_Test.cpp -o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_common.QType_Test.o

$(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_common.SQBoolean_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_common/SQBoolean_Test.cpp
	$(CXX) $(COMPILEROPTIONS_DEBUGWIN32SHAREDRTSTATIC) $(INCLUDES_DEBUGWIN32SHAREDRTSTATIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_common/SQBoolean_Test.cpp -o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_common.SQBoolean_Test.o

$(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_common.SQFloat_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_common/SQFloat_Test.cpp
	$(CXX) $(COMPILEROPTIONS_DEBUGWIN32SHAREDRTSTATIC) $(INCLUDES_DEBUGWIN32SHAREDRTSTATIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_common/SQFloat_Test.cpp -o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_common.SQFloat_Test.o

$(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_common.SQInteger_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_common/SQInteger_Test.cpp
	$(CXX) $(COMPILEROPTIONS_DEBUGWIN32SHAREDRTSTATIC) $(INCLUDES_DEBUGWIN32SHAREDRTSTATIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_common/SQInteger_Test.cpp -o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_common.SQInteger_Test.o

$(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_common.SQVF32_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_common/SQVF32_Test.cpp
	$(CXX) $(COMPILEROPTIONS_DEBUGWIN32SHAREDRTSTATIC) $(INCLUDES_DEBUGWIN32SHAREDRTSTATIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_common/SQVF32_Test.cpp -o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_common.SQVF32_Test.o

$(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_common.QCharIterator_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_common/QCharIterator_Test.cpp
	$(CXX) $(COMPILEROPTIONS_DEBUGWIN32SHAREDRTSTATIC) $(INCLUDES_DEBUGWIN32SHAREDRTSTATIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_common/QCharIterator_Test.cpp -o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_common.QCharIterator_Test.o

$(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_common.AllocationOperators_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_common/AllocationOperators_Test.cpp
	$(CXX) $(COMPILEROPTIONS_DEBUGWIN32SHAREDRTSTATIC) $(INCLUDES_DEBUGWIN32SHAREDRTSTATIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_common/AllocationOperators_Test.cpp -o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_common.AllocationOperators_Test.o

$(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_common.QAlignment_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_common/QAlignment_Test.cpp
	$(CXX) $(COMPILEROPTIONS_DEBUGWIN32SHAREDRTSTATIC) $(INCLUDES_DEBUGWIN32SHAREDRTSTATIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_common/QAlignment_Test.cpp -o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_common.QAlignment_Test.o

$(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_common.QPoolAllocator_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_common/QPoolAllocator_Test.cpp
	$(CXX) $(COMPILEROPTIONS_DEBUGWIN32SHAREDRTSTATIC) $(INCLUDES_DEBUGWIN32SHAREDRTSTATIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_common/QPoolAllocator_Test.cpp -o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_common.QPoolAllocator_Test.o

$(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_common.QLinearAllocator_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_common/QLinearAllocator_Test.cpp
	$(CXX) $(COMPILEROPTIONS_DEBUGWIN32SHAREDRTSTATIC) $(INCLUDES_DEBUGWIN32SHAREDRTSTATIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_common/QLinearAllocator_Test.cpp -o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_common.QLinearAllocator_Test.o

$(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_common.QBlockHeader_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_common/QBlockHeader_Test.cpp
	$(CXX) $(COMPILEROPTIONS_DEBUGWIN32SHAREDRTSTATIC) $(INCLUDES_DEBUGWIN32SHAREDRTSTATIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_common/QBlockHeader_Test.cpp -o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_common.QBlockHeader_Test.o

$(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_common.QMark_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_common/QMark_Test.cpp
	$(CXX) $(COMPILEROPTIONS_DEBUGWIN32SHAREDRTSTATIC) $(INCLUDES_DEBUGWIN32SHAREDRTSTATIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_common/QMark_Test.cpp -o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_common.QMark_Test.o

$(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_common.QMarkMocked.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_common/QMarkMocked.cpp
	$(CXX) $(COMPILEROPTIONS_DEBUGWIN32SHAREDRTSTATIC) $(INCLUDES_DEBUGWIN32SHAREDRTSTATIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_common/QMarkMocked.cpp -o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_common.QMarkMocked.o

$(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_common.QStackAllocator_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_common/QStackAllocator_Test.cpp
	$(CXX) $(COMPILEROPTIONS_DEBUGWIN32SHAREDRTSTATIC) $(INCLUDES_DEBUGWIN32SHAREDRTSTATIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_common/QStackAllocator_Test.cpp -o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_common.QStackAllocator_Test.o

$(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_common.EQEnumeration_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_common/EQEnumeration_Test.cpp
	$(CXX) $(COMPILEROPTIONS_DEBUGWIN32SHAREDRTSTATIC) $(INCLUDES_DEBUGWIN32SHAREDRTSTATIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_common/EQEnumeration_Test.cpp -o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_common.EQEnumeration_Test.o

$(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTSTATIC)__.__.__.testsystem.EQTestType.o: $(EXECUTION_PATH)../../../testsystem/EQTestType.cpp
	$(CXX) $(COMPILEROPTIONS_DEBUGWIN32SHAREDRTSTATIC) $(INCLUDES_DEBUGWIN32SHAREDRTSTATIC) -c $(EXECUTION_PATH)../../../testsystem/EQTestType.cpp -o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTSTATIC)__.__.__.testsystem.EQTestType.o

$(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTSTATIC)__.__.__.testsystem.QCommonTestConfig.o: $(EXECUTION_PATH)../../../testsystem/QCommonTestConfig.cpp
	$(CXX) $(COMPILEROPTIONS_DEBUGWIN32SHAREDRTSTATIC) $(INCLUDES_DEBUGWIN32SHAREDRTSTATIC) -c $(EXECUTION_PATH)../../../testsystem/QCommonTestConfig.cpp -o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTSTATIC)__.__.__.testsystem.QCommonTestConfig.o

$(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTSTATIC)__.__.__.testsystem.QSimpleConfigLoader.o: $(EXECUTION_PATH)../../../testsystem/QSimpleConfigLoader.cpp
	$(CXX) $(COMPILEROPTIONS_DEBUGWIN32SHAREDRTSTATIC) $(INCLUDES_DEBUGWIN32SHAREDRTSTATIC) -c $(EXECUTION_PATH)../../../testsystem/QSimpleConfigLoader.cpp -o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTSTATIC)__.__.__.testsystem.QSimpleConfigLoader.o

postbuildDebugWin32SharedrtStatic:
	cmd /c copy "$(EXECUTION_PATH)..\..\..\bin\TestConfig.txt" "$(EXECUTION_PATH)..\..\..\bin\MinGW\DebugWin32SharedrtStatic" /Y
	cmd /c copy "$(EXECUTION_PATH)..\..\..\bin\NormalizationTest.txt" "$(EXECUTION_PATH)..\..\..\bin\MinGW\DebugWin32SharedrtStatic" /Y
	cmd /c copy "$(EXECUTION_PATH)..\..\..\..\3rdparty\ICU\bin\Win32\ReleaseSharedrtDynamic\MinGW\*.dll" "$(EXECUTION_PATH)..\..\..\bin\MinGW\DebugWin32SharedrtStatic" /Y


buildDebugWin32SharedrtStatic: prebuildDebugWin32SharedrtStatic DebugWin32SharedrtStatic postbuildDebugWin32SharedrtStatic

cleanDebugWin32SharedrtStatic:
	rm -f $(OBJECTS_DEBUGWIN32SHAREDRTSTATIC)
	rm -f $(OUTPUT_DEBUGWIN32SHAREDRTSTATIC)
	cmd /c if exist $(EXECUTION_PATH)..\..\..\bin\MinGW\DebugWin32SharedrtStatic rmdir "$(EXECUTION_PATH)..\..\..\bin\MinGW\DebugWin32SharedrtStatic" /s /q
	cmd /c if exist $(EXECUTION_PATH)..\..\..\garbage\MinGW\DebugWin32SharedrtStatic rmdir "$(EXECUTION_PATH)..\..\..\garbage\MinGW\DebugWin32SharedrtStatic" /s /q



.PHONY:buildDebugLinux32SharedrtDynamic prebuildDebugLinux32SharedrtDynamic DebugLinux32SharedrtDynamic postbuildDebugLinux32SharedrtDynamic cleanDebugLinux32SharedrtDynamic buildDebugLinux32SharedrtStatic prebuildDebugLinux32SharedrtStatic DebugLinux32SharedrtStatic postbuildDebugLinux32SharedrtStatic cleanDebugLinux32SharedrtStatic buildDebugMac32SharedrtDynamic prebuildDebugMac32SharedrtDynamic DebugMac32SharedrtDynamic postbuildDebugMac32SharedrtDynamic cleanDebugMac32SharedrtDynamic buildDebugMac32SharedrtStatic prebuildDebugMac32SharedrtStatic DebugMac32SharedrtStatic postbuildDebugMac32SharedrtStatic cleanDebugMac32SharedrtStatic buildDebugWin32SharedrtDynamic prebuildDebugWin32SharedrtDynamic DebugWin32SharedrtDynamic postbuildDebugWin32SharedrtDynamic cleanDebugWin32SharedrtDynamic buildDebugWin32SharedrtStatic prebuildDebugWin32SharedrtStatic DebugWin32SharedrtStatic postbuildDebugWin32SharedrtStatic cleanDebugWin32SharedrtStatic 