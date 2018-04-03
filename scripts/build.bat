@echo off
 
:: Create build dir
set buildDir=%~dp0..\build
if not exist %buildDir% mkdir %buildDir%
pushd %buildDir%

set srcDir=%~dp0..\src
set extDir=%~dp0..\external

:: Compiler input
set objDir=.\obj\
set outputExe=%buildDir%/Tetris.exe

if not exist %objDir% mkdir %objDir%

:: Dependencies
set INCLUDE=%scriptsDir%-I%extDir%\SDL2-2.0.7\include
set INCLUDE=%scriptsDir%-I%extDir%\SDL2_image-2.0.2\include %INCLUDE%
set INCLUDE=%scriptsDir%-I%extDir%\SDL2_mixer-2.0.2\include %INCLUDE%
set INCLUDE=%scriptsDir%-I%extDir%\SDL2_ttf-2.0.14\include %INCLUDE%
set INCLUDE=%scriptsDir%-I%extDir%\glew-2.1.0\include %INCLUDE%
set INCLUDE=%scriptsDir%-I%extDir%\glm-0.9.5 %INCLUDE%

set LIB=%scriptsDir%-L%extDir%\SDL2-2.0.7\lib\x64
set LIB=%scriptsDir%-L%extDir%\SDL2_image-2.0.2\lib\x64 %LIB%
set LIB=%scriptsDir%-L%extDir%\SDL2_mixer-2.0.2\lib\x64 %LIB%
set LIB=%scriptsDir%-L%extDir%\SDL2_ttf-2.0.14\lib\x64 %LIB%
set LIB=%scriptsDir%-L%extDir%\glew-2.1.0\lib\Release\x64 %LIB%

set Librairies=-lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer -llibpng16-16 -lglew32 -lzlib1 -lopengl32

:: Compile everything (not optimal)
g++ -g -Wall -Wextra -c %srcDir%\shader.cpp -o %objDir%\shader.o %INCLUDE%
g++ -g -Wall -Wextra -c %srcDir%\main.cpp -o %objDir%\main.o %INCLUDE%
g++ -g -Wall -Wextra -c %srcDir%\board.cpp -o %objDir%\board.o %INCLUDE%
g++ -g -Wall -Wextra -c %srcDir%\game.cpp -o %objDir%\game.o %INCLUDE%
g++ -g -Wall -Wextra -c %srcDir%\pieces.cpp -o %objDir%\pieces.o %INCLUDE%
g++ -g -Wall -Wextra -c %srcDir%\renderer_geometry.cpp -o %objDir%\renderer_geometry.o %INCLUDE%
g++ -g -Wall -Wextra -c %srcDir%\renderer_sprite.cpp -o %objDir%\renderer_sprite.o %INCLUDE%
g++ -g -Wall -Wextra -c %srcDir%\resource_manager.cpp -o %objDir%\resource_manager.o %INCLUDE%
g++ -g -Wall -Wextra -c %srcDir%\scene_game.cpp -o %objDir%\scene_game.o %INCLUDE%
g++ -g -Wall -Wextra -c %srcDir%\texture.cpp -o %objDir%\texture.o %INCLUDE%

set obj=%objDir%\main.o
set obj=%objDir%\board.o %obj%
set obj=%objDir%\game.o %obj%
set obj=%objDir%\pieces.o %obj%
set obj=%objDir%\shader.o %obj%
set obj=%objDir%\renderer_geometry.o %obj%
set obj=%objDir%\renderer_sprite.o %obj%
set obj=%objDir%\resource_manager.o %obj%
set obj=%objDir%\scene_game.o %obj%
set obj=%objDir%\texture.o %obj%

g++ -g %obj% %LIB% %Librairies% -o %outputExe%

:: Copy dependencies
if not exist %buildDir%\SDL2.dll xcopy /y %extDir%\SDL2-2.0.7\lib\x64\SDL2.dll .
if not exist %buildDir%\SDL2_image.dll xcopy /y %extDir%\SDL2_image-2.0.2\lib\x64\SDL2_image.dll .
if not exist %buildDir%\SDL2_mixer.dll xcopy /y %extDir%\SDL2_mixer-2.0.2\lib\x64\SDL2_mixer.dll .
if not exist %buildDir%\SDL2_ttf.dll xcopy /y %extDir%\SDL2_ttf-2.0.14\lib\x64\SDL2_ttf.dll .
if not exist %buildDir%\glew32.dll xcopy /y %extDir%\glew-2.1.0\bin\Release\x64\glew32.dll .
if not exist %buildDir%\libpng16-16.dll xcopy /y %extDir%\SDL2_image-2.0.2\lib\x64\libpng16-16.dll .
if not exist %buildDir%\zlib1.dll xcopy /y %extDir%\SDL2_image-2.0.2\lib\x64\zlib1.dll .

popd