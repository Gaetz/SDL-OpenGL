@echo off
 
:: Create build dir
set releaseDir=%~dp0..\release
if not exist %releaseDir% mkdir %releaseDir%
pushd %releaseDir%

:: Create obj dir
set objDir=.\obj
if not exist %objDir% mkdir %objDir%

:: Needed folders
set extDir=%~dp0..\external
set scriptDir=%~dp0..\scripts

:: Use make to build default target
cd %scriptDir%\
mingw32-make release

cd %releaseDir%

:: Copy dependencies
if not exist %releaseDir%\SDL2.dll xcopy /y %extDir%\SDL2-2.0.7\lib\x64\SDL2.dll .
if not exist %releaseDir%\SDL2_image.dll xcopy /y %extDir%\SDL2_image-2.0.2\lib\x64\SDL2_image.dll .
if not exist %releaseDir%\SDL2_mixer.dll xcopy /y %extDir%\SDL2_mixer-2.0.2\lib\x64\SDL2_mixer.dll .
if not exist %releaseDir%\SDL2_ttf.dll xcopy /y %extDir%\SDL2_ttf-2.0.14\lib\x64\SDL2_ttf.dll .
if not exist %releaseDir%\glew32.dll xcopy /y %extDir%\glew-2.1.0\bin\Release\x64\glew32.dll .
if not exist %releaseDir%\libpng16-16.dll xcopy /y %extDir%\SDL2_image-2.0.2\lib\x64\libpng16-16.dll .
if not exist %releaseDir%\zlib1.dll xcopy /y %extDir%\SDL2_image-2.0.2\lib\x64\zlib1.dll .

:: Copy assets
set assetsDir=%~dp0..\assets

:: Copy assets
if not exist %releaseDir%\assets mkdir %releaseDir%\assets
xcopy /y /s %assetsDir% %releaseDir%\assets

:: Remove release obj files
rd /s /q %releaseDir%\%objDir%

popd