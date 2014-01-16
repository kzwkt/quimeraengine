#------------------------------------------------------------------------------#
# This makefile was generated by 'cbp2make' tool rev.137                       #
#------------------------------------------------------------------------------#


WORKDIR = %cd%

CC = gcc.exe
CXX = g++.exe
AR = ar.exe
LD = g++.exe
WINDRES = windres.exe

#DebugWin32SharedrtStatic
INC_DEBUGWIN32SHAREDRTSTATIC =  -I$(MAKEPATH)\\trunk\\headers -I$(MAKEPATH)\\trunk\\3rdparty\\Boost\\include
CFLAGS_DEBUGWIN32SHAREDRTSTATIC =  -march=pentium4 -Wshadow -Wredundant-decls -Wcast-align -Winline -Wmissing-include-dirs -Wswitch-default -Wall -fpermissive -g -fpermissive -D_DEBUG
RESINC_DEBUGWIN32SHAREDRTSTATIC =  
RCFLAGS_DEBUGWIN32SHAREDRTSTATIC =  
LIBDIR_DEBUGWIN32SHAREDRTSTATIC =  
LIB_DEBUGWIN32SHAREDRTSTATIC = 
LDFLAGS_DEBUGWIN32SHAREDRTSTATIC =  
OBJDIR_DEBUGWIN32SHAREDRTSTATIC = $(MAKEPATH)\\trunk\\garbage\\CodeBlocks10\\DebugWin32SharedrtStatic
DEP_DEBUGWIN32SHAREDRTSTATIC = 
OUT_DEBUGWIN32SHAREDRTSTATIC = $(MAKEPATH)\\trunk\\bin\\CodeBlocks10\\DebugWin32SharedrtStatic\\QuimeraEngineTools.lib
OBJ_DEBUGWIN32SHAREDRTSTATIC = $(OBJDIR_DEBUGWIN32SHAREDRTSTATIC)$(MAKEPATH__)\\trunk\\source\\QDualQuaternion.o $(OBJDIR_DEBUGWIN32SHAREDRTSTATIC)$(MAKEPATH__)\\trunk\\source\\EQSpaceRelation.o $(OBJDIR_DEBUGWIN32SHAREDRTSTATIC)$(MAKEPATH__)\\trunk\\source\\EQIntersections.o $(OBJDIR_DEBUGWIN32SHAREDRTSTATIC)$(MAKEPATH__)\\trunk\\source\\SQAngle.o $(OBJDIR_DEBUGWIN32SHAREDRTSTATIC)$(MAKEPATH__)\\trunk\\source\\QVector4.o $(OBJDIR_DEBUGWIN32SHAREDRTSTATIC)$(MAKEPATH__)\\trunk\\source\\QVector3.o $(OBJDIR_DEBUGWIN32SHAREDRTSTATIC)$(MAKEPATH__)\\trunk\\source\\QVector2.o $(OBJDIR_DEBUGWIN32SHAREDRTSTATIC)$(MAKEPATH__)\\trunk\\source\\QTransformationMatrix3x3.o $(OBJDIR_DEBUGWIN32SHAREDRTSTATIC)$(MAKEPATH__)\\trunk\\source\\QSpaceConversionMatrix.o $(OBJDIR_DEBUGWIN32SHAREDRTSTATIC)$(MAKEPATH__)\\trunk\\source\\QScalingMatrix3x3.o $(OBJDIR_DEBUGWIN32SHAREDRTSTATIC)$(MAKEPATH__)\\trunk\\source\\QRotationMatrix3x3.o $(OBJDIR_DEBUGWIN32SHAREDRTSTATIC)$(MAKEPATH__)\\trunk\\source\\QRay2D.o $(OBJDIR_DEBUGWIN32SHAREDRTSTATIC)$(MAKEPATH__)\\trunk\\source\\QQuaternion.o $(OBJDIR_DEBUGWIN32SHAREDRTSTATIC)$(MAKEPATH__)\\trunk\\source\\QQuadrilateral.o $(OBJDIR_DEBUGWIN32SHAREDRTSTATIC)$(MAKEPATH__)\\trunk\\source\\QPlane.o $(OBJDIR_DEBUGWIN32SHAREDRTSTATIC)$(MAKEPATH__)\\trunk\\source\\QMatrix4x4.o $(OBJDIR_DEBUGWIN32SHAREDRTSTATIC)$(MAKEPATH__)\\trunk\\source\\QMatrix4x3.o $(OBJDIR_DEBUGWIN32SHAREDRTSTATIC)$(MAKEPATH__)\\trunk\\source\\QMatrix3x4.o $(OBJDIR_DEBUGWIN32SHAREDRTSTATIC)$(MAKEPATH__)\\trunk\\source\\QMatrix3x3.o $(OBJDIR_DEBUGWIN32SHAREDRTSTATIC)$(MAKEPATH__)\\trunk\\source\\QMatrix2x2.o $(OBJDIR_DEBUGWIN32SHAREDRTSTATIC)$(MAKEPATH__)\\trunk\\source\\QLineSegment2D.o $(OBJDIR_DEBUGWIN32SHAREDRTSTATIC)$(MAKEPATH__)\\trunk\\source\\QCircle.o $(OBJDIR_DEBUGWIN32SHAREDRTSTATIC)$(MAKEPATH__)\\trunk\\source\\QTriangle2D.o $(OBJDIR_DEBUGWIN32SHAREDRTSTATIC)$(MAKEPATH__)\\trunk\\source\\ToolsExports.o $(OBJDIR_DEBUGWIN32SHAREDRTSTATIC)$(MAKEPATH__)\\trunk\\source\\QBaseDualQuaternion.o $(OBJDIR_DEBUGWIN32SHAREDRTSTATIC)$(MAKEPATH__)\\trunk\\source\\QBaseMatrix2x2.o $(OBJDIR_DEBUGWIN32SHAREDRTSTATIC)$(MAKEPATH__)\\trunk\\source\\QBaseMatrix3x3.o $(OBJDIR_DEBUGWIN32SHAREDRTSTATIC)$(MAKEPATH__)\\trunk\\source\\QBaseMatrix3x4.o $(OBJDIR_DEBUGWIN32SHAREDRTSTATIC)$(MAKEPATH__)\\trunk\\source\\QBaseMatrix4x3.o $(OBJDIR_DEBUGWIN32SHAREDRTSTATIC)$(MAKEPATH__)\\trunk\\source\\QBaseMatrix4x4.o $(OBJDIR_DEBUGWIN32SHAREDRTSTATIC)$(MAKEPATH__)\\trunk\\source\\QBasePlane.o $(OBJDIR_DEBUGWIN32SHAREDRTSTATIC)$(MAKEPATH__)\\trunk\\source\\QBaseQuadrilateral.o $(OBJDIR_DEBUGWIN32SHAREDRTSTATIC)$(MAKEPATH__)\\trunk\\source\\QBaseQuaternion.o $(OBJDIR_DEBUGWIN32SHAREDRTSTATIC)$(MAKEPATH__)\\trunk\\source\\QBaseVector2.o $(OBJDIR_DEBUGWIN32SHAREDRTSTATIC)$(MAKEPATH__)\\trunk\\source\\QBaseVector3.o $(OBJDIR_DEBUGWIN32SHAREDRTSTATIC)$(MAKEPATH__)\\trunk\\source\\QBaseVector4.o $(OBJDIR_DEBUGWIN32SHAREDRTSTATIC)$(MAKEPATH__)\\trunk\\source\\SQPoint.o

#DebugWin32SharedrtDynamic
INC_DEBUGWIN32SHAREDRTDYNAMIC =  -I$(MAKEPATH)\\trunk\\headers -I$(MAKEPATH)\\trunk\\3rdparty\\Boost\\include
CFLAGS_DEBUGWIN32SHAREDRTDYNAMIC =  -march=pentium4 -Wshadow -Wredundant-decls -Wcast-align -Winline -Wmissing-include-dirs -Wswitch-default -Wall -fpermissive -g -fpermissive -D_DEBUG -DQE_PREPROCESSOR_IMPORTLIB_COMMON -DQE_PREPROCESSOR_EXPORTLIB_TOOLS
RESINC_DEBUGWIN32SHAREDRTDYNAMIC =  
RCFLAGS_DEBUGWIN32SHAREDRTDYNAMIC =  
LIBDIR_DEBUGWIN32SHAREDRTDYNAMIC =  
LIB_DEBUGWIN32SHAREDRTDYNAMIC = $(MAKEPATH)\\trunk\\bin\CodeBlocks10\DebugWin32SharedrtDynamic\QuimeraEngineCommon.dll
LDFLAGS_DEBUGWIN32SHAREDRTDYNAMIC =  
OBJDIR_DEBUGWIN32SHAREDRTDYNAMIC = $(MAKEPATH)\\trunk\\garbage\\CodeBlocks10\\DebugWin32SharedrtDynamic
DEP_DEBUGWIN32SHAREDRTDYNAMIC = 
OUT_DEBUGWIN32SHAREDRTDYNAMIC = $(MAKEPATH)\\trunk\\bin\\CodeBlocks10\\DebugWin32SharedrtDynamic\\QuimeraEngineTools.dll
OBJ_DEBUGWIN32SHAREDRTDYNAMIC = $(OBJDIR_DEBUGWIN32SHAREDRTDYNAMIC)$(MAKEPATH__)\\trunk\\source\\QDualQuaternion.o $(OBJDIR_DEBUGWIN32SHAREDRTDYNAMIC)$(MAKEPATH__)\\trunk\\source\\EQSpaceRelation.o $(OBJDIR_DEBUGWIN32SHAREDRTDYNAMIC)$(MAKEPATH__)\\trunk\\source\\EQIntersections.o $(OBJDIR_DEBUGWIN32SHAREDRTDYNAMIC)$(MAKEPATH__)\\trunk\\source\\SQAngle.o $(OBJDIR_DEBUGWIN32SHAREDRTDYNAMIC)$(MAKEPATH__)\\trunk\\source\\QVector4.o $(OBJDIR_DEBUGWIN32SHAREDRTDYNAMIC)$(MAKEPATH__)\\trunk\\source\\QVector3.o $(OBJDIR_DEBUGWIN32SHAREDRTDYNAMIC)$(MAKEPATH__)\\trunk\\source\\QVector2.o $(OBJDIR_DEBUGWIN32SHAREDRTDYNAMIC)$(MAKEPATH__)\\trunk\\source\\QTransformationMatrix3x3.o $(OBJDIR_DEBUGWIN32SHAREDRTDYNAMIC)$(MAKEPATH__)\\trunk\\source\\QSpaceConversionMatrix.o $(OBJDIR_DEBUGWIN32SHAREDRTDYNAMIC)$(MAKEPATH__)\\trunk\\source\\QScalingMatrix3x3.o $(OBJDIR_DEBUGWIN32SHAREDRTDYNAMIC)$(MAKEPATH__)\\trunk\\source\\QRotationMatrix3x3.o $(OBJDIR_DEBUGWIN32SHAREDRTDYNAMIC)$(MAKEPATH__)\\trunk\\source\\QRay2D.o $(OBJDIR_DEBUGWIN32SHAREDRTDYNAMIC)$(MAKEPATH__)\\trunk\\source\\QQuaternion.o $(OBJDIR_DEBUGWIN32SHAREDRTDYNAMIC)$(MAKEPATH__)\\trunk\\source\\QQuadrilateral.o $(OBJDIR_DEBUGWIN32SHAREDRTDYNAMIC)$(MAKEPATH__)\\trunk\\source\\QPlane.o $(OBJDIR_DEBUGWIN32SHAREDRTDYNAMIC)$(MAKEPATH__)\\trunk\\source\\QMatrix4x4.o $(OBJDIR_DEBUGWIN32SHAREDRTDYNAMIC)$(MAKEPATH__)\\trunk\\source\\QMatrix4x3.o $(OBJDIR_DEBUGWIN32SHAREDRTDYNAMIC)$(MAKEPATH__)\\trunk\\source\\QMatrix3x4.o $(OBJDIR_DEBUGWIN32SHAREDRTDYNAMIC)$(MAKEPATH__)\\trunk\\source\\QMatrix3x3.o $(OBJDIR_DEBUGWIN32SHAREDRTDYNAMIC)$(MAKEPATH__)\\trunk\\source\\QMatrix2x2.o $(OBJDIR_DEBUGWIN32SHAREDRTDYNAMIC)$(MAKEPATH__)\\trunk\\source\\QLineSegment2D.o $(OBJDIR_DEBUGWIN32SHAREDRTDYNAMIC)$(MAKEPATH__)\\trunk\\source\\QCircle.o $(OBJDIR_DEBUGWIN32SHAREDRTDYNAMIC)$(MAKEPATH__)\\trunk\\source\\QTriangle2D.o $(OBJDIR_DEBUGWIN32SHAREDRTDYNAMIC)$(MAKEPATH__)\\trunk\\source\\ToolsExports.o $(OBJDIR_DEBUGWIN32SHAREDRTDYNAMIC)$(MAKEPATH__)\\trunk\\source\\QBaseDualQuaternion.o $(OBJDIR_DEBUGWIN32SHAREDRTDYNAMIC)$(MAKEPATH__)\\trunk\\source\\QBaseMatrix2x2.o $(OBJDIR_DEBUGWIN32SHAREDRTDYNAMIC)$(MAKEPATH__)\\trunk\\source\\QBaseMatrix3x3.o $(OBJDIR_DEBUGWIN32SHAREDRTDYNAMIC)$(MAKEPATH__)\\trunk\\source\\QBaseMatrix3x4.o $(OBJDIR_DEBUGWIN32SHAREDRTDYNAMIC)$(MAKEPATH__)\\trunk\\source\\QBaseMatrix4x3.o $(OBJDIR_DEBUGWIN32SHAREDRTDYNAMIC)$(MAKEPATH__)\\trunk\\source\\QBaseMatrix4x4.o $(OBJDIR_DEBUGWIN32SHAREDRTDYNAMIC)$(MAKEPATH__)\\trunk\\source\\QBasePlane.o $(OBJDIR_DEBUGWIN32SHAREDRTDYNAMIC)$(MAKEPATH__)\\trunk\\source\\QBaseQuadrilateral.o $(OBJDIR_DEBUGWIN32SHAREDRTDYNAMIC)$(MAKEPATH__)\\trunk\\source\\QBaseQuaternion.o $(OBJDIR_DEBUGWIN32SHAREDRTDYNAMIC)$(MAKEPATH__)\\trunk\\source\\QBaseVector2.o $(OBJDIR_DEBUGWIN32SHAREDRTDYNAMIC)$(MAKEPATH__)\\trunk\\source\\QBaseVector3.o $(OBJDIR_DEBUGWIN32SHAREDRTDYNAMIC)$(MAKEPATH__)\\trunk\\source\\QBaseVector4.o $(OBJDIR_DEBUGWIN32SHAREDRTDYNAMIC)$(MAKEPATH__)\\trunk\\source\\SQPoint.o
	
all: debugwin32sharedrtstatic debugwin32sharedrtdynamic

clean: clean_debugwin32sharedrtstatic clean_debugwin32sharedrtdynamic

#----------------------------------------------------------------------------------------------------------------------------------------------------------------------------#
#	DebugWin32SharedrtStatic   ~~~   DebugWin32SharedrtStatic   ~~~   DebugWin32SharedrtStatic   ~~~   DebugWin32SharedrtStatic   ~~~   DebugWin32SharedrtStatic   ~~~       #  
#----------------------------------------------------------------------------------------------------------------------------------------------------------------------------#
	
before_debugwin32sharedrtstatic: 
	cmd /c if not exist $(MAKEPATH)\\trunk\\bin\\CodeBlocks10\\DebugWin32SharedrtStatic md $(MAKEPATH)\\trunk\\bin\\CodeBlocks10\\DebugWin32SharedrtStatic
	cmd /c if not exist $(OBJDIR_DEBUGWIN32SHAREDRTSTATIC)$(MAKEPATH__)\\trunk\\source md $(OBJDIR_DEBUGWIN32SHAREDRTSTATIC)$(MAKEPATH__)\\trunk\\source

after_debugwin32sharedrtstatic: 

debugwin32sharedrtstatic: before_debugwin32sharedrtstatic out_debugwin32sharedrtstatic after_debugwin32sharedrtstatic

out_debugwin32sharedrtstatic: $(OBJ_DEBUGWIN32SHAREDRTSTATIC) $(DEP_DEBUGWIN32SHAREDRTSTATIC)
	$(AR) rcs $(OUT_DEBUGWIN32SHAREDRTSTATIC) $(OBJ_DEBUGWIN32SHAREDRTSTATIC)

$(OBJDIR_DEBUGWIN32SHAREDRTSTATIC)$(MAKEPATH__)\\trunk\\source\\QDualQuaternion.o: $(MAKEPATH)\\trunk\\source\\QDualQuaternion.cpp
	$(CXX) $(CFLAGS_DEBUGWIN32SHAREDRTSTATIC) $(INC_DEBUGWIN32SHAREDRTSTATIC) -c $(MAKEPATH)\\trunk\\source\\QDualQuaternion.cpp -o $(OBJDIR_DEBUGWIN32SHAREDRTSTATIC)$(MAKEPATH__)\\trunk\\source\\QDualQuaternion.o

$(OBJDIR_DEBUGWIN32SHAREDRTSTATIC)$(MAKEPATH__)\\trunk\\source\\EQSpaceRelation.o: $(MAKEPATH)\\trunk\\source\\EQSpaceRelation.cpp
	$(CXX) $(CFLAGS_DEBUGWIN32SHAREDRTSTATIC) $(INC_DEBUGWIN32SHAREDRTSTATIC) -c $(MAKEPATH)\\trunk\\source\\EQSpaceRelation.cpp -o $(OBJDIR_DEBUGWIN32SHAREDRTSTATIC)$(MAKEPATH__)\\trunk\\source\\EQSpaceRelation.o

$(OBJDIR_DEBUGWIN32SHAREDRTSTATIC)$(MAKEPATH__)\\trunk\\source\\EQIntersections.o: $(MAKEPATH)\\trunk\\source\\EQIntersections.cpp
	$(CXX) $(CFLAGS_DEBUGWIN32SHAREDRTSTATIC) $(INC_DEBUGWIN32SHAREDRTSTATIC) -c $(MAKEPATH)\\trunk\\source\\EQIntersections.cpp -o $(OBJDIR_DEBUGWIN32SHAREDRTSTATIC)$(MAKEPATH__)\\trunk\\source\\EQIntersections.o

$(OBJDIR_DEBUGWIN32SHAREDRTSTATIC)$(MAKEPATH__)\\trunk\\source\\SQAngle.o: $(MAKEPATH)\\trunk\\source\\SQAngle.cpp
	$(CXX) $(CFLAGS_DEBUGWIN32SHAREDRTSTATIC) $(INC_DEBUGWIN32SHAREDRTSTATIC) -c $(MAKEPATH)\\trunk\\source\\SQAngle.cpp -o $(OBJDIR_DEBUGWIN32SHAREDRTSTATIC)$(MAKEPATH__)\\trunk\\source\\SQAngle.o

$(OBJDIR_DEBUGWIN32SHAREDRTSTATIC)$(MAKEPATH__)\\trunk\\source\\QVector4.o: $(MAKEPATH)\\trunk\\source\\QVector4.cpp
	$(CXX) $(CFLAGS_DEBUGWIN32SHAREDRTSTATIC) $(INC_DEBUGWIN32SHAREDRTSTATIC) -c $(MAKEPATH)\\trunk\\source\\QVector4.cpp -o $(OBJDIR_DEBUGWIN32SHAREDRTSTATIC)$(MAKEPATH__)\\trunk\\source\\QVector4.o

$(OBJDIR_DEBUGWIN32SHAREDRTSTATIC)$(MAKEPATH__)\\trunk\\source\\QVector3.o: $(MAKEPATH)\\trunk\\source\\QVector3.cpp
	$(CXX) $(CFLAGS_DEBUGWIN32SHAREDRTSTATIC) $(INC_DEBUGWIN32SHAREDRTSTATIC) -c $(MAKEPATH)\\trunk\\source\\QVector3.cpp -o $(OBJDIR_DEBUGWIN32SHAREDRTSTATIC)$(MAKEPATH__)\\trunk\\source\\QVector3.o

$(OBJDIR_DEBUGWIN32SHAREDRTSTATIC)$(MAKEPATH__)\\trunk\\source\\QVector2.o: $(MAKEPATH)\\trunk\\source\\QVector2.cpp
	$(CXX) $(CFLAGS_DEBUGWIN32SHAREDRTSTATIC) $(INC_DEBUGWIN32SHAREDRTSTATIC) -c $(MAKEPATH)\\trunk\\source\\QVector2.cpp -o $(OBJDIR_DEBUGWIN32SHAREDRTSTATIC)$(MAKEPATH__)\\trunk\\source\\QVector2.o

$(OBJDIR_DEBUGWIN32SHAREDRTSTATIC)$(MAKEPATH__)\\trunk\\source\\QTransformationMatrix3x3.o: $(MAKEPATH)\\trunk\\source\\QTransformationMatrix3x3.cpp
	$(CXX) $(CFLAGS_DEBUGWIN32SHAREDRTSTATIC) $(INC_DEBUGWIN32SHAREDRTSTATIC) -c $(MAKEPATH)\\trunk\\source\\QTransformationMatrix3x3.cpp -o $(OBJDIR_DEBUGWIN32SHAREDRTSTATIC)$(MAKEPATH__)\\trunk\\source\\QTransformationMatrix3x3.o

$(OBJDIR_DEBUGWIN32SHAREDRTSTATIC)$(MAKEPATH__)\\trunk\\source\\QSpaceConversionMatrix.o: $(MAKEPATH)\\trunk\\source\\QSpaceConversionMatrix.cpp
	$(CXX) $(CFLAGS_DEBUGWIN32SHAREDRTSTATIC) $(INC_DEBUGWIN32SHAREDRTSTATIC) -c $(MAKEPATH)\\trunk\\source\\QSpaceConversionMatrix.cpp -o $(OBJDIR_DEBUGWIN32SHAREDRTSTATIC)$(MAKEPATH__)\\trunk\\source\\QSpaceConversionMatrix.o

$(OBJDIR_DEBUGWIN32SHAREDRTSTATIC)$(MAKEPATH__)\\trunk\\source\\QScalingMatrix3x3.o: $(MAKEPATH)\\trunk\\source\\QScalingMatrix3x3.cpp
	$(CXX) $(CFLAGS_DEBUGWIN32SHAREDRTSTATIC) $(INC_DEBUGWIN32SHAREDRTSTATIC) -c $(MAKEPATH)\\trunk\\source\\QScalingMatrix3x3.cpp -o $(OBJDIR_DEBUGWIN32SHAREDRTSTATIC)$(MAKEPATH__)\\trunk\\source\\QScalingMatrix3x3.o

$(OBJDIR_DEBUGWIN32SHAREDRTSTATIC)$(MAKEPATH__)\\trunk\\source\\QRotationMatrix3x3.o: $(MAKEPATH)\\trunk\\source\\QRotationMatrix3x3.cpp
	$(CXX) $(CFLAGS_DEBUGWIN32SHAREDRTSTATIC) $(INC_DEBUGWIN32SHAREDRTSTATIC) -c $(MAKEPATH)\\trunk\\source\\QRotationMatrix3x3.cpp -o $(OBJDIR_DEBUGWIN32SHAREDRTSTATIC)$(MAKEPATH__)\\trunk\\source\\QRotationMatrix3x3.o

$(OBJDIR_DEBUGWIN32SHAREDRTSTATIC)$(MAKEPATH__)\\trunk\\source\\QRay2D.o: $(MAKEPATH)\\trunk\\source\\QRay2D.cpp
	$(CXX) $(CFLAGS_DEBUGWIN32SHAREDRTSTATIC) $(INC_DEBUGWIN32SHAREDRTSTATIC) -c $(MAKEPATH)\\trunk\\source\\QRay2D.cpp -o $(OBJDIR_DEBUGWIN32SHAREDRTSTATIC)$(MAKEPATH__)\\trunk\\source\\QRay2D.o

$(OBJDIR_DEBUGWIN32SHAREDRTSTATIC)$(MAKEPATH__)\\trunk\\source\\QQuaternion.o: $(MAKEPATH)\\trunk\\source\\QQuaternion.cpp
	$(CXX) $(CFLAGS_DEBUGWIN32SHAREDRTSTATIC) $(INC_DEBUGWIN32SHAREDRTSTATIC) -c $(MAKEPATH)\\trunk\\source\\QQuaternion.cpp -o $(OBJDIR_DEBUGWIN32SHAREDRTSTATIC)$(MAKEPATH__)\\trunk\\source\\QQuaternion.o

$(OBJDIR_DEBUGWIN32SHAREDRTSTATIC)$(MAKEPATH__)\\trunk\\source\\QQuadrilateral.o: $(MAKEPATH)\\trunk\\source\\QQuadrilateral.cpp
	$(CXX) $(CFLAGS_DEBUGWIN32SHAREDRTSTATIC) $(INC_DEBUGWIN32SHAREDRTSTATIC) -c $(MAKEPATH)\\trunk\\source\\QQuadrilateral.cpp -o $(OBJDIR_DEBUGWIN32SHAREDRTSTATIC)$(MAKEPATH__)\\trunk\\source\\QQuadrilateral.o

$(OBJDIR_DEBUGWIN32SHAREDRTSTATIC)$(MAKEPATH__)\\trunk\\source\\QPlane.o: $(MAKEPATH)\\trunk\\source\\QPlane.cpp
	$(CXX) $(CFLAGS_DEBUGWIN32SHAREDRTSTATIC) $(INC_DEBUGWIN32SHAREDRTSTATIC) -c $(MAKEPATH)\\trunk\\source\\QPlane.cpp -o $(OBJDIR_DEBUGWIN32SHAREDRTSTATIC)$(MAKEPATH__)\\trunk\\source\\QPlane.o

$(OBJDIR_DEBUGWIN32SHAREDRTSTATIC)$(MAKEPATH__)\\trunk\\source\\QMatrix4x4.o: $(MAKEPATH)\\trunk\\source\\QMatrix4x4.cpp
	$(CXX) $(CFLAGS_DEBUGWIN32SHAREDRTSTATIC) $(INC_DEBUGWIN32SHAREDRTSTATIC) -c $(MAKEPATH)\\trunk\\source\\QMatrix4x4.cpp -o $(OBJDIR_DEBUGWIN32SHAREDRTSTATIC)$(MAKEPATH__)\\trunk\\source\\QMatrix4x4.o

$(OBJDIR_DEBUGWIN32SHAREDRTSTATIC)$(MAKEPATH__)\\trunk\\source\\QMatrix4x3.o: $(MAKEPATH)\\trunk\\source\\QMatrix4x3.cpp
	$(CXX) $(CFLAGS_DEBUGWIN32SHAREDRTSTATIC) $(INC_DEBUGWIN32SHAREDRTSTATIC) -c $(MAKEPATH)\\trunk\\source\\QMatrix4x3.cpp -o $(OBJDIR_DEBUGWIN32SHAREDRTSTATIC)$(MAKEPATH__)\\trunk\\source\\QMatrix4x3.o

$(OBJDIR_DEBUGWIN32SHAREDRTSTATIC)$(MAKEPATH__)\\trunk\\source\\QMatrix3x4.o: $(MAKEPATH)\\trunk\\source\\QMatrix3x4.cpp
	$(CXX) $(CFLAGS_DEBUGWIN32SHAREDRTSTATIC) $(INC_DEBUGWIN32SHAREDRTSTATIC) -c $(MAKEPATH)\\trunk\\source\\QMatrix3x4.cpp -o $(OBJDIR_DEBUGWIN32SHAREDRTSTATIC)$(MAKEPATH__)\\trunk\\source\\QMatrix3x4.o

$(OBJDIR_DEBUGWIN32SHAREDRTSTATIC)$(MAKEPATH__)\\trunk\\source\\QMatrix3x3.o: $(MAKEPATH)\\trunk\\source\\QMatrix3x3.cpp
	$(CXX) $(CFLAGS_DEBUGWIN32SHAREDRTSTATIC) $(INC_DEBUGWIN32SHAREDRTSTATIC) -c $(MAKEPATH)\\trunk\\source\\QMatrix3x3.cpp -o $(OBJDIR_DEBUGWIN32SHAREDRTSTATIC)$(MAKEPATH__)\\trunk\\source\\QMatrix3x3.o

$(OBJDIR_DEBUGWIN32SHAREDRTSTATIC)$(MAKEPATH__)\\trunk\\source\\QMatrix2x2.o: $(MAKEPATH)\\trunk\\source\\QMatrix2x2.cpp
	$(CXX) $(CFLAGS_DEBUGWIN32SHAREDRTSTATIC) $(INC_DEBUGWIN32SHAREDRTSTATIC) -c $(MAKEPATH)\\trunk\\source\\QMatrix2x2.cpp -o $(OBJDIR_DEBUGWIN32SHAREDRTSTATIC)$(MAKEPATH__)\\trunk\\source\\QMatrix2x2.o

$(OBJDIR_DEBUGWIN32SHAREDRTSTATIC)$(MAKEPATH__)\\trunk\\source\\QLineSegment2D.o: $(MAKEPATH)\\trunk\\source\\QLineSegment2D.cpp
	$(CXX) $(CFLAGS_DEBUGWIN32SHAREDRTSTATIC) $(INC_DEBUGWIN32SHAREDRTSTATIC) -c $(MAKEPATH)\\trunk\\source\\QLineSegment2D.cpp -o $(OBJDIR_DEBUGWIN32SHAREDRTSTATIC)$(MAKEPATH__)\\trunk\\source\\QLineSegment2D.o

$(OBJDIR_DEBUGWIN32SHAREDRTSTATIC)$(MAKEPATH__)\\trunk\\source\\QCircle.o: $(MAKEPATH)\\trunk\\source\\QCircle.cpp
	$(CXX) $(CFLAGS_DEBUGWIN32SHAREDRTSTATIC) $(INC_DEBUGWIN32SHAREDRTSTATIC) -c $(MAKEPATH)\\trunk\\source\\QCircle.cpp -o $(OBJDIR_DEBUGWIN32SHAREDRTSTATIC)$(MAKEPATH__)\\trunk\\source\\QCircle.o

$(OBJDIR_DEBUGWIN32SHAREDRTSTATIC)$(MAKEPATH__)\\trunk\\source\\QTriangle2D.o: $(MAKEPATH)\\trunk\\source\\QTriangle2D.cpp
	$(CXX) $(CFLAGS_DEBUGWIN32SHAREDRTSTATIC) $(INC_DEBUGWIN32SHAREDRTSTATIC) -c $(MAKEPATH)\\trunk\\source\\QTriangle2D.cpp -o $(OBJDIR_DEBUGWIN32SHAREDRTSTATIC)$(MAKEPATH__)\\trunk\\source\\QTriangle2D.o

$(OBJDIR_DEBUGWIN32SHAREDRTSTATIC)$(MAKEPATH__)\\trunk\\source\\ToolsExports.o: $(MAKEPATH)\\trunk\\source\\ToolsExports.cpp
	$(CXX) $(CFLAGS_DEBUGWIN32SHAREDRTSTATIC) $(INC_DEBUGWIN32SHAREDRTSTATIC) -c $(MAKEPATH)\\trunk\\source\\ToolsExports.cpp -o $(OBJDIR_DEBUGWIN32SHAREDRTSTATIC)$(MAKEPATH__)\\trunk\\source\\ToolsExports.o

$(OBJDIR_DEBUGWIN32SHAREDRTSTATIC)$(MAKEPATH__)\\trunk\\source\\QBaseDualQuaternion.o: $(MAKEPATH)\\trunk\\source\\QBaseDualQuaternion.cpp
	$(CXX) $(CFLAGS_DEBUGWIN32SHAREDRTSTATIC) $(INC_DEBUGWIN32SHAREDRTSTATIC) -c $(MAKEPATH)\\trunk\\source\\QBaseDualQuaternion.cpp -o $(OBJDIR_DEBUGWIN32SHAREDRTSTATIC)$(MAKEPATH__)\\trunk\\source\\QBaseDualQuaternion.o

$(OBJDIR_DEBUGWIN32SHAREDRTSTATIC)$(MAKEPATH__)\\trunk\\source\\QBaseMatrix2x2.o: $(MAKEPATH)\\trunk\\source\\QBaseMatrix2x2.cpp
	$(CXX) $(CFLAGS_DEBUGWIN32SHAREDRTSTATIC) $(INC_DEBUGWIN32SHAREDRTSTATIC) -c $(MAKEPATH)\\trunk\\source\\QBaseMatrix2x2.cpp -o $(OBJDIR_DEBUGWIN32SHAREDRTSTATIC)$(MAKEPATH__)\\trunk\\source\\QBaseMatrix2x2.o

$(OBJDIR_DEBUGWIN32SHAREDRTSTATIC)$(MAKEPATH__)\\trunk\\source\\QBaseMatrix3x3.o: $(MAKEPATH)\\trunk\\source\\QBaseMatrix3x3.cpp
	$(CXX) $(CFLAGS_DEBUGWIN32SHAREDRTSTATIC) $(INC_DEBUGWIN32SHAREDRTSTATIC) -c $(MAKEPATH)\\trunk\\source\\QBaseMatrix3x3.cpp -o $(OBJDIR_DEBUGWIN32SHAREDRTSTATIC)$(MAKEPATH__)\\trunk\\source\\QBaseMatrix3x3.o

$(OBJDIR_DEBUGWIN32SHAREDRTSTATIC)$(MAKEPATH__)\\trunk\\source\\QBaseMatrix3x4.o: $(MAKEPATH)\\trunk\\source\\QBaseMatrix3x4.cpp
	$(CXX) $(CFLAGS_DEBUGWIN32SHAREDRTSTATIC) $(INC_DEBUGWIN32SHAREDRTSTATIC) -c $(MAKEPATH)\\trunk\\source\\QBaseMatrix3x4.cpp -o $(OBJDIR_DEBUGWIN32SHAREDRTSTATIC)$(MAKEPATH__)\\trunk\\source\\QBaseMatrix3x4.o

$(OBJDIR_DEBUGWIN32SHAREDRTSTATIC)$(MAKEPATH__)\\trunk\\source\\QBaseMatrix4x3.o: $(MAKEPATH)\\trunk\\source\\QBaseMatrix4x3.cpp
	$(CXX) $(CFLAGS_DEBUGWIN32SHAREDRTSTATIC) $(INC_DEBUGWIN32SHAREDRTSTATIC) -c $(MAKEPATH)\\trunk\\source\\QBaseMatrix4x3.cpp -o $(OBJDIR_DEBUGWIN32SHAREDRTSTATIC)$(MAKEPATH__)\\trunk\\source\\QBaseMatrix4x3.o

$(OBJDIR_DEBUGWIN32SHAREDRTSTATIC)$(MAKEPATH__)\\trunk\\source\\QBaseMatrix4x4.o: $(MAKEPATH)\\trunk\\source\\QBaseMatrix4x4.cpp
	$(CXX) $(CFLAGS_DEBUGWIN32SHAREDRTSTATIC) $(INC_DEBUGWIN32SHAREDRTSTATIC) -c $(MAKEPATH)\\trunk\\source\\QBaseMatrix4x4.cpp -o $(OBJDIR_DEBUGWIN32SHAREDRTSTATIC)$(MAKEPATH__)\\trunk\\source\\QBaseMatrix4x4.o

$(OBJDIR_DEBUGWIN32SHAREDRTSTATIC)$(MAKEPATH__)\\trunk\\source\\QBasePlane.o: $(MAKEPATH)\\trunk\\source\\QBasePlane.cpp
	$(CXX) $(CFLAGS_DEBUGWIN32SHAREDRTSTATIC) $(INC_DEBUGWIN32SHAREDRTSTATIC) -c $(MAKEPATH)\\trunk\\source\\QBasePlane.cpp -o $(OBJDIR_DEBUGWIN32SHAREDRTSTATIC)$(MAKEPATH__)\\trunk\\source\\QBasePlane.o

$(OBJDIR_DEBUGWIN32SHAREDRTSTATIC)$(MAKEPATH__)\\trunk\\source\\QBaseQuadrilateral.o: $(MAKEPATH)\\trunk\\source\\QBaseQuadrilateral.cpp
	$(CXX) $(CFLAGS_DEBUGWIN32SHAREDRTSTATIC) $(INC_DEBUGWIN32SHAREDRTSTATIC) -c $(MAKEPATH)\\trunk\\source\\QBaseQuadrilateral.cpp -o $(OBJDIR_DEBUGWIN32SHAREDRTSTATIC)$(MAKEPATH__)\\trunk\\source\\QBaseQuadrilateral.o

$(OBJDIR_DEBUGWIN32SHAREDRTSTATIC)$(MAKEPATH__)\\trunk\\source\\QBaseQuaternion.o: $(MAKEPATH)\\trunk\\source\\QBaseQuaternion.cpp
	$(CXX) $(CFLAGS_DEBUGWIN32SHAREDRTSTATIC) $(INC_DEBUGWIN32SHAREDRTSTATIC) -c $(MAKEPATH)\\trunk\\source\\QBaseQuaternion.cpp -o $(OBJDIR_DEBUGWIN32SHAREDRTSTATIC)$(MAKEPATH__)\\trunk\\source\\QBaseQuaternion.o

$(OBJDIR_DEBUGWIN32SHAREDRTSTATIC)$(MAKEPATH__)\\trunk\\source\\QBaseVector2.o: $(MAKEPATH)\\trunk\\source\\QBaseVector2.cpp
	$(CXX) $(CFLAGS_DEBUGWIN32SHAREDRTSTATIC) $(INC_DEBUGWIN32SHAREDRTSTATIC) -c $(MAKEPATH)\\trunk\\source\\QBaseVector2.cpp -o $(OBJDIR_DEBUGWIN32SHAREDRTSTATIC)$(MAKEPATH__)\\trunk\\source\\QBaseVector2.o

$(OBJDIR_DEBUGWIN32SHAREDRTSTATIC)$(MAKEPATH__)\\trunk\\source\\QBaseVector3.o: $(MAKEPATH)\\trunk\\source\\QBaseVector3.cpp
	$(CXX) $(CFLAGS_DEBUGWIN32SHAREDRTSTATIC) $(INC_DEBUGWIN32SHAREDRTSTATIC) -c $(MAKEPATH)\\trunk\\source\\QBaseVector3.cpp -o $(OBJDIR_DEBUGWIN32SHAREDRTSTATIC)$(MAKEPATH__)\\trunk\\source\\QBaseVector3.o

$(OBJDIR_DEBUGWIN32SHAREDRTSTATIC)$(MAKEPATH__)\\trunk\\source\\QBaseVector4.o: $(MAKEPATH)\\trunk\\source\\QBaseVector4.cpp
	$(CXX) $(CFLAGS_DEBUGWIN32SHAREDRTSTATIC) $(INC_DEBUGWIN32SHAREDRTSTATIC) -c $(MAKEPATH)\\trunk\\source\\QBaseVector4.cpp -o $(OBJDIR_DEBUGWIN32SHAREDRTSTATIC)$(MAKEPATH__)\\trunk\\source\\QBaseVector4.o

$(OBJDIR_DEBUGWIN32SHAREDRTSTATIC)$(MAKEPATH__)\\trunk\\source\\SQPoint.o: $(MAKEPATH)\\trunk\\source\\SQPoint.cpp
	$(CXX) $(CFLAGS_DEBUGWIN32SHAREDRTSTATIC) $(INC_DEBUGWIN32SHAREDRTSTATIC) -c $(MAKEPATH)\\trunk\\source\\SQPoint.cpp -o $(OBJDIR_DEBUGWIN32SHAREDRTSTATIC)$(MAKEPATH__)\\trunk\\source\\SQPoint.o

	
clean_debugwin32sharedrtstatic: 


#----------------------------------------------------------------------------------------------------------------------------------------------------------------------------#
#	DebugWin32SharedrtDynamic   ~~~   DebugWin32SharedrtDynamic   ~~~   DebugWin32SharedrtDynamic   ~~~   DebugWin32SharedrtDynamic   ~~~   DebugWin32SharedrtDynamic   ~~~  #  
#----------------------------------------------------------------------------------------------------------------------------------------------------------------------------#
	
before_debugwin32sharedrtdynamic: 
	cmd /c if not exist $(MAKEPATH)\\trunk\\bin\\CodeBlocks10\\DebugWin32SharedrtDynamic md $(MAKEPATH)\\trunk\\bin\\CodeBlocks10\\DebugWin32SharedrtDynamic
	cmd /c if not exist $(OBJDIR_DEBUGWIN32SHAREDRTDYNAMIC)$(MAKEPATH__)\\trunk\\source md $(OBJDIR_DEBUGWIN32SHAREDRTDYNAMIC)$(MAKEPATH__)\\trunk\\source

after_debugwin32sharedrtdynamic: 

debugwin32sharedrtdynamic: before_debugwin32sharedrtdynamic out_debugwin32sharedrtdynamic after_debugwin32sharedrtdynamic

out_debugwin32sharedrtdynamic: $(OBJ_DEBUGWIN32SHAREDRTDYNAMIC) $(DEP_DEBUGWIN32SHAREDRTDYNAMIC)
	$(LD) -shared $(LDFLAGS_DEBUGWIN32SHAREDRTDYNAMIC) $(LIBDIR_DEBUGWIN32SHAREDRTDYNAMIC) $(OBJ_DEBUGWIN32SHAREDRTDYNAMIC) $(LIB_DEBUGWIN32SHAREDRTDYNAMIC) -o $(OUT_DEBUGWIN32SHAREDRTDYNAMIC)

$(OBJDIR_DEBUGWIN32SHAREDRTDYNAMIC)$(MAKEPATH__)\\trunk\\source\\QDualQuaternion.o: $(MAKEPATH)\\trunk\\source\\QDualQuaternion.cpp
	$(CXX) $(CFLAGS_DEBUGWIN32SHAREDRTDYNAMIC) $(INC_DEBUGWIN32SHAREDRTDYNAMIC) -c $(MAKEPATH)\\trunk\\source\\QDualQuaternion.cpp -o $(OBJDIR_DEBUGWIN32SHAREDRTDYNAMIC)$(MAKEPATH__)\\trunk\\source\\QDualQuaternion.o

$(OBJDIR_DEBUGWIN32SHAREDRTDYNAMIC)$(MAKEPATH__)\\trunk\\source\\EQSpaceRelation.o: $(MAKEPATH)\\trunk\\source\\EQSpaceRelation.cpp
	$(CXX) $(CFLAGS_DEBUGWIN32SHAREDRTDYNAMIC) $(INC_DEBUGWIN32SHAREDRTDYNAMIC) -c $(MAKEPATH)\\trunk\\source\\EQSpaceRelation.cpp -o $(OBJDIR_DEBUGWIN32SHAREDRTDYNAMIC)$(MAKEPATH__)\\trunk\\source\\EQSpaceRelation.o

$(OBJDIR_DEBUGWIN32SHAREDRTDYNAMIC)$(MAKEPATH__)\\trunk\\source\\EQIntersections.o: $(MAKEPATH)\\trunk\\source\\EQIntersections.cpp
	$(CXX) $(CFLAGS_DEBUGWIN32SHAREDRTDYNAMIC) $(INC_DEBUGWIN32SHAREDRTDYNAMIC) -c $(MAKEPATH)\\trunk\\source\\EQIntersections.cpp -o $(OBJDIR_DEBUGWIN32SHAREDRTDYNAMIC)$(MAKEPATH__)\\trunk\\source\\EQIntersections.o

$(OBJDIR_DEBUGWIN32SHAREDRTDYNAMIC)$(MAKEPATH__)\\trunk\\source\\SQAngle.o: $(MAKEPATH)\\trunk\\source\\SQAngle.cpp
	$(CXX) $(CFLAGS_DEBUGWIN32SHAREDRTDYNAMIC) $(INC_DEBUGWIN32SHAREDRTDYNAMIC) -c $(MAKEPATH)\\trunk\\source\\SQAngle.cpp -o $(OBJDIR_DEBUGWIN32SHAREDRTDYNAMIC)$(MAKEPATH__)\\trunk\\source\\SQAngle.o

$(OBJDIR_DEBUGWIN32SHAREDRTDYNAMIC)$(MAKEPATH__)\\trunk\\source\\QVector4.o: $(MAKEPATH)\\trunk\\source\\QVector4.cpp
	$(CXX) $(CFLAGS_DEBUGWIN32SHAREDRTDYNAMIC) $(INC_DEBUGWIN32SHAREDRTDYNAMIC) -c $(MAKEPATH)\\trunk\\source\\QVector4.cpp -o $(OBJDIR_DEBUGWIN32SHAREDRTDYNAMIC)$(MAKEPATH__)\\trunk\\source\\QVector4.o

$(OBJDIR_DEBUGWIN32SHAREDRTDYNAMIC)$(MAKEPATH__)\\trunk\\source\\QVector3.o: $(MAKEPATH)\\trunk\\source\\QVector3.cpp
	$(CXX) $(CFLAGS_DEBUGWIN32SHAREDRTDYNAMIC) $(INC_DEBUGWIN32SHAREDRTDYNAMIC) -c $(MAKEPATH)\\trunk\\source\\QVector3.cpp -o $(OBJDIR_DEBUGWIN32SHAREDRTDYNAMIC)$(MAKEPATH__)\\trunk\\source\\QVector3.o

$(OBJDIR_DEBUGWIN32SHAREDRTDYNAMIC)$(MAKEPATH__)\\trunk\\source\\QVector2.o: $(MAKEPATH)\\trunk\\source\\QVector2.cpp
	$(CXX) $(CFLAGS_DEBUGWIN32SHAREDRTDYNAMIC) $(INC_DEBUGWIN32SHAREDRTDYNAMIC) -c $(MAKEPATH)\\trunk\\source\\QVector2.cpp -o $(OBJDIR_DEBUGWIN32SHAREDRTDYNAMIC)$(MAKEPATH__)\\trunk\\source\\QVector2.o

$(OBJDIR_DEBUGWIN32SHAREDRTDYNAMIC)$(MAKEPATH__)\\trunk\\source\\QTransformationMatrix3x3.o: $(MAKEPATH)\\trunk\\source\\QTransformationMatrix3x3.cpp
	$(CXX) $(CFLAGS_DEBUGWIN32SHAREDRTDYNAMIC) $(INC_DEBUGWIN32SHAREDRTDYNAMIC) -c $(MAKEPATH)\\trunk\\source\\QTransformationMatrix3x3.cpp -o $(OBJDIR_DEBUGWIN32SHAREDRTDYNAMIC)$(MAKEPATH__)\\trunk\\source\\QTransformationMatrix3x3.o

$(OBJDIR_DEBUGWIN32SHAREDRTDYNAMIC)$(MAKEPATH__)\\trunk\\source\\QSpaceConversionMatrix.o: $(MAKEPATH)\\trunk\\source\\QSpaceConversionMatrix.cpp
	$(CXX) $(CFLAGS_DEBUGWIN32SHAREDRTDYNAMIC) $(INC_DEBUGWIN32SHAREDRTDYNAMIC) -c $(MAKEPATH)\\trunk\\source\\QSpaceConversionMatrix.cpp -o $(OBJDIR_DEBUGWIN32SHAREDRTDYNAMIC)$(MAKEPATH__)\\trunk\\source\\QSpaceConversionMatrix.o

$(OBJDIR_DEBUGWIN32SHAREDRTDYNAMIC)$(MAKEPATH__)\\trunk\\source\\QScalingMatrix3x3.o: $(MAKEPATH)\\trunk\\source\\QScalingMatrix3x3.cpp
	$(CXX) $(CFLAGS_DEBUGWIN32SHAREDRTDYNAMIC) $(INC_DEBUGWIN32SHAREDRTDYNAMIC) -c $(MAKEPATH)\\trunk\\source\\QScalingMatrix3x3.cpp -o $(OBJDIR_DEBUGWIN32SHAREDRTDYNAMIC)$(MAKEPATH__)\\trunk\\source\\QScalingMatrix3x3.o

$(OBJDIR_DEBUGWIN32SHAREDRTDYNAMIC)$(MAKEPATH__)\\trunk\\source\\QRotationMatrix3x3.o: $(MAKEPATH)\\trunk\\source\\QRotationMatrix3x3.cpp
	$(CXX) $(CFLAGS_DEBUGWIN32SHAREDRTDYNAMIC) $(INC_DEBUGWIN32SHAREDRTDYNAMIC) -c $(MAKEPATH)\\trunk\\source\\QRotationMatrix3x3.cpp -o $(OBJDIR_DEBUGWIN32SHAREDRTDYNAMIC)$(MAKEPATH__)\\trunk\\source\\QRotationMatrix3x3.o

$(OBJDIR_DEBUGWIN32SHAREDRTDYNAMIC)$(MAKEPATH__)\\trunk\\source\\QRay2D.o: $(MAKEPATH)\\trunk\\source\\QRay2D.cpp
	$(CXX) $(CFLAGS_DEBUGWIN32SHAREDRTDYNAMIC) $(INC_DEBUGWIN32SHAREDRTDYNAMIC) -c $(MAKEPATH)\\trunk\\source\\QRay2D.cpp -o $(OBJDIR_DEBUGWIN32SHAREDRTDYNAMIC)$(MAKEPATH__)\\trunk\\source\\QRay2D.o

$(OBJDIR_DEBUGWIN32SHAREDRTDYNAMIC)$(MAKEPATH__)\\trunk\\source\\QQuaternion.o: $(MAKEPATH)\\trunk\\source\\QQuaternion.cpp
	$(CXX) $(CFLAGS_DEBUGWIN32SHAREDRTDYNAMIC) $(INC_DEBUGWIN32SHAREDRTDYNAMIC) -c $(MAKEPATH)\\trunk\\source\\QQuaternion.cpp -o $(OBJDIR_DEBUGWIN32SHAREDRTDYNAMIC)$(MAKEPATH__)\\trunk\\source\\QQuaternion.o

$(OBJDIR_DEBUGWIN32SHAREDRTDYNAMIC)$(MAKEPATH__)\\trunk\\source\\QQuadrilateral.o: $(MAKEPATH)\\trunk\\source\\QQuadrilateral.cpp
	$(CXX) $(CFLAGS_DEBUGWIN32SHAREDRTDYNAMIC) $(INC_DEBUGWIN32SHAREDRTDYNAMIC) -c $(MAKEPATH)\\trunk\\source\\QQuadrilateral.cpp -o $(OBJDIR_DEBUGWIN32SHAREDRTDYNAMIC)$(MAKEPATH__)\\trunk\\source\\QQuadrilateral.o

$(OBJDIR_DEBUGWIN32SHAREDRTDYNAMIC)$(MAKEPATH__)\\trunk\\source\\QPlane.o: $(MAKEPATH)\\trunk\\source\\QPlane.cpp
	$(CXX) $(CFLAGS_DEBUGWIN32SHAREDRTDYNAMIC) $(INC_DEBUGWIN32SHAREDRTDYNAMIC) -c $(MAKEPATH)\\trunk\\source\\QPlane.cpp -o $(OBJDIR_DEBUGWIN32SHAREDRTDYNAMIC)$(MAKEPATH__)\\trunk\\source\\QPlane.o

$(OBJDIR_DEBUGWIN32SHAREDRTDYNAMIC)$(MAKEPATH__)\\trunk\\source\\QMatrix4x4.o: $(MAKEPATH)\\trunk\\source\\QMatrix4x4.cpp
	$(CXX) $(CFLAGS_DEBUGWIN32SHAREDRTDYNAMIC) $(INC_DEBUGWIN32SHAREDRTDYNAMIC) -c $(MAKEPATH)\\trunk\\source\\QMatrix4x4.cpp -o $(OBJDIR_DEBUGWIN32SHAREDRTDYNAMIC)$(MAKEPATH__)\\trunk\\source\\QMatrix4x4.o

$(OBJDIR_DEBUGWIN32SHAREDRTDYNAMIC)$(MAKEPATH__)\\trunk\\source\\QMatrix4x3.o: $(MAKEPATH)\\trunk\\source\\QMatrix4x3.cpp
	$(CXX) $(CFLAGS_DEBUGWIN32SHAREDRTDYNAMIC) $(INC_DEBUGWIN32SHAREDRTDYNAMIC) -c $(MAKEPATH)\\trunk\\source\\QMatrix4x3.cpp -o $(OBJDIR_DEBUGWIN32SHAREDRTDYNAMIC)$(MAKEPATH__)\\trunk\\source\\QMatrix4x3.o

$(OBJDIR_DEBUGWIN32SHAREDRTDYNAMIC)$(MAKEPATH__)\\trunk\\source\\QMatrix3x4.o: $(MAKEPATH)\\trunk\\source\\QMatrix3x4.cpp
	$(CXX) $(CFLAGS_DEBUGWIN32SHAREDRTDYNAMIC) $(INC_DEBUGWIN32SHAREDRTDYNAMIC) -c $(MAKEPATH)\\trunk\\source\\QMatrix3x4.cpp -o $(OBJDIR_DEBUGWIN32SHAREDRTDYNAMIC)$(MAKEPATH__)\\trunk\\source\\QMatrix3x4.o

$(OBJDIR_DEBUGWIN32SHAREDRTDYNAMIC)$(MAKEPATH__)\\trunk\\source\\QMatrix3x3.o: $(MAKEPATH)\\trunk\\source\\QMatrix3x3.cpp
	$(CXX) $(CFLAGS_DEBUGWIN32SHAREDRTDYNAMIC) $(INC_DEBUGWIN32SHAREDRTDYNAMIC) -c $(MAKEPATH)\\trunk\\source\\QMatrix3x3.cpp -o $(OBJDIR_DEBUGWIN32SHAREDRTDYNAMIC)$(MAKEPATH__)\\trunk\\source\\QMatrix3x3.o

$(OBJDIR_DEBUGWIN32SHAREDRTDYNAMIC)$(MAKEPATH__)\\trunk\\source\\QMatrix2x2.o: $(MAKEPATH)\\trunk\\source\\QMatrix2x2.cpp
	$(CXX) $(CFLAGS_DEBUGWIN32SHAREDRTDYNAMIC) $(INC_DEBUGWIN32SHAREDRTDYNAMIC) -c $(MAKEPATH)\\trunk\\source\\QMatrix2x2.cpp -o $(OBJDIR_DEBUGWIN32SHAREDRTDYNAMIC)$(MAKEPATH__)\\trunk\\source\\QMatrix2x2.o

$(OBJDIR_DEBUGWIN32SHAREDRTDYNAMIC)$(MAKEPATH__)\\trunk\\source\\QLineSegment2D.o: $(MAKEPATH)\\trunk\\source\\QLineSegment2D.cpp
	$(CXX) $(CFLAGS_DEBUGWIN32SHAREDRTDYNAMIC) $(INC_DEBUGWIN32SHAREDRTDYNAMIC) -c $(MAKEPATH)\\trunk\\source\\QLineSegment2D.cpp -o $(OBJDIR_DEBUGWIN32SHAREDRTDYNAMIC)$(MAKEPATH__)\\trunk\\source\\QLineSegment2D.o

$(OBJDIR_DEBUGWIN32SHAREDRTDYNAMIC)$(MAKEPATH__)\\trunk\\source\\QCircle.o: $(MAKEPATH)\\trunk\\source\\QCircle.cpp
	$(CXX) $(CFLAGS_DEBUGWIN32SHAREDRTDYNAMIC) $(INC_DEBUGWIN32SHAREDRTDYNAMIC) -c $(MAKEPATH)\\trunk\\source\\QCircle.cpp -o $(OBJDIR_DEBUGWIN32SHAREDRTDYNAMIC)$(MAKEPATH__)\\trunk\\source\\QCircle.o

$(OBJDIR_DEBUGWIN32SHAREDRTDYNAMIC)$(MAKEPATH__)\\trunk\\source\\QTriangle2D.o: $(MAKEPATH)\\trunk\\source\\QTriangle2D.cpp
	$(CXX) $(CFLAGS_DEBUGWIN32SHAREDRTDYNAMIC) $(INC_DEBUGWIN32SHAREDRTDYNAMIC) -c $(MAKEPATH)\\trunk\\source\\QTriangle2D.cpp -o $(OBJDIR_DEBUGWIN32SHAREDRTDYNAMIC)$(MAKEPATH__)\\trunk\\source\\QTriangle2D.o

$(OBJDIR_DEBUGWIN32SHAREDRTDYNAMIC)$(MAKEPATH__)\\trunk\\source\\ToolsExports.o: $(MAKEPATH)\\trunk\\source\\ToolsExports.cpp
	$(CXX) $(CFLAGS_DEBUGWIN32SHAREDRTDYNAMIC) $(INC_DEBUGWIN32SHAREDRTDYNAMIC) -c $(MAKEPATH)\\trunk\\source\\ToolsExports.cpp -o $(OBJDIR_DEBUGWIN32SHAREDRTDYNAMIC)$(MAKEPATH__)\\trunk\\source\\ToolsExports.o

$(OBJDIR_DEBUGWIN32SHAREDRTDYNAMIC)$(MAKEPATH__)\\trunk\\source\\QBaseDualQuaternion.o: $(MAKEPATH)\\trunk\\source\\QBaseDualQuaternion.cpp
	$(CXX) $(CFLAGS_DEBUGWIN32SHAREDRTDYNAMIC) $(INC_DEBUGWIN32SHAREDRTDYNAMIC) -c $(MAKEPATH)\\trunk\\source\\QBaseDualQuaternion.cpp -o $(OBJDIR_DEBUGWIN32SHAREDRTDYNAMIC)$(MAKEPATH__)\\trunk\\source\\QBaseDualQuaternion.o

$(OBJDIR_DEBUGWIN32SHAREDRTDYNAMIC)$(MAKEPATH__)\\trunk\\source\\QBaseMatrix2x2.o: $(MAKEPATH)\\trunk\\source\\QBaseMatrix2x2.cpp
	$(CXX) $(CFLAGS_DEBUGWIN32SHAREDRTDYNAMIC) $(INC_DEBUGWIN32SHAREDRTDYNAMIC) -c $(MAKEPATH)\\trunk\\source\\QBaseMatrix2x2.cpp -o $(OBJDIR_DEBUGWIN32SHAREDRTDYNAMIC)$(MAKEPATH__)\\trunk\\source\\QBaseMatrix2x2.o

$(OBJDIR_DEBUGWIN32SHAREDRTDYNAMIC)$(MAKEPATH__)\\trunk\\source\\QBaseMatrix3x3.o: $(MAKEPATH)\\trunk\\source\\QBaseMatrix3x3.cpp
	$(CXX) $(CFLAGS_DEBUGWIN32SHAREDRTDYNAMIC) $(INC_DEBUGWIN32SHAREDRTDYNAMIC) -c $(MAKEPATH)\\trunk\\source\\QBaseMatrix3x3.cpp -o $(OBJDIR_DEBUGWIN32SHAREDRTDYNAMIC)$(MAKEPATH__)\\trunk\\source\\QBaseMatrix3x3.o

$(OBJDIR_DEBUGWIN32SHAREDRTDYNAMIC)$(MAKEPATH__)\\trunk\\source\\QBaseMatrix3x4.o: $(MAKEPATH)\\trunk\\source\\QBaseMatrix3x4.cpp
	$(CXX) $(CFLAGS_DEBUGWIN32SHAREDRTDYNAMIC) $(INC_DEBUGWIN32SHAREDRTDYNAMIC) -c $(MAKEPATH)\\trunk\\source\\QBaseMatrix3x4.cpp -o $(OBJDIR_DEBUGWIN32SHAREDRTDYNAMIC)$(MAKEPATH__)\\trunk\\source\\QBaseMatrix3x4.o

$(OBJDIR_DEBUGWIN32SHAREDRTDYNAMIC)$(MAKEPATH__)\\trunk\\source\\QBaseMatrix4x3.o: $(MAKEPATH)\\trunk\\source\\QBaseMatrix4x3.cpp
	$(CXX) $(CFLAGS_DEBUGWIN32SHAREDRTDYNAMIC) $(INC_DEBUGWIN32SHAREDRTDYNAMIC) -c $(MAKEPATH)\\trunk\\source\\QBaseMatrix4x3.cpp -o $(OBJDIR_DEBUGWIN32SHAREDRTDYNAMIC)$(MAKEPATH__)\\trunk\\source\\QBaseMatrix4x3.o

$(OBJDIR_DEBUGWIN32SHAREDRTDYNAMIC)$(MAKEPATH__)\\trunk\\source\\QBaseMatrix4x4.o: $(MAKEPATH)\\trunk\\source\\QBaseMatrix4x4.cpp
	$(CXX) $(CFLAGS_DEBUGWIN32SHAREDRTDYNAMIC) $(INC_DEBUGWIN32SHAREDRTDYNAMIC) -c $(MAKEPATH)\\trunk\\source\\QBaseMatrix4x4.cpp -o $(OBJDIR_DEBUGWIN32SHAREDRTDYNAMIC)$(MAKEPATH__)\\trunk\\source\\QBaseMatrix4x4.o

$(OBJDIR_DEBUGWIN32SHAREDRTDYNAMIC)$(MAKEPATH__)\\trunk\\source\\QBasePlane.o: $(MAKEPATH)\\trunk\\source\\QBasePlane.cpp
	$(CXX) $(CFLAGS_DEBUGWIN32SHAREDRTDYNAMIC) $(INC_DEBUGWIN32SHAREDRTDYNAMIC) -c $(MAKEPATH)\\trunk\\source\\QBasePlane.cpp -o $(OBJDIR_DEBUGWIN32SHAREDRTDYNAMIC)$(MAKEPATH__)\\trunk\\source\\QBasePlane.o

$(OBJDIR_DEBUGWIN32SHAREDRTDYNAMIC)$(MAKEPATH__)\\trunk\\source\\QBaseQuadrilateral.o: $(MAKEPATH)\\trunk\\source\\QBaseQuadrilateral.cpp
	$(CXX) $(CFLAGS_DEBUGWIN32SHAREDRTDYNAMIC) $(INC_DEBUGWIN32SHAREDRTDYNAMIC) -c $(MAKEPATH)\\trunk\\source\\QBaseQuadrilateral.cpp -o $(OBJDIR_DEBUGWIN32SHAREDRTDYNAMIC)$(MAKEPATH__)\\trunk\\source\\QBaseQuadrilateral.o

$(OBJDIR_DEBUGWIN32SHAREDRTDYNAMIC)$(MAKEPATH__)\\trunk\\source\\QBaseQuaternion.o: $(MAKEPATH)\\trunk\\source\\QBaseQuaternion.cpp
	$(CXX) $(CFLAGS_DEBUGWIN32SHAREDRTDYNAMIC) $(INC_DEBUGWIN32SHAREDRTDYNAMIC) -c $(MAKEPATH)\\trunk\\source\\QBaseQuaternion.cpp -o $(OBJDIR_DEBUGWIN32SHAREDRTDYNAMIC)$(MAKEPATH__)\\trunk\\source\\QBaseQuaternion.o

$(OBJDIR_DEBUGWIN32SHAREDRTDYNAMIC)$(MAKEPATH__)\\trunk\\source\\QBaseVector2.o: $(MAKEPATH)\\trunk\\source\\QBaseVector2.cpp
	$(CXX) $(CFLAGS_DEBUGWIN32SHAREDRTDYNAMIC) $(INC_DEBUGWIN32SHAREDRTDYNAMIC) -c $(MAKEPATH)\\trunk\\source\\QBaseVector2.cpp -o $(OBJDIR_DEBUGWIN32SHAREDRTDYNAMIC)$(MAKEPATH__)\\trunk\\source\\QBaseVector2.o

$(OBJDIR_DEBUGWIN32SHAREDRTDYNAMIC)$(MAKEPATH__)\\trunk\\source\\QBaseVector3.o: $(MAKEPATH)\\trunk\\source\\QBaseVector3.cpp
	$(CXX) $(CFLAGS_DEBUGWIN32SHAREDRTDYNAMIC) $(INC_DEBUGWIN32SHAREDRTDYNAMIC) -c $(MAKEPATH)\\trunk\\source\\QBaseVector3.cpp -o $(OBJDIR_DEBUGWIN32SHAREDRTDYNAMIC)$(MAKEPATH__)\\trunk\\source\\QBaseVector3.o

$(OBJDIR_DEBUGWIN32SHAREDRTDYNAMIC)$(MAKEPATH__)\\trunk\\source\\QBaseVector4.o: $(MAKEPATH)\\trunk\\source\\QBaseVector4.cpp
	$(CXX) $(CFLAGS_DEBUGWIN32SHAREDRTDYNAMIC) $(INC_DEBUGWIN32SHAREDRTDYNAMIC) -c $(MAKEPATH)\\trunk\\source\\QBaseVector4.cpp -o $(OBJDIR_DEBUGWIN32SHAREDRTDYNAMIC)$(MAKEPATH__)\\trunk\\source\\QBaseVector4.o

$(OBJDIR_DEBUGWIN32SHAREDRTDYNAMIC)$(MAKEPATH__)\\trunk\\source\\SQPoint.o: $(MAKEPATH)\\trunk\\source\\SQPoint.cpp
	$(CXX) $(CFLAGS_DEBUGWIN32SHAREDRTDYNAMIC) $(INC_DEBUGWIN32SHAREDRTDYNAMIC) -c $(MAKEPATH)\\trunk\\source\\SQPoint.cpp -o $(OBJDIR_DEBUGWIN32SHAREDRTDYNAMIC)$(MAKEPATH__)\\trunk\\source\\SQPoint.o

	
clean_debugwin32sharedrtdynamic: 

	
	
.PHONY: before_debugwin32sharedrtstatic after_debugwin32sharedrtstatic clean_debugwin32sharedrtstatic before_debugwin32sharedrtdynamic after_debugwin32sharedrtdynamic clean_debugwin32sharedrtdynamic

