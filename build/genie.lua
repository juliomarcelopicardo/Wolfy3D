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
  	path.join(PROJ_DIR, "src/"),
    --[[
    -- LUA
    path.join(PROJ_DIR, "deps/lua/include/"),
    path.join(PROJ_DIR, "deps/lua/src/"),
    -- IMGUI
    path.join(PROJ_DIR, "deps/imgui/include/"),
    path.join(PROJ_DIR, "deps/imgui/src/"),
    -- GLM
    path.join(PROJ_DIR, "deps/glm/include/"),
    path.join(PROJ_DIR, "deps/glm/src/"),
    ]]
  }

  files {
    path.join(PROJ_DIR, "src/*.cc"),
    path.join(PROJ_DIR, "include/*.h"),
    path.join(PROJ_DIR, "include/core/*.h"),
    path.join(PROJ_DIR, "include/utils/*.h"),
    path.join(PROJ_DIR, "assets/geometries/*.*"),
    path.join(PROJ_DIR, "assets/materials/*.*"),
    path.join(PROJ_DIR, "assets/textures/*.*"),
    --[[
    -- LUA
    path.join(PROJ_DIR, "deps/lua/src/*.*"),
    -- IMGUI
    path.join(PROJ_DIR, "deps/imgui/src/*.*"),
    -- GLM
    path.join(PROJ_DIR, "deps/glm/include/GLM/detail/*.*"),
    path.join(PROJ_DIR, "deps/glm/include/GLM/gtc/*.*"),
    path.join(PROJ_DIR, "deps/glm/include/GLM/gtx/*.*"),
    path.join(PROJ_DIR, "deps/glm/include/GLM/simd/*.*"),
    path.join(PROJ_DIR, "deps/glm/include/GLM/*.*"),
    path.join(PROJ_DIR, "deps/glm/src/*.cpp"),
    ]]

  }

  configuration "Debug"
    targetdir ("../bin/")
    links {
	    "dxgi",
			"d3d11",
			"d3dx11",
			"d3dx10"
	  }

  configuration "Release"
    targetdir ("../bin/")
  	links {
  	  "dxgi",
			"d3d11",
			"d3dx11",
			"d3dx10"
  	}

-- Function to generate the different mains or projects.
function GenerateProject(name)

  project(name)
	kind "WindowedApp"
  flags { "WinMain" }

  includedirs {
    "$(DXSDK_DIR)Include",
    path.join(PROJ_DIR, "include/"),
    --[[
    path.join(PROJ_DIR, "build/lua_files/"),
    path.join(PROJ_DIR, "deps/lua/include/"),
    path.join(PROJ_DIR, "deps/imgui/include/"),
    path.join(PROJ_DIR, "deps/glm/include/"),
    ]]
  }

  files {
    path.join(PROJ_DIR, "assets/"..name.."/*.*"),
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
	  }

  configuration "Release"
    targetdir ("../bin/")
  	links {
      "dxgi",
			"d3d11",
			"d3dx11",
			"d3dx10",
      "SilverLynx",
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
