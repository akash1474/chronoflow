-- Building
-- MsBuild XPlayer.sln /p:configuration=Release

workspace "ProjectOpenGL"
   architecture "x64"
   configurations { "Debug", "Release", "Dist" }


outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

includeDirs={}
includeDirs["glfw"]="packages/glfw/include"
includeDirs["SpdLog"]="packages/spdlog/include"
includeDirs["ImGui"]="packages/imgui"
includeDirs["Mini"]="packages/mINI/src/mini"
includeDirs["LunaSVG"]="packages/lunasvg/include"
includeDirs["ImPlot"]="packages/implot"
includeDirs["Json"]="packages/nlohmann"

-- /MP -- Multithreaded build 
-- /MT -- Static Linking. Defines _MT 
-- /MD -- Dynamic Linking. Defines _MT and _DLL 
include "packages/glfw"
include "packages/imgui"
include "packages/lunasvg"
include "packages/implot"

project "project"
   kind "ConsoleApp"
   language "C++"
   cppdialect "C++17"
   targetdir "bin"
   objdir "bin/obj"
   pchheader "pch.h"
   pchsource "src/pch.cpp"

   links {
      "glfw","ImGui","opengl32","LunaSVG","ImPlot","userenv","Shell32","dwmapi"
   }

   includedirs{
      "src",
      "%{includeDirs.glfw}",
      "%{includeDirs.ImGui}",
      "%{includeDirs.LunaSVG}",
      "%{includeDirs.SpdLog}",
      "%{includeDirs.ImPlot}",
      "%{includeDirs.Json}",
   }

   files { 
      "src/**.cpp"
   }


   filter "system:windows"
      systemversion "latest"

   filter "configurations:Debug"
      runtime "Debug"
      symbols "On"
      staticruntime "On"
      optimize "Off"
      characterset ("Unicode") -- Default
      buildoptions { "/MP","/DEBUG:FULL","/utf-8" } --"/utf-8" - tells compiler to interprete string literals as utf8
      defines {"GL_DEBUG"} 

   filter {"configurations:Release"}
      runtime "Release"
      optimize "On"
      symbols "Off"
      staticruntime "On"
      buildoptions { "/MP","/utf-8" }
      defines {"GL_DEBUG","_CRT_SECURE_NO_WARNINGS"}

   filter "configurations:Dist"
      kind "WindowedApp"
      runtime "Release"
      optimize "On"
      symbols "Off"
      staticruntime "On"
      buildoptions { "/MP","/utf-8"}
      linkoptions {"/ENTRY:mainCRTStartup"}
      files { 'setup.rc', '**.ico' }
      vpaths { ['./*'] = { '*.rc', '**.ico' }}
