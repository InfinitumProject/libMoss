#!/bin/bash

modules="network"

packageName="libMoss"; packageMajor="1"; packageMinor="0"; packageRevision="2"

packageFull="${packageName}_${packageMajor}.${packageMinor}-${packageRevision}"

echo $packageFull

rm -rf build

make BuildLib modules=$modules

mkdir $packageFull

mkdir -p $packageFull/lib
mkdir -p $packageFull/usr/lib
mkdir -p $packageFull/usr/local/lib



cp -f ./build/lib/$packageName.so $packageFull/lib
cp -f ./build/lib/$packageName.so $packageFull/usr/local/lib
cp -rf ./include $packageFull/usr/include/
cp -rf ./include $packageFull/usr/local/include/


mkdir $packageFull/DEBIAN

echo "Package: ${packageName}
Version: ${packageMajor}.${packageMinor}-${packageRevision}
Section: base
Priority: optional
Architecture: all
Maintainer: Moss Mayfly <mossmayfly@gmail.com>
Description: Miss-Moss Library
 Currently a library that I hope to expand into something greater.
 For now it is a dependecny free, C++ style TCP library." > $packageFull/DEBIAN/control

dpkg-deb --build --root-owner-group $packageFull

rm -rf build $packageFull