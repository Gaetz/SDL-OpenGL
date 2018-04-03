# cpp-Tetris

A tetris game kata with sdl2 and openGl, built with minGW-w64 and Visual Studio Code for windows 10.


# Project structure

With inspiration from Anthony Reddan: http://anthonyreddan.com/sdl-and-vscode/

```
.vscode/        // Visual studio code files
assets/         // Game assets
build/          // Build files, not versioned
external/       // Libraries where will be taken files necessary for compilation
release/        // Release game, not versioned
resources/      // Files used to create game assets
scripts/        // Build scripts (.bat files and makefile)
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


# Scripts and makefile

The `build.bat` script will use a makefile to build only updated sources. Everything will be built to the `build` folder. This script also copy dlls to the `build` folder, so they can be used by the generated exe.

The makefile contains all includes and libs dependencies.

The `clean.bat` script will empty the `build` folder to start over build if needed.

The `assets.bat` will copy game assets to the `build` folder. It will be used before program launch.

The `release.bat` will use makefile release target to compile to the `release` folder, copy dlls, assets, then delete obj files. The `release` folder can be used to release the game.


## Makefile

Create a `makefile` file in the `scripts` folder.

Makefiles are used to find sources to be built and to avoid compiling not modified sources.

```
SRC_DIR := ..\src
OBJ_DIR := ..\build\obj
EXT_DIR := ..\external
BUILD_DIR := ..\build

SRC_FILES := $(wildcard $(SRC_DIR)/*.cpp)
OBJ_FILES := $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRC_FILES))

INCLUDE :=-I$(EXT_DIR)\SDL2-2.0.7\include \
	-I$(EXT_DIR)\SDL2-2.0.7\include \
	-I$(EXT_DIR)\SDL2_image-2.0.2\include \
	-I$(EXT_DIR)\SDL2_mixer-2.0.2\include \
	-I$(EXT_DIR)\SDL2_ttf-2.0.14\include \
	-I$(EXT_DIR)\glew-2.1.0\include \
	-I$(EXT_DIR)\glm-0.9.5

LIB :=-L$(EXT_DIR)\SDL2-2.0.7\lib\x64 \
	-L$(EXT_DIR)\SDL2_image-2.0.2\lib\x64 \
	-L$(EXT_DIR)\SDL2_mixer-2.0.2\lib\x64 \
	-L$(EXT_DIR)\SDL2_ttf-2.0.14\lib\x64 \
	-L$(EXT_DIR)\glew-2.1.0\lib\Release\x64

LIBRAIRIES := -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer -llibpng16-16 -lglew32 -lzlib1 -lopengl32

# Target, with all .o prerequisites
Tetris.exe: $(OBJ_FILES)
	g++ -g -o $(BUILD_DIR)\$@ $^ $(LIB) $(LIBRAIRIES)

# Each .o file finds his .cpp counterpart
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	g++ -std=c++17 -g -Wall -Wextra -c -o $@ $< $(INCLUDE)

# Release target
release: $(RELEASE_OBJ_FILES)
	g++ -O3 -mwindows -o $(RELEASE_DIR)\Tetris.exe $^ $(LIB) $(LIBRAIRIES)

# Each .o file finds his .cpp counterpart, with optimisations
$(RELEASE_OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	g++ -std=c++17 -O3 -Wall -Wextra -c -o $@ $< $(INCLUDE)

```

Note that you name the output exe file in this makefile.

## Build script

Create a `build.bat` file in the `scripts` folder.

This script executes the makefile, creates and copies needed folders and files.

```
@echo off
 
:: Create build dir
set buildDir=%~dp0..\build
if not exist %buildDir% mkdir %buildDir%
pushd %buildDir%

:: Create obj dir
set objDir=.\obj
if not exist %objDir% mkdir %objDir%

:: Needed folders
set extDir=%~dp0..\external
set scriptDir=%~dp0..\scripts

:: Use make to build default target
cd %scriptDir%\
mingw32-make

cd %buildDir%

:: Copy dependencies
if not exist %buildDir%\SDL2.dll xcopy /y %extDir%\SDL2-2.0.7\lib\x64\SDL2.dll .
if not exist %buildDir%\SDL2_image.dll xcopy /y %extDir%\SDL2_image-2.0.2\lib\x64\SDL2_image.dll .
if not exist %buildDir%\SDL2_mixer.dll xcopy /y %extDir%\SDL2_mixer-2.0.2\lib\x64\SDL2_mixer.dll .
if not exist %buildDir%\SDL2_ttf.dll xcopy /y %extDir%\SDL2_ttf-2.0.14\lib\x64\SDL2_ttf.dll .
if not exist %buildDir%\glew32.dll xcopy /y %extDir%\glew-2.1.0\bin\Release\x64\glew32.dll .
if not exist %buildDir%\libpng16-16.dll xcopy /y %extDir%\SDL2_image-2.0.2\lib\x64\libpng16-16.dll .
if not exist %buildDir%\zlib1.dll xcopy /y %extDir%\SDL2_image-2.0.2\lib\x64\zlib1.dll .

popd
```

## Clean script

Create a `clean.bat` file in the `scripts` folder.

This script cleans the `build` and the `release` folder.

```
@echo off
 
set buildDir=%~dp0..\build
set releaseDir=%~dp0..\release
set objDir=.\obj\
set assetDir=.\assets\

if exist %buildDir% (  
  pushd %buildDir%
  del /q /s *.exe *.pdb *.ilk *.dll
  rd /s /q %objDir%
  if exist %assetDir% rd /s /q %assetDir%
  popd
)

if exist %releaseDir% (  
  pushd %releaseDir%
  del /q /s *.exe *.pdb *.ilk *.dll
  rd /s /q %objDir%
  if exist %assetDir% rd /s /q %assetDir%
  popd
)

```

## Asset copy script

This script will copy game assets to the `build` folder.

Create a `assets.bat` file in the `scripts` folder.

```
@echo off

set buildDir=%~dp0..\build
set assetsDir=%~dp0..\assets

:: Copy assets
if not exist %buildDir%\assets mkdir %buildDir%\assets
xcopy /y /s %assetsDir% %buildDir%\assets

```

## Release script

This script will prepare game for release. Game will be compiled ready to ship into the `release` folder.

Create a `release.bat` file in the `scripts` folder.

```
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

```

# VS Code configuration

## Cpp extension

Install the C/C++ extension from Microsoft.

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
                "command": "",
                "args": ["./scripts/build"]
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
                "command": "",
                "args": ["./scripts/clean"]
            }
        },
        {
            "label": "prepare-assets",
            "type": "shell",
            "windows": {
                "command": "",
                "args": ["./scripts/assets"]
            }
        },
        {
            "label": "release",
            "type": "shell",
            "windows": {
                "command": "",
                "args": ["./scripts/release"]
            },
            "problemMatcher": { "owner": "cpp", "fileLocation": ["relative", "${workspaceRoot}"], "pattern": { "regexp": "^(.*):(/d+):(/d+):/s+(warning|error):/s+(.*)$", "file": 1, "line": 2, "column": 3, "severity": 4, "message": 5 } }        
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

Ctrl + Shift + p, open `launch.json`

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
            "preLaunchTask": "prepare-assets"
        } 
    ]
}

```

The `program` field must name the output exe file. The `miDebuggerPath` shall point to the gdb exe.

# .gitignore

We don't need `build` and `release` folders. Thus we create a `.gitignore` file at the project root.

```
# Compiled Object files
*.slo
*.lo
*.o
*.obj

# Executables
*.exe
*.out
*.app

# Builds
build/
release/

```

# Try your game

Build with ctrl + shift + b then launch with F5.
