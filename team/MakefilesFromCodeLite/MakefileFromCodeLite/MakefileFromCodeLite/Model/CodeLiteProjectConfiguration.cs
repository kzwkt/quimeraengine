using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace MakefileFromCodeLite.Model
{

    enum OutputType
    {
        Executable,
        DynamicLibrary,
        StaticLibrary,
        WTF
    }

    class CodeLiteProjectConfiguration
    {
        public string Name;
        public string CompilerOptions;
        public string LinkerOptions;
        public List<string> IncludePaths;
        public List<string> LibraryPaths;
        public List<string> Libraries;
        public List<string> Preprocessors;
        public string OutputFile;
        public string IntermediateDirectory;
        public List<string> PreBuildCommands;
        public List<string> PostBuildCommands;
        public OutputType Type;
    }
}
