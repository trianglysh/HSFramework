OutputDir = {}
OutputDir["_Completer_"] = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"
OutputDir["Binaries"] = "%{wks.location}/Binaries/%{OutputDir._Completer_}"
OutputDir["Intermediates"] = "%{wks.location}/Binaries-Int/%{OutputDir._Completer_}"

ProjectDir = {}
ProjectDir["Core"] = "%{wks.location}/Core"
ProjectDir["Runtime"] = "%{wks.location}/Runtime"

IncludeDir = {}
IncludeDir["Core"] = "%{ProjectDir.Core}/Source"
IncludeDir["Runtime"] = "%{ProjectDir.Runtime}/Source"

SourceDir = {}
SourceDir["Core"] = "%{IncludeDir.Core}"
SourceDir["Runtime"] = "%{IncludeDir.Runtime}"
