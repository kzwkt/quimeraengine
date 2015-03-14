#------------------------------------QuimeraEngine------------------------------------#

buildDebugWin32SharedrtStatic:
	@echo "----------- Building configuration DebugWin32SharedrtStatic -----------"
	$(MAKE) buildDebugWin32SharedrtStatic -f $(EXECUTION_PATH)Common/Common.project.mak EXECUTION_PATH="$(EXECUTION_PATH)"
	$(MAKE) buildDebugWin32SharedrtStatic -f $(EXECUTION_PATH)Tools/Tools.project.mak EXECUTION_PATH="$(EXECUTION_PATH)"
	$(MAKE) buildDebugWin32SharedrtStatic -f $(EXECUTION_PATH)System/System.project.mak EXECUTION_PATH="$(EXECUTION_PATH)"
	$(MAKE) buildDebugWin32SharedrtStatic -f $(EXECUTION_PATH)Core/Core.project.mak EXECUTION_PATH="$(EXECUTION_PATH)"

cleanDebugWin32SharedrtStatic:
	@echo "----------- Cleaning configuration DebugWin32SharedrtStatic -----------"
	$(MAKE) cleanDebugWin32SharedrtStatic -f $(EXECUTION_PATH)Common/Common.project.mak EXECUTION_PATH="$(EXECUTION_PATH)"
	$(MAKE) cleanDebugWin32SharedrtStatic -f $(EXECUTION_PATH)Tools/Tools.project.mak EXECUTION_PATH="$(EXECUTION_PATH)"
	$(MAKE) cleanDebugWin32SharedrtStatic -f $(EXECUTION_PATH)System/System.project.mak EXECUTION_PATH="$(EXECUTION_PATH)"
	$(MAKE) cleanDebugWin32SharedrtStatic -f $(EXECUTION_PATH)Core/Core.project.mak EXECUTION_PATH="$(EXECUTION_PATH)"

buildDebugWin32SharedrtDynamic:
	@echo "----------- Building configuration DebugWin32SharedrtDynamic -----------"
	$(MAKE) buildDebugWin32SharedrtDynamic -f $(EXECUTION_PATH)Common/Common.project.mak EXECUTION_PATH="$(EXECUTION_PATH)"
	$(MAKE) buildDebugWin32SharedrtDynamic -f $(EXECUTION_PATH)Tools/Tools.project.mak EXECUTION_PATH="$(EXECUTION_PATH)"
	$(MAKE) buildDebugWin32SharedrtDynamic -f $(EXECUTION_PATH)System/System.project.mak EXECUTION_PATH="$(EXECUTION_PATH)"
	$(MAKE) buildDebugWin32SharedrtDynamic -f $(EXECUTION_PATH)Core/Core.project.mak EXECUTION_PATH="$(EXECUTION_PATH)"

cleanDebugWin32SharedrtDynamic:
	@echo "----------- Cleaning configuration DebugWin32SharedrtDynamic -----------"
	$(MAKE) cleanDebugWin32SharedrtDynamic -f $(EXECUTION_PATH)Common/Common.project.mak EXECUTION_PATH="$(EXECUTION_PATH)"
	$(MAKE) cleanDebugWin32SharedrtDynamic -f $(EXECUTION_PATH)Tools/Tools.project.mak EXECUTION_PATH="$(EXECUTION_PATH)"
	$(MAKE) cleanDebugWin32SharedrtDynamic -f $(EXECUTION_PATH)System/System.project.mak EXECUTION_PATH="$(EXECUTION_PATH)"
	$(MAKE) cleanDebugWin32SharedrtDynamic -f $(EXECUTION_PATH)Core/Core.project.mak EXECUTION_PATH="$(EXECUTION_PATH)"

buildDebugLinux32SharedrtStatic:
	@echo "----------- Building configuration DebugLinux32SharedrtStatic -----------"
	$(MAKE) buildDebugLinux32SharedrtStatic -f $(EXECUTION_PATH)Common/Common.project.mak EXECUTION_PATH="$(EXECUTION_PATH)"
	$(MAKE) buildDebugLinux32SharedrtStatic -f $(EXECUTION_PATH)Tools/Tools.project.mak EXECUTION_PATH="$(EXECUTION_PATH)"
	$(MAKE) buildDebugLinux32SharedrtStatic -f $(EXECUTION_PATH)System/System.project.mak EXECUTION_PATH="$(EXECUTION_PATH)"
	$(MAKE) buildDebugLinux32SharedrtStatic -f $(EXECUTION_PATH)Core/Core.project.mak EXECUTION_PATH="$(EXECUTION_PATH)"

cleanDebugLinux32SharedrtStatic:
	@echo "----------- Cleaning configuration DebugLinux32SharedrtStatic -----------"
	$(MAKE) cleanDebugLinux32SharedrtStatic -f $(EXECUTION_PATH)Common/Common.project.mak EXECUTION_PATH="$(EXECUTION_PATH)"
	$(MAKE) cleanDebugLinux32SharedrtStatic -f $(EXECUTION_PATH)Tools/Tools.project.mak EXECUTION_PATH="$(EXECUTION_PATH)"
	$(MAKE) cleanDebugLinux32SharedrtStatic -f $(EXECUTION_PATH)System/System.project.mak EXECUTION_PATH="$(EXECUTION_PATH)"
	$(MAKE) cleanDebugLinux32SharedrtStatic -f $(EXECUTION_PATH)Core/Core.project.mak EXECUTION_PATH="$(EXECUTION_PATH)"

buildDebugLinux32SharedrtDynamic:
	@echo "----------- Building configuration DebugLinux32SharedrtDynamic -----------"
	$(MAKE) buildDebugLinux32SharedrtDynamic -f $(EXECUTION_PATH)Common/Common.project.mak EXECUTION_PATH="$(EXECUTION_PATH)"
	$(MAKE) buildDebugLinux32SharedrtDynamic -f $(EXECUTION_PATH)Tools/Tools.project.mak EXECUTION_PATH="$(EXECUTION_PATH)"
	$(MAKE) buildDebugLinux32SharedrtDynamic -f $(EXECUTION_PATH)System/System.project.mak EXECUTION_PATH="$(EXECUTION_PATH)"
	$(MAKE) buildDebugLinux32SharedrtDynamic -f $(EXECUTION_PATH)Core/Core.project.mak EXECUTION_PATH="$(EXECUTION_PATH)"

cleanDebugLinux32SharedrtDynamic:
	@echo "----------- Cleaning configuration DebugLinux32SharedrtDynamic -----------"
	$(MAKE) cleanDebugLinux32SharedrtDynamic -f $(EXECUTION_PATH)Common/Common.project.mak EXECUTION_PATH="$(EXECUTION_PATH)"
	$(MAKE) cleanDebugLinux32SharedrtDynamic -f $(EXECUTION_PATH)Tools/Tools.project.mak EXECUTION_PATH="$(EXECUTION_PATH)"
	$(MAKE) cleanDebugLinux32SharedrtDynamic -f $(EXECUTION_PATH)System/System.project.mak EXECUTION_PATH="$(EXECUTION_PATH)"
	$(MAKE) cleanDebugLinux32SharedrtDynamic -f $(EXECUTION_PATH)Core/Core.project.mak EXECUTION_PATH="$(EXECUTION_PATH)"

buildDebugMac32SharedrtStatic:
	@echo "----------- Building configuration DebugMac32SharedrtStatic -----------"
	$(MAKE) buildDebugMac32SharedrtStatic -f $(EXECUTION_PATH)Common/Common.project.mak EXECUTION_PATH="$(EXECUTION_PATH)"
	$(MAKE) buildDebugMac32SharedrtStatic -f $(EXECUTION_PATH)Tools/Tools.project.mak EXECUTION_PATH="$(EXECUTION_PATH)"
	$(MAKE) buildDebugMac32SharedrtStatic -f $(EXECUTION_PATH)System/System.project.mak EXECUTION_PATH="$(EXECUTION_PATH)"
	$(MAKE) buildDebugMac32SharedrtStatic -f $(EXECUTION_PATH)Core/Core.project.mak EXECUTION_PATH="$(EXECUTION_PATH)"

cleanDebugMac32SharedrtStatic:
	@echo "----------- Cleaning configuration DebugMac32SharedrtStatic -----------"
	$(MAKE) cleanDebugMac32SharedrtStatic -f $(EXECUTION_PATH)Common/Common.project.mak EXECUTION_PATH="$(EXECUTION_PATH)"
	$(MAKE) cleanDebugMac32SharedrtStatic -f $(EXECUTION_PATH)Tools/Tools.project.mak EXECUTION_PATH="$(EXECUTION_PATH)"
	$(MAKE) cleanDebugMac32SharedrtStatic -f $(EXECUTION_PATH)System/System.project.mak EXECUTION_PATH="$(EXECUTION_PATH)"
	$(MAKE) cleanDebugMac32SharedrtStatic -f $(EXECUTION_PATH)Core/Core.project.mak EXECUTION_PATH="$(EXECUTION_PATH)"

buildDebugMac32SharedrtDynamic:
	@echo "----------- Building configuration DebugMac32SharedrtDynamic -----------"
	$(MAKE) buildDebugMac32SharedrtDynamic -f $(EXECUTION_PATH)Common/Common.project.mak EXECUTION_PATH="$(EXECUTION_PATH)"
	$(MAKE) buildDebugMac32SharedrtDynamic -f $(EXECUTION_PATH)Tools/Tools.project.mak EXECUTION_PATH="$(EXECUTION_PATH)"
	$(MAKE) buildDebugMac32SharedrtDynamic -f $(EXECUTION_PATH)System/System.project.mak EXECUTION_PATH="$(EXECUTION_PATH)"
	$(MAKE) buildDebugMac32SharedrtDynamic -f $(EXECUTION_PATH)Core/Core.project.mak EXECUTION_PATH="$(EXECUTION_PATH)"

cleanDebugMac32SharedrtDynamic:
	@echo "----------- Cleaning configuration DebugMac32SharedrtDynamic -----------"
	$(MAKE) cleanDebugMac32SharedrtDynamic -f $(EXECUTION_PATH)Common/Common.project.mak EXECUTION_PATH="$(EXECUTION_PATH)"
	$(MAKE) cleanDebugMac32SharedrtDynamic -f $(EXECUTION_PATH)Tools/Tools.project.mak EXECUTION_PATH="$(EXECUTION_PATH)"
	$(MAKE) cleanDebugMac32SharedrtDynamic -f $(EXECUTION_PATH)System/System.project.mak EXECUTION_PATH="$(EXECUTION_PATH)"
	$(MAKE) cleanDebugMac32SharedrtDynamic -f $(EXECUTION_PATH)Core/Core.project.mak EXECUTION_PATH="$(EXECUTION_PATH)"

.PHONY: buildDebugWin32SharedrtStatic cleanDebugWin32SharedrtStatic buildDebugWin32SharedrtDynamic cleanDebugWin32SharedrtDynamic buildDebugLinux32SharedrtStatic cleanDebugLinux32SharedrtStatic buildDebugLinux32SharedrtDynamic cleanDebugLinux32SharedrtDynamic buildDebugMac32SharedrtStatic cleanDebugMac32SharedrtStatic buildDebugMac32SharedrtDynamic cleanDebugMac32SharedrtDynamic