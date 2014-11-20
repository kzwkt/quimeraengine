using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace MakefileFromCodeLite.Model
{
    class CodeLiteProject
    {
        public string Name;
        public string Path;
        public List<string> CodeFiles;
        public List<Dependencies> Dependencies;
        public List<CodeLiteProjectConfiguration> Configurations;
        public CodeLiteProjectConfiguration GlobalConfiguration;
    }
}
