namespace MakefileFromCodeLite
{
    partial class Form1
    {
        /// <summary>
        /// Variable del diseñador requerida.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Limpiar los recursos que se estén utilizando.
        /// </summary>
        /// <param name="disposing">true si los recursos administrados se deben eliminar; false en caso contrario, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Código generado por el Diseñador de Windows Forms

        /// <summary>
        /// Método necesario para admitir el Diseñador. No se puede modificar
        /// el contenido del método con el editor de código.
        /// </summary>
        private void InitializeComponent()
        {
            this.openFileDialogWorkspace = new System.Windows.Forms.OpenFileDialog();
            this.splitContainer1 = new System.Windows.Forms.SplitContainer();
            this.buttonGenerate = new System.Windows.Forms.Button();
            this.comboBoxConfigurations = new System.Windows.Forms.ComboBox();
            this.buttonPick = new System.Windows.Forms.Button();
            this.textBoxWorkspacePath = new System.Windows.Forms.TextBox();
            this.treeViewProjectHierarchy = new System.Windows.Forms.TreeView();
            this.label8 = new System.Windows.Forms.Label();
            this.label7 = new System.Windows.Forms.Label();
            this.label6 = new System.Windows.Forms.Label();
            this.label5 = new System.Windows.Forms.Label();
            this.label4 = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.label1 = new System.Windows.Forms.Label();
            this.textBoxIntermediaryDir = new System.Windows.Forms.TextBox();
            this.textBoxOutput = new System.Windows.Forms.TextBox();
            this.textBoxDefinitions = new System.Windows.Forms.TextBox();
            this.textBoxLinkerOptions = new System.Windows.Forms.TextBox();
            this.textBoxCompilerOptions = new System.Windows.Forms.TextBox();
            this.listIncludeDirectories = new System.Windows.Forms.ListBox();
            this.listLibraryDirectories = new System.Windows.Forms.ListBox();
            this.listLibraries = new System.Windows.Forms.ListBox();
            this.listCodeFiles = new System.Windows.Forms.ListBox();
            this.listPrebuild = new System.Windows.Forms.ListBox();
            this.label9 = new System.Windows.Forms.Label();
            this.listPostbuild = new System.Windows.Forms.ListBox();
            this.label10 = new System.Windows.Forms.Label();
            this.label11 = new System.Windows.Forms.Label();
            ((System.ComponentModel.ISupportInitialize)(this.splitContainer1)).BeginInit();
            this.splitContainer1.Panel1.SuspendLayout();
            this.splitContainer1.Panel2.SuspendLayout();
            this.splitContainer1.SuspendLayout();
            this.SuspendLayout();
            // 
            // openFileDialogWorkspace
            // 
            this.openFileDialogWorkspace.Filter = "CodeLite workspaces|*.workspace|CodeLite projects|*.project";
            this.openFileDialogWorkspace.Title = "Select the workrspace to parse";
            // 
            // splitContainer1
            // 
            this.splitContainer1.Dock = System.Windows.Forms.DockStyle.Fill;
            this.splitContainer1.Location = new System.Drawing.Point(0, 0);
            this.splitContainer1.Name = "splitContainer1";
            // 
            // splitContainer1.Panel1
            // 
            this.splitContainer1.Panel1.Controls.Add(this.buttonGenerate);
            this.splitContainer1.Panel1.Controls.Add(this.comboBoxConfigurations);
            this.splitContainer1.Panel1.Controls.Add(this.buttonPick);
            this.splitContainer1.Panel1.Controls.Add(this.textBoxWorkspacePath);
            this.splitContainer1.Panel1.Controls.Add(this.treeViewProjectHierarchy);
            // 
            // splitContainer1.Panel2
            // 
            this.splitContainer1.Panel2.Controls.Add(this.label10);
            this.splitContainer1.Panel2.Controls.Add(this.label9);
            this.splitContainer1.Panel2.Controls.Add(this.label8);
            this.splitContainer1.Panel2.Controls.Add(this.label7);
            this.splitContainer1.Panel2.Controls.Add(this.label6);
            this.splitContainer1.Panel2.Controls.Add(this.label5);
            this.splitContainer1.Panel2.Controls.Add(this.label4);
            this.splitContainer1.Panel2.Controls.Add(this.label3);
            this.splitContainer1.Panel2.Controls.Add(this.label2);
            this.splitContainer1.Panel2.Controls.Add(this.label11);
            this.splitContainer1.Panel2.Controls.Add(this.label1);
            this.splitContainer1.Panel2.Controls.Add(this.textBoxIntermediaryDir);
            this.splitContainer1.Panel2.Controls.Add(this.textBoxOutput);
            this.splitContainer1.Panel2.Controls.Add(this.textBoxDefinitions);
            this.splitContainer1.Panel2.Controls.Add(this.textBoxLinkerOptions);
            this.splitContainer1.Panel2.Controls.Add(this.textBoxCompilerOptions);
            this.splitContainer1.Panel2.Controls.Add(this.listIncludeDirectories);
            this.splitContainer1.Panel2.Controls.Add(this.listLibraryDirectories);
            this.splitContainer1.Panel2.Controls.Add(this.listPostbuild);
            this.splitContainer1.Panel2.Controls.Add(this.listPrebuild);
            this.splitContainer1.Panel2.Controls.Add(this.listLibraries);
            this.splitContainer1.Panel2.Controls.Add(this.listCodeFiles);
            this.splitContainer1.Size = new System.Drawing.Size(1176, 855);
            this.splitContainer1.SplitterDistance = 250;
            this.splitContainer1.TabIndex = 1;
            // 
            // buttonGenerate
            // 
            this.buttonGenerate.Location = new System.Drawing.Point(67, 96);
            this.buttonGenerate.Name = "buttonGenerate";
            this.buttonGenerate.Size = new System.Drawing.Size(115, 23);
            this.buttonGenerate.TabIndex = 4;
            this.buttonGenerate.Text = "Generate makefiles";
            this.buttonGenerate.UseVisualStyleBackColor = true;
            this.buttonGenerate.Click += new System.EventHandler(this.buttonGenerate_Click);
            // 
            // comboBoxConfigurations
            // 
            this.comboBoxConfigurations.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.comboBoxConfigurations.FormattingEnabled = true;
            this.comboBoxConfigurations.Location = new System.Drawing.Point(3, 69);
            this.comboBoxConfigurations.Name = "comboBoxConfigurations";
            this.comboBoxConfigurations.Size = new System.Drawing.Size(239, 21);
            this.comboBoxConfigurations.TabIndex = 3;
            this.comboBoxConfigurations.SelectedIndexChanged += new System.EventHandler(this.comboBoxConfigurations_SelectedIndexChanged);
            // 
            // buttonPick
            // 
            this.buttonPick.Location = new System.Drawing.Point(67, 38);
            this.buttonPick.Name = "buttonPick";
            this.buttonPick.Size = new System.Drawing.Size(115, 23);
            this.buttonPick.TabIndex = 2;
            this.buttonPick.Text = "Pick workspace";
            this.buttonPick.UseVisualStyleBackColor = true;
            this.buttonPick.Click += new System.EventHandler(this.buttonPick_Click);
            // 
            // textBoxWorkspacePath
            // 
            this.textBoxWorkspacePath.BackColor = System.Drawing.SystemColors.Window;
            this.textBoxWorkspacePath.Location = new System.Drawing.Point(4, 12);
            this.textBoxWorkspacePath.Name = "textBoxWorkspacePath";
            this.textBoxWorkspacePath.ReadOnly = true;
            this.textBoxWorkspacePath.Size = new System.Drawing.Size(238, 20);
            this.textBoxWorkspacePath.TabIndex = 1;
            // 
            // treeViewProjectHierarchy
            // 
            this.treeViewProjectHierarchy.Location = new System.Drawing.Point(3, 125);
            this.treeViewProjectHierarchy.Name = "treeViewProjectHierarchy";
            this.treeViewProjectHierarchy.Size = new System.Drawing.Size(239, 721);
            this.treeViewProjectHierarchy.TabIndex = 0;
            this.treeViewProjectHierarchy.AfterSelect += new System.Windows.Forms.TreeViewEventHandler(this.treeViewProjectHierarchy_AfterSelect);
            // 
            // label8
            // 
            this.label8.AutoSize = true;
            this.label8.Location = new System.Drawing.Point(4, 545);
            this.label8.Name = "label8";
            this.label8.Size = new System.Drawing.Size(46, 13);
            this.label8.TabIndex = 7;
            this.label8.Text = "Libraries";
            // 
            // label7
            // 
            this.label7.AutoSize = true;
            this.label7.Location = new System.Drawing.Point(4, 317);
            this.label7.Name = "label7";
            this.label7.Size = new System.Drawing.Size(95, 13);
            this.label7.TabIndex = 7;
            this.label7.Text = "Include Directories";
            // 
            // label6
            // 
            this.label6.AutoSize = true;
            this.label6.Location = new System.Drawing.Point(3, 434);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(91, 13);
            this.label6.TabIndex = 7;
            this.label6.Text = "Library Directories";
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Location = new System.Drawing.Point(4, 236);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(56, 13);
            this.label5.TabIndex = 7;
            this.label5.Text = "Definitions";
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(3, 167);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(73, 13);
            this.label4.TabIndex = 7;
            this.label4.Text = "Linker options";
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(3, 98);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(84, 13);
            this.label3.TabIndex = 7;
            this.label3.Text = "Compiler options";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(3, 56);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(117, 13);
            this.label2.TabIndex = 7;
            this.label2.Text = "Intermediary Directories";
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(486, 15);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(74, 13);
            this.label1.TabIndex = 7;
            this.label1.Text = "Files in project";
            // 
            // textBoxIntermediaryDir
            // 
            this.textBoxIntermediaryDir.BackColor = System.Drawing.SystemColors.Window;
            this.textBoxIntermediaryDir.Location = new System.Drawing.Point(2, 72);
            this.textBoxIntermediaryDir.Name = "textBoxIntermediaryDir";
            this.textBoxIntermediaryDir.ReadOnly = true;
            this.textBoxIntermediaryDir.Size = new System.Drawing.Size(480, 20);
            this.textBoxIntermediaryDir.TabIndex = 6;
            // 
            // textBoxOutput
            // 
            this.textBoxOutput.BackColor = System.Drawing.SystemColors.Window;
            this.textBoxOutput.Location = new System.Drawing.Point(3, 30);
            this.textBoxOutput.Name = "textBoxOutput";
            this.textBoxOutput.ReadOnly = true;
            this.textBoxOutput.Size = new System.Drawing.Size(479, 20);
            this.textBoxOutput.TabIndex = 5;
            // 
            // textBoxDefinitions
            // 
            this.textBoxDefinitions.Location = new System.Drawing.Point(4, 255);
            this.textBoxDefinitions.Multiline = true;
            this.textBoxDefinitions.Name = "textBoxDefinitions";
            this.textBoxDefinitions.Size = new System.Drawing.Size(480, 50);
            this.textBoxDefinitions.TabIndex = 4;
            // 
            // textBoxLinkerOptions
            // 
            this.textBoxLinkerOptions.Location = new System.Drawing.Point(3, 183);
            this.textBoxLinkerOptions.Multiline = true;
            this.textBoxLinkerOptions.Name = "textBoxLinkerOptions";
            this.textBoxLinkerOptions.Size = new System.Drawing.Size(480, 50);
            this.textBoxLinkerOptions.TabIndex = 4;
            // 
            // textBoxCompilerOptions
            // 
            this.textBoxCompilerOptions.Location = new System.Drawing.Point(2, 114);
            this.textBoxCompilerOptions.Multiline = true;
            this.textBoxCompilerOptions.Name = "textBoxCompilerOptions";
            this.textBoxCompilerOptions.Size = new System.Drawing.Size(480, 50);
            this.textBoxCompilerOptions.TabIndex = 4;
            // 
            // listIncludeDirectories
            // 
            this.listIncludeDirectories.FormattingEnabled = true;
            this.listIncludeDirectories.Location = new System.Drawing.Point(2, 340);
            this.listIncludeDirectories.Name = "listIncludeDirectories";
            this.listIncludeDirectories.Size = new System.Drawing.Size(480, 82);
            this.listIncludeDirectories.TabIndex = 3;
            // 
            // listLibraryDirectories
            // 
            this.listLibraryDirectories.FormattingEnabled = true;
            this.listLibraryDirectories.Location = new System.Drawing.Point(2, 458);
            this.listLibraryDirectories.Name = "listLibraryDirectories";
            this.listLibraryDirectories.Size = new System.Drawing.Size(480, 82);
            this.listLibraryDirectories.TabIndex = 3;
            // 
            // listLibraries
            // 
            this.listLibraries.FormattingEnabled = true;
            this.listLibraries.Location = new System.Drawing.Point(2, 561);
            this.listLibraries.Name = "listLibraries";
            this.listLibraries.Size = new System.Drawing.Size(480, 82);
            this.listLibraries.TabIndex = 2;
            // 
            // listCodeFiles
            // 
            this.listCodeFiles.FormattingEnabled = true;
            this.listCodeFiles.Location = new System.Drawing.Point(489, 31);
            this.listCodeFiles.Name = "listCodeFiles";
            this.listCodeFiles.Size = new System.Drawing.Size(421, 810);
            this.listCodeFiles.TabIndex = 1;
            // 
            // listPrebuild
            // 
            this.listPrebuild.FormattingEnabled = true;
            this.listPrebuild.Location = new System.Drawing.Point(2, 663);
            this.listPrebuild.Name = "listPrebuild";
            this.listPrebuild.Size = new System.Drawing.Size(480, 82);
            this.listPrebuild.TabIndex = 2;
            // 
            // label9
            // 
            this.label9.AutoSize = true;
            this.label9.Location = new System.Drawing.Point(4, 647);
            this.label9.Name = "label9";
            this.label9.Size = new System.Drawing.Size(103, 13);
            this.label9.TabIndex = 7;
            this.label9.Text = "Pre-build Commands";
            // 
            // listPostbuild
            // 
            this.listPostbuild.FormattingEnabled = true;
            this.listPostbuild.Location = new System.Drawing.Point(2, 764);
            this.listPostbuild.Name = "listPostbuild";
            this.listPostbuild.Size = new System.Drawing.Size(480, 82);
            this.listPostbuild.TabIndex = 2;
            // 
            // label10
            // 
            this.label10.AutoSize = true;
            this.label10.Location = new System.Drawing.Point(4, 748);
            this.label10.Name = "label10";
            this.label10.Size = new System.Drawing.Size(108, 13);
            this.label10.TabIndex = 7;
            this.label10.Text = "Post-build Commands";
            // 
            // label11
            // 
            this.label11.AutoSize = true;
            this.label11.Location = new System.Drawing.Point(3, 15);
            this.label11.Name = "label11";
            this.label11.Size = new System.Drawing.Size(39, 13);
            this.label11.TabIndex = 7;
            this.label11.Text = "Output";
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(1176, 855);
            this.Controls.Add(this.splitContainer1);
            this.Name = "Form1";
            this.Text = "Makefiles from CodeLite projects Generator";
            this.Load += new System.EventHandler(this.Form1_Load);
            this.splitContainer1.Panel1.ResumeLayout(false);
            this.splitContainer1.Panel1.PerformLayout();
            this.splitContainer1.Panel2.ResumeLayout(false);
            this.splitContainer1.Panel2.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.splitContainer1)).EndInit();
            this.splitContainer1.ResumeLayout(false);
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.OpenFileDialog openFileDialogWorkspace;
        private System.Windows.Forms.SplitContainer splitContainer1;
        private System.Windows.Forms.Button buttonPick;
        private System.Windows.Forms.TextBox textBoxWorkspacePath;
        private System.Windows.Forms.TreeView treeViewProjectHierarchy;
        private System.Windows.Forms.TextBox textBoxLinkerOptions;
        private System.Windows.Forms.TextBox textBoxCompilerOptions;
        private System.Windows.Forms.ListBox listLibraryDirectories;
        private System.Windows.Forms.ListBox listCodeFiles;
        private System.Windows.Forms.Button buttonGenerate;
        private System.Windows.Forms.ComboBox comboBoxConfigurations;
        private System.Windows.Forms.ListBox listIncludeDirectories;
        private System.Windows.Forms.TextBox textBoxIntermediaryDir;
        private System.Windows.Forms.TextBox textBoxOutput;
        private System.Windows.Forms.ListBox listLibraries;
        private System.Windows.Forms.Label label6;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.TextBox textBoxDefinitions;
        private System.Windows.Forms.Label label8;
        private System.Windows.Forms.Label label7;
        private System.Windows.Forms.Label label10;
        private System.Windows.Forms.Label label9;
        private System.Windows.Forms.ListBox listPostbuild;
        private System.Windows.Forms.ListBox listPrebuild;
        private System.Windows.Forms.Label label11;
    }
}

