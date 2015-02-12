#------------------------------------------------------------------------------------------------------------#
#------------------------------------Core------------------------------------#
#------------------------------------------------------------------------------------------------------------#

#------------------------------------------------------------
#----------------------- GLOBAL ---------------------
#------------------------------------------------------------
INCLUDES_GLOBAL = -I$(EXECUTION_PATH).
LIBRARYDIRS_GLOBAL = -L$(EXECUTION_PATH).
LIBRARIES_GLOBAL =
COMPILEROPTIONS_GLOBAL = -Wno-comment
LINKEROPTIONS_GLOBAL = 
DEFINITIONS_GLOBAL =

#------------------------------------------------------------
#------------- DebugLinux32SharedrtDynamic --------------
#------------------------------------------------------------
CXX_DEBUGLINUX32SHAREDRTDYNAMIC = g++
AR_DEBUGLINUX32SHAREDRTDYNAMIC = ar
LD_DEBUGLINUX32SHAREDRTDYNAMIC = g++
AS_DEBUGLINUX32SHAREDRTDYNAMIC = as
INCLUDES_DEBUGLINUX32SHAREDRTDYNAMIC = $(INCLUDES_GLOBAL) -I$(EXECUTION_PATH)../../../headers -I$(EXECUTION_PATH)../../../3rdparty/ICU/include
LIBRARYDIRS_DEBUGLINUX32SHAREDRTDYNAMIC = $(LIBRARYDIRS_GLOBAL) -L$(EXECUTION_PATH)../../../bin/GCC/DebugLinux32SharedrtDynamic -L$(EXECUTION_PATH)../../../3rdparty/Boost/bin/Linux32/DebugSharedrtStatic
LIBRARIES_DEBUGLINUX32SHAREDRTDYNAMIC = $(LIBRARIES_GLOBAL) -licudata -licuuc -licui18n -lQuimeraEngineSystem -lQuimeraEngineTools -lQuimeraEngineCommon
COMPILEROPTIONS_DEBUGLINUX32SHAREDRTDYNAMIC = $(COMPILEROPTIONS_GLOBAL) -g -Wall -Wno-comment -m32 -isystem $(EXECUTION_PATH)../../../3rdparty/Boost/include -fno-rtti -fno-exceptions
LINKEROPTIONS_DEBUGLINUX32SHAREDRTDYNAMIC = $(LINKEROPTIONS_GLOBAL) -m32
DEFINITIONS_DEBUGLINUX32SHAREDRTDYNAMIC = $(DEFINITIONS_GLOBAL) -DQE_PREPROCESSOR_EXPORTLIB_CORE -DQE_PREPROCESSOR_IMPORTLIB_SYSTEM -DQE_PREPROCESSOR_IMPORTLIB_TOOLS -DQE_PREPROCESSOR_IMPORTLIB_COMMON -DBOOST_NO_RTTI -DBOOST_NO_TYPEID -DBOOST_NO_EXCEPTIONS
OUTPUT_DEBUGLINUX32SHAREDRTDYNAMIC = $(EXECUTION_PATH)../../../bin/GCC/DebugLinux32SharedrtDynamic/libQuimeraEngineCore.so
INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTDYNAMIC = $(EXECUTION_PATH)../../../garbage/GCC/DebugLinux32SharedrtDynamic/
OBJECTS_DEBUGLINUX32SHAREDRTDYNAMIC = $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTDYNAMIC)__.__.__.source.Prueba.o

prebuildDebugLinux32SharedrtDynamic:
	if ! (test -d $(EXECUTION_PATH)../../../bin/GCC/DebugLinux32SharedrtDynamic) then mkdir -p "$(EXECUTION_PATH)../../../bin/GCC/DebugLinux32SharedrtDynamic"; fi
	if ! (test -d $(EXECUTION_PATH)../../../garbage/GCC/DebugLinux32SharedrtDynamic) then mkdir -p "$(EXECUTION_PATH)../../../garbage/GCC/DebugLinux32SharedrtDynamic"; fi


DebugLinux32SharedrtDynamic: $(OBJECTS_DEBUGLINUX32SHAREDRTDYNAMIC)
	$(LD_DEBUGLINUX32SHAREDRTDYNAMIC) -shared $(LINKEROPTIONS_DEBUGLINUX32SHAREDRTDYNAMIC) $(LIBRARYDIRS_DEBUGLINUX32SHAREDRTDYNAMIC) $(OBJECTS_DEBUGLINUX32SHAREDRTDYNAMIC) $(LIBRARIES_DEBUGLINUX32SHAREDRTDYNAMIC) -o $(OUTPUT_DEBUGLINUX32SHAREDRTDYNAMIC)

$(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTDYNAMIC)__.__.__.source.Prueba.o: $(EXECUTION_PATH)../../../source/Prueba.cpp
	$(CXX_DEBUGLINUX32SHAREDRTDYNAMIC) $(COMPILEROPTIONS_DEBUGLINUX32SHAREDRTDYNAMIC) $(DEFINITIONS_DEBUGLINUX32SHAREDRTDYNAMIC) $(INCLUDES_DEBUGLINUX32SHAREDRTDYNAMIC) -c $(EXECUTION_PATH)../../../source/Prueba.cpp -o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTDYNAMIC)__.__.__.source.Prueba.o

postbuildDebugLinux32SharedrtDynamic:


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
INCLUDES_DEBUGLINUX32SHAREDRTSTATIC = $(INCLUDES_GLOBAL) -I$(EXECUTION_PATH)../../../headers -I$(EXECUTION_PATH)../../../3rdparty/ICU/include
LIBRARYDIRS_DEBUGLINUX32SHAREDRTSTATIC = $(LIBRARYDIRS_GLOBAL)
LIBRARIES_DEBUGLINUX32SHAREDRTSTATIC = $(LIBRARIES_GLOBAL)
COMPILEROPTIONS_DEBUGLINUX32SHAREDRTSTATIC = $(COMPILEROPTIONS_GLOBAL) -g -Wall -Wno-comment -m32 -isystem $(EXECUTION_PATH)../../../3rdparty/Boost/include -fno-rtti -fno-exceptions
LINKEROPTIONS_DEBUGLINUX32SHAREDRTSTATIC = $(LINKEROPTIONS_GLOBAL) -m32
DEFINITIONS_DEBUGLINUX32SHAREDRTSTATIC = $(DEFINITIONS_GLOBAL) -DBOOST_NO_RTTI -DBOOST_NO_TYPEID -DBOOST_NO_EXCEPTIONS
OUTPUT_DEBUGLINUX32SHAREDRTSTATIC = $(EXECUTION_PATH)../../../bin/GCC/DebugLinux32SharedrtStatic/libQuimeraEngineCore.a
INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTSTATIC = $(EXECUTION_PATH)../../../garbage/GCC/DebugLinux32SharedrtStatic/
OBJECTS_DEBUGLINUX32SHAREDRTSTATIC = $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTSTATIC)__.__.__.source.Prueba.o

prebuildDebugLinux32SharedrtStatic:
	if ! (test -d $(EXECUTION_PATH)../../../bin/GCC/DebugLinux32SharedrtStatic) then mkdir -p "$(EXECUTION_PATH)../../../bin/GCC/DebugLinux32SharedrtStatic"; fi
	if ! (test -d $(EXECUTION_PATH)../../../garbage/GCC/DebugLinux32SharedrtStatic) then mkdir -p "$(EXECUTION_PATH)../../../garbage/GCC/DebugLinux32SharedrtStatic"; fi


DebugLinux32SharedrtStatic: $(OBJECTS_DEBUGLINUX32SHAREDRTSTATIC)
	$(AR_DEBUGLINUX32SHAREDRTSTATIC) $(OUTPUT_DEBUGLINUX32SHAREDRTSTATIC) $(OBJECTS_DEBUGLINUX32SHAREDRTSTATIC)

$(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTSTATIC)__.__.__.source.Prueba.o: $(EXECUTION_PATH)../../../source/Prueba.cpp
	$(CXX_DEBUGLINUX32SHAREDRTSTATIC) $(COMPILEROPTIONS_DEBUGLINUX32SHAREDRTSTATIC) $(DEFINITIONS_DEBUGLINUX32SHAREDRTSTATIC) $(INCLUDES_DEBUGLINUX32SHAREDRTSTATIC) -c $(EXECUTION_PATH)../../../source/Prueba.cpp -o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTSTATIC)__.__.__.source.Prueba.o

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
INCLUDES_DEBUGMAC32SHAREDRTDYNAMIC = $(INCLUDES_GLOBAL) -I$(EXECUTION_PATH)../../../headers -I$(EXECUTION_PATH)../../../3rdparty/ICU/include
LIBRARYDIRS_DEBUGMAC32SHAREDRTDYNAMIC = $(LIBRARYDIRS_GLOBAL) -L$(EXECUTION_PATH)../../../bin/Clang/DebugMac32SharedrtDynamic -L$(EXECUTION_PATH)../../../3rdparty/Boost/bin/Mac32/DebugSharedrtStatic
LIBRARIES_DEBUGMAC32SHAREDRTDYNAMIC = $(LIBRARIES_GLOBAL) -licudata -licuuc -licui18n -lQuimeraEngineSystem -lQuimeraEngineTools -lQuimeraEngineCommon -lboost_system-mt-d
COMPILEROPTIONS_DEBUGMAC32SHAREDRTDYNAMIC = $(COMPILEROPTIONS_GLOBAL) -g -Wall -Wno-comment -m32 -isystem $(EXECUTION_PATH)../../../3rdparty/Boost/include -fno-rtti -fno-exceptions
LINKEROPTIONS_DEBUGMAC32SHAREDRTDYNAMIC = $(LINKEROPTIONS_GLOBAL) -m32
DEFINITIONS_DEBUGMAC32SHAREDRTDYNAMIC = $(DEFINITIONS_GLOBAL) -DQE_PREPROCESSOR_EXPORTLIB_CORE -DQE_PREPROCESSOR_IMPORTLIB_SYSTEM -DQE_PREPROCESSOR_IMPORTLIB_TOOLS -DQE_PREPROCESSOR_IMPORTLIB_COMMON -DBOOST_NO_RTTI -DBOOST_NO_TYPEID -DBOOST_NO_EXCEPTIONS
OUTPUT_DEBUGMAC32SHAREDRTDYNAMIC = $(EXECUTION_PATH)../../../bin/Clang/DebugMac32SharedrtDynamic/libQuimeraEngineCore.dylib
INTERMEDIARYDIR_DEBUGMAC32SHAREDRTDYNAMIC = $(EXECUTION_PATH)../../../garbage/Clang/DebugMac32SharedrtDynamic/
OBJECTS_DEBUGMAC32SHAREDRTDYNAMIC = $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTDYNAMIC)__.__.__.source.Prueba.o

prebuildDebugMac32SharedrtDynamic:
	if ! (test -d $(EXECUTION_PATH)../../../bin/Clang/DebugMac32SharedrtDynamic) then mkdir -p "$(EXECUTION_PATH)../../../bin/Clang/DebugMac32SharedrtDynamic"; fi
	if ! (test -d $(EXECUTION_PATH)../../../garbage/Clang/DebugMac32SharedrtDynamic) then mkdir -p "$(EXECUTION_PATH)../../../garbage/Clang/DebugMac32SharedrtDynamic"; fi


DebugMac32SharedrtDynamic: $(OBJECTS_DEBUGMAC32SHAREDRTDYNAMIC)
	$(LD_DEBUGMAC32SHAREDRTDYNAMIC) -shared $(LINKEROPTIONS_DEBUGMAC32SHAREDRTDYNAMIC) $(LIBRARYDIRS_DEBUGMAC32SHAREDRTDYNAMIC) $(OBJECTS_DEBUGMAC32SHAREDRTDYNAMIC) $(LIBRARIES_DEBUGMAC32SHAREDRTDYNAMIC) -o $(OUTPUT_DEBUGMAC32SHAREDRTDYNAMIC)

$(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTDYNAMIC)__.__.__.source.Prueba.o: $(EXECUTION_PATH)../../../source/Prueba.cpp
	$(CXX_DEBUGMAC32SHAREDRTDYNAMIC) $(COMPILEROPTIONS_DEBUGMAC32SHAREDRTDYNAMIC) $(DEFINITIONS_DEBUGMAC32SHAREDRTDYNAMIC) $(INCLUDES_DEBUGMAC32SHAREDRTDYNAMIC) -c $(EXECUTION_PATH)../../../source/Prueba.cpp -o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTDYNAMIC)__.__.__.source.Prueba.o

postbuildDebugMac32SharedrtDynamic:


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
INCLUDES_DEBUGMAC32SHAREDRTSTATIC = $(INCLUDES_GLOBAL) -I$(EXECUTION_PATH)../../../headers -I$(EXECUTION_PATH)../../../3rdparty/ICU/include
LIBRARYDIRS_DEBUGMAC32SHAREDRTSTATIC = $(LIBRARYDIRS_GLOBAL)
LIBRARIES_DEBUGMAC32SHAREDRTSTATIC = $(LIBRARIES_GLOBAL)
COMPILEROPTIONS_DEBUGMAC32SHAREDRTSTATIC = $(COMPILEROPTIONS_GLOBAL) -g -Wall -Wno-comment -m32 -isystem $(EXECUTION_PATH)../../../3rdparty/Boost/include -fno-rtti -fno-exceptions
LINKEROPTIONS_DEBUGMAC32SHAREDRTSTATIC = $(LINKEROPTIONS_GLOBAL) -m32
DEFINITIONS_DEBUGMAC32SHAREDRTSTATIC = $(DEFINITIONS_GLOBAL) -DBOOST_NO_RTTI -DBOOST_NO_TYPEID -DBOOST_NO_EXCEPTIONS
OUTPUT_DEBUGMAC32SHAREDRTSTATIC = $(EXECUTION_PATH)../../../bin/Clang/DebugMac32SharedrtStatic/libQuimeraEngineCore.a
INTERMEDIARYDIR_DEBUGMAC32SHAREDRTSTATIC = $(EXECUTION_PATH)../../../garbage/Clang/DebugMac32SharedrtStatic/
OBJECTS_DEBUGMAC32SHAREDRTSTATIC = $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTSTATIC)__.__.__.source.Prueba.o

prebuildDebugMac32SharedrtStatic:
	if ! (test -d $(EXECUTION_PATH)../../../bin/Clang/DebugMac32SharedrtStatic) then mkdir -p "$(EXECUTION_PATH)../../../bin/Clang/DebugMac32SharedrtStatic"; fi
	if ! (test -d $(EXECUTION_PATH)../../../garbage/Clang/DebugMac32SharedrtStatic) then mkdir -p "$(EXECUTION_PATH)../../../garbage/Clang/DebugMac32SharedrtStatic"; fi


DebugMac32SharedrtStatic: $(OBJECTS_DEBUGMAC32SHAREDRTSTATIC)
	$(AR_DEBUGMAC32SHAREDRTSTATIC) $(OUTPUT_DEBUGMAC32SHAREDRTSTATIC) $(OBJECTS_DEBUGMAC32SHAREDRTSTATIC)

$(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTSTATIC)__.__.__.source.Prueba.o: $(EXECUTION_PATH)../../../source/Prueba.cpp
	$(CXX_DEBUGMAC32SHAREDRTSTATIC) $(COMPILEROPTIONS_DEBUGMAC32SHAREDRTSTATIC) $(DEFINITIONS_DEBUGMAC32SHAREDRTSTATIC) $(INCLUDES_DEBUGMAC32SHAREDRTSTATIC) -c $(EXECUTION_PATH)../../../source/Prueba.cpp -o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTSTATIC)__.__.__.source.Prueba.o

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
INCLUDES_DEBUGWIN32SHAREDRTDYNAMIC = $(INCLUDES_GLOBAL) -I$(EXECUTION_PATH)../../../headers -I$(EXECUTION_PATH)../../../3rdparty/ICU/include
LIBRARYDIRS_DEBUGWIN32SHAREDRTDYNAMIC = $(LIBRARYDIRS_GLOBAL) -L$(EXECUTION_PATH)../../../3rdparty/ICU/bin/Win32/ReleaseSharedrtDynamic/MinGW -L$(EXECUTION_PATH)../../../bin/MinGW/DebugWin32SharedrtDynamic -L$(EXECUTION_PATH)../../../3rdparty/Boost/bin/Win32/DebugSharedrtStatic
LIBRARIES_DEBUGWIN32SHAREDRTDYNAMIC = $(LIBRARIES_GLOBAL) -licudt -licuuc -licuin -lQuimeraEngineSystem -lQuimeraEngineTools -lQuimeraEngineCommon -lboost_system-mt-d
COMPILEROPTIONS_DEBUGWIN32SHAREDRTDYNAMIC = $(COMPILEROPTIONS_GLOBAL) -g -Wall -Wno-comment -m32 -isystem $(EXECUTION_PATH)../../../3rdparty/Boost/include -fno-rtti -fno-exceptions
LINKEROPTIONS_DEBUGWIN32SHAREDRTDYNAMIC = $(LINKEROPTIONS_GLOBAL) -m32
DEFINITIONS_DEBUGWIN32SHAREDRTDYNAMIC = $(DEFINITIONS_GLOBAL) -DQE_PREPROCESSOR_EXPORTLIB_CORE -DQE_PREPROCESSOR_IMPORTLIB_SYSTEM -DQE_PREPROCESSOR_IMPORTLIB_TOOLS -DQE_PREPROCESSOR_IMPORTLIB_COMMON -DBOOST_NO_RTTI -DBOOST_NO_TYPEID -DBOOST_NO_EXCEPTIONS
OUTPUT_DEBUGWIN32SHAREDRTDYNAMIC = $(EXECUTION_PATH)../../../bin/MinGW/DebugWin32SharedrtDynamic/QuimeraEngineCore.dll
INTERMEDIARYDIR_DEBUGWIN32SHAREDRTDYNAMIC = $(EXECUTION_PATH)../../../garbage/MinGW/DebugWin32SharedrtDynamic/
OBJECTS_DEBUGWIN32SHAREDRTDYNAMIC = $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTDYNAMIC)__.__.__.source.Prueba.o

prebuildDebugWin32SharedrtDynamic:
	cmd /c if not exist $(EXECUTION_PATH)..\..\..\bin\MinGW\DebugWin32SharedrtDynamic mkdir "$(EXECUTION_PATH)..\..\..\bin\MinGW\DebugWin32SharedrtDynamic"
	cmd /c if not exist $(EXECUTION_PATH)..\..\..\garbage\MinGW\DebugWin32SharedrtDynamic mkdir "$(EXECUTION_PATH)..\..\..\garbage\MinGW\DebugWin32SharedrtDynamic"


DebugWin32SharedrtDynamic: $(OBJECTS_DEBUGWIN32SHAREDRTDYNAMIC)
	$(LD_DEBUGWIN32SHAREDRTDYNAMIC) -shared $(LINKEROPTIONS_DEBUGWIN32SHAREDRTDYNAMIC) $(LIBRARYDIRS_DEBUGWIN32SHAREDRTDYNAMIC) $(OBJECTS_DEBUGWIN32SHAREDRTDYNAMIC) $(LIBRARIES_DEBUGWIN32SHAREDRTDYNAMIC) -o $(OUTPUT_DEBUGWIN32SHAREDRTDYNAMIC)

$(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTDYNAMIC)__.__.__.source.Prueba.o: $(EXECUTION_PATH)../../../source/Prueba.cpp
	$(CXX_DEBUGWIN32SHAREDRTDYNAMIC) $(COMPILEROPTIONS_DEBUGWIN32SHAREDRTDYNAMIC) $(DEFINITIONS_DEBUGWIN32SHAREDRTDYNAMIC) $(INCLUDES_DEBUGWIN32SHAREDRTDYNAMIC) -c $(EXECUTION_PATH)../../../source/Prueba.cpp -o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTDYNAMIC)__.__.__.source.Prueba.o

postbuildDebugWin32SharedrtDynamic:


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
INCLUDES_DEBUGWIN32SHAREDRTSTATIC = $(INCLUDES_GLOBAL) -I$(EXECUTION_PATH)../../../headers -I$(EXECUTION_PATH)../../../3rdparty/ICU/include
LIBRARYDIRS_DEBUGWIN32SHAREDRTSTATIC = $(LIBRARYDIRS_GLOBAL)
LIBRARIES_DEBUGWIN32SHAREDRTSTATIC = $(LIBRARIES_GLOBAL)
COMPILEROPTIONS_DEBUGWIN32SHAREDRTSTATIC = $(COMPILEROPTIONS_GLOBAL) -g -Wall -Wno-comment -m32 -isystem $(EXECUTION_PATH)../../../3rdparty/Boost/include -fno-rtti -fno-exceptions
LINKEROPTIONS_DEBUGWIN32SHAREDRTSTATIC = $(LINKEROPTIONS_GLOBAL) -m32
DEFINITIONS_DEBUGWIN32SHAREDRTSTATIC = $(DEFINITIONS_GLOBAL) -DBOOST_NO_RTTI -DBOOST_NO_TYPEID -DBOOST_NO_EXCEPTIONS
OUTPUT_DEBUGWIN32SHAREDRTSTATIC = $(EXECUTION_PATH)../../../bin/MinGW/DebugWin32SharedrtStatic/libQuimeraEngineCore.a
INTERMEDIARYDIR_DEBUGWIN32SHAREDRTSTATIC = $(EXECUTION_PATH)../../../garbage/MinGW/DebugWin32SharedrtStatic/
OBJECTS_DEBUGWIN32SHAREDRTSTATIC = $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTSTATIC)__.__.__.source.Prueba.o

prebuildDebugWin32SharedrtStatic:
	cmd /c if not exist $(EXECUTION_PATH)..\..\..\bin\MinGW\DebugWin32SharedrtStatic mkdir "$(EXECUTION_PATH)..\..\..\bin\MinGW\DebugWin32SharedrtStatic"
	cmd /c if not exist $(EXECUTION_PATH)..\..\..\garbage\MinGW\DebugWin32SharedrtStatic mkdir "$(EXECUTION_PATH)..\..\..\garbage\MinGW\DebugWin32SharedrtStatic"


DebugWin32SharedrtStatic: $(OBJECTS_DEBUGWIN32SHAREDRTSTATIC)
	$(AR_DEBUGWIN32SHAREDRTSTATIC) $(OUTPUT_DEBUGWIN32SHAREDRTSTATIC) $(OBJECTS_DEBUGWIN32SHAREDRTSTATIC)

$(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTSTATIC)__.__.__.source.Prueba.o: $(EXECUTION_PATH)../../../source/Prueba.cpp
	$(CXX_DEBUGWIN32SHAREDRTSTATIC) $(COMPILEROPTIONS_DEBUGWIN32SHAREDRTSTATIC) $(DEFINITIONS_DEBUGWIN32SHAREDRTSTATIC) $(INCLUDES_DEBUGWIN32SHAREDRTSTATIC) -c $(EXECUTION_PATH)../../../source/Prueba.cpp -o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTSTATIC)__.__.__.source.Prueba.o

postbuildDebugWin32SharedrtStatic:


buildDebugWin32SharedrtStatic: prebuildDebugWin32SharedrtStatic DebugWin32SharedrtStatic postbuildDebugWin32SharedrtStatic

cleanDebugWin32SharedrtStatic:
	rm -f $(OBJECTS_DEBUGWIN32SHAREDRTSTATIC)
	rm -f $(OUTPUT_DEBUGWIN32SHAREDRTSTATIC)
	cmd /c if exist $(EXECUTION_PATH)..\..\..\bin\MinGW\DebugWin32SharedrtStatic rmdir "$(EXECUTION_PATH)..\..\..\bin\MinGW\DebugWin32SharedrtStatic" /s /q
	cmd /c if exist $(EXECUTION_PATH)..\..\..\garbage\MinGW\DebugWin32SharedrtStatic rmdir "$(EXECUTION_PATH)..\..\..\garbage\MinGW\DebugWin32SharedrtStatic" /s /q



.PHONY:buildDebugLinux32SharedrtDynamic prebuildDebugLinux32SharedrtDynamic DebugLinux32SharedrtDynamic postbuildDebugLinux32SharedrtDynamic cleanDebugLinux32SharedrtDynamic buildDebugLinux32SharedrtStatic prebuildDebugLinux32SharedrtStatic DebugLinux32SharedrtStatic postbuildDebugLinux32SharedrtStatic cleanDebugLinux32SharedrtStatic buildDebugMac32SharedrtDynamic prebuildDebugMac32SharedrtDynamic DebugMac32SharedrtDynamic postbuildDebugMac32SharedrtDynamic cleanDebugMac32SharedrtDynamic buildDebugMac32SharedrtStatic prebuildDebugMac32SharedrtStatic DebugMac32SharedrtStatic postbuildDebugMac32SharedrtStatic cleanDebugMac32SharedrtStatic buildDebugWin32SharedrtDynamic prebuildDebugWin32SharedrtDynamic DebugWin32SharedrtDynamic postbuildDebugWin32SharedrtDynamic cleanDebugWin32SharedrtDynamic buildDebugWin32SharedrtStatic prebuildDebugWin32SharedrtStatic DebugWin32SharedrtStatic postbuildDebugWin32SharedrtStatic cleanDebugWin32SharedrtStatic 