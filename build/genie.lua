-- GENIe solution to build the project.
-- Julio Marcelo Picardo <juliomarcelopicardo@gmail.com>

PROJ_DIR = path.getabsolute("../")

solution "Wolfy3D_Solution"
  configurations {
    "Release",
    "Debug",
  }
  language "C++"
  platforms { "x32", "x64" }

  configuration "Debug"
    flags { "Symbols" }
  	targetsuffix "-d"
  	links {
      "dxgi",
			"d3d11",
			"d3dx11",
			"d3dx10"
  	}
    defines {
      "DEBUG_MODE"
	  }

  configuration "Release"
    flags { "OptimizeSize" }
  	links {
      "dxgi",
			"d3d11",
			"d3dx11",
			"d3dx10"
  	}
    defines {
      "RELEASE_MODE"
	  }

  configuration "x32"
    libdirs     { "$(DXSDK_DIR)Lib/x86" }

  configuration "x64"
    libdirs     { "$(DXSDK_DIR)Lib/x64" }

project "Wolfy3D"
  kind "staticlib"
  language "C++"


  includedirs {
    "$(DXSDK_DIR)Include",
    path.join(PROJ_DIR, "include/"),
	  path.join(PROJ_DIR, "external/"),
    path.join(PROJ_DIR, "external/imgui/"),
    path.join(PROJ_DIR, "external/tinyxml2/")
  }

  files {
    path.join(PROJ_DIR, "src/*.cc"),
    path.join(PROJ_DIR, "src/core/*.cc"),
    path.join(PROJ_DIR, "src/Wolfy3D/*.cc"),
	  path.join(PROJ_DIR, "src/core/components/*.cc"),
    path.join(PROJ_DIR, "include/*.h"),
    path.join(PROJ_DIR, "include/core/*.h"),
    path.join(PROJ_DIR, "include/Wolfy3D/*.h"),
	  path.join(PROJ_DIR, "include/core/components/*.h"),
	  path.join(PROJ_DIR, "external/imgui/*.cpp"),
    path.join(PROJ_DIR, "external/imgui/*.h"),
    path.join(PROJ_DIR, "external/tinyxml2/*.cpp"),
	  path.join(PROJ_DIR, "external/tinyxml2/*.h"),
    path.join(PROJ_DIR, "data/**.**"),
  }

  configuration "Debug"
    targetdir ("../bin/")
    links {
	    "dxgi",
      "d3d11",
      "d3dx11",
      "d3dx10",
      "d3dcompiler"
	  }

  configuration "Release"
    targetdir ("../bin/")
  	links {
  	  "dxgi",
      "d3d11",
      "d3dx11",
      "d3dx10",
      "d3dcompiler"
  	}

-- Function to generate the different mains or projects.
function GenerateProject(name)

  project(name)
	kind "WindowedApp"
  flags { "WinMain" }

  includedirs {
    "$(DXSDK_DIR)Include",
	  path.join(PROJ_DIR, "external/"),
    path.join(PROJ_DIR, "include/"),
    path.join(PROJ_DIR, "src/"),
	  path.join(PROJ_DIR, "examples/"..name.."/include/")
  }

  files {
    path.join(PROJ_DIR, "data/"..name.."/*.*"),
    path.join(PROJ_DIR, "examples/"..name.."/*.*"),
	  path.join(PROJ_DIR, "examples/"..name.."/src/*.*"),
	  path.join(PROJ_DIR, "examples/"..name.."/include/*.*"),
  }

  configuration "Debug"
    targetdir ("../bin/")
    links {
      "dxgi",
			"d3d11",
			"d3dx11",
			"d3dx10",
			"Wolfy3D",
	  	"d3dcompiler"
	  }

  configuration "Release"
    targetdir ("../bin/")
  	links {
      "dxgi",
			"d3d11",
			"d3dx11",
			"d3dx10",
			"Wolfy3D",
	  	"d3dcompiler"
  	}

end

-- PROJECTS
GenerateProject("00_Testing")
GenerateProject("01_Assignment")
