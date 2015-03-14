using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.IO;

namespace MakefileFromCodeLite
{
    public partial class Form1 : Form
    {
        private MakefileFromCodeLite.Model.CodeLiteWorkspace m_model;

        private string m_selectedConfiguration;

        private string m_selectedProject;

        public Form1()
        {
            InitializeComponent();
        }

        private void Form1_Load(object sender, EventArgs e)
        {

        }

        private void buttonPick_Click(object sender, EventArgs e)
        {
            DialogResult res = this.openFileDialogWorkspace.ShowDialog(this);

            if (res == System.Windows.Forms.DialogResult.OK)
            {
                this.textBoxWorkspacePath.Text = this.openFileDialogWorkspace.FileName;

                CodeLiteProjectParser parser = new CodeLiteProjectParser();
                m_model = parser.ParseWorkspace(this.openFileDialogWorkspace.FileName);

                FillControlsWithModel(m_model);
            }
        }

        private void FillControlsWithModel(Model.CodeLiteWorkspace workspaceModel)
        {
            // Configurations combo
            this.comboBoxConfigurations.Items.Clear();
            this.comboBoxConfigurations.Items.Add("<Global>");

            foreach (var config in workspaceModel.Configurations)
            {
                this.comboBoxConfigurations.Items.Add(config.Name);
            }

            this.comboBoxConfigurations.SelectedIndex = 0;

            // Projects tree
            TreeNode root = new TreeNode(workspaceModel.Name);
            this.treeViewProjectHierarchy.Nodes.Clear();
            this.treeViewProjectHierarchy.Nodes.Add(root);

            foreach (var project in workspaceModel.Projects)
            {
                root.Nodes.Add(new TreeNode(project.Name));
            }
        }

        private void UpdateControlsAfterSelection()
        {
            var projects = m_model.Projects.Where(p => p.Name == m_selectedProject);

            if (projects.Any())
            {
                MakefileFromCodeLite.Model.CodeLiteProject project = projects.First();

                var configs = project.Configurations.Where(c => c.Name == m_selectedConfiguration);

                if (configs.Any())
                {
                    MakefileFromCodeLite.Model.CodeLiteProjectConfiguration config = configs.First();

                    // Output
                    this.textBoxOutput.Text = config.OutputFile;

                    // Intermediary directory
                    this.textBoxIntermediaryDir.Text = config.IntermediateDirectory;

                    // Compiler options
                    this.textBoxCompilerOptions.Text = config.CompilerOptions;

                    // Linker options
                    this.textBoxLinkerOptions.Text = config.LinkerOptions;

                    // Definitions
                    this.textBoxDefinitions.Text = string.Empty;

                    foreach (string definition in config.Preprocessors)
                    {
                        this.textBoxDefinitions.Text += definition + " ";
                    }

                    // Include Directories
                    this.listIncludeDirectories.Items.Clear();

                    foreach (string includeDirectory in config.IncludePaths)
                    {
                        this.listIncludeDirectories.Items.Add(includeDirectory);
                    }

                    // Library Directories
                    this.listLibraryDirectories.Items.Clear();

                    foreach (string libraryDirectory in config.LibraryPaths)
                    {
                        this.listLibraryDirectories.Items.Add(libraryDirectory);
                    }

                    // Libraries
                    this.listLibraries.Items.Clear();

                    foreach (string library in config.Libraries)
                    {
                        this.listLibraries.Items.Add(library);
                    }

                    // Pre-build commands
                    this.listPrebuild.Items.Clear();

                    foreach (string command in config.PreBuildCommands)
                    {
                        this.listPrebuild.Items.Add(command);
                    }

                    // Post-build commands
                    this.listPostbuild.Items.Clear();

                    foreach (string command in config.PostBuildCommands)
                    {
                        this.listPostbuild.Items.Add(command);
                    }
                }
                else if (m_selectedConfiguration == "<Global>")
                {
                    // Output
                    this.textBoxOutput.Text = string.Empty;

                    // Intermediary directory
                    this.textBoxIntermediaryDir.Text = string.Empty;

                    // Compiler options
                    this.textBoxCompilerOptions.Text = project.GlobalConfiguration.CompilerOptions;

                    // Linker options
                    this.textBoxLinkerOptions.Text = project.GlobalConfiguration.LinkerOptions;

                    // Definitions
                    this.textBoxDefinitions.Text = string.Empty;

                    foreach (string definition in project.GlobalConfiguration.Preprocessors)
                    {
                        this.textBoxDefinitions.Text += definition + " ";
                    }

                    // Include Directories
                    this.listIncludeDirectories.Items.Clear();

                    foreach (string includeDirectory in project.GlobalConfiguration.IncludePaths)
                    {
                        this.listIncludeDirectories.Items.Add(includeDirectory);
                    }

                    // Library Directories
                    this.listLibraryDirectories.Items.Clear();

                    foreach (string libraryDirectory in project.GlobalConfiguration.LibraryPaths)
                    {
                        this.listLibraryDirectories.Items.Add(libraryDirectory);
                    }

                    // Libraries
                    this.listLibraries.Items.Clear();

                    foreach (string library in project.GlobalConfiguration.Libraries)
                    {
                        this.listLibraries.Items.Add(library);
                    }

                    // Pre-build commands
                    this.listPrebuild.Items.Clear();

                    foreach (string command in project.GlobalConfiguration.PreBuildCommands)
                    {
                        this.listPrebuild.Items.Add(command);
                    }

                    // Post-build commands
                    this.listPostbuild.Items.Clear();

                    foreach (string command in project.GlobalConfiguration.PostBuildCommands)
                    {
                        this.listPostbuild.Items.Add(command);
                    }
                }

                // Code Files
                this.listCodeFiles.Items.Clear();

                foreach (string codeFile in project.CodeFiles)
                {
                    this.listCodeFiles.Items.Add(codeFile);
                }
            }
        }
        
        private void treeViewProjectHierarchy_AfterSelect(object sender, TreeViewEventArgs e)
        {
            m_selectedProject = this.treeViewProjectHierarchy.SelectedNode.Text;
            UpdateControlsAfterSelection();
        }

        private void comboBoxConfigurations_SelectedIndexChanged(object sender, EventArgs e)
        {
            m_selectedConfiguration = this.comboBoxConfigurations.SelectedItem as string;
            UpdateControlsAfterSelection();
        }

        private void buttonGenerate_Click(object sender, EventArgs e)
        {
            MakefileGenerator generator = new MakefileGenerator();
            string workspaceMakefileContent = generator.GenerateWorkspaceMakefileFromModel(m_model);

            string workspaceMakefilePath = this.textBoxWorkspacePath.Text + ".mak";

            TextWriter workspaceWriter = new StreamWriter(new FileStream(workspaceMakefilePath, FileMode.Create), Encoding.ASCII);
            workspaceWriter.Write(workspaceMakefileContent);
            workspaceWriter.Close();

            foreach (var project in m_model.Projects)
	        {
                string projectMakefilePath = Path.GetDirectoryName(this.textBoxWorkspacePath.Text) + Path.DirectorySeparatorChar + project.Path + ".mak";

                string projectMakefileContent = generator.GenerateProjectMakefileFromModel(project);

                TextWriter projectWriter = new StreamWriter(new FileStream(projectMakefilePath, FileMode.Create), Encoding.ASCII);
                projectWriter.Write(projectMakefileContent);
                projectWriter.Close();
	        } 
        }
    }
}
