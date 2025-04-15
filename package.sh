#!/bin/bash

packageName="MossLib"; packageMajor="1"; packageMinor="0"; packageRevision="0"

packageFull="${packageName}_${packageMajor}.${packageMinor}-${packageRevision}"

echo $packageFull

rm -rf build

make BuildLib modules=network

mkdir $packageFull

mkdir -p $packageFull/lib
mkdir -p $packageFull/usr/lib
mkdir -p $packageFull/usr/local/lib



cp -f ./build/lib/libMoss.so $packageFull/lib
cp -f ./build/lib/libMoss.so $packageFull/usr/local/lib
cp -rf ./include $packageFull/usr/include/
cp -rf ./include $packageFull/usr/local/include/


mkdir $packageFull/debian

echo "Package: ${packageName}
Version: ${packageMajor}.${packageMinor}-${packageRevision}
Section: base
Priority: optional
Architecture: all
Maintainer: Moss Mayfly <mossmayfly@gmail.com>
Description: Miss-Moss Library
 Currently a library that I hope to expand into something greater.
 For now it is a dependecny free, C++ style TCP library." > $packageFull/debian/control

dpkg-deb --build $packageFull

rm -rf build $packageFull