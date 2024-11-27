OutputDir = {}
OutputDir["_Completer_"] = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"
OutputDir["Binaries"] = "%{wks.location}/Binaries/%{OutputDir._Completer_}"
OutputDir["Intermediates"] = "%{wks.location}/Binaries-Int/%{OutputDir._Completer_}"

ProjectDir = {}
ProjectDir["Core"] = "%{wks.location}/Core"
ProjectDir["Runtime"] = "%{wks.location}/Runtime"
ProjectDir["jsoncpp"] = "%{wks.location}/Vendor/jsoncpp"

IncludeDir = {}
IncludeDir["Core"] = "%{ProjectDir.Core}/Source"
IncludeDir["Runtime"] = "%{ProjectDir.Runtime}/Source"
IncludeDir["jsoncpp"] = "%{ProjectDir.jsoncpp}/include"
IncludeDir["fmtlib"] = "%{wks.location}/Vendor/fmtlib/include"
IncludeDir["spdlog"] = "%{wks.location}/Vendor/spdlog/include"
IncludeDir["glm"] = "%{wks.location}/vendor/glm"

SourceDir = {}
SourceDir["Core"] = "%{IncludeDir.Core}"
SourceDir["Runtime"] = "%{IncludeDir.Runtime}"
SourceDir["jsoncpp"] = "%{ProjectDir.jsoncpp}/src"
