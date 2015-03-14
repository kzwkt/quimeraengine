#------------------------------------------------------------------------------#
# This makefile was generated by 'cbp2make' tool rev.137                       #
# and then tuned by Kinesis Team to adjust to Quimera Engine project's needs.  #
#------------------------------------------------------------------------------#

WRKDIR = %cd%

#----------------------------------------------------------------------------------------------------------------------------------------------------------------------------#
#  DebugLinux32SharedrtStatic ~~~  DebugLinux32SharedrtStatic  ~~~  DebugLinux32SharedrtStatic  ~~~  DebugLinux32SharedrtStatic  ~~~  DebugLinux32SharedrtStatic  ~~~        #  
#----------------------------------------------------------------------------------------------------------------------------------------------------------------------------#

buildDebugLinux32SharedrtStatic: common_debuglinux32sharedrtstatic tools_debuglinux32sharedrtstatic system_debuglinux32sharedrtstatic

system_debuglinux32sharedrtstatic: 
	$(MAKE) debuglinux32sharedrtstatic -f $(MAKEPATH)trunk/testing/projects/CodeBlocks10/QEUnitTests/System/System-linux.cbp.mak

tools_debuglinux32sharedrtstatic: 
	$(MAKE) debuglinux32sharedrtstatic -f $(MAKEPATH)trunk/testing/projects/CodeBlocks10/QEUnitTests/Tools/Tools-linux.cbp.mak

common_debuglinux32sharedrtstatic: 
	$(MAKE) debuglinux32sharedrtstatic -f $(MAKEPATH)trunk/testing/projects/CodeBlocks10/QEUnitTests/Common/Common-linux.cbp.mak

cleanDebugLinux32SharedrtStatic: clean_common_debuglinux32sharedrtstatic clean_tools_debuglinux32sharedrtstatic clean_system_debuglinux32sharedrtstatic

clean_system_debuglinux32sharedrtstatic: 
	$(MAKE) clean_debuglinux32sharedrtstatic -f $(MAKEPATH)trunk/testing/projects/CodeBlocks10/QEUnitTests/System/System-linux.cbp.mak
	
clean_tools_debuglinux32sharedrtstatic: 
	$(MAKE) clean_debuglinux32sharedrtstatic -f $(MAKEPATH)trunk/testing/projects/CodeBlocks10/QEUnitTests/Tools/Tools-linux.cbp.mak
	
clean_common_debuglinux32sharedrtstatic: 
	$(MAKE) clean_debuglinux32sharedrtstatic -f $(MAKEPATH)trunk/testing/projects/CodeBlocks10/QEUnitTests/Common/Common-linux.cbp.mak


#----------------------------------------------------------------------------------------------------------------------------------------------------------------------------#
#  DebugLinux32SharedrtDynamic  ~~~  DebugLinux32SharedrtDynamic  ~~~  DebugLinux32SharedrtDynamic  ~~~  DebugLinux32SharedrtDynamic  ~~~  DebugLinux32SharedrtDynamic  ~~~  #  
#----------------------------------------------------------------------------------------------------------------------------------------------------------------------------#

buildDebugLinux32SharedrtDynamic: common_debuglinux32sharedrtdynamic tools_debuglinux32sharedrtdynamic system_debuglinux32sharedrtdynamic

system_debuglinux32sharedrtdynamic: 
	$(MAKE) debuglinux32sharedrtdynamic -f $(MAKEPATH)trunk/testing/projects/CodeBlocks10/QEUnitTests/System/System-linux.cbp.mak

tools_debuglinux32sharedrtdynamic: 
	$(MAKE) debuglinux32sharedrtdynamic -f $(MAKEPATH)trunk/testing/projects/CodeBlocks10/QEUnitTests/Tools/Tools-linux.cbp.mak

common_debuglinux32sharedrtdynamic: 
	$(MAKE) debuglinux32sharedrtdynamic -f $(MAKEPATH)trunk/testing/projects/CodeBlocks10/QEUnitTests/Common/Common-linux.cbp.mak
	
cleanDebugLinux32SharedrtDynamic: clean_system_debuglinux32sharedrtdynamic clean_tools_debuglinux32sharedrtdynamic clean_common_debuglinux32sharedrtdynamic

clean_system_debuglinux32sharedrtdynamic: 
	$(MAKE) clean_debuglinux32sharedrtdynamic -f $(MAKEPATH)trunk/testing/projects/CodeBlocks10/QEUnitTests/System/System-linux.cbp.mak

clean_tools_debuglinux32sharedrtdynamic: 
	$(MAKE) clean_debuglinux32sharedrtdynamic -f $(MAKEPATH)trunk/testing/projects/CodeBlocks10/QEUnitTests/Tools/Tools-linux.cbp.mak

clean_common_debuglinux32sharedrtdynamic: 
	$(MAKE) clean_debuglinux32sharedrtdynamic -f $(MAKEPATH)trunk/testing/projects/CodeBlocks10/QEUnitTests/Common/Common-linux.cbp.mak

	

.PHONY: clean_tools_tools

