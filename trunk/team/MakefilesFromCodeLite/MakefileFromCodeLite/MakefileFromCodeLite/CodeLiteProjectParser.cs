using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using MakefileFromCodeLite.Model;
using System.Xml;
using System.IO;

namespace MakefileFromCodeLite
{
    class CodeLiteProjectParser
    {
        public CodeLiteWorkspace ParseWorkspace(string workspacePath)
        {
            // WORKSPACE
            XmlDocument workspaceReader = new XmlDocument();
            workspaceReader.Load(workspacePath);

            CodeLiteWorkspace workspace = new CodeLiteWorkspace();
            workspace.Name = workspaceReader.SelectSingleNode("CodeLite_Workspace").Attributes.GetNamedItem("Name").Value;

            // Configurations
            XmlNode buildMatrixNode = workspaceReader.SelectSingleNode("CodeLite_Workspace/BuildMatrix");
            workspace.Configurations = new List<WorkspaceConfiguration>();

            foreach (XmlNode configurationNode in buildMatrixNode.SelectNodes("WorkspaceConfiguration"))
            {
                WorkspaceConfiguration workspaceConfig = new WorkspaceConfiguration();
                workspace.Configurations.Add(workspaceConfig);
                workspaceConfig.Name = configurationNode.Attributes.GetNamedItem("Name").Value;

                workspaceConfig.Projects = new List<WorkspaceConfigurationProject>();

                foreach (XmlNode projectInConfigNode in configurationNode.SelectNodes("Project"))
                {
                    WorkspaceConfigurationProject projectConfiguration = new WorkspaceConfigurationProject();
                    workspaceConfig.Projects.Add(projectConfiguration);
                    projectConfiguration.Name = projectInConfigNode.Attributes.GetNamedItem("Name").Value;
                    projectConfiguration.ConfigName = projectInConfigNode.Attributes.GetNamedItem("ConfigName").Value;
                }
            }

            // PROJECTS
            workspace.Projects = new List<CodeLiteProject>();
            
            foreach (XmlNode projectNode in workspaceReader.SelectNodes("CodeLite_Workspace/Project"))
            {
                CodeLiteProject project = new CodeLiteProject();
                workspace.Projects.Add(project);
                project.Name = projectNode.Attributes.GetNamedItem("Name").Value;
                project.Path = projectNode.Attributes.GetNamedItem("Path").Value;
                
                XmlDocument projectReader = new XmlDocument();
                projectReader.Load(Path.GetDirectoryName(workspacePath) + Path.DirectorySeparatorChar + project.Path);

                // Files
                project.CodeFiles = new List<string>();

                foreach (XmlNode directoryNode in projectReader.SelectNodes("CodeLite_Project/VirtualDirectory"))
                {
                    ParseVirtualDirectory(directoryNode, project);
                }

                // Dependencies
                project.Dependencies = new List<Dependencies>();

                foreach (XmlNode dependencyNode in projectReader.SelectNodes("CodeLite_Project/Dependencies"))
                {
                    if (dependencyNode.Attributes.GetNamedItem("Name") != null)
                    {
                        Dependencies dependencies = new Dependencies();
                        project.Dependencies.Add(dependencies);
                        dependencies.Name = dependencyNode.Attributes.GetNamedItem("Name").Value;

                        XmlNodeList dependencyProjects = dependencyNode.SelectNodes("Project");

                        dependencies.ProjectNames = new List<string>();

                        foreach (XmlNode dependencyProjectNode in dependencyProjects)
                        {
                            dependencies.ProjectNames.Add(dependencyProjectNode.Attributes.GetNamedItem("Name").Value);
                        }
                    }
                }

                // Configurations
                project.Configurations = new List<CodeLiteProjectConfiguration>();

                foreach (XmlNode configNode in projectReader.SelectSingleNode("CodeLite_Project/Settings").SelectNodes("Configuration"))
                {
                    project.Configurations.Add(ParseProjectConfiguration(configNode));
                }

                // Global settings
                project.GlobalConfiguration = ParseProjectConfiguration(projectReader.SelectSingleNode("CodeLite_Project/Settings").SelectSingleNode("GlobalSettings"));
            }

            return workspace;
        }

        protected void ParseVirtualDirectory(XmlNode virtualDirectoryNode, CodeLiteProject project)
        {
            foreach (XmlNode fileNode in virtualDirectoryNode.SelectNodes("File"))
            {
                project.CodeFiles.Add(fileNode.Attributes.GetNamedItem("Name").Value);
            }

            foreach (XmlNode directoryNode in virtualDirectoryNode.SelectNodes("VirtualDirectory"))
            {
                ParseVirtualDirectory(directoryNode, project);
            }
        }

        protected CodeLiteProjectConfiguration ParseProjectConfiguration(XmlNode configurationNode)
        {
            CodeLiteProjectConfiguration config = new CodeLiteProjectConfiguration();

            if (configurationNode.Attributes.GetNamedItem("Name") != null)
            {
                config.Name = configurationNode.Attributes.GetNamedItem("Name").Value;
            }

            XmlNode compilerNode = configurationNode.SelectSingleNode("Compiler");
            config.CompilerOptions = compilerNode.Attributes.GetNamedItem("Options").Value;

            // Include paths
            config.IncludePaths = new List<string>();

            foreach (XmlNode includePathNode in compilerNode.SelectNodes("IncludePath"))
            {
                config.IncludePaths.Add(includePathNode.Attributes.GetNamedItem("Value").Value);
            }

            // Preprocessor definitions
            config.Preprocessors = new List<string>();

            foreach (XmlNode preprocessorNode in compilerNode.SelectNodes("Preprocessor"))
            {
                config.Preprocessors.Add(preprocessorNode.Attributes.GetNamedItem("Value").Value);
            }

            XmlNode linkerNode = configurationNode.SelectSingleNode("Linker");
            config.LinkerOptions = linkerNode.Attributes.GetNamedItem("Options").Value;

            // Library paths
            config.LibraryPaths = new List<string>();

            foreach (XmlNode libraryPathNode in linkerNode.SelectNodes("LibraryPath"))
            {
                config.LibraryPaths.Add(libraryPathNode.Attributes.GetNamedItem("Value").Value);
            }

            // Libraries
            config.Libraries = new List<string>();

            foreach (XmlNode libraryNode in linkerNode.SelectNodes("Library"))
            {
                config.Libraries.Add(libraryNode.Attributes.GetNamedItem("Value").Value);
            }

            // General
            if (configurationNode.SelectSingleNode("General") != null)
            {
                config.OutputFile = configurationNode.SelectSingleNode("General").Attributes.GetNamedItem("OutputFile").Value;
                config.IntermediateDirectory = configurationNode.SelectSingleNode("General").Attributes.GetNamedItem("IntermediateDirectory").Value;
            }

            // Prebuild commands
            config.PreBuildCommands = new List<string>();

            if (configurationNode.SelectSingleNode("PreBuild") != null)
            {
                foreach (XmlNode prebuildNode in configurationNode.SelectSingleNode("PreBuild").SelectNodes("Command"))
                {
                    if (prebuildNode.Attributes.GetNamedItem("Enabled").Value == "yes")
                    {
                        config.PreBuildCommands.Add(prebuildNode.InnerText);
                    }
                }
            }

            // Postbuild commands
            config.PostBuildCommands = new List<string>();

            if (configurationNode.SelectSingleNode("PostBuild") != null)
            {
                foreach (XmlNode postNode in configurationNode.SelectSingleNode("PostBuild").SelectNodes("Command"))
                {
                    if (postNode.Attributes.GetNamedItem("Enabled").Value == "yes")
                    {
                        config.PostBuildCommands.Add(postNode.InnerText);
                    }
                }
            }

            // Type
            config.Type = OutputType.WTF;

            if(configurationNode.Attributes.GetNamedItem("Type") != null)
            {
                string type = configurationNode.Attributes.GetNamedItem("Type").Value;

                if(type == "Executable")
                {
                    config.Type = OutputType.Executable;
                }
                else if(type == "Dynamic Library")
                {
                    config.Type = OutputType.DynamicLibrary;
                }
                else if (type == "Static Library")
                {
                    config.Type = OutputType.StaticLibrary;
                }
            }

            return config;
        }
    }
}
