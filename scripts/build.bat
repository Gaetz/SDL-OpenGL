::@echo off
 
set buildDir=%~dp0..\build
 
if not exist %buildDir% mkdir %buildDir%
 
pushd %buildDir%
 
:: compiler input
set objDir=.\obj\
set outputExe=%buildDir%/Tetris.exe

set files=..\src\main.cpp ..\src\board.cpp ..\src\game.cpp ..\src\pieces.cpp ..\src\shader.cpp ..\src\texture.cpp 
set files=..\src\renderer_geometry.cpp ..\src\renderer_sprite.cpp ..\src\resource_manager.cpp ..\src\scene_game.cpp %files%

if not exist %objDir% mkdir %objDir%
 
set INCLUDE=%scriptsDir%-I..\external\SDL2-2.0.7\include
set INCLUDE=%scriptsDir%-I..\external\SDL2_image-2.0.2\include %INCLUDE%
set INCLUDE=%scriptsDir%-I..\external\SDL2_mixer-2.0.2\include %INCLUDE%
set INCLUDE=%scriptsDir%-I..\external\SDL2_ttf-2.0.14\include %INCLUDE%
set INCLUDE=%scriptsDir%-I..\external\glew-2.1.0\include %INCLUDE%
set INCLUDE=%scriptsDir%-I..\external\glm-0.9.5 %INCLUDE%

set LIB=%scriptsDir%-L..\external\SDL2-2.0.7\lib\x64
set LIB=%scriptsDir%-L..\external\SDL2_image-2.0.2\lib\x64 %LIB%
set LIB=%scriptsDir%-L..\external\SDL2_mixer-2.0.2\lib\x64 %LIB%
set LIB=%scriptsDir%-L..\external\SDL2_ttf-2.0.14\lib\x64 %LIB%
set LIB=%scriptsDir%-L..\external\glew-2.1.0\lib\Release\x64 %LIB%

set Librairies=-lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer -llibpng16-16 -lglew32 -lzlib1 -lopengl32

g++ -g -Wall %files% %INCLUDE% %LIB% %Librairies% -o %outputExe%

:: Copy dependencies
xcopy /y ..\external\SDL2-2.0.7\lib\x64\SDL2.dll .
xcopy /y ..\external\SDL2_image-2.0.2\lib\x64\SDL2_image.dll .
xcopy /y ..\external\SDL2_mixer-2.0.2\lib\x64\SDL2_mixer.dll .
xcopy /y ..\external\SDL2_ttf-2.0.14\lib\x64\SDL2_ttf.dll .
xcopy /y ..\external\glew-2.1.0\bin\Release\x64\glew32.dll .
xcopy /y ..\external\SDL2_image-2.0.2\lib\x64\libpng16-16.dll .
xcopy /y ..\external\SDL2_image-2.0.2\lib\x64\zlib1.dll .

mkdir %buildDir%\assets
xcopy /y /s ..\assets %buildDir%\assets

popd