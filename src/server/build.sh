#!/usr/bin/env bash
# Preparo directorio de build
mkdir build
cd build
cmake ..
# Compilo
make -j4
# Copio scripts
cp ../coverage.sh .
cp ../run.sh
cp ../runTests.sh .
cp -r ../config .
