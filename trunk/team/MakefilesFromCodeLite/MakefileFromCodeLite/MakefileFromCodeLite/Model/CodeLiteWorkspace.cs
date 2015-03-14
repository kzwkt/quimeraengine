using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace MakefileFromCodeLite.Model
{
    class CodeLiteWorkspace
    {
        public string Name;
        public List<CodeLiteProject> Projects;
        public List<WorkspaceConfiguration> Configurations;
    }

}
