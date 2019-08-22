set buildDir=%~dp0..\build
set assetsDir=%~dp0..\assets
set extDir=%~dp0..\external

:: Copy dependencies
if not exist %buildDir%\SDL2.dll xcopy /y %extDir%\SDL2-2.0.10\lib\x64\SDL2.dll %buildDir%
if not exist %buildDir%\SDL2_mixer.dll xcopy /y %extDir%\SDL2_mixer-2.0.2\lib\x64\SDL2_mixer.dll %buildDir%
if not exist %buildDir%\SDL2_ttf.dll xcopy /y %extDir%\SDL2_ttf-2.0.15\lib\x64\SDL2_ttf.dll %buildDir%
if not exist %buildDir%\zlib1.dll xcopy /y %extDir%\SDL2_ttf-2.0.15\lib\x64\zlib1.dll %buildDir%
if not exist %buildDir%\glew32.dll xcopy /y %extDir%\glew-2.1.0\bin\Release\x64\glew32.dll %buildDir%

:: Copy assets
if not exist %buildDir%\assets mkdir %buildDir%\assets
xcopy /y /s %assetsDir% %buildDir%\assets
