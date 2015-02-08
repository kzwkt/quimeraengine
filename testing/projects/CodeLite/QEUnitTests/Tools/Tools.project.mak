#------------------------------------------------------------------------------------------------------------#
#------------------------------------Tools------------------------------------#
#------------------------------------------------------------------------------------------------------------#

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
CXX_DEBUGLINUX32SHAREDRTDYNAMIC = g++
AR_DEBUGLINUX32SHAREDRTDYNAMIC = ar
LD_DEBUGLINUX32SHAREDRTDYNAMIC = g++
AS_DEBUGLINUX32SHAREDRTDYNAMIC = as
INCLUDES_DEBUGLINUX32SHAREDRTDYNAMIC = $(INCLUDES_GLOBAL) -I$(EXECUTION_PATH)../../../../headers -I$(EXECUTION_PATH)../../../tests/unit/testmodule_tools -I$(EXECUTION_PATH)../../../tests/unit -I$(EXECUTION_PATH)../../../../3rdparty/ICU/include
LIBRARYDIRS_DEBUGLINUX32SHAREDRTDYNAMIC = $(LIBRARYDIRS_GLOBAL) -L$(EXECUTION_PATH)../../../../3rdparty/Boost/bin/Linux32/DebugSharedrtStatic -L$(EXECUTION_PATH)../../../../bin/GCC/DebugLinux32SharedrtDynamic
LIBRARIES_DEBUGLINUX32SHAREDRTDYNAMIC = $(LIBRARIES_GLOBAL) -lQuimeraEngineTools -lQuimeraEngineCommon -lboost_unit_test_framework-mt-d -licudata -licuuc -licui18n
COMPILEROPTIONS_DEBUGLINUX32SHAREDRTDYNAMIC = $(COMPILEROPTIONS_GLOBAL) -g -O0 -Wall -Wno-comment -Wno-unused-local-typedefs -m32 -isystem $(EXECUTION_PATH)../../../../3rdparty/Boost/include
LINKEROPTIONS_DEBUGLINUX32SHAREDRTDYNAMIC = $(LINKEROPTIONS_GLOBAL) -m32
DEFINITIONS_DEBUGLINUX32SHAREDRTDYNAMIC = $(DEFINITIONS_GLOBAL) -DQE_PREPROCESSOR_IMPORTLIB_QUIMERAENGINE -DBOOST_NO_RTTI -DBOOST_NO_TYPEID
OUTPUT_DEBUGLINUX32SHAREDRTDYNAMIC = $(EXECUTION_PATH)../../../bin/GCC/DebugLinux32SharedrtDynamic/Unit_TestModule_Tools.sh
INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTDYNAMIC = $(EXECUTION_PATH)../../../garbage/GCC/DebugLinux32SharedrtDynamic/
OBJECTS_DEBUGLINUX32SHAREDRTDYNAMIC = $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.TestModule_Tools.o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QArrayIterator_Test.o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QList_Test.o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QListIterator_Test.o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QNTree_Test.o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.CallCounter.o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QNTreeIterator_Test.o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QBinarySearchTree_Test.o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QConstArrayIterator_Test.o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QConstListIterator_Test.o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QConstNTreeIterator_Test.o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QConstBinarySearchTreeIterator_Test.o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.SQComparatorDefault_Test.o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QKeyValuePair_Test.o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.SQKeyValuePairComparator_Test.o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.SQEqualityComparator_Test.o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QDictionary_Test.o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QHashtable_Test.o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.SQIntegerHashProvider_Test.o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.SQStringHashProvider_Test.o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QConstDictionaryIterator_Test.o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QConstHashtableIterator_Test.o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QArrayDynamic_Test.o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QArrayFixed_Test.o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QDateTime_Test.o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QDstInformation_Test.o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QTimeSpan_Test.o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QTimeZone_Test.o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.SQTimeZoneFactory_Test.o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QBaseDualQuaternion_Test.o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QBaseHexahedron_Test.o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QBaseLineSegment_Test.o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QBaseMatrix2x2_Test.o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QBaseMatrix3x3_Test.o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QBaseMatrix3x4_Test.o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QBaseMatrix4x3_Test.o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QBaseMatrix4x4_Test.o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QBaseOrb_Test.o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QBasePlane_Test.o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QBaseQuadrilateral_Test.o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QBaseQuaternion_Test.o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QBaseRay_QVector4_Test.o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QBaseRay_Test.o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QBaseTriangle_Test.o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QBaseVector2_Test.o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QBaseVector3_Test.o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QBaseVector4_Test.o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QCircle_Test.o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QDualQuaternion_Test.o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QHexahedron_Test.o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QLineSegment2D_Test.o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QLineSegment3D_Test.o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QLineSegment_Test.o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QMatrix2x2_Test.o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QMatrix3x3_Test.o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QMatrix3x4_Test.o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QMatrix4x3_Test.o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QMatrix4x4_Test.o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QOrb_Test.o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QPlane_Test.o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QQuadrilateral_Test.o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QQuaternion_Test.o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QRay2D_Test.o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QRay3D_Test.o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QRay_QVector4_Test.o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QRay_Test.o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QRotationMatrix3x3_Test.o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QScalingMatrix3x3_Test.o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QSpaceConversionMatrix_Test.o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QSphere_Test.o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QTransformationMatrix3x3_Test.o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QTransformationMatrix_Test.o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QTranslationMatrix_Test.o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QTriangle2D_Test.o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QTriangle3D_Test.o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QTriangle_Test.o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QVector2_Test.o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QVector3_Test.o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QVector4_Test.o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.SQAngle_Test.o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.SQPoint_Test.o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QEvent_Test.o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTDYNAMIC)__.__.__.testsystem.EQTestType.o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTDYNAMIC)__.__.__.testsystem.QCommonTestConfig.o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTDYNAMIC)__.__.__.testsystem.QSimpleConfigLoader.o

prebuildDebugLinux32SharedrtDynamic:
	if ! (test -d $(EXECUTION_PATH)../../../bin/GCC/DebugLinux32SharedrtDynamic) then mkdir -p "$(EXECUTION_PATH)../../../bin/GCC/DebugLinux32SharedrtDynamic"; fi
	if ! (test -d $(EXECUTION_PATH)../../../garbage/GCC/DebugLinux32SharedrtDynamic) then mkdir -p "$(EXECUTION_PATH)../../../garbage/GCC/DebugLinux32SharedrtDynamic"; fi
	mkdir -p $(EXECUTION_PATH)../../../bin/GCC/DebugLinux32SharedrtDynamic
	cp "$(EXECUTION_PATH)../../../../bin/GCC/DebugLinux32SharedrtDynamic/libQuimeraEngineCommon.so" "$(EXECUTION_PATH)../../../bin/GCC/DebugLinux32SharedrtDynamic"
	cp "$(EXECUTION_PATH)../../../../bin/GCC/DebugLinux32SharedrtDynamic/libQuimeraEngineCommon.so" "$(EXECUTION_PATH)."
	cp "$(EXECUTION_PATH)../../../../bin/GCC/DebugLinux32SharedrtDynamic/libQuimeraEngineTools.so" "$(EXECUTION_PATH)../../../bin/GCC/DebugLinux32SharedrtDynamic"
	cp "$(EXECUTION_PATH)../../../../bin/GCC/DebugLinux32SharedrtDynamic/libQuimeraEngineTools.so" "$(EXECUTION_PATH)."
	cp "$(EXECUTION_PATH)../../../bin/TestConfig.txt" "$(EXECUTION_PATH)../../../bin/GCC/DebugLinux32SharedrtDynamic"
	cp "$(EXECUTION_PATH)../../../bin/NormalizationTest.txt" "$(EXECUTION_PATH)../../../bin/GCC/DebugLinux32SharedrtDynamic"


DebugLinux32SharedrtDynamic: $(OBJECTS_DEBUGLINUX32SHAREDRTDYNAMIC)
	$(LD_DEBUGLINUX32SHAREDRTDYNAMIC) $(DEFINITIONS_DEBUGLINUX32SHAREDRTDYNAMIC) $(LINKEROPTIONS_DEBUGLINUX32SHAREDRTDYNAMIC) $(LIBRARYDIRS_DEBUGLINUX32SHAREDRTDYNAMIC) $(OBJECTS_DEBUGLINUX32SHAREDRTDYNAMIC) $(LIBRARIES_DEBUGLINUX32SHAREDRTDYNAMIC) -o $(OUTPUT_DEBUGLINUX32SHAREDRTDYNAMIC)

$(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.TestModule_Tools.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/TestModule_Tools.cpp
	$(CXX_DEBUGLINUX32SHAREDRTDYNAMIC) $(COMPILEROPTIONS_DEBUGLINUX32SHAREDRTDYNAMIC) $(DEFINITIONS_DEBUGLINUX32SHAREDRTDYNAMIC) $(INCLUDES_DEBUGLINUX32SHAREDRTDYNAMIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/TestModule_Tools.cpp -o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.TestModule_Tools.o

$(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QArrayIterator_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QArrayIterator_Test.cpp
	$(CXX_DEBUGLINUX32SHAREDRTDYNAMIC) $(COMPILEROPTIONS_DEBUGLINUX32SHAREDRTDYNAMIC) $(DEFINITIONS_DEBUGLINUX32SHAREDRTDYNAMIC) $(INCLUDES_DEBUGLINUX32SHAREDRTDYNAMIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QArrayIterator_Test.cpp -o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QArrayIterator_Test.o

$(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QList_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QList_Test.cpp
	$(CXX_DEBUGLINUX32SHAREDRTDYNAMIC) $(COMPILEROPTIONS_DEBUGLINUX32SHAREDRTDYNAMIC) $(DEFINITIONS_DEBUGLINUX32SHAREDRTDYNAMIC) $(INCLUDES_DEBUGLINUX32SHAREDRTDYNAMIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QList_Test.cpp -o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QList_Test.o

$(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QListIterator_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QListIterator_Test.cpp
	$(CXX_DEBUGLINUX32SHAREDRTDYNAMIC) $(COMPILEROPTIONS_DEBUGLINUX32SHAREDRTDYNAMIC) $(DEFINITIONS_DEBUGLINUX32SHAREDRTDYNAMIC) $(INCLUDES_DEBUGLINUX32SHAREDRTDYNAMIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QListIterator_Test.cpp -o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QListIterator_Test.o

$(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QNTree_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QNTree_Test.cpp
	$(CXX_DEBUGLINUX32SHAREDRTDYNAMIC) $(COMPILEROPTIONS_DEBUGLINUX32SHAREDRTDYNAMIC) $(DEFINITIONS_DEBUGLINUX32SHAREDRTDYNAMIC) $(INCLUDES_DEBUGLINUX32SHAREDRTDYNAMIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QNTree_Test.cpp -o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QNTree_Test.o

$(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.CallCounter.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/CallCounter.cpp
	$(CXX_DEBUGLINUX32SHAREDRTDYNAMIC) $(COMPILEROPTIONS_DEBUGLINUX32SHAREDRTDYNAMIC) $(DEFINITIONS_DEBUGLINUX32SHAREDRTDYNAMIC) $(INCLUDES_DEBUGLINUX32SHAREDRTDYNAMIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/CallCounter.cpp -o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.CallCounter.o

$(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QNTreeIterator_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QNTreeIterator_Test.cpp
	$(CXX_DEBUGLINUX32SHAREDRTDYNAMIC) $(COMPILEROPTIONS_DEBUGLINUX32SHAREDRTDYNAMIC) $(DEFINITIONS_DEBUGLINUX32SHAREDRTDYNAMIC) $(INCLUDES_DEBUGLINUX32SHAREDRTDYNAMIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QNTreeIterator_Test.cpp -o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QNTreeIterator_Test.o

$(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QBinarySearchTree_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QBinarySearchTree_Test.cpp
	$(CXX_DEBUGLINUX32SHAREDRTDYNAMIC) $(COMPILEROPTIONS_DEBUGLINUX32SHAREDRTDYNAMIC) $(DEFINITIONS_DEBUGLINUX32SHAREDRTDYNAMIC) $(INCLUDES_DEBUGLINUX32SHAREDRTDYNAMIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QBinarySearchTree_Test.cpp -o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QBinarySearchTree_Test.o

$(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QConstArrayIterator_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QConstArrayIterator_Test.cpp
	$(CXX_DEBUGLINUX32SHAREDRTDYNAMIC) $(COMPILEROPTIONS_DEBUGLINUX32SHAREDRTDYNAMIC) $(DEFINITIONS_DEBUGLINUX32SHAREDRTDYNAMIC) $(INCLUDES_DEBUGLINUX32SHAREDRTDYNAMIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QConstArrayIterator_Test.cpp -o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QConstArrayIterator_Test.o

$(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QConstListIterator_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QConstListIterator_Test.cpp
	$(CXX_DEBUGLINUX32SHAREDRTDYNAMIC) $(COMPILEROPTIONS_DEBUGLINUX32SHAREDRTDYNAMIC) $(DEFINITIONS_DEBUGLINUX32SHAREDRTDYNAMIC) $(INCLUDES_DEBUGLINUX32SHAREDRTDYNAMIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QConstListIterator_Test.cpp -o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QConstListIterator_Test.o

$(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QConstNTreeIterator_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QConstNTreeIterator_Test.cpp
	$(CXX_DEBUGLINUX32SHAREDRTDYNAMIC) $(COMPILEROPTIONS_DEBUGLINUX32SHAREDRTDYNAMIC) $(DEFINITIONS_DEBUGLINUX32SHAREDRTDYNAMIC) $(INCLUDES_DEBUGLINUX32SHAREDRTDYNAMIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QConstNTreeIterator_Test.cpp -o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QConstNTreeIterator_Test.o

$(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QConstBinarySearchTreeIterator_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QConstBinarySearchTreeIterator_Test.cpp
	$(CXX_DEBUGLINUX32SHAREDRTDYNAMIC) $(COMPILEROPTIONS_DEBUGLINUX32SHAREDRTDYNAMIC) $(DEFINITIONS_DEBUGLINUX32SHAREDRTDYNAMIC) $(INCLUDES_DEBUGLINUX32SHAREDRTDYNAMIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QConstBinarySearchTreeIterator_Test.cpp -o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QConstBinarySearchTreeIterator_Test.o

$(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.SQComparatorDefault_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/SQComparatorDefault_Test.cpp
	$(CXX_DEBUGLINUX32SHAREDRTDYNAMIC) $(COMPILEROPTIONS_DEBUGLINUX32SHAREDRTDYNAMIC) $(DEFINITIONS_DEBUGLINUX32SHAREDRTDYNAMIC) $(INCLUDES_DEBUGLINUX32SHAREDRTDYNAMIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/SQComparatorDefault_Test.cpp -o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.SQComparatorDefault_Test.o

$(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QKeyValuePair_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QKeyValuePair_Test.cpp
	$(CXX_DEBUGLINUX32SHAREDRTDYNAMIC) $(COMPILEROPTIONS_DEBUGLINUX32SHAREDRTDYNAMIC) $(DEFINITIONS_DEBUGLINUX32SHAREDRTDYNAMIC) $(INCLUDES_DEBUGLINUX32SHAREDRTDYNAMIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QKeyValuePair_Test.cpp -o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QKeyValuePair_Test.o

$(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.SQKeyValuePairComparator_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/SQKeyValuePairComparator_Test.cpp
	$(CXX_DEBUGLINUX32SHAREDRTDYNAMIC) $(COMPILEROPTIONS_DEBUGLINUX32SHAREDRTDYNAMIC) $(DEFINITIONS_DEBUGLINUX32SHAREDRTDYNAMIC) $(INCLUDES_DEBUGLINUX32SHAREDRTDYNAMIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/SQKeyValuePairComparator_Test.cpp -o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.SQKeyValuePairComparator_Test.o

$(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.SQEqualityComparator_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/SQEqualityComparator_Test.cpp
	$(CXX_DEBUGLINUX32SHAREDRTDYNAMIC) $(COMPILEROPTIONS_DEBUGLINUX32SHAREDRTDYNAMIC) $(DEFINITIONS_DEBUGLINUX32SHAREDRTDYNAMIC) $(INCLUDES_DEBUGLINUX32SHAREDRTDYNAMIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/SQEqualityComparator_Test.cpp -o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.SQEqualityComparator_Test.o

$(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QDictionary_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QDictionary_Test.cpp
	$(CXX_DEBUGLINUX32SHAREDRTDYNAMIC) $(COMPILEROPTIONS_DEBUGLINUX32SHAREDRTDYNAMIC) $(DEFINITIONS_DEBUGLINUX32SHAREDRTDYNAMIC) $(INCLUDES_DEBUGLINUX32SHAREDRTDYNAMIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QDictionary_Test.cpp -o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QDictionary_Test.o

$(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QHashtable_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QHashtable_Test.cpp
	$(CXX_DEBUGLINUX32SHAREDRTDYNAMIC) $(COMPILEROPTIONS_DEBUGLINUX32SHAREDRTDYNAMIC) $(DEFINITIONS_DEBUGLINUX32SHAREDRTDYNAMIC) $(INCLUDES_DEBUGLINUX32SHAREDRTDYNAMIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QHashtable_Test.cpp -o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QHashtable_Test.o

$(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.SQIntegerHashProvider_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/SQIntegerHashProvider_Test.cpp
	$(CXX_DEBUGLINUX32SHAREDRTDYNAMIC) $(COMPILEROPTIONS_DEBUGLINUX32SHAREDRTDYNAMIC) $(DEFINITIONS_DEBUGLINUX32SHAREDRTDYNAMIC) $(INCLUDES_DEBUGLINUX32SHAREDRTDYNAMIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/SQIntegerHashProvider_Test.cpp -o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.SQIntegerHashProvider_Test.o

$(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.SQStringHashProvider_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/SQStringHashProvider_Test.cpp
	$(CXX_DEBUGLINUX32SHAREDRTDYNAMIC) $(COMPILEROPTIONS_DEBUGLINUX32SHAREDRTDYNAMIC) $(DEFINITIONS_DEBUGLINUX32SHAREDRTDYNAMIC) $(INCLUDES_DEBUGLINUX32SHAREDRTDYNAMIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/SQStringHashProvider_Test.cpp -o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.SQStringHashProvider_Test.o

$(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QConstDictionaryIterator_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QConstDictionaryIterator_Test.cpp
	$(CXX_DEBUGLINUX32SHAREDRTDYNAMIC) $(COMPILEROPTIONS_DEBUGLINUX32SHAREDRTDYNAMIC) $(DEFINITIONS_DEBUGLINUX32SHAREDRTDYNAMIC) $(INCLUDES_DEBUGLINUX32SHAREDRTDYNAMIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QConstDictionaryIterator_Test.cpp -o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QConstDictionaryIterator_Test.o

$(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QConstHashtableIterator_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QConstHashtableIterator_Test.cpp
	$(CXX_DEBUGLINUX32SHAREDRTDYNAMIC) $(COMPILEROPTIONS_DEBUGLINUX32SHAREDRTDYNAMIC) $(DEFINITIONS_DEBUGLINUX32SHAREDRTDYNAMIC) $(INCLUDES_DEBUGLINUX32SHAREDRTDYNAMIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QConstHashtableIterator_Test.cpp -o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QConstHashtableIterator_Test.o

$(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QArrayDynamic_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QArrayDynamic_Test.cpp
	$(CXX_DEBUGLINUX32SHAREDRTDYNAMIC) $(COMPILEROPTIONS_DEBUGLINUX32SHAREDRTDYNAMIC) $(DEFINITIONS_DEBUGLINUX32SHAREDRTDYNAMIC) $(INCLUDES_DEBUGLINUX32SHAREDRTDYNAMIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QArrayDynamic_Test.cpp -o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QArrayDynamic_Test.o

$(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QArrayFixed_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QArrayFixed_Test.cpp
	$(CXX_DEBUGLINUX32SHAREDRTDYNAMIC) $(COMPILEROPTIONS_DEBUGLINUX32SHAREDRTDYNAMIC) $(DEFINITIONS_DEBUGLINUX32SHAREDRTDYNAMIC) $(INCLUDES_DEBUGLINUX32SHAREDRTDYNAMIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QArrayFixed_Test.cpp -o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QArrayFixed_Test.o

$(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QDateTime_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QDateTime_Test.cpp
	$(CXX_DEBUGLINUX32SHAREDRTDYNAMIC) $(COMPILEROPTIONS_DEBUGLINUX32SHAREDRTDYNAMIC) $(DEFINITIONS_DEBUGLINUX32SHAREDRTDYNAMIC) $(INCLUDES_DEBUGLINUX32SHAREDRTDYNAMIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QDateTime_Test.cpp -o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QDateTime_Test.o

$(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QDstInformation_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QDstInformation_Test.cpp
	$(CXX_DEBUGLINUX32SHAREDRTDYNAMIC) $(COMPILEROPTIONS_DEBUGLINUX32SHAREDRTDYNAMIC) $(DEFINITIONS_DEBUGLINUX32SHAREDRTDYNAMIC) $(INCLUDES_DEBUGLINUX32SHAREDRTDYNAMIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QDstInformation_Test.cpp -o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QDstInformation_Test.o

$(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QTimeSpan_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QTimeSpan_Test.cpp
	$(CXX_DEBUGLINUX32SHAREDRTDYNAMIC) $(COMPILEROPTIONS_DEBUGLINUX32SHAREDRTDYNAMIC) $(DEFINITIONS_DEBUGLINUX32SHAREDRTDYNAMIC) $(INCLUDES_DEBUGLINUX32SHAREDRTDYNAMIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QTimeSpan_Test.cpp -o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QTimeSpan_Test.o

$(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QTimeZone_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QTimeZone_Test.cpp
	$(CXX_DEBUGLINUX32SHAREDRTDYNAMIC) $(COMPILEROPTIONS_DEBUGLINUX32SHAREDRTDYNAMIC) $(DEFINITIONS_DEBUGLINUX32SHAREDRTDYNAMIC) $(INCLUDES_DEBUGLINUX32SHAREDRTDYNAMIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QTimeZone_Test.cpp -o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QTimeZone_Test.o

$(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.SQTimeZoneFactory_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/SQTimeZoneFactory_Test.cpp
	$(CXX_DEBUGLINUX32SHAREDRTDYNAMIC) $(COMPILEROPTIONS_DEBUGLINUX32SHAREDRTDYNAMIC) $(DEFINITIONS_DEBUGLINUX32SHAREDRTDYNAMIC) $(INCLUDES_DEBUGLINUX32SHAREDRTDYNAMIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/SQTimeZoneFactory_Test.cpp -o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.SQTimeZoneFactory_Test.o

$(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QBaseDualQuaternion_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QBaseDualQuaternion_Test.cpp
	$(CXX_DEBUGLINUX32SHAREDRTDYNAMIC) $(COMPILEROPTIONS_DEBUGLINUX32SHAREDRTDYNAMIC) $(DEFINITIONS_DEBUGLINUX32SHAREDRTDYNAMIC) $(INCLUDES_DEBUGLINUX32SHAREDRTDYNAMIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QBaseDualQuaternion_Test.cpp -o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QBaseDualQuaternion_Test.o

$(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QBaseHexahedron_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QBaseHexahedron_Test.cpp
	$(CXX_DEBUGLINUX32SHAREDRTDYNAMIC) $(COMPILEROPTIONS_DEBUGLINUX32SHAREDRTDYNAMIC) $(DEFINITIONS_DEBUGLINUX32SHAREDRTDYNAMIC) $(INCLUDES_DEBUGLINUX32SHAREDRTDYNAMIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QBaseHexahedron_Test.cpp -o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QBaseHexahedron_Test.o

$(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QBaseLineSegment_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QBaseLineSegment_Test.cpp
	$(CXX_DEBUGLINUX32SHAREDRTDYNAMIC) $(COMPILEROPTIONS_DEBUGLINUX32SHAREDRTDYNAMIC) $(DEFINITIONS_DEBUGLINUX32SHAREDRTDYNAMIC) $(INCLUDES_DEBUGLINUX32SHAREDRTDYNAMIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QBaseLineSegment_Test.cpp -o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QBaseLineSegment_Test.o

$(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QBaseMatrix2x2_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QBaseMatrix2x2_Test.cpp
	$(CXX_DEBUGLINUX32SHAREDRTDYNAMIC) $(COMPILEROPTIONS_DEBUGLINUX32SHAREDRTDYNAMIC) $(DEFINITIONS_DEBUGLINUX32SHAREDRTDYNAMIC) $(INCLUDES_DEBUGLINUX32SHAREDRTDYNAMIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QBaseMatrix2x2_Test.cpp -o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QBaseMatrix2x2_Test.o

$(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QBaseMatrix3x3_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QBaseMatrix3x3_Test.cpp
	$(CXX_DEBUGLINUX32SHAREDRTDYNAMIC) $(COMPILEROPTIONS_DEBUGLINUX32SHAREDRTDYNAMIC) $(DEFINITIONS_DEBUGLINUX32SHAREDRTDYNAMIC) $(INCLUDES_DEBUGLINUX32SHAREDRTDYNAMIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QBaseMatrix3x3_Test.cpp -o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QBaseMatrix3x3_Test.o

$(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QBaseMatrix3x4_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QBaseMatrix3x4_Test.cpp
	$(CXX_DEBUGLINUX32SHAREDRTDYNAMIC) $(COMPILEROPTIONS_DEBUGLINUX32SHAREDRTDYNAMIC) $(DEFINITIONS_DEBUGLINUX32SHAREDRTDYNAMIC) $(INCLUDES_DEBUGLINUX32SHAREDRTDYNAMIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QBaseMatrix3x4_Test.cpp -o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QBaseMatrix3x4_Test.o

$(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QBaseMatrix4x3_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QBaseMatrix4x3_Test.cpp
	$(CXX_DEBUGLINUX32SHAREDRTDYNAMIC) $(COMPILEROPTIONS_DEBUGLINUX32SHAREDRTDYNAMIC) $(DEFINITIONS_DEBUGLINUX32SHAREDRTDYNAMIC) $(INCLUDES_DEBUGLINUX32SHAREDRTDYNAMIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QBaseMatrix4x3_Test.cpp -o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QBaseMatrix4x3_Test.o

$(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QBaseMatrix4x4_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QBaseMatrix4x4_Test.cpp
	$(CXX_DEBUGLINUX32SHAREDRTDYNAMIC) $(COMPILEROPTIONS_DEBUGLINUX32SHAREDRTDYNAMIC) $(DEFINITIONS_DEBUGLINUX32SHAREDRTDYNAMIC) $(INCLUDES_DEBUGLINUX32SHAREDRTDYNAMIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QBaseMatrix4x4_Test.cpp -o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QBaseMatrix4x4_Test.o

$(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QBaseOrb_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QBaseOrb_Test.cpp
	$(CXX_DEBUGLINUX32SHAREDRTDYNAMIC) $(COMPILEROPTIONS_DEBUGLINUX32SHAREDRTDYNAMIC) $(DEFINITIONS_DEBUGLINUX32SHAREDRTDYNAMIC) $(INCLUDES_DEBUGLINUX32SHAREDRTDYNAMIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QBaseOrb_Test.cpp -o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QBaseOrb_Test.o

$(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QBasePlane_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QBasePlane_Test.cpp
	$(CXX_DEBUGLINUX32SHAREDRTDYNAMIC) $(COMPILEROPTIONS_DEBUGLINUX32SHAREDRTDYNAMIC) $(DEFINITIONS_DEBUGLINUX32SHAREDRTDYNAMIC) $(INCLUDES_DEBUGLINUX32SHAREDRTDYNAMIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QBasePlane_Test.cpp -o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QBasePlane_Test.o

$(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QBaseQuadrilateral_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QBaseQuadrilateral_Test.cpp
	$(CXX_DEBUGLINUX32SHAREDRTDYNAMIC) $(COMPILEROPTIONS_DEBUGLINUX32SHAREDRTDYNAMIC) $(DEFINITIONS_DEBUGLINUX32SHAREDRTDYNAMIC) $(INCLUDES_DEBUGLINUX32SHAREDRTDYNAMIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QBaseQuadrilateral_Test.cpp -o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QBaseQuadrilateral_Test.o

$(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QBaseQuaternion_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QBaseQuaternion_Test.cpp
	$(CXX_DEBUGLINUX32SHAREDRTDYNAMIC) $(COMPILEROPTIONS_DEBUGLINUX32SHAREDRTDYNAMIC) $(DEFINITIONS_DEBUGLINUX32SHAREDRTDYNAMIC) $(INCLUDES_DEBUGLINUX32SHAREDRTDYNAMIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QBaseQuaternion_Test.cpp -o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QBaseQuaternion_Test.o

$(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QBaseRay_QVector4_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QBaseRay_QVector4_Test.cpp
	$(CXX_DEBUGLINUX32SHAREDRTDYNAMIC) $(COMPILEROPTIONS_DEBUGLINUX32SHAREDRTDYNAMIC) $(DEFINITIONS_DEBUGLINUX32SHAREDRTDYNAMIC) $(INCLUDES_DEBUGLINUX32SHAREDRTDYNAMIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QBaseRay_QVector4_Test.cpp -o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QBaseRay_QVector4_Test.o

$(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QBaseRay_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QBaseRay_Test.cpp
	$(CXX_DEBUGLINUX32SHAREDRTDYNAMIC) $(COMPILEROPTIONS_DEBUGLINUX32SHAREDRTDYNAMIC) $(DEFINITIONS_DEBUGLINUX32SHAREDRTDYNAMIC) $(INCLUDES_DEBUGLINUX32SHAREDRTDYNAMIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QBaseRay_Test.cpp -o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QBaseRay_Test.o

$(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QBaseTriangle_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QBaseTriangle_Test.cpp
	$(CXX_DEBUGLINUX32SHAREDRTDYNAMIC) $(COMPILEROPTIONS_DEBUGLINUX32SHAREDRTDYNAMIC) $(DEFINITIONS_DEBUGLINUX32SHAREDRTDYNAMIC) $(INCLUDES_DEBUGLINUX32SHAREDRTDYNAMIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QBaseTriangle_Test.cpp -o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QBaseTriangle_Test.o

$(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QBaseVector2_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QBaseVector2_Test.cpp
	$(CXX_DEBUGLINUX32SHAREDRTDYNAMIC) $(COMPILEROPTIONS_DEBUGLINUX32SHAREDRTDYNAMIC) $(DEFINITIONS_DEBUGLINUX32SHAREDRTDYNAMIC) $(INCLUDES_DEBUGLINUX32SHAREDRTDYNAMIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QBaseVector2_Test.cpp -o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QBaseVector2_Test.o

$(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QBaseVector3_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QBaseVector3_Test.cpp
	$(CXX_DEBUGLINUX32SHAREDRTDYNAMIC) $(COMPILEROPTIONS_DEBUGLINUX32SHAREDRTDYNAMIC) $(DEFINITIONS_DEBUGLINUX32SHAREDRTDYNAMIC) $(INCLUDES_DEBUGLINUX32SHAREDRTDYNAMIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QBaseVector3_Test.cpp -o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QBaseVector3_Test.o

$(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QBaseVector4_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QBaseVector4_Test.cpp
	$(CXX_DEBUGLINUX32SHAREDRTDYNAMIC) $(COMPILEROPTIONS_DEBUGLINUX32SHAREDRTDYNAMIC) $(DEFINITIONS_DEBUGLINUX32SHAREDRTDYNAMIC) $(INCLUDES_DEBUGLINUX32SHAREDRTDYNAMIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QBaseVector4_Test.cpp -o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QBaseVector4_Test.o

$(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QCircle_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QCircle_Test.cpp
	$(CXX_DEBUGLINUX32SHAREDRTDYNAMIC) $(COMPILEROPTIONS_DEBUGLINUX32SHAREDRTDYNAMIC) $(DEFINITIONS_DEBUGLINUX32SHAREDRTDYNAMIC) $(INCLUDES_DEBUGLINUX32SHAREDRTDYNAMIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QCircle_Test.cpp -o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QCircle_Test.o

$(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QDualQuaternion_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QDualQuaternion_Test.cpp
	$(CXX_DEBUGLINUX32SHAREDRTDYNAMIC) $(COMPILEROPTIONS_DEBUGLINUX32SHAREDRTDYNAMIC) $(DEFINITIONS_DEBUGLINUX32SHAREDRTDYNAMIC) $(INCLUDES_DEBUGLINUX32SHAREDRTDYNAMIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QDualQuaternion_Test.cpp -o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QDualQuaternion_Test.o

$(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QHexahedron_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QHexahedron_Test.cpp
	$(CXX_DEBUGLINUX32SHAREDRTDYNAMIC) $(COMPILEROPTIONS_DEBUGLINUX32SHAREDRTDYNAMIC) $(DEFINITIONS_DEBUGLINUX32SHAREDRTDYNAMIC) $(INCLUDES_DEBUGLINUX32SHAREDRTDYNAMIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QHexahedron_Test.cpp -o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QHexahedron_Test.o

$(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QLineSegment2D_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QLineSegment2D_Test.cpp
	$(CXX_DEBUGLINUX32SHAREDRTDYNAMIC) $(COMPILEROPTIONS_DEBUGLINUX32SHAREDRTDYNAMIC) $(DEFINITIONS_DEBUGLINUX32SHAREDRTDYNAMIC) $(INCLUDES_DEBUGLINUX32SHAREDRTDYNAMIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QLineSegment2D_Test.cpp -o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QLineSegment2D_Test.o

$(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QLineSegment3D_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QLineSegment3D_Test.cpp
	$(CXX_DEBUGLINUX32SHAREDRTDYNAMIC) $(COMPILEROPTIONS_DEBUGLINUX32SHAREDRTDYNAMIC) $(DEFINITIONS_DEBUGLINUX32SHAREDRTDYNAMIC) $(INCLUDES_DEBUGLINUX32SHAREDRTDYNAMIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QLineSegment3D_Test.cpp -o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QLineSegment3D_Test.o

$(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QLineSegment_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QLineSegment_Test.cpp
	$(CXX_DEBUGLINUX32SHAREDRTDYNAMIC) $(COMPILEROPTIONS_DEBUGLINUX32SHAREDRTDYNAMIC) $(DEFINITIONS_DEBUGLINUX32SHAREDRTDYNAMIC) $(INCLUDES_DEBUGLINUX32SHAREDRTDYNAMIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QLineSegment_Test.cpp -o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QLineSegment_Test.o

$(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QMatrix2x2_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QMatrix2x2_Test.cpp
	$(CXX_DEBUGLINUX32SHAREDRTDYNAMIC) $(COMPILEROPTIONS_DEBUGLINUX32SHAREDRTDYNAMIC) $(DEFINITIONS_DEBUGLINUX32SHAREDRTDYNAMIC) $(INCLUDES_DEBUGLINUX32SHAREDRTDYNAMIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QMatrix2x2_Test.cpp -o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QMatrix2x2_Test.o

$(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QMatrix3x3_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QMatrix3x3_Test.cpp
	$(CXX_DEBUGLINUX32SHAREDRTDYNAMIC) $(COMPILEROPTIONS_DEBUGLINUX32SHAREDRTDYNAMIC) $(DEFINITIONS_DEBUGLINUX32SHAREDRTDYNAMIC) $(INCLUDES_DEBUGLINUX32SHAREDRTDYNAMIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QMatrix3x3_Test.cpp -o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QMatrix3x3_Test.o

$(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QMatrix3x4_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QMatrix3x4_Test.cpp
	$(CXX_DEBUGLINUX32SHAREDRTDYNAMIC) $(COMPILEROPTIONS_DEBUGLINUX32SHAREDRTDYNAMIC) $(DEFINITIONS_DEBUGLINUX32SHAREDRTDYNAMIC) $(INCLUDES_DEBUGLINUX32SHAREDRTDYNAMIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QMatrix3x4_Test.cpp -o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QMatrix3x4_Test.o

$(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QMatrix4x3_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QMatrix4x3_Test.cpp
	$(CXX_DEBUGLINUX32SHAREDRTDYNAMIC) $(COMPILEROPTIONS_DEBUGLINUX32SHAREDRTDYNAMIC) $(DEFINITIONS_DEBUGLINUX32SHAREDRTDYNAMIC) $(INCLUDES_DEBUGLINUX32SHAREDRTDYNAMIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QMatrix4x3_Test.cpp -o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QMatrix4x3_Test.o

$(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QMatrix4x4_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QMatrix4x4_Test.cpp
	$(CXX_DEBUGLINUX32SHAREDRTDYNAMIC) $(COMPILEROPTIONS_DEBUGLINUX32SHAREDRTDYNAMIC) $(DEFINITIONS_DEBUGLINUX32SHAREDRTDYNAMIC) $(INCLUDES_DEBUGLINUX32SHAREDRTDYNAMIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QMatrix4x4_Test.cpp -o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QMatrix4x4_Test.o

$(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QOrb_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QOrb_Test.cpp
	$(CXX_DEBUGLINUX32SHAREDRTDYNAMIC) $(COMPILEROPTIONS_DEBUGLINUX32SHAREDRTDYNAMIC) $(DEFINITIONS_DEBUGLINUX32SHAREDRTDYNAMIC) $(INCLUDES_DEBUGLINUX32SHAREDRTDYNAMIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QOrb_Test.cpp -o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QOrb_Test.o

$(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QPlane_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QPlane_Test.cpp
	$(CXX_DEBUGLINUX32SHAREDRTDYNAMIC) $(COMPILEROPTIONS_DEBUGLINUX32SHAREDRTDYNAMIC) $(DEFINITIONS_DEBUGLINUX32SHAREDRTDYNAMIC) $(INCLUDES_DEBUGLINUX32SHAREDRTDYNAMIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QPlane_Test.cpp -o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QPlane_Test.o

$(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QQuadrilateral_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QQuadrilateral_Test.cpp
	$(CXX_DEBUGLINUX32SHAREDRTDYNAMIC) $(COMPILEROPTIONS_DEBUGLINUX32SHAREDRTDYNAMIC) $(DEFINITIONS_DEBUGLINUX32SHAREDRTDYNAMIC) $(INCLUDES_DEBUGLINUX32SHAREDRTDYNAMIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QQuadrilateral_Test.cpp -o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QQuadrilateral_Test.o

$(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QQuaternion_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QQuaternion_Test.cpp
	$(CXX_DEBUGLINUX32SHAREDRTDYNAMIC) $(COMPILEROPTIONS_DEBUGLINUX32SHAREDRTDYNAMIC) $(DEFINITIONS_DEBUGLINUX32SHAREDRTDYNAMIC) $(INCLUDES_DEBUGLINUX32SHAREDRTDYNAMIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QQuaternion_Test.cpp -o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QQuaternion_Test.o

$(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QRay2D_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QRay2D_Test.cpp
	$(CXX_DEBUGLINUX32SHAREDRTDYNAMIC) $(COMPILEROPTIONS_DEBUGLINUX32SHAREDRTDYNAMIC) $(DEFINITIONS_DEBUGLINUX32SHAREDRTDYNAMIC) $(INCLUDES_DEBUGLINUX32SHAREDRTDYNAMIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QRay2D_Test.cpp -o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QRay2D_Test.o

$(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QRay3D_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QRay3D_Test.cpp
	$(CXX_DEBUGLINUX32SHAREDRTDYNAMIC) $(COMPILEROPTIONS_DEBUGLINUX32SHAREDRTDYNAMIC) $(DEFINITIONS_DEBUGLINUX32SHAREDRTDYNAMIC) $(INCLUDES_DEBUGLINUX32SHAREDRTDYNAMIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QRay3D_Test.cpp -o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QRay3D_Test.o

$(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QRay_QVector4_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QRay_QVector4_Test.cpp
	$(CXX_DEBUGLINUX32SHAREDRTDYNAMIC) $(COMPILEROPTIONS_DEBUGLINUX32SHAREDRTDYNAMIC) $(DEFINITIONS_DEBUGLINUX32SHAREDRTDYNAMIC) $(INCLUDES_DEBUGLINUX32SHAREDRTDYNAMIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QRay_QVector4_Test.cpp -o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QRay_QVector4_Test.o

$(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QRay_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QRay_Test.cpp
	$(CXX_DEBUGLINUX32SHAREDRTDYNAMIC) $(COMPILEROPTIONS_DEBUGLINUX32SHAREDRTDYNAMIC) $(DEFINITIONS_DEBUGLINUX32SHAREDRTDYNAMIC) $(INCLUDES_DEBUGLINUX32SHAREDRTDYNAMIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QRay_Test.cpp -o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QRay_Test.o

$(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QRotationMatrix3x3_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QRotationMatrix3x3_Test.cpp
	$(CXX_DEBUGLINUX32SHAREDRTDYNAMIC) $(COMPILEROPTIONS_DEBUGLINUX32SHAREDRTDYNAMIC) $(DEFINITIONS_DEBUGLINUX32SHAREDRTDYNAMIC) $(INCLUDES_DEBUGLINUX32SHAREDRTDYNAMIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QRotationMatrix3x3_Test.cpp -o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QRotationMatrix3x3_Test.o

$(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QScalingMatrix3x3_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QScalingMatrix3x3_Test.cpp
	$(CXX_DEBUGLINUX32SHAREDRTDYNAMIC) $(COMPILEROPTIONS_DEBUGLINUX32SHAREDRTDYNAMIC) $(DEFINITIONS_DEBUGLINUX32SHAREDRTDYNAMIC) $(INCLUDES_DEBUGLINUX32SHAREDRTDYNAMIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QScalingMatrix3x3_Test.cpp -o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QScalingMatrix3x3_Test.o

$(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QSpaceConversionMatrix_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QSpaceConversionMatrix_Test.cpp
	$(CXX_DEBUGLINUX32SHAREDRTDYNAMIC) $(COMPILEROPTIONS_DEBUGLINUX32SHAREDRTDYNAMIC) $(DEFINITIONS_DEBUGLINUX32SHAREDRTDYNAMIC) $(INCLUDES_DEBUGLINUX32SHAREDRTDYNAMIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QSpaceConversionMatrix_Test.cpp -o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QSpaceConversionMatrix_Test.o

$(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QSphere_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QSphere_Test.cpp
	$(CXX_DEBUGLINUX32SHAREDRTDYNAMIC) $(COMPILEROPTIONS_DEBUGLINUX32SHAREDRTDYNAMIC) $(DEFINITIONS_DEBUGLINUX32SHAREDRTDYNAMIC) $(INCLUDES_DEBUGLINUX32SHAREDRTDYNAMIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QSphere_Test.cpp -o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QSphere_Test.o

$(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QTransformationMatrix3x3_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QTransformationMatrix3x3_Test.cpp
	$(CXX_DEBUGLINUX32SHAREDRTDYNAMIC) $(COMPILEROPTIONS_DEBUGLINUX32SHAREDRTDYNAMIC) $(DEFINITIONS_DEBUGLINUX32SHAREDRTDYNAMIC) $(INCLUDES_DEBUGLINUX32SHAREDRTDYNAMIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QTransformationMatrix3x3_Test.cpp -o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QTransformationMatrix3x3_Test.o

$(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QTransformationMatrix_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QTransformationMatrix_Test.cpp
	$(CXX_DEBUGLINUX32SHAREDRTDYNAMIC) $(COMPILEROPTIONS_DEBUGLINUX32SHAREDRTDYNAMIC) $(DEFINITIONS_DEBUGLINUX32SHAREDRTDYNAMIC) $(INCLUDES_DEBUGLINUX32SHAREDRTDYNAMIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QTransformationMatrix_Test.cpp -o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QTransformationMatrix_Test.o

$(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QTranslationMatrix_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QTranslationMatrix_Test.cpp
	$(CXX_DEBUGLINUX32SHAREDRTDYNAMIC) $(COMPILEROPTIONS_DEBUGLINUX32SHAREDRTDYNAMIC) $(DEFINITIONS_DEBUGLINUX32SHAREDRTDYNAMIC) $(INCLUDES_DEBUGLINUX32SHAREDRTDYNAMIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QTranslationMatrix_Test.cpp -o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QTranslationMatrix_Test.o

$(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QTriangle2D_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QTriangle2D_Test.cpp
	$(CXX_DEBUGLINUX32SHAREDRTDYNAMIC) $(COMPILEROPTIONS_DEBUGLINUX32SHAREDRTDYNAMIC) $(DEFINITIONS_DEBUGLINUX32SHAREDRTDYNAMIC) $(INCLUDES_DEBUGLINUX32SHAREDRTDYNAMIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QTriangle2D_Test.cpp -o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QTriangle2D_Test.o

$(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QTriangle3D_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QTriangle3D_Test.cpp
	$(CXX_DEBUGLINUX32SHAREDRTDYNAMIC) $(COMPILEROPTIONS_DEBUGLINUX32SHAREDRTDYNAMIC) $(DEFINITIONS_DEBUGLINUX32SHAREDRTDYNAMIC) $(INCLUDES_DEBUGLINUX32SHAREDRTDYNAMIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QTriangle3D_Test.cpp -o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QTriangle3D_Test.o

$(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QTriangle_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QTriangle_Test.cpp
	$(CXX_DEBUGLINUX32SHAREDRTDYNAMIC) $(COMPILEROPTIONS_DEBUGLINUX32SHAREDRTDYNAMIC) $(DEFINITIONS_DEBUGLINUX32SHAREDRTDYNAMIC) $(INCLUDES_DEBUGLINUX32SHAREDRTDYNAMIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QTriangle_Test.cpp -o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QTriangle_Test.o

$(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QVector2_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QVector2_Test.cpp
	$(CXX_DEBUGLINUX32SHAREDRTDYNAMIC) $(COMPILEROPTIONS_DEBUGLINUX32SHAREDRTDYNAMIC) $(DEFINITIONS_DEBUGLINUX32SHAREDRTDYNAMIC) $(INCLUDES_DEBUGLINUX32SHAREDRTDYNAMIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QVector2_Test.cpp -o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QVector2_Test.o

$(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QVector3_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QVector3_Test.cpp
	$(CXX_DEBUGLINUX32SHAREDRTDYNAMIC) $(COMPILEROPTIONS_DEBUGLINUX32SHAREDRTDYNAMIC) $(DEFINITIONS_DEBUGLINUX32SHAREDRTDYNAMIC) $(INCLUDES_DEBUGLINUX32SHAREDRTDYNAMIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QVector3_Test.cpp -o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QVector3_Test.o

$(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QVector4_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QVector4_Test.cpp
	$(CXX_DEBUGLINUX32SHAREDRTDYNAMIC) $(COMPILEROPTIONS_DEBUGLINUX32SHAREDRTDYNAMIC) $(DEFINITIONS_DEBUGLINUX32SHAREDRTDYNAMIC) $(INCLUDES_DEBUGLINUX32SHAREDRTDYNAMIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QVector4_Test.cpp -o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QVector4_Test.o

$(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.SQAngle_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/SQAngle_Test.cpp
	$(CXX_DEBUGLINUX32SHAREDRTDYNAMIC) $(COMPILEROPTIONS_DEBUGLINUX32SHAREDRTDYNAMIC) $(DEFINITIONS_DEBUGLINUX32SHAREDRTDYNAMIC) $(INCLUDES_DEBUGLINUX32SHAREDRTDYNAMIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/SQAngle_Test.cpp -o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.SQAngle_Test.o

$(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.SQPoint_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/SQPoint_Test.cpp
	$(CXX_DEBUGLINUX32SHAREDRTDYNAMIC) $(COMPILEROPTIONS_DEBUGLINUX32SHAREDRTDYNAMIC) $(DEFINITIONS_DEBUGLINUX32SHAREDRTDYNAMIC) $(INCLUDES_DEBUGLINUX32SHAREDRTDYNAMIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/SQPoint_Test.cpp -o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.SQPoint_Test.o

$(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QEvent_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QEvent_Test.cpp
	$(CXX_DEBUGLINUX32SHAREDRTDYNAMIC) $(COMPILEROPTIONS_DEBUGLINUX32SHAREDRTDYNAMIC) $(DEFINITIONS_DEBUGLINUX32SHAREDRTDYNAMIC) $(INCLUDES_DEBUGLINUX32SHAREDRTDYNAMIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QEvent_Test.cpp -o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QEvent_Test.o

$(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTDYNAMIC)__.__.__.testsystem.EQTestType.o: $(EXECUTION_PATH)../../../testsystem/EQTestType.cpp
	$(CXX_DEBUGLINUX32SHAREDRTDYNAMIC) $(COMPILEROPTIONS_DEBUGLINUX32SHAREDRTDYNAMIC) $(DEFINITIONS_DEBUGLINUX32SHAREDRTDYNAMIC) $(INCLUDES_DEBUGLINUX32SHAREDRTDYNAMIC) -c $(EXECUTION_PATH)../../../testsystem/EQTestType.cpp -o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTDYNAMIC)__.__.__.testsystem.EQTestType.o

$(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTDYNAMIC)__.__.__.testsystem.QCommonTestConfig.o: $(EXECUTION_PATH)../../../testsystem/QCommonTestConfig.cpp
	$(CXX_DEBUGLINUX32SHAREDRTDYNAMIC) $(COMPILEROPTIONS_DEBUGLINUX32SHAREDRTDYNAMIC) $(DEFINITIONS_DEBUGLINUX32SHAREDRTDYNAMIC) $(INCLUDES_DEBUGLINUX32SHAREDRTDYNAMIC) -c $(EXECUTION_PATH)../../../testsystem/QCommonTestConfig.cpp -o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTDYNAMIC)__.__.__.testsystem.QCommonTestConfig.o

$(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTDYNAMIC)__.__.__.testsystem.QSimpleConfigLoader.o: $(EXECUTION_PATH)../../../testsystem/QSimpleConfigLoader.cpp
	$(CXX_DEBUGLINUX32SHAREDRTDYNAMIC) $(COMPILEROPTIONS_DEBUGLINUX32SHAREDRTDYNAMIC) $(DEFINITIONS_DEBUGLINUX32SHAREDRTDYNAMIC) $(INCLUDES_DEBUGLINUX32SHAREDRTDYNAMIC) -c $(EXECUTION_PATH)../../../testsystem/QSimpleConfigLoader.cpp -o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTDYNAMIC)__.__.__.testsystem.QSimpleConfigLoader.o

postbuildDebugLinux32SharedrtDynamic:
	rm -f *.so


buildDebugLinux32SharedrtDynamic: prebuildDebugLinux32SharedrtDynamic DebugLinux32SharedrtDynamic postbuildDebugLinux32SharedrtDynamic

cleanDebugLinux32SharedrtDynamic:
	rm -f $(OBJECTS_DEBUGLINUX32SHAREDRTDYNAMIC)
	rm -f $(OUTPUT_DEBUGLINUX32SHAREDRTDYNAMIC)
	if (test -d $(EXECUTION_PATH)../../../bin/GCC/DebugLinux32SharedrtDynamic) then rm -rf "$(EXECUTION_PATH)../../../bin/GCC/DebugLinux32SharedrtDynamic"; fi
	if (test -d $(EXECUTION_PATH)../../../bin/GCC/DebugLinux32SharedrtDynamic) then rmdir "$(EXECUTION_PATH)../../../bin/GCC/DebugLinux32SharedrtDynamic"; fi
	if (test -d $(EXECUTION_PATH)../../../garbage/GCC/DebugLinux32SharedrtDynamic) then rm -rf "$(EXECUTION_PATH)../../../garbage/GCC/DebugLinux32SharedrtDynamic"; fi
	if (test -d $(EXECUTION_PATH)../../../garbage/GCC/DebugLinux32SharedrtDynamic) then rmdir "$(EXECUTION_PATH)../../../garbage/GCC/DebugLinux32SharedrtDynamic"; fi


#------------------------------------------------------------
#------------- DebugLinux32SharedrtStatic --------------
#------------------------------------------------------------
CXX_DEBUGLINUX32SHAREDRTSTATIC = g++
AR_DEBUGLINUX32SHAREDRTSTATIC = ar
LD_DEBUGLINUX32SHAREDRTSTATIC = g++
AS_DEBUGLINUX32SHAREDRTSTATIC = as
INCLUDES_DEBUGLINUX32SHAREDRTSTATIC = $(INCLUDES_GLOBAL) -I$(EXECUTION_PATH)../../../../headers -I$(EXECUTION_PATH)../../../tests/unit -I$(EXECUTION_PATH)../../../../3rdparty/ICU/include
LIBRARYDIRS_DEBUGLINUX32SHAREDRTSTATIC = $(LIBRARYDIRS_GLOBAL) -L$(EXECUTION_PATH)../../../../3rdparty/Boost/bin/Linux32/DebugSharedrtStatic -L$(EXECUTION_PATH)../../../../bin/GCC/DebugLinux32SharedrtStatic
LIBRARIES_DEBUGLINUX32SHAREDRTSTATIC = $(LIBRARIES_GLOBAL) -lQuimeraEngineTools -lQuimeraEngineCommon -lboost_unit_test_framework-mt-d -licudata -licuuc -licui18n
COMPILEROPTIONS_DEBUGLINUX32SHAREDRTSTATIC = $(COMPILEROPTIONS_GLOBAL) -g -O0 -Wall -Wno-comment -Wno-unused-local-typedefs -m32 -isystem $(EXECUTION_PATH)../../../../3rdparty/Boost/include
LINKEROPTIONS_DEBUGLINUX32SHAREDRTSTATIC = $(LINKEROPTIONS_GLOBAL) -m32
DEFINITIONS_DEBUGLINUX32SHAREDRTSTATIC = $(DEFINITIONS_GLOBAL) -DBOOST_NO_RTTI -DBOOST_NO_TYPEID
OUTPUT_DEBUGLINUX32SHAREDRTSTATIC = $(EXECUTION_PATH)../../../bin/GCC/DebugLinux32SharedrtStatic/Unit_TestModule_Tools.sh
INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTSTATIC = $(EXECUTION_PATH)../../../garbage/GCC/DebugLinux32SharedrtStatic/
OBJECTS_DEBUGLINUX32SHAREDRTSTATIC = $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.TestModule_Tools.o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QArrayIterator_Test.o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QList_Test.o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QListIterator_Test.o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QNTree_Test.o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.CallCounter.o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QNTreeIterator_Test.o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QBinarySearchTree_Test.o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QConstArrayIterator_Test.o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QConstListIterator_Test.o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QConstNTreeIterator_Test.o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QConstBinarySearchTreeIterator_Test.o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.SQComparatorDefault_Test.o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QKeyValuePair_Test.o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.SQKeyValuePairComparator_Test.o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.SQEqualityComparator_Test.o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QDictionary_Test.o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QHashtable_Test.o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.SQIntegerHashProvider_Test.o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.SQStringHashProvider_Test.o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QConstDictionaryIterator_Test.o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QConstHashtableIterator_Test.o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QArrayDynamic_Test.o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QArrayFixed_Test.o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QDateTime_Test.o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QDstInformation_Test.o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QTimeSpan_Test.o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QTimeZone_Test.o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.SQTimeZoneFactory_Test.o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QBaseDualQuaternion_Test.o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QBaseHexahedron_Test.o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QBaseLineSegment_Test.o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QBaseMatrix2x2_Test.o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QBaseMatrix3x3_Test.o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QBaseMatrix3x4_Test.o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QBaseMatrix4x3_Test.o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QBaseMatrix4x4_Test.o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QBaseOrb_Test.o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QBasePlane_Test.o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QBaseQuadrilateral_Test.o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QBaseQuaternion_Test.o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QBaseRay_QVector4_Test.o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QBaseRay_Test.o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QBaseTriangle_Test.o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QBaseVector2_Test.o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QBaseVector3_Test.o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QBaseVector4_Test.o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QCircle_Test.o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QDualQuaternion_Test.o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QHexahedron_Test.o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QLineSegment2D_Test.o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QLineSegment3D_Test.o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QLineSegment_Test.o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QMatrix2x2_Test.o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QMatrix3x3_Test.o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QMatrix3x4_Test.o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QMatrix4x3_Test.o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QMatrix4x4_Test.o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QOrb_Test.o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QPlane_Test.o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QQuadrilateral_Test.o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QQuaternion_Test.o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QRay2D_Test.o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QRay3D_Test.o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QRay_QVector4_Test.o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QRay_Test.o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QRotationMatrix3x3_Test.o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QScalingMatrix3x3_Test.o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QSpaceConversionMatrix_Test.o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QSphere_Test.o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QTransformationMatrix3x3_Test.o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QTransformationMatrix_Test.o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QTranslationMatrix_Test.o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QTriangle2D_Test.o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QTriangle3D_Test.o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QTriangle_Test.o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QVector2_Test.o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QVector3_Test.o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QVector4_Test.o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.SQAngle_Test.o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.SQPoint_Test.o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QEvent_Test.o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTSTATIC)__.__.__.testsystem.EQTestType.o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTSTATIC)__.__.__.testsystem.QCommonTestConfig.o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTSTATIC)__.__.__.testsystem.QSimpleConfigLoader.o

prebuildDebugLinux32SharedrtStatic:
	if ! (test -d $(EXECUTION_PATH)../../../bin/GCC/DebugLinux32SharedrtStatic) then mkdir -p "$(EXECUTION_PATH)../../../bin/GCC/DebugLinux32SharedrtStatic"; fi
	if ! (test -d $(EXECUTION_PATH)../../../garbage/GCC/DebugLinux32SharedrtStatic) then mkdir -p "$(EXECUTION_PATH)../../../garbage/GCC/DebugLinux32SharedrtStatic"; fi
	mkdir -p $(EXECUTION_PATH)../../../bin/GCC/DebugLinux32SharedrtStatic
	cp "$(EXECUTION_PATH)../../../bin/TestConfig.txt" "$(EXECUTION_PATH)../../../bin/GCC/DebugLinux32SharedrtStatic"
	cp "$(EXECUTION_PATH)../../../bin/NormalizationTest.txt" "$(EXECUTION_PATH)../../../bin/GCC/DebugLinux32SharedrtStatic"


DebugLinux32SharedrtStatic: $(OBJECTS_DEBUGLINUX32SHAREDRTSTATIC)
	$(LD_DEBUGLINUX32SHAREDRTSTATIC) $(DEFINITIONS_DEBUGLINUX32SHAREDRTSTATIC) $(LINKEROPTIONS_DEBUGLINUX32SHAREDRTSTATIC) $(LIBRARYDIRS_DEBUGLINUX32SHAREDRTSTATIC) $(OBJECTS_DEBUGLINUX32SHAREDRTSTATIC) $(LIBRARIES_DEBUGLINUX32SHAREDRTSTATIC) -o $(OUTPUT_DEBUGLINUX32SHAREDRTSTATIC)

$(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.TestModule_Tools.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/TestModule_Tools.cpp
	$(CXX_DEBUGLINUX32SHAREDRTSTATIC) $(COMPILEROPTIONS_DEBUGLINUX32SHAREDRTSTATIC) $(DEFINITIONS_DEBUGLINUX32SHAREDRTSTATIC) $(INCLUDES_DEBUGLINUX32SHAREDRTSTATIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/TestModule_Tools.cpp -o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.TestModule_Tools.o

$(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QArrayIterator_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QArrayIterator_Test.cpp
	$(CXX_DEBUGLINUX32SHAREDRTSTATIC) $(COMPILEROPTIONS_DEBUGLINUX32SHAREDRTSTATIC) $(DEFINITIONS_DEBUGLINUX32SHAREDRTSTATIC) $(INCLUDES_DEBUGLINUX32SHAREDRTSTATIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QArrayIterator_Test.cpp -o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QArrayIterator_Test.o

$(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QList_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QList_Test.cpp
	$(CXX_DEBUGLINUX32SHAREDRTSTATIC) $(COMPILEROPTIONS_DEBUGLINUX32SHAREDRTSTATIC) $(DEFINITIONS_DEBUGLINUX32SHAREDRTSTATIC) $(INCLUDES_DEBUGLINUX32SHAREDRTSTATIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QList_Test.cpp -o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QList_Test.o

$(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QListIterator_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QListIterator_Test.cpp
	$(CXX_DEBUGLINUX32SHAREDRTSTATIC) $(COMPILEROPTIONS_DEBUGLINUX32SHAREDRTSTATIC) $(DEFINITIONS_DEBUGLINUX32SHAREDRTSTATIC) $(INCLUDES_DEBUGLINUX32SHAREDRTSTATIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QListIterator_Test.cpp -o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QListIterator_Test.o

$(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QNTree_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QNTree_Test.cpp
	$(CXX_DEBUGLINUX32SHAREDRTSTATIC) $(COMPILEROPTIONS_DEBUGLINUX32SHAREDRTSTATIC) $(DEFINITIONS_DEBUGLINUX32SHAREDRTSTATIC) $(INCLUDES_DEBUGLINUX32SHAREDRTSTATIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QNTree_Test.cpp -o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QNTree_Test.o

$(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.CallCounter.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/CallCounter.cpp
	$(CXX_DEBUGLINUX32SHAREDRTSTATIC) $(COMPILEROPTIONS_DEBUGLINUX32SHAREDRTSTATIC) $(DEFINITIONS_DEBUGLINUX32SHAREDRTSTATIC) $(INCLUDES_DEBUGLINUX32SHAREDRTSTATIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/CallCounter.cpp -o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.CallCounter.o

$(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QNTreeIterator_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QNTreeIterator_Test.cpp
	$(CXX_DEBUGLINUX32SHAREDRTSTATIC) $(COMPILEROPTIONS_DEBUGLINUX32SHAREDRTSTATIC) $(DEFINITIONS_DEBUGLINUX32SHAREDRTSTATIC) $(INCLUDES_DEBUGLINUX32SHAREDRTSTATIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QNTreeIterator_Test.cpp -o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QNTreeIterator_Test.o

$(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QBinarySearchTree_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QBinarySearchTree_Test.cpp
	$(CXX_DEBUGLINUX32SHAREDRTSTATIC) $(COMPILEROPTIONS_DEBUGLINUX32SHAREDRTSTATIC) $(DEFINITIONS_DEBUGLINUX32SHAREDRTSTATIC) $(INCLUDES_DEBUGLINUX32SHAREDRTSTATIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QBinarySearchTree_Test.cpp -o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QBinarySearchTree_Test.o

$(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QConstArrayIterator_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QConstArrayIterator_Test.cpp
	$(CXX_DEBUGLINUX32SHAREDRTSTATIC) $(COMPILEROPTIONS_DEBUGLINUX32SHAREDRTSTATIC) $(DEFINITIONS_DEBUGLINUX32SHAREDRTSTATIC) $(INCLUDES_DEBUGLINUX32SHAREDRTSTATIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QConstArrayIterator_Test.cpp -o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QConstArrayIterator_Test.o

$(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QConstListIterator_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QConstListIterator_Test.cpp
	$(CXX_DEBUGLINUX32SHAREDRTSTATIC) $(COMPILEROPTIONS_DEBUGLINUX32SHAREDRTSTATIC) $(DEFINITIONS_DEBUGLINUX32SHAREDRTSTATIC) $(INCLUDES_DEBUGLINUX32SHAREDRTSTATIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QConstListIterator_Test.cpp -o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QConstListIterator_Test.o

$(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QConstNTreeIterator_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QConstNTreeIterator_Test.cpp
	$(CXX_DEBUGLINUX32SHAREDRTSTATIC) $(COMPILEROPTIONS_DEBUGLINUX32SHAREDRTSTATIC) $(DEFINITIONS_DEBUGLINUX32SHAREDRTSTATIC) $(INCLUDES_DEBUGLINUX32SHAREDRTSTATIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QConstNTreeIterator_Test.cpp -o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QConstNTreeIterator_Test.o

$(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QConstBinarySearchTreeIterator_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QConstBinarySearchTreeIterator_Test.cpp
	$(CXX_DEBUGLINUX32SHAREDRTSTATIC) $(COMPILEROPTIONS_DEBUGLINUX32SHAREDRTSTATIC) $(DEFINITIONS_DEBUGLINUX32SHAREDRTSTATIC) $(INCLUDES_DEBUGLINUX32SHAREDRTSTATIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QConstBinarySearchTreeIterator_Test.cpp -o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QConstBinarySearchTreeIterator_Test.o

$(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.SQComparatorDefault_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/SQComparatorDefault_Test.cpp
	$(CXX_DEBUGLINUX32SHAREDRTSTATIC) $(COMPILEROPTIONS_DEBUGLINUX32SHAREDRTSTATIC) $(DEFINITIONS_DEBUGLINUX32SHAREDRTSTATIC) $(INCLUDES_DEBUGLINUX32SHAREDRTSTATIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/SQComparatorDefault_Test.cpp -o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.SQComparatorDefault_Test.o

$(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QKeyValuePair_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QKeyValuePair_Test.cpp
	$(CXX_DEBUGLINUX32SHAREDRTSTATIC) $(COMPILEROPTIONS_DEBUGLINUX32SHAREDRTSTATIC) $(DEFINITIONS_DEBUGLINUX32SHAREDRTSTATIC) $(INCLUDES_DEBUGLINUX32SHAREDRTSTATIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QKeyValuePair_Test.cpp -o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QKeyValuePair_Test.o

$(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.SQKeyValuePairComparator_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/SQKeyValuePairComparator_Test.cpp
	$(CXX_DEBUGLINUX32SHAREDRTSTATIC) $(COMPILEROPTIONS_DEBUGLINUX32SHAREDRTSTATIC) $(DEFINITIONS_DEBUGLINUX32SHAREDRTSTATIC) $(INCLUDES_DEBUGLINUX32SHAREDRTSTATIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/SQKeyValuePairComparator_Test.cpp -o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.SQKeyValuePairComparator_Test.o

$(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.SQEqualityComparator_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/SQEqualityComparator_Test.cpp
	$(CXX_DEBUGLINUX32SHAREDRTSTATIC) $(COMPILEROPTIONS_DEBUGLINUX32SHAREDRTSTATIC) $(DEFINITIONS_DEBUGLINUX32SHAREDRTSTATIC) $(INCLUDES_DEBUGLINUX32SHAREDRTSTATIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/SQEqualityComparator_Test.cpp -o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.SQEqualityComparator_Test.o

$(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QDictionary_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QDictionary_Test.cpp
	$(CXX_DEBUGLINUX32SHAREDRTSTATIC) $(COMPILEROPTIONS_DEBUGLINUX32SHAREDRTSTATIC) $(DEFINITIONS_DEBUGLINUX32SHAREDRTSTATIC) $(INCLUDES_DEBUGLINUX32SHAREDRTSTATIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QDictionary_Test.cpp -o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QDictionary_Test.o

$(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QHashtable_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QHashtable_Test.cpp
	$(CXX_DEBUGLINUX32SHAREDRTSTATIC) $(COMPILEROPTIONS_DEBUGLINUX32SHAREDRTSTATIC) $(DEFINITIONS_DEBUGLINUX32SHAREDRTSTATIC) $(INCLUDES_DEBUGLINUX32SHAREDRTSTATIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QHashtable_Test.cpp -o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QHashtable_Test.o

$(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.SQIntegerHashProvider_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/SQIntegerHashProvider_Test.cpp
	$(CXX_DEBUGLINUX32SHAREDRTSTATIC) $(COMPILEROPTIONS_DEBUGLINUX32SHAREDRTSTATIC) $(DEFINITIONS_DEBUGLINUX32SHAREDRTSTATIC) $(INCLUDES_DEBUGLINUX32SHAREDRTSTATIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/SQIntegerHashProvider_Test.cpp -o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.SQIntegerHashProvider_Test.o

$(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.SQStringHashProvider_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/SQStringHashProvider_Test.cpp
	$(CXX_DEBUGLINUX32SHAREDRTSTATIC) $(COMPILEROPTIONS_DEBUGLINUX32SHAREDRTSTATIC) $(DEFINITIONS_DEBUGLINUX32SHAREDRTSTATIC) $(INCLUDES_DEBUGLINUX32SHAREDRTSTATIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/SQStringHashProvider_Test.cpp -o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.SQStringHashProvider_Test.o

$(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QConstDictionaryIterator_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QConstDictionaryIterator_Test.cpp
	$(CXX_DEBUGLINUX32SHAREDRTSTATIC) $(COMPILEROPTIONS_DEBUGLINUX32SHAREDRTSTATIC) $(DEFINITIONS_DEBUGLINUX32SHAREDRTSTATIC) $(INCLUDES_DEBUGLINUX32SHAREDRTSTATIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QConstDictionaryIterator_Test.cpp -o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QConstDictionaryIterator_Test.o

$(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QConstHashtableIterator_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QConstHashtableIterator_Test.cpp
	$(CXX_DEBUGLINUX32SHAREDRTSTATIC) $(COMPILEROPTIONS_DEBUGLINUX32SHAREDRTSTATIC) $(DEFINITIONS_DEBUGLINUX32SHAREDRTSTATIC) $(INCLUDES_DEBUGLINUX32SHAREDRTSTATIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QConstHashtableIterator_Test.cpp -o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QConstHashtableIterator_Test.o

$(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QArrayDynamic_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QArrayDynamic_Test.cpp
	$(CXX_DEBUGLINUX32SHAREDRTSTATIC) $(COMPILEROPTIONS_DEBUGLINUX32SHAREDRTSTATIC) $(DEFINITIONS_DEBUGLINUX32SHAREDRTSTATIC) $(INCLUDES_DEBUGLINUX32SHAREDRTSTATIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QArrayDynamic_Test.cpp -o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QArrayDynamic_Test.o

$(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QArrayFixed_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QArrayFixed_Test.cpp
	$(CXX_DEBUGLINUX32SHAREDRTSTATIC) $(COMPILEROPTIONS_DEBUGLINUX32SHAREDRTSTATIC) $(DEFINITIONS_DEBUGLINUX32SHAREDRTSTATIC) $(INCLUDES_DEBUGLINUX32SHAREDRTSTATIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QArrayFixed_Test.cpp -o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QArrayFixed_Test.o

$(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QDateTime_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QDateTime_Test.cpp
	$(CXX_DEBUGLINUX32SHAREDRTSTATIC) $(COMPILEROPTIONS_DEBUGLINUX32SHAREDRTSTATIC) $(DEFINITIONS_DEBUGLINUX32SHAREDRTSTATIC) $(INCLUDES_DEBUGLINUX32SHAREDRTSTATIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QDateTime_Test.cpp -o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QDateTime_Test.o

$(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QDstInformation_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QDstInformation_Test.cpp
	$(CXX_DEBUGLINUX32SHAREDRTSTATIC) $(COMPILEROPTIONS_DEBUGLINUX32SHAREDRTSTATIC) $(DEFINITIONS_DEBUGLINUX32SHAREDRTSTATIC) $(INCLUDES_DEBUGLINUX32SHAREDRTSTATIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QDstInformation_Test.cpp -o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QDstInformation_Test.o

$(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QTimeSpan_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QTimeSpan_Test.cpp
	$(CXX_DEBUGLINUX32SHAREDRTSTATIC) $(COMPILEROPTIONS_DEBUGLINUX32SHAREDRTSTATIC) $(DEFINITIONS_DEBUGLINUX32SHAREDRTSTATIC) $(INCLUDES_DEBUGLINUX32SHAREDRTSTATIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QTimeSpan_Test.cpp -o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QTimeSpan_Test.o

$(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QTimeZone_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QTimeZone_Test.cpp
	$(CXX_DEBUGLINUX32SHAREDRTSTATIC) $(COMPILEROPTIONS_DEBUGLINUX32SHAREDRTSTATIC) $(DEFINITIONS_DEBUGLINUX32SHAREDRTSTATIC) $(INCLUDES_DEBUGLINUX32SHAREDRTSTATIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QTimeZone_Test.cpp -o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QTimeZone_Test.o

$(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.SQTimeZoneFactory_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/SQTimeZoneFactory_Test.cpp
	$(CXX_DEBUGLINUX32SHAREDRTSTATIC) $(COMPILEROPTIONS_DEBUGLINUX32SHAREDRTSTATIC) $(DEFINITIONS_DEBUGLINUX32SHAREDRTSTATIC) $(INCLUDES_DEBUGLINUX32SHAREDRTSTATIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/SQTimeZoneFactory_Test.cpp -o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.SQTimeZoneFactory_Test.o

$(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QBaseDualQuaternion_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QBaseDualQuaternion_Test.cpp
	$(CXX_DEBUGLINUX32SHAREDRTSTATIC) $(COMPILEROPTIONS_DEBUGLINUX32SHAREDRTSTATIC) $(DEFINITIONS_DEBUGLINUX32SHAREDRTSTATIC) $(INCLUDES_DEBUGLINUX32SHAREDRTSTATIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QBaseDualQuaternion_Test.cpp -o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QBaseDualQuaternion_Test.o

$(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QBaseHexahedron_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QBaseHexahedron_Test.cpp
	$(CXX_DEBUGLINUX32SHAREDRTSTATIC) $(COMPILEROPTIONS_DEBUGLINUX32SHAREDRTSTATIC) $(DEFINITIONS_DEBUGLINUX32SHAREDRTSTATIC) $(INCLUDES_DEBUGLINUX32SHAREDRTSTATIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QBaseHexahedron_Test.cpp -o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QBaseHexahedron_Test.o

$(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QBaseLineSegment_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QBaseLineSegment_Test.cpp
	$(CXX_DEBUGLINUX32SHAREDRTSTATIC) $(COMPILEROPTIONS_DEBUGLINUX32SHAREDRTSTATIC) $(DEFINITIONS_DEBUGLINUX32SHAREDRTSTATIC) $(INCLUDES_DEBUGLINUX32SHAREDRTSTATIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QBaseLineSegment_Test.cpp -o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QBaseLineSegment_Test.o

$(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QBaseMatrix2x2_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QBaseMatrix2x2_Test.cpp
	$(CXX_DEBUGLINUX32SHAREDRTSTATIC) $(COMPILEROPTIONS_DEBUGLINUX32SHAREDRTSTATIC) $(DEFINITIONS_DEBUGLINUX32SHAREDRTSTATIC) $(INCLUDES_DEBUGLINUX32SHAREDRTSTATIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QBaseMatrix2x2_Test.cpp -o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QBaseMatrix2x2_Test.o

$(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QBaseMatrix3x3_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QBaseMatrix3x3_Test.cpp
	$(CXX_DEBUGLINUX32SHAREDRTSTATIC) $(COMPILEROPTIONS_DEBUGLINUX32SHAREDRTSTATIC) $(DEFINITIONS_DEBUGLINUX32SHAREDRTSTATIC) $(INCLUDES_DEBUGLINUX32SHAREDRTSTATIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QBaseMatrix3x3_Test.cpp -o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QBaseMatrix3x3_Test.o

$(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QBaseMatrix3x4_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QBaseMatrix3x4_Test.cpp
	$(CXX_DEBUGLINUX32SHAREDRTSTATIC) $(COMPILEROPTIONS_DEBUGLINUX32SHAREDRTSTATIC) $(DEFINITIONS_DEBUGLINUX32SHAREDRTSTATIC) $(INCLUDES_DEBUGLINUX32SHAREDRTSTATIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QBaseMatrix3x4_Test.cpp -o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QBaseMatrix3x4_Test.o

$(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QBaseMatrix4x3_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QBaseMatrix4x3_Test.cpp
	$(CXX_DEBUGLINUX32SHAREDRTSTATIC) $(COMPILEROPTIONS_DEBUGLINUX32SHAREDRTSTATIC) $(DEFINITIONS_DEBUGLINUX32SHAREDRTSTATIC) $(INCLUDES_DEBUGLINUX32SHAREDRTSTATIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QBaseMatrix4x3_Test.cpp -o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QBaseMatrix4x3_Test.o

$(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QBaseMatrix4x4_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QBaseMatrix4x4_Test.cpp
	$(CXX_DEBUGLINUX32SHAREDRTSTATIC) $(COMPILEROPTIONS_DEBUGLINUX32SHAREDRTSTATIC) $(DEFINITIONS_DEBUGLINUX32SHAREDRTSTATIC) $(INCLUDES_DEBUGLINUX32SHAREDRTSTATIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QBaseMatrix4x4_Test.cpp -o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QBaseMatrix4x4_Test.o

$(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QBaseOrb_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QBaseOrb_Test.cpp
	$(CXX_DEBUGLINUX32SHAREDRTSTATIC) $(COMPILEROPTIONS_DEBUGLINUX32SHAREDRTSTATIC) $(DEFINITIONS_DEBUGLINUX32SHAREDRTSTATIC) $(INCLUDES_DEBUGLINUX32SHAREDRTSTATIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QBaseOrb_Test.cpp -o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QBaseOrb_Test.o

$(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QBasePlane_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QBasePlane_Test.cpp
	$(CXX_DEBUGLINUX32SHAREDRTSTATIC) $(COMPILEROPTIONS_DEBUGLINUX32SHAREDRTSTATIC) $(DEFINITIONS_DEBUGLINUX32SHAREDRTSTATIC) $(INCLUDES_DEBUGLINUX32SHAREDRTSTATIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QBasePlane_Test.cpp -o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QBasePlane_Test.o

$(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QBaseQuadrilateral_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QBaseQuadrilateral_Test.cpp
	$(CXX_DEBUGLINUX32SHAREDRTSTATIC) $(COMPILEROPTIONS_DEBUGLINUX32SHAREDRTSTATIC) $(DEFINITIONS_DEBUGLINUX32SHAREDRTSTATIC) $(INCLUDES_DEBUGLINUX32SHAREDRTSTATIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QBaseQuadrilateral_Test.cpp -o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QBaseQuadrilateral_Test.o

$(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QBaseQuaternion_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QBaseQuaternion_Test.cpp
	$(CXX_DEBUGLINUX32SHAREDRTSTATIC) $(COMPILEROPTIONS_DEBUGLINUX32SHAREDRTSTATIC) $(DEFINITIONS_DEBUGLINUX32SHAREDRTSTATIC) $(INCLUDES_DEBUGLINUX32SHAREDRTSTATIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QBaseQuaternion_Test.cpp -o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QBaseQuaternion_Test.o

$(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QBaseRay_QVector4_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QBaseRay_QVector4_Test.cpp
	$(CXX_DEBUGLINUX32SHAREDRTSTATIC) $(COMPILEROPTIONS_DEBUGLINUX32SHAREDRTSTATIC) $(DEFINITIONS_DEBUGLINUX32SHAREDRTSTATIC) $(INCLUDES_DEBUGLINUX32SHAREDRTSTATIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QBaseRay_QVector4_Test.cpp -o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QBaseRay_QVector4_Test.o

$(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QBaseRay_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QBaseRay_Test.cpp
	$(CXX_DEBUGLINUX32SHAREDRTSTATIC) $(COMPILEROPTIONS_DEBUGLINUX32SHAREDRTSTATIC) $(DEFINITIONS_DEBUGLINUX32SHAREDRTSTATIC) $(INCLUDES_DEBUGLINUX32SHAREDRTSTATIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QBaseRay_Test.cpp -o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QBaseRay_Test.o

$(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QBaseTriangle_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QBaseTriangle_Test.cpp
	$(CXX_DEBUGLINUX32SHAREDRTSTATIC) $(COMPILEROPTIONS_DEBUGLINUX32SHAREDRTSTATIC) $(DEFINITIONS_DEBUGLINUX32SHAREDRTSTATIC) $(INCLUDES_DEBUGLINUX32SHAREDRTSTATIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QBaseTriangle_Test.cpp -o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QBaseTriangle_Test.o

$(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QBaseVector2_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QBaseVector2_Test.cpp
	$(CXX_DEBUGLINUX32SHAREDRTSTATIC) $(COMPILEROPTIONS_DEBUGLINUX32SHAREDRTSTATIC) $(DEFINITIONS_DEBUGLINUX32SHAREDRTSTATIC) $(INCLUDES_DEBUGLINUX32SHAREDRTSTATIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QBaseVector2_Test.cpp -o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QBaseVector2_Test.o

$(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QBaseVector3_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QBaseVector3_Test.cpp
	$(CXX_DEBUGLINUX32SHAREDRTSTATIC) $(COMPILEROPTIONS_DEBUGLINUX32SHAREDRTSTATIC) $(DEFINITIONS_DEBUGLINUX32SHAREDRTSTATIC) $(INCLUDES_DEBUGLINUX32SHAREDRTSTATIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QBaseVector3_Test.cpp -o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QBaseVector3_Test.o

$(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QBaseVector4_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QBaseVector4_Test.cpp
	$(CXX_DEBUGLINUX32SHAREDRTSTATIC) $(COMPILEROPTIONS_DEBUGLINUX32SHAREDRTSTATIC) $(DEFINITIONS_DEBUGLINUX32SHAREDRTSTATIC) $(INCLUDES_DEBUGLINUX32SHAREDRTSTATIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QBaseVector4_Test.cpp -o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QBaseVector4_Test.o

$(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QCircle_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QCircle_Test.cpp
	$(CXX_DEBUGLINUX32SHAREDRTSTATIC) $(COMPILEROPTIONS_DEBUGLINUX32SHAREDRTSTATIC) $(DEFINITIONS_DEBUGLINUX32SHAREDRTSTATIC) $(INCLUDES_DEBUGLINUX32SHAREDRTSTATIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QCircle_Test.cpp -o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QCircle_Test.o

$(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QDualQuaternion_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QDualQuaternion_Test.cpp
	$(CXX_DEBUGLINUX32SHAREDRTSTATIC) $(COMPILEROPTIONS_DEBUGLINUX32SHAREDRTSTATIC) $(DEFINITIONS_DEBUGLINUX32SHAREDRTSTATIC) $(INCLUDES_DEBUGLINUX32SHAREDRTSTATIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QDualQuaternion_Test.cpp -o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QDualQuaternion_Test.o

$(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QHexahedron_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QHexahedron_Test.cpp
	$(CXX_DEBUGLINUX32SHAREDRTSTATIC) $(COMPILEROPTIONS_DEBUGLINUX32SHAREDRTSTATIC) $(DEFINITIONS_DEBUGLINUX32SHAREDRTSTATIC) $(INCLUDES_DEBUGLINUX32SHAREDRTSTATIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QHexahedron_Test.cpp -o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QHexahedron_Test.o

$(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QLineSegment2D_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QLineSegment2D_Test.cpp
	$(CXX_DEBUGLINUX32SHAREDRTSTATIC) $(COMPILEROPTIONS_DEBUGLINUX32SHAREDRTSTATIC) $(DEFINITIONS_DEBUGLINUX32SHAREDRTSTATIC) $(INCLUDES_DEBUGLINUX32SHAREDRTSTATIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QLineSegment2D_Test.cpp -o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QLineSegment2D_Test.o

$(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QLineSegment3D_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QLineSegment3D_Test.cpp
	$(CXX_DEBUGLINUX32SHAREDRTSTATIC) $(COMPILEROPTIONS_DEBUGLINUX32SHAREDRTSTATIC) $(DEFINITIONS_DEBUGLINUX32SHAREDRTSTATIC) $(INCLUDES_DEBUGLINUX32SHAREDRTSTATIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QLineSegment3D_Test.cpp -o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QLineSegment3D_Test.o

$(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QLineSegment_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QLineSegment_Test.cpp
	$(CXX_DEBUGLINUX32SHAREDRTSTATIC) $(COMPILEROPTIONS_DEBUGLINUX32SHAREDRTSTATIC) $(DEFINITIONS_DEBUGLINUX32SHAREDRTSTATIC) $(INCLUDES_DEBUGLINUX32SHAREDRTSTATIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QLineSegment_Test.cpp -o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QLineSegment_Test.o

$(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QMatrix2x2_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QMatrix2x2_Test.cpp
	$(CXX_DEBUGLINUX32SHAREDRTSTATIC) $(COMPILEROPTIONS_DEBUGLINUX32SHAREDRTSTATIC) $(DEFINITIONS_DEBUGLINUX32SHAREDRTSTATIC) $(INCLUDES_DEBUGLINUX32SHAREDRTSTATIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QMatrix2x2_Test.cpp -o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QMatrix2x2_Test.o

$(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QMatrix3x3_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QMatrix3x3_Test.cpp
	$(CXX_DEBUGLINUX32SHAREDRTSTATIC) $(COMPILEROPTIONS_DEBUGLINUX32SHAREDRTSTATIC) $(DEFINITIONS_DEBUGLINUX32SHAREDRTSTATIC) $(INCLUDES_DEBUGLINUX32SHAREDRTSTATIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QMatrix3x3_Test.cpp -o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QMatrix3x3_Test.o

$(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QMatrix3x4_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QMatrix3x4_Test.cpp
	$(CXX_DEBUGLINUX32SHAREDRTSTATIC) $(COMPILEROPTIONS_DEBUGLINUX32SHAREDRTSTATIC) $(DEFINITIONS_DEBUGLINUX32SHAREDRTSTATIC) $(INCLUDES_DEBUGLINUX32SHAREDRTSTATIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QMatrix3x4_Test.cpp -o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QMatrix3x4_Test.o

$(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QMatrix4x3_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QMatrix4x3_Test.cpp
	$(CXX_DEBUGLINUX32SHAREDRTSTATIC) $(COMPILEROPTIONS_DEBUGLINUX32SHAREDRTSTATIC) $(DEFINITIONS_DEBUGLINUX32SHAREDRTSTATIC) $(INCLUDES_DEBUGLINUX32SHAREDRTSTATIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QMatrix4x3_Test.cpp -o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QMatrix4x3_Test.o

$(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QMatrix4x4_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QMatrix4x4_Test.cpp
	$(CXX_DEBUGLINUX32SHAREDRTSTATIC) $(COMPILEROPTIONS_DEBUGLINUX32SHAREDRTSTATIC) $(DEFINITIONS_DEBUGLINUX32SHAREDRTSTATIC) $(INCLUDES_DEBUGLINUX32SHAREDRTSTATIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QMatrix4x4_Test.cpp -o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QMatrix4x4_Test.o

$(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QOrb_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QOrb_Test.cpp
	$(CXX_DEBUGLINUX32SHAREDRTSTATIC) $(COMPILEROPTIONS_DEBUGLINUX32SHAREDRTSTATIC) $(DEFINITIONS_DEBUGLINUX32SHAREDRTSTATIC) $(INCLUDES_DEBUGLINUX32SHAREDRTSTATIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QOrb_Test.cpp -o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QOrb_Test.o

$(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QPlane_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QPlane_Test.cpp
	$(CXX_DEBUGLINUX32SHAREDRTSTATIC) $(COMPILEROPTIONS_DEBUGLINUX32SHAREDRTSTATIC) $(DEFINITIONS_DEBUGLINUX32SHAREDRTSTATIC) $(INCLUDES_DEBUGLINUX32SHAREDRTSTATIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QPlane_Test.cpp -o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QPlane_Test.o

$(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QQuadrilateral_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QQuadrilateral_Test.cpp
	$(CXX_DEBUGLINUX32SHAREDRTSTATIC) $(COMPILEROPTIONS_DEBUGLINUX32SHAREDRTSTATIC) $(DEFINITIONS_DEBUGLINUX32SHAREDRTSTATIC) $(INCLUDES_DEBUGLINUX32SHAREDRTSTATIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QQuadrilateral_Test.cpp -o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QQuadrilateral_Test.o

$(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QQuaternion_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QQuaternion_Test.cpp
	$(CXX_DEBUGLINUX32SHAREDRTSTATIC) $(COMPILEROPTIONS_DEBUGLINUX32SHAREDRTSTATIC) $(DEFINITIONS_DEBUGLINUX32SHAREDRTSTATIC) $(INCLUDES_DEBUGLINUX32SHAREDRTSTATIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QQuaternion_Test.cpp -o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QQuaternion_Test.o

$(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QRay2D_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QRay2D_Test.cpp
	$(CXX_DEBUGLINUX32SHAREDRTSTATIC) $(COMPILEROPTIONS_DEBUGLINUX32SHAREDRTSTATIC) $(DEFINITIONS_DEBUGLINUX32SHAREDRTSTATIC) $(INCLUDES_DEBUGLINUX32SHAREDRTSTATIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QRay2D_Test.cpp -o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QRay2D_Test.o

$(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QRay3D_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QRay3D_Test.cpp
	$(CXX_DEBUGLINUX32SHAREDRTSTATIC) $(COMPILEROPTIONS_DEBUGLINUX32SHAREDRTSTATIC) $(DEFINITIONS_DEBUGLINUX32SHAREDRTSTATIC) $(INCLUDES_DEBUGLINUX32SHAREDRTSTATIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QRay3D_Test.cpp -o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QRay3D_Test.o

$(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QRay_QVector4_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QRay_QVector4_Test.cpp
	$(CXX_DEBUGLINUX32SHAREDRTSTATIC) $(COMPILEROPTIONS_DEBUGLINUX32SHAREDRTSTATIC) $(DEFINITIONS_DEBUGLINUX32SHAREDRTSTATIC) $(INCLUDES_DEBUGLINUX32SHAREDRTSTATIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QRay_QVector4_Test.cpp -o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QRay_QVector4_Test.o

$(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QRay_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QRay_Test.cpp
	$(CXX_DEBUGLINUX32SHAREDRTSTATIC) $(COMPILEROPTIONS_DEBUGLINUX32SHAREDRTSTATIC) $(DEFINITIONS_DEBUGLINUX32SHAREDRTSTATIC) $(INCLUDES_DEBUGLINUX32SHAREDRTSTATIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QRay_Test.cpp -o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QRay_Test.o

$(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QRotationMatrix3x3_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QRotationMatrix3x3_Test.cpp
	$(CXX_DEBUGLINUX32SHAREDRTSTATIC) $(COMPILEROPTIONS_DEBUGLINUX32SHAREDRTSTATIC) $(DEFINITIONS_DEBUGLINUX32SHAREDRTSTATIC) $(INCLUDES_DEBUGLINUX32SHAREDRTSTATIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QRotationMatrix3x3_Test.cpp -o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QRotationMatrix3x3_Test.o

$(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QScalingMatrix3x3_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QScalingMatrix3x3_Test.cpp
	$(CXX_DEBUGLINUX32SHAREDRTSTATIC) $(COMPILEROPTIONS_DEBUGLINUX32SHAREDRTSTATIC) $(DEFINITIONS_DEBUGLINUX32SHAREDRTSTATIC) $(INCLUDES_DEBUGLINUX32SHAREDRTSTATIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QScalingMatrix3x3_Test.cpp -o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QScalingMatrix3x3_Test.o

$(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QSpaceConversionMatrix_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QSpaceConversionMatrix_Test.cpp
	$(CXX_DEBUGLINUX32SHAREDRTSTATIC) $(COMPILEROPTIONS_DEBUGLINUX32SHAREDRTSTATIC) $(DEFINITIONS_DEBUGLINUX32SHAREDRTSTATIC) $(INCLUDES_DEBUGLINUX32SHAREDRTSTATIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QSpaceConversionMatrix_Test.cpp -o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QSpaceConversionMatrix_Test.o

$(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QSphere_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QSphere_Test.cpp
	$(CXX_DEBUGLINUX32SHAREDRTSTATIC) $(COMPILEROPTIONS_DEBUGLINUX32SHAREDRTSTATIC) $(DEFINITIONS_DEBUGLINUX32SHAREDRTSTATIC) $(INCLUDES_DEBUGLINUX32SHAREDRTSTATIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QSphere_Test.cpp -o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QSphere_Test.o

$(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QTransformationMatrix3x3_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QTransformationMatrix3x3_Test.cpp
	$(CXX_DEBUGLINUX32SHAREDRTSTATIC) $(COMPILEROPTIONS_DEBUGLINUX32SHAREDRTSTATIC) $(DEFINITIONS_DEBUGLINUX32SHAREDRTSTATIC) $(INCLUDES_DEBUGLINUX32SHAREDRTSTATIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QTransformationMatrix3x3_Test.cpp -o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QTransformationMatrix3x3_Test.o

$(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QTransformationMatrix_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QTransformationMatrix_Test.cpp
	$(CXX_DEBUGLINUX32SHAREDRTSTATIC) $(COMPILEROPTIONS_DEBUGLINUX32SHAREDRTSTATIC) $(DEFINITIONS_DEBUGLINUX32SHAREDRTSTATIC) $(INCLUDES_DEBUGLINUX32SHAREDRTSTATIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QTransformationMatrix_Test.cpp -o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QTransformationMatrix_Test.o

$(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QTranslationMatrix_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QTranslationMatrix_Test.cpp
	$(CXX_DEBUGLINUX32SHAREDRTSTATIC) $(COMPILEROPTIONS_DEBUGLINUX32SHAREDRTSTATIC) $(DEFINITIONS_DEBUGLINUX32SHAREDRTSTATIC) $(INCLUDES_DEBUGLINUX32SHAREDRTSTATIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QTranslationMatrix_Test.cpp -o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QTranslationMatrix_Test.o

$(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QTriangle2D_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QTriangle2D_Test.cpp
	$(CXX_DEBUGLINUX32SHAREDRTSTATIC) $(COMPILEROPTIONS_DEBUGLINUX32SHAREDRTSTATIC) $(DEFINITIONS_DEBUGLINUX32SHAREDRTSTATIC) $(INCLUDES_DEBUGLINUX32SHAREDRTSTATIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QTriangle2D_Test.cpp -o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QTriangle2D_Test.o

$(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QTriangle3D_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QTriangle3D_Test.cpp
	$(CXX_DEBUGLINUX32SHAREDRTSTATIC) $(COMPILEROPTIONS_DEBUGLINUX32SHAREDRTSTATIC) $(DEFINITIONS_DEBUGLINUX32SHAREDRTSTATIC) $(INCLUDES_DEBUGLINUX32SHAREDRTSTATIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QTriangle3D_Test.cpp -o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QTriangle3D_Test.o

$(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QTriangle_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QTriangle_Test.cpp
	$(CXX_DEBUGLINUX32SHAREDRTSTATIC) $(COMPILEROPTIONS_DEBUGLINUX32SHAREDRTSTATIC) $(DEFINITIONS_DEBUGLINUX32SHAREDRTSTATIC) $(INCLUDES_DEBUGLINUX32SHAREDRTSTATIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QTriangle_Test.cpp -o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QTriangle_Test.o

$(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QVector2_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QVector2_Test.cpp
	$(CXX_DEBUGLINUX32SHAREDRTSTATIC) $(COMPILEROPTIONS_DEBUGLINUX32SHAREDRTSTATIC) $(DEFINITIONS_DEBUGLINUX32SHAREDRTSTATIC) $(INCLUDES_DEBUGLINUX32SHAREDRTSTATIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QVector2_Test.cpp -o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QVector2_Test.o

$(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QVector3_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QVector3_Test.cpp
	$(CXX_DEBUGLINUX32SHAREDRTSTATIC) $(COMPILEROPTIONS_DEBUGLINUX32SHAREDRTSTATIC) $(DEFINITIONS_DEBUGLINUX32SHAREDRTSTATIC) $(INCLUDES_DEBUGLINUX32SHAREDRTSTATIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QVector3_Test.cpp -o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QVector3_Test.o

$(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QVector4_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QVector4_Test.cpp
	$(CXX_DEBUGLINUX32SHAREDRTSTATIC) $(COMPILEROPTIONS_DEBUGLINUX32SHAREDRTSTATIC) $(DEFINITIONS_DEBUGLINUX32SHAREDRTSTATIC) $(INCLUDES_DEBUGLINUX32SHAREDRTSTATIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QVector4_Test.cpp -o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QVector4_Test.o

$(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.SQAngle_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/SQAngle_Test.cpp
	$(CXX_DEBUGLINUX32SHAREDRTSTATIC) $(COMPILEROPTIONS_DEBUGLINUX32SHAREDRTSTATIC) $(DEFINITIONS_DEBUGLINUX32SHAREDRTSTATIC) $(INCLUDES_DEBUGLINUX32SHAREDRTSTATIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/SQAngle_Test.cpp -o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.SQAngle_Test.o

$(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.SQPoint_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/SQPoint_Test.cpp
	$(CXX_DEBUGLINUX32SHAREDRTSTATIC) $(COMPILEROPTIONS_DEBUGLINUX32SHAREDRTSTATIC) $(DEFINITIONS_DEBUGLINUX32SHAREDRTSTATIC) $(INCLUDES_DEBUGLINUX32SHAREDRTSTATIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/SQPoint_Test.cpp -o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.SQPoint_Test.o

$(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QEvent_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QEvent_Test.cpp
	$(CXX_DEBUGLINUX32SHAREDRTSTATIC) $(COMPILEROPTIONS_DEBUGLINUX32SHAREDRTSTATIC) $(DEFINITIONS_DEBUGLINUX32SHAREDRTSTATIC) $(INCLUDES_DEBUGLINUX32SHAREDRTSTATIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QEvent_Test.cpp -o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QEvent_Test.o

$(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTSTATIC)__.__.__.testsystem.EQTestType.o: $(EXECUTION_PATH)../../../testsystem/EQTestType.cpp
	$(CXX_DEBUGLINUX32SHAREDRTSTATIC) $(COMPILEROPTIONS_DEBUGLINUX32SHAREDRTSTATIC) $(DEFINITIONS_DEBUGLINUX32SHAREDRTSTATIC) $(INCLUDES_DEBUGLINUX32SHAREDRTSTATIC) -c $(EXECUTION_PATH)../../../testsystem/EQTestType.cpp -o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTSTATIC)__.__.__.testsystem.EQTestType.o

$(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTSTATIC)__.__.__.testsystem.QCommonTestConfig.o: $(EXECUTION_PATH)../../../testsystem/QCommonTestConfig.cpp
	$(CXX_DEBUGLINUX32SHAREDRTSTATIC) $(COMPILEROPTIONS_DEBUGLINUX32SHAREDRTSTATIC) $(DEFINITIONS_DEBUGLINUX32SHAREDRTSTATIC) $(INCLUDES_DEBUGLINUX32SHAREDRTSTATIC) -c $(EXECUTION_PATH)../../../testsystem/QCommonTestConfig.cpp -o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTSTATIC)__.__.__.testsystem.QCommonTestConfig.o

$(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTSTATIC)__.__.__.testsystem.QSimpleConfigLoader.o: $(EXECUTION_PATH)../../../testsystem/QSimpleConfigLoader.cpp
	$(CXX_DEBUGLINUX32SHAREDRTSTATIC) $(COMPILEROPTIONS_DEBUGLINUX32SHAREDRTSTATIC) $(DEFINITIONS_DEBUGLINUX32SHAREDRTSTATIC) $(INCLUDES_DEBUGLINUX32SHAREDRTSTATIC) -c $(EXECUTION_PATH)../../../testsystem/QSimpleConfigLoader.cpp -o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTSTATIC)__.__.__.testsystem.QSimpleConfigLoader.o

postbuildDebugLinux32SharedrtStatic:
	


buildDebugLinux32SharedrtStatic: prebuildDebugLinux32SharedrtStatic DebugLinux32SharedrtStatic postbuildDebugLinux32SharedrtStatic

cleanDebugLinux32SharedrtStatic:
	rm -f $(OBJECTS_DEBUGLINUX32SHAREDRTSTATIC)
	rm -f $(OUTPUT_DEBUGLINUX32SHAREDRTSTATIC)
	if (test -d $(EXECUTION_PATH)../../../bin/GCC/DebugLinux32SharedrtStatic) then rm -rf "$(EXECUTION_PATH)../../../bin/GCC/DebugLinux32SharedrtStatic"; fi
	if (test -d $(EXECUTION_PATH)../../../bin/GCC/DebugLinux32SharedrtStatic) then rmdir "$(EXECUTION_PATH)../../../bin/GCC/DebugLinux32SharedrtStatic"; fi
	if (test -d $(EXECUTION_PATH)../../../garbage/GCC/DebugLinux32SharedrtStatic) then rm -rf "$(EXECUTION_PATH)../../../garbage/GCC/DebugLinux32SharedrtStatic"; fi
	if (test -d $(EXECUTION_PATH)../../../garbage/GCC/DebugLinux32SharedrtStatic) then rmdir "$(EXECUTION_PATH)../../../garbage/GCC/DebugLinux32SharedrtStatic"; fi


#------------------------------------------------------------
#------------- DebugMac32SharedrtDynamic --------------
#------------------------------------------------------------
CXX_DEBUGMAC32SHAREDRTDYNAMIC = clang++
AR_DEBUGMAC32SHAREDRTDYNAMIC = ar rcu
LD_DEBUGMAC32SHAREDRTDYNAMIC = clang++
AS_DEBUGMAC32SHAREDRTDYNAMIC = llvm-as
INCLUDES_DEBUGMAC32SHAREDRTDYNAMIC = $(INCLUDES_GLOBAL) -I$(EXECUTION_PATH)../../../../headers -I$(EXECUTION_PATH)../../../tests/unit/testmodule_tools -I$(EXECUTION_PATH)../../../tests/unit -I$(EXECUTION_PATH)../../../../3rdparty/ICU/include
LIBRARYDIRS_DEBUGMAC32SHAREDRTDYNAMIC = $(LIBRARYDIRS_GLOBAL) -L$(EXECUTION_PATH)../../../../3rdparty/Boost/bin/Mac32/DebugSharedrtStatic -L$(EXECUTION_PATH)../../../../bin/Clang/DebugMac32SharedrtDynamic
LIBRARIES_DEBUGMAC32SHAREDRTDYNAMIC = $(LIBRARIES_GLOBAL) -lQuimeraEngineTools -lQuimeraEngineCommon -lboost_unit_test_framework-mt-d -licudata -licuuc -licui18n
COMPILEROPTIONS_DEBUGMAC32SHAREDRTDYNAMIC = $(COMPILEROPTIONS_GLOBAL) -g -O0 -Wall -Wno-comment -Wno-unused-local-typedefs -m32 -isystem $(EXECUTION_PATH)../../../../3rdparty/Boost/include
LINKEROPTIONS_DEBUGMAC32SHAREDRTDYNAMIC = $(LINKEROPTIONS_GLOBAL) -m32
DEFINITIONS_DEBUGMAC32SHAREDRTDYNAMIC = $(DEFINITIONS_GLOBAL) -DQE_PREPROCESSOR_IMPORTLIB_QUIMERAENGINE -DBOOST_NO_RTTI -DBOOST_NO_TYPEID
OUTPUT_DEBUGMAC32SHAREDRTDYNAMIC = $(EXECUTION_PATH)../../../bin/Clang/DebugMac32SharedrtDynamic/Unit_TestModule_Tools.sh
INTERMEDIARYDIR_DEBUGMAC32SHAREDRTDYNAMIC = $(EXECUTION_PATH)../../../garbage/Clang/DebugMac32SharedrtDynamic/
OBJECTS_DEBUGMAC32SHAREDRTDYNAMIC = $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.TestModule_Tools.o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QArrayIterator_Test.o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QList_Test.o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QListIterator_Test.o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QNTree_Test.o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.CallCounter.o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QNTreeIterator_Test.o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QBinarySearchTree_Test.o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QConstArrayIterator_Test.o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QConstListIterator_Test.o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QConstNTreeIterator_Test.o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QConstBinarySearchTreeIterator_Test.o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.SQComparatorDefault_Test.o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QKeyValuePair_Test.o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.SQKeyValuePairComparator_Test.o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.SQEqualityComparator_Test.o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QDictionary_Test.o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QHashtable_Test.o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.SQIntegerHashProvider_Test.o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.SQStringHashProvider_Test.o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QConstDictionaryIterator_Test.o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QConstHashtableIterator_Test.o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QArrayDynamic_Test.o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QArrayFixed_Test.o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QDateTime_Test.o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QDstInformation_Test.o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QTimeSpan_Test.o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QTimeZone_Test.o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.SQTimeZoneFactory_Test.o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QBaseDualQuaternion_Test.o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QBaseHexahedron_Test.o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QBaseLineSegment_Test.o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QBaseMatrix2x2_Test.o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QBaseMatrix3x3_Test.o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QBaseMatrix3x4_Test.o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QBaseMatrix4x3_Test.o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QBaseMatrix4x4_Test.o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QBaseOrb_Test.o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QBasePlane_Test.o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QBaseQuadrilateral_Test.o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QBaseQuaternion_Test.o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QBaseRay_QVector4_Test.o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QBaseRay_Test.o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QBaseTriangle_Test.o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QBaseVector2_Test.o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QBaseVector3_Test.o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QBaseVector4_Test.o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QCircle_Test.o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QDualQuaternion_Test.o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QHexahedron_Test.o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QLineSegment2D_Test.o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QLineSegment3D_Test.o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QLineSegment_Test.o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QMatrix2x2_Test.o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QMatrix3x3_Test.o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QMatrix3x4_Test.o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QMatrix4x3_Test.o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QMatrix4x4_Test.o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QOrb_Test.o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QPlane_Test.o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QQuadrilateral_Test.o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QQuaternion_Test.o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QRay2D_Test.o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QRay3D_Test.o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QRay_QVector4_Test.o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QRay_Test.o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QRotationMatrix3x3_Test.o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QScalingMatrix3x3_Test.o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QSpaceConversionMatrix_Test.o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QSphere_Test.o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QTransformationMatrix3x3_Test.o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QTransformationMatrix_Test.o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QTranslationMatrix_Test.o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QTriangle2D_Test.o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QTriangle3D_Test.o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QTriangle_Test.o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QVector2_Test.o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QVector3_Test.o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QVector4_Test.o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.SQAngle_Test.o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.SQPoint_Test.o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QEvent_Test.o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTDYNAMIC)__.__.__.testsystem.EQTestType.o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTDYNAMIC)__.__.__.testsystem.QCommonTestConfig.o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTDYNAMIC)__.__.__.testsystem.QSimpleConfigLoader.o

prebuildDebugMac32SharedrtDynamic:
	if ! (test -d $(EXECUTION_PATH)../../../bin/Clang/DebugMac32SharedrtDynamic) then mkdir -p "$(EXECUTION_PATH)../../../bin/Clang/DebugMac32SharedrtDynamic"; fi
	if ! (test -d $(EXECUTION_PATH)../../../garbage/Clang/DebugMac32SharedrtDynamic) then mkdir -p "$(EXECUTION_PATH)../../../garbage/Clang/DebugMac32SharedrtDynamic"; fi
	mkdir -p $(EXECUTION_PATH)../../../bin/Clang/DebugMac32SharedrtDynamic
	cp "$(EXECUTION_PATH)../../../../bin/Clang/DebugMac32SharedrtDynamic/libQuimeraEngineCommon.dylib" "$(EXECUTION_PATH)../../../bin/Clang/DebugMac32SharedrtDynamic"
	cp "$(EXECUTION_PATH)../../../../bin/Clang/DebugMac32SharedrtDynamic/libQuimeraEngineCommon.dylib" "$(EXECUTION_PATH)."
	cp "$(EXECUTION_PATH)../../../../bin/Clang/DebugMac32SharedrtDynamic/libQuimeraEngineTools.dylib" "$(EXECUTION_PATH)../../../bin/Clang/DebugMac32SharedrtDynamic"
	cp "$(EXECUTION_PATH)../../../../bin/Clang/DebugMac32SharedrtDynamic/libQuimeraEngineTools.dylib" "$(EXECUTION_PATH)."
	cp "$(EXECUTION_PATH)../../../bin/TestConfig.txt" "$(EXECUTION_PATH)../../../bin/Clang/DebugMac32SharedrtDynamic"
	cp "$(EXECUTION_PATH)../../../bin/NormalizationTest.txt" "$(EXECUTION_PATH)../../../bin/Clang/DebugMac32SharedrtDynamic"


DebugMac32SharedrtDynamic: $(OBJECTS_DEBUGMAC32SHAREDRTDYNAMIC)
	$(LD_DEBUGMAC32SHAREDRTDYNAMIC) $(DEFINITIONS_DEBUGMAC32SHAREDRTDYNAMIC) $(LINKEROPTIONS_DEBUGMAC32SHAREDRTDYNAMIC) $(LIBRARYDIRS_DEBUGMAC32SHAREDRTDYNAMIC) $(OBJECTS_DEBUGMAC32SHAREDRTDYNAMIC) $(LIBRARIES_DEBUGMAC32SHAREDRTDYNAMIC) -o $(OUTPUT_DEBUGMAC32SHAREDRTDYNAMIC)

$(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.TestModule_Tools.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/TestModule_Tools.cpp
	$(CXX_DEBUGMAC32SHAREDRTDYNAMIC) $(COMPILEROPTIONS_DEBUGMAC32SHAREDRTDYNAMIC) $(DEFINITIONS_DEBUGMAC32SHAREDRTDYNAMIC) $(INCLUDES_DEBUGMAC32SHAREDRTDYNAMIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/TestModule_Tools.cpp -o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.TestModule_Tools.o

$(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QArrayIterator_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QArrayIterator_Test.cpp
	$(CXX_DEBUGMAC32SHAREDRTDYNAMIC) $(COMPILEROPTIONS_DEBUGMAC32SHAREDRTDYNAMIC) $(DEFINITIONS_DEBUGMAC32SHAREDRTDYNAMIC) $(INCLUDES_DEBUGMAC32SHAREDRTDYNAMIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QArrayIterator_Test.cpp -o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QArrayIterator_Test.o

$(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QList_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QList_Test.cpp
	$(CXX_DEBUGMAC32SHAREDRTDYNAMIC) $(COMPILEROPTIONS_DEBUGMAC32SHAREDRTDYNAMIC) $(DEFINITIONS_DEBUGMAC32SHAREDRTDYNAMIC) $(INCLUDES_DEBUGMAC32SHAREDRTDYNAMIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QList_Test.cpp -o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QList_Test.o

$(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QListIterator_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QListIterator_Test.cpp
	$(CXX_DEBUGMAC32SHAREDRTDYNAMIC) $(COMPILEROPTIONS_DEBUGMAC32SHAREDRTDYNAMIC) $(DEFINITIONS_DEBUGMAC32SHAREDRTDYNAMIC) $(INCLUDES_DEBUGMAC32SHAREDRTDYNAMIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QListIterator_Test.cpp -o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QListIterator_Test.o

$(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QNTree_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QNTree_Test.cpp
	$(CXX_DEBUGMAC32SHAREDRTDYNAMIC) $(COMPILEROPTIONS_DEBUGMAC32SHAREDRTDYNAMIC) $(DEFINITIONS_DEBUGMAC32SHAREDRTDYNAMIC) $(INCLUDES_DEBUGMAC32SHAREDRTDYNAMIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QNTree_Test.cpp -o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QNTree_Test.o

$(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.CallCounter.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/CallCounter.cpp
	$(CXX_DEBUGMAC32SHAREDRTDYNAMIC) $(COMPILEROPTIONS_DEBUGMAC32SHAREDRTDYNAMIC) $(DEFINITIONS_DEBUGMAC32SHAREDRTDYNAMIC) $(INCLUDES_DEBUGMAC32SHAREDRTDYNAMIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/CallCounter.cpp -o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.CallCounter.o

$(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QNTreeIterator_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QNTreeIterator_Test.cpp
	$(CXX_DEBUGMAC32SHAREDRTDYNAMIC) $(COMPILEROPTIONS_DEBUGMAC32SHAREDRTDYNAMIC) $(DEFINITIONS_DEBUGMAC32SHAREDRTDYNAMIC) $(INCLUDES_DEBUGMAC32SHAREDRTDYNAMIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QNTreeIterator_Test.cpp -o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QNTreeIterator_Test.o

$(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QBinarySearchTree_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QBinarySearchTree_Test.cpp
	$(CXX_DEBUGMAC32SHAREDRTDYNAMIC) $(COMPILEROPTIONS_DEBUGMAC32SHAREDRTDYNAMIC) $(DEFINITIONS_DEBUGMAC32SHAREDRTDYNAMIC) $(INCLUDES_DEBUGMAC32SHAREDRTDYNAMIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QBinarySearchTree_Test.cpp -o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QBinarySearchTree_Test.o

$(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QConstArrayIterator_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QConstArrayIterator_Test.cpp
	$(CXX_DEBUGMAC32SHAREDRTDYNAMIC) $(COMPILEROPTIONS_DEBUGMAC32SHAREDRTDYNAMIC) $(DEFINITIONS_DEBUGMAC32SHAREDRTDYNAMIC) $(INCLUDES_DEBUGMAC32SHAREDRTDYNAMIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QConstArrayIterator_Test.cpp -o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QConstArrayIterator_Test.o

$(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QConstListIterator_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QConstListIterator_Test.cpp
	$(CXX_DEBUGMAC32SHAREDRTDYNAMIC) $(COMPILEROPTIONS_DEBUGMAC32SHAREDRTDYNAMIC) $(DEFINITIONS_DEBUGMAC32SHAREDRTDYNAMIC) $(INCLUDES_DEBUGMAC32SHAREDRTDYNAMIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QConstListIterator_Test.cpp -o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QConstListIterator_Test.o

$(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QConstNTreeIterator_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QConstNTreeIterator_Test.cpp
	$(CXX_DEBUGMAC32SHAREDRTDYNAMIC) $(COMPILEROPTIONS_DEBUGMAC32SHAREDRTDYNAMIC) $(DEFINITIONS_DEBUGMAC32SHAREDRTDYNAMIC) $(INCLUDES_DEBUGMAC32SHAREDRTDYNAMIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QConstNTreeIterator_Test.cpp -o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QConstNTreeIterator_Test.o

$(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QConstBinarySearchTreeIterator_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QConstBinarySearchTreeIterator_Test.cpp
	$(CXX_DEBUGMAC32SHAREDRTDYNAMIC) $(COMPILEROPTIONS_DEBUGMAC32SHAREDRTDYNAMIC) $(DEFINITIONS_DEBUGMAC32SHAREDRTDYNAMIC) $(INCLUDES_DEBUGMAC32SHAREDRTDYNAMIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QConstBinarySearchTreeIterator_Test.cpp -o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QConstBinarySearchTreeIterator_Test.o

$(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.SQComparatorDefault_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/SQComparatorDefault_Test.cpp
	$(CXX_DEBUGMAC32SHAREDRTDYNAMIC) $(COMPILEROPTIONS_DEBUGMAC32SHAREDRTDYNAMIC) $(DEFINITIONS_DEBUGMAC32SHAREDRTDYNAMIC) $(INCLUDES_DEBUGMAC32SHAREDRTDYNAMIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/SQComparatorDefault_Test.cpp -o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.SQComparatorDefault_Test.o

$(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QKeyValuePair_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QKeyValuePair_Test.cpp
	$(CXX_DEBUGMAC32SHAREDRTDYNAMIC) $(COMPILEROPTIONS_DEBUGMAC32SHAREDRTDYNAMIC) $(DEFINITIONS_DEBUGMAC32SHAREDRTDYNAMIC) $(INCLUDES_DEBUGMAC32SHAREDRTDYNAMIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QKeyValuePair_Test.cpp -o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QKeyValuePair_Test.o

$(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.SQKeyValuePairComparator_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/SQKeyValuePairComparator_Test.cpp
	$(CXX_DEBUGMAC32SHAREDRTDYNAMIC) $(COMPILEROPTIONS_DEBUGMAC32SHAREDRTDYNAMIC) $(DEFINITIONS_DEBUGMAC32SHAREDRTDYNAMIC) $(INCLUDES_DEBUGMAC32SHAREDRTDYNAMIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/SQKeyValuePairComparator_Test.cpp -o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.SQKeyValuePairComparator_Test.o

$(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.SQEqualityComparator_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/SQEqualityComparator_Test.cpp
	$(CXX_DEBUGMAC32SHAREDRTDYNAMIC) $(COMPILEROPTIONS_DEBUGMAC32SHAREDRTDYNAMIC) $(DEFINITIONS_DEBUGMAC32SHAREDRTDYNAMIC) $(INCLUDES_DEBUGMAC32SHAREDRTDYNAMIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/SQEqualityComparator_Test.cpp -o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.SQEqualityComparator_Test.o

$(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QDictionary_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QDictionary_Test.cpp
	$(CXX_DEBUGMAC32SHAREDRTDYNAMIC) $(COMPILEROPTIONS_DEBUGMAC32SHAREDRTDYNAMIC) $(DEFINITIONS_DEBUGMAC32SHAREDRTDYNAMIC) $(INCLUDES_DEBUGMAC32SHAREDRTDYNAMIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QDictionary_Test.cpp -o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QDictionary_Test.o

$(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QHashtable_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QHashtable_Test.cpp
	$(CXX_DEBUGMAC32SHAREDRTDYNAMIC) $(COMPILEROPTIONS_DEBUGMAC32SHAREDRTDYNAMIC) $(DEFINITIONS_DEBUGMAC32SHAREDRTDYNAMIC) $(INCLUDES_DEBUGMAC32SHAREDRTDYNAMIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QHashtable_Test.cpp -o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QHashtable_Test.o

$(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.SQIntegerHashProvider_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/SQIntegerHashProvider_Test.cpp
	$(CXX_DEBUGMAC32SHAREDRTDYNAMIC) $(COMPILEROPTIONS_DEBUGMAC32SHAREDRTDYNAMIC) $(DEFINITIONS_DEBUGMAC32SHAREDRTDYNAMIC) $(INCLUDES_DEBUGMAC32SHAREDRTDYNAMIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/SQIntegerHashProvider_Test.cpp -o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.SQIntegerHashProvider_Test.o

$(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.SQStringHashProvider_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/SQStringHashProvider_Test.cpp
	$(CXX_DEBUGMAC32SHAREDRTDYNAMIC) $(COMPILEROPTIONS_DEBUGMAC32SHAREDRTDYNAMIC) $(DEFINITIONS_DEBUGMAC32SHAREDRTDYNAMIC) $(INCLUDES_DEBUGMAC32SHAREDRTDYNAMIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/SQStringHashProvider_Test.cpp -o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.SQStringHashProvider_Test.o

$(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QConstDictionaryIterator_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QConstDictionaryIterator_Test.cpp
	$(CXX_DEBUGMAC32SHAREDRTDYNAMIC) $(COMPILEROPTIONS_DEBUGMAC32SHAREDRTDYNAMIC) $(DEFINITIONS_DEBUGMAC32SHAREDRTDYNAMIC) $(INCLUDES_DEBUGMAC32SHAREDRTDYNAMIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QConstDictionaryIterator_Test.cpp -o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QConstDictionaryIterator_Test.o

$(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QConstHashtableIterator_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QConstHashtableIterator_Test.cpp
	$(CXX_DEBUGMAC32SHAREDRTDYNAMIC) $(COMPILEROPTIONS_DEBUGMAC32SHAREDRTDYNAMIC) $(DEFINITIONS_DEBUGMAC32SHAREDRTDYNAMIC) $(INCLUDES_DEBUGMAC32SHAREDRTDYNAMIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QConstHashtableIterator_Test.cpp -o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QConstHashtableIterator_Test.o

$(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QArrayDynamic_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QArrayDynamic_Test.cpp
	$(CXX_DEBUGMAC32SHAREDRTDYNAMIC) $(COMPILEROPTIONS_DEBUGMAC32SHAREDRTDYNAMIC) $(DEFINITIONS_DEBUGMAC32SHAREDRTDYNAMIC) $(INCLUDES_DEBUGMAC32SHAREDRTDYNAMIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QArrayDynamic_Test.cpp -o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QArrayDynamic_Test.o

$(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QArrayFixed_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QArrayFixed_Test.cpp
	$(CXX_DEBUGMAC32SHAREDRTDYNAMIC) $(COMPILEROPTIONS_DEBUGMAC32SHAREDRTDYNAMIC) $(DEFINITIONS_DEBUGMAC32SHAREDRTDYNAMIC) $(INCLUDES_DEBUGMAC32SHAREDRTDYNAMIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QArrayFixed_Test.cpp -o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QArrayFixed_Test.o

$(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QDateTime_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QDateTime_Test.cpp
	$(CXX_DEBUGMAC32SHAREDRTDYNAMIC) $(COMPILEROPTIONS_DEBUGMAC32SHAREDRTDYNAMIC) $(DEFINITIONS_DEBUGMAC32SHAREDRTDYNAMIC) $(INCLUDES_DEBUGMAC32SHAREDRTDYNAMIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QDateTime_Test.cpp -o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QDateTime_Test.o

$(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QDstInformation_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QDstInformation_Test.cpp
	$(CXX_DEBUGMAC32SHAREDRTDYNAMIC) $(COMPILEROPTIONS_DEBUGMAC32SHAREDRTDYNAMIC) $(DEFINITIONS_DEBUGMAC32SHAREDRTDYNAMIC) $(INCLUDES_DEBUGMAC32SHAREDRTDYNAMIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QDstInformation_Test.cpp -o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QDstInformation_Test.o

$(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QTimeSpan_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QTimeSpan_Test.cpp
	$(CXX_DEBUGMAC32SHAREDRTDYNAMIC) $(COMPILEROPTIONS_DEBUGMAC32SHAREDRTDYNAMIC) $(DEFINITIONS_DEBUGMAC32SHAREDRTDYNAMIC) $(INCLUDES_DEBUGMAC32SHAREDRTDYNAMIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QTimeSpan_Test.cpp -o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QTimeSpan_Test.o

$(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QTimeZone_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QTimeZone_Test.cpp
	$(CXX_DEBUGMAC32SHAREDRTDYNAMIC) $(COMPILEROPTIONS_DEBUGMAC32SHAREDRTDYNAMIC) $(DEFINITIONS_DEBUGMAC32SHAREDRTDYNAMIC) $(INCLUDES_DEBUGMAC32SHAREDRTDYNAMIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QTimeZone_Test.cpp -o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QTimeZone_Test.o

$(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.SQTimeZoneFactory_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/SQTimeZoneFactory_Test.cpp
	$(CXX_DEBUGMAC32SHAREDRTDYNAMIC) $(COMPILEROPTIONS_DEBUGMAC32SHAREDRTDYNAMIC) $(DEFINITIONS_DEBUGMAC32SHAREDRTDYNAMIC) $(INCLUDES_DEBUGMAC32SHAREDRTDYNAMIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/SQTimeZoneFactory_Test.cpp -o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.SQTimeZoneFactory_Test.o

$(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QBaseDualQuaternion_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QBaseDualQuaternion_Test.cpp
	$(CXX_DEBUGMAC32SHAREDRTDYNAMIC) $(COMPILEROPTIONS_DEBUGMAC32SHAREDRTDYNAMIC) $(DEFINITIONS_DEBUGMAC32SHAREDRTDYNAMIC) $(INCLUDES_DEBUGMAC32SHAREDRTDYNAMIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QBaseDualQuaternion_Test.cpp -o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QBaseDualQuaternion_Test.o

$(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QBaseHexahedron_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QBaseHexahedron_Test.cpp
	$(CXX_DEBUGMAC32SHAREDRTDYNAMIC) $(COMPILEROPTIONS_DEBUGMAC32SHAREDRTDYNAMIC) $(DEFINITIONS_DEBUGMAC32SHAREDRTDYNAMIC) $(INCLUDES_DEBUGMAC32SHAREDRTDYNAMIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QBaseHexahedron_Test.cpp -o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QBaseHexahedron_Test.o

$(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QBaseLineSegment_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QBaseLineSegment_Test.cpp
	$(CXX_DEBUGMAC32SHAREDRTDYNAMIC) $(COMPILEROPTIONS_DEBUGMAC32SHAREDRTDYNAMIC) $(DEFINITIONS_DEBUGMAC32SHAREDRTDYNAMIC) $(INCLUDES_DEBUGMAC32SHAREDRTDYNAMIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QBaseLineSegment_Test.cpp -o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QBaseLineSegment_Test.o

$(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QBaseMatrix2x2_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QBaseMatrix2x2_Test.cpp
	$(CXX_DEBUGMAC32SHAREDRTDYNAMIC) $(COMPILEROPTIONS_DEBUGMAC32SHAREDRTDYNAMIC) $(DEFINITIONS_DEBUGMAC32SHAREDRTDYNAMIC) $(INCLUDES_DEBUGMAC32SHAREDRTDYNAMIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QBaseMatrix2x2_Test.cpp -o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QBaseMatrix2x2_Test.o

$(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QBaseMatrix3x3_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QBaseMatrix3x3_Test.cpp
	$(CXX_DEBUGMAC32SHAREDRTDYNAMIC) $(COMPILEROPTIONS_DEBUGMAC32SHAREDRTDYNAMIC) $(DEFINITIONS_DEBUGMAC32SHAREDRTDYNAMIC) $(INCLUDES_DEBUGMAC32SHAREDRTDYNAMIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QBaseMatrix3x3_Test.cpp -o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QBaseMatrix3x3_Test.o

$(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QBaseMatrix3x4_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QBaseMatrix3x4_Test.cpp
	$(CXX_DEBUGMAC32SHAREDRTDYNAMIC) $(COMPILEROPTIONS_DEBUGMAC32SHAREDRTDYNAMIC) $(DEFINITIONS_DEBUGMAC32SHAREDRTDYNAMIC) $(INCLUDES_DEBUGMAC32SHAREDRTDYNAMIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QBaseMatrix3x4_Test.cpp -o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QBaseMatrix3x4_Test.o

$(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QBaseMatrix4x3_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QBaseMatrix4x3_Test.cpp
	$(CXX_DEBUGMAC32SHAREDRTDYNAMIC) $(COMPILEROPTIONS_DEBUGMAC32SHAREDRTDYNAMIC) $(DEFINITIONS_DEBUGMAC32SHAREDRTDYNAMIC) $(INCLUDES_DEBUGMAC32SHAREDRTDYNAMIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QBaseMatrix4x3_Test.cpp -o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QBaseMatrix4x3_Test.o

$(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QBaseMatrix4x4_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QBaseMatrix4x4_Test.cpp
	$(CXX_DEBUGMAC32SHAREDRTDYNAMIC) $(COMPILEROPTIONS_DEBUGMAC32SHAREDRTDYNAMIC) $(DEFINITIONS_DEBUGMAC32SHAREDRTDYNAMIC) $(INCLUDES_DEBUGMAC32SHAREDRTDYNAMIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QBaseMatrix4x4_Test.cpp -o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QBaseMatrix4x4_Test.o

$(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QBaseOrb_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QBaseOrb_Test.cpp
	$(CXX_DEBUGMAC32SHAREDRTDYNAMIC) $(COMPILEROPTIONS_DEBUGMAC32SHAREDRTDYNAMIC) $(DEFINITIONS_DEBUGMAC32SHAREDRTDYNAMIC) $(INCLUDES_DEBUGMAC32SHAREDRTDYNAMIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QBaseOrb_Test.cpp -o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QBaseOrb_Test.o

$(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QBasePlane_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QBasePlane_Test.cpp
	$(CXX_DEBUGMAC32SHAREDRTDYNAMIC) $(COMPILEROPTIONS_DEBUGMAC32SHAREDRTDYNAMIC) $(DEFINITIONS_DEBUGMAC32SHAREDRTDYNAMIC) $(INCLUDES_DEBUGMAC32SHAREDRTDYNAMIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QBasePlane_Test.cpp -o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QBasePlane_Test.o

$(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QBaseQuadrilateral_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QBaseQuadrilateral_Test.cpp
	$(CXX_DEBUGMAC32SHAREDRTDYNAMIC) $(COMPILEROPTIONS_DEBUGMAC32SHAREDRTDYNAMIC) $(DEFINITIONS_DEBUGMAC32SHAREDRTDYNAMIC) $(INCLUDES_DEBUGMAC32SHAREDRTDYNAMIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QBaseQuadrilateral_Test.cpp -o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QBaseQuadrilateral_Test.o

$(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QBaseQuaternion_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QBaseQuaternion_Test.cpp
	$(CXX_DEBUGMAC32SHAREDRTDYNAMIC) $(COMPILEROPTIONS_DEBUGMAC32SHAREDRTDYNAMIC) $(DEFINITIONS_DEBUGMAC32SHAREDRTDYNAMIC) $(INCLUDES_DEBUGMAC32SHAREDRTDYNAMIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QBaseQuaternion_Test.cpp -o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QBaseQuaternion_Test.o

$(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QBaseRay_QVector4_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QBaseRay_QVector4_Test.cpp
	$(CXX_DEBUGMAC32SHAREDRTDYNAMIC) $(COMPILEROPTIONS_DEBUGMAC32SHAREDRTDYNAMIC) $(DEFINITIONS_DEBUGMAC32SHAREDRTDYNAMIC) $(INCLUDES_DEBUGMAC32SHAREDRTDYNAMIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QBaseRay_QVector4_Test.cpp -o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QBaseRay_QVector4_Test.o

$(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QBaseRay_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QBaseRay_Test.cpp
	$(CXX_DEBUGMAC32SHAREDRTDYNAMIC) $(COMPILEROPTIONS_DEBUGMAC32SHAREDRTDYNAMIC) $(DEFINITIONS_DEBUGMAC32SHAREDRTDYNAMIC) $(INCLUDES_DEBUGMAC32SHAREDRTDYNAMIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QBaseRay_Test.cpp -o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QBaseRay_Test.o

$(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QBaseTriangle_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QBaseTriangle_Test.cpp
	$(CXX_DEBUGMAC32SHAREDRTDYNAMIC) $(COMPILEROPTIONS_DEBUGMAC32SHAREDRTDYNAMIC) $(DEFINITIONS_DEBUGMAC32SHAREDRTDYNAMIC) $(INCLUDES_DEBUGMAC32SHAREDRTDYNAMIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QBaseTriangle_Test.cpp -o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QBaseTriangle_Test.o

$(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QBaseVector2_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QBaseVector2_Test.cpp
	$(CXX_DEBUGMAC32SHAREDRTDYNAMIC) $(COMPILEROPTIONS_DEBUGMAC32SHAREDRTDYNAMIC) $(DEFINITIONS_DEBUGMAC32SHAREDRTDYNAMIC) $(INCLUDES_DEBUGMAC32SHAREDRTDYNAMIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QBaseVector2_Test.cpp -o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QBaseVector2_Test.o

$(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QBaseVector3_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QBaseVector3_Test.cpp
	$(CXX_DEBUGMAC32SHAREDRTDYNAMIC) $(COMPILEROPTIONS_DEBUGMAC32SHAREDRTDYNAMIC) $(DEFINITIONS_DEBUGMAC32SHAREDRTDYNAMIC) $(INCLUDES_DEBUGMAC32SHAREDRTDYNAMIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QBaseVector3_Test.cpp -o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QBaseVector3_Test.o

$(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QBaseVector4_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QBaseVector4_Test.cpp
	$(CXX_DEBUGMAC32SHAREDRTDYNAMIC) $(COMPILEROPTIONS_DEBUGMAC32SHAREDRTDYNAMIC) $(DEFINITIONS_DEBUGMAC32SHAREDRTDYNAMIC) $(INCLUDES_DEBUGMAC32SHAREDRTDYNAMIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QBaseVector4_Test.cpp -o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QBaseVector4_Test.o

$(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QCircle_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QCircle_Test.cpp
	$(CXX_DEBUGMAC32SHAREDRTDYNAMIC) $(COMPILEROPTIONS_DEBUGMAC32SHAREDRTDYNAMIC) $(DEFINITIONS_DEBUGMAC32SHAREDRTDYNAMIC) $(INCLUDES_DEBUGMAC32SHAREDRTDYNAMIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QCircle_Test.cpp -o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QCircle_Test.o

$(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QDualQuaternion_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QDualQuaternion_Test.cpp
	$(CXX_DEBUGMAC32SHAREDRTDYNAMIC) $(COMPILEROPTIONS_DEBUGMAC32SHAREDRTDYNAMIC) $(DEFINITIONS_DEBUGMAC32SHAREDRTDYNAMIC) $(INCLUDES_DEBUGMAC32SHAREDRTDYNAMIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QDualQuaternion_Test.cpp -o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QDualQuaternion_Test.o

$(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QHexahedron_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QHexahedron_Test.cpp
	$(CXX_DEBUGMAC32SHAREDRTDYNAMIC) $(COMPILEROPTIONS_DEBUGMAC32SHAREDRTDYNAMIC) $(DEFINITIONS_DEBUGMAC32SHAREDRTDYNAMIC) $(INCLUDES_DEBUGMAC32SHAREDRTDYNAMIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QHexahedron_Test.cpp -o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QHexahedron_Test.o

$(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QLineSegment2D_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QLineSegment2D_Test.cpp
	$(CXX_DEBUGMAC32SHAREDRTDYNAMIC) $(COMPILEROPTIONS_DEBUGMAC32SHAREDRTDYNAMIC) $(DEFINITIONS_DEBUGMAC32SHAREDRTDYNAMIC) $(INCLUDES_DEBUGMAC32SHAREDRTDYNAMIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QLineSegment2D_Test.cpp -o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QLineSegment2D_Test.o

$(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QLineSegment3D_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QLineSegment3D_Test.cpp
	$(CXX_DEBUGMAC32SHAREDRTDYNAMIC) $(COMPILEROPTIONS_DEBUGMAC32SHAREDRTDYNAMIC) $(DEFINITIONS_DEBUGMAC32SHAREDRTDYNAMIC) $(INCLUDES_DEBUGMAC32SHAREDRTDYNAMIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QLineSegment3D_Test.cpp -o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QLineSegment3D_Test.o

$(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QLineSegment_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QLineSegment_Test.cpp
	$(CXX_DEBUGMAC32SHAREDRTDYNAMIC) $(COMPILEROPTIONS_DEBUGMAC32SHAREDRTDYNAMIC) $(DEFINITIONS_DEBUGMAC32SHAREDRTDYNAMIC) $(INCLUDES_DEBUGMAC32SHAREDRTDYNAMIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QLineSegment_Test.cpp -o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QLineSegment_Test.o

$(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QMatrix2x2_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QMatrix2x2_Test.cpp
	$(CXX_DEBUGMAC32SHAREDRTDYNAMIC) $(COMPILEROPTIONS_DEBUGMAC32SHAREDRTDYNAMIC) $(DEFINITIONS_DEBUGMAC32SHAREDRTDYNAMIC) $(INCLUDES_DEBUGMAC32SHAREDRTDYNAMIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QMatrix2x2_Test.cpp -o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QMatrix2x2_Test.o

$(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QMatrix3x3_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QMatrix3x3_Test.cpp
	$(CXX_DEBUGMAC32SHAREDRTDYNAMIC) $(COMPILEROPTIONS_DEBUGMAC32SHAREDRTDYNAMIC) $(DEFINITIONS_DEBUGMAC32SHAREDRTDYNAMIC) $(INCLUDES_DEBUGMAC32SHAREDRTDYNAMIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QMatrix3x3_Test.cpp -o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QMatrix3x3_Test.o

$(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QMatrix3x4_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QMatrix3x4_Test.cpp
	$(CXX_DEBUGMAC32SHAREDRTDYNAMIC) $(COMPILEROPTIONS_DEBUGMAC32SHAREDRTDYNAMIC) $(DEFINITIONS_DEBUGMAC32SHAREDRTDYNAMIC) $(INCLUDES_DEBUGMAC32SHAREDRTDYNAMIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QMatrix3x4_Test.cpp -o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QMatrix3x4_Test.o

$(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QMatrix4x3_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QMatrix4x3_Test.cpp
	$(CXX_DEBUGMAC32SHAREDRTDYNAMIC) $(COMPILEROPTIONS_DEBUGMAC32SHAREDRTDYNAMIC) $(DEFINITIONS_DEBUGMAC32SHAREDRTDYNAMIC) $(INCLUDES_DEBUGMAC32SHAREDRTDYNAMIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QMatrix4x3_Test.cpp -o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QMatrix4x3_Test.o

$(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QMatrix4x4_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QMatrix4x4_Test.cpp
	$(CXX_DEBUGMAC32SHAREDRTDYNAMIC) $(COMPILEROPTIONS_DEBUGMAC32SHAREDRTDYNAMIC) $(DEFINITIONS_DEBUGMAC32SHAREDRTDYNAMIC) $(INCLUDES_DEBUGMAC32SHAREDRTDYNAMIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QMatrix4x4_Test.cpp -o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QMatrix4x4_Test.o

$(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QOrb_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QOrb_Test.cpp
	$(CXX_DEBUGMAC32SHAREDRTDYNAMIC) $(COMPILEROPTIONS_DEBUGMAC32SHAREDRTDYNAMIC) $(DEFINITIONS_DEBUGMAC32SHAREDRTDYNAMIC) $(INCLUDES_DEBUGMAC32SHAREDRTDYNAMIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QOrb_Test.cpp -o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QOrb_Test.o

$(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QPlane_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QPlane_Test.cpp
	$(CXX_DEBUGMAC32SHAREDRTDYNAMIC) $(COMPILEROPTIONS_DEBUGMAC32SHAREDRTDYNAMIC) $(DEFINITIONS_DEBUGMAC32SHAREDRTDYNAMIC) $(INCLUDES_DEBUGMAC32SHAREDRTDYNAMIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QPlane_Test.cpp -o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QPlane_Test.o

$(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QQuadrilateral_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QQuadrilateral_Test.cpp
	$(CXX_DEBUGMAC32SHAREDRTDYNAMIC) $(COMPILEROPTIONS_DEBUGMAC32SHAREDRTDYNAMIC) $(DEFINITIONS_DEBUGMAC32SHAREDRTDYNAMIC) $(INCLUDES_DEBUGMAC32SHAREDRTDYNAMIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QQuadrilateral_Test.cpp -o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QQuadrilateral_Test.o

$(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QQuaternion_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QQuaternion_Test.cpp
	$(CXX_DEBUGMAC32SHAREDRTDYNAMIC) $(COMPILEROPTIONS_DEBUGMAC32SHAREDRTDYNAMIC) $(DEFINITIONS_DEBUGMAC32SHAREDRTDYNAMIC) $(INCLUDES_DEBUGMAC32SHAREDRTDYNAMIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QQuaternion_Test.cpp -o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QQuaternion_Test.o

$(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QRay2D_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QRay2D_Test.cpp
	$(CXX_DEBUGMAC32SHAREDRTDYNAMIC) $(COMPILEROPTIONS_DEBUGMAC32SHAREDRTDYNAMIC) $(DEFINITIONS_DEBUGMAC32SHAREDRTDYNAMIC) $(INCLUDES_DEBUGMAC32SHAREDRTDYNAMIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QRay2D_Test.cpp -o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QRay2D_Test.o

$(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QRay3D_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QRay3D_Test.cpp
	$(CXX_DEBUGMAC32SHAREDRTDYNAMIC) $(COMPILEROPTIONS_DEBUGMAC32SHAREDRTDYNAMIC) $(DEFINITIONS_DEBUGMAC32SHAREDRTDYNAMIC) $(INCLUDES_DEBUGMAC32SHAREDRTDYNAMIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QRay3D_Test.cpp -o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QRay3D_Test.o

$(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QRay_QVector4_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QRay_QVector4_Test.cpp
	$(CXX_DEBUGMAC32SHAREDRTDYNAMIC) $(COMPILEROPTIONS_DEBUGMAC32SHAREDRTDYNAMIC) $(DEFINITIONS_DEBUGMAC32SHAREDRTDYNAMIC) $(INCLUDES_DEBUGMAC32SHAREDRTDYNAMIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QRay_QVector4_Test.cpp -o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QRay_QVector4_Test.o

$(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QRay_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QRay_Test.cpp
	$(CXX_DEBUGMAC32SHAREDRTDYNAMIC) $(COMPILEROPTIONS_DEBUGMAC32SHAREDRTDYNAMIC) $(DEFINITIONS_DEBUGMAC32SHAREDRTDYNAMIC) $(INCLUDES_DEBUGMAC32SHAREDRTDYNAMIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QRay_Test.cpp -o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QRay_Test.o

$(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QRotationMatrix3x3_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QRotationMatrix3x3_Test.cpp
	$(CXX_DEBUGMAC32SHAREDRTDYNAMIC) $(COMPILEROPTIONS_DEBUGMAC32SHAREDRTDYNAMIC) $(DEFINITIONS_DEBUGMAC32SHAREDRTDYNAMIC) $(INCLUDES_DEBUGMAC32SHAREDRTDYNAMIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QRotationMatrix3x3_Test.cpp -o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QRotationMatrix3x3_Test.o

$(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QScalingMatrix3x3_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QScalingMatrix3x3_Test.cpp
	$(CXX_DEBUGMAC32SHAREDRTDYNAMIC) $(COMPILEROPTIONS_DEBUGMAC32SHAREDRTDYNAMIC) $(DEFINITIONS_DEBUGMAC32SHAREDRTDYNAMIC) $(INCLUDES_DEBUGMAC32SHAREDRTDYNAMIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QScalingMatrix3x3_Test.cpp -o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QScalingMatrix3x3_Test.o

$(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QSpaceConversionMatrix_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QSpaceConversionMatrix_Test.cpp
	$(CXX_DEBUGMAC32SHAREDRTDYNAMIC) $(COMPILEROPTIONS_DEBUGMAC32SHAREDRTDYNAMIC) $(DEFINITIONS_DEBUGMAC32SHAREDRTDYNAMIC) $(INCLUDES_DEBUGMAC32SHAREDRTDYNAMIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QSpaceConversionMatrix_Test.cpp -o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QSpaceConversionMatrix_Test.o

$(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QSphere_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QSphere_Test.cpp
	$(CXX_DEBUGMAC32SHAREDRTDYNAMIC) $(COMPILEROPTIONS_DEBUGMAC32SHAREDRTDYNAMIC) $(DEFINITIONS_DEBUGMAC32SHAREDRTDYNAMIC) $(INCLUDES_DEBUGMAC32SHAREDRTDYNAMIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QSphere_Test.cpp -o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QSphere_Test.o

$(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QTransformationMatrix3x3_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QTransformationMatrix3x3_Test.cpp
	$(CXX_DEBUGMAC32SHAREDRTDYNAMIC) $(COMPILEROPTIONS_DEBUGMAC32SHAREDRTDYNAMIC) $(DEFINITIONS_DEBUGMAC32SHAREDRTDYNAMIC) $(INCLUDES_DEBUGMAC32SHAREDRTDYNAMIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QTransformationMatrix3x3_Test.cpp -o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QTransformationMatrix3x3_Test.o

$(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QTransformationMatrix_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QTransformationMatrix_Test.cpp
	$(CXX_DEBUGMAC32SHAREDRTDYNAMIC) $(COMPILEROPTIONS_DEBUGMAC32SHAREDRTDYNAMIC) $(DEFINITIONS_DEBUGMAC32SHAREDRTDYNAMIC) $(INCLUDES_DEBUGMAC32SHAREDRTDYNAMIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QTransformationMatrix_Test.cpp -o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QTransformationMatrix_Test.o

$(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QTranslationMatrix_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QTranslationMatrix_Test.cpp
	$(CXX_DEBUGMAC32SHAREDRTDYNAMIC) $(COMPILEROPTIONS_DEBUGMAC32SHAREDRTDYNAMIC) $(DEFINITIONS_DEBUGMAC32SHAREDRTDYNAMIC) $(INCLUDES_DEBUGMAC32SHAREDRTDYNAMIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QTranslationMatrix_Test.cpp -o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QTranslationMatrix_Test.o

$(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QTriangle2D_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QTriangle2D_Test.cpp
	$(CXX_DEBUGMAC32SHAREDRTDYNAMIC) $(COMPILEROPTIONS_DEBUGMAC32SHAREDRTDYNAMIC) $(DEFINITIONS_DEBUGMAC32SHAREDRTDYNAMIC) $(INCLUDES_DEBUGMAC32SHAREDRTDYNAMIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QTriangle2D_Test.cpp -o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QTriangle2D_Test.o

$(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QTriangle3D_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QTriangle3D_Test.cpp
	$(CXX_DEBUGMAC32SHAREDRTDYNAMIC) $(COMPILEROPTIONS_DEBUGMAC32SHAREDRTDYNAMIC) $(DEFINITIONS_DEBUGMAC32SHAREDRTDYNAMIC) $(INCLUDES_DEBUGMAC32SHAREDRTDYNAMIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QTriangle3D_Test.cpp -o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QTriangle3D_Test.o

$(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QTriangle_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QTriangle_Test.cpp
	$(CXX_DEBUGMAC32SHAREDRTDYNAMIC) $(COMPILEROPTIONS_DEBUGMAC32SHAREDRTDYNAMIC) $(DEFINITIONS_DEBUGMAC32SHAREDRTDYNAMIC) $(INCLUDES_DEBUGMAC32SHAREDRTDYNAMIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QTriangle_Test.cpp -o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QTriangle_Test.o

$(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QVector2_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QVector2_Test.cpp
	$(CXX_DEBUGMAC32SHAREDRTDYNAMIC) $(COMPILEROPTIONS_DEBUGMAC32SHAREDRTDYNAMIC) $(DEFINITIONS_DEBUGMAC32SHAREDRTDYNAMIC) $(INCLUDES_DEBUGMAC32SHAREDRTDYNAMIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QVector2_Test.cpp -o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QVector2_Test.o

$(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QVector3_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QVector3_Test.cpp
	$(CXX_DEBUGMAC32SHAREDRTDYNAMIC) $(COMPILEROPTIONS_DEBUGMAC32SHAREDRTDYNAMIC) $(DEFINITIONS_DEBUGMAC32SHAREDRTDYNAMIC) $(INCLUDES_DEBUGMAC32SHAREDRTDYNAMIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QVector3_Test.cpp -o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QVector3_Test.o

$(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QVector4_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QVector4_Test.cpp
	$(CXX_DEBUGMAC32SHAREDRTDYNAMIC) $(COMPILEROPTIONS_DEBUGMAC32SHAREDRTDYNAMIC) $(DEFINITIONS_DEBUGMAC32SHAREDRTDYNAMIC) $(INCLUDES_DEBUGMAC32SHAREDRTDYNAMIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QVector4_Test.cpp -o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QVector4_Test.o

$(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.SQAngle_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/SQAngle_Test.cpp
	$(CXX_DEBUGMAC32SHAREDRTDYNAMIC) $(COMPILEROPTIONS_DEBUGMAC32SHAREDRTDYNAMIC) $(DEFINITIONS_DEBUGMAC32SHAREDRTDYNAMIC) $(INCLUDES_DEBUGMAC32SHAREDRTDYNAMIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/SQAngle_Test.cpp -o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.SQAngle_Test.o

$(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.SQPoint_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/SQPoint_Test.cpp
	$(CXX_DEBUGMAC32SHAREDRTDYNAMIC) $(COMPILEROPTIONS_DEBUGMAC32SHAREDRTDYNAMIC) $(DEFINITIONS_DEBUGMAC32SHAREDRTDYNAMIC) $(INCLUDES_DEBUGMAC32SHAREDRTDYNAMIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/SQPoint_Test.cpp -o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.SQPoint_Test.o

$(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QEvent_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QEvent_Test.cpp
	$(CXX_DEBUGMAC32SHAREDRTDYNAMIC) $(COMPILEROPTIONS_DEBUGMAC32SHAREDRTDYNAMIC) $(DEFINITIONS_DEBUGMAC32SHAREDRTDYNAMIC) $(INCLUDES_DEBUGMAC32SHAREDRTDYNAMIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QEvent_Test.cpp -o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QEvent_Test.o

$(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTDYNAMIC)__.__.__.testsystem.EQTestType.o: $(EXECUTION_PATH)../../../testsystem/EQTestType.cpp
	$(CXX_DEBUGMAC32SHAREDRTDYNAMIC) $(COMPILEROPTIONS_DEBUGMAC32SHAREDRTDYNAMIC) $(DEFINITIONS_DEBUGMAC32SHAREDRTDYNAMIC) $(INCLUDES_DEBUGMAC32SHAREDRTDYNAMIC) -c $(EXECUTION_PATH)../../../testsystem/EQTestType.cpp -o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTDYNAMIC)__.__.__.testsystem.EQTestType.o

$(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTDYNAMIC)__.__.__.testsystem.QCommonTestConfig.o: $(EXECUTION_PATH)../../../testsystem/QCommonTestConfig.cpp
	$(CXX_DEBUGMAC32SHAREDRTDYNAMIC) $(COMPILEROPTIONS_DEBUGMAC32SHAREDRTDYNAMIC) $(DEFINITIONS_DEBUGMAC32SHAREDRTDYNAMIC) $(INCLUDES_DEBUGMAC32SHAREDRTDYNAMIC) -c $(EXECUTION_PATH)../../../testsystem/QCommonTestConfig.cpp -o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTDYNAMIC)__.__.__.testsystem.QCommonTestConfig.o

$(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTDYNAMIC)__.__.__.testsystem.QSimpleConfigLoader.o: $(EXECUTION_PATH)../../../testsystem/QSimpleConfigLoader.cpp
	$(CXX_DEBUGMAC32SHAREDRTDYNAMIC) $(COMPILEROPTIONS_DEBUGMAC32SHAREDRTDYNAMIC) $(DEFINITIONS_DEBUGMAC32SHAREDRTDYNAMIC) $(INCLUDES_DEBUGMAC32SHAREDRTDYNAMIC) -c $(EXECUTION_PATH)../../../testsystem/QSimpleConfigLoader.cpp -o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTDYNAMIC)__.__.__.testsystem.QSimpleConfigLoader.o

postbuildDebugMac32SharedrtDynamic:
	rm -f *.dylib


buildDebugMac32SharedrtDynamic: prebuildDebugMac32SharedrtDynamic DebugMac32SharedrtDynamic postbuildDebugMac32SharedrtDynamic

cleanDebugMac32SharedrtDynamic:
	rm -f $(OBJECTS_DEBUGMAC32SHAREDRTDYNAMIC)
	rm -f $(OUTPUT_DEBUGMAC32SHAREDRTDYNAMIC)
	if (test -d $(EXECUTION_PATH)../../../bin/Clang/DebugMac32SharedrtDynamic) then rm -rf "$(EXECUTION_PATH)../../../bin/Clang/DebugMac32SharedrtDynamic"; fi
	if (test -d $(EXECUTION_PATH)../../../bin/Clang/DebugMac32SharedrtDynamic) then rmdir "$(EXECUTION_PATH)../../../bin/Clang/DebugMac32SharedrtDynamic"; fi
	if (test -d $(EXECUTION_PATH)../../../garbage/Clang/DebugMac32SharedrtDynamic) then rm -rf "$(EXECUTION_PATH)../../../garbage/Clang/DebugMac32SharedrtDynamic"; fi
	if (test -d $(EXECUTION_PATH)../../../garbage/Clang/DebugMac32SharedrtDynamic) then rmdir "$(EXECUTION_PATH)../../../garbage/Clang/DebugMac32SharedrtDynamic"; fi


#------------------------------------------------------------
#------------- DebugMac32SharedrtStatic --------------
#------------------------------------------------------------
CXX_DEBUGMAC32SHAREDRTSTATIC = clang++
AR_DEBUGMAC32SHAREDRTSTATIC = ar rcu
LD_DEBUGMAC32SHAREDRTSTATIC = clang++
AS_DEBUGMAC32SHAREDRTSTATIC = llvm-as
INCLUDES_DEBUGMAC32SHAREDRTSTATIC = $(INCLUDES_GLOBAL) -I$(EXECUTION_PATH)../../../../headers -I$(EXECUTION_PATH)../../../tests/unit -I$(EXECUTION_PATH)../../../../3rdparty/ICU/include
LIBRARYDIRS_DEBUGMAC32SHAREDRTSTATIC = $(LIBRARYDIRS_GLOBAL) -L$(EXECUTION_PATH)../../../../3rdparty/Boost/bin/Mac32/DebugSharedrtStatic -L$(EXECUTION_PATH)../../../../bin/Clang/DebugMac32SharedrtStatic
LIBRARIES_DEBUGMAC32SHAREDRTSTATIC = $(LIBRARIES_GLOBAL) -lQuimeraEngineTools -lQuimeraEngineCommon -lboost_unit_test_framework-mt-d -licudata -licuuc -licui18n
COMPILEROPTIONS_DEBUGMAC32SHAREDRTSTATIC = $(COMPILEROPTIONS_GLOBAL) -g -O0 -Wall -Wno-comment -Wno-unused-local-typedefs -m32 -isystem $(EXECUTION_PATH)../../../../3rdparty/Boost/include
LINKEROPTIONS_DEBUGMAC32SHAREDRTSTATIC = $(LINKEROPTIONS_GLOBAL) -m32
DEFINITIONS_DEBUGMAC32SHAREDRTSTATIC = $(DEFINITIONS_GLOBAL) -DBOOST_NO_RTTI -DBOOST_NO_TYPEID
OUTPUT_DEBUGMAC32SHAREDRTSTATIC = $(EXECUTION_PATH)../../../bin/Clang/DebugMac32SharedrtStatic/Unit_TestModule_Tools.sh
INTERMEDIARYDIR_DEBUGMAC32SHAREDRTSTATIC = $(EXECUTION_PATH)../../../garbage/Clang/DebugMac32SharedrtStatic/
OBJECTS_DEBUGMAC32SHAREDRTSTATIC = $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.TestModule_Tools.o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QArrayIterator_Test.o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QList_Test.o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QListIterator_Test.o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QNTree_Test.o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.CallCounter.o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QNTreeIterator_Test.o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QBinarySearchTree_Test.o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QConstArrayIterator_Test.o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QConstListIterator_Test.o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QConstNTreeIterator_Test.o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QConstBinarySearchTreeIterator_Test.o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.SQComparatorDefault_Test.o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QKeyValuePair_Test.o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.SQKeyValuePairComparator_Test.o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.SQEqualityComparator_Test.o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QDictionary_Test.o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QHashtable_Test.o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.SQIntegerHashProvider_Test.o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.SQStringHashProvider_Test.o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QConstDictionaryIterator_Test.o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QConstHashtableIterator_Test.o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QArrayDynamic_Test.o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QArrayFixed_Test.o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QDateTime_Test.o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QDstInformation_Test.o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QTimeSpan_Test.o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QTimeZone_Test.o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.SQTimeZoneFactory_Test.o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QBaseDualQuaternion_Test.o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QBaseHexahedron_Test.o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QBaseLineSegment_Test.o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QBaseMatrix2x2_Test.o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QBaseMatrix3x3_Test.o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QBaseMatrix3x4_Test.o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QBaseMatrix4x3_Test.o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QBaseMatrix4x4_Test.o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QBaseOrb_Test.o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QBasePlane_Test.o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QBaseQuadrilateral_Test.o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QBaseQuaternion_Test.o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QBaseRay_QVector4_Test.o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QBaseRay_Test.o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QBaseTriangle_Test.o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QBaseVector2_Test.o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QBaseVector3_Test.o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QBaseVector4_Test.o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QCircle_Test.o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QDualQuaternion_Test.o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QHexahedron_Test.o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QLineSegment2D_Test.o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QLineSegment3D_Test.o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QLineSegment_Test.o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QMatrix2x2_Test.o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QMatrix3x3_Test.o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QMatrix3x4_Test.o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QMatrix4x3_Test.o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QMatrix4x4_Test.o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QOrb_Test.o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QPlane_Test.o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QQuadrilateral_Test.o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QQuaternion_Test.o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QRay2D_Test.o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QRay3D_Test.o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QRay_QVector4_Test.o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QRay_Test.o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QRotationMatrix3x3_Test.o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QScalingMatrix3x3_Test.o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QSpaceConversionMatrix_Test.o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QSphere_Test.o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QTransformationMatrix3x3_Test.o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QTransformationMatrix_Test.o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QTranslationMatrix_Test.o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QTriangle2D_Test.o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QTriangle3D_Test.o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QTriangle_Test.o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QVector2_Test.o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QVector3_Test.o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QVector4_Test.o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.SQAngle_Test.o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.SQPoint_Test.o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QEvent_Test.o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTSTATIC)__.__.__.testsystem.EQTestType.o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTSTATIC)__.__.__.testsystem.QCommonTestConfig.o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTSTATIC)__.__.__.testsystem.QSimpleConfigLoader.o

prebuildDebugMac32SharedrtStatic:
	if ! (test -d $(EXECUTION_PATH)../../../bin/Clang/DebugMac32SharedrtStatic) then mkdir -p "$(EXECUTION_PATH)../../../bin/Clang/DebugMac32SharedrtStatic"; fi
	if ! (test -d $(EXECUTION_PATH)../../../garbage/Clang/DebugMac32SharedrtStatic) then mkdir -p "$(EXECUTION_PATH)../../../garbage/Clang/DebugMac32SharedrtStatic"; fi
	mkdir -p $(EXECUTION_PATH)../../../bin/Clang/DebugMac32SharedrtStatic
	cp "$(EXECUTION_PATH)../../../bin/TestConfig.txt" "$(EXECUTION_PATH)../../../bin/Clang/DebugMac32SharedrtStatic"
	cp "$(EXECUTION_PATH)../../../bin/NormalizationTest.txt" "$(EXECUTION_PATH)../../../bin/Clang/DebugMac32SharedrtStatic"
	


DebugMac32SharedrtStatic: $(OBJECTS_DEBUGMAC32SHAREDRTSTATIC)
	$(LD_DEBUGMAC32SHAREDRTSTATIC) $(DEFINITIONS_DEBUGMAC32SHAREDRTSTATIC) $(LINKEROPTIONS_DEBUGMAC32SHAREDRTSTATIC) $(LIBRARYDIRS_DEBUGMAC32SHAREDRTSTATIC) $(OBJECTS_DEBUGMAC32SHAREDRTSTATIC) $(LIBRARIES_DEBUGMAC32SHAREDRTSTATIC) -o $(OUTPUT_DEBUGMAC32SHAREDRTSTATIC)

$(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.TestModule_Tools.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/TestModule_Tools.cpp
	$(CXX_DEBUGMAC32SHAREDRTSTATIC) $(COMPILEROPTIONS_DEBUGMAC32SHAREDRTSTATIC) $(DEFINITIONS_DEBUGMAC32SHAREDRTSTATIC) $(INCLUDES_DEBUGMAC32SHAREDRTSTATIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/TestModule_Tools.cpp -o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.TestModule_Tools.o

$(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QArrayIterator_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QArrayIterator_Test.cpp
	$(CXX_DEBUGMAC32SHAREDRTSTATIC) $(COMPILEROPTIONS_DEBUGMAC32SHAREDRTSTATIC) $(DEFINITIONS_DEBUGMAC32SHAREDRTSTATIC) $(INCLUDES_DEBUGMAC32SHAREDRTSTATIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QArrayIterator_Test.cpp -o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QArrayIterator_Test.o

$(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QList_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QList_Test.cpp
	$(CXX_DEBUGMAC32SHAREDRTSTATIC) $(COMPILEROPTIONS_DEBUGMAC32SHAREDRTSTATIC) $(DEFINITIONS_DEBUGMAC32SHAREDRTSTATIC) $(INCLUDES_DEBUGMAC32SHAREDRTSTATIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QList_Test.cpp -o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QList_Test.o

$(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QListIterator_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QListIterator_Test.cpp
	$(CXX_DEBUGMAC32SHAREDRTSTATIC) $(COMPILEROPTIONS_DEBUGMAC32SHAREDRTSTATIC) $(DEFINITIONS_DEBUGMAC32SHAREDRTSTATIC) $(INCLUDES_DEBUGMAC32SHAREDRTSTATIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QListIterator_Test.cpp -o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QListIterator_Test.o

$(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QNTree_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QNTree_Test.cpp
	$(CXX_DEBUGMAC32SHAREDRTSTATIC) $(COMPILEROPTIONS_DEBUGMAC32SHAREDRTSTATIC) $(DEFINITIONS_DEBUGMAC32SHAREDRTSTATIC) $(INCLUDES_DEBUGMAC32SHAREDRTSTATIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QNTree_Test.cpp -o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QNTree_Test.o

$(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.CallCounter.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/CallCounter.cpp
	$(CXX_DEBUGMAC32SHAREDRTSTATIC) $(COMPILEROPTIONS_DEBUGMAC32SHAREDRTSTATIC) $(DEFINITIONS_DEBUGMAC32SHAREDRTSTATIC) $(INCLUDES_DEBUGMAC32SHAREDRTSTATIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/CallCounter.cpp -o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.CallCounter.o

$(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QNTreeIterator_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QNTreeIterator_Test.cpp
	$(CXX_DEBUGMAC32SHAREDRTSTATIC) $(COMPILEROPTIONS_DEBUGMAC32SHAREDRTSTATIC) $(DEFINITIONS_DEBUGMAC32SHAREDRTSTATIC) $(INCLUDES_DEBUGMAC32SHAREDRTSTATIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QNTreeIterator_Test.cpp -o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QNTreeIterator_Test.o

$(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QBinarySearchTree_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QBinarySearchTree_Test.cpp
	$(CXX_DEBUGMAC32SHAREDRTSTATIC) $(COMPILEROPTIONS_DEBUGMAC32SHAREDRTSTATIC) $(DEFINITIONS_DEBUGMAC32SHAREDRTSTATIC) $(INCLUDES_DEBUGMAC32SHAREDRTSTATIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QBinarySearchTree_Test.cpp -o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QBinarySearchTree_Test.o

$(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QConstArrayIterator_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QConstArrayIterator_Test.cpp
	$(CXX_DEBUGMAC32SHAREDRTSTATIC) $(COMPILEROPTIONS_DEBUGMAC32SHAREDRTSTATIC) $(DEFINITIONS_DEBUGMAC32SHAREDRTSTATIC) $(INCLUDES_DEBUGMAC32SHAREDRTSTATIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QConstArrayIterator_Test.cpp -o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QConstArrayIterator_Test.o

$(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QConstListIterator_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QConstListIterator_Test.cpp
	$(CXX_DEBUGMAC32SHAREDRTSTATIC) $(COMPILEROPTIONS_DEBUGMAC32SHAREDRTSTATIC) $(DEFINITIONS_DEBUGMAC32SHAREDRTSTATIC) $(INCLUDES_DEBUGMAC32SHAREDRTSTATIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QConstListIterator_Test.cpp -o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QConstListIterator_Test.o

$(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QConstNTreeIterator_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QConstNTreeIterator_Test.cpp
	$(CXX_DEBUGMAC32SHAREDRTSTATIC) $(COMPILEROPTIONS_DEBUGMAC32SHAREDRTSTATIC) $(DEFINITIONS_DEBUGMAC32SHAREDRTSTATIC) $(INCLUDES_DEBUGMAC32SHAREDRTSTATIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QConstNTreeIterator_Test.cpp -o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QConstNTreeIterator_Test.o

$(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QConstBinarySearchTreeIterator_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QConstBinarySearchTreeIterator_Test.cpp
	$(CXX_DEBUGMAC32SHAREDRTSTATIC) $(COMPILEROPTIONS_DEBUGMAC32SHAREDRTSTATIC) $(DEFINITIONS_DEBUGMAC32SHAREDRTSTATIC) $(INCLUDES_DEBUGMAC32SHAREDRTSTATIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QConstBinarySearchTreeIterator_Test.cpp -o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QConstBinarySearchTreeIterator_Test.o

$(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.SQComparatorDefault_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/SQComparatorDefault_Test.cpp
	$(CXX_DEBUGMAC32SHAREDRTSTATIC) $(COMPILEROPTIONS_DEBUGMAC32SHAREDRTSTATIC) $(DEFINITIONS_DEBUGMAC32SHAREDRTSTATIC) $(INCLUDES_DEBUGMAC32SHAREDRTSTATIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/SQComparatorDefault_Test.cpp -o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.SQComparatorDefault_Test.o

$(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QKeyValuePair_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QKeyValuePair_Test.cpp
	$(CXX_DEBUGMAC32SHAREDRTSTATIC) $(COMPILEROPTIONS_DEBUGMAC32SHAREDRTSTATIC) $(DEFINITIONS_DEBUGMAC32SHAREDRTSTATIC) $(INCLUDES_DEBUGMAC32SHAREDRTSTATIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QKeyValuePair_Test.cpp -o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QKeyValuePair_Test.o

$(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.SQKeyValuePairComparator_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/SQKeyValuePairComparator_Test.cpp
	$(CXX_DEBUGMAC32SHAREDRTSTATIC) $(COMPILEROPTIONS_DEBUGMAC32SHAREDRTSTATIC) $(DEFINITIONS_DEBUGMAC32SHAREDRTSTATIC) $(INCLUDES_DEBUGMAC32SHAREDRTSTATIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/SQKeyValuePairComparator_Test.cpp -o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.SQKeyValuePairComparator_Test.o

$(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.SQEqualityComparator_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/SQEqualityComparator_Test.cpp
	$(CXX_DEBUGMAC32SHAREDRTSTATIC) $(COMPILEROPTIONS_DEBUGMAC32SHAREDRTSTATIC) $(DEFINITIONS_DEBUGMAC32SHAREDRTSTATIC) $(INCLUDES_DEBUGMAC32SHAREDRTSTATIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/SQEqualityComparator_Test.cpp -o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.SQEqualityComparator_Test.o

$(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QDictionary_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QDictionary_Test.cpp
	$(CXX_DEBUGMAC32SHAREDRTSTATIC) $(COMPILEROPTIONS_DEBUGMAC32SHAREDRTSTATIC) $(DEFINITIONS_DEBUGMAC32SHAREDRTSTATIC) $(INCLUDES_DEBUGMAC32SHAREDRTSTATIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QDictionary_Test.cpp -o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QDictionary_Test.o

$(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QHashtable_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QHashtable_Test.cpp
	$(CXX_DEBUGMAC32SHAREDRTSTATIC) $(COMPILEROPTIONS_DEBUGMAC32SHAREDRTSTATIC) $(DEFINITIONS_DEBUGMAC32SHAREDRTSTATIC) $(INCLUDES_DEBUGMAC32SHAREDRTSTATIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QHashtable_Test.cpp -o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QHashtable_Test.o

$(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.SQIntegerHashProvider_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/SQIntegerHashProvider_Test.cpp
	$(CXX_DEBUGMAC32SHAREDRTSTATIC) $(COMPILEROPTIONS_DEBUGMAC32SHAREDRTSTATIC) $(DEFINITIONS_DEBUGMAC32SHAREDRTSTATIC) $(INCLUDES_DEBUGMAC32SHAREDRTSTATIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/SQIntegerHashProvider_Test.cpp -o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.SQIntegerHashProvider_Test.o

$(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.SQStringHashProvider_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/SQStringHashProvider_Test.cpp
	$(CXX_DEBUGMAC32SHAREDRTSTATIC) $(COMPILEROPTIONS_DEBUGMAC32SHAREDRTSTATIC) $(DEFINITIONS_DEBUGMAC32SHAREDRTSTATIC) $(INCLUDES_DEBUGMAC32SHAREDRTSTATIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/SQStringHashProvider_Test.cpp -o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.SQStringHashProvider_Test.o

$(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QConstDictionaryIterator_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QConstDictionaryIterator_Test.cpp
	$(CXX_DEBUGMAC32SHAREDRTSTATIC) $(COMPILEROPTIONS_DEBUGMAC32SHAREDRTSTATIC) $(DEFINITIONS_DEBUGMAC32SHAREDRTSTATIC) $(INCLUDES_DEBUGMAC32SHAREDRTSTATIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QConstDictionaryIterator_Test.cpp -o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QConstDictionaryIterator_Test.o

$(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QConstHashtableIterator_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QConstHashtableIterator_Test.cpp
	$(CXX_DEBUGMAC32SHAREDRTSTATIC) $(COMPILEROPTIONS_DEBUGMAC32SHAREDRTSTATIC) $(DEFINITIONS_DEBUGMAC32SHAREDRTSTATIC) $(INCLUDES_DEBUGMAC32SHAREDRTSTATIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QConstHashtableIterator_Test.cpp -o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QConstHashtableIterator_Test.o

$(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QArrayDynamic_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QArrayDynamic_Test.cpp
	$(CXX_DEBUGMAC32SHAREDRTSTATIC) $(COMPILEROPTIONS_DEBUGMAC32SHAREDRTSTATIC) $(DEFINITIONS_DEBUGMAC32SHAREDRTSTATIC) $(INCLUDES_DEBUGMAC32SHAREDRTSTATIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QArrayDynamic_Test.cpp -o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QArrayDynamic_Test.o

$(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QArrayFixed_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QArrayFixed_Test.cpp
	$(CXX_DEBUGMAC32SHAREDRTSTATIC) $(COMPILEROPTIONS_DEBUGMAC32SHAREDRTSTATIC) $(DEFINITIONS_DEBUGMAC32SHAREDRTSTATIC) $(INCLUDES_DEBUGMAC32SHAREDRTSTATIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QArrayFixed_Test.cpp -o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QArrayFixed_Test.o

$(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QDateTime_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QDateTime_Test.cpp
	$(CXX_DEBUGMAC32SHAREDRTSTATIC) $(COMPILEROPTIONS_DEBUGMAC32SHAREDRTSTATIC) $(DEFINITIONS_DEBUGMAC32SHAREDRTSTATIC) $(INCLUDES_DEBUGMAC32SHAREDRTSTATIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QDateTime_Test.cpp -o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QDateTime_Test.o

$(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QDstInformation_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QDstInformation_Test.cpp
	$(CXX_DEBUGMAC32SHAREDRTSTATIC) $(COMPILEROPTIONS_DEBUGMAC32SHAREDRTSTATIC) $(DEFINITIONS_DEBUGMAC32SHAREDRTSTATIC) $(INCLUDES_DEBUGMAC32SHAREDRTSTATIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QDstInformation_Test.cpp -o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QDstInformation_Test.o

$(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QTimeSpan_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QTimeSpan_Test.cpp
	$(CXX_DEBUGMAC32SHAREDRTSTATIC) $(COMPILEROPTIONS_DEBUGMAC32SHAREDRTSTATIC) $(DEFINITIONS_DEBUGMAC32SHAREDRTSTATIC) $(INCLUDES_DEBUGMAC32SHAREDRTSTATIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QTimeSpan_Test.cpp -o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QTimeSpan_Test.o

$(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QTimeZone_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QTimeZone_Test.cpp
	$(CXX_DEBUGMAC32SHAREDRTSTATIC) $(COMPILEROPTIONS_DEBUGMAC32SHAREDRTSTATIC) $(DEFINITIONS_DEBUGMAC32SHAREDRTSTATIC) $(INCLUDES_DEBUGMAC32SHAREDRTSTATIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QTimeZone_Test.cpp -o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QTimeZone_Test.o

$(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.SQTimeZoneFactory_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/SQTimeZoneFactory_Test.cpp
	$(CXX_DEBUGMAC32SHAREDRTSTATIC) $(COMPILEROPTIONS_DEBUGMAC32SHAREDRTSTATIC) $(DEFINITIONS_DEBUGMAC32SHAREDRTSTATIC) $(INCLUDES_DEBUGMAC32SHAREDRTSTATIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/SQTimeZoneFactory_Test.cpp -o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.SQTimeZoneFactory_Test.o

$(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QBaseDualQuaternion_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QBaseDualQuaternion_Test.cpp
	$(CXX_DEBUGMAC32SHAREDRTSTATIC) $(COMPILEROPTIONS_DEBUGMAC32SHAREDRTSTATIC) $(DEFINITIONS_DEBUGMAC32SHAREDRTSTATIC) $(INCLUDES_DEBUGMAC32SHAREDRTSTATIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QBaseDualQuaternion_Test.cpp -o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QBaseDualQuaternion_Test.o

$(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QBaseHexahedron_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QBaseHexahedron_Test.cpp
	$(CXX_DEBUGMAC32SHAREDRTSTATIC) $(COMPILEROPTIONS_DEBUGMAC32SHAREDRTSTATIC) $(DEFINITIONS_DEBUGMAC32SHAREDRTSTATIC) $(INCLUDES_DEBUGMAC32SHAREDRTSTATIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QBaseHexahedron_Test.cpp -o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QBaseHexahedron_Test.o

$(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QBaseLineSegment_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QBaseLineSegment_Test.cpp
	$(CXX_DEBUGMAC32SHAREDRTSTATIC) $(COMPILEROPTIONS_DEBUGMAC32SHAREDRTSTATIC) $(DEFINITIONS_DEBUGMAC32SHAREDRTSTATIC) $(INCLUDES_DEBUGMAC32SHAREDRTSTATIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QBaseLineSegment_Test.cpp -o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QBaseLineSegment_Test.o

$(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QBaseMatrix2x2_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QBaseMatrix2x2_Test.cpp
	$(CXX_DEBUGMAC32SHAREDRTSTATIC) $(COMPILEROPTIONS_DEBUGMAC32SHAREDRTSTATIC) $(DEFINITIONS_DEBUGMAC32SHAREDRTSTATIC) $(INCLUDES_DEBUGMAC32SHAREDRTSTATIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QBaseMatrix2x2_Test.cpp -o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QBaseMatrix2x2_Test.o

$(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QBaseMatrix3x3_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QBaseMatrix3x3_Test.cpp
	$(CXX_DEBUGMAC32SHAREDRTSTATIC) $(COMPILEROPTIONS_DEBUGMAC32SHAREDRTSTATIC) $(DEFINITIONS_DEBUGMAC32SHAREDRTSTATIC) $(INCLUDES_DEBUGMAC32SHAREDRTSTATIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QBaseMatrix3x3_Test.cpp -o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QBaseMatrix3x3_Test.o

$(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QBaseMatrix3x4_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QBaseMatrix3x4_Test.cpp
	$(CXX_DEBUGMAC32SHAREDRTSTATIC) $(COMPILEROPTIONS_DEBUGMAC32SHAREDRTSTATIC) $(DEFINITIONS_DEBUGMAC32SHAREDRTSTATIC) $(INCLUDES_DEBUGMAC32SHAREDRTSTATIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QBaseMatrix3x4_Test.cpp -o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QBaseMatrix3x4_Test.o

$(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QBaseMatrix4x3_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QBaseMatrix4x3_Test.cpp
	$(CXX_DEBUGMAC32SHAREDRTSTATIC) $(COMPILEROPTIONS_DEBUGMAC32SHAREDRTSTATIC) $(DEFINITIONS_DEBUGMAC32SHAREDRTSTATIC) $(INCLUDES_DEBUGMAC32SHAREDRTSTATIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QBaseMatrix4x3_Test.cpp -o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QBaseMatrix4x3_Test.o

$(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QBaseMatrix4x4_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QBaseMatrix4x4_Test.cpp
	$(CXX_DEBUGMAC32SHAREDRTSTATIC) $(COMPILEROPTIONS_DEBUGMAC32SHAREDRTSTATIC) $(DEFINITIONS_DEBUGMAC32SHAREDRTSTATIC) $(INCLUDES_DEBUGMAC32SHAREDRTSTATIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QBaseMatrix4x4_Test.cpp -o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QBaseMatrix4x4_Test.o

$(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QBaseOrb_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QBaseOrb_Test.cpp
	$(CXX_DEBUGMAC32SHAREDRTSTATIC) $(COMPILEROPTIONS_DEBUGMAC32SHAREDRTSTATIC) $(DEFINITIONS_DEBUGMAC32SHAREDRTSTATIC) $(INCLUDES_DEBUGMAC32SHAREDRTSTATIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QBaseOrb_Test.cpp -o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QBaseOrb_Test.o

$(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QBasePlane_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QBasePlane_Test.cpp
	$(CXX_DEBUGMAC32SHAREDRTSTATIC) $(COMPILEROPTIONS_DEBUGMAC32SHAREDRTSTATIC) $(DEFINITIONS_DEBUGMAC32SHAREDRTSTATIC) $(INCLUDES_DEBUGMAC32SHAREDRTSTATIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QBasePlane_Test.cpp -o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QBasePlane_Test.o

$(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QBaseQuadrilateral_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QBaseQuadrilateral_Test.cpp
	$(CXX_DEBUGMAC32SHAREDRTSTATIC) $(COMPILEROPTIONS_DEBUGMAC32SHAREDRTSTATIC) $(DEFINITIONS_DEBUGMAC32SHAREDRTSTATIC) $(INCLUDES_DEBUGMAC32SHAREDRTSTATIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QBaseQuadrilateral_Test.cpp -o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QBaseQuadrilateral_Test.o

$(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QBaseQuaternion_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QBaseQuaternion_Test.cpp
	$(CXX_DEBUGMAC32SHAREDRTSTATIC) $(COMPILEROPTIONS_DEBUGMAC32SHAREDRTSTATIC) $(DEFINITIONS_DEBUGMAC32SHAREDRTSTATIC) $(INCLUDES_DEBUGMAC32SHAREDRTSTATIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QBaseQuaternion_Test.cpp -o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QBaseQuaternion_Test.o

$(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QBaseRay_QVector4_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QBaseRay_QVector4_Test.cpp
	$(CXX_DEBUGMAC32SHAREDRTSTATIC) $(COMPILEROPTIONS_DEBUGMAC32SHAREDRTSTATIC) $(DEFINITIONS_DEBUGMAC32SHAREDRTSTATIC) $(INCLUDES_DEBUGMAC32SHAREDRTSTATIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QBaseRay_QVector4_Test.cpp -o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QBaseRay_QVector4_Test.o

$(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QBaseRay_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QBaseRay_Test.cpp
	$(CXX_DEBUGMAC32SHAREDRTSTATIC) $(COMPILEROPTIONS_DEBUGMAC32SHAREDRTSTATIC) $(DEFINITIONS_DEBUGMAC32SHAREDRTSTATIC) $(INCLUDES_DEBUGMAC32SHAREDRTSTATIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QBaseRay_Test.cpp -o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QBaseRay_Test.o

$(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QBaseTriangle_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QBaseTriangle_Test.cpp
	$(CXX_DEBUGMAC32SHAREDRTSTATIC) $(COMPILEROPTIONS_DEBUGMAC32SHAREDRTSTATIC) $(DEFINITIONS_DEBUGMAC32SHAREDRTSTATIC) $(INCLUDES_DEBUGMAC32SHAREDRTSTATIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QBaseTriangle_Test.cpp -o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QBaseTriangle_Test.o

$(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QBaseVector2_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QBaseVector2_Test.cpp
	$(CXX_DEBUGMAC32SHAREDRTSTATIC) $(COMPILEROPTIONS_DEBUGMAC32SHAREDRTSTATIC) $(DEFINITIONS_DEBUGMAC32SHAREDRTSTATIC) $(INCLUDES_DEBUGMAC32SHAREDRTSTATIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QBaseVector2_Test.cpp -o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QBaseVector2_Test.o

$(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QBaseVector3_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QBaseVector3_Test.cpp
	$(CXX_DEBUGMAC32SHAREDRTSTATIC) $(COMPILEROPTIONS_DEBUGMAC32SHAREDRTSTATIC) $(DEFINITIONS_DEBUGMAC32SHAREDRTSTATIC) $(INCLUDES_DEBUGMAC32SHAREDRTSTATIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QBaseVector3_Test.cpp -o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QBaseVector3_Test.o

$(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QBaseVector4_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QBaseVector4_Test.cpp
	$(CXX_DEBUGMAC32SHAREDRTSTATIC) $(COMPILEROPTIONS_DEBUGMAC32SHAREDRTSTATIC) $(DEFINITIONS_DEBUGMAC32SHAREDRTSTATIC) $(INCLUDES_DEBUGMAC32SHAREDRTSTATIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QBaseVector4_Test.cpp -o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QBaseVector4_Test.o

$(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QCircle_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QCircle_Test.cpp
	$(CXX_DEBUGMAC32SHAREDRTSTATIC) $(COMPILEROPTIONS_DEBUGMAC32SHAREDRTSTATIC) $(DEFINITIONS_DEBUGMAC32SHAREDRTSTATIC) $(INCLUDES_DEBUGMAC32SHAREDRTSTATIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QCircle_Test.cpp -o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QCircle_Test.o

$(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QDualQuaternion_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QDualQuaternion_Test.cpp
	$(CXX_DEBUGMAC32SHAREDRTSTATIC) $(COMPILEROPTIONS_DEBUGMAC32SHAREDRTSTATIC) $(DEFINITIONS_DEBUGMAC32SHAREDRTSTATIC) $(INCLUDES_DEBUGMAC32SHAREDRTSTATIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QDualQuaternion_Test.cpp -o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QDualQuaternion_Test.o

$(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QHexahedron_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QHexahedron_Test.cpp
	$(CXX_DEBUGMAC32SHAREDRTSTATIC) $(COMPILEROPTIONS_DEBUGMAC32SHAREDRTSTATIC) $(DEFINITIONS_DEBUGMAC32SHAREDRTSTATIC) $(INCLUDES_DEBUGMAC32SHAREDRTSTATIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QHexahedron_Test.cpp -o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QHexahedron_Test.o

$(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QLineSegment2D_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QLineSegment2D_Test.cpp
	$(CXX_DEBUGMAC32SHAREDRTSTATIC) $(COMPILEROPTIONS_DEBUGMAC32SHAREDRTSTATIC) $(DEFINITIONS_DEBUGMAC32SHAREDRTSTATIC) $(INCLUDES_DEBUGMAC32SHAREDRTSTATIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QLineSegment2D_Test.cpp -o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QLineSegment2D_Test.o

$(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QLineSegment3D_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QLineSegment3D_Test.cpp
	$(CXX_DEBUGMAC32SHAREDRTSTATIC) $(COMPILEROPTIONS_DEBUGMAC32SHAREDRTSTATIC) $(DEFINITIONS_DEBUGMAC32SHAREDRTSTATIC) $(INCLUDES_DEBUGMAC32SHAREDRTSTATIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QLineSegment3D_Test.cpp -o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QLineSegment3D_Test.o

$(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QLineSegment_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QLineSegment_Test.cpp
	$(CXX_DEBUGMAC32SHAREDRTSTATIC) $(COMPILEROPTIONS_DEBUGMAC32SHAREDRTSTATIC) $(DEFINITIONS_DEBUGMAC32SHAREDRTSTATIC) $(INCLUDES_DEBUGMAC32SHAREDRTSTATIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QLineSegment_Test.cpp -o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QLineSegment_Test.o

$(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QMatrix2x2_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QMatrix2x2_Test.cpp
	$(CXX_DEBUGMAC32SHAREDRTSTATIC) $(COMPILEROPTIONS_DEBUGMAC32SHAREDRTSTATIC) $(DEFINITIONS_DEBUGMAC32SHAREDRTSTATIC) $(INCLUDES_DEBUGMAC32SHAREDRTSTATIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QMatrix2x2_Test.cpp -o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QMatrix2x2_Test.o

$(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QMatrix3x3_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QMatrix3x3_Test.cpp
	$(CXX_DEBUGMAC32SHAREDRTSTATIC) $(COMPILEROPTIONS_DEBUGMAC32SHAREDRTSTATIC) $(DEFINITIONS_DEBUGMAC32SHAREDRTSTATIC) $(INCLUDES_DEBUGMAC32SHAREDRTSTATIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QMatrix3x3_Test.cpp -o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QMatrix3x3_Test.o

$(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QMatrix3x4_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QMatrix3x4_Test.cpp
	$(CXX_DEBUGMAC32SHAREDRTSTATIC) $(COMPILEROPTIONS_DEBUGMAC32SHAREDRTSTATIC) $(DEFINITIONS_DEBUGMAC32SHAREDRTSTATIC) $(INCLUDES_DEBUGMAC32SHAREDRTSTATIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QMatrix3x4_Test.cpp -o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QMatrix3x4_Test.o

$(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QMatrix4x3_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QMatrix4x3_Test.cpp
	$(CXX_DEBUGMAC32SHAREDRTSTATIC) $(COMPILEROPTIONS_DEBUGMAC32SHAREDRTSTATIC) $(DEFINITIONS_DEBUGMAC32SHAREDRTSTATIC) $(INCLUDES_DEBUGMAC32SHAREDRTSTATIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QMatrix4x3_Test.cpp -o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QMatrix4x3_Test.o

$(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QMatrix4x4_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QMatrix4x4_Test.cpp
	$(CXX_DEBUGMAC32SHAREDRTSTATIC) $(COMPILEROPTIONS_DEBUGMAC32SHAREDRTSTATIC) $(DEFINITIONS_DEBUGMAC32SHAREDRTSTATIC) $(INCLUDES_DEBUGMAC32SHAREDRTSTATIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QMatrix4x4_Test.cpp -o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QMatrix4x4_Test.o

$(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QOrb_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QOrb_Test.cpp
	$(CXX_DEBUGMAC32SHAREDRTSTATIC) $(COMPILEROPTIONS_DEBUGMAC32SHAREDRTSTATIC) $(DEFINITIONS_DEBUGMAC32SHAREDRTSTATIC) $(INCLUDES_DEBUGMAC32SHAREDRTSTATIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QOrb_Test.cpp -o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QOrb_Test.o

$(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QPlane_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QPlane_Test.cpp
	$(CXX_DEBUGMAC32SHAREDRTSTATIC) $(COMPILEROPTIONS_DEBUGMAC32SHAREDRTSTATIC) $(DEFINITIONS_DEBUGMAC32SHAREDRTSTATIC) $(INCLUDES_DEBUGMAC32SHAREDRTSTATIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QPlane_Test.cpp -o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QPlane_Test.o

$(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QQuadrilateral_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QQuadrilateral_Test.cpp
	$(CXX_DEBUGMAC32SHAREDRTSTATIC) $(COMPILEROPTIONS_DEBUGMAC32SHAREDRTSTATIC) $(DEFINITIONS_DEBUGMAC32SHAREDRTSTATIC) $(INCLUDES_DEBUGMAC32SHAREDRTSTATIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QQuadrilateral_Test.cpp -o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QQuadrilateral_Test.o

$(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QQuaternion_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QQuaternion_Test.cpp
	$(CXX_DEBUGMAC32SHAREDRTSTATIC) $(COMPILEROPTIONS_DEBUGMAC32SHAREDRTSTATIC) $(DEFINITIONS_DEBUGMAC32SHAREDRTSTATIC) $(INCLUDES_DEBUGMAC32SHAREDRTSTATIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QQuaternion_Test.cpp -o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QQuaternion_Test.o

$(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QRay2D_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QRay2D_Test.cpp
	$(CXX_DEBUGMAC32SHAREDRTSTATIC) $(COMPILEROPTIONS_DEBUGMAC32SHAREDRTSTATIC) $(DEFINITIONS_DEBUGMAC32SHAREDRTSTATIC) $(INCLUDES_DEBUGMAC32SHAREDRTSTATIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QRay2D_Test.cpp -o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QRay2D_Test.o

$(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QRay3D_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QRay3D_Test.cpp
	$(CXX_DEBUGMAC32SHAREDRTSTATIC) $(COMPILEROPTIONS_DEBUGMAC32SHAREDRTSTATIC) $(DEFINITIONS_DEBUGMAC32SHAREDRTSTATIC) $(INCLUDES_DEBUGMAC32SHAREDRTSTATIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QRay3D_Test.cpp -o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QRay3D_Test.o

$(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QRay_QVector4_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QRay_QVector4_Test.cpp
	$(CXX_DEBUGMAC32SHAREDRTSTATIC) $(COMPILEROPTIONS_DEBUGMAC32SHAREDRTSTATIC) $(DEFINITIONS_DEBUGMAC32SHAREDRTSTATIC) $(INCLUDES_DEBUGMAC32SHAREDRTSTATIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QRay_QVector4_Test.cpp -o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QRay_QVector4_Test.o

$(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QRay_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QRay_Test.cpp
	$(CXX_DEBUGMAC32SHAREDRTSTATIC) $(COMPILEROPTIONS_DEBUGMAC32SHAREDRTSTATIC) $(DEFINITIONS_DEBUGMAC32SHAREDRTSTATIC) $(INCLUDES_DEBUGMAC32SHAREDRTSTATIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QRay_Test.cpp -o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QRay_Test.o

$(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QRotationMatrix3x3_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QRotationMatrix3x3_Test.cpp
	$(CXX_DEBUGMAC32SHAREDRTSTATIC) $(COMPILEROPTIONS_DEBUGMAC32SHAREDRTSTATIC) $(DEFINITIONS_DEBUGMAC32SHAREDRTSTATIC) $(INCLUDES_DEBUGMAC32SHAREDRTSTATIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QRotationMatrix3x3_Test.cpp -o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QRotationMatrix3x3_Test.o

$(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QScalingMatrix3x3_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QScalingMatrix3x3_Test.cpp
	$(CXX_DEBUGMAC32SHAREDRTSTATIC) $(COMPILEROPTIONS_DEBUGMAC32SHAREDRTSTATIC) $(DEFINITIONS_DEBUGMAC32SHAREDRTSTATIC) $(INCLUDES_DEBUGMAC32SHAREDRTSTATIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QScalingMatrix3x3_Test.cpp -o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QScalingMatrix3x3_Test.o

$(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QSpaceConversionMatrix_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QSpaceConversionMatrix_Test.cpp
	$(CXX_DEBUGMAC32SHAREDRTSTATIC) $(COMPILEROPTIONS_DEBUGMAC32SHAREDRTSTATIC) $(DEFINITIONS_DEBUGMAC32SHAREDRTSTATIC) $(INCLUDES_DEBUGMAC32SHAREDRTSTATIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QSpaceConversionMatrix_Test.cpp -o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QSpaceConversionMatrix_Test.o

$(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QSphere_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QSphere_Test.cpp
	$(CXX_DEBUGMAC32SHAREDRTSTATIC) $(COMPILEROPTIONS_DEBUGMAC32SHAREDRTSTATIC) $(DEFINITIONS_DEBUGMAC32SHAREDRTSTATIC) $(INCLUDES_DEBUGMAC32SHAREDRTSTATIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QSphere_Test.cpp -o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QSphere_Test.o

$(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QTransformationMatrix3x3_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QTransformationMatrix3x3_Test.cpp
	$(CXX_DEBUGMAC32SHAREDRTSTATIC) $(COMPILEROPTIONS_DEBUGMAC32SHAREDRTSTATIC) $(DEFINITIONS_DEBUGMAC32SHAREDRTSTATIC) $(INCLUDES_DEBUGMAC32SHAREDRTSTATIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QTransformationMatrix3x3_Test.cpp -o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QTransformationMatrix3x3_Test.o

$(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QTransformationMatrix_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QTransformationMatrix_Test.cpp
	$(CXX_DEBUGMAC32SHAREDRTSTATIC) $(COMPILEROPTIONS_DEBUGMAC32SHAREDRTSTATIC) $(DEFINITIONS_DEBUGMAC32SHAREDRTSTATIC) $(INCLUDES_DEBUGMAC32SHAREDRTSTATIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QTransformationMatrix_Test.cpp -o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QTransformationMatrix_Test.o

$(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QTranslationMatrix_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QTranslationMatrix_Test.cpp
	$(CXX_DEBUGMAC32SHAREDRTSTATIC) $(COMPILEROPTIONS_DEBUGMAC32SHAREDRTSTATIC) $(DEFINITIONS_DEBUGMAC32SHAREDRTSTATIC) $(INCLUDES_DEBUGMAC32SHAREDRTSTATIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QTranslationMatrix_Test.cpp -o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QTranslationMatrix_Test.o

$(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QTriangle2D_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QTriangle2D_Test.cpp
	$(CXX_DEBUGMAC32SHAREDRTSTATIC) $(COMPILEROPTIONS_DEBUGMAC32SHAREDRTSTATIC) $(DEFINITIONS_DEBUGMAC32SHAREDRTSTATIC) $(INCLUDES_DEBUGMAC32SHAREDRTSTATIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QTriangle2D_Test.cpp -o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QTriangle2D_Test.o

$(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QTriangle3D_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QTriangle3D_Test.cpp
	$(CXX_DEBUGMAC32SHAREDRTSTATIC) $(COMPILEROPTIONS_DEBUGMAC32SHAREDRTSTATIC) $(DEFINITIONS_DEBUGMAC32SHAREDRTSTATIC) $(INCLUDES_DEBUGMAC32SHAREDRTSTATIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QTriangle3D_Test.cpp -o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QTriangle3D_Test.o

$(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QTriangle_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QTriangle_Test.cpp
	$(CXX_DEBUGMAC32SHAREDRTSTATIC) $(COMPILEROPTIONS_DEBUGMAC32SHAREDRTSTATIC) $(DEFINITIONS_DEBUGMAC32SHAREDRTSTATIC) $(INCLUDES_DEBUGMAC32SHAREDRTSTATIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QTriangle_Test.cpp -o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QTriangle_Test.o

$(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QVector2_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QVector2_Test.cpp
	$(CXX_DEBUGMAC32SHAREDRTSTATIC) $(COMPILEROPTIONS_DEBUGMAC32SHAREDRTSTATIC) $(DEFINITIONS_DEBUGMAC32SHAREDRTSTATIC) $(INCLUDES_DEBUGMAC32SHAREDRTSTATIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QVector2_Test.cpp -o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QVector2_Test.o

$(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QVector3_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QVector3_Test.cpp
	$(CXX_DEBUGMAC32SHAREDRTSTATIC) $(COMPILEROPTIONS_DEBUGMAC32SHAREDRTSTATIC) $(DEFINITIONS_DEBUGMAC32SHAREDRTSTATIC) $(INCLUDES_DEBUGMAC32SHAREDRTSTATIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QVector3_Test.cpp -o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QVector3_Test.o

$(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QVector4_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QVector4_Test.cpp
	$(CXX_DEBUGMAC32SHAREDRTSTATIC) $(COMPILEROPTIONS_DEBUGMAC32SHAREDRTSTATIC) $(DEFINITIONS_DEBUGMAC32SHAREDRTSTATIC) $(INCLUDES_DEBUGMAC32SHAREDRTSTATIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QVector4_Test.cpp -o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QVector4_Test.o

$(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.SQAngle_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/SQAngle_Test.cpp
	$(CXX_DEBUGMAC32SHAREDRTSTATIC) $(COMPILEROPTIONS_DEBUGMAC32SHAREDRTSTATIC) $(DEFINITIONS_DEBUGMAC32SHAREDRTSTATIC) $(INCLUDES_DEBUGMAC32SHAREDRTSTATIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/SQAngle_Test.cpp -o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.SQAngle_Test.o

$(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.SQPoint_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/SQPoint_Test.cpp
	$(CXX_DEBUGMAC32SHAREDRTSTATIC) $(COMPILEROPTIONS_DEBUGMAC32SHAREDRTSTATIC) $(DEFINITIONS_DEBUGMAC32SHAREDRTSTATIC) $(INCLUDES_DEBUGMAC32SHAREDRTSTATIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/SQPoint_Test.cpp -o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.SQPoint_Test.o

$(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QEvent_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QEvent_Test.cpp
	$(CXX_DEBUGMAC32SHAREDRTSTATIC) $(COMPILEROPTIONS_DEBUGMAC32SHAREDRTSTATIC) $(DEFINITIONS_DEBUGMAC32SHAREDRTSTATIC) $(INCLUDES_DEBUGMAC32SHAREDRTSTATIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QEvent_Test.cpp -o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QEvent_Test.o

$(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTSTATIC)__.__.__.testsystem.EQTestType.o: $(EXECUTION_PATH)../../../testsystem/EQTestType.cpp
	$(CXX_DEBUGMAC32SHAREDRTSTATIC) $(COMPILEROPTIONS_DEBUGMAC32SHAREDRTSTATIC) $(DEFINITIONS_DEBUGMAC32SHAREDRTSTATIC) $(INCLUDES_DEBUGMAC32SHAREDRTSTATIC) -c $(EXECUTION_PATH)../../../testsystem/EQTestType.cpp -o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTSTATIC)__.__.__.testsystem.EQTestType.o

$(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTSTATIC)__.__.__.testsystem.QCommonTestConfig.o: $(EXECUTION_PATH)../../../testsystem/QCommonTestConfig.cpp
	$(CXX_DEBUGMAC32SHAREDRTSTATIC) $(COMPILEROPTIONS_DEBUGMAC32SHAREDRTSTATIC) $(DEFINITIONS_DEBUGMAC32SHAREDRTSTATIC) $(INCLUDES_DEBUGMAC32SHAREDRTSTATIC) -c $(EXECUTION_PATH)../../../testsystem/QCommonTestConfig.cpp -o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTSTATIC)__.__.__.testsystem.QCommonTestConfig.o

$(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTSTATIC)__.__.__.testsystem.QSimpleConfigLoader.o: $(EXECUTION_PATH)../../../testsystem/QSimpleConfigLoader.cpp
	$(CXX_DEBUGMAC32SHAREDRTSTATIC) $(COMPILEROPTIONS_DEBUGMAC32SHAREDRTSTATIC) $(DEFINITIONS_DEBUGMAC32SHAREDRTSTATIC) $(INCLUDES_DEBUGMAC32SHAREDRTSTATIC) -c $(EXECUTION_PATH)../../../testsystem/QSimpleConfigLoader.cpp -o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTSTATIC)__.__.__.testsystem.QSimpleConfigLoader.o

postbuildDebugMac32SharedrtStatic:
	


buildDebugMac32SharedrtStatic: prebuildDebugMac32SharedrtStatic DebugMac32SharedrtStatic postbuildDebugMac32SharedrtStatic

cleanDebugMac32SharedrtStatic:
	rm -f $(OBJECTS_DEBUGMAC32SHAREDRTSTATIC)
	rm -f $(OUTPUT_DEBUGMAC32SHAREDRTSTATIC)
	if (test -d $(EXECUTION_PATH)../../../bin/Clang/DebugMac32SharedrtStatic) then rm -rf "$(EXECUTION_PATH)../../../bin/Clang/DebugMac32SharedrtStatic"; fi
	if (test -d $(EXECUTION_PATH)../../../bin/Clang/DebugMac32SharedrtStatic) then rmdir "$(EXECUTION_PATH)../../../bin/Clang/DebugMac32SharedrtStatic"; fi
	if (test -d $(EXECUTION_PATH)../../../garbage/Clang/DebugMac32SharedrtStatic) then rm -rf "$(EXECUTION_PATH)../../../garbage/Clang/DebugMac32SharedrtStatic"; fi
	if (test -d $(EXECUTION_PATH)../../../garbage/Clang/DebugMac32SharedrtStatic) then rmdir "$(EXECUTION_PATH)../../../garbage/Clang/DebugMac32SharedrtStatic"; fi


#------------------------------------------------------------
#------------- DebugWin32SharedrtDynamic --------------
#------------------------------------------------------------
CXX_DEBUGWIN32SHAREDRTDYNAMIC = g++.exe
AR_DEBUGWIN32SHAREDRTDYNAMIC = ar.exe
LD_DEBUGWIN32SHAREDRTDYNAMIC = g++.exe
AS_DEBUGWIN32SHAREDRTDYNAMIC = as.exe
INCLUDES_DEBUGWIN32SHAREDRTDYNAMIC = $(INCLUDES_GLOBAL) -I$(EXECUTION_PATH)../../../../headers -I$(EXECUTION_PATH)../../../tests/unit/testmodule_tools -I$(EXECUTION_PATH)../../../tests/unit -I$(EXECUTION_PATH)../../../../3rdparty/ICU/include
LIBRARYDIRS_DEBUGWIN32SHAREDRTDYNAMIC = $(LIBRARYDIRS_GLOBAL) -L$(EXECUTION_PATH)../../../../3rdparty/Boost/bin/Win32/DebugSharedrtStatic -L$(EXECUTION_PATH)../../../../3rdparty/ICU/bin/Win32/ReleaseSharedrtDynamic/MinGW -L$(EXECUTION_PATH)../../../../bin/MinGW/DebugWin32SharedrtDynamic
LIBRARIES_DEBUGWIN32SHAREDRTDYNAMIC = $(LIBRARIES_GLOBAL) -lQuimeraEngineTools -lQuimeraEngineCommon -lboost_unit_test_framework-mt-d -licudt -licuuc -licuin
COMPILEROPTIONS_DEBUGWIN32SHAREDRTDYNAMIC = $(COMPILEROPTIONS_GLOBAL) -g -O0 -Wall -Wno-comment -Wno-unused-local-typedefs -m32 -isystem $(EXECUTION_PATH)../../../../3rdparty/Boost/include
LINKEROPTIONS_DEBUGWIN32SHAREDRTDYNAMIC = $(LINKEROPTIONS_GLOBAL) -m32
DEFINITIONS_DEBUGWIN32SHAREDRTDYNAMIC = $(DEFINITIONS_GLOBAL) -DQE_PREPROCESSOR_IMPORTLIB_QUIMERAENGINE -DBOOST_NO_RTTI -DBOOST_NO_TYPEID
OUTPUT_DEBUGWIN32SHAREDRTDYNAMIC = $(EXECUTION_PATH)../../../bin/MinGW/DebugWin32SharedrtDynamic/Unit_TestModule_Tools.exe
INTERMEDIARYDIR_DEBUGWIN32SHAREDRTDYNAMIC = $(EXECUTION_PATH)../../../garbage/MinGW/DebugWin32SharedrtDynamic/
OBJECTS_DEBUGWIN32SHAREDRTDYNAMIC = $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.TestModule_Tools.o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QArrayIterator_Test.o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QList_Test.o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QListIterator_Test.o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QNTree_Test.o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.CallCounter.o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QNTreeIterator_Test.o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QBinarySearchTree_Test.o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QConstArrayIterator_Test.o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QConstListIterator_Test.o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QConstNTreeIterator_Test.o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QConstBinarySearchTreeIterator_Test.o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.SQComparatorDefault_Test.o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QKeyValuePair_Test.o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.SQKeyValuePairComparator_Test.o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.SQEqualityComparator_Test.o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QDictionary_Test.o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QHashtable_Test.o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.SQIntegerHashProvider_Test.o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.SQStringHashProvider_Test.o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QConstDictionaryIterator_Test.o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QConstHashtableIterator_Test.o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QArrayDynamic_Test.o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QArrayFixed_Test.o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QDateTime_Test.o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QDstInformation_Test.o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QTimeSpan_Test.o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QTimeZone_Test.o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.SQTimeZoneFactory_Test.o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QBaseDualQuaternion_Test.o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QBaseHexahedron_Test.o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QBaseLineSegment_Test.o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QBaseMatrix2x2_Test.o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QBaseMatrix3x3_Test.o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QBaseMatrix3x4_Test.o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QBaseMatrix4x3_Test.o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QBaseMatrix4x4_Test.o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QBaseOrb_Test.o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QBasePlane_Test.o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QBaseQuadrilateral_Test.o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QBaseQuaternion_Test.o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QBaseRay_QVector4_Test.o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QBaseRay_Test.o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QBaseTriangle_Test.o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QBaseVector2_Test.o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QBaseVector3_Test.o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QBaseVector4_Test.o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QCircle_Test.o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QDualQuaternion_Test.o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QHexahedron_Test.o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QLineSegment2D_Test.o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QLineSegment3D_Test.o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QLineSegment_Test.o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QMatrix2x2_Test.o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QMatrix3x3_Test.o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QMatrix3x4_Test.o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QMatrix4x3_Test.o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QMatrix4x4_Test.o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QOrb_Test.o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QPlane_Test.o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QQuadrilateral_Test.o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QQuaternion_Test.o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QRay2D_Test.o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QRay3D_Test.o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QRay_QVector4_Test.o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QRay_Test.o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QRotationMatrix3x3_Test.o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QScalingMatrix3x3_Test.o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QSpaceConversionMatrix_Test.o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QSphere_Test.o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QTransformationMatrix3x3_Test.o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QTransformationMatrix_Test.o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QTranslationMatrix_Test.o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QTriangle2D_Test.o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QTriangle3D_Test.o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QTriangle_Test.o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QVector2_Test.o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QVector3_Test.o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QVector4_Test.o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.SQAngle_Test.o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.SQPoint_Test.o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QEvent_Test.o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTDYNAMIC)__.__.__.testsystem.EQTestType.o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTDYNAMIC)__.__.__.testsystem.QCommonTestConfig.o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTDYNAMIC)__.__.__.testsystem.QSimpleConfigLoader.o

prebuildDebugWin32SharedrtDynamic:
	cmd /c if not exist $(EXECUTION_PATH)..\..\..\bin\MinGW\DebugWin32SharedrtDynamic mkdir "$(EXECUTION_PATH)..\..\..\bin\MinGW\DebugWin32SharedrtDynamic"
	cmd /c if not exist $(EXECUTION_PATH)..\..\..\garbage\MinGW\DebugWin32SharedrtDynamic mkdir "$(EXECUTION_PATH)..\..\..\garbage\MinGW\DebugWin32SharedrtDynamic"


DebugWin32SharedrtDynamic: $(OBJECTS_DEBUGWIN32SHAREDRTDYNAMIC)
	$(LD_DEBUGWIN32SHAREDRTDYNAMIC) $(DEFINITIONS_DEBUGWIN32SHAREDRTDYNAMIC) $(LINKEROPTIONS_DEBUGWIN32SHAREDRTDYNAMIC) $(LIBRARYDIRS_DEBUGWIN32SHAREDRTDYNAMIC) $(OBJECTS_DEBUGWIN32SHAREDRTDYNAMIC) $(LIBRARIES_DEBUGWIN32SHAREDRTDYNAMIC) -o $(OUTPUT_DEBUGWIN32SHAREDRTDYNAMIC)

$(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.TestModule_Tools.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/TestModule_Tools.cpp
	$(CXX_DEBUGWIN32SHAREDRTDYNAMIC) $(COMPILEROPTIONS_DEBUGWIN32SHAREDRTDYNAMIC) $(DEFINITIONS_DEBUGWIN32SHAREDRTDYNAMIC) $(INCLUDES_DEBUGWIN32SHAREDRTDYNAMIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/TestModule_Tools.cpp -o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.TestModule_Tools.o

$(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QArrayIterator_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QArrayIterator_Test.cpp
	$(CXX_DEBUGWIN32SHAREDRTDYNAMIC) $(COMPILEROPTIONS_DEBUGWIN32SHAREDRTDYNAMIC) $(DEFINITIONS_DEBUGWIN32SHAREDRTDYNAMIC) $(INCLUDES_DEBUGWIN32SHAREDRTDYNAMIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QArrayIterator_Test.cpp -o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QArrayIterator_Test.o

$(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QList_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QList_Test.cpp
	$(CXX_DEBUGWIN32SHAREDRTDYNAMIC) $(COMPILEROPTIONS_DEBUGWIN32SHAREDRTDYNAMIC) $(DEFINITIONS_DEBUGWIN32SHAREDRTDYNAMIC) $(INCLUDES_DEBUGWIN32SHAREDRTDYNAMIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QList_Test.cpp -o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QList_Test.o

$(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QListIterator_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QListIterator_Test.cpp
	$(CXX_DEBUGWIN32SHAREDRTDYNAMIC) $(COMPILEROPTIONS_DEBUGWIN32SHAREDRTDYNAMIC) $(DEFINITIONS_DEBUGWIN32SHAREDRTDYNAMIC) $(INCLUDES_DEBUGWIN32SHAREDRTDYNAMIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QListIterator_Test.cpp -o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QListIterator_Test.o

$(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QNTree_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QNTree_Test.cpp
	$(CXX_DEBUGWIN32SHAREDRTDYNAMIC) $(COMPILEROPTIONS_DEBUGWIN32SHAREDRTDYNAMIC) $(DEFINITIONS_DEBUGWIN32SHAREDRTDYNAMIC) $(INCLUDES_DEBUGWIN32SHAREDRTDYNAMIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QNTree_Test.cpp -o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QNTree_Test.o

$(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.CallCounter.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/CallCounter.cpp
	$(CXX_DEBUGWIN32SHAREDRTDYNAMIC) $(COMPILEROPTIONS_DEBUGWIN32SHAREDRTDYNAMIC) $(DEFINITIONS_DEBUGWIN32SHAREDRTDYNAMIC) $(INCLUDES_DEBUGWIN32SHAREDRTDYNAMIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/CallCounter.cpp -o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.CallCounter.o

$(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QNTreeIterator_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QNTreeIterator_Test.cpp
	$(CXX_DEBUGWIN32SHAREDRTDYNAMIC) $(COMPILEROPTIONS_DEBUGWIN32SHAREDRTDYNAMIC) $(DEFINITIONS_DEBUGWIN32SHAREDRTDYNAMIC) $(INCLUDES_DEBUGWIN32SHAREDRTDYNAMIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QNTreeIterator_Test.cpp -o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QNTreeIterator_Test.o

$(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QBinarySearchTree_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QBinarySearchTree_Test.cpp
	$(CXX_DEBUGWIN32SHAREDRTDYNAMIC) $(COMPILEROPTIONS_DEBUGWIN32SHAREDRTDYNAMIC) $(DEFINITIONS_DEBUGWIN32SHAREDRTDYNAMIC) $(INCLUDES_DEBUGWIN32SHAREDRTDYNAMIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QBinarySearchTree_Test.cpp -o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QBinarySearchTree_Test.o

$(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QConstArrayIterator_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QConstArrayIterator_Test.cpp
	$(CXX_DEBUGWIN32SHAREDRTDYNAMIC) $(COMPILEROPTIONS_DEBUGWIN32SHAREDRTDYNAMIC) $(DEFINITIONS_DEBUGWIN32SHAREDRTDYNAMIC) $(INCLUDES_DEBUGWIN32SHAREDRTDYNAMIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QConstArrayIterator_Test.cpp -o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QConstArrayIterator_Test.o

$(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QConstListIterator_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QConstListIterator_Test.cpp
	$(CXX_DEBUGWIN32SHAREDRTDYNAMIC) $(COMPILEROPTIONS_DEBUGWIN32SHAREDRTDYNAMIC) $(DEFINITIONS_DEBUGWIN32SHAREDRTDYNAMIC) $(INCLUDES_DEBUGWIN32SHAREDRTDYNAMIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QConstListIterator_Test.cpp -o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QConstListIterator_Test.o

$(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QConstNTreeIterator_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QConstNTreeIterator_Test.cpp
	$(CXX_DEBUGWIN32SHAREDRTDYNAMIC) $(COMPILEROPTIONS_DEBUGWIN32SHAREDRTDYNAMIC) $(DEFINITIONS_DEBUGWIN32SHAREDRTDYNAMIC) $(INCLUDES_DEBUGWIN32SHAREDRTDYNAMIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QConstNTreeIterator_Test.cpp -o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QConstNTreeIterator_Test.o

$(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QConstBinarySearchTreeIterator_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QConstBinarySearchTreeIterator_Test.cpp
	$(CXX_DEBUGWIN32SHAREDRTDYNAMIC) $(COMPILEROPTIONS_DEBUGWIN32SHAREDRTDYNAMIC) $(DEFINITIONS_DEBUGWIN32SHAREDRTDYNAMIC) $(INCLUDES_DEBUGWIN32SHAREDRTDYNAMIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QConstBinarySearchTreeIterator_Test.cpp -o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QConstBinarySearchTreeIterator_Test.o

$(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.SQComparatorDefault_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/SQComparatorDefault_Test.cpp
	$(CXX_DEBUGWIN32SHAREDRTDYNAMIC) $(COMPILEROPTIONS_DEBUGWIN32SHAREDRTDYNAMIC) $(DEFINITIONS_DEBUGWIN32SHAREDRTDYNAMIC) $(INCLUDES_DEBUGWIN32SHAREDRTDYNAMIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/SQComparatorDefault_Test.cpp -o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.SQComparatorDefault_Test.o

$(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QKeyValuePair_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QKeyValuePair_Test.cpp
	$(CXX_DEBUGWIN32SHAREDRTDYNAMIC) $(COMPILEROPTIONS_DEBUGWIN32SHAREDRTDYNAMIC) $(DEFINITIONS_DEBUGWIN32SHAREDRTDYNAMIC) $(INCLUDES_DEBUGWIN32SHAREDRTDYNAMIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QKeyValuePair_Test.cpp -o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QKeyValuePair_Test.o

$(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.SQKeyValuePairComparator_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/SQKeyValuePairComparator_Test.cpp
	$(CXX_DEBUGWIN32SHAREDRTDYNAMIC) $(COMPILEROPTIONS_DEBUGWIN32SHAREDRTDYNAMIC) $(DEFINITIONS_DEBUGWIN32SHAREDRTDYNAMIC) $(INCLUDES_DEBUGWIN32SHAREDRTDYNAMIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/SQKeyValuePairComparator_Test.cpp -o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.SQKeyValuePairComparator_Test.o

$(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.SQEqualityComparator_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/SQEqualityComparator_Test.cpp
	$(CXX_DEBUGWIN32SHAREDRTDYNAMIC) $(COMPILEROPTIONS_DEBUGWIN32SHAREDRTDYNAMIC) $(DEFINITIONS_DEBUGWIN32SHAREDRTDYNAMIC) $(INCLUDES_DEBUGWIN32SHAREDRTDYNAMIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/SQEqualityComparator_Test.cpp -o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.SQEqualityComparator_Test.o

$(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QDictionary_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QDictionary_Test.cpp
	$(CXX_DEBUGWIN32SHAREDRTDYNAMIC) $(COMPILEROPTIONS_DEBUGWIN32SHAREDRTDYNAMIC) $(DEFINITIONS_DEBUGWIN32SHAREDRTDYNAMIC) $(INCLUDES_DEBUGWIN32SHAREDRTDYNAMIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QDictionary_Test.cpp -o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QDictionary_Test.o

$(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QHashtable_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QHashtable_Test.cpp
	$(CXX_DEBUGWIN32SHAREDRTDYNAMIC) $(COMPILEROPTIONS_DEBUGWIN32SHAREDRTDYNAMIC) $(DEFINITIONS_DEBUGWIN32SHAREDRTDYNAMIC) $(INCLUDES_DEBUGWIN32SHAREDRTDYNAMIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QHashtable_Test.cpp -o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QHashtable_Test.o

$(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.SQIntegerHashProvider_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/SQIntegerHashProvider_Test.cpp
	$(CXX_DEBUGWIN32SHAREDRTDYNAMIC) $(COMPILEROPTIONS_DEBUGWIN32SHAREDRTDYNAMIC) $(DEFINITIONS_DEBUGWIN32SHAREDRTDYNAMIC) $(INCLUDES_DEBUGWIN32SHAREDRTDYNAMIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/SQIntegerHashProvider_Test.cpp -o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.SQIntegerHashProvider_Test.o

$(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.SQStringHashProvider_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/SQStringHashProvider_Test.cpp
	$(CXX_DEBUGWIN32SHAREDRTDYNAMIC) $(COMPILEROPTIONS_DEBUGWIN32SHAREDRTDYNAMIC) $(DEFINITIONS_DEBUGWIN32SHAREDRTDYNAMIC) $(INCLUDES_DEBUGWIN32SHAREDRTDYNAMIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/SQStringHashProvider_Test.cpp -o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.SQStringHashProvider_Test.o

$(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QConstDictionaryIterator_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QConstDictionaryIterator_Test.cpp
	$(CXX_DEBUGWIN32SHAREDRTDYNAMIC) $(COMPILEROPTIONS_DEBUGWIN32SHAREDRTDYNAMIC) $(DEFINITIONS_DEBUGWIN32SHAREDRTDYNAMIC) $(INCLUDES_DEBUGWIN32SHAREDRTDYNAMIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QConstDictionaryIterator_Test.cpp -o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QConstDictionaryIterator_Test.o

$(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QConstHashtableIterator_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QConstHashtableIterator_Test.cpp
	$(CXX_DEBUGWIN32SHAREDRTDYNAMIC) $(COMPILEROPTIONS_DEBUGWIN32SHAREDRTDYNAMIC) $(DEFINITIONS_DEBUGWIN32SHAREDRTDYNAMIC) $(INCLUDES_DEBUGWIN32SHAREDRTDYNAMIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QConstHashtableIterator_Test.cpp -o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QConstHashtableIterator_Test.o

$(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QArrayDynamic_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QArrayDynamic_Test.cpp
	$(CXX_DEBUGWIN32SHAREDRTDYNAMIC) $(COMPILEROPTIONS_DEBUGWIN32SHAREDRTDYNAMIC) $(DEFINITIONS_DEBUGWIN32SHAREDRTDYNAMIC) $(INCLUDES_DEBUGWIN32SHAREDRTDYNAMIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QArrayDynamic_Test.cpp -o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QArrayDynamic_Test.o

$(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QArrayFixed_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QArrayFixed_Test.cpp
	$(CXX_DEBUGWIN32SHAREDRTDYNAMIC) $(COMPILEROPTIONS_DEBUGWIN32SHAREDRTDYNAMIC) $(DEFINITIONS_DEBUGWIN32SHAREDRTDYNAMIC) $(INCLUDES_DEBUGWIN32SHAREDRTDYNAMIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QArrayFixed_Test.cpp -o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QArrayFixed_Test.o

$(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QDateTime_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QDateTime_Test.cpp
	$(CXX_DEBUGWIN32SHAREDRTDYNAMIC) $(COMPILEROPTIONS_DEBUGWIN32SHAREDRTDYNAMIC) $(DEFINITIONS_DEBUGWIN32SHAREDRTDYNAMIC) $(INCLUDES_DEBUGWIN32SHAREDRTDYNAMIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QDateTime_Test.cpp -o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QDateTime_Test.o

$(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QDstInformation_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QDstInformation_Test.cpp
	$(CXX_DEBUGWIN32SHAREDRTDYNAMIC) $(COMPILEROPTIONS_DEBUGWIN32SHAREDRTDYNAMIC) $(DEFINITIONS_DEBUGWIN32SHAREDRTDYNAMIC) $(INCLUDES_DEBUGWIN32SHAREDRTDYNAMIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QDstInformation_Test.cpp -o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QDstInformation_Test.o

$(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QTimeSpan_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QTimeSpan_Test.cpp
	$(CXX_DEBUGWIN32SHAREDRTDYNAMIC) $(COMPILEROPTIONS_DEBUGWIN32SHAREDRTDYNAMIC) $(DEFINITIONS_DEBUGWIN32SHAREDRTDYNAMIC) $(INCLUDES_DEBUGWIN32SHAREDRTDYNAMIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QTimeSpan_Test.cpp -o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QTimeSpan_Test.o

$(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QTimeZone_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QTimeZone_Test.cpp
	$(CXX_DEBUGWIN32SHAREDRTDYNAMIC) $(COMPILEROPTIONS_DEBUGWIN32SHAREDRTDYNAMIC) $(DEFINITIONS_DEBUGWIN32SHAREDRTDYNAMIC) $(INCLUDES_DEBUGWIN32SHAREDRTDYNAMIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QTimeZone_Test.cpp -o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QTimeZone_Test.o

$(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.SQTimeZoneFactory_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/SQTimeZoneFactory_Test.cpp
	$(CXX_DEBUGWIN32SHAREDRTDYNAMIC) $(COMPILEROPTIONS_DEBUGWIN32SHAREDRTDYNAMIC) $(DEFINITIONS_DEBUGWIN32SHAREDRTDYNAMIC) $(INCLUDES_DEBUGWIN32SHAREDRTDYNAMIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/SQTimeZoneFactory_Test.cpp -o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.SQTimeZoneFactory_Test.o

$(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QBaseDualQuaternion_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QBaseDualQuaternion_Test.cpp
	$(CXX_DEBUGWIN32SHAREDRTDYNAMIC) $(COMPILEROPTIONS_DEBUGWIN32SHAREDRTDYNAMIC) $(DEFINITIONS_DEBUGWIN32SHAREDRTDYNAMIC) $(INCLUDES_DEBUGWIN32SHAREDRTDYNAMIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QBaseDualQuaternion_Test.cpp -o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QBaseDualQuaternion_Test.o

$(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QBaseHexahedron_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QBaseHexahedron_Test.cpp
	$(CXX_DEBUGWIN32SHAREDRTDYNAMIC) $(COMPILEROPTIONS_DEBUGWIN32SHAREDRTDYNAMIC) $(DEFINITIONS_DEBUGWIN32SHAREDRTDYNAMIC) $(INCLUDES_DEBUGWIN32SHAREDRTDYNAMIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QBaseHexahedron_Test.cpp -o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QBaseHexahedron_Test.o

$(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QBaseLineSegment_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QBaseLineSegment_Test.cpp
	$(CXX_DEBUGWIN32SHAREDRTDYNAMIC) $(COMPILEROPTIONS_DEBUGWIN32SHAREDRTDYNAMIC) $(DEFINITIONS_DEBUGWIN32SHAREDRTDYNAMIC) $(INCLUDES_DEBUGWIN32SHAREDRTDYNAMIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QBaseLineSegment_Test.cpp -o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QBaseLineSegment_Test.o

$(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QBaseMatrix2x2_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QBaseMatrix2x2_Test.cpp
	$(CXX_DEBUGWIN32SHAREDRTDYNAMIC) $(COMPILEROPTIONS_DEBUGWIN32SHAREDRTDYNAMIC) $(DEFINITIONS_DEBUGWIN32SHAREDRTDYNAMIC) $(INCLUDES_DEBUGWIN32SHAREDRTDYNAMIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QBaseMatrix2x2_Test.cpp -o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QBaseMatrix2x2_Test.o

$(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QBaseMatrix3x3_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QBaseMatrix3x3_Test.cpp
	$(CXX_DEBUGWIN32SHAREDRTDYNAMIC) $(COMPILEROPTIONS_DEBUGWIN32SHAREDRTDYNAMIC) $(DEFINITIONS_DEBUGWIN32SHAREDRTDYNAMIC) $(INCLUDES_DEBUGWIN32SHAREDRTDYNAMIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QBaseMatrix3x3_Test.cpp -o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QBaseMatrix3x3_Test.o

$(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QBaseMatrix3x4_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QBaseMatrix3x4_Test.cpp
	$(CXX_DEBUGWIN32SHAREDRTDYNAMIC) $(COMPILEROPTIONS_DEBUGWIN32SHAREDRTDYNAMIC) $(DEFINITIONS_DEBUGWIN32SHAREDRTDYNAMIC) $(INCLUDES_DEBUGWIN32SHAREDRTDYNAMIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QBaseMatrix3x4_Test.cpp -o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QBaseMatrix3x4_Test.o

$(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QBaseMatrix4x3_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QBaseMatrix4x3_Test.cpp
	$(CXX_DEBUGWIN32SHAREDRTDYNAMIC) $(COMPILEROPTIONS_DEBUGWIN32SHAREDRTDYNAMIC) $(DEFINITIONS_DEBUGWIN32SHAREDRTDYNAMIC) $(INCLUDES_DEBUGWIN32SHAREDRTDYNAMIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QBaseMatrix4x3_Test.cpp -o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QBaseMatrix4x3_Test.o

$(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QBaseMatrix4x4_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QBaseMatrix4x4_Test.cpp
	$(CXX_DEBUGWIN32SHAREDRTDYNAMIC) $(COMPILEROPTIONS_DEBUGWIN32SHAREDRTDYNAMIC) $(DEFINITIONS_DEBUGWIN32SHAREDRTDYNAMIC) $(INCLUDES_DEBUGWIN32SHAREDRTDYNAMIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QBaseMatrix4x4_Test.cpp -o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QBaseMatrix4x4_Test.o

$(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QBaseOrb_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QBaseOrb_Test.cpp
	$(CXX_DEBUGWIN32SHAREDRTDYNAMIC) $(COMPILEROPTIONS_DEBUGWIN32SHAREDRTDYNAMIC) $(DEFINITIONS_DEBUGWIN32SHAREDRTDYNAMIC) $(INCLUDES_DEBUGWIN32SHAREDRTDYNAMIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QBaseOrb_Test.cpp -o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QBaseOrb_Test.o

$(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QBasePlane_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QBasePlane_Test.cpp
	$(CXX_DEBUGWIN32SHAREDRTDYNAMIC) $(COMPILEROPTIONS_DEBUGWIN32SHAREDRTDYNAMIC) $(DEFINITIONS_DEBUGWIN32SHAREDRTDYNAMIC) $(INCLUDES_DEBUGWIN32SHAREDRTDYNAMIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QBasePlane_Test.cpp -o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QBasePlane_Test.o

$(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QBaseQuadrilateral_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QBaseQuadrilateral_Test.cpp
	$(CXX_DEBUGWIN32SHAREDRTDYNAMIC) $(COMPILEROPTIONS_DEBUGWIN32SHAREDRTDYNAMIC) $(DEFINITIONS_DEBUGWIN32SHAREDRTDYNAMIC) $(INCLUDES_DEBUGWIN32SHAREDRTDYNAMIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QBaseQuadrilateral_Test.cpp -o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QBaseQuadrilateral_Test.o

$(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QBaseQuaternion_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QBaseQuaternion_Test.cpp
	$(CXX_DEBUGWIN32SHAREDRTDYNAMIC) $(COMPILEROPTIONS_DEBUGWIN32SHAREDRTDYNAMIC) $(DEFINITIONS_DEBUGWIN32SHAREDRTDYNAMIC) $(INCLUDES_DEBUGWIN32SHAREDRTDYNAMIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QBaseQuaternion_Test.cpp -o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QBaseQuaternion_Test.o

$(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QBaseRay_QVector4_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QBaseRay_QVector4_Test.cpp
	$(CXX_DEBUGWIN32SHAREDRTDYNAMIC) $(COMPILEROPTIONS_DEBUGWIN32SHAREDRTDYNAMIC) $(DEFINITIONS_DEBUGWIN32SHAREDRTDYNAMIC) $(INCLUDES_DEBUGWIN32SHAREDRTDYNAMIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QBaseRay_QVector4_Test.cpp -o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QBaseRay_QVector4_Test.o

$(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QBaseRay_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QBaseRay_Test.cpp
	$(CXX_DEBUGWIN32SHAREDRTDYNAMIC) $(COMPILEROPTIONS_DEBUGWIN32SHAREDRTDYNAMIC) $(DEFINITIONS_DEBUGWIN32SHAREDRTDYNAMIC) $(INCLUDES_DEBUGWIN32SHAREDRTDYNAMIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QBaseRay_Test.cpp -o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QBaseRay_Test.o

$(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QBaseTriangle_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QBaseTriangle_Test.cpp
	$(CXX_DEBUGWIN32SHAREDRTDYNAMIC) $(COMPILEROPTIONS_DEBUGWIN32SHAREDRTDYNAMIC) $(DEFINITIONS_DEBUGWIN32SHAREDRTDYNAMIC) $(INCLUDES_DEBUGWIN32SHAREDRTDYNAMIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QBaseTriangle_Test.cpp -o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QBaseTriangle_Test.o

$(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QBaseVector2_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QBaseVector2_Test.cpp
	$(CXX_DEBUGWIN32SHAREDRTDYNAMIC) $(COMPILEROPTIONS_DEBUGWIN32SHAREDRTDYNAMIC) $(DEFINITIONS_DEBUGWIN32SHAREDRTDYNAMIC) $(INCLUDES_DEBUGWIN32SHAREDRTDYNAMIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QBaseVector2_Test.cpp -o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QBaseVector2_Test.o

$(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QBaseVector3_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QBaseVector3_Test.cpp
	$(CXX_DEBUGWIN32SHAREDRTDYNAMIC) $(COMPILEROPTIONS_DEBUGWIN32SHAREDRTDYNAMIC) $(DEFINITIONS_DEBUGWIN32SHAREDRTDYNAMIC) $(INCLUDES_DEBUGWIN32SHAREDRTDYNAMIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QBaseVector3_Test.cpp -o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QBaseVector3_Test.o

$(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QBaseVector4_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QBaseVector4_Test.cpp
	$(CXX_DEBUGWIN32SHAREDRTDYNAMIC) $(COMPILEROPTIONS_DEBUGWIN32SHAREDRTDYNAMIC) $(DEFINITIONS_DEBUGWIN32SHAREDRTDYNAMIC) $(INCLUDES_DEBUGWIN32SHAREDRTDYNAMIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QBaseVector4_Test.cpp -o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QBaseVector4_Test.o

$(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QCircle_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QCircle_Test.cpp
	$(CXX_DEBUGWIN32SHAREDRTDYNAMIC) $(COMPILEROPTIONS_DEBUGWIN32SHAREDRTDYNAMIC) $(DEFINITIONS_DEBUGWIN32SHAREDRTDYNAMIC) $(INCLUDES_DEBUGWIN32SHAREDRTDYNAMIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QCircle_Test.cpp -o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QCircle_Test.o

$(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QDualQuaternion_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QDualQuaternion_Test.cpp
	$(CXX_DEBUGWIN32SHAREDRTDYNAMIC) $(COMPILEROPTIONS_DEBUGWIN32SHAREDRTDYNAMIC) $(DEFINITIONS_DEBUGWIN32SHAREDRTDYNAMIC) $(INCLUDES_DEBUGWIN32SHAREDRTDYNAMIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QDualQuaternion_Test.cpp -o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QDualQuaternion_Test.o

$(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QHexahedron_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QHexahedron_Test.cpp
	$(CXX_DEBUGWIN32SHAREDRTDYNAMIC) $(COMPILEROPTIONS_DEBUGWIN32SHAREDRTDYNAMIC) $(DEFINITIONS_DEBUGWIN32SHAREDRTDYNAMIC) $(INCLUDES_DEBUGWIN32SHAREDRTDYNAMIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QHexahedron_Test.cpp -o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QHexahedron_Test.o

$(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QLineSegment2D_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QLineSegment2D_Test.cpp
	$(CXX_DEBUGWIN32SHAREDRTDYNAMIC) $(COMPILEROPTIONS_DEBUGWIN32SHAREDRTDYNAMIC) $(DEFINITIONS_DEBUGWIN32SHAREDRTDYNAMIC) $(INCLUDES_DEBUGWIN32SHAREDRTDYNAMIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QLineSegment2D_Test.cpp -o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QLineSegment2D_Test.o

$(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QLineSegment3D_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QLineSegment3D_Test.cpp
	$(CXX_DEBUGWIN32SHAREDRTDYNAMIC) $(COMPILEROPTIONS_DEBUGWIN32SHAREDRTDYNAMIC) $(DEFINITIONS_DEBUGWIN32SHAREDRTDYNAMIC) $(INCLUDES_DEBUGWIN32SHAREDRTDYNAMIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QLineSegment3D_Test.cpp -o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QLineSegment3D_Test.o

$(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QLineSegment_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QLineSegment_Test.cpp
	$(CXX_DEBUGWIN32SHAREDRTDYNAMIC) $(COMPILEROPTIONS_DEBUGWIN32SHAREDRTDYNAMIC) $(DEFINITIONS_DEBUGWIN32SHAREDRTDYNAMIC) $(INCLUDES_DEBUGWIN32SHAREDRTDYNAMIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QLineSegment_Test.cpp -o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QLineSegment_Test.o

$(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QMatrix2x2_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QMatrix2x2_Test.cpp
	$(CXX_DEBUGWIN32SHAREDRTDYNAMIC) $(COMPILEROPTIONS_DEBUGWIN32SHAREDRTDYNAMIC) $(DEFINITIONS_DEBUGWIN32SHAREDRTDYNAMIC) $(INCLUDES_DEBUGWIN32SHAREDRTDYNAMIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QMatrix2x2_Test.cpp -o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QMatrix2x2_Test.o

$(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QMatrix3x3_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QMatrix3x3_Test.cpp
	$(CXX_DEBUGWIN32SHAREDRTDYNAMIC) $(COMPILEROPTIONS_DEBUGWIN32SHAREDRTDYNAMIC) $(DEFINITIONS_DEBUGWIN32SHAREDRTDYNAMIC) $(INCLUDES_DEBUGWIN32SHAREDRTDYNAMIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QMatrix3x3_Test.cpp -o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QMatrix3x3_Test.o

$(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QMatrix3x4_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QMatrix3x4_Test.cpp
	$(CXX_DEBUGWIN32SHAREDRTDYNAMIC) $(COMPILEROPTIONS_DEBUGWIN32SHAREDRTDYNAMIC) $(DEFINITIONS_DEBUGWIN32SHAREDRTDYNAMIC) $(INCLUDES_DEBUGWIN32SHAREDRTDYNAMIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QMatrix3x4_Test.cpp -o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QMatrix3x4_Test.o

$(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QMatrix4x3_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QMatrix4x3_Test.cpp
	$(CXX_DEBUGWIN32SHAREDRTDYNAMIC) $(COMPILEROPTIONS_DEBUGWIN32SHAREDRTDYNAMIC) $(DEFINITIONS_DEBUGWIN32SHAREDRTDYNAMIC) $(INCLUDES_DEBUGWIN32SHAREDRTDYNAMIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QMatrix4x3_Test.cpp -o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QMatrix4x3_Test.o

$(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QMatrix4x4_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QMatrix4x4_Test.cpp
	$(CXX_DEBUGWIN32SHAREDRTDYNAMIC) $(COMPILEROPTIONS_DEBUGWIN32SHAREDRTDYNAMIC) $(DEFINITIONS_DEBUGWIN32SHAREDRTDYNAMIC) $(INCLUDES_DEBUGWIN32SHAREDRTDYNAMIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QMatrix4x4_Test.cpp -o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QMatrix4x4_Test.o

$(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QOrb_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QOrb_Test.cpp
	$(CXX_DEBUGWIN32SHAREDRTDYNAMIC) $(COMPILEROPTIONS_DEBUGWIN32SHAREDRTDYNAMIC) $(DEFINITIONS_DEBUGWIN32SHAREDRTDYNAMIC) $(INCLUDES_DEBUGWIN32SHAREDRTDYNAMIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QOrb_Test.cpp -o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QOrb_Test.o

$(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QPlane_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QPlane_Test.cpp
	$(CXX_DEBUGWIN32SHAREDRTDYNAMIC) $(COMPILEROPTIONS_DEBUGWIN32SHAREDRTDYNAMIC) $(DEFINITIONS_DEBUGWIN32SHAREDRTDYNAMIC) $(INCLUDES_DEBUGWIN32SHAREDRTDYNAMIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QPlane_Test.cpp -o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QPlane_Test.o

$(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QQuadrilateral_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QQuadrilateral_Test.cpp
	$(CXX_DEBUGWIN32SHAREDRTDYNAMIC) $(COMPILEROPTIONS_DEBUGWIN32SHAREDRTDYNAMIC) $(DEFINITIONS_DEBUGWIN32SHAREDRTDYNAMIC) $(INCLUDES_DEBUGWIN32SHAREDRTDYNAMIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QQuadrilateral_Test.cpp -o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QQuadrilateral_Test.o

$(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QQuaternion_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QQuaternion_Test.cpp
	$(CXX_DEBUGWIN32SHAREDRTDYNAMIC) $(COMPILEROPTIONS_DEBUGWIN32SHAREDRTDYNAMIC) $(DEFINITIONS_DEBUGWIN32SHAREDRTDYNAMIC) $(INCLUDES_DEBUGWIN32SHAREDRTDYNAMIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QQuaternion_Test.cpp -o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QQuaternion_Test.o

$(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QRay2D_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QRay2D_Test.cpp
	$(CXX_DEBUGWIN32SHAREDRTDYNAMIC) $(COMPILEROPTIONS_DEBUGWIN32SHAREDRTDYNAMIC) $(DEFINITIONS_DEBUGWIN32SHAREDRTDYNAMIC) $(INCLUDES_DEBUGWIN32SHAREDRTDYNAMIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QRay2D_Test.cpp -o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QRay2D_Test.o

$(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QRay3D_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QRay3D_Test.cpp
	$(CXX_DEBUGWIN32SHAREDRTDYNAMIC) $(COMPILEROPTIONS_DEBUGWIN32SHAREDRTDYNAMIC) $(DEFINITIONS_DEBUGWIN32SHAREDRTDYNAMIC) $(INCLUDES_DEBUGWIN32SHAREDRTDYNAMIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QRay3D_Test.cpp -o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QRay3D_Test.o

$(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QRay_QVector4_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QRay_QVector4_Test.cpp
	$(CXX_DEBUGWIN32SHAREDRTDYNAMIC) $(COMPILEROPTIONS_DEBUGWIN32SHAREDRTDYNAMIC) $(DEFINITIONS_DEBUGWIN32SHAREDRTDYNAMIC) $(INCLUDES_DEBUGWIN32SHAREDRTDYNAMIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QRay_QVector4_Test.cpp -o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QRay_QVector4_Test.o

$(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QRay_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QRay_Test.cpp
	$(CXX_DEBUGWIN32SHAREDRTDYNAMIC) $(COMPILEROPTIONS_DEBUGWIN32SHAREDRTDYNAMIC) $(DEFINITIONS_DEBUGWIN32SHAREDRTDYNAMIC) $(INCLUDES_DEBUGWIN32SHAREDRTDYNAMIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QRay_Test.cpp -o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QRay_Test.o

$(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QRotationMatrix3x3_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QRotationMatrix3x3_Test.cpp
	$(CXX_DEBUGWIN32SHAREDRTDYNAMIC) $(COMPILEROPTIONS_DEBUGWIN32SHAREDRTDYNAMIC) $(DEFINITIONS_DEBUGWIN32SHAREDRTDYNAMIC) $(INCLUDES_DEBUGWIN32SHAREDRTDYNAMIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QRotationMatrix3x3_Test.cpp -o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QRotationMatrix3x3_Test.o

$(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QScalingMatrix3x3_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QScalingMatrix3x3_Test.cpp
	$(CXX_DEBUGWIN32SHAREDRTDYNAMIC) $(COMPILEROPTIONS_DEBUGWIN32SHAREDRTDYNAMIC) $(DEFINITIONS_DEBUGWIN32SHAREDRTDYNAMIC) $(INCLUDES_DEBUGWIN32SHAREDRTDYNAMIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QScalingMatrix3x3_Test.cpp -o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QScalingMatrix3x3_Test.o

$(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QSpaceConversionMatrix_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QSpaceConversionMatrix_Test.cpp
	$(CXX_DEBUGWIN32SHAREDRTDYNAMIC) $(COMPILEROPTIONS_DEBUGWIN32SHAREDRTDYNAMIC) $(DEFINITIONS_DEBUGWIN32SHAREDRTDYNAMIC) $(INCLUDES_DEBUGWIN32SHAREDRTDYNAMIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QSpaceConversionMatrix_Test.cpp -o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QSpaceConversionMatrix_Test.o

$(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QSphere_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QSphere_Test.cpp
	$(CXX_DEBUGWIN32SHAREDRTDYNAMIC) $(COMPILEROPTIONS_DEBUGWIN32SHAREDRTDYNAMIC) $(DEFINITIONS_DEBUGWIN32SHAREDRTDYNAMIC) $(INCLUDES_DEBUGWIN32SHAREDRTDYNAMIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QSphere_Test.cpp -o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QSphere_Test.o

$(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QTransformationMatrix3x3_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QTransformationMatrix3x3_Test.cpp
	$(CXX_DEBUGWIN32SHAREDRTDYNAMIC) $(COMPILEROPTIONS_DEBUGWIN32SHAREDRTDYNAMIC) $(DEFINITIONS_DEBUGWIN32SHAREDRTDYNAMIC) $(INCLUDES_DEBUGWIN32SHAREDRTDYNAMIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QTransformationMatrix3x3_Test.cpp -o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QTransformationMatrix3x3_Test.o

$(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QTransformationMatrix_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QTransformationMatrix_Test.cpp
	$(CXX_DEBUGWIN32SHAREDRTDYNAMIC) $(COMPILEROPTIONS_DEBUGWIN32SHAREDRTDYNAMIC) $(DEFINITIONS_DEBUGWIN32SHAREDRTDYNAMIC) $(INCLUDES_DEBUGWIN32SHAREDRTDYNAMIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QTransformationMatrix_Test.cpp -o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QTransformationMatrix_Test.o

$(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QTranslationMatrix_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QTranslationMatrix_Test.cpp
	$(CXX_DEBUGWIN32SHAREDRTDYNAMIC) $(COMPILEROPTIONS_DEBUGWIN32SHAREDRTDYNAMIC) $(DEFINITIONS_DEBUGWIN32SHAREDRTDYNAMIC) $(INCLUDES_DEBUGWIN32SHAREDRTDYNAMIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QTranslationMatrix_Test.cpp -o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QTranslationMatrix_Test.o

$(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QTriangle2D_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QTriangle2D_Test.cpp
	$(CXX_DEBUGWIN32SHAREDRTDYNAMIC) $(COMPILEROPTIONS_DEBUGWIN32SHAREDRTDYNAMIC) $(DEFINITIONS_DEBUGWIN32SHAREDRTDYNAMIC) $(INCLUDES_DEBUGWIN32SHAREDRTDYNAMIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QTriangle2D_Test.cpp -o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QTriangle2D_Test.o

$(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QTriangle3D_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QTriangle3D_Test.cpp
	$(CXX_DEBUGWIN32SHAREDRTDYNAMIC) $(COMPILEROPTIONS_DEBUGWIN32SHAREDRTDYNAMIC) $(DEFINITIONS_DEBUGWIN32SHAREDRTDYNAMIC) $(INCLUDES_DEBUGWIN32SHAREDRTDYNAMIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QTriangle3D_Test.cpp -o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QTriangle3D_Test.o

$(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QTriangle_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QTriangle_Test.cpp
	$(CXX_DEBUGWIN32SHAREDRTDYNAMIC) $(COMPILEROPTIONS_DEBUGWIN32SHAREDRTDYNAMIC) $(DEFINITIONS_DEBUGWIN32SHAREDRTDYNAMIC) $(INCLUDES_DEBUGWIN32SHAREDRTDYNAMIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QTriangle_Test.cpp -o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QTriangle_Test.o

$(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QVector2_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QVector2_Test.cpp
	$(CXX_DEBUGWIN32SHAREDRTDYNAMIC) $(COMPILEROPTIONS_DEBUGWIN32SHAREDRTDYNAMIC) $(DEFINITIONS_DEBUGWIN32SHAREDRTDYNAMIC) $(INCLUDES_DEBUGWIN32SHAREDRTDYNAMIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QVector2_Test.cpp -o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QVector2_Test.o

$(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QVector3_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QVector3_Test.cpp
	$(CXX_DEBUGWIN32SHAREDRTDYNAMIC) $(COMPILEROPTIONS_DEBUGWIN32SHAREDRTDYNAMIC) $(DEFINITIONS_DEBUGWIN32SHAREDRTDYNAMIC) $(INCLUDES_DEBUGWIN32SHAREDRTDYNAMIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QVector3_Test.cpp -o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QVector3_Test.o

$(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QVector4_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QVector4_Test.cpp
	$(CXX_DEBUGWIN32SHAREDRTDYNAMIC) $(COMPILEROPTIONS_DEBUGWIN32SHAREDRTDYNAMIC) $(DEFINITIONS_DEBUGWIN32SHAREDRTDYNAMIC) $(INCLUDES_DEBUGWIN32SHAREDRTDYNAMIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QVector4_Test.cpp -o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QVector4_Test.o

$(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.SQAngle_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/SQAngle_Test.cpp
	$(CXX_DEBUGWIN32SHAREDRTDYNAMIC) $(COMPILEROPTIONS_DEBUGWIN32SHAREDRTDYNAMIC) $(DEFINITIONS_DEBUGWIN32SHAREDRTDYNAMIC) $(INCLUDES_DEBUGWIN32SHAREDRTDYNAMIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/SQAngle_Test.cpp -o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.SQAngle_Test.o

$(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.SQPoint_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/SQPoint_Test.cpp
	$(CXX_DEBUGWIN32SHAREDRTDYNAMIC) $(COMPILEROPTIONS_DEBUGWIN32SHAREDRTDYNAMIC) $(DEFINITIONS_DEBUGWIN32SHAREDRTDYNAMIC) $(INCLUDES_DEBUGWIN32SHAREDRTDYNAMIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/SQPoint_Test.cpp -o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.SQPoint_Test.o

$(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QEvent_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QEvent_Test.cpp
	$(CXX_DEBUGWIN32SHAREDRTDYNAMIC) $(COMPILEROPTIONS_DEBUGWIN32SHAREDRTDYNAMIC) $(DEFINITIONS_DEBUGWIN32SHAREDRTDYNAMIC) $(INCLUDES_DEBUGWIN32SHAREDRTDYNAMIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QEvent_Test.cpp -o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTDYNAMIC)__.__.__.tests.unit.testmodule_tools.QEvent_Test.o

$(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTDYNAMIC)__.__.__.testsystem.EQTestType.o: $(EXECUTION_PATH)../../../testsystem/EQTestType.cpp
	$(CXX_DEBUGWIN32SHAREDRTDYNAMIC) $(COMPILEROPTIONS_DEBUGWIN32SHAREDRTDYNAMIC) $(DEFINITIONS_DEBUGWIN32SHAREDRTDYNAMIC) $(INCLUDES_DEBUGWIN32SHAREDRTDYNAMIC) -c $(EXECUTION_PATH)../../../testsystem/EQTestType.cpp -o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTDYNAMIC)__.__.__.testsystem.EQTestType.o

$(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTDYNAMIC)__.__.__.testsystem.QCommonTestConfig.o: $(EXECUTION_PATH)../../../testsystem/QCommonTestConfig.cpp
	$(CXX_DEBUGWIN32SHAREDRTDYNAMIC) $(COMPILEROPTIONS_DEBUGWIN32SHAREDRTDYNAMIC) $(DEFINITIONS_DEBUGWIN32SHAREDRTDYNAMIC) $(INCLUDES_DEBUGWIN32SHAREDRTDYNAMIC) -c $(EXECUTION_PATH)../../../testsystem/QCommonTestConfig.cpp -o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTDYNAMIC)__.__.__.testsystem.QCommonTestConfig.o

$(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTDYNAMIC)__.__.__.testsystem.QSimpleConfigLoader.o: $(EXECUTION_PATH)../../../testsystem/QSimpleConfigLoader.cpp
	$(CXX_DEBUGWIN32SHAREDRTDYNAMIC) $(COMPILEROPTIONS_DEBUGWIN32SHAREDRTDYNAMIC) $(DEFINITIONS_DEBUGWIN32SHAREDRTDYNAMIC) $(INCLUDES_DEBUGWIN32SHAREDRTDYNAMIC) -c $(EXECUTION_PATH)../../../testsystem/QSimpleConfigLoader.cpp -o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTDYNAMIC)__.__.__.testsystem.QSimpleConfigLoader.o

postbuildDebugWin32SharedrtDynamic:
	cmd /c copy "$(EXECUTION_PATH)..\..\..\bin\TestConfig.txt" "$(EXECUTION_PATH)..\..\..\bin\MinGW\DebugWin32SharedrtDynamic" /Y
	cmd /c copy "$(EXECUTION_PATH)..\..\..\bin\NormalizationTest.txt" "$(EXECUTION_PATH)..\..\..\bin\MinGW\DebugWin32SharedrtDynamic" /Y
	cmd /c copy "$(EXECUTION_PATH)..\..\..\..\3rdparty\ICU\bin\Win32\ReleaseSharedrtDynamic\MinGW\*.dll" "$(EXECUTION_PATH)..\..\..\bin\MinGW\DebugWin32SharedrtDynamic" /Y
	cmd /c copy "$(EXECUTION_PATH)..\..\..\..\bin\MinGW\DebugWin32SharedrtDynamic\QuimeraEngineCommon.dll" "$(EXECUTION_PATH)..\..\..\bin\MinGW\DebugWin32SharedrtDynamic" /Y
	cmd /c copy "$(EXECUTION_PATH)..\..\..\..\bin\MinGW\DebugWin32SharedrtDynamic\QuimeraEngineTools.dll" "$(EXECUTION_PATH)..\..\..\bin\MinGW\DebugWin32SharedrtDynamic" /Y


buildDebugWin32SharedrtDynamic: prebuildDebugWin32SharedrtDynamic DebugWin32SharedrtDynamic postbuildDebugWin32SharedrtDynamic

cleanDebugWin32SharedrtDynamic:
	rm -f $(OBJECTS_DEBUGWIN32SHAREDRTDYNAMIC)
	rm -f $(OUTPUT_DEBUGWIN32SHAREDRTDYNAMIC)
	cmd /c if exist $(EXECUTION_PATH)..\..\..\bin\MinGW\DebugWin32SharedrtDynamic rmdir "$(EXECUTION_PATH)..\..\..\bin\MinGW\DebugWin32SharedrtDynamic" /s /q
	cmd /c if exist $(EXECUTION_PATH)..\..\..\garbage\MinGW\DebugWin32SharedrtDynamic rmdir "$(EXECUTION_PATH)..\..\..\garbage\MinGW\DebugWin32SharedrtDynamic" /s /q


#------------------------------------------------------------
#------------- DebugWin32SharedrtStatic --------------
#------------------------------------------------------------
CXX_DEBUGWIN32SHAREDRTSTATIC = g++.exe
AR_DEBUGWIN32SHAREDRTSTATIC = ar.exe
LD_DEBUGWIN32SHAREDRTSTATIC = g++.exe
AS_DEBUGWIN32SHAREDRTSTATIC = as.exe
INCLUDES_DEBUGWIN32SHAREDRTSTATIC = $(INCLUDES_GLOBAL) -I$(EXECUTION_PATH)../../../../headers -I$(EXECUTION_PATH)../../../tests/unit/testmodule_system -I$(EXECUTION_PATH)../../../tests/unit -I$(EXECUTION_PATH)../../../../3rdparty/ICU/include
LIBRARYDIRS_DEBUGWIN32SHAREDRTSTATIC = $(LIBRARYDIRS_GLOBAL) -L$(EXECUTION_PATH)../../../../3rdparty/Boost/bin/Win32/DebugSharedrtStatic -L$(EXECUTION_PATH)../../../../3rdparty/ICU/bin/Win32/ReleaseSharedrtDynamic/MinGW -L$(EXECUTION_PATH)../../../../bin/MinGW/DebugWin32SharedrtStatic
LIBRARIES_DEBUGWIN32SHAREDRTSTATIC = $(LIBRARIES_GLOBAL) -lQuimeraEngineTools -lQuimeraEngineCommon -lboost_unit_test_framework-mt-d -licudt -licuuc -licuin
COMPILEROPTIONS_DEBUGWIN32SHAREDRTSTATIC = $(COMPILEROPTIONS_GLOBAL) -g -O0 -Wall -Wno-comment -Wno-unused-local-typedefs -m32 -isystem $(EXECUTION_PATH)../../../../3rdparty/Boost/include
LINKEROPTIONS_DEBUGWIN32SHAREDRTSTATIC = $(LINKEROPTIONS_GLOBAL) -m32
DEFINITIONS_DEBUGWIN32SHAREDRTSTATIC = $(DEFINITIONS_GLOBAL) -DBOOST_NO_RTTI -DBOOST_NO_TYPEID
OUTPUT_DEBUGWIN32SHAREDRTSTATIC = $(EXECUTION_PATH)../../../bin/MinGW/DebugWin32SharedrtStatic/Unit_TestModule_Tools.exe
INTERMEDIARYDIR_DEBUGWIN32SHAREDRTSTATIC = $(EXECUTION_PATH)../../../garbage/MinGW/DebugWin32SharedrtStatic/
OBJECTS_DEBUGWIN32SHAREDRTSTATIC = $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.TestModule_Tools.o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QArrayIterator_Test.o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QList_Test.o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QListIterator_Test.o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QNTree_Test.o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.CallCounter.o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QNTreeIterator_Test.o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QBinarySearchTree_Test.o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QConstArrayIterator_Test.o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QConstListIterator_Test.o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QConstNTreeIterator_Test.o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QConstBinarySearchTreeIterator_Test.o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.SQComparatorDefault_Test.o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QKeyValuePair_Test.o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.SQKeyValuePairComparator_Test.o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.SQEqualityComparator_Test.o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QDictionary_Test.o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QHashtable_Test.o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.SQIntegerHashProvider_Test.o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.SQStringHashProvider_Test.o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QConstDictionaryIterator_Test.o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QConstHashtableIterator_Test.o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QArrayDynamic_Test.o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QArrayFixed_Test.o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QDateTime_Test.o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QDstInformation_Test.o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QTimeSpan_Test.o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QTimeZone_Test.o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.SQTimeZoneFactory_Test.o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QBaseDualQuaternion_Test.o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QBaseHexahedron_Test.o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QBaseLineSegment_Test.o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QBaseMatrix2x2_Test.o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QBaseMatrix3x3_Test.o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QBaseMatrix3x4_Test.o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QBaseMatrix4x3_Test.o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QBaseMatrix4x4_Test.o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QBaseOrb_Test.o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QBasePlane_Test.o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QBaseQuadrilateral_Test.o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QBaseQuaternion_Test.o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QBaseRay_QVector4_Test.o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QBaseRay_Test.o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QBaseTriangle_Test.o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QBaseVector2_Test.o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QBaseVector3_Test.o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QBaseVector4_Test.o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QCircle_Test.o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QDualQuaternion_Test.o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QHexahedron_Test.o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QLineSegment2D_Test.o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QLineSegment3D_Test.o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QLineSegment_Test.o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QMatrix2x2_Test.o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QMatrix3x3_Test.o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QMatrix3x4_Test.o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QMatrix4x3_Test.o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QMatrix4x4_Test.o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QOrb_Test.o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QPlane_Test.o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QQuadrilateral_Test.o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QQuaternion_Test.o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QRay2D_Test.o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QRay3D_Test.o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QRay_QVector4_Test.o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QRay_Test.o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QRotationMatrix3x3_Test.o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QScalingMatrix3x3_Test.o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QSpaceConversionMatrix_Test.o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QSphere_Test.o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QTransformationMatrix3x3_Test.o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QTransformationMatrix_Test.o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QTranslationMatrix_Test.o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QTriangle2D_Test.o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QTriangle3D_Test.o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QTriangle_Test.o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QVector2_Test.o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QVector3_Test.o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QVector4_Test.o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.SQAngle_Test.o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.SQPoint_Test.o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QEvent_Test.o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTSTATIC)__.__.__.testsystem.EQTestType.o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTSTATIC)__.__.__.testsystem.QCommonTestConfig.o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTSTATIC)__.__.__.testsystem.QSimpleConfigLoader.o

prebuildDebugWin32SharedrtStatic:
	cmd /c if not exist $(EXECUTION_PATH)..\..\..\bin\MinGW\DebugWin32SharedrtStatic mkdir "$(EXECUTION_PATH)..\..\..\bin\MinGW\DebugWin32SharedrtStatic"
	cmd /c if not exist $(EXECUTION_PATH)..\..\..\garbage\MinGW\DebugWin32SharedrtStatic mkdir "$(EXECUTION_PATH)..\..\..\garbage\MinGW\DebugWin32SharedrtStatic"


DebugWin32SharedrtStatic: $(OBJECTS_DEBUGWIN32SHAREDRTSTATIC)
	$(LD_DEBUGWIN32SHAREDRTSTATIC) $(DEFINITIONS_DEBUGWIN32SHAREDRTSTATIC) $(LINKEROPTIONS_DEBUGWIN32SHAREDRTSTATIC) $(LIBRARYDIRS_DEBUGWIN32SHAREDRTSTATIC) $(OBJECTS_DEBUGWIN32SHAREDRTSTATIC) $(LIBRARIES_DEBUGWIN32SHAREDRTSTATIC) -o $(OUTPUT_DEBUGWIN32SHAREDRTSTATIC)

$(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.TestModule_Tools.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/TestModule_Tools.cpp
	$(CXX_DEBUGWIN32SHAREDRTSTATIC) $(COMPILEROPTIONS_DEBUGWIN32SHAREDRTSTATIC) $(DEFINITIONS_DEBUGWIN32SHAREDRTSTATIC) $(INCLUDES_DEBUGWIN32SHAREDRTSTATIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/TestModule_Tools.cpp -o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.TestModule_Tools.o

$(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QArrayIterator_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QArrayIterator_Test.cpp
	$(CXX_DEBUGWIN32SHAREDRTSTATIC) $(COMPILEROPTIONS_DEBUGWIN32SHAREDRTSTATIC) $(DEFINITIONS_DEBUGWIN32SHAREDRTSTATIC) $(INCLUDES_DEBUGWIN32SHAREDRTSTATIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QArrayIterator_Test.cpp -o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QArrayIterator_Test.o

$(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QList_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QList_Test.cpp
	$(CXX_DEBUGWIN32SHAREDRTSTATIC) $(COMPILEROPTIONS_DEBUGWIN32SHAREDRTSTATIC) $(DEFINITIONS_DEBUGWIN32SHAREDRTSTATIC) $(INCLUDES_DEBUGWIN32SHAREDRTSTATIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QList_Test.cpp -o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QList_Test.o

$(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QListIterator_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QListIterator_Test.cpp
	$(CXX_DEBUGWIN32SHAREDRTSTATIC) $(COMPILEROPTIONS_DEBUGWIN32SHAREDRTSTATIC) $(DEFINITIONS_DEBUGWIN32SHAREDRTSTATIC) $(INCLUDES_DEBUGWIN32SHAREDRTSTATIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QListIterator_Test.cpp -o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QListIterator_Test.o

$(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QNTree_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QNTree_Test.cpp
	$(CXX_DEBUGWIN32SHAREDRTSTATIC) $(COMPILEROPTIONS_DEBUGWIN32SHAREDRTSTATIC) $(DEFINITIONS_DEBUGWIN32SHAREDRTSTATIC) $(INCLUDES_DEBUGWIN32SHAREDRTSTATIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QNTree_Test.cpp -o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QNTree_Test.o

$(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.CallCounter.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/CallCounter.cpp
	$(CXX_DEBUGWIN32SHAREDRTSTATIC) $(COMPILEROPTIONS_DEBUGWIN32SHAREDRTSTATIC) $(DEFINITIONS_DEBUGWIN32SHAREDRTSTATIC) $(INCLUDES_DEBUGWIN32SHAREDRTSTATIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/CallCounter.cpp -o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.CallCounter.o

$(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QNTreeIterator_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QNTreeIterator_Test.cpp
	$(CXX_DEBUGWIN32SHAREDRTSTATIC) $(COMPILEROPTIONS_DEBUGWIN32SHAREDRTSTATIC) $(DEFINITIONS_DEBUGWIN32SHAREDRTSTATIC) $(INCLUDES_DEBUGWIN32SHAREDRTSTATIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QNTreeIterator_Test.cpp -o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QNTreeIterator_Test.o

$(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QBinarySearchTree_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QBinarySearchTree_Test.cpp
	$(CXX_DEBUGWIN32SHAREDRTSTATIC) $(COMPILEROPTIONS_DEBUGWIN32SHAREDRTSTATIC) $(DEFINITIONS_DEBUGWIN32SHAREDRTSTATIC) $(INCLUDES_DEBUGWIN32SHAREDRTSTATIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QBinarySearchTree_Test.cpp -o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QBinarySearchTree_Test.o

$(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QConstArrayIterator_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QConstArrayIterator_Test.cpp
	$(CXX_DEBUGWIN32SHAREDRTSTATIC) $(COMPILEROPTIONS_DEBUGWIN32SHAREDRTSTATIC) $(DEFINITIONS_DEBUGWIN32SHAREDRTSTATIC) $(INCLUDES_DEBUGWIN32SHAREDRTSTATIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QConstArrayIterator_Test.cpp -o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QConstArrayIterator_Test.o

$(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QConstListIterator_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QConstListIterator_Test.cpp
	$(CXX_DEBUGWIN32SHAREDRTSTATIC) $(COMPILEROPTIONS_DEBUGWIN32SHAREDRTSTATIC) $(DEFINITIONS_DEBUGWIN32SHAREDRTSTATIC) $(INCLUDES_DEBUGWIN32SHAREDRTSTATIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QConstListIterator_Test.cpp -o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QConstListIterator_Test.o

$(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QConstNTreeIterator_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QConstNTreeIterator_Test.cpp
	$(CXX_DEBUGWIN32SHAREDRTSTATIC) $(COMPILEROPTIONS_DEBUGWIN32SHAREDRTSTATIC) $(DEFINITIONS_DEBUGWIN32SHAREDRTSTATIC) $(INCLUDES_DEBUGWIN32SHAREDRTSTATIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QConstNTreeIterator_Test.cpp -o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QConstNTreeIterator_Test.o

$(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QConstBinarySearchTreeIterator_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QConstBinarySearchTreeIterator_Test.cpp
	$(CXX_DEBUGWIN32SHAREDRTSTATIC) $(COMPILEROPTIONS_DEBUGWIN32SHAREDRTSTATIC) $(DEFINITIONS_DEBUGWIN32SHAREDRTSTATIC) $(INCLUDES_DEBUGWIN32SHAREDRTSTATIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QConstBinarySearchTreeIterator_Test.cpp -o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QConstBinarySearchTreeIterator_Test.o

$(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.SQComparatorDefault_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/SQComparatorDefault_Test.cpp
	$(CXX_DEBUGWIN32SHAREDRTSTATIC) $(COMPILEROPTIONS_DEBUGWIN32SHAREDRTSTATIC) $(DEFINITIONS_DEBUGWIN32SHAREDRTSTATIC) $(INCLUDES_DEBUGWIN32SHAREDRTSTATIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/SQComparatorDefault_Test.cpp -o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.SQComparatorDefault_Test.o

$(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QKeyValuePair_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QKeyValuePair_Test.cpp
	$(CXX_DEBUGWIN32SHAREDRTSTATIC) $(COMPILEROPTIONS_DEBUGWIN32SHAREDRTSTATIC) $(DEFINITIONS_DEBUGWIN32SHAREDRTSTATIC) $(INCLUDES_DEBUGWIN32SHAREDRTSTATIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QKeyValuePair_Test.cpp -o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QKeyValuePair_Test.o

$(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.SQKeyValuePairComparator_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/SQKeyValuePairComparator_Test.cpp
	$(CXX_DEBUGWIN32SHAREDRTSTATIC) $(COMPILEROPTIONS_DEBUGWIN32SHAREDRTSTATIC) $(DEFINITIONS_DEBUGWIN32SHAREDRTSTATIC) $(INCLUDES_DEBUGWIN32SHAREDRTSTATIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/SQKeyValuePairComparator_Test.cpp -o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.SQKeyValuePairComparator_Test.o

$(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.SQEqualityComparator_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/SQEqualityComparator_Test.cpp
	$(CXX_DEBUGWIN32SHAREDRTSTATIC) $(COMPILEROPTIONS_DEBUGWIN32SHAREDRTSTATIC) $(DEFINITIONS_DEBUGWIN32SHAREDRTSTATIC) $(INCLUDES_DEBUGWIN32SHAREDRTSTATIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/SQEqualityComparator_Test.cpp -o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.SQEqualityComparator_Test.o

$(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QDictionary_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QDictionary_Test.cpp
	$(CXX_DEBUGWIN32SHAREDRTSTATIC) $(COMPILEROPTIONS_DEBUGWIN32SHAREDRTSTATIC) $(DEFINITIONS_DEBUGWIN32SHAREDRTSTATIC) $(INCLUDES_DEBUGWIN32SHAREDRTSTATIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QDictionary_Test.cpp -o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QDictionary_Test.o

$(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QHashtable_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QHashtable_Test.cpp
	$(CXX_DEBUGWIN32SHAREDRTSTATIC) $(COMPILEROPTIONS_DEBUGWIN32SHAREDRTSTATIC) $(DEFINITIONS_DEBUGWIN32SHAREDRTSTATIC) $(INCLUDES_DEBUGWIN32SHAREDRTSTATIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QHashtable_Test.cpp -o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QHashtable_Test.o

$(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.SQIntegerHashProvider_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/SQIntegerHashProvider_Test.cpp
	$(CXX_DEBUGWIN32SHAREDRTSTATIC) $(COMPILEROPTIONS_DEBUGWIN32SHAREDRTSTATIC) $(DEFINITIONS_DEBUGWIN32SHAREDRTSTATIC) $(INCLUDES_DEBUGWIN32SHAREDRTSTATIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/SQIntegerHashProvider_Test.cpp -o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.SQIntegerHashProvider_Test.o

$(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.SQStringHashProvider_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/SQStringHashProvider_Test.cpp
	$(CXX_DEBUGWIN32SHAREDRTSTATIC) $(COMPILEROPTIONS_DEBUGWIN32SHAREDRTSTATIC) $(DEFINITIONS_DEBUGWIN32SHAREDRTSTATIC) $(INCLUDES_DEBUGWIN32SHAREDRTSTATIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/SQStringHashProvider_Test.cpp -o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.SQStringHashProvider_Test.o

$(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QConstDictionaryIterator_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QConstDictionaryIterator_Test.cpp
	$(CXX_DEBUGWIN32SHAREDRTSTATIC) $(COMPILEROPTIONS_DEBUGWIN32SHAREDRTSTATIC) $(DEFINITIONS_DEBUGWIN32SHAREDRTSTATIC) $(INCLUDES_DEBUGWIN32SHAREDRTSTATIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QConstDictionaryIterator_Test.cpp -o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QConstDictionaryIterator_Test.o

$(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QConstHashtableIterator_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QConstHashtableIterator_Test.cpp
	$(CXX_DEBUGWIN32SHAREDRTSTATIC) $(COMPILEROPTIONS_DEBUGWIN32SHAREDRTSTATIC) $(DEFINITIONS_DEBUGWIN32SHAREDRTSTATIC) $(INCLUDES_DEBUGWIN32SHAREDRTSTATIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QConstHashtableIterator_Test.cpp -o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QConstHashtableIterator_Test.o

$(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QArrayDynamic_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QArrayDynamic_Test.cpp
	$(CXX_DEBUGWIN32SHAREDRTSTATIC) $(COMPILEROPTIONS_DEBUGWIN32SHAREDRTSTATIC) $(DEFINITIONS_DEBUGWIN32SHAREDRTSTATIC) $(INCLUDES_DEBUGWIN32SHAREDRTSTATIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QArrayDynamic_Test.cpp -o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QArrayDynamic_Test.o

$(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QArrayFixed_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QArrayFixed_Test.cpp
	$(CXX_DEBUGWIN32SHAREDRTSTATIC) $(COMPILEROPTIONS_DEBUGWIN32SHAREDRTSTATIC) $(DEFINITIONS_DEBUGWIN32SHAREDRTSTATIC) $(INCLUDES_DEBUGWIN32SHAREDRTSTATIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QArrayFixed_Test.cpp -o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QArrayFixed_Test.o

$(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QDateTime_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QDateTime_Test.cpp
	$(CXX_DEBUGWIN32SHAREDRTSTATIC) $(COMPILEROPTIONS_DEBUGWIN32SHAREDRTSTATIC) $(DEFINITIONS_DEBUGWIN32SHAREDRTSTATIC) $(INCLUDES_DEBUGWIN32SHAREDRTSTATIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QDateTime_Test.cpp -o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QDateTime_Test.o

$(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QDstInformation_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QDstInformation_Test.cpp
	$(CXX_DEBUGWIN32SHAREDRTSTATIC) $(COMPILEROPTIONS_DEBUGWIN32SHAREDRTSTATIC) $(DEFINITIONS_DEBUGWIN32SHAREDRTSTATIC) $(INCLUDES_DEBUGWIN32SHAREDRTSTATIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QDstInformation_Test.cpp -o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QDstInformation_Test.o

$(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QTimeSpan_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QTimeSpan_Test.cpp
	$(CXX_DEBUGWIN32SHAREDRTSTATIC) $(COMPILEROPTIONS_DEBUGWIN32SHAREDRTSTATIC) $(DEFINITIONS_DEBUGWIN32SHAREDRTSTATIC) $(INCLUDES_DEBUGWIN32SHAREDRTSTATIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QTimeSpan_Test.cpp -o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QTimeSpan_Test.o

$(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QTimeZone_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QTimeZone_Test.cpp
	$(CXX_DEBUGWIN32SHAREDRTSTATIC) $(COMPILEROPTIONS_DEBUGWIN32SHAREDRTSTATIC) $(DEFINITIONS_DEBUGWIN32SHAREDRTSTATIC) $(INCLUDES_DEBUGWIN32SHAREDRTSTATIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QTimeZone_Test.cpp -o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QTimeZone_Test.o

$(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.SQTimeZoneFactory_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/SQTimeZoneFactory_Test.cpp
	$(CXX_DEBUGWIN32SHAREDRTSTATIC) $(COMPILEROPTIONS_DEBUGWIN32SHAREDRTSTATIC) $(DEFINITIONS_DEBUGWIN32SHAREDRTSTATIC) $(INCLUDES_DEBUGWIN32SHAREDRTSTATIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/SQTimeZoneFactory_Test.cpp -o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.SQTimeZoneFactory_Test.o

$(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QBaseDualQuaternion_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QBaseDualQuaternion_Test.cpp
	$(CXX_DEBUGWIN32SHAREDRTSTATIC) $(COMPILEROPTIONS_DEBUGWIN32SHAREDRTSTATIC) $(DEFINITIONS_DEBUGWIN32SHAREDRTSTATIC) $(INCLUDES_DEBUGWIN32SHAREDRTSTATIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QBaseDualQuaternion_Test.cpp -o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QBaseDualQuaternion_Test.o

$(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QBaseHexahedron_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QBaseHexahedron_Test.cpp
	$(CXX_DEBUGWIN32SHAREDRTSTATIC) $(COMPILEROPTIONS_DEBUGWIN32SHAREDRTSTATIC) $(DEFINITIONS_DEBUGWIN32SHAREDRTSTATIC) $(INCLUDES_DEBUGWIN32SHAREDRTSTATIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QBaseHexahedron_Test.cpp -o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QBaseHexahedron_Test.o

$(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QBaseLineSegment_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QBaseLineSegment_Test.cpp
	$(CXX_DEBUGWIN32SHAREDRTSTATIC) $(COMPILEROPTIONS_DEBUGWIN32SHAREDRTSTATIC) $(DEFINITIONS_DEBUGWIN32SHAREDRTSTATIC) $(INCLUDES_DEBUGWIN32SHAREDRTSTATIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QBaseLineSegment_Test.cpp -o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QBaseLineSegment_Test.o

$(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QBaseMatrix2x2_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QBaseMatrix2x2_Test.cpp
	$(CXX_DEBUGWIN32SHAREDRTSTATIC) $(COMPILEROPTIONS_DEBUGWIN32SHAREDRTSTATIC) $(DEFINITIONS_DEBUGWIN32SHAREDRTSTATIC) $(INCLUDES_DEBUGWIN32SHAREDRTSTATIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QBaseMatrix2x2_Test.cpp -o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QBaseMatrix2x2_Test.o

$(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QBaseMatrix3x3_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QBaseMatrix3x3_Test.cpp
	$(CXX_DEBUGWIN32SHAREDRTSTATIC) $(COMPILEROPTIONS_DEBUGWIN32SHAREDRTSTATIC) $(DEFINITIONS_DEBUGWIN32SHAREDRTSTATIC) $(INCLUDES_DEBUGWIN32SHAREDRTSTATIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QBaseMatrix3x3_Test.cpp -o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QBaseMatrix3x3_Test.o

$(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QBaseMatrix3x4_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QBaseMatrix3x4_Test.cpp
	$(CXX_DEBUGWIN32SHAREDRTSTATIC) $(COMPILEROPTIONS_DEBUGWIN32SHAREDRTSTATIC) $(DEFINITIONS_DEBUGWIN32SHAREDRTSTATIC) $(INCLUDES_DEBUGWIN32SHAREDRTSTATIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QBaseMatrix3x4_Test.cpp -o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QBaseMatrix3x4_Test.o

$(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QBaseMatrix4x3_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QBaseMatrix4x3_Test.cpp
	$(CXX_DEBUGWIN32SHAREDRTSTATIC) $(COMPILEROPTIONS_DEBUGWIN32SHAREDRTSTATIC) $(DEFINITIONS_DEBUGWIN32SHAREDRTSTATIC) $(INCLUDES_DEBUGWIN32SHAREDRTSTATIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QBaseMatrix4x3_Test.cpp -o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QBaseMatrix4x3_Test.o

$(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QBaseMatrix4x4_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QBaseMatrix4x4_Test.cpp
	$(CXX_DEBUGWIN32SHAREDRTSTATIC) $(COMPILEROPTIONS_DEBUGWIN32SHAREDRTSTATIC) $(DEFINITIONS_DEBUGWIN32SHAREDRTSTATIC) $(INCLUDES_DEBUGWIN32SHAREDRTSTATIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QBaseMatrix4x4_Test.cpp -o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QBaseMatrix4x4_Test.o

$(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QBaseOrb_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QBaseOrb_Test.cpp
	$(CXX_DEBUGWIN32SHAREDRTSTATIC) $(COMPILEROPTIONS_DEBUGWIN32SHAREDRTSTATIC) $(DEFINITIONS_DEBUGWIN32SHAREDRTSTATIC) $(INCLUDES_DEBUGWIN32SHAREDRTSTATIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QBaseOrb_Test.cpp -o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QBaseOrb_Test.o

$(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QBasePlane_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QBasePlane_Test.cpp
	$(CXX_DEBUGWIN32SHAREDRTSTATIC) $(COMPILEROPTIONS_DEBUGWIN32SHAREDRTSTATIC) $(DEFINITIONS_DEBUGWIN32SHAREDRTSTATIC) $(INCLUDES_DEBUGWIN32SHAREDRTSTATIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QBasePlane_Test.cpp -o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QBasePlane_Test.o

$(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QBaseQuadrilateral_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QBaseQuadrilateral_Test.cpp
	$(CXX_DEBUGWIN32SHAREDRTSTATIC) $(COMPILEROPTIONS_DEBUGWIN32SHAREDRTSTATIC) $(DEFINITIONS_DEBUGWIN32SHAREDRTSTATIC) $(INCLUDES_DEBUGWIN32SHAREDRTSTATIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QBaseQuadrilateral_Test.cpp -o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QBaseQuadrilateral_Test.o

$(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QBaseQuaternion_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QBaseQuaternion_Test.cpp
	$(CXX_DEBUGWIN32SHAREDRTSTATIC) $(COMPILEROPTIONS_DEBUGWIN32SHAREDRTSTATIC) $(DEFINITIONS_DEBUGWIN32SHAREDRTSTATIC) $(INCLUDES_DEBUGWIN32SHAREDRTSTATIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QBaseQuaternion_Test.cpp -o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QBaseQuaternion_Test.o

$(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QBaseRay_QVector4_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QBaseRay_QVector4_Test.cpp
	$(CXX_DEBUGWIN32SHAREDRTSTATIC) $(COMPILEROPTIONS_DEBUGWIN32SHAREDRTSTATIC) $(DEFINITIONS_DEBUGWIN32SHAREDRTSTATIC) $(INCLUDES_DEBUGWIN32SHAREDRTSTATIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QBaseRay_QVector4_Test.cpp -o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QBaseRay_QVector4_Test.o

$(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QBaseRay_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QBaseRay_Test.cpp
	$(CXX_DEBUGWIN32SHAREDRTSTATIC) $(COMPILEROPTIONS_DEBUGWIN32SHAREDRTSTATIC) $(DEFINITIONS_DEBUGWIN32SHAREDRTSTATIC) $(INCLUDES_DEBUGWIN32SHAREDRTSTATIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QBaseRay_Test.cpp -o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QBaseRay_Test.o

$(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QBaseTriangle_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QBaseTriangle_Test.cpp
	$(CXX_DEBUGWIN32SHAREDRTSTATIC) $(COMPILEROPTIONS_DEBUGWIN32SHAREDRTSTATIC) $(DEFINITIONS_DEBUGWIN32SHAREDRTSTATIC) $(INCLUDES_DEBUGWIN32SHAREDRTSTATIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QBaseTriangle_Test.cpp -o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QBaseTriangle_Test.o

$(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QBaseVector2_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QBaseVector2_Test.cpp
	$(CXX_DEBUGWIN32SHAREDRTSTATIC) $(COMPILEROPTIONS_DEBUGWIN32SHAREDRTSTATIC) $(DEFINITIONS_DEBUGWIN32SHAREDRTSTATIC) $(INCLUDES_DEBUGWIN32SHAREDRTSTATIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QBaseVector2_Test.cpp -o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QBaseVector2_Test.o

$(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QBaseVector3_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QBaseVector3_Test.cpp
	$(CXX_DEBUGWIN32SHAREDRTSTATIC) $(COMPILEROPTIONS_DEBUGWIN32SHAREDRTSTATIC) $(DEFINITIONS_DEBUGWIN32SHAREDRTSTATIC) $(INCLUDES_DEBUGWIN32SHAREDRTSTATIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QBaseVector3_Test.cpp -o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QBaseVector3_Test.o

$(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QBaseVector4_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QBaseVector4_Test.cpp
	$(CXX_DEBUGWIN32SHAREDRTSTATIC) $(COMPILEROPTIONS_DEBUGWIN32SHAREDRTSTATIC) $(DEFINITIONS_DEBUGWIN32SHAREDRTSTATIC) $(INCLUDES_DEBUGWIN32SHAREDRTSTATIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QBaseVector4_Test.cpp -o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QBaseVector4_Test.o

$(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QCircle_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QCircle_Test.cpp
	$(CXX_DEBUGWIN32SHAREDRTSTATIC) $(COMPILEROPTIONS_DEBUGWIN32SHAREDRTSTATIC) $(DEFINITIONS_DEBUGWIN32SHAREDRTSTATIC) $(INCLUDES_DEBUGWIN32SHAREDRTSTATIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QCircle_Test.cpp -o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QCircle_Test.o

$(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QDualQuaternion_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QDualQuaternion_Test.cpp
	$(CXX_DEBUGWIN32SHAREDRTSTATIC) $(COMPILEROPTIONS_DEBUGWIN32SHAREDRTSTATIC) $(DEFINITIONS_DEBUGWIN32SHAREDRTSTATIC) $(INCLUDES_DEBUGWIN32SHAREDRTSTATIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QDualQuaternion_Test.cpp -o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QDualQuaternion_Test.o

$(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QHexahedron_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QHexahedron_Test.cpp
	$(CXX_DEBUGWIN32SHAREDRTSTATIC) $(COMPILEROPTIONS_DEBUGWIN32SHAREDRTSTATIC) $(DEFINITIONS_DEBUGWIN32SHAREDRTSTATIC) $(INCLUDES_DEBUGWIN32SHAREDRTSTATIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QHexahedron_Test.cpp -o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QHexahedron_Test.o

$(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QLineSegment2D_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QLineSegment2D_Test.cpp
	$(CXX_DEBUGWIN32SHAREDRTSTATIC) $(COMPILEROPTIONS_DEBUGWIN32SHAREDRTSTATIC) $(DEFINITIONS_DEBUGWIN32SHAREDRTSTATIC) $(INCLUDES_DEBUGWIN32SHAREDRTSTATIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QLineSegment2D_Test.cpp -o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QLineSegment2D_Test.o

$(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QLineSegment3D_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QLineSegment3D_Test.cpp
	$(CXX_DEBUGWIN32SHAREDRTSTATIC) $(COMPILEROPTIONS_DEBUGWIN32SHAREDRTSTATIC) $(DEFINITIONS_DEBUGWIN32SHAREDRTSTATIC) $(INCLUDES_DEBUGWIN32SHAREDRTSTATIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QLineSegment3D_Test.cpp -o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QLineSegment3D_Test.o

$(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QLineSegment_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QLineSegment_Test.cpp
	$(CXX_DEBUGWIN32SHAREDRTSTATIC) $(COMPILEROPTIONS_DEBUGWIN32SHAREDRTSTATIC) $(DEFINITIONS_DEBUGWIN32SHAREDRTSTATIC) $(INCLUDES_DEBUGWIN32SHAREDRTSTATIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QLineSegment_Test.cpp -o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QLineSegment_Test.o

$(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QMatrix2x2_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QMatrix2x2_Test.cpp
	$(CXX_DEBUGWIN32SHAREDRTSTATIC) $(COMPILEROPTIONS_DEBUGWIN32SHAREDRTSTATIC) $(DEFINITIONS_DEBUGWIN32SHAREDRTSTATIC) $(INCLUDES_DEBUGWIN32SHAREDRTSTATIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QMatrix2x2_Test.cpp -o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QMatrix2x2_Test.o

$(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QMatrix3x3_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QMatrix3x3_Test.cpp
	$(CXX_DEBUGWIN32SHAREDRTSTATIC) $(COMPILEROPTIONS_DEBUGWIN32SHAREDRTSTATIC) $(DEFINITIONS_DEBUGWIN32SHAREDRTSTATIC) $(INCLUDES_DEBUGWIN32SHAREDRTSTATIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QMatrix3x3_Test.cpp -o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QMatrix3x3_Test.o

$(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QMatrix3x4_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QMatrix3x4_Test.cpp
	$(CXX_DEBUGWIN32SHAREDRTSTATIC) $(COMPILEROPTIONS_DEBUGWIN32SHAREDRTSTATIC) $(DEFINITIONS_DEBUGWIN32SHAREDRTSTATIC) $(INCLUDES_DEBUGWIN32SHAREDRTSTATIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QMatrix3x4_Test.cpp -o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QMatrix3x4_Test.o

$(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QMatrix4x3_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QMatrix4x3_Test.cpp
	$(CXX_DEBUGWIN32SHAREDRTSTATIC) $(COMPILEROPTIONS_DEBUGWIN32SHAREDRTSTATIC) $(DEFINITIONS_DEBUGWIN32SHAREDRTSTATIC) $(INCLUDES_DEBUGWIN32SHAREDRTSTATIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QMatrix4x3_Test.cpp -o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QMatrix4x3_Test.o

$(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QMatrix4x4_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QMatrix4x4_Test.cpp
	$(CXX_DEBUGWIN32SHAREDRTSTATIC) $(COMPILEROPTIONS_DEBUGWIN32SHAREDRTSTATIC) $(DEFINITIONS_DEBUGWIN32SHAREDRTSTATIC) $(INCLUDES_DEBUGWIN32SHAREDRTSTATIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QMatrix4x4_Test.cpp -o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QMatrix4x4_Test.o

$(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QOrb_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QOrb_Test.cpp
	$(CXX_DEBUGWIN32SHAREDRTSTATIC) $(COMPILEROPTIONS_DEBUGWIN32SHAREDRTSTATIC) $(DEFINITIONS_DEBUGWIN32SHAREDRTSTATIC) $(INCLUDES_DEBUGWIN32SHAREDRTSTATIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QOrb_Test.cpp -o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QOrb_Test.o

$(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QPlane_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QPlane_Test.cpp
	$(CXX_DEBUGWIN32SHAREDRTSTATIC) $(COMPILEROPTIONS_DEBUGWIN32SHAREDRTSTATIC) $(DEFINITIONS_DEBUGWIN32SHAREDRTSTATIC) $(INCLUDES_DEBUGWIN32SHAREDRTSTATIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QPlane_Test.cpp -o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QPlane_Test.o

$(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QQuadrilateral_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QQuadrilateral_Test.cpp
	$(CXX_DEBUGWIN32SHAREDRTSTATIC) $(COMPILEROPTIONS_DEBUGWIN32SHAREDRTSTATIC) $(DEFINITIONS_DEBUGWIN32SHAREDRTSTATIC) $(INCLUDES_DEBUGWIN32SHAREDRTSTATIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QQuadrilateral_Test.cpp -o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QQuadrilateral_Test.o

$(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QQuaternion_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QQuaternion_Test.cpp
	$(CXX_DEBUGWIN32SHAREDRTSTATIC) $(COMPILEROPTIONS_DEBUGWIN32SHAREDRTSTATIC) $(DEFINITIONS_DEBUGWIN32SHAREDRTSTATIC) $(INCLUDES_DEBUGWIN32SHAREDRTSTATIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QQuaternion_Test.cpp -o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QQuaternion_Test.o

$(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QRay2D_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QRay2D_Test.cpp
	$(CXX_DEBUGWIN32SHAREDRTSTATIC) $(COMPILEROPTIONS_DEBUGWIN32SHAREDRTSTATIC) $(DEFINITIONS_DEBUGWIN32SHAREDRTSTATIC) $(INCLUDES_DEBUGWIN32SHAREDRTSTATIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QRay2D_Test.cpp -o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QRay2D_Test.o

$(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QRay3D_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QRay3D_Test.cpp
	$(CXX_DEBUGWIN32SHAREDRTSTATIC) $(COMPILEROPTIONS_DEBUGWIN32SHAREDRTSTATIC) $(DEFINITIONS_DEBUGWIN32SHAREDRTSTATIC) $(INCLUDES_DEBUGWIN32SHAREDRTSTATIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QRay3D_Test.cpp -o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QRay3D_Test.o

$(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QRay_QVector4_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QRay_QVector4_Test.cpp
	$(CXX_DEBUGWIN32SHAREDRTSTATIC) $(COMPILEROPTIONS_DEBUGWIN32SHAREDRTSTATIC) $(DEFINITIONS_DEBUGWIN32SHAREDRTSTATIC) $(INCLUDES_DEBUGWIN32SHAREDRTSTATIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QRay_QVector4_Test.cpp -o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QRay_QVector4_Test.o

$(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QRay_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QRay_Test.cpp
	$(CXX_DEBUGWIN32SHAREDRTSTATIC) $(COMPILEROPTIONS_DEBUGWIN32SHAREDRTSTATIC) $(DEFINITIONS_DEBUGWIN32SHAREDRTSTATIC) $(INCLUDES_DEBUGWIN32SHAREDRTSTATIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QRay_Test.cpp -o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QRay_Test.o

$(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QRotationMatrix3x3_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QRotationMatrix3x3_Test.cpp
	$(CXX_DEBUGWIN32SHAREDRTSTATIC) $(COMPILEROPTIONS_DEBUGWIN32SHAREDRTSTATIC) $(DEFINITIONS_DEBUGWIN32SHAREDRTSTATIC) $(INCLUDES_DEBUGWIN32SHAREDRTSTATIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QRotationMatrix3x3_Test.cpp -o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QRotationMatrix3x3_Test.o

$(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QScalingMatrix3x3_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QScalingMatrix3x3_Test.cpp
	$(CXX_DEBUGWIN32SHAREDRTSTATIC) $(COMPILEROPTIONS_DEBUGWIN32SHAREDRTSTATIC) $(DEFINITIONS_DEBUGWIN32SHAREDRTSTATIC) $(INCLUDES_DEBUGWIN32SHAREDRTSTATIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QScalingMatrix3x3_Test.cpp -o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QScalingMatrix3x3_Test.o

$(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QSpaceConversionMatrix_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QSpaceConversionMatrix_Test.cpp
	$(CXX_DEBUGWIN32SHAREDRTSTATIC) $(COMPILEROPTIONS_DEBUGWIN32SHAREDRTSTATIC) $(DEFINITIONS_DEBUGWIN32SHAREDRTSTATIC) $(INCLUDES_DEBUGWIN32SHAREDRTSTATIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QSpaceConversionMatrix_Test.cpp -o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QSpaceConversionMatrix_Test.o

$(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QSphere_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QSphere_Test.cpp
	$(CXX_DEBUGWIN32SHAREDRTSTATIC) $(COMPILEROPTIONS_DEBUGWIN32SHAREDRTSTATIC) $(DEFINITIONS_DEBUGWIN32SHAREDRTSTATIC) $(INCLUDES_DEBUGWIN32SHAREDRTSTATIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QSphere_Test.cpp -o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QSphere_Test.o

$(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QTransformationMatrix3x3_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QTransformationMatrix3x3_Test.cpp
	$(CXX_DEBUGWIN32SHAREDRTSTATIC) $(COMPILEROPTIONS_DEBUGWIN32SHAREDRTSTATIC) $(DEFINITIONS_DEBUGWIN32SHAREDRTSTATIC) $(INCLUDES_DEBUGWIN32SHAREDRTSTATIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QTransformationMatrix3x3_Test.cpp -o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QTransformationMatrix3x3_Test.o

$(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QTransformationMatrix_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QTransformationMatrix_Test.cpp
	$(CXX_DEBUGWIN32SHAREDRTSTATIC) $(COMPILEROPTIONS_DEBUGWIN32SHAREDRTSTATIC) $(DEFINITIONS_DEBUGWIN32SHAREDRTSTATIC) $(INCLUDES_DEBUGWIN32SHAREDRTSTATIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QTransformationMatrix_Test.cpp -o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QTransformationMatrix_Test.o

$(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QTranslationMatrix_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QTranslationMatrix_Test.cpp
	$(CXX_DEBUGWIN32SHAREDRTSTATIC) $(COMPILEROPTIONS_DEBUGWIN32SHAREDRTSTATIC) $(DEFINITIONS_DEBUGWIN32SHAREDRTSTATIC) $(INCLUDES_DEBUGWIN32SHAREDRTSTATIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QTranslationMatrix_Test.cpp -o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QTranslationMatrix_Test.o

$(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QTriangle2D_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QTriangle2D_Test.cpp
	$(CXX_DEBUGWIN32SHAREDRTSTATIC) $(COMPILEROPTIONS_DEBUGWIN32SHAREDRTSTATIC) $(DEFINITIONS_DEBUGWIN32SHAREDRTSTATIC) $(INCLUDES_DEBUGWIN32SHAREDRTSTATIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QTriangle2D_Test.cpp -o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QTriangle2D_Test.o

$(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QTriangle3D_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QTriangle3D_Test.cpp
	$(CXX_DEBUGWIN32SHAREDRTSTATIC) $(COMPILEROPTIONS_DEBUGWIN32SHAREDRTSTATIC) $(DEFINITIONS_DEBUGWIN32SHAREDRTSTATIC) $(INCLUDES_DEBUGWIN32SHAREDRTSTATIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QTriangle3D_Test.cpp -o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QTriangle3D_Test.o

$(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QTriangle_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QTriangle_Test.cpp
	$(CXX_DEBUGWIN32SHAREDRTSTATIC) $(COMPILEROPTIONS_DEBUGWIN32SHAREDRTSTATIC) $(DEFINITIONS_DEBUGWIN32SHAREDRTSTATIC) $(INCLUDES_DEBUGWIN32SHAREDRTSTATIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QTriangle_Test.cpp -o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QTriangle_Test.o

$(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QVector2_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QVector2_Test.cpp
	$(CXX_DEBUGWIN32SHAREDRTSTATIC) $(COMPILEROPTIONS_DEBUGWIN32SHAREDRTSTATIC) $(DEFINITIONS_DEBUGWIN32SHAREDRTSTATIC) $(INCLUDES_DEBUGWIN32SHAREDRTSTATIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QVector2_Test.cpp -o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QVector2_Test.o

$(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QVector3_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QVector3_Test.cpp
	$(CXX_DEBUGWIN32SHAREDRTSTATIC) $(COMPILEROPTIONS_DEBUGWIN32SHAREDRTSTATIC) $(DEFINITIONS_DEBUGWIN32SHAREDRTSTATIC) $(INCLUDES_DEBUGWIN32SHAREDRTSTATIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QVector3_Test.cpp -o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QVector3_Test.o

$(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QVector4_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QVector4_Test.cpp
	$(CXX_DEBUGWIN32SHAREDRTSTATIC) $(COMPILEROPTIONS_DEBUGWIN32SHAREDRTSTATIC) $(DEFINITIONS_DEBUGWIN32SHAREDRTSTATIC) $(INCLUDES_DEBUGWIN32SHAREDRTSTATIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QVector4_Test.cpp -o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QVector4_Test.o

$(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.SQAngle_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/SQAngle_Test.cpp
	$(CXX_DEBUGWIN32SHAREDRTSTATIC) $(COMPILEROPTIONS_DEBUGWIN32SHAREDRTSTATIC) $(DEFINITIONS_DEBUGWIN32SHAREDRTSTATIC) $(INCLUDES_DEBUGWIN32SHAREDRTSTATIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/SQAngle_Test.cpp -o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.SQAngle_Test.o

$(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.SQPoint_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/SQPoint_Test.cpp
	$(CXX_DEBUGWIN32SHAREDRTSTATIC) $(COMPILEROPTIONS_DEBUGWIN32SHAREDRTSTATIC) $(DEFINITIONS_DEBUGWIN32SHAREDRTSTATIC) $(INCLUDES_DEBUGWIN32SHAREDRTSTATIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/SQPoint_Test.cpp -o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.SQPoint_Test.o

$(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QEvent_Test.o: $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QEvent_Test.cpp
	$(CXX_DEBUGWIN32SHAREDRTSTATIC) $(COMPILEROPTIONS_DEBUGWIN32SHAREDRTSTATIC) $(DEFINITIONS_DEBUGWIN32SHAREDRTSTATIC) $(INCLUDES_DEBUGWIN32SHAREDRTSTATIC) -c $(EXECUTION_PATH)../../../tests/unit/testmodule_tools/QEvent_Test.cpp -o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTSTATIC)__.__.__.tests.unit.testmodule_tools.QEvent_Test.o

$(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTSTATIC)__.__.__.testsystem.EQTestType.o: $(EXECUTION_PATH)../../../testsystem/EQTestType.cpp
	$(CXX_DEBUGWIN32SHAREDRTSTATIC) $(COMPILEROPTIONS_DEBUGWIN32SHAREDRTSTATIC) $(DEFINITIONS_DEBUGWIN32SHAREDRTSTATIC) $(INCLUDES_DEBUGWIN32SHAREDRTSTATIC) -c $(EXECUTION_PATH)../../../testsystem/EQTestType.cpp -o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTSTATIC)__.__.__.testsystem.EQTestType.o

$(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTSTATIC)__.__.__.testsystem.QCommonTestConfig.o: $(EXECUTION_PATH)../../../testsystem/QCommonTestConfig.cpp
	$(CXX_DEBUGWIN32SHAREDRTSTATIC) $(COMPILEROPTIONS_DEBUGWIN32SHAREDRTSTATIC) $(DEFINITIONS_DEBUGWIN32SHAREDRTSTATIC) $(INCLUDES_DEBUGWIN32SHAREDRTSTATIC) -c $(EXECUTION_PATH)../../../testsystem/QCommonTestConfig.cpp -o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTSTATIC)__.__.__.testsystem.QCommonTestConfig.o

$(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTSTATIC)__.__.__.testsystem.QSimpleConfigLoader.o: $(EXECUTION_PATH)../../../testsystem/QSimpleConfigLoader.cpp
	$(CXX_DEBUGWIN32SHAREDRTSTATIC) $(COMPILEROPTIONS_DEBUGWIN32SHAREDRTSTATIC) $(DEFINITIONS_DEBUGWIN32SHAREDRTSTATIC) $(INCLUDES_DEBUGWIN32SHAREDRTSTATIC) -c $(EXECUTION_PATH)../../../testsystem/QSimpleConfigLoader.cpp -o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTSTATIC)__.__.__.testsystem.QSimpleConfigLoader.o

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