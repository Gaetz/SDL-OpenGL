set buildDir=%~dp0..\build\Debug
set assetsDir=%~dp0..\assets
set extDir=%~dp0..\external

:: Copy dependencies
if not exist %buildDir%\SDL2.dll xcopy /y %extDir%\SDL2-2.0.30\lib\x64\SDL2.dll %buildDir%
if not exist %buildDir%\glew32.dll xcopy /y %extDir%\glew-2.2.0\bin\Release\x64\glew32.dll %buildDir%

:: Copy assets
if not exist %buildDir%\assets mkdir %buildDir%\assets
xcopy /y /s %assetsDir% %buildDir%\assets
