#------------------------------------------------------------------------------------------------------------#
#------------------------------------System------------------------------------#
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
INCLUDES_DEBUGLINUX32SHAREDRTDYNAMIC = $(INCLUDES_GLOBAL) -I$(EXECUTION_PATH)../../../../headers -I$(EXECUTION_PATH)../../../tests/unit/testmodule_system -I$(EXECUTION_PATH)../../../tests/unit -I$(EXECUTION_PATH)../../../../3rdparty/ICU/include
LIBRARYDIRS_DEBUGLINUX32SHAREDRTDYNAMIC = $(LIBRARYDIRS_GLOBAL) -L$(EXECUTION_PATH)../../../../3rdparty/Boost/bin/Linux32/DebugSharedrtStatic -L$(EXECUTION_PATH)../../../../bin/GCC/DebugLinux32SharedrtDynamic
LIBRARIES_DEBUGLINUX32SHAREDRTDYNAMIC = $(LIBRARIES_GLOBAL) -lQuimeraEngineSystem -lQuimeraEngineTools -lQuimeraEngineCommon -lboost_thread-mt-d -lboost_system-mt-d -lboost_filesystem-mt-d -lboost_unit_test_framework-mt-d -licudata -licuuc -licui18n
COMPILEROPTIONS_DEBUGLINUX32SHAREDRTDYNAMIC = $(COMPILEROPTIONS_GLOBAL) -g -O0 -Wall -Wno-comment -Wno-unused-local-typedefs -m32 -isystem $(EXECUTION_PATH)../../../../3rdparty/Boost/include
LINKEROPTIONS_DEBUGLINUX32SHAREDRTDYNAMIC = $(LINKEROPTIONS_GLOBAL) -m32
DEFINITIONS_DEBUGLINUX32SHAREDRTDYNAMIC = $(DEFINITIONS_GLOBAL) -DQE_PREPROCESSOR_IMPORTLIB_QUIMERAENGINE
OUTPUT_DEBUGLINUX32SHAREDRTDYNAMIC = $(EXECUTION_PATH)../../../bin/GCC/DebugLinux32SharedrtDynamic/Unit_TestModule_System.sh
INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTDYNAMIC = $(EXECUTION_PATH)../../../garbage/GCC/DebugLinux32SharedrtDynamic/
OBJECTS_DEBUGLINUX32SHAREDRTDYNAMIC = $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_system.TestModule_System.o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_system.QObject_Test.o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_system.QLocalTimeZone_Test.o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_system.QDateTimeNow_Test.o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_system.QStopwatch_Test.o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_system.QMemoryStream_Test.o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_system.QUri_Test.o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_system.QBinaryStreamReader_Test.o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_system.QBinaryStreamWriter_Test.o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_system.QTextStreamReader_Test.o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_system.QPath_Test.o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_system.SQDirectory_Test.o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_system.SQFile_Test.o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_system.QFileStream_Test.o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_system.QDerivedFromObject.o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_system.SQAnyTypeToStringConverter_Test.o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_system.SQTypeExtensions_Test.o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_system.QArgumentTrace_Test.o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_system.QCallTrace_Test.o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_system.QCallStackTrace_Test.o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_system.QThread_Test.o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_system.SQThisThread_Test.o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTDYNAMIC)__.__.__.testsystem.EQTestType.o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTDYNAMIC)__.__.__.testsystem.QCommonTestConfig.o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTDYNAMIC)__.__.__.testsystem.QSimpleConfigLoader.o

prebuildDebugLinux32SharedrtDynamic:
	test -d $(EXECUTION_PATH)../../../bin/GCC/DebugLinux32SharedrtDynamic mkdir -p "$(EXECUTION_PATH)../../../bin/GCC/DebugLinux32SharedrtDynamic"
	test -d $(EXECUTION_PATH)../../../garbage/GCC/DebugLinux32SharedrtDynamic mkdir -p "$(EXECUTION_PATH)../../../garbage/GCC/DebugLinux32SharedrtDynamic"
	mkdir -p $(EXECUTION_PATH)../../../bin/GCC/DebugLinux32SharedrtDynamic
	cp "$(EXECUTION_PATH)../../../../bin/GCC/DebugLinux32SharedrtDynamic/libQuimeraEngineCommon.so" "$(EXECUTION_PATH)../../../bin/GCC/DebugLinux32SharedrtDynamic"
	cp "$(EXECUTION_PATH)../../../../bin/GCC/DebugLinux32SharedrtDynamic/libQuimeraEngineCommon.so" "$(EXECUTION_PATH)."
	cp "$(EXECUTION_PATH)../../../../bin/GCC/DebugLinux32SharedrtDynamic/libQuimeraEngineTools.so" "$(EXECUTION_PATH)../../../bin/GCC/DebugLinux32SharedrtDynamic"
	cp "$(EXECUTION_PATH)../../../../bin/GCC/DebugLinux32SharedrtDynamic/libQuimeraEngineTools.so" "$(EXECUTION_PATH)."
	cp "$(EXECUTION_PATH)../../../../bin/GCC/DebugLinux32SharedrtDynamic/libQuimeraEngineSystem.so" "$(EXECUTION_PATH)../../../bin/GCC/DebugLinux32SharedrtDynamic"
	cp "$(EXECUTION_PATH)../../../../bin/GCC/DebugLinux32SharedrtDynamic/libQuimeraEngineSystem.so" "$(EXECUTION_PATH)."
	cp "$(EXECUTION_PATH)../../../bin/TestConfig.txt" "$(EXECUTION_PATH)../../../bin/GCC/DebugLinux32SharedrtDynamic"
	cp "$(EXECUTION_PATH)../../../bin/NormalizationTest.txt" "$(EXECUTION_PATH)../../../bin/GCC/DebugLinux32SharedrtDynamic"
	


DebugLinux32SharedrtDynamic: $(OBJECTS_DEBUGLINUX32SHAREDRTDYNAMIC)
	$(LD) $(LINKEROPTIONS_DEBUGLINUX32SHAREDRTDYNAMIC) $(LIBRARYDIRS_DEBUGLINUX32SHAREDRTDYNAMIC) $(OBJECTS_DEBUGLINUX32SHAREDRTDYNAMIC) $(LIBRARIES_DEBUGLINUX32SHAREDRTDYNAMIC) -o $(OUTPUT_DEBUGLINUX32SHAREDRTDYNAMIC)

$(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_system.TestModule_System.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_system/TestModule_System.cpp
	$(CXX) $(COMPILEROPTIONS_DEBUGLINUX32SHAREDRTDYNAMIC) $(INCLUDES_DEBUGLINUX32SHAREDRTDYNAMIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_system/TestModule_System.cpp -o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_system.TestModule_System.o

$(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_system.QObject_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_system/QObject_Test.cpp
	$(CXX) $(COMPILEROPTIONS_DEBUGLINUX32SHAREDRTDYNAMIC) $(INCLUDES_DEBUGLINUX32SHAREDRTDYNAMIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_system/QObject_Test.cpp -o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_system.QObject_Test.o

$(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_system.QLocalTimeZone_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_system/QLocalTimeZone_Test.cpp
	$(CXX) $(COMPILEROPTIONS_DEBUGLINUX32SHAREDRTDYNAMIC) $(INCLUDES_DEBUGLINUX32SHAREDRTDYNAMIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_system/QLocalTimeZone_Test.cpp -o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_system.QLocalTimeZone_Test.o

$(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_system.QDateTimeNow_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_system/QDateTimeNow_Test.cpp
	$(CXX) $(COMPILEROPTIONS_DEBUGLINUX32SHAREDRTDYNAMIC) $(INCLUDES_DEBUGLINUX32SHAREDRTDYNAMIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_system/QDateTimeNow_Test.cpp -o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_system.QDateTimeNow_Test.o

$(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_system.QStopwatch_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_system/QStopwatch_Test.cpp
	$(CXX) $(COMPILEROPTIONS_DEBUGLINUX32SHAREDRTDYNAMIC) $(INCLUDES_DEBUGLINUX32SHAREDRTDYNAMIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_system/QStopwatch_Test.cpp -o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_system.QStopwatch_Test.o

$(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_system.QMemoryStream_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_system/QMemoryStream_Test.cpp
	$(CXX) $(COMPILEROPTIONS_DEBUGLINUX32SHAREDRTDYNAMIC) $(INCLUDES_DEBUGLINUX32SHAREDRTDYNAMIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_system/QMemoryStream_Test.cpp -o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_system.QMemoryStream_Test.o

$(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_system.QUri_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_system/QUri_Test.cpp
	$(CXX) $(COMPILEROPTIONS_DEBUGLINUX32SHAREDRTDYNAMIC) $(INCLUDES_DEBUGLINUX32SHAREDRTDYNAMIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_system/QUri_Test.cpp -o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_system.QUri_Test.o

$(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_system.QBinaryStreamReader_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_system/QBinaryStreamReader_Test.cpp
	$(CXX) $(COMPILEROPTIONS_DEBUGLINUX32SHAREDRTDYNAMIC) $(INCLUDES_DEBUGLINUX32SHAREDRTDYNAMIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_system/QBinaryStreamReader_Test.cpp -o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_system.QBinaryStreamReader_Test.o

$(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_system.QBinaryStreamWriter_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_system/QBinaryStreamWriter_Test.cpp
	$(CXX) $(COMPILEROPTIONS_DEBUGLINUX32SHAREDRTDYNAMIC) $(INCLUDES_DEBUGLINUX32SHAREDRTDYNAMIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_system/QBinaryStreamWriter_Test.cpp -o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_system.QBinaryStreamWriter_Test.o

$(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_system.QTextStreamReader_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_system/QTextStreamReader_Test.cpp
	$(CXX) $(COMPILEROPTIONS_DEBUGLINUX32SHAREDRTDYNAMIC) $(INCLUDES_DEBUGLINUX32SHAREDRTDYNAMIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_system/QTextStreamReader_Test.cpp -o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_system.QTextStreamReader_Test.o

$(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_system.QPath_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_system/QPath_Test.cpp
	$(CXX) $(COMPILEROPTIONS_DEBUGLINUX32SHAREDRTDYNAMIC) $(INCLUDES_DEBUGLINUX32SHAREDRTDYNAMIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_system/QPath_Test.cpp -o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_system.QPath_Test.o

$(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_system.SQDirectory_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_system/SQDirectory_Test.cpp
	$(CXX) $(COMPILEROPTIONS_DEBUGLINUX32SHAREDRTDYNAMIC) $(INCLUDES_DEBUGLINUX32SHAREDRTDYNAMIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_system/SQDirectory_Test.cpp -o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_system.SQDirectory_Test.o

$(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_system.SQFile_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_system/SQFile_Test.cpp
	$(CXX) $(COMPILEROPTIONS_DEBUGLINUX32SHAREDRTDYNAMIC) $(INCLUDES_DEBUGLINUX32SHAREDRTDYNAMIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_system/SQFile_Test.cpp -o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_system.SQFile_Test.o

$(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_system.QFileStream_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_system/QFileStream_Test.cpp
	$(CXX) $(COMPILEROPTIONS_DEBUGLINUX32SHAREDRTDYNAMIC) $(INCLUDES_DEBUGLINUX32SHAREDRTDYNAMIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_system/QFileStream_Test.cpp -o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_system.QFileStream_Test.o

$(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_system.QDerivedFromObject.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_system/QDerivedFromObject.cpp
	$(CXX) $(COMPILEROPTIONS_DEBUGLINUX32SHAREDRTDYNAMIC) $(INCLUDES_DEBUGLINUX32SHAREDRTDYNAMIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_system/QDerivedFromObject.cpp -o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_system.QDerivedFromObject.o

$(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_system.SQAnyTypeToStringConverter_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_system/SQAnyTypeToStringConverter_Test.cpp
	$(CXX) $(COMPILEROPTIONS_DEBUGLINUX32SHAREDRTDYNAMIC) $(INCLUDES_DEBUGLINUX32SHAREDRTDYNAMIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_system/SQAnyTypeToStringConverter_Test.cpp -o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_system.SQAnyTypeToStringConverter_Test.o

$(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_system.SQTypeExtensions_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_system/SQTypeExtensions_Test.cpp
	$(CXX) $(COMPILEROPTIONS_DEBUGLINUX32SHAREDRTDYNAMIC) $(INCLUDES_DEBUGLINUX32SHAREDRTDYNAMIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_system/SQTypeExtensions_Test.cpp -o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_system.SQTypeExtensions_Test.o

$(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_system.QArgumentTrace_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_system/QArgumentTrace_Test.cpp
	$(CXX) $(COMPILEROPTIONS_DEBUGLINUX32SHAREDRTDYNAMIC) $(INCLUDES_DEBUGLINUX32SHAREDRTDYNAMIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_system/QArgumentTrace_Test.cpp -o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_system.QArgumentTrace_Test.o

$(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_system.QCallTrace_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_system/QCallTrace_Test.cpp
	$(CXX) $(COMPILEROPTIONS_DEBUGLINUX32SHAREDRTDYNAMIC) $(INCLUDES_DEBUGLINUX32SHAREDRTDYNAMIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_system/QCallTrace_Test.cpp -o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_system.QCallTrace_Test.o

$(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_system.QCallStackTrace_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_system/QCallStackTrace_Test.cpp
	$(CXX) $(COMPILEROPTIONS_DEBUGLINUX32SHAREDRTDYNAMIC) $(INCLUDES_DEBUGLINUX32SHAREDRTDYNAMIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_system/QCallStackTrace_Test.cpp -o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_system.QCallStackTrace_Test.o

$(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_system.QThread_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_system/QThread_Test.cpp
	$(CXX) $(COMPILEROPTIONS_DEBUGLINUX32SHAREDRTDYNAMIC) $(INCLUDES_DEBUGLINUX32SHAREDRTDYNAMIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_system/QThread_Test.cpp -o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_system.QThread_Test.o

$(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_system.SQThisThread_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_system/SQThisThread_Test.cpp
	$(CXX) $(COMPILEROPTIONS_DEBUGLINUX32SHAREDRTDYNAMIC) $(INCLUDES_DEBUGLINUX32SHAREDRTDYNAMIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_system/SQThisThread_Test.cpp -o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_system.SQThisThread_Test.o

$(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTDYNAMIC)__.__.__.testsystem.EQTestType.o: $(EXECUTION_PATH)../../../testsystem/EQTestType.cpp
	$(CXX) $(COMPILEROPTIONS_DEBUGLINUX32SHAREDRTDYNAMIC) $(INCLUDES_DEBUGLINUX32SHAREDRTDYNAMIC) -c $(EXECUTION_PATH)../../../testsystem/EQTestType.cpp -o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTDYNAMIC)__.__.__.testsystem.EQTestType.o

$(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTDYNAMIC)__.__.__.testsystem.QCommonTestConfig.o: $(EXECUTION_PATH)../../../testsystem/QCommonTestConfig.cpp
	$(CXX) $(COMPILEROPTIONS_DEBUGLINUX32SHAREDRTDYNAMIC) $(INCLUDES_DEBUGLINUX32SHAREDRTDYNAMIC) -c $(EXECUTION_PATH)../../../testsystem/QCommonTestConfig.cpp -o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTDYNAMIC)__.__.__.testsystem.QCommonTestConfig.o

$(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTDYNAMIC)__.__.__.testsystem.QSimpleConfigLoader.o: $(EXECUTION_PATH)../../../testsystem/QSimpleConfigLoader.cpp
	$(CXX) $(COMPILEROPTIONS_DEBUGLINUX32SHAREDRTDYNAMIC) $(INCLUDES_DEBUGLINUX32SHAREDRTDYNAMIC) -c $(EXECUTION_PATH)../../../testsystem/QSimpleConfigLoader.cpp -o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTDYNAMIC)__.__.__.testsystem.QSimpleConfigLoader.o

postbuildDebugLinux32SharedrtDynamic:
	rm -f *.so
	if test -d "$(EXECUTION_PATH)../../../bin/GCC/DebugLinux32SharedrtDynamic/artifacts/"; then rm -rf "$(EXECUTION_PATH)../../../bin/GCC/DebugLinux32SharedrtDynamic/artifacts/"; fi
	rsync -a --exclude='.*' $(EXECUTION_PATH)../../../bin/artifacts/artifacts $(EXECUTION_PATH)../../../bin/GCC/DebugLinux32SharedrtDynamic


buildDebugLinux32SharedrtDynamic: prebuildDebugLinux32SharedrtDynamic DebugLinux32SharedrtDynamic postbuildDebugLinux32SharedrtDynamic

cleanDebugLinux32SharedrtDynamic:
	rm -f $(OBJECTS_DEBUGLINUX32SHAREDRTDYNAMIC)
	rm -f $(OUTPUT_DEBUGLINUX32SHAREDRTDYNAMIC)
	test -d $(EXECUTION_PATH)../../../bin/GCC/DebugLinux32SharedrtDynamic rmdir "$(EXECUTION_PATH)..\..\..\bin\GCC\DebugLinux32SharedrtDynamic"
	test -d $(EXECUTION_PATH)../../../garbage/GCC/DebugLinux32SharedrtDynamic rmdir "$(EXECUTION_PATH)..\..\..\garbage\GCC\DebugLinux32SharedrtDynamic"


#------------------------------------------------------------
#------------- DebugLinux32SharedrtStatic --------------
#------------------------------------------------------------
INCLUDES_DEBUGLINUX32SHAREDRTSTATIC = $(INCLUDES_GLOBAL) -I$(EXECUTION_PATH)../../../../headers -I$(EXECUTION_PATH)../../../tests/unit/testmodule_system -I$(EXECUTION_PATH)../../../tests/unit -I$(EXECUTION_PATH)../../../../3rdparty/ICU/include
LIBRARYDIRS_DEBUGLINUX32SHAREDRTSTATIC = $(LIBRARYDIRS_GLOBAL) -L$(EXECUTION_PATH)../../../../3rdparty/Boost/bin/Linux32/DebugSharedrtStatic -L$(EXECUTION_PATH)../../../../bin/GCC/DebugLinux32SharedrtStatic
LIBRARIES_DEBUGLINUX32SHAREDRTSTATIC = $(LIBRARIES_GLOBAL) -lQuimeraEngineSystem -lQuimeraEngineTools -lQuimeraEngineCommon -lboost_thread-mt-d -lboost_system-mt-d -lboost_filesystem-mt-d -lboost_unit_test_framework-mt-d -licudata -licuuc -licui18n -lrt
COMPILEROPTIONS_DEBUGLINUX32SHAREDRTSTATIC = $(COMPILEROPTIONS_GLOBAL) -g -O0 -Wall -Wno-comment -Wno-unused-local-typedefs -m32 -isystem $(EXECUTION_PATH)../../../../3rdparty/Boost/include
LINKEROPTIONS_DEBUGLINUX32SHAREDRTSTATIC = $(LINKEROPTIONS_GLOBAL) -m32
DEFINITIONS_DEBUGLINUX32SHAREDRTSTATIC = $(DEFINITIONS_GLOBAL)
OUTPUT_DEBUGLINUX32SHAREDRTSTATIC = $(EXECUTION_PATH)../../../bin/GCC/DebugLinux32SharedrtStatic/Unit_TestModule_System.sh
INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTSTATIC = $(EXECUTION_PATH)../../../garbage/GCC/DebugLinux32SharedrtStatic/
OBJECTS_DEBUGLINUX32SHAREDRTSTATIC = $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_system.TestModule_System.o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_system.QObject_Test.o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_system.QLocalTimeZone_Test.o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_system.QDateTimeNow_Test.o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_system.QStopwatch_Test.o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_system.QMemoryStream_Test.o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_system.QUri_Test.o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_system.QBinaryStreamReader_Test.o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_system.QBinaryStreamWriter_Test.o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_system.QTextStreamReader_Test.o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_system.QPath_Test.o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_system.SQDirectory_Test.o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_system.SQFile_Test.o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_system.QFileStream_Test.o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_system.QDerivedFromObject.o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_system.SQAnyTypeToStringConverter_Test.o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_system.SQTypeExtensions_Test.o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_system.QArgumentTrace_Test.o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_system.QCallTrace_Test.o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_system.QCallStackTrace_Test.o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_system.QThread_Test.o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_system.SQThisThread_Test.o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTSTATIC)__.__.__.testsystem.EQTestType.o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTSTATIC)__.__.__.testsystem.QCommonTestConfig.o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTSTATIC)__.__.__.testsystem.QSimpleConfigLoader.o

prebuildDebugLinux32SharedrtStatic:
	test -d $(EXECUTION_PATH)../../../bin/GCC/DebugLinux32SharedrtStatic mkdir -p "$(EXECUTION_PATH)../../../bin/GCC/DebugLinux32SharedrtStatic"
	test -d $(EXECUTION_PATH)../../../garbage/GCC/DebugLinux32SharedrtStatic mkdir -p "$(EXECUTION_PATH)../../../garbage/GCC/DebugLinux32SharedrtStatic"
	mkdir -p $(EXECUTION_PATH)../../../bin/GCC/DebugLinux32SharedrtStatic
	cp "$(EXECUTION_PATH)../../../bin/TestConfig.txt" "$(EXECUTION_PATH)../../../bin/GCC/DebugLinux32SharedrtStatic"
	cp "$(EXECUTION_PATH)../../../bin/NormalizationTest.txt" "$(EXECUTION_PATH)../../../bin/GCC/DebugLinux32SharedrtStatic"
	


DebugLinux32SharedrtStatic: $(OBJECTS_DEBUGLINUX32SHAREDRTSTATIC)
	$(LD) $(LINKEROPTIONS_DEBUGLINUX32SHAREDRTSTATIC) $(LIBRARYDIRS_DEBUGLINUX32SHAREDRTSTATIC) $(OBJECTS_DEBUGLINUX32SHAREDRTSTATIC) $(LIBRARIES_DEBUGLINUX32SHAREDRTSTATIC) -o $(OUTPUT_DEBUGLINUX32SHAREDRTSTATIC)

$(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_system.TestModule_System.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_system/TestModule_System.cpp
	$(CXX) $(COMPILEROPTIONS_DEBUGLINUX32SHAREDRTSTATIC) $(INCLUDES_DEBUGLINUX32SHAREDRTSTATIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_system/TestModule_System.cpp -o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_system.TestModule_System.o

$(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_system.QObject_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_system/QObject_Test.cpp
	$(CXX) $(COMPILEROPTIONS_DEBUGLINUX32SHAREDRTSTATIC) $(INCLUDES_DEBUGLINUX32SHAREDRTSTATIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_system/QObject_Test.cpp -o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_system.QObject_Test.o

$(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_system.QLocalTimeZone_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_system/QLocalTimeZone_Test.cpp
	$(CXX) $(COMPILEROPTIONS_DEBUGLINUX32SHAREDRTSTATIC) $(INCLUDES_DEBUGLINUX32SHAREDRTSTATIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_system/QLocalTimeZone_Test.cpp -o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_system.QLocalTimeZone_Test.o

$(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_system.QDateTimeNow_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_system/QDateTimeNow_Test.cpp
	$(CXX) $(COMPILEROPTIONS_DEBUGLINUX32SHAREDRTSTATIC) $(INCLUDES_DEBUGLINUX32SHAREDRTSTATIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_system/QDateTimeNow_Test.cpp -o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_system.QDateTimeNow_Test.o

$(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_system.QStopwatch_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_system/QStopwatch_Test.cpp
	$(CXX) $(COMPILEROPTIONS_DEBUGLINUX32SHAREDRTSTATIC) $(INCLUDES_DEBUGLINUX32SHAREDRTSTATIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_system/QStopwatch_Test.cpp -o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_system.QStopwatch_Test.o

$(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_system.QMemoryStream_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_system/QMemoryStream_Test.cpp
	$(CXX) $(COMPILEROPTIONS_DEBUGLINUX32SHAREDRTSTATIC) $(INCLUDES_DEBUGLINUX32SHAREDRTSTATIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_system/QMemoryStream_Test.cpp -o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_system.QMemoryStream_Test.o

$(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_system.QUri_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_system/QUri_Test.cpp
	$(CXX) $(COMPILEROPTIONS_DEBUGLINUX32SHAREDRTSTATIC) $(INCLUDES_DEBUGLINUX32SHAREDRTSTATIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_system/QUri_Test.cpp -o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_system.QUri_Test.o

$(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_system.QBinaryStreamReader_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_system/QBinaryStreamReader_Test.cpp
	$(CXX) $(COMPILEROPTIONS_DEBUGLINUX32SHAREDRTSTATIC) $(INCLUDES_DEBUGLINUX32SHAREDRTSTATIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_system/QBinaryStreamReader_Test.cpp -o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_system.QBinaryStreamReader_Test.o

$(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_system.QBinaryStreamWriter_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_system/QBinaryStreamWriter_Test.cpp
	$(CXX) $(COMPILEROPTIONS_DEBUGLINUX32SHAREDRTSTATIC) $(INCLUDES_DEBUGLINUX32SHAREDRTSTATIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_system/QBinaryStreamWriter_Test.cpp -o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_system.QBinaryStreamWriter_Test.o

$(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_system.QTextStreamReader_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_system/QTextStreamReader_Test.cpp
	$(CXX) $(COMPILEROPTIONS_DEBUGLINUX32SHAREDRTSTATIC) $(INCLUDES_DEBUGLINUX32SHAREDRTSTATIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_system/QTextStreamReader_Test.cpp -o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_system.QTextStreamReader_Test.o

$(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_system.QPath_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_system/QPath_Test.cpp
	$(CXX) $(COMPILEROPTIONS_DEBUGLINUX32SHAREDRTSTATIC) $(INCLUDES_DEBUGLINUX32SHAREDRTSTATIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_system/QPath_Test.cpp -o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_system.QPath_Test.o

$(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_system.SQDirectory_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_system/SQDirectory_Test.cpp
	$(CXX) $(COMPILEROPTIONS_DEBUGLINUX32SHAREDRTSTATIC) $(INCLUDES_DEBUGLINUX32SHAREDRTSTATIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_system/SQDirectory_Test.cpp -o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_system.SQDirectory_Test.o

$(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_system.SQFile_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_system/SQFile_Test.cpp
	$(CXX) $(COMPILEROPTIONS_DEBUGLINUX32SHAREDRTSTATIC) $(INCLUDES_DEBUGLINUX32SHAREDRTSTATIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_system/SQFile_Test.cpp -o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_system.SQFile_Test.o

$(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_system.QFileStream_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_system/QFileStream_Test.cpp
	$(CXX) $(COMPILEROPTIONS_DEBUGLINUX32SHAREDRTSTATIC) $(INCLUDES_DEBUGLINUX32SHAREDRTSTATIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_system/QFileStream_Test.cpp -o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_system.QFileStream_Test.o

$(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_system.QDerivedFromObject.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_system/QDerivedFromObject.cpp
	$(CXX) $(COMPILEROPTIONS_DEBUGLINUX32SHAREDRTSTATIC) $(INCLUDES_DEBUGLINUX32SHAREDRTSTATIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_system/QDerivedFromObject.cpp -o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_system.QDerivedFromObject.o

$(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_system.SQAnyTypeToStringConverter_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_system/SQAnyTypeToStringConverter_Test.cpp
	$(CXX) $(COMPILEROPTIONS_DEBUGLINUX32SHAREDRTSTATIC) $(INCLUDES_DEBUGLINUX32SHAREDRTSTATIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_system/SQAnyTypeToStringConverter_Test.cpp -o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_system.SQAnyTypeToStringConverter_Test.o

$(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_system.SQTypeExtensions_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_system/SQTypeExtensions_Test.cpp
	$(CXX) $(COMPILEROPTIONS_DEBUGLINUX32SHAREDRTSTATIC) $(INCLUDES_DEBUGLINUX32SHAREDRTSTATIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_system/SQTypeExtensions_Test.cpp -o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_system.SQTypeExtensions_Test.o

$(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_system.QArgumentTrace_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_system/QArgumentTrace_Test.cpp
	$(CXX) $(COMPILEROPTIONS_DEBUGLINUX32SHAREDRTSTATIC) $(INCLUDES_DEBUGLINUX32SHAREDRTSTATIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_system/QArgumentTrace_Test.cpp -o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_system.QArgumentTrace_Test.o

$(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_system.QCallTrace_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_system/QCallTrace_Test.cpp
	$(CXX) $(COMPILEROPTIONS_DEBUGLINUX32SHAREDRTSTATIC) $(INCLUDES_DEBUGLINUX32SHAREDRTSTATIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_system/QCallTrace_Test.cpp -o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_system.QCallTrace_Test.o

$(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_system.QCallStackTrace_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_system/QCallStackTrace_Test.cpp
	$(CXX) $(COMPILEROPTIONS_DEBUGLINUX32SHAREDRTSTATIC) $(INCLUDES_DEBUGLINUX32SHAREDRTSTATIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_system/QCallStackTrace_Test.cpp -o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_system.QCallStackTrace_Test.o

$(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_system.QThread_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_system/QThread_Test.cpp
	$(CXX) $(COMPILEROPTIONS_DEBUGLINUX32SHAREDRTSTATIC) $(INCLUDES_DEBUGLINUX32SHAREDRTSTATIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_system/QThread_Test.cpp -o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_system.QThread_Test.o

$(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_system.SQThisThread_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_system/SQThisThread_Test.cpp
	$(CXX) $(COMPILEROPTIONS_DEBUGLINUX32SHAREDRTSTATIC) $(INCLUDES_DEBUGLINUX32SHAREDRTSTATIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_system/SQThisThread_Test.cpp -o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_system.SQThisThread_Test.o

$(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTSTATIC)__.__.__.testsystem.EQTestType.o: $(EXECUTION_PATH)../../../testsystem/EQTestType.cpp
	$(CXX) $(COMPILEROPTIONS_DEBUGLINUX32SHAREDRTSTATIC) $(INCLUDES_DEBUGLINUX32SHAREDRTSTATIC) -c $(EXECUTION_PATH)../../../testsystem/EQTestType.cpp -o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTSTATIC)__.__.__.testsystem.EQTestType.o

$(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTSTATIC)__.__.__.testsystem.QCommonTestConfig.o: $(EXECUTION_PATH)../../../testsystem/QCommonTestConfig.cpp
	$(CXX) $(COMPILEROPTIONS_DEBUGLINUX32SHAREDRTSTATIC) $(INCLUDES_DEBUGLINUX32SHAREDRTSTATIC) -c $(EXECUTION_PATH)../../../testsystem/QCommonTestConfig.cpp -o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTSTATIC)__.__.__.testsystem.QCommonTestConfig.o

$(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTSTATIC)__.__.__.testsystem.QSimpleConfigLoader.o: $(EXECUTION_PATH)../../../testsystem/QSimpleConfigLoader.cpp
	$(CXX) $(COMPILEROPTIONS_DEBUGLINUX32SHAREDRTSTATIC) $(INCLUDES_DEBUGLINUX32SHAREDRTSTATIC) -c $(EXECUTION_PATH)../../../testsystem/QSimpleConfigLoader.cpp -o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTSTATIC)__.__.__.testsystem.QSimpleConfigLoader.o

postbuildDebugLinux32SharedrtStatic:
	if test -d "$(EXECUTION_PATH)../../../bin/GCC/DebugLinux32SharedrtStatic/artifacts/"; then rm -rf "$(EXECUTION_PATH)../../../bin/GCC/DebugLinux32SharedrtStatic/artifacts/"; fi
	rsync -a --exclude='.*' $(EXECUTION_PATH)../../../bin/artifacts/artifacts $(EXECUTION_PATH)../../../bin/GCC/DebugLinux32SharedrtStatic


buildDebugLinux32SharedrtStatic: prebuildDebugLinux32SharedrtStatic DebugLinux32SharedrtStatic postbuildDebugLinux32SharedrtStatic

cleanDebugLinux32SharedrtStatic:
	rm -f $(OBJECTS_DEBUGLINUX32SHAREDRTSTATIC)
	rm -f $(OUTPUT_DEBUGLINUX32SHAREDRTSTATIC)
	test -d $(EXECUTION_PATH)../../../bin/GCC/DebugLinux32SharedrtStatic rmdir "$(EXECUTION_PATH)..\..\..\bin\GCC\DebugLinux32SharedrtStatic"
	test -d $(EXECUTION_PATH)../../../garbage/GCC/DebugLinux32SharedrtStatic rmdir "$(EXECUTION_PATH)..\..\..\garbage\GCC\DebugLinux32SharedrtStatic"


#------------------------------------------------------------
#------------- DebugMac32SharedrtDynamic --------------
#------------------------------------------------------------
INCLUDES_DEBUGMAC32SHAREDRTDYNAMIC = $(INCLUDES_GLOBAL) -I$(EXECUTION_PATH)../../../../headers -I$(EXECUTION_PATH)../../../tests/unit/testmodule_system -I$(EXECUTION_PATH)../../../tests/unit -I$(EXECUTION_PATH)../../../../3rdparty/ICU/include
LIBRARYDIRS_DEBUGMAC32SHAREDRTDYNAMIC = $(LIBRARYDIRS_GLOBAL) -L$(EXECUTION_PATH)../../../../3rdparty/Boost/bin/Mac32/DebugSharedrtStatic -L$(EXECUTION_PATH)../../../../bin/Clang/DebugMac32SharedrtDynamic
LIBRARIES_DEBUGMAC32SHAREDRTDYNAMIC = $(LIBRARIES_GLOBAL) -lQuimeraEngineSystem -lQuimeraEngineTools -lQuimeraEngineCommon -lboost_thread-mt-d -lboost_system-mt-d -lboost_filesystem-mt-d -lboost_unit_test_framework-mt-d -licudata -licuuc -licui18n
COMPILEROPTIONS_DEBUGMAC32SHAREDRTDYNAMIC = $(COMPILEROPTIONS_GLOBAL) -g -O0 -Wall -Wno-comment -m32 -isystem $(EXECUTION_PATH)../../../../3rdparty/Boost/include
LINKEROPTIONS_DEBUGMAC32SHAREDRTDYNAMIC = $(LINKEROPTIONS_GLOBAL) -m32
DEFINITIONS_DEBUGMAC32SHAREDRTDYNAMIC = $(DEFINITIONS_GLOBAL) -DQE_PREPROCESSOR_IMPORTLIB_QUIMERAENGINE
OUTPUT_DEBUGMAC32SHAREDRTDYNAMIC = $(EXECUTION_PATH)../../../bin/Clang/DebugMac32SharedrtDynamic/Unit_TestModule_System.sh
INTERMEDIARYDIR_DEBUGMAC32SHAREDRTDYNAMIC = $(EXECUTION_PATH)../../../garbage/Clang/DebugMac32SharedrtDynamic/
OBJECTS_DEBUGMAC32SHAREDRTDYNAMIC = $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_system.TestModule_System.o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_system.QObject_Test.o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_system.QLocalTimeZone_Test.o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_system.QDateTimeNow_Test.o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_system.QStopwatch_Test.o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_system.QMemoryStream_Test.o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_system.QUri_Test.o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_system.QBinaryStreamReader_Test.o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_system.QBinaryStreamWriter_Test.o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_system.QTextStreamReader_Test.o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_system.QPath_Test.o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_system.SQDirectory_Test.o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_system.SQFile_Test.o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_system.QFileStream_Test.o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_system.QDerivedFromObject.o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_system.SQAnyTypeToStringConverter_Test.o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_system.SQTypeExtensions_Test.o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_system.QArgumentTrace_Test.o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_system.QCallTrace_Test.o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_system.QCallStackTrace_Test.o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_system.QThread_Test.o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_system.SQThisThread_Test.o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTDYNAMIC)__.__.__.testsystem.EQTestType.o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTDYNAMIC)__.__.__.testsystem.QCommonTestConfig.o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTDYNAMIC)__.__.__.testsystem.QSimpleConfigLoader.o

prebuildDebugMac32SharedrtDynamic:
	test -d $(EXECUTION_PATH)../../../bin/Clang/DebugMac32SharedrtDynamic mkdir -p "$(EXECUTION_PATH)../../../bin/Clang/DebugMac32SharedrtDynamic"
	test -d $(EXECUTION_PATH)../../../garbage/Clang/DebugMac32SharedrtDynamic mkdir -p "$(EXECUTION_PATH)../../../garbage/Clang/DebugMac32SharedrtDynamic"
	mkdir -p $(EXECUTION_PATH)../../../bin/Clang/DebugMac32SharedrtDynamic
	cp "$(EXECUTION_PATH)../../../../bin/Clang/DebugMac32SharedrtDynamic/libQuimeraEngineCommon.dylib" "$(EXECUTION_PATH)../../../bin/Clang/DebugMac32SharedrtDynamic"
	cp "$(EXECUTION_PATH)../../../../bin/Clang/DebugMac32SharedrtDynamic/libQuimeraEngineCommon.dylib" "$(EXECUTION_PATH)."
	cp "$(EXECUTION_PATH)../../../../bin/Clang/DebugMac32SharedrtDynamic/libQuimeraEngineTools.dylib" "$(EXECUTION_PATH)../../../bin/Clang/DebugMac32SharedrtDynamic"
	cp "$(EXECUTION_PATH)../../../../bin/Clang/DebugMac32SharedrtDynamic/libQuimeraEngineTools.dylib" "$(EXECUTION_PATH)."
	cp "$(EXECUTION_PATH)../../../../bin/Clang/DebugMac32SharedrtDynamic/libQuimeraEngineSystem.dylib" "$(EXECUTION_PATH)../../../bin/Clang/DebugMac32SharedrtDynamic"
	cp "$(EXECUTION_PATH)../../../../bin/Clang/DebugMac32SharedrtDynamic/libQuimeraEngineSystem.dylib" "$(EXECUTION_PATH)."
	cp "$(EXECUTION_PATH)../../../bin/TestConfig.txt" "$(EXECUTION_PATH)../../../bin/Clang/DebugMac32SharedrtDynamic"
	cp "$(EXECUTION_PATH)../../../bin/NormalizationTest.txt" "$(EXECUTION_PATH)../../../bin/Clang/DebugMac32SharedrtDynamic"
	


DebugMac32SharedrtDynamic: $(OBJECTS_DEBUGMAC32SHAREDRTDYNAMIC)
	$(LD) $(LINKEROPTIONS_DEBUGMAC32SHAREDRTDYNAMIC) $(LIBRARYDIRS_DEBUGMAC32SHAREDRTDYNAMIC) $(OBJECTS_DEBUGMAC32SHAREDRTDYNAMIC) $(LIBRARIES_DEBUGMAC32SHAREDRTDYNAMIC) -o $(OUTPUT_DEBUGMAC32SHAREDRTDYNAMIC)

$(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_system.TestModule_System.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_system/TestModule_System.cpp
	$(CXX) $(COMPILEROPTIONS_DEBUGMAC32SHAREDRTDYNAMIC) $(INCLUDES_DEBUGMAC32SHAREDRTDYNAMIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_system/TestModule_System.cpp -o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_system.TestModule_System.o

$(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_system.QObject_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_system/QObject_Test.cpp
	$(CXX) $(COMPILEROPTIONS_DEBUGMAC32SHAREDRTDYNAMIC) $(INCLUDES_DEBUGMAC32SHAREDRTDYNAMIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_system/QObject_Test.cpp -o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_system.QObject_Test.o

$(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_system.QLocalTimeZone_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_system/QLocalTimeZone_Test.cpp
	$(CXX) $(COMPILEROPTIONS_DEBUGMAC32SHAREDRTDYNAMIC) $(INCLUDES_DEBUGMAC32SHAREDRTDYNAMIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_system/QLocalTimeZone_Test.cpp -o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_system.QLocalTimeZone_Test.o

$(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_system.QDateTimeNow_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_system/QDateTimeNow_Test.cpp
	$(CXX) $(COMPILEROPTIONS_DEBUGMAC32SHAREDRTDYNAMIC) $(INCLUDES_DEBUGMAC32SHAREDRTDYNAMIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_system/QDateTimeNow_Test.cpp -o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_system.QDateTimeNow_Test.o

$(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_system.QStopwatch_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_system/QStopwatch_Test.cpp
	$(CXX) $(COMPILEROPTIONS_DEBUGMAC32SHAREDRTDYNAMIC) $(INCLUDES_DEBUGMAC32SHAREDRTDYNAMIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_system/QStopwatch_Test.cpp -o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_system.QStopwatch_Test.o

$(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_system.QMemoryStream_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_system/QMemoryStream_Test.cpp
	$(CXX) $(COMPILEROPTIONS_DEBUGMAC32SHAREDRTDYNAMIC) $(INCLUDES_DEBUGMAC32SHAREDRTDYNAMIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_system/QMemoryStream_Test.cpp -o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_system.QMemoryStream_Test.o

$(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_system.QUri_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_system/QUri_Test.cpp
	$(CXX) $(COMPILEROPTIONS_DEBUGMAC32SHAREDRTDYNAMIC) $(INCLUDES_DEBUGMAC32SHAREDRTDYNAMIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_system/QUri_Test.cpp -o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_system.QUri_Test.o

$(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_system.QBinaryStreamReader_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_system/QBinaryStreamReader_Test.cpp
	$(CXX) $(COMPILEROPTIONS_DEBUGMAC32SHAREDRTDYNAMIC) $(INCLUDES_DEBUGMAC32SHAREDRTDYNAMIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_system/QBinaryStreamReader_Test.cpp -o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_system.QBinaryStreamReader_Test.o

$(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_system.QBinaryStreamWriter_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_system/QBinaryStreamWriter_Test.cpp
	$(CXX) $(COMPILEROPTIONS_DEBUGMAC32SHAREDRTDYNAMIC) $(INCLUDES_DEBUGMAC32SHAREDRTDYNAMIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_system/QBinaryStreamWriter_Test.cpp -o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_system.QBinaryStreamWriter_Test.o

$(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_system.QTextStreamReader_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_system/QTextStreamReader_Test.cpp
	$(CXX) $(COMPILEROPTIONS_DEBUGMAC32SHAREDRTDYNAMIC) $(INCLUDES_DEBUGMAC32SHAREDRTDYNAMIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_system/QTextStreamReader_Test.cpp -o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_system.QTextStreamReader_Test.o

$(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_system.QPath_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_system/QPath_Test.cpp
	$(CXX) $(COMPILEROPTIONS_DEBUGMAC32SHAREDRTDYNAMIC) $(INCLUDES_DEBUGMAC32SHAREDRTDYNAMIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_system/QPath_Test.cpp -o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_system.QPath_Test.o

$(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_system.SQDirectory_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_system/SQDirectory_Test.cpp
	$(CXX) $(COMPILEROPTIONS_DEBUGMAC32SHAREDRTDYNAMIC) $(INCLUDES_DEBUGMAC32SHAREDRTDYNAMIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_system/SQDirectory_Test.cpp -o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_system.SQDirectory_Test.o

$(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_system.SQFile_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_system/SQFile_Test.cpp
	$(CXX) $(COMPILEROPTIONS_DEBUGMAC32SHAREDRTDYNAMIC) $(INCLUDES_DEBUGMAC32SHAREDRTDYNAMIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_system/SQFile_Test.cpp -o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_system.SQFile_Test.o

$(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_system.QFileStream_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_system/QFileStream_Test.cpp
	$(CXX) $(COMPILEROPTIONS_DEBUGMAC32SHAREDRTDYNAMIC) $(INCLUDES_DEBUGMAC32SHAREDRTDYNAMIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_system/QFileStream_Test.cpp -o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_system.QFileStream_Test.o

$(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_system.QDerivedFromObject.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_system/QDerivedFromObject.cpp
	$(CXX) $(COMPILEROPTIONS_DEBUGMAC32SHAREDRTDYNAMIC) $(INCLUDES_DEBUGMAC32SHAREDRTDYNAMIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_system/QDerivedFromObject.cpp -o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_system.QDerivedFromObject.o

$(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_system.SQAnyTypeToStringConverter_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_system/SQAnyTypeToStringConverter_Test.cpp
	$(CXX) $(COMPILEROPTIONS_DEBUGMAC32SHAREDRTDYNAMIC) $(INCLUDES_DEBUGMAC32SHAREDRTDYNAMIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_system/SQAnyTypeToStringConverter_Test.cpp -o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_system.SQAnyTypeToStringConverter_Test.o

$(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_system.SQTypeExtensions_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_system/SQTypeExtensions_Test.cpp
	$(CXX) $(COMPILEROPTIONS_DEBUGMAC32SHAREDRTDYNAMIC) $(INCLUDES_DEBUGMAC32SHAREDRTDYNAMIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_system/SQTypeExtensions_Test.cpp -o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_system.SQTypeExtensions_Test.o

$(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_system.QArgumentTrace_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_system/QArgumentTrace_Test.cpp
	$(CXX) $(COMPILEROPTIONS_DEBUGMAC32SHAREDRTDYNAMIC) $(INCLUDES_DEBUGMAC32SHAREDRTDYNAMIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_system/QArgumentTrace_Test.cpp -o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_system.QArgumentTrace_Test.o

$(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_system.QCallTrace_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_system/QCallTrace_Test.cpp
	$(CXX) $(COMPILEROPTIONS_DEBUGMAC32SHAREDRTDYNAMIC) $(INCLUDES_DEBUGMAC32SHAREDRTDYNAMIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_system/QCallTrace_Test.cpp -o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_system.QCallTrace_Test.o

$(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_system.QCallStackTrace_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_system/QCallStackTrace_Test.cpp
	$(CXX) $(COMPILEROPTIONS_DEBUGMAC32SHAREDRTDYNAMIC) $(INCLUDES_DEBUGMAC32SHAREDRTDYNAMIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_system/QCallStackTrace_Test.cpp -o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_system.QCallStackTrace_Test.o

$(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_system.QThread_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_system/QThread_Test.cpp
	$(CXX) $(COMPILEROPTIONS_DEBUGMAC32SHAREDRTDYNAMIC) $(INCLUDES_DEBUGMAC32SHAREDRTDYNAMIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_system/QThread_Test.cpp -o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_system.QThread_Test.o

$(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_system.SQThisThread_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_system/SQThisThread_Test.cpp
	$(CXX) $(COMPILEROPTIONS_DEBUGMAC32SHAREDRTDYNAMIC) $(INCLUDES_DEBUGMAC32SHAREDRTDYNAMIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_system/SQThisThread_Test.cpp -o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_system.SQThisThread_Test.o

$(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTDYNAMIC)__.__.__.testsystem.EQTestType.o: $(EXECUTION_PATH)../../../testsystem/EQTestType.cpp
	$(CXX) $(COMPILEROPTIONS_DEBUGMAC32SHAREDRTDYNAMIC) $(INCLUDES_DEBUGMAC32SHAREDRTDYNAMIC) -c $(EXECUTION_PATH)../../../testsystem/EQTestType.cpp -o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTDYNAMIC)__.__.__.testsystem.EQTestType.o

$(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTDYNAMIC)__.__.__.testsystem.QCommonTestConfig.o: $(EXECUTION_PATH)../../../testsystem/QCommonTestConfig.cpp
	$(CXX) $(COMPILEROPTIONS_DEBUGMAC32SHAREDRTDYNAMIC) $(INCLUDES_DEBUGMAC32SHAREDRTDYNAMIC) -c $(EXECUTION_PATH)../../../testsystem/QCommonTestConfig.cpp -o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTDYNAMIC)__.__.__.testsystem.QCommonTestConfig.o

$(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTDYNAMIC)__.__.__.testsystem.QSimpleConfigLoader.o: $(EXECUTION_PATH)../../../testsystem/QSimpleConfigLoader.cpp
	$(CXX) $(COMPILEROPTIONS_DEBUGMAC32SHAREDRTDYNAMIC) $(INCLUDES_DEBUGMAC32SHAREDRTDYNAMIC) -c $(EXECUTION_PATH)../../../testsystem/QSimpleConfigLoader.cpp -o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTDYNAMIC)__.__.__.testsystem.QSimpleConfigLoader.o

postbuildDebugMac32SharedrtDynamic:
	rm -f *.dylib
	if test -d "$(EXECUTION_PATH)../../../bin/Clang/DebugMac32SharedrtDynamic/artifacts/"; then rm -rf "$(EXECUTION_PATH)../../../bin/Clang/DebugMac32SharedrtDynamic/artifacts/"; fi
	rsync -a --exclude='.*' $(EXECUTION_PATH)../../../bin/artifacts/artifacts $(EXECUTION_PATH)../../../bin/Clang/DebugMac32SharedrtDynamic


buildDebugMac32SharedrtDynamic: prebuildDebugMac32SharedrtDynamic DebugMac32SharedrtDynamic postbuildDebugMac32SharedrtDynamic

cleanDebugMac32SharedrtDynamic:
	rm -f $(OBJECTS_DEBUGMAC32SHAREDRTDYNAMIC)
	rm -f $(OUTPUT_DEBUGMAC32SHAREDRTDYNAMIC)
	test -d $(EXECUTION_PATH)../../../bin/Clang/DebugMac32SharedrtDynamic rmdir "$(EXECUTION_PATH)..\..\..\bin\Clang\DebugMac32SharedrtDynamic"
	test -d $(EXECUTION_PATH)../../../garbage/Clang/DebugMac32SharedrtDynamic rmdir "$(EXECUTION_PATH)..\..\..\garbage\Clang\DebugMac32SharedrtDynamic"


#------------------------------------------------------------
#------------- DebugMac32SharedrtStatic --------------
#------------------------------------------------------------
INCLUDES_DEBUGMAC32SHAREDRTSTATIC = $(INCLUDES_GLOBAL) -I$(EXECUTION_PATH)../../../../headers -I$(EXECUTION_PATH)../../../tests/unit/testmodule_system -I$(EXECUTION_PATH)../../../tests/unit -I$(EXECUTION_PATH)../../../../3rdparty/ICU/include
LIBRARYDIRS_DEBUGMAC32SHAREDRTSTATIC = $(LIBRARYDIRS_GLOBAL) -L$(EXECUTION_PATH)../../../../3rdparty/Boost/bin/Mac32/DebugSharedrtStatic -L$(EXECUTION_PATH)../../../../bin/Clang/DebugMac32SharedrtStatic
LIBRARIES_DEBUGMAC32SHAREDRTSTATIC = $(LIBRARIES_GLOBAL) -lQuimeraEngineSystem -lQuimeraEngineTools -lQuimeraEngineCommon -lboost_thread-mt-d -lboost_system-mt-d -lboost_filesystem-mt-d -lboost_unit_test_framework-mt-d -licudata -licuuc -licui18n
COMPILEROPTIONS_DEBUGMAC32SHAREDRTSTATIC = $(COMPILEROPTIONS_GLOBAL) -g -O0 -Wall -Wno-comment -m32 -isystem $(EXECUTION_PATH)../../../../3rdparty/Boost/include
LINKEROPTIONS_DEBUGMAC32SHAREDRTSTATIC = $(LINKEROPTIONS_GLOBAL) -m32
DEFINITIONS_DEBUGMAC32SHAREDRTSTATIC = $(DEFINITIONS_GLOBAL)
OUTPUT_DEBUGMAC32SHAREDRTSTATIC = $(EXECUTION_PATH)../../../bin/Clang/DebugMac32SharedrtStatic/Unit_TestModule_System.sh
INTERMEDIARYDIR_DEBUGMAC32SHAREDRTSTATIC = $(EXECUTION_PATH)../../../garbage/Clang/DebugMac32SharedrtStatic/
OBJECTS_DEBUGMAC32SHAREDRTSTATIC = $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_system.TestModule_System.o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_system.QObject_Test.o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_system.QLocalTimeZone_Test.o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_system.QDateTimeNow_Test.o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_system.QStopwatch_Test.o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_system.QMemoryStream_Test.o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_system.QUri_Test.o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_system.QBinaryStreamReader_Test.o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_system.QBinaryStreamWriter_Test.o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_system.QTextStreamReader_Test.o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_system.QPath_Test.o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_system.SQDirectory_Test.o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_system.SQFile_Test.o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_system.QFileStream_Test.o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_system.QDerivedFromObject.o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_system.SQAnyTypeToStringConverter_Test.o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_system.SQTypeExtensions_Test.o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_system.QArgumentTrace_Test.o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_system.QCallTrace_Test.o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_system.QCallStackTrace_Test.o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_system.QThread_Test.o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_system.SQThisThread_Test.o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTSTATIC)__.__.__.testsystem.EQTestType.o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTSTATIC)__.__.__.testsystem.QCommonTestConfig.o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTSTATIC)__.__.__.testsystem.QSimpleConfigLoader.o

prebuildDebugMac32SharedrtStatic:
	test -d $(EXECUTION_PATH)../../../bin/Clang/DebugMac32SharedrtStatic mkdir -p "$(EXECUTION_PATH)../../../bin/Clang/DebugMac32SharedrtStatic"
	test -d $(EXECUTION_PATH)../../../garbage/Clang/DebugMac32SharedrtStatic mkdir -p "$(EXECUTION_PATH)../../../garbage/Clang/DebugMac32SharedrtStatic"
	mkdir -p $(EXECUTION_PATH)../../../bin/Clang/DebugMac32SharedrtStatic
	cp "$(EXECUTION_PATH)../../../bin/TestConfig.txt" "$(EXECUTION_PATH)../../../bin/Clang/DebugMac32SharedrtStatic"
	cp "$(EXECUTION_PATH)../../../bin/NormalizationTest.txt" "$(EXECUTION_PATH)../../../bin/Clang/DebugMac32SharedrtStatic"
	


DebugMac32SharedrtStatic: $(OBJECTS_DEBUGMAC32SHAREDRTSTATIC)
	$(LD) $(LINKEROPTIONS_DEBUGMAC32SHAREDRTSTATIC) $(LIBRARYDIRS_DEBUGMAC32SHAREDRTSTATIC) $(OBJECTS_DEBUGMAC32SHAREDRTSTATIC) $(LIBRARIES_DEBUGMAC32SHAREDRTSTATIC) -o $(OUTPUT_DEBUGMAC32SHAREDRTSTATIC)

$(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_system.TestModule_System.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_system/TestModule_System.cpp
	$(CXX) $(COMPILEROPTIONS_DEBUGMAC32SHAREDRTSTATIC) $(INCLUDES_DEBUGMAC32SHAREDRTSTATIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_system/TestModule_System.cpp -o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_system.TestModule_System.o

$(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_system.QObject_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_system/QObject_Test.cpp
	$(CXX) $(COMPILEROPTIONS_DEBUGMAC32SHAREDRTSTATIC) $(INCLUDES_DEBUGMAC32SHAREDRTSTATIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_system/QObject_Test.cpp -o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_system.QObject_Test.o

$(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_system.QLocalTimeZone_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_system/QLocalTimeZone_Test.cpp
	$(CXX) $(COMPILEROPTIONS_DEBUGMAC32SHAREDRTSTATIC) $(INCLUDES_DEBUGMAC32SHAREDRTSTATIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_system/QLocalTimeZone_Test.cpp -o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_system.QLocalTimeZone_Test.o

$(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_system.QDateTimeNow_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_system/QDateTimeNow_Test.cpp
	$(CXX) $(COMPILEROPTIONS_DEBUGMAC32SHAREDRTSTATIC) $(INCLUDES_DEBUGMAC32SHAREDRTSTATIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_system/QDateTimeNow_Test.cpp -o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_system.QDateTimeNow_Test.o

$(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_system.QStopwatch_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_system/QStopwatch_Test.cpp
	$(CXX) $(COMPILEROPTIONS_DEBUGMAC32SHAREDRTSTATIC) $(INCLUDES_DEBUGMAC32SHAREDRTSTATIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_system/QStopwatch_Test.cpp -o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_system.QStopwatch_Test.o

$(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_system.QMemoryStream_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_system/QMemoryStream_Test.cpp
	$(CXX) $(COMPILEROPTIONS_DEBUGMAC32SHAREDRTSTATIC) $(INCLUDES_DEBUGMAC32SHAREDRTSTATIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_system/QMemoryStream_Test.cpp -o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_system.QMemoryStream_Test.o

$(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_system.QUri_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_system/QUri_Test.cpp
	$(CXX) $(COMPILEROPTIONS_DEBUGMAC32SHAREDRTSTATIC) $(INCLUDES_DEBUGMAC32SHAREDRTSTATIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_system/QUri_Test.cpp -o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_system.QUri_Test.o

$(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_system.QBinaryStreamReader_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_system/QBinaryStreamReader_Test.cpp
	$(CXX) $(COMPILEROPTIONS_DEBUGMAC32SHAREDRTSTATIC) $(INCLUDES_DEBUGMAC32SHAREDRTSTATIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_system/QBinaryStreamReader_Test.cpp -o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_system.QBinaryStreamReader_Test.o

$(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_system.QBinaryStreamWriter_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_system/QBinaryStreamWriter_Test.cpp
	$(CXX) $(COMPILEROPTIONS_DEBUGMAC32SHAREDRTSTATIC) $(INCLUDES_DEBUGMAC32SHAREDRTSTATIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_system/QBinaryStreamWriter_Test.cpp -o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_system.QBinaryStreamWriter_Test.o

$(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_system.QTextStreamReader_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_system/QTextStreamReader_Test.cpp
	$(CXX) $(COMPILEROPTIONS_DEBUGMAC32SHAREDRTSTATIC) $(INCLUDES_DEBUGMAC32SHAREDRTSTATIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_system/QTextStreamReader_Test.cpp -o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_system.QTextStreamReader_Test.o

$(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_system.QPath_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_system/QPath_Test.cpp
	$(CXX) $(COMPILEROPTIONS_DEBUGMAC32SHAREDRTSTATIC) $(INCLUDES_DEBUGMAC32SHAREDRTSTATIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_system/QPath_Test.cpp -o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_system.QPath_Test.o

$(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_system.SQDirectory_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_system/SQDirectory_Test.cpp
	$(CXX) $(COMPILEROPTIONS_DEBUGMAC32SHAREDRTSTATIC) $(INCLUDES_DEBUGMAC32SHAREDRTSTATIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_system/SQDirectory_Test.cpp -o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_system.SQDirectory_Test.o

$(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_system.SQFile_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_system/SQFile_Test.cpp
	$(CXX) $(COMPILEROPTIONS_DEBUGMAC32SHAREDRTSTATIC) $(INCLUDES_DEBUGMAC32SHAREDRTSTATIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_system/SQFile_Test.cpp -o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_system.SQFile_Test.o

$(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_system.QFileStream_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_system/QFileStream_Test.cpp
	$(CXX) $(COMPILEROPTIONS_DEBUGMAC32SHAREDRTSTATIC) $(INCLUDES_DEBUGMAC32SHAREDRTSTATIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_system/QFileStream_Test.cpp -o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_system.QFileStream_Test.o

$(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_system.QDerivedFromObject.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_system/QDerivedFromObject.cpp
	$(CXX) $(COMPILEROPTIONS_DEBUGMAC32SHAREDRTSTATIC) $(INCLUDES_DEBUGMAC32SHAREDRTSTATIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_system/QDerivedFromObject.cpp -o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_system.QDerivedFromObject.o

$(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_system.SQAnyTypeToStringConverter_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_system/SQAnyTypeToStringConverter_Test.cpp
	$(CXX) $(COMPILEROPTIONS_DEBUGMAC32SHAREDRTSTATIC) $(INCLUDES_DEBUGMAC32SHAREDRTSTATIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_system/SQAnyTypeToStringConverter_Test.cpp -o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_system.SQAnyTypeToStringConverter_Test.o

$(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_system.SQTypeExtensions_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_system/SQTypeExtensions_Test.cpp
	$(CXX) $(COMPILEROPTIONS_DEBUGMAC32SHAREDRTSTATIC) $(INCLUDES_DEBUGMAC32SHAREDRTSTATIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_system/SQTypeExtensions_Test.cpp -o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_system.SQTypeExtensions_Test.o

$(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_system.QArgumentTrace_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_system/QArgumentTrace_Test.cpp
	$(CXX) $(COMPILEROPTIONS_DEBUGMAC32SHAREDRTSTATIC) $(INCLUDES_DEBUGMAC32SHAREDRTSTATIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_system/QArgumentTrace_Test.cpp -o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_system.QArgumentTrace_Test.o

$(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_system.QCallTrace_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_system/QCallTrace_Test.cpp
	$(CXX) $(COMPILEROPTIONS_DEBUGMAC32SHAREDRTSTATIC) $(INCLUDES_DEBUGMAC32SHAREDRTSTATIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_system/QCallTrace_Test.cpp -o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_system.QCallTrace_Test.o

$(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_system.QCallStackTrace_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_system/QCallStackTrace_Test.cpp
	$(CXX) $(COMPILEROPTIONS_DEBUGMAC32SHAREDRTSTATIC) $(INCLUDES_DEBUGMAC32SHAREDRTSTATIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_system/QCallStackTrace_Test.cpp -o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_system.QCallStackTrace_Test.o

$(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_system.QThread_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_system/QThread_Test.cpp
	$(CXX) $(COMPILEROPTIONS_DEBUGMAC32SHAREDRTSTATIC) $(INCLUDES_DEBUGMAC32SHAREDRTSTATIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_system/QThread_Test.cpp -o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_system.QThread_Test.o

$(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_system.SQThisThread_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_system/SQThisThread_Test.cpp
	$(CXX) $(COMPILEROPTIONS_DEBUGMAC32SHAREDRTSTATIC) $(INCLUDES_DEBUGMAC32SHAREDRTSTATIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_system/SQThisThread_Test.cpp -o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_system.SQThisThread_Test.o

$(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTSTATIC)__.__.__.testsystem.EQTestType.o: $(EXECUTION_PATH)../../../testsystem/EQTestType.cpp
	$(CXX) $(COMPILEROPTIONS_DEBUGMAC32SHAREDRTSTATIC) $(INCLUDES_DEBUGMAC32SHAREDRTSTATIC) -c $(EXECUTION_PATH)../../../testsystem/EQTestType.cpp -o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTSTATIC)__.__.__.testsystem.EQTestType.o

$(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTSTATIC)__.__.__.testsystem.QCommonTestConfig.o: $(EXECUTION_PATH)../../../testsystem/QCommonTestConfig.cpp
	$(CXX) $(COMPILEROPTIONS_DEBUGMAC32SHAREDRTSTATIC) $(INCLUDES_DEBUGMAC32SHAREDRTSTATIC) -c $(EXECUTION_PATH)../../../testsystem/QCommonTestConfig.cpp -o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTSTATIC)__.__.__.testsystem.QCommonTestConfig.o

$(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTSTATIC)__.__.__.testsystem.QSimpleConfigLoader.o: $(EXECUTION_PATH)../../../testsystem/QSimpleConfigLoader.cpp
	$(CXX) $(COMPILEROPTIONS_DEBUGMAC32SHAREDRTSTATIC) $(INCLUDES_DEBUGMAC32SHAREDRTSTATIC) -c $(EXECUTION_PATH)../../../testsystem/QSimpleConfigLoader.cpp -o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTSTATIC)__.__.__.testsystem.QSimpleConfigLoader.o

postbuildDebugMac32SharedrtStatic:
	if test -d "$(EXECUTION_PATH)../../../bin/Clang/DebugMac32SharedrtStatic/artifacts/"; then rm -rf "$(EXECUTION_PATH)../../../bin/Clang/DebugMac32SharedrtStatic/artifacts/"; fi
	rsync -a --exclude='.*' $(EXECUTION_PATH)../../../bin/artifacts/artifacts $(EXECUTION_PATH)../../../bin/Clang/DebugMac32SharedrtStatic


buildDebugMac32SharedrtStatic: prebuildDebugMac32SharedrtStatic DebugMac32SharedrtStatic postbuildDebugMac32SharedrtStatic

cleanDebugMac32SharedrtStatic:
	rm -f $(OBJECTS_DEBUGMAC32SHAREDRTSTATIC)
	rm -f $(OUTPUT_DEBUGMAC32SHAREDRTSTATIC)
	test -d $(EXECUTION_PATH)../../../bin/Clang/DebugMac32SharedrtStatic rmdir "$(EXECUTION_PATH)..\..\..\bin\Clang\DebugMac32SharedrtStatic"
	test -d $(EXECUTION_PATH)../../../garbage/Clang/DebugMac32SharedrtStatic rmdir "$(EXECUTION_PATH)..\..\..\garbage\Clang\DebugMac32SharedrtStatic"


#------------------------------------------------------------
#------------- DebugWin32SharedrtDynamic --------------
#------------------------------------------------------------
INCLUDES_DEBUGWIN32SHAREDRTDYNAMIC = $(INCLUDES_GLOBAL) -I$(EXECUTION_PATH)../../../../headers -I$(EXECUTION_PATH)../../../tests/unit/testmodule_system -I$(EXECUTION_PATH)../../../tests/unit -I$(EXECUTION_PATH)../../../../3rdparty/ICU/include
LIBRARYDIRS_DEBUGWIN32SHAREDRTDYNAMIC = $(LIBRARYDIRS_GLOBAL) -L$(EXECUTION_PATH)../../../../3rdparty/Boost/bin/Win32/DebugSharedrtStatic -L$(EXECUTION_PATH)../../../../3rdparty/ICU/bin/Win32/ReleaseSharedrtDynamic/MinGW -L$(EXECUTION_PATH)../../../../bin/MinGW/DebugWin32SharedrtDynamic
LIBRARIES_DEBUGWIN32SHAREDRTDYNAMIC = $(LIBRARIES_GLOBAL) -lQuimeraEngineSystem -lQuimeraEngineTools -lQuimeraEngineCommon -lboost_thread-mt-d -lboost_system-mt-d -lboost_filesystem-mt-d -lboost_unit_test_framework-mt-d -licudt -licuuc -licuin
COMPILEROPTIONS_DEBUGWIN32SHAREDRTDYNAMIC = $(COMPILEROPTIONS_GLOBAL) -g -O0 -Wall -Wno-comment -Wno-unused-local-typedefs -m32 -isystem $(EXECUTION_PATH)../../../../3rdparty/Boost/include
LINKEROPTIONS_DEBUGWIN32SHAREDRTDYNAMIC = $(LINKEROPTIONS_GLOBAL) -m32
DEFINITIONS_DEBUGWIN32SHAREDRTDYNAMIC = $(DEFINITIONS_GLOBAL) -DQE_PREPROCESSOR_IMPORTLIB_QUIMERAENGINE
OUTPUT_DEBUGWIN32SHAREDRTDYNAMIC = $(EXECUTION_PATH)../../../bin/MinGW/DebugWin32SharedrtDynamic/Unit_TestModule_System.exe
INTERMEDIARYDIR_DEBUGWIN32SHAREDRTDYNAMIC = $(EXECUTION_PATH)../../../garbage/MinGW/DebugWin32SharedrtDynamic/
OBJECTS_DEBUGWIN32SHAREDRTDYNAMIC = $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_system.TestModule_System.o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_system.QObject_Test.o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_system.QLocalTimeZone_Test.o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_system.QDateTimeNow_Test.o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_system.QStopwatch_Test.o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_system.QMemoryStream_Test.o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_system.QUri_Test.o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_system.QBinaryStreamReader_Test.o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_system.QBinaryStreamWriter_Test.o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_system.QTextStreamReader_Test.o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_system.QPath_Test.o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_system.SQDirectory_Test.o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_system.SQFile_Test.o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_system.QFileStream_Test.o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_system.QDerivedFromObject.o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_system.SQAnyTypeToStringConverter_Test.o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_system.SQTypeExtensions_Test.o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_system.QArgumentTrace_Test.o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_system.QCallTrace_Test.o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_system.QCallStackTrace_Test.o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_system.QThread_Test.o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_system.SQThisThread_Test.o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTDYNAMIC)__.__.__.testsystem.EQTestType.o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTDYNAMIC)__.__.__.testsystem.QCommonTestConfig.o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTDYNAMIC)__.__.__.testsystem.QSimpleConfigLoader.o

prebuildDebugWin32SharedrtDynamic:
	cmd /c if not exist $(EXECUTION_PATH)..\..\..\bin\MinGW\DebugWin32SharedrtDynamic mkdir "$(EXECUTION_PATH)..\..\..\bin\MinGW\DebugWin32SharedrtDynamic"
	cmd /c if not exist $(EXECUTION_PATH)..\..\..\garbage\MinGW\DebugWin32SharedrtDynamic mkdir "$(EXECUTION_PATH)..\..\..\garbage\MinGW\DebugWin32SharedrtDynamic"


DebugWin32SharedrtDynamic: $(OBJECTS_DEBUGWIN32SHAREDRTDYNAMIC)
	$(LD) $(LINKEROPTIONS_DEBUGWIN32SHAREDRTDYNAMIC) $(LIBRARYDIRS_DEBUGWIN32SHAREDRTDYNAMIC) $(OBJECTS_DEBUGWIN32SHAREDRTDYNAMIC) $(LIBRARIES_DEBUGWIN32SHAREDRTDYNAMIC) -o $(OUTPUT_DEBUGWIN32SHAREDRTDYNAMIC)

$(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_system.TestModule_System.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_system/TestModule_System.cpp
	$(CXX) $(COMPILEROPTIONS_DEBUGWIN32SHAREDRTDYNAMIC) $(INCLUDES_DEBUGWIN32SHAREDRTDYNAMIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_system/TestModule_System.cpp -o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_system.TestModule_System.o

$(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_system.QObject_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_system/QObject_Test.cpp
	$(CXX) $(COMPILEROPTIONS_DEBUGWIN32SHAREDRTDYNAMIC) $(INCLUDES_DEBUGWIN32SHAREDRTDYNAMIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_system/QObject_Test.cpp -o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_system.QObject_Test.o

$(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_system.QLocalTimeZone_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_system/QLocalTimeZone_Test.cpp
	$(CXX) $(COMPILEROPTIONS_DEBUGWIN32SHAREDRTDYNAMIC) $(INCLUDES_DEBUGWIN32SHAREDRTDYNAMIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_system/QLocalTimeZone_Test.cpp -o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_system.QLocalTimeZone_Test.o

$(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_system.QDateTimeNow_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_system/QDateTimeNow_Test.cpp
	$(CXX) $(COMPILEROPTIONS_DEBUGWIN32SHAREDRTDYNAMIC) $(INCLUDES_DEBUGWIN32SHAREDRTDYNAMIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_system/QDateTimeNow_Test.cpp -o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_system.QDateTimeNow_Test.o

$(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_system.QStopwatch_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_system/QStopwatch_Test.cpp
	$(CXX) $(COMPILEROPTIONS_DEBUGWIN32SHAREDRTDYNAMIC) $(INCLUDES_DEBUGWIN32SHAREDRTDYNAMIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_system/QStopwatch_Test.cpp -o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_system.QStopwatch_Test.o

$(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_system.QMemoryStream_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_system/QMemoryStream_Test.cpp
	$(CXX) $(COMPILEROPTIONS_DEBUGWIN32SHAREDRTDYNAMIC) $(INCLUDES_DEBUGWIN32SHAREDRTDYNAMIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_system/QMemoryStream_Test.cpp -o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_system.QMemoryStream_Test.o

$(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_system.QUri_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_system/QUri_Test.cpp
	$(CXX) $(COMPILEROPTIONS_DEBUGWIN32SHAREDRTDYNAMIC) $(INCLUDES_DEBUGWIN32SHAREDRTDYNAMIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_system/QUri_Test.cpp -o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_system.QUri_Test.o

$(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_system.QBinaryStreamReader_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_system/QBinaryStreamReader_Test.cpp
	$(CXX) $(COMPILEROPTIONS_DEBUGWIN32SHAREDRTDYNAMIC) $(INCLUDES_DEBUGWIN32SHAREDRTDYNAMIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_system/QBinaryStreamReader_Test.cpp -o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_system.QBinaryStreamReader_Test.o

$(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_system.QBinaryStreamWriter_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_system/QBinaryStreamWriter_Test.cpp
	$(CXX) $(COMPILEROPTIONS_DEBUGWIN32SHAREDRTDYNAMIC) $(INCLUDES_DEBUGWIN32SHAREDRTDYNAMIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_system/QBinaryStreamWriter_Test.cpp -o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_system.QBinaryStreamWriter_Test.o

$(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_system.QTextStreamReader_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_system/QTextStreamReader_Test.cpp
	$(CXX) $(COMPILEROPTIONS_DEBUGWIN32SHAREDRTDYNAMIC) $(INCLUDES_DEBUGWIN32SHAREDRTDYNAMIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_system/QTextStreamReader_Test.cpp -o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_system.QTextStreamReader_Test.o

$(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_system.QPath_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_system/QPath_Test.cpp
	$(CXX) $(COMPILEROPTIONS_DEBUGWIN32SHAREDRTDYNAMIC) $(INCLUDES_DEBUGWIN32SHAREDRTDYNAMIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_system/QPath_Test.cpp -o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_system.QPath_Test.o

$(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_system.SQDirectory_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_system/SQDirectory_Test.cpp
	$(CXX) $(COMPILEROPTIONS_DEBUGWIN32SHAREDRTDYNAMIC) $(INCLUDES_DEBUGWIN32SHAREDRTDYNAMIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_system/SQDirectory_Test.cpp -o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_system.SQDirectory_Test.o

$(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_system.SQFile_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_system/SQFile_Test.cpp
	$(CXX) $(COMPILEROPTIONS_DEBUGWIN32SHAREDRTDYNAMIC) $(INCLUDES_DEBUGWIN32SHAREDRTDYNAMIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_system/SQFile_Test.cpp -o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_system.SQFile_Test.o

$(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_system.QFileStream_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_system/QFileStream_Test.cpp
	$(CXX) $(COMPILEROPTIONS_DEBUGWIN32SHAREDRTDYNAMIC) $(INCLUDES_DEBUGWIN32SHAREDRTDYNAMIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_system/QFileStream_Test.cpp -o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_system.QFileStream_Test.o

$(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_system.QDerivedFromObject.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_system/QDerivedFromObject.cpp
	$(CXX) $(COMPILEROPTIONS_DEBUGWIN32SHAREDRTDYNAMIC) $(INCLUDES_DEBUGWIN32SHAREDRTDYNAMIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_system/QDerivedFromObject.cpp -o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_system.QDerivedFromObject.o

$(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_system.SQAnyTypeToStringConverter_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_system/SQAnyTypeToStringConverter_Test.cpp
	$(CXX) $(COMPILEROPTIONS_DEBUGWIN32SHAREDRTDYNAMIC) $(INCLUDES_DEBUGWIN32SHAREDRTDYNAMIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_system/SQAnyTypeToStringConverter_Test.cpp -o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_system.SQAnyTypeToStringConverter_Test.o

$(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_system.SQTypeExtensions_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_system/SQTypeExtensions_Test.cpp
	$(CXX) $(COMPILEROPTIONS_DEBUGWIN32SHAREDRTDYNAMIC) $(INCLUDES_DEBUGWIN32SHAREDRTDYNAMIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_system/SQTypeExtensions_Test.cpp -o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_system.SQTypeExtensions_Test.o

$(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_system.QArgumentTrace_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_system/QArgumentTrace_Test.cpp
	$(CXX) $(COMPILEROPTIONS_DEBUGWIN32SHAREDRTDYNAMIC) $(INCLUDES_DEBUGWIN32SHAREDRTDYNAMIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_system/QArgumentTrace_Test.cpp -o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_system.QArgumentTrace_Test.o

$(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_system.QCallTrace_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_system/QCallTrace_Test.cpp
	$(CXX) $(COMPILEROPTIONS_DEBUGWIN32SHAREDRTDYNAMIC) $(INCLUDES_DEBUGWIN32SHAREDRTDYNAMIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_system/QCallTrace_Test.cpp -o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_system.QCallTrace_Test.o

$(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_system.QCallStackTrace_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_system/QCallStackTrace_Test.cpp
	$(CXX) $(COMPILEROPTIONS_DEBUGWIN32SHAREDRTDYNAMIC) $(INCLUDES_DEBUGWIN32SHAREDRTDYNAMIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_system/QCallStackTrace_Test.cpp -o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_system.QCallStackTrace_Test.o

$(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_system.QThread_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_system/QThread_Test.cpp
	$(CXX) $(COMPILEROPTIONS_DEBUGWIN32SHAREDRTDYNAMIC) $(INCLUDES_DEBUGWIN32SHAREDRTDYNAMIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_system/QThread_Test.cpp -o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_system.QThread_Test.o

$(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_system.SQThisThread_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_system/SQThisThread_Test.cpp
	$(CXX) $(COMPILEROPTIONS_DEBUGWIN32SHAREDRTDYNAMIC) $(INCLUDES_DEBUGWIN32SHAREDRTDYNAMIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_system/SQThisThread_Test.cpp -o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_system.SQThisThread_Test.o

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
	cmd /c copy "$(EXECUTION_PATH)..\..\..\..\bin\MinGW\DebugWin32SharedrtDynamic\QuimeraEngineTools.dll" "$(EXECUTION_PATH)..\..\..\bin\MinGW\DebugWin32SharedrtDynamic" /Y
	cmd /c copy "$(EXECUTION_PATH)..\..\..\..\bin\MinGW\DebugWin32SharedrtDynamic\QuimeraEngineSystem.dll" "$(EXECUTION_PATH)..\..\..\bin\MinGW\DebugWin32SharedrtDynamic" /Y
	cmd /c if exist $(EXECUTION_PATH)..\..\..\bin\MinGW\DebugWin32SharedrtDynamic\artifacts rmdir $(EXECUTION_PATH)..\..\..\bin\MinGW\DebugWin32SharedrtDynamic\artifacts /s /q
	cmd /c xcopy $(EXECUTION_PATH)..\..\..\bin\artifacts $(EXECUTION_PATH)..\..\..\bin\MinGW\DebugWin32SharedrtDynamic /Y /I /E /K /O


buildDebugWin32SharedrtDynamic: prebuildDebugWin32SharedrtDynamic DebugWin32SharedrtDynamic postbuildDebugWin32SharedrtDynamic

cleanDebugWin32SharedrtDynamic:
	rm -f $(OBJECTS_DEBUGWIN32SHAREDRTDYNAMIC)
	rm -f $(OUTPUT_DEBUGWIN32SHAREDRTDYNAMIC)
	cmd /c if exist $(EXECUTION_PATH)..\..\..\bin\MinGW\DebugWin32SharedrtDynamic rmdir "$(EXECUTION_PATH)..\..\..\bin\MinGW\DebugWin32SharedrtDynamic" /s /q
	cmd /c if exist $(EXECUTION_PATH)..\..\..\garbage\MinGW\DebugWin32SharedrtDynamic rmdir "$(EXECUTION_PATH)..\..\..\garbage\MinGW\DebugWin32SharedrtDynamic" /s /q


#------------------------------------------------------------
#------------- DebugWin32SharedrtStatic --------------
#------------------------------------------------------------
INCLUDES_DEBUGWIN32SHAREDRTSTATIC = $(INCLUDES_GLOBAL) -I$(EXECUTION_PATH)../../../../headers -I$(EXECUTION_PATH)../../../tests/unit/testmodule_system -I$(EXECUTION_PATH)../../../tests/unit -I$(EXECUTION_PATH)../../../../3rdparty/ICU/include
LIBRARYDIRS_DEBUGWIN32SHAREDRTSTATIC = $(LIBRARYDIRS_GLOBAL) -L$(EXECUTION_PATH)../../../../3rdparty/Boost/bin/Win32/DebugSharedrtStatic -L$(EXECUTION_PATH)../../../../3rdparty/ICU/bin/Win32/ReleaseSharedrtDynamic/MinGW -L$(EXECUTION_PATH)../../../../bin/MinGW/DebugWin32SharedrtStatic
LIBRARIES_DEBUGWIN32SHAREDRTSTATIC = $(LIBRARIES_GLOBAL) -lQuimeraEngineSystem -lQuimeraEngineTools -lQuimeraEngineCommon -lboost_thread-mt-d -lboost_system-mt-d -lboost_filesystem-mt-d -lboost_chrono-mt-d -lboost_unit_test_framework-mt-d -licudt -licuuc -licuin
COMPILEROPTIONS_DEBUGWIN32SHAREDRTSTATIC = $(COMPILEROPTIONS_GLOBAL) -g -O0 -Wall -Wno-comment -Wno-unused-local-typedefs -m32 -mwindows -isystem $(EXECUTION_PATH)../../../../3rdparty/Boost/include
LINKEROPTIONS_DEBUGWIN32SHAREDRTSTATIC = $(LINKEROPTIONS_GLOBAL) -m32 -mwindows
DEFINITIONS_DEBUGWIN32SHAREDRTSTATIC = $(DEFINITIONS_GLOBAL)
OUTPUT_DEBUGWIN32SHAREDRTSTATIC = $(EXECUTION_PATH)../../../bin/MinGW/DebugWin32SharedrtStatic/Unit_TestModule_System.exe
INTERMEDIARYDIR_DEBUGWIN32SHAREDRTSTATIC = $(EXECUTION_PATH)../../../garbage/MinGW/DebugWin32SharedrtStatic/
OBJECTS_DEBUGWIN32SHAREDRTSTATIC = $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_system.TestModule_System.o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_system.QObject_Test.o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_system.QLocalTimeZone_Test.o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_system.QDateTimeNow_Test.o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_system.QStopwatch_Test.o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_system.QMemoryStream_Test.o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_system.QUri_Test.o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_system.QBinaryStreamReader_Test.o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_system.QBinaryStreamWriter_Test.o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_system.QTextStreamReader_Test.o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_system.QPath_Test.o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_system.SQDirectory_Test.o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_system.SQFile_Test.o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_system.QFileStream_Test.o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_system.QDerivedFromObject.o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_system.SQAnyTypeToStringConverter_Test.o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_system.SQTypeExtensions_Test.o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_system.QArgumentTrace_Test.o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_system.QCallTrace_Test.o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_system.QCallStackTrace_Test.o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_system.QThread_Test.o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_system.SQThisThread_Test.o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTSTATIC)__.__.__.testsystem.EQTestType.o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTSTATIC)__.__.__.testsystem.QCommonTestConfig.o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTSTATIC)__.__.__.testsystem.QSimpleConfigLoader.o

prebuildDebugWin32SharedrtStatic:
	cmd /c if not exist $(EXECUTION_PATH)..\..\..\bin\MinGW\DebugWin32SharedrtStatic mkdir "$(EXECUTION_PATH)..\..\..\bin\MinGW\DebugWin32SharedrtStatic"
	cmd /c if not exist $(EXECUTION_PATH)..\..\..\garbage\MinGW\DebugWin32SharedrtStatic mkdir "$(EXECUTION_PATH)..\..\..\garbage\MinGW\DebugWin32SharedrtStatic"


DebugWin32SharedrtStatic: $(OBJECTS_DEBUGWIN32SHAREDRTSTATIC)
	$(LD) $(LINKEROPTIONS_DEBUGWIN32SHAREDRTSTATIC) $(LIBRARYDIRS_DEBUGWIN32SHAREDRTSTATIC) $(OBJECTS_DEBUGWIN32SHAREDRTSTATIC) $(LIBRARIES_DEBUGWIN32SHAREDRTSTATIC) -o $(OUTPUT_DEBUGWIN32SHAREDRTSTATIC)

$(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_system.TestModule_System.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_system/TestModule_System.cpp
	$(CXX) $(COMPILEROPTIONS_DEBUGWIN32SHAREDRTSTATIC) $(INCLUDES_DEBUGWIN32SHAREDRTSTATIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_system/TestModule_System.cpp -o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_system.TestModule_System.o

$(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_system.QObject_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_system/QObject_Test.cpp
	$(CXX) $(COMPILEROPTIONS_DEBUGWIN32SHAREDRTSTATIC) $(INCLUDES_DEBUGWIN32SHAREDRTSTATIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_system/QObject_Test.cpp -o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_system.QObject_Test.o

$(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_system.QLocalTimeZone_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_system/QLocalTimeZone_Test.cpp
	$(CXX) $(COMPILEROPTIONS_DEBUGWIN32SHAREDRTSTATIC) $(INCLUDES_DEBUGWIN32SHAREDRTSTATIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_system/QLocalTimeZone_Test.cpp -o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_system.QLocalTimeZone_Test.o

$(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_system.QDateTimeNow_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_system/QDateTimeNow_Test.cpp
	$(CXX) $(COMPILEROPTIONS_DEBUGWIN32SHAREDRTSTATIC) $(INCLUDES_DEBUGWIN32SHAREDRTSTATIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_system/QDateTimeNow_Test.cpp -o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_system.QDateTimeNow_Test.o

$(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_system.QStopwatch_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_system/QStopwatch_Test.cpp
	$(CXX) $(COMPILEROPTIONS_DEBUGWIN32SHAREDRTSTATIC) $(INCLUDES_DEBUGWIN32SHAREDRTSTATIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_system/QStopwatch_Test.cpp -o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_system.QStopwatch_Test.o

$(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_system.QMemoryStream_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_system/QMemoryStream_Test.cpp
	$(CXX) $(COMPILEROPTIONS_DEBUGWIN32SHAREDRTSTATIC) $(INCLUDES_DEBUGWIN32SHAREDRTSTATIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_system/QMemoryStream_Test.cpp -o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_system.QMemoryStream_Test.o

$(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_system.QUri_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_system/QUri_Test.cpp
	$(CXX) $(COMPILEROPTIONS_DEBUGWIN32SHAREDRTSTATIC) $(INCLUDES_DEBUGWIN32SHAREDRTSTATIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_system/QUri_Test.cpp -o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_system.QUri_Test.o

$(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_system.QBinaryStreamReader_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_system/QBinaryStreamReader_Test.cpp
	$(CXX) $(COMPILEROPTIONS_DEBUGWIN32SHAREDRTSTATIC) $(INCLUDES_DEBUGWIN32SHAREDRTSTATIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_system/QBinaryStreamReader_Test.cpp -o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_system.QBinaryStreamReader_Test.o

$(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_system.QBinaryStreamWriter_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_system/QBinaryStreamWriter_Test.cpp
	$(CXX) $(COMPILEROPTIONS_DEBUGWIN32SHAREDRTSTATIC) $(INCLUDES_DEBUGWIN32SHAREDRTSTATIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_system/QBinaryStreamWriter_Test.cpp -o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_system.QBinaryStreamWriter_Test.o

$(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_system.QTextStreamReader_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_system/QTextStreamReader_Test.cpp
	$(CXX) $(COMPILEROPTIONS_DEBUGWIN32SHAREDRTSTATIC) $(INCLUDES_DEBUGWIN32SHAREDRTSTATIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_system/QTextStreamReader_Test.cpp -o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_system.QTextStreamReader_Test.o

$(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_system.QPath_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_system/QPath_Test.cpp
	$(CXX) $(COMPILEROPTIONS_DEBUGWIN32SHAREDRTSTATIC) $(INCLUDES_DEBUGWIN32SHAREDRTSTATIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_system/QPath_Test.cpp -o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_system.QPath_Test.o

$(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_system.SQDirectory_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_system/SQDirectory_Test.cpp
	$(CXX) $(COMPILEROPTIONS_DEBUGWIN32SHAREDRTSTATIC) $(INCLUDES_DEBUGWIN32SHAREDRTSTATIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_system/SQDirectory_Test.cpp -o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_system.SQDirectory_Test.o

$(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_system.SQFile_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_system/SQFile_Test.cpp
	$(CXX) $(COMPILEROPTIONS_DEBUGWIN32SHAREDRTSTATIC) $(INCLUDES_DEBUGWIN32SHAREDRTSTATIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_system/SQFile_Test.cpp -o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_system.SQFile_Test.o

$(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_system.QFileStream_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_system/QFileStream_Test.cpp
	$(CXX) $(COMPILEROPTIONS_DEBUGWIN32SHAREDRTSTATIC) $(INCLUDES_DEBUGWIN32SHAREDRTSTATIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_system/QFileStream_Test.cpp -o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_system.QFileStream_Test.o

$(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_system.QDerivedFromObject.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_system/QDerivedFromObject.cpp
	$(CXX) $(COMPILEROPTIONS_DEBUGWIN32SHAREDRTSTATIC) $(INCLUDES_DEBUGWIN32SHAREDRTSTATIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_system/QDerivedFromObject.cpp -o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_system.QDerivedFromObject.o

$(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_system.SQAnyTypeToStringConverter_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_system/SQAnyTypeToStringConverter_Test.cpp
	$(CXX) $(COMPILEROPTIONS_DEBUGWIN32SHAREDRTSTATIC) $(INCLUDES_DEBUGWIN32SHAREDRTSTATIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_system/SQAnyTypeToStringConverter_Test.cpp -o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_system.SQAnyTypeToStringConverter_Test.o

$(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_system.SQTypeExtensions_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_system/SQTypeExtensions_Test.cpp
	$(CXX) $(COMPILEROPTIONS_DEBUGWIN32SHAREDRTSTATIC) $(INCLUDES_DEBUGWIN32SHAREDRTSTATIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_system/SQTypeExtensions_Test.cpp -o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_system.SQTypeExtensions_Test.o

$(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_system.QArgumentTrace_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_system/QArgumentTrace_Test.cpp
	$(CXX) $(COMPILEROPTIONS_DEBUGWIN32SHAREDRTSTATIC) $(INCLUDES_DEBUGWIN32SHAREDRTSTATIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_system/QArgumentTrace_Test.cpp -o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_system.QArgumentTrace_Test.o

$(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_system.QCallTrace_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_system/QCallTrace_Test.cpp
	$(CXX) $(COMPILEROPTIONS_DEBUGWIN32SHAREDRTSTATIC) $(INCLUDES_DEBUGWIN32SHAREDRTSTATIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_system/QCallTrace_Test.cpp -o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_system.QCallTrace_Test.o

$(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_system.QCallStackTrace_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_system/QCallStackTrace_Test.cpp
	$(CXX) $(COMPILEROPTIONS_DEBUGWIN32SHAREDRTSTATIC) $(INCLUDES_DEBUGWIN32SHAREDRTSTATIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_system/QCallStackTrace_Test.cpp -o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_system.QCallStackTrace_Test.o

$(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_system.QThread_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_system/QThread_Test.cpp
	$(CXX) $(COMPILEROPTIONS_DEBUGWIN32SHAREDRTSTATIC) $(INCLUDES_DEBUGWIN32SHAREDRTSTATIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_system/QThread_Test.cpp -o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_system.QThread_Test.o

$(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_system.SQThisThread_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_system/SQThisThread_Test.cpp
	$(CXX) $(COMPILEROPTIONS_DEBUGWIN32SHAREDRTSTATIC) $(INCLUDES_DEBUGWIN32SHAREDRTSTATIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_system/SQThisThread_Test.cpp -o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_system.SQThisThread_Test.o

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
	cmd /c if exist $(EXECUTION_PATH)..\..\..\bin\MinGW\DebugWin32SharedrtStatic\artifacts rmdir $(EXECUTION_PATH)..\..\..\bin\MinGW\DebugWin32SharedrtStatic\artifacts /s /q
	cmd /c xcopy $(EXECUTION_PATH)..\..\..\bin\artifacts $(EXECUTION_PATH)..\..\..\bin\MinGW\DebugWin32SharedrtStatic /Y /I /E /K /O


buildDebugWin32SharedrtStatic: prebuildDebugWin32SharedrtStatic DebugWin32SharedrtStatic postbuildDebugWin32SharedrtStatic

cleanDebugWin32SharedrtStatic:
	rm -f $(OBJECTS_DEBUGWIN32SHAREDRTSTATIC)
	rm -f $(OUTPUT_DEBUGWIN32SHAREDRTSTATIC)
	cmd /c if exist $(EXECUTION_PATH)..\..\..\bin\MinGW\DebugWin32SharedrtStatic rmdir "$(EXECUTION_PATH)..\..\..\bin\MinGW\DebugWin32SharedrtStatic" /s /q
	cmd /c if exist $(EXECUTION_PATH)..\..\..\garbage\MinGW\DebugWin32SharedrtStatic rmdir "$(EXECUTION_PATH)..\..\..\garbage\MinGW\DebugWin32SharedrtStatic" /s /q



.PHONY:buildDebugLinux32SharedrtDynamic prebuildDebugLinux32SharedrtDynamic DebugLinux32SharedrtDynamic postbuildDebugLinux32SharedrtDynamic cleanDebugLinux32SharedrtDynamic buildDebugLinux32SharedrtStatic prebuildDebugLinux32SharedrtStatic DebugLinux32SharedrtStatic postbuildDebugLinux32SharedrtStatic cleanDebugLinux32SharedrtStatic buildDebugMac32SharedrtDynamic prebuildDebugMac32SharedrtDynamic DebugMac32SharedrtDynamic postbuildDebugMac32SharedrtDynamic cleanDebugMac32SharedrtDynamic buildDebugMac32SharedrtStatic prebuildDebugMac32SharedrtStatic DebugMac32SharedrtStatic postbuildDebugMac32SharedrtStatic cleanDebugMac32SharedrtStatic buildDebugWin32SharedrtDynamic prebuildDebugWin32SharedrtDynamic DebugWin32SharedrtDynamic postbuildDebugWin32SharedrtDynamic cleanDebugWin32SharedrtDynamic buildDebugWin32SharedrtStatic prebuildDebugWin32SharedrtStatic DebugWin32SharedrtStatic postbuildDebugWin32SharedrtStatic cleanDebugWin32SharedrtStatic 