@echo off

set buildDir=%~dp0..\build
set extDir=%~dp0..\external
set assetsDir=%~dp0..\assets

:: Copy assets
if not exist %buildDir%\assets mkdir %buildDir%\assets
xcopy /y /s %assetsDir% %buildDir%\assets
