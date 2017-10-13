-- GENIe solution to build the project.
-- Julio Marcelo Picardo <juliomarcelopicardo@gmail.com>
-- Antonio Diaz <antoniozero@outlook.com>

PROJ_DIR = path.getabsolute("../")

solution "SilverLynx_Solution"
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
      "DEBUGUEA_PREMOH"
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
      "DEJATE_DE_DEBUGUEOS"
	  }

  configuration "x32"
    libdirs     { "$(DXSDK_DIR)Lib/x86" }

  configuration "x64"
    libdirs     { "$(DXSDK_DIR)Lib/x64" }

project "SilverLynx"
  kind "staticlib"
  language "C++"


  includedirs {
    "$(DXSDK_DIR)Include",
    path.join(PROJ_DIR, "include/"),
	path.join(PROJ_DIR, "external/"),
	path.join(PROJ_DIR, "external/imgui/")
  }

  files {
    path.join(PROJ_DIR, "src/*.cc"),
    path.join(PROJ_DIR, "src/core/*.cc"),
    path.join(PROJ_DIR, "src/SilverLynx/*.cc"),
	path.join(PROJ_DIR, "src/core/components/*.cc"),
    path.join(PROJ_DIR, "include/*.h"),
    path.join(PROJ_DIR, "include/core/*.h"),
    path.join(PROJ_DIR, "include/SilverLynx/*.h"),
	path.join(PROJ_DIR, "include/core/components/*.h"),
	path.join(PROJ_DIR, "external/imgui/*.cpp"),
	path.join(PROJ_DIR, "external/imgui/*.h"),
    path.join(PROJ_DIR, "data/geometries/*.*"),
    path.join(PROJ_DIR, "data/materials/*.*"),
    path.join(PROJ_DIR, "data/textures/*.*")
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
  }

  files {
    path.join(PROJ_DIR, "data/"..name.."/*.*"),
    path.join(PROJ_DIR, "examples/"..name.."/*.*"),
  }

  configuration "Debug"
    targetdir ("../bin/")
    links {
      "dxgi",
			"d3d11",
			"d3dx11",
			"d3dx10",
			"SilverLynx",
	  		"d3dcompiler"
	  }

  configuration "Release"
    targetdir ("../bin/")
  	links {
      "dxgi",
			"d3d11",
			"d3dx11",
			"d3dx10",
			"SilverLynx",
	  		"d3dcompiler"
  	}
--[[

  configuration "x32"
    libdirs     { "$(DXSDK_DIR)Lib/x86" }

  configuration "x64"
    libdirs     { "$(DXSDK_DIR)Lib/x64" }
]]

end

-- PROJECTS
GenerateProject("01_InitWindow")
