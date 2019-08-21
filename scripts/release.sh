#!/bin/bash

# Create build dir
dot="$(dirname "$0")"
releaseDir=$dot/../release
if [ ! -d "$releaseDir" ]; then
    mkdir $releaseDir
fi

# Create obj dir
objDir=$releaseDir/obj
if [ ! -d "$objDir" ]; then
    mkdir $objDir
fi

# Needed folders
extDir=$dot/../external
scriptDir=$dot/../scripts

# Use make to build default target
cd $scriptDir
make release


cd $releaseDir

# Copy dependencies
#if not exist %releaseDir%\SDL2.dll xcopy /y %extDir%\SDL2-2.0.7\lib\x64\SDL2.dll .
#if not exist %releaseDir%\SDL2_mixer.dll xcopy /y %extDir%\SDL2_mixer-2.0.2\lib\x64\SDL2_mixer.dll .
#if not exist %releaseDir%\SDL2_ttf.dll xcopy /y %extDir%\SDL2_ttf-2.0.14\lib\x64\SDL2_ttf.dll .
#if not exist %releaseDir%\glew32.dll xcopy /y %extDir%\glew-2.1.0\bin\Release\x64\glew32.dll .

# Copy assets
assetsDir=$dot/../assets
if [ ! -d "$releaseDir/assets" ]; then
    mkdir "$releaseDir/assets"
fi
cp -a "$assetsDir/." "$releaseDir/assets"

# Remove release obj files
rm -r $objDir

cd $dot