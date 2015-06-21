#!/usr/bin/env bash
# Compilo rocksDB

echo "Instalando dependencias"
sudo apt-get install g++ cmake libbz2-dev zlib1g-dev libcppunit-dev libcurl4-gnutls-dev lcov

echo "Compilando rocksDB"
cd 3rd-party/rocksdb

make static_lib

cd -

CMAKE_FLAGS=""

if [ "$1" ==  "coverage" ]
then
	CMAKE_FLAGS="-Dcoverage-test=true"
fi
cmake . $CMAKE_FLAGS
# Compilo
make -j4
