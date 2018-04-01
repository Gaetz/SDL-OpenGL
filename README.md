# cpp-Tetris

A tetris game kata with sdl2 and openGl, built with minGW-w64 and Visual Studio Code for windows 10.


# Project structure

With inspiration from Anthony Reddan: http://anthonyreddan.com/sdl-and-vscode/

```
.vscode/        // Visual studio code files
assets/         // Game assets
build/          // Build files, not versioned
external/       // Libraries where will be taken files necessary for compilation
resources/      // Files used to create game assets
scripts/        // Build scripts (.bat files)
src/            // Sources
.gitignore      // Files we don't want to version
LICENCE         // Your rights
Readme.md       // This file ;)
```


# Installing mingw-w64

MinGW allow to use gcc on windows command prompt. MinGW-w64 is the 64 bits version. Go there: https://mingw-w64.org/doku.php/download and choose MingW-W64-builds.

Launch the installer. Choose:

```
Version:        latest
Architecture:   x86_64
Threads:        posix
Exceptions:     sjlj
Build revision: 0
```

Choose a folder on c: drive *with no space*. Like `C:\mingw-w64`. 
The installer will add a folder with mingw version. Go on installing.

Open your environment variables. Add the mingw bin folder to your PATH.
e.g.: C:\mingw-w64\x86_64-7.3.0-posix-sjlj-rt_v5-rev0\mingw64\bin

Open a promt and try g++ command.

# Download dependencies

Put your dependencies in the `external` folder.


# Build and clean scripts

Create a `build.bat` file in the `scripts` folder.

```
@echo off
 
:: Create build dir
set buildDir=%~dp0..\build
if not exist %buildDir% mkdir %buildDir%
pushd %buildDir%
 
:: Compiler input
set objDir=.\obj\
set outputExe=%buildDir%/Tetris.exe

set files=..\src\main.cpp ..\src\board.cpp ..\src\game.cpp ..\src\pieces.cpp ..\src\shader.cpp ..\src\texture.cpp 
set files=..\src\renderer_geometry.cpp ..\src\renderer_sprite.cpp ..\src\resource_manager.cpp ..\src\scene_game.cpp %files%

if not exist %objDir% mkdir %objDir%

:: Dependencies
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

:: Compile everything (not optimal)
g++ -g -Wall %files% %INCLUDE% %LIB% %Librairies% -o %outputExe%

:: Copy dependencies
xcopy /y ..\external\SDL2-2.0.7\lib\x64\SDL2.dll .
xcopy /y ..\external\SDL2_image-2.0.2\lib\x64\SDL2_image.dll .
xcopy /y ..\external\SDL2_mixer-2.0.2\lib\x64\SDL2_mixer.dll .
xcopy /y ..\external\SDL2_ttf-2.0.14\lib\x64\SDL2_ttf.dll .
xcopy /y ..\external\glew-2.1.0\bin\Release\x64\glew32.dll .
xcopy /y ..\external\SDL2_image-2.0.2\lib\x64\libpng16-16.dll .
xcopy /y ..\external\SDL2_image-2.0.2\lib\x64\zlib1.dll .

:: Copy assets
mkdir %buildDir%\assets
xcopy /y /s ..\assets %buildDir%\assets

popd
```

Note that you name the output exe file in this script.

Create a `clean.bat` file in the `scripts` folder.

```
@echo off
 
set buildDir=%~dp0..\build
set objDir=.\obj\
set assetDir=.\assets\

if exist %buildDir% (  
  pushd %buildDir%
  del /q /s *.exe *.pdb *.ilk *.dll
  rd /s /q %objDir%
  rd /s /q %assetDir%
  rd /s /q .vs
  popd
)
```

# VS Code configuration

## Cpp configuration

Ctrl + Shift + p then C/Cpp Edit configuration. This file must contains mmingw includes and your librairies includes.

```
{
    "configurations": [
        {
            "name": "Win32",
            "intelliSenseMode": "clang-x64",
            "includePath": [
                "${workspaceRoot}",
                "C:/mingw-w64/x86_64-7.3.0-posix-sjlj-rt_v5-rev0/mingw64/include",
                "C:/mingw-w64/x86_64-7.3.0-posix-sjlj-rt_v5-rev0/mingw64/bin/../lib/gcc/x86_64-w64-mingw32/7.3.0/include/c++",
                "C:/mingw-w64/x86_64-7.3.0-posix-sjlj-rt_v5-rev0/mingw64/bin/../lib/gcc/x86_64-w64-mingw32/7.3.0/include/c++/x86_64-w64-mingw32",
                "C:/mingw-w64/x86_64-7.3.0-posix-sjlj-rt_v5-rev0/mingw64/bin/../lib/gcc/x86_64-w64-mingw32/7.3.0/include/c++/backward",
                "C:/mingw-w64/x86_64-7.3.0-posix-sjlj-rt_v5-rev0/mingw64/bin/../lib/gcc/x86_64-w64-mingw32/7.3.0/include",
                "C:/mingw-w64/x86_64-7.3.0-posix-sjlj-rt_v5-rev0/mingw64/bin/../lib/gcc/x86_64-w64-mingw32/7.3.0/include-fixed",
                "C:/mingw-w64/x86_64-7.3.0-posix-sjlj-rt_v5-rev0/mingw64/bin/../lib/gcc/x86_64-w64-mingw32/7.3.0/../../../../x86_64-w64-mingw32/include",
                "${workspaceRoot}/external/SDL2-2.0.7/include",
                "${workspaceRoot}/external/SDL2_image-2.0.2/include",
                "${workspaceRoot}/external/SDL2_mixer-2.0.2/include",
                "${workspaceRoot}/external/SDL2_ttf-2.0.14/include",
                "${workspaceRoot}/external/glew-2.1.0/include",
                "${workspaceRoot}/external/glm-0.9.5"
            ],
            "defines": [
                "_DEBUG",
                "UNICODE",
                "__GNUC__=7",
                "__cdecl=__attribute__((__cdecl__))",
                "_WIN64"
            ],
            "browse": {
                "path": [
                    "${workspaceFolder}",
                    "C:/mingw-w64/x86_64-7.3.0-posix-sjlj-rt_v5-rev0/mingw64/include/*",
                    "C:/mingw-w64/x86_64-7.3.0-posix-sjlj-rt_v5-rev0/mingw64/bin/../lib/gcc/x86_64-w64-mingw32/7.3.0/include",
                    "C:/mingw-w64/x86_64-7.3.0-posix-sjlj-rt_v5-rev0/mingw64/bin/../lib/gcc/x86_64-w64-mingw32/7.3.0/include-fixed",
                    "${workspaceRoot}/external/SDL2-2.0.7/include",
                    "${workspaceRoot}/external/SDL2_image-2.0.2/include",
                    "${workspaceRoot}/external/SDL2_mixer-2.0.2/include",
                    "${workspaceRoot}/external/SDL2_ttf-2.0.14/include",
                    "${workspaceRoot}/external/glew-2.1.0/include",
                    "${workspaceRoot}/external/glm-0.9.5"
                ],
                "limitSymbolsToIncludedHeaders": true,
                "databaseFilename": ""
            },
            "cStandard": "c11",
            "cppStandard": "c++17"
        }
    ],
    "version": 3
}
```

Note that `__GNUC__` must be equal to mingw major version. Here 7 for version 7.3.0.

## User settings configuration

Ctrl + Shift + p, open user settings. Add:

```    "C_Cpp.intelliSenseEngine": "Default" ```

## Tasks

Ctrl + Shift + p, config default build task.

```
{
    // See https://go.microsoft.com/fwlink/?LinkId=733558
    // for the documentation about the tasks.json format
    "version": "2.0.0",
    "tasks": [
        {
            "label": "build",
            "type": "shell",
            "windows": {
                "command": "powershell",
                "args": ["./scripts/build.bat"]
            },
            "group": {
                "kind": "build",
                "isDefault": true
            },
            "problemMatcher": { "owner": "cpp", "fileLocation": ["relative", "${workspaceRoot}"], "pattern": { "regexp": "^(.*):(/d+):(/d+):/s+(warning|error):/s+(.*)$", "file": 1, "line": 2, "column": 3, "severity": 4, "message": 5 } }        
        },
        {
            "label": "clean",
            "type": "shell",
            "windows": {
                "command": "powershell",
                "args": ["./scripts/clean"]
            }
        }
    ]
}
```

The build script will compile the exe to the `build` folder, copy dlls and assets there to. 

The clean script will clean the build folder.

## Keyboard shortcut to clean

 Ctrl + Shift + p, open keyboard shortcuts file.

 In your personal bindings:

```
[
    {
        "key": "ctrl+shift+c",
        "command": "workbench.action.tasks.runTask",
        "args": "clean"
    }
]
```

Build shortcut is already configured to ctrl + shift + b.

## Launch config

Ctrl + Shift + p, open launch.json

```
{
    // Utilisez IntelliSense pour en savoir plus sur les attributs possibles.
    // Pointez pour afficher la description des attributs existants.
    // Pour plus d'informations, visitez : https://go.microsoft.com/fwlink/?linkid=830387
    "version": "0.2.0",
    "configurations": [
        {
            "name": "(Windows) Launch",
            "type": "cppdbg",
            "request": "launch",
            "program": "${workspaceRoot}/build/Tetris.exe",
            "args": [],
            "stopAtEntry": false,
            "cwd": "${workspaceFolder}/build",
            "environment": [],
            "externalConsole": true,
            "MIMode": "gdb",
            "miDebuggerPath": "C:\\mingw-w64\\x86_64-7.3.0-posix-sjlj-rt_v5-rev0\\mingw64\\bin\\gdb.exe",
            "setupCommands": [
                {
                    "description": "Enable pretty-printing for gdb",
                    "text": "-enable-pretty-printing",
                    "ignoreFailures": true
                }
            ],
        } 
    ]
}
```

The `program` field must name the output exe file. The `miDebuggerPath` should point to the gdb exe.

# Try your game

Build with ctrl + shift + b then launch with F5.
