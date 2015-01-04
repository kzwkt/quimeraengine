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
DebugLinux32SharedrtDynamic: CXX = g++
DebugLinux32SharedrtDynamic: AR = ar
DebugLinux32SharedrtDynamic: LD = g++
DebugLinux32SharedrtDynamic: AS = as
DebugLinux32SharedrtDynamic: INCLUDES_DEBUGLINUX32SHAREDRTDYNAMIC = $(INCLUDES_GLOBAL) -I$(EXECUTION_PATH)../../../headers -I$(EXECUTION_PATH)../../../3rdparty/ICU/include
DebugLinux32SharedrtDynamic: LIBRARYDIRS_DEBUGLINUX32SHAREDRTDYNAMIC = $(LIBRARYDIRS_GLOBAL) -L$(EXECUTION_PATH)../../../bin/GCC/DebugLinux32SharedrtDynamic -L$(EXECUTION_PATH)../../../3rdparty/Boost/bin/Linux32/DebugSharedrtStatic
DebugLinux32SharedrtDynamic: LIBRARIES_DEBUGLINUX32SHAREDRTDYNAMIC = $(LIBRARIES_GLOBAL) -licudata -licuuc -licui18n -lQuimeraEngineSystem -lQuimeraEngineTools -lQuimeraEngineCommon
DebugLinux32SharedrtDynamic: COMPILEROPTIONS_DEBUGLINUX32SHAREDRTDYNAMIC = $(COMPILEROPTIONS_GLOBAL) -g -Wall -Wno-comment -m32 -isystem $(EXECUTION_PATH)../../../3rdparty/Boost/include
DebugLinux32SharedrtDynamic: LINKEROPTIONS_DEBUGLINUX32SHAREDRTDYNAMIC = $(LINKEROPTIONS_GLOBAL) -m32
DebugLinux32SharedrtDynamic: DEFINITIONS_DEBUGLINUX32SHAREDRTDYNAMIC = $(DEFINITIONS_GLOBAL) -DQE_PREPROCESSOR_EXPORTLIB_CORE -DQE_PREPROCESSOR_IMPORTLIB_SYSTEM -DQE_PREPROCESSOR_IMPORTLIB_TOOLS -DQE_PREPROCESSOR_IMPORTLIB_COMMON
DebugLinux32SharedrtDynamic: OUTPUT_DEBUGLINUX32SHAREDRTDYNAMIC = $(EXECUTION_PATH)../../../bin/GCC/DebugLinux32SharedrtDynamic/libQuimeraEngineCore.so
DebugLinux32SharedrtDynamic: INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTDYNAMIC = $(EXECUTION_PATH)../../../garbage/GCC/DebugLinux32SharedrtDynamic/
DebugLinux32SharedrtDynamic: OBJECTS_DEBUGLINUX32SHAREDRTDYNAMIC = $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTDYNAMIC)__.__.__.source.Prueba.o

prebuildDebugLinux32SharedrtDynamic:
	if ! (test -d $(EXECUTION_PATH)../../../bin/GCC/DebugLinux32SharedrtDynamic) then mkdir -p "$(EXECUTION_PATH)../../../bin/GCC/DebugLinux32SharedrtDynamic"; fi
	if ! (test -d $(EXECUTION_PATH)../../../garbage/GCC/DebugLinux32SharedrtDynamic) then mkdir -p "$(EXECUTION_PATH)../../../garbage/GCC/DebugLinux32SharedrtDynamic"; fi


DebugLinux32SharedrtDynamic: $(OBJECTS_DEBUGLINUX32SHAREDRTDYNAMIC)
	$(LD) -shared $(LINKEROPTIONS_DEBUGLINUX32SHAREDRTDYNAMIC) $(LIBRARYDIRS_DEBUGLINUX32SHAREDRTDYNAMIC) $(OBJECTS_DEBUGLINUX32SHAREDRTDYNAMIC) $(LIBRARIES_DEBUGLINUX32SHAREDRTDYNAMIC) -o $(OUTPUT_DEBUGLINUX32SHAREDRTDYNAMIC)

$(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTDYNAMIC)__.__.__.source.Prueba.o: $(EXECUTION_PATH)../../../source/Prueba.cpp
	$(CXX) $(COMPILEROPTIONS_DEBUGLINUX32SHAREDRTDYNAMIC) $(INCLUDES_DEBUGLINUX32SHAREDRTDYNAMIC) -c $(EXECUTION_PATH)../../../source/Prueba.cpp -o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTDYNAMIC)__.__.__.source.Prueba.o

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
DebugLinux32SharedrtStatic: CXX = g++
DebugLinux32SharedrtStatic: AR = ar
DebugLinux32SharedrtStatic: LD = g++
DebugLinux32SharedrtStatic: AS = as
DebugLinux32SharedrtStatic: INCLUDES_DEBUGLINUX32SHAREDRTSTATIC = $(INCLUDES_GLOBAL) -I$(EXECUTION_PATH)../../../headers -I$(EXECUTION_PATH)../../../3rdparty/ICU/include
DebugLinux32SharedrtStatic: LIBRARYDIRS_DEBUGLINUX32SHAREDRTSTATIC = $(LIBRARYDIRS_GLOBAL)
DebugLinux32SharedrtStatic: LIBRARIES_DEBUGLINUX32SHAREDRTSTATIC = $(LIBRARIES_GLOBAL)
DebugLinux32SharedrtStatic: COMPILEROPTIONS_DEBUGLINUX32SHAREDRTSTATIC = $(COMPILEROPTIONS_GLOBAL) -g -Wall -Wno-comment -m32 -isystem $(EXECUTION_PATH)../../../3rdparty/Boost/include
DebugLinux32SharedrtStatic: LINKEROPTIONS_DEBUGLINUX32SHAREDRTSTATIC = $(LINKEROPTIONS_GLOBAL) -m32
DebugLinux32SharedrtStatic: DEFINITIONS_DEBUGLINUX32SHAREDRTSTATIC = $(DEFINITIONS_GLOBAL)
DebugLinux32SharedrtStatic: OUTPUT_DEBUGLINUX32SHAREDRTSTATIC = $(EXECUTION_PATH)../../../bin/GCC/DebugLinux32SharedrtStatic/libQuimeraEngineCore.a
DebugLinux32SharedrtStatic: INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTSTATIC = $(EXECUTION_PATH)../../../garbage/GCC/DebugLinux32SharedrtStatic/
DebugLinux32SharedrtStatic: OBJECTS_DEBUGLINUX32SHAREDRTSTATIC = $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTSTATIC)__.__.__.source.Prueba.o

prebuildDebugLinux32SharedrtStatic:
	if ! (test -d $(EXECUTION_PATH)../../../bin/GCC/DebugLinux32SharedrtStatic) then mkdir -p "$(EXECUTION_PATH)../../../bin/GCC/DebugLinux32SharedrtStatic"; fi
	if ! (test -d $(EXECUTION_PATH)../../../garbage/GCC/DebugLinux32SharedrtStatic) then mkdir -p "$(EXECUTION_PATH)../../../garbage/GCC/DebugLinux32SharedrtStatic"; fi


DebugLinux32SharedrtStatic: $(OBJECTS_DEBUGLINUX32SHAREDRTSTATIC)
	$(AR) rcs $(OUTPUT_DEBUGLINUX32SHAREDRTSTATIC) $(OBJECTS_DEBUGLINUX32SHAREDRTSTATIC)

$(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTSTATIC)__.__.__.source.Prueba.o: $(EXECUTION_PATH)../../../source/Prueba.cpp
	$(CXX) $(COMPILEROPTIONS_DEBUGLINUX32SHAREDRTSTATIC) $(INCLUDES_DEBUGLINUX32SHAREDRTSTATIC) -c $(EXECUTION_PATH)../../../source/Prueba.cpp -o $(INTERMEDIARYDIR_DEBUGLINUX32SHAREDRTSTATIC)__.__.__.source.Prueba.o

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
DebugMac32SharedrtDynamic: CXX = clang++
DebugMac32SharedrtDynamic: AR = ar rcu
DebugMac32SharedrtDynamic: LD = clang++
DebugMac32SharedrtDynamic: AS = llvm-as
DebugMac32SharedrtDynamic: INCLUDES_DEBUGMAC32SHAREDRTDYNAMIC = $(INCLUDES_GLOBAL) -I$(EXECUTION_PATH)../../../headers -I$(EXECUTION_PATH)../../../3rdparty/ICU/include
DebugMac32SharedrtDynamic: LIBRARYDIRS_DEBUGMAC32SHAREDRTDYNAMIC = $(LIBRARYDIRS_GLOBAL) -L$(EXECUTION_PATH)../../../bin/Clang/DebugMac32SharedrtDynamic -L$(EXECUTION_PATH)../../../3rdparty/Boost/bin/Mac32/DebugSharedrtStatic
DebugMac32SharedrtDynamic: LIBRARIES_DEBUGMAC32SHAREDRTDYNAMIC = $(LIBRARIES_GLOBAL) -licudata -licuuc -licui18n -lQuimeraEngineSystem -lQuimeraEngineTools -lQuimeraEngineCommon -lboost_system-mt-d
DebugMac32SharedrtDynamic: COMPILEROPTIONS_DEBUGMAC32SHAREDRTDYNAMIC = $(COMPILEROPTIONS_GLOBAL) -g -Wall -Wno-comment -m32 -isystem $(EXECUTION_PATH)../../../3rdparty/Boost/include
DebugMac32SharedrtDynamic: LINKEROPTIONS_DEBUGMAC32SHAREDRTDYNAMIC = $(LINKEROPTIONS_GLOBAL) -m32
DebugMac32SharedrtDynamic: DEFINITIONS_DEBUGMAC32SHAREDRTDYNAMIC = $(DEFINITIONS_GLOBAL) -DQE_PREPROCESSOR_EXPORTLIB_CORE -DQE_PREPROCESSOR_IMPORTLIB_SYSTEM -DQE_PREPROCESSOR_IMPORTLIB_TOOLS -DQE_PREPROCESSOR_IMPORTLIB_COMMON
DebugMac32SharedrtDynamic: OUTPUT_DEBUGMAC32SHAREDRTDYNAMIC = $(EXECUTION_PATH)../../../bin/Clang/DebugMac32SharedrtDynamic/libQuimeraEngineCore.dylib
DebugMac32SharedrtDynamic: INTERMEDIARYDIR_DEBUGMAC32SHAREDRTDYNAMIC = $(EXECUTION_PATH)../../../garbage/Clang/DebugMac32SharedrtDynamic/
DebugMac32SharedrtDynamic: OBJECTS_DEBUGMAC32SHAREDRTDYNAMIC = $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTDYNAMIC)__.__.__.source.Prueba.o

prebuildDebugMac32SharedrtDynamic:
	if ! (test -d $(EXECUTION_PATH)../../../bin/Clang/DebugMac32SharedrtDynamic) then mkdir -p "$(EXECUTION_PATH)../../../bin/Clang/DebugMac32SharedrtDynamic"; fi
	if ! (test -d $(EXECUTION_PATH)../../../garbage/Clang/DebugMac32SharedrtDynamic) then mkdir -p "$(EXECUTION_PATH)../../../garbage/Clang/DebugMac32SharedrtDynamic"; fi


DebugMac32SharedrtDynamic: $(OBJECTS_DEBUGMAC32SHAREDRTDYNAMIC)
	$(LD) -shared $(LINKEROPTIONS_DEBUGMAC32SHAREDRTDYNAMIC) $(LIBRARYDIRS_DEBUGMAC32SHAREDRTDYNAMIC) $(OBJECTS_DEBUGMAC32SHAREDRTDYNAMIC) $(LIBRARIES_DEBUGMAC32SHAREDRTDYNAMIC) -o $(OUTPUT_DEBUGMAC32SHAREDRTDYNAMIC)

$(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTDYNAMIC)__.__.__.source.Prueba.o: $(EXECUTION_PATH)../../../source/Prueba.cpp
	$(CXX) $(COMPILEROPTIONS_DEBUGMAC32SHAREDRTDYNAMIC) $(INCLUDES_DEBUGMAC32SHAREDRTDYNAMIC) -c $(EXECUTION_PATH)../../../source/Prueba.cpp -o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTDYNAMIC)__.__.__.source.Prueba.o

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
DebugMac32SharedrtStatic: CXX = clang++
DebugMac32SharedrtStatic: AR = ar rcu
DebugMac32SharedrtStatic: LD = clang++
DebugMac32SharedrtStatic: AS = llvm-as
DebugMac32SharedrtStatic: INCLUDES_DEBUGMAC32SHAREDRTSTATIC = $(INCLUDES_GLOBAL) -I$(EXECUTION_PATH)../../../headers -I$(EXECUTION_PATH)../../../3rdparty/ICU/include
DebugMac32SharedrtStatic: LIBRARYDIRS_DEBUGMAC32SHAREDRTSTATIC = $(LIBRARYDIRS_GLOBAL)
DebugMac32SharedrtStatic: LIBRARIES_DEBUGMAC32SHAREDRTSTATIC = $(LIBRARIES_GLOBAL)
DebugMac32SharedrtStatic: COMPILEROPTIONS_DEBUGMAC32SHAREDRTSTATIC = $(COMPILEROPTIONS_GLOBAL) -g -Wall -Wno-comment -m32 -isystem $(EXECUTION_PATH)../../../3rdparty/Boost/include
DebugMac32SharedrtStatic: LINKEROPTIONS_DEBUGMAC32SHAREDRTSTATIC = $(LINKEROPTIONS_GLOBAL) -m32
DebugMac32SharedrtStatic: DEFINITIONS_DEBUGMAC32SHAREDRTSTATIC = $(DEFINITIONS_GLOBAL)
DebugMac32SharedrtStatic: OUTPUT_DEBUGMAC32SHAREDRTSTATIC = $(EXECUTION_PATH)../../../bin/Clang/DebugMac32SharedrtStatic/libQuimeraEngineCore.a
DebugMac32SharedrtStatic: INTERMEDIARYDIR_DEBUGMAC32SHAREDRTSTATIC = $(EXECUTION_PATH)../../../garbage/Clang/DebugMac32SharedrtStatic/
DebugMac32SharedrtStatic: OBJECTS_DEBUGMAC32SHAREDRTSTATIC = $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTSTATIC)__.__.__.source.Prueba.o

prebuildDebugMac32SharedrtStatic:
	if ! (test -d $(EXECUTION_PATH)../../../bin/Clang/DebugMac32SharedrtStatic) then mkdir -p "$(EXECUTION_PATH)../../../bin/Clang/DebugMac32SharedrtStatic"; fi
	if ! (test -d $(EXECUTION_PATH)../../../garbage/Clang/DebugMac32SharedrtStatic) then mkdir -p "$(EXECUTION_PATH)../../../garbage/Clang/DebugMac32SharedrtStatic"; fi


DebugMac32SharedrtStatic: $(OBJECTS_DEBUGMAC32SHAREDRTSTATIC)
	$(AR) rcs $(OUTPUT_DEBUGMAC32SHAREDRTSTATIC) $(OBJECTS_DEBUGMAC32SHAREDRTSTATIC)

$(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTSTATIC)__.__.__.source.Prueba.o: $(EXECUTION_PATH)../../../source/Prueba.cpp
	$(CXX) $(COMPILEROPTIONS_DEBUGMAC32SHAREDRTSTATIC) $(INCLUDES_DEBUGMAC32SHAREDRTSTATIC) -c $(EXECUTION_PATH)../../../source/Prueba.cpp -o $(INTERMEDIARYDIR_DEBUGMAC32SHAREDRTSTATIC)__.__.__.source.Prueba.o

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
DebugWin32SharedrtDynamic: CXX = g++.exe
DebugWin32SharedrtDynamic: AR = ar.exe
DebugWin32SharedrtDynamic: LD = g++.exe
DebugWin32SharedrtDynamic: AS = as.exe
DebugWin32SharedrtDynamic: INCLUDES_DEBUGWIN32SHAREDRTDYNAMIC = $(INCLUDES_GLOBAL) -I$(EXECUTION_PATH)../../../headers -I$(EXECUTION_PATH)../../../3rdparty/ICU/include
DebugWin32SharedrtDynamic: LIBRARYDIRS_DEBUGWIN32SHAREDRTDYNAMIC = $(LIBRARYDIRS_GLOBAL) -L$(EXECUTION_PATH)../../../3rdparty/ICU/bin/Win32/ReleaseSharedrtDynamic/MinGW -L$(EXECUTION_PATH)../../../bin/MinGW/DebugWin32SharedrtDynamic -L$(EXECUTION_PATH)../../../3rdparty/Boost/bin/Win32/DebugSharedrtStatic
DebugWin32SharedrtDynamic: LIBRARIES_DEBUGWIN32SHAREDRTDYNAMIC = $(LIBRARIES_GLOBAL) -licudt -licuuc -licuin -lQuimeraEngineSystem -lQuimeraEngineTools -lQuimeraEngineCommon -lboost_system-mt-d
DebugWin32SharedrtDynamic: COMPILEROPTIONS_DEBUGWIN32SHAREDRTDYNAMIC = $(COMPILEROPTIONS_GLOBAL) -g -Wall -Wno-comment -m32 -isystem $(EXECUTION_PATH)../../../3rdparty/Boost/include
DebugWin32SharedrtDynamic: LINKEROPTIONS_DEBUGWIN32SHAREDRTDYNAMIC = $(LINKEROPTIONS_GLOBAL) -m32
DebugWin32SharedrtDynamic: DEFINITIONS_DEBUGWIN32SHAREDRTDYNAMIC = $(DEFINITIONS_GLOBAL) -DQE_PREPROCESSOR_EXPORTLIB_CORE -DQE_PREPROCESSOR_IMPORTLIB_SYSTEM -DQE_PREPROCESSOR_IMPORTLIB_TOOLS -DQE_PREPROCESSOR_IMPORTLIB_COMMON
DebugWin32SharedrtDynamic: OUTPUT_DEBUGWIN32SHAREDRTDYNAMIC = $(EXECUTION_PATH)../../../bin/MinGW/DebugWin32SharedrtDynamic/QuimeraEngineCore.dll
DebugWin32SharedrtDynamic: INTERMEDIARYDIR_DEBUGWIN32SHAREDRTDYNAMIC = $(EXECUTION_PATH)../../../garbage/MinGW/DebugWin32SharedrtDynamic/
DebugWin32SharedrtDynamic: OBJECTS_DEBUGWIN32SHAREDRTDYNAMIC = $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTDYNAMIC)__.__.__.source.Prueba.o

prebuildDebugWin32SharedrtDynamic:
	cmd /c if not exist $(EXECUTION_PATH)..\..\..\bin\MinGW\DebugWin32SharedrtDynamic mkdir "$(EXECUTION_PATH)..\..\..\bin\MinGW\DebugWin32SharedrtDynamic"
	cmd /c if not exist $(EXECUTION_PATH)..\..\..\garbage\MinGW\DebugWin32SharedrtDynamic mkdir "$(EXECUTION_PATH)..\..\..\garbage\MinGW\DebugWin32SharedrtDynamic"


DebugWin32SharedrtDynamic: $(OBJECTS_DEBUGWIN32SHAREDRTDYNAMIC)
	$(LD) -shared $(LINKEROPTIONS_DEBUGWIN32SHAREDRTDYNAMIC) $(LIBRARYDIRS_DEBUGWIN32SHAREDRTDYNAMIC) $(OBJECTS_DEBUGWIN32SHAREDRTDYNAMIC) $(LIBRARIES_DEBUGWIN32SHAREDRTDYNAMIC) -o $(OUTPUT_DEBUGWIN32SHAREDRTDYNAMIC)

$(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTDYNAMIC)__.__.__.source.Prueba.o: $(EXECUTION_PATH)../../../source/Prueba.cpp
	$(CXX) $(COMPILEROPTIONS_DEBUGWIN32SHAREDRTDYNAMIC) $(INCLUDES_DEBUGWIN32SHAREDRTDYNAMIC) -c $(EXECUTION_PATH)../../../source/Prueba.cpp -o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTDYNAMIC)__.__.__.source.Prueba.o

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
DebugWin32SharedrtStatic: CXX = g++.exe
DebugWin32SharedrtStatic: AR = ar.exe
DebugWin32SharedrtStatic: LD = g++.exe
DebugWin32SharedrtStatic: AS = as.exe
DebugWin32SharedrtStatic: INCLUDES_DEBUGWIN32SHAREDRTSTATIC = $(INCLUDES_GLOBAL) -I$(EXECUTION_PATH)../../../headers -I$(EXECUTION_PATH)../../../3rdparty/ICU/include
DebugWin32SharedrtStatic: LIBRARYDIRS_DEBUGWIN32SHAREDRTSTATIC = $(LIBRARYDIRS_GLOBAL)
DebugWin32SharedrtStatic: LIBRARIES_DEBUGWIN32SHAREDRTSTATIC = $(LIBRARIES_GLOBAL)
DebugWin32SharedrtStatic: COMPILEROPTIONS_DEBUGWIN32SHAREDRTSTATIC = $(COMPILEROPTIONS_GLOBAL) -g -Wall -Wno-comment -m32 -isystem $(EXECUTION_PATH)../../../3rdparty/Boost/include
DebugWin32SharedrtStatic: LINKEROPTIONS_DEBUGWIN32SHAREDRTSTATIC = $(LINKEROPTIONS_GLOBAL) -m32
DebugWin32SharedrtStatic: DEFINITIONS_DEBUGWIN32SHAREDRTSTATIC = $(DEFINITIONS_GLOBAL)
DebugWin32SharedrtStatic: OUTPUT_DEBUGWIN32SHAREDRTSTATIC = $(EXECUTION_PATH)../../../bin/MinGW/DebugWin32SharedrtStatic/libQuimeraEngineCore.a
DebugWin32SharedrtStatic: INTERMEDIARYDIR_DEBUGWIN32SHAREDRTSTATIC = $(EXECUTION_PATH)../../../garbage/MinGW/DebugWin32SharedrtStatic/
DebugWin32SharedrtStatic: OBJECTS_DEBUGWIN32SHAREDRTSTATIC = $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTSTATIC)__.__.__.source.Prueba.o

prebuildDebugWin32SharedrtStatic:
	cmd /c if not exist $(EXECUTION_PATH)..\..\..\bin\MinGW\DebugWin32SharedrtStatic mkdir "$(EXECUTION_PATH)..\..\..\bin\MinGW\DebugWin32SharedrtStatic"
	cmd /c if not exist $(EXECUTION_PATH)..\..\..\garbage\MinGW\DebugWin32SharedrtStatic mkdir "$(EXECUTION_PATH)..\..\..\garbage\MinGW\DebugWin32SharedrtStatic"


DebugWin32SharedrtStatic: $(OBJECTS_DEBUGWIN32SHAREDRTSTATIC)
	$(AR) rcs $(OUTPUT_DEBUGWIN32SHAREDRTSTATIC) $(OBJECTS_DEBUGWIN32SHAREDRTSTATIC)

$(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTSTATIC)__.__.__.source.Prueba.o: $(EXECUTION_PATH)../../../source/Prueba.cpp
	$(CXX) $(COMPILEROPTIONS_DEBUGWIN32SHAREDRTSTATIC) $(INCLUDES_DEBUGWIN32SHAREDRTSTATIC) -c $(EXECUTION_PATH)../../../source/Prueba.cpp -o $(INTERMEDIARYDIR_DEBUGWIN32SHAREDRTSTATIC)__.__.__.source.Prueba.o

postbuildDebugWin32SharedrtStatic:


buildDebugWin32SharedrtStatic: prebuildDebugWin32SharedrtStatic DebugWin32SharedrtStatic postbuildDebugWin32SharedrtStatic

cleanDebugWin32SharedrtStatic:
	rm -f $(OBJECTS_DEBUGWIN32SHAREDRTSTATIC)
	rm -f $(OUTPUT_DEBUGWIN32SHAREDRTSTATIC)
	cmd /c if exist $(EXECUTION_PATH)..\..\..\bin\MinGW\DebugWin32SharedrtStatic rmdir "$(EXECUTION_PATH)..\..\..\bin\MinGW\DebugWin32SharedrtStatic" /s /q
	cmd /c if exist $(EXECUTION_PATH)..\..\..\garbage\MinGW\DebugWin32SharedrtStatic rmdir "$(EXECUTION_PATH)..\..\..\garbage\MinGW\DebugWin32SharedrtStatic" /s /q



.PHONY:buildDebugLinux32SharedrtDynamic prebuildDebugLinux32SharedrtDynamic DebugLinux32SharedrtDynamic postbuildDebugLinux32SharedrtDynamic cleanDebugLinux32SharedrtDynamic buildDebugLinux32SharedrtStatic prebuildDebugLinux32SharedrtStatic DebugLinux32SharedrtStatic postbuildDebugLinux32SharedrtStatic cleanDebugLinux32SharedrtStatic buildDebugMac32SharedrtDynamic prebuildDebugMac32SharedrtDynamic DebugMac32SharedrtDynamic postbuildDebugMac32SharedrtDynamic cleanDebugMac32SharedrtDynamic buildDebugMac32SharedrtStatic prebuildDebugMac32SharedrtStatic DebugMac32SharedrtStatic postbuildDebugMac32SharedrtStatic cleanDebugMac32SharedrtStatic buildDebugWin32SharedrtDynamic prebuildDebugWin32SharedrtDynamic DebugWin32SharedrtDynamic postbuildDebugWin32SharedrtDynamic cleanDebugWin32SharedrtDynamic buildDebugWin32SharedrtStatic prebuildDebugWin32SharedrtStatic DebugWin32SharedrtStatic postbuildDebugWin32SharedrtStatic cleanDebugWin32SharedrtStatic 