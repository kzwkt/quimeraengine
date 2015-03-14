



.PHONY: clean build_DebugWin32SharedrtStatic_all build_DebugWin32SharedrtDynamic_all clean_DebugWin32SharedrtStatic_all clean_DebugWin32SharedrtDynamic_all

build_DebugWin32SharedrtStatic_all:
	@echo "----------Building project:[ Common - DebugWin32SharedrtStatic ]----------"
	@cd "Common" && $(MAKE) -f  "Common.mk"
	@echo "----------Building project:[ Tools - DebugWin32SharedrtStatic ]----------"
	@cd "Tools" && $(MAKE) -f  "Tools.mk"
	@echo "----------Building project:[ System - DebugWin32SharedrtStatic ]----------"
	@cd "System" && $(MAKE) -f  "System.mk"
	@echo "----------Building project:[ Core - DebugWin32SharedrtStatic ]----------"
	@cd "Core" && $(MAKE) -f  "Core.mk"
build_DebugWin32SharedrtDynamic_all:
	@echo "----------Building project:[ Common - DebugWin32SharedrtDynamic ]----------"
	@cd "Common" && $(MAKE) -f  "Common.mk"
	@echo "----------Building project:[ Tools - DebugWin32SharedrtDynamic ]----------"
	@cd "Tools" && $(MAKE) -f  "Tools.mk"
	@echo "----------Building project:[ System - DebugWin32SharedrtDynamic ]----------"
	@cd "System" && $(MAKE) -f  "System.mk"
	@echo "----------Building project:[ Core - DebugWin32SharedrtDynamic ]----------"
	@cd "Core" && $(MAKE) -f  "Core.mk"
clean_DebugWin32SharedrtStatic_all:
	@echo "----------Cleaning project:[ Common - DebugWin32SharedrtStatic ]----------"
	@cd "Common" && $(MAKE) -f  "Common.mk"  clean 
	@echo "----------Cleaning project:[ Tools - DebugWin32SharedrtStatic ]----------"
	@cd "Tools" && $(MAKE) -f  "Tools.mk"  clean
	@echo "----------Cleaning project:[ System - DebugWin32SharedrtStatic ]----------"
	@cd "System" && $(MAKE) -f  "System.mk"  clean
	@echo "----------Cleaning project:[ Core - DebugWin32SharedrtStatic ]----------"
	@cd "Core" && $(MAKE) -f  "Core.mk" clean
clean_DebugWin32SharedrtDynamic_all:
	@echo "----------Cleaning project:[ Common - DebugWin32SharedrtDynamic ]----------"
	@cd "Common" && $(MAKE) -f  "Common.mk"  clean 
	@echo "----------Cleaning project:[ Tools - DebugWin32SharedrtDynamic ]----------"
	@cd "Tools" && $(MAKE) -f  "Tools.mk"  clean
	@echo "----------Cleaning project:[ System - DebugWin32SharedrtDynamic ]----------"
	@cd "System" && $(MAKE) -f  "System.mk"  clean
	@echo "----------Cleaning project:[ Core - DebugWin32SharedrtDynamic ]----------"
	@cd "Core" && $(MAKE) -f  "Core.mk" clean
