#!/bin/bash

# Create build dir
dot="$(dirname "$0")"
buildDir=$dot/../build
if [ ! -d "$buildDir" ]; then
    mkdir $buildDir
fi

# Create obj dir
objDir=$dot/obj
if [ ! -d "$objDir" ]; then
    mkdir $objDir
fi

# Needed folders
extDir=$dot/../external
scriptDir=$dot/../scripts

# Use make to build default target
cd $scriptDir
make

#cd $buildDir

# Copy dependencies
#if not exist %buildDir%\SDL2.dll xcopy /y %extDir%\SDL2-2.0.7\lib\x64\SDL2.dll .
#if not exist %buildDir%\SDL2_image.dll xcopy /y %extDir%\SDL2_image-2.0.2\lib\x64\SDL2_image.dll .
#if not exist %buildDir%\SDL2_mixer.dll xcopy /y %extDir%\SDL2_mixer-2.0.2\lib\x64\SDL2_mixer.dll .
#if not exist %buildDir%\SDL2_ttf.dll xcopy /y %extDir%\SDL2_ttf-2.0.14\lib\x64\SDL2_ttf.dll .
#if not exist %buildDir%\glew32.dll xcopy /y %extDir%\glew-2.1.0\bin\Release\x64\glew32.dll .
#if not exist %buildDir%\libpng16-16.dll xcopy /y %extDir%\SDL2_image-2.0.2\lib\x64\libpng16-16.dll .
#if not exist %buildDir%\zlib1.dll xcopy /y %extDir%\SDL2_image-2.0.2\lib\x64\zlib1.dll .

cd $dot