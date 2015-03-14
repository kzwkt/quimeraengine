using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.IO;
using System.Windows.Forms;

namespace MakefileFromCodeLite
{
    class MakefileGenerator
    {
        enum ConfigurationOS
        {
            Windows,
            Linux,
            Mac,
            WTF
        }

        public string AdjustPath(string path)
        {
            string result = path.Replace("..\\", "../");

            if (result.Contains("../"))
            {
                int whitespacePos = 0;

                while (whitespacePos >= 0 && result.IndexOf("../", whitespacePos) != -1)
                {
                    int pos = result.IndexOf("../", whitespacePos);
                    result = result.Substring(0, pos) + result.Substring(pos + 3);
                    whitespacePos = result.IndexOf(" ", pos);
                }
            }

            return result;
        }

        public string ManglePath(string path)
        {
            return path.Replace(".", "_").Replace("/", ".").Replace("\\", ".");
        }

        public string GenerateWorkspaceMakefileFromModel(MakefileFromCodeLite.Model.CodeLiteWorkspace workspaceModel)
        {
            const string MAKE = "$(MAKE)";
            const string EXECUTION_PATH = "$(EXECUTION_PATH)";

            string result = "#------------------------------------" + workspaceModel.Name + "------------------------------------#\n\n";
            string phony = ".PHONY:";

            foreach (var config in workspaceModel.Configurations)
            {
                result += "build" + config.Name + ":\n";
                result += "\t@echo \"----------- Building configuration " + config.Name + " -----------\"\n";

                string projectTargets = "";

                foreach (var project in workspaceModel.Projects)
                {
                    projectTargets += "\t" + MAKE + " build" + config.Name + " -f " + EXECUTION_PATH + project.Path + ".mak EXECUTION_PATH=\"" + EXECUTION_PATH + "\"\n";
                }

                result += projectTargets + "\n";

                result += "clean" + config.Name + ":\n";
                result += "\t@echo \"----------- Cleaning configuration " + config.Name + " -----------\"\n";

                projectTargets = "";

                foreach (var project in workspaceModel.Projects)
                {
                    projectTargets += "\t" + MAKE + " clean" + config.Name + " -f " + EXECUTION_PATH + project.Path + ".mak EXECUTION_PATH=\"" + EXECUTION_PATH + "\"\n";
                }

                result += projectTargets + "\n";

                phony += " build" + config.Name + " clean" + config.Name;
            }

            result += phony;

            return result;
        }

        public string GenerateProjectMakefileFromModel(MakefileFromCodeLite.Model.CodeLiteProject projectModel)
        {
            const string EXECUTION_PATH = "$(EXECUTION_PATH)";

            string result = "#------------------------------------------------------------------------------------------------------------#\n";
            result += "#------------------------------------" + projectModel.Name + "------------------------------------#\n";
            result += "#------------------------------------------------------------------------------------------------------------#\n";
            result += "\n";

            string phony = ".PHONY:";

            // Global configuration
            const string GLOBAL_CONFIG = "GLOBAL";

            result += "#------------------------------------------------------------\n";
            result += "#----------------------- " + GLOBAL_CONFIG + " ---------------------\n";
            result += "#------------------------------------------------------------\n";
            result += "INCLUDES_" + GLOBAL_CONFIG + " =";

            foreach (string includePath in projectModel.GlobalConfiguration.IncludePaths)
            {
                result += " -I" + EXECUTION_PATH + AdjustPath(includePath);
            }

            result += "\n";
            result += "LIBRARYDIRS_" + GLOBAL_CONFIG + " =";

            foreach (string libraryDir in projectModel.GlobalConfiguration.LibraryPaths)
            {
                result += " -L" + EXECUTION_PATH + AdjustPath(libraryDir);
            }

            result += "\n";
            result += "LIBRARIES_" + GLOBAL_CONFIG + " =";

            foreach (string library in projectModel.GlobalConfiguration.Libraries)
            {
                result += " -l" + library;
            }

            result += "\n";
            result += "COMPILEROPTIONS_" + GLOBAL_CONFIG + " = " + AdjustPath(projectModel.GlobalConfiguration.CompilerOptions.Replace(";", " ")) + "\n";
            result += "LINKEROPTIONS_" + GLOBAL_CONFIG + " = " + projectModel.GlobalConfiguration.LinkerOptions.Replace(";", " ") + "\n";
            result += "DEFINITIONS_" + GLOBAL_CONFIG + " =";

            foreach (string definition in projectModel.GlobalConfiguration.Preprocessors)
            {
                result += " -D" + definition;
            }
            
            result += "\n\n";

            // Configurations
            result = result.Replace("$(ProjectName)", projectModel.Name);
            result = result.Replace("$(ConfigurationName)", projectModel.GlobalConfiguration.Name);

            foreach (var config in projectModel.Configurations)
            {
                ConfigurationOS OPERATING_SYSTEM = ConfigurationOS.WTF;

                if (config.Name.Contains("Win"))
                {
                    OPERATING_SYSTEM = ConfigurationOS.Windows;
                }
                else if(config.Name.Contains("Linux"))
                {
                    OPERATING_SYSTEM = ConfigurationOS.Linux;
                }
                else if (config.Name.Contains("Mac"))
                {
                    OPERATING_SYSTEM = ConfigurationOS.Mac;
                }


                string projectResult = "";
                string CONFIG_NAME = config.Name.ToUpper();

                projectResult += "#------------------------------------------------------------\n";
                projectResult += "#------------- " + config.Name + " --------------\n";
                projectResult += "#------------------------------------------------------------\n";

                switch (OPERATING_SYSTEM)
                {
                    case ConfigurationOS.Windows:
                        projectResult += "CXX_" + CONFIG_NAME + " = g++.exe\n";
                        projectResult += "AR_" + CONFIG_NAME + " = ar.exe rcu\n";
                        projectResult += "LD_" + CONFIG_NAME + " = g++.exe\n";
                        projectResult += "AS_" + CONFIG_NAME + " = as.exe\n";
                        break;
                    case ConfigurationOS.Linux:
                        projectResult += "CXX_" + CONFIG_NAME + " = g++\n";
                        projectResult += "AR_" + CONFIG_NAME + " = ar rcu\n";
                        projectResult += "LD_" + CONFIG_NAME + " = g++\n";
                        projectResult += "AS_" + CONFIG_NAME + " = as\n";
                        break;
                    case ConfigurationOS.Mac:
                        projectResult += "CXX_" + CONFIG_NAME + " = clang++\n";
                        projectResult += "AR_" + CONFIG_NAME + " = ar rcu\n";
                        projectResult += "LD_" + CONFIG_NAME + " = clang++\n";
                        projectResult += "AS_" + CONFIG_NAME + " = llvm-as\n";
                        break;
                    case ConfigurationOS.WTF:
                        break;
                    default:
                        break;
                }

                projectResult += "INCLUDES_" + CONFIG_NAME + " = $(INCLUDES_" + GLOBAL_CONFIG + ")";

                foreach (string includePath in config.IncludePaths)
                {
                    projectResult += " -I" + EXECUTION_PATH + AdjustPath(includePath);
                }

                projectResult += "\n";
                projectResult += "LIBRARYDIRS_" + CONFIG_NAME + " = $(LIBRARYDIRS_" + GLOBAL_CONFIG + ")";

                foreach (string libraryDir in config.LibraryPaths)
                {
                    projectResult += " -L" + EXECUTION_PATH + AdjustPath(libraryDir);
                }

                projectResult += "\n";
                projectResult += "LIBRARIES_" + CONFIG_NAME + " = $(LIBRARIES_" + GLOBAL_CONFIG + ")";

                foreach (string library in config.Libraries)
                {
                    projectResult += " -l" + library;
                }

                projectResult += "\n";
                projectResult += "COMPILEROPTIONS_" + CONFIG_NAME + " = $(COMPILEROPTIONS_" + GLOBAL_CONFIG + ") " + AdjustPath(config.CompilerOptions.Replace(";", " ")) + "\n";
                projectResult += "LINKEROPTIONS_" + CONFIG_NAME + " = $(LINKEROPTIONS_" + GLOBAL_CONFIG + ") " + config.LinkerOptions + "\n";
                projectResult += "DEFINITIONS_" + CONFIG_NAME + " = $(DEFINITIONS_" + GLOBAL_CONFIG + ")";

                // Definitions
                foreach (string definition in config.Preprocessors)
                {
                    projectResult += " -D" + definition;
                }

                projectResult += "\n";
                projectResult += "OUTPUT_" + CONFIG_NAME + " = " + EXECUTION_PATH + AdjustPath(config.OutputFile) + "\n";
                projectResult += "INTERMEDIARYDIR_" + CONFIG_NAME + " = " + EXECUTION_PATH + AdjustPath(config.IntermediateDirectory) + "/\n";
                projectResult += "OBJECTS_" + CONFIG_NAME + " =";

                // Objects
                foreach (string codeFile in projectModel.CodeFiles.Where(c => c.Contains(".cpp")))
                {
                    projectResult += " " + "$(INTERMEDIARYDIR_" + CONFIG_NAME + ")" + ManglePath(AdjustPath(codeFile.Replace(".cpp", ".o")));
                }

                projectResult += "\n\n";
                projectResult += "prebuild" + config.Name + ":\n";

                // Creates directories
                if (OPERATING_SYSTEM == ConfigurationOS.Windows)
                {
                    string directory = EXECUTION_PATH + Path.GetDirectoryName(AdjustPath(config.OutputFile));
                    projectResult += "\tcmd /c if not exist " + directory + " mkdir \"" + directory + "\"\n";
                    directory = EXECUTION_PATH + Path.GetDirectoryName(AdjustPath(config.IntermediateDirectory + "\\"));
                    projectResult += "\tcmd /c if not exist " + directory + " mkdir \"" + directory + "\"\n";
                }
                else
                {
                    string directory = (EXECUTION_PATH + Path.GetDirectoryName(AdjustPath(config.OutputFile))).Replace("\\", "/");
                    projectResult += "\tif ! (test -d " + directory + ") then mkdir -p \"" + directory + "\"; fi\n";
                    directory = (EXECUTION_PATH + Path.GetDirectoryName(AdjustPath(config.IntermediateDirectory + "/"))).Replace("\\", "/");
                    projectResult += "\tif ! (test -d " + directory + ") then mkdir -p \"" + directory + "\"; fi\n";
                }

                // Prebuild commands
                foreach (string command in config.PreBuildCommands)
                {
                    if (OPERATING_SYSTEM == ConfigurationOS.Windows)
                    {
                        projectResult += "\t" + AdjustPath(command).Replace("../", "..\\") + "\n";
                    }
                    else
                    {
                        projectResult += "\t" + AdjustPath(command).Replace("\\", "/") + "\n";
                    }
                }

                projectResult += "\n\n";

                switch (config.Type)
                {
                    case MakefileFromCodeLite.Model.OutputType.Executable:
                        projectResult += config.Name + ": $(OBJECTS_" + CONFIG_NAME + ")\n\t$(LD_" + CONFIG_NAME + ") $(LINKEROPTIONS_" + CONFIG_NAME + ") $(LIBRARYDIRS_" + CONFIG_NAME + ") $(OBJECTS_" + CONFIG_NAME + ") $(LIBRARIES_" + CONFIG_NAME + ") -o $(OUTPUT_" + CONFIG_NAME + ")\n\n";
                        break;
                    case MakefileFromCodeLite.Model.OutputType.DynamicLibrary:
                        projectResult += config.Name + ": $(OBJECTS_" + CONFIG_NAME + ")\n\t$(LD_" + CONFIG_NAME + ") -shared $(LINKEROPTIONS_" + CONFIG_NAME + ") $(LIBRARYDIRS_" + CONFIG_NAME + ") $(OBJECTS_" + CONFIG_NAME + ") $(LIBRARIES_" + CONFIG_NAME + ") -o $(OUTPUT_" + CONFIG_NAME + ")\n\n";
                        break;
                    case MakefileFromCodeLite.Model.OutputType.StaticLibrary:
                        projectResult += config.Name + ": $(OBJECTS_" + CONFIG_NAME + ")\n\t$(AR_" + CONFIG_NAME + ") $(OUTPUT_" + CONFIG_NAME + ") $(OBJECTS_" + CONFIG_NAME + ")\n\n";
                        break;
                    default:
                        MessageBox.Show("Invalid output type");
                        break;
                }

                // Targets
                foreach (string codeFile in projectModel.CodeFiles.Where(c => c.Contains(".cpp")))
                {
                    projectResult += "$(INTERMEDIARYDIR_" + CONFIG_NAME + ")" + ManglePath(AdjustPath(codeFile.Replace(".cpp", ".o"))) + ": " + EXECUTION_PATH + AdjustPath(codeFile) + "\n";
                    projectResult += "\t$(CXX_" + CONFIG_NAME + ") $(COMPILEROPTIONS_" + CONFIG_NAME + ") $(DEFINITIONS_" + CONFIG_NAME + ") $(INCLUDES_" + CONFIG_NAME + ") -c " + EXECUTION_PATH + AdjustPath(codeFile) + " -o " + "$(INTERMEDIARYDIR_" + CONFIG_NAME + ")" + ManglePath(AdjustPath(codeFile.Replace(".cpp", ".o"))) + "\n\n";
                }

                // Postbuild commands
                projectResult += "postbuild" + config.Name + ":\n";
                foreach (string command in config.PostBuildCommands)
                {
                    if (OPERATING_SYSTEM == ConfigurationOS.Windows)
                    {
                        projectResult += "\t" + AdjustPath(command).Replace("../", "..\\") + "\n";
                    }
                    else
                    {
                        projectResult += "\t" + AdjustPath(command).Replace("\\", "/") + "\n";
                    }
                }

                projectResult += "\n\n";
                projectResult += "build" + config.Name + ":" + " prebuild" + config.Name + " " + config.Name + " postbuild" + config.Name;

                projectResult += "\n\n";
                projectResult += "clean" + config.Name + ":\n";

                // Removes files
                projectResult += "\trm -f " + "$(OBJECTS_" + CONFIG_NAME + ")\n";
                projectResult += "\trm -f " + "$(OUTPUT_" + CONFIG_NAME + ")\n";

                // Removes directories
                if (OPERATING_SYSTEM == ConfigurationOS.Windows)
                {
                    string directory = EXECUTION_PATH + Path.GetDirectoryName(AdjustPath(config.OutputFile));
                    projectResult += "\tcmd /c if exist " + directory + " rmdir \"" + directory + "\" /s /q\n";

                    directory = EXECUTION_PATH + Path.GetDirectoryName(AdjustPath(config.IntermediateDirectory + "\\"));
                    projectResult += "\tcmd /c if exist " + directory + " rmdir \"" + directory + "\" /s /q\n";
                }
                else
                {
                    string directory = (EXECUTION_PATH + Path.GetDirectoryName(AdjustPath(config.OutputFile))).Replace("\\", "/");
                    projectResult += "\tif (test -d " + directory + ") then rm -rf \"" + EXECUTION_PATH + Path.GetDirectoryName(AdjustPath(config.OutputFile)).Replace("\\", "/") + "\"; fi\n";
                    projectResult += "\tif (test -d " + directory + ") then rmdir \"" + EXECUTION_PATH + Path.GetDirectoryName(AdjustPath(config.OutputFile)).Replace("\\", "/") + "\"; fi\n";

                    directory = (EXECUTION_PATH + AdjustPath(config.IntermediateDirectory)).Replace("\\", "/");
                    projectResult += "\tif (test -d " + directory + ") then rm -rf \"" + EXECUTION_PATH + Path.GetDirectoryName(AdjustPath(config.IntermediateDirectory + "/")).Replace("\\", "/") + "\"; fi\n";
                    projectResult += "\tif (test -d " + directory + ") then rmdir \"" + EXECUTION_PATH + Path.GetDirectoryName(AdjustPath(config.IntermediateDirectory + "/")).Replace("\\", "/") + "\"; fi\n";
                }

                projectResult += "\n\n";

                projectResult = projectResult.Replace("$(ProjectName)", projectModel.Name);
                projectResult = projectResult.Replace("$(ConfigurationName)", config.Name);
                projectResult = projectResult.Replace("_o", ".o");
                //projectResult = projectResult.Replace("\\", "/");
                result += projectResult;

                phony += "build" + config.Name + " prebuild" + config.Name + " " + config.Name + " postbuild" + config.Name + " clean" + config.Name + " ";
            }

            result += "\n" + phony;

            return result;
        }
    }
}
