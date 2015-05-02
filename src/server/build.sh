#!/usr/bin/env bash
# Preparo directorio de build
mkdir build
cd build

CMAKE_FLAGS=""

if [ "$1" ==  "coverage" ]
then
	CMAKE_FLAGS="-Dcoverage-test=true"
fi
cmake .. $CMAKE_FLAGS
# Compilo
make -j4
# Copio scripts
cp ../coverage.sh .
cp ../run.sh .
cp ../runTests.sh .
cp -r ../config .
