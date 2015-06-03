#!/usr/bin/env bash
# Compilo rocksDB
echo "Compilando rocksDB"
cd 3rd-party/rocksdb

make static_lib

cd -

# Preparo directorio de build
echo "Creando carpeta 'build' como destino de compilacion"
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
