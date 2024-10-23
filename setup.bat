@echo off
set glfw=https://github.com/glfw/glfw.git
set lunasvg=https://github.com/sammycage/lunasvg.git
set mini=https://github.com/pulzed/mINI.git
set spdlog=https://github.com/gabime/spdlog.git
set imgui=https://github.com/ocornut/imgui.git



echo -- Cloning glfw github repo
git clone --depth 1 %glfw%
echo.
echo -- Cloning spdlog
git clone -b v1.14.1 --single-branch %spdlog%  --depth 1 ./packages/spdlog
echo.
echo -- Cloning imgui
git clone  --branch v1.91.4 --single-branch %imgui% --depth 1
echo.
echo -- Cloning lunasvg
git clone -b v2.3.9 --single-branch %lunasvg% --depth 1
echo.
echo -- Cloning mini
git clone --depth 1 %mini% ./packages/mINI
echo.



if exist glfw (
	echo.
	echo Setting Up GLFW
	move /y ".\glfw\deps" ".\packages\glfw"
	move /y ".\glfw\include" ".\packages\glfw"
	move /y ".\glfw\src" ".\packages\glfw"
) else (
	echo [ GLFW ] No directory found
	exit /b
)

if exist lunasvg (
	echo.
	echo Setting Up LunaSVG
	move /y ".\lunasvg\*" ".\packages\lunasvg"
	move /y ".\lunasvg\3rdparty" ".\packages\lunasvg"
	move /y ".\lunasvg\include" ".\packages\lunasvg"
	move /y ".\lunasvg\source" ".\packages\lunasvg"
) else (
	echo [ LunaSVG ] No directory found
	exit /b
)




if not exist .\packages\spdlog mkdir .\packages\spdlog
if not exist .\packages\imgui mkdir .\packages\imgui


echo -- Setting up imgui
move /y ".\imgui\*.cpp" ".\packages\imgui"
move /y ".\imgui\*.h" ".\packages\imgui"
move /y ".\imgui\backends\imgui_impl_opengl2.cpp" ".\packages\imgui"
move /y ".\imgui\backends\imgui_impl_opengl2.h" ".\packages\imgui"
move /y ".\imgui\backends\imgui_impl_opengl3.cpp" ".\packages\imgui"
move /y ".\imgui\backends\imgui_impl_opengl3.h" ".\packages\imgui"
move /y ".\imgui\backends\imgui_impl_opengl3_loader.h" ".\packages\imgui"
move /y ".\imgui\backends\imgui_impl_glfw.cpp" ".\packages\imgui"
move /y ".\imgui\backends\imgui_impl_glfw.h" ".\packages\imgui"

echo -- Cleaning
rmdir /s /q imgui
rmdir /s /q glfw
rmdir /s /q lunasvg
build