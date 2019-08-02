#!/bin/bash

dot=$(dirname "$0")
buildDir=$dot/../build
assetsDir=$dot/../assets

# Copy assets
if [ ! -d "$buildDir/assets" ]; then
    mkdir "$buildDir/assets"
fi
cp -a "$assetsDir/." "$buildDir/assets"

cd $dot