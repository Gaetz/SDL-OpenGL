#!/bin/bash

# Create build dir
dot="$(pwd)/$(dirname "$0")"
buildDir=$dot/../build
if [ ! -d "$buildDir" ]; then
    mkdir $buildDir
fi

# Create obj dir
objDir="$buildDir/obj"
if [ ! -d "$objDir" ]; then
    mkdir $objDir
    mkdir $objDir/engine
    mkdir $objDir/game
fi

# Needed folders
extDir=$dot/../external
scriptDir=$dot/../scripts

# Use make to build default target
cd $scriptDir
make

cd $dot