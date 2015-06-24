#!/usr/bin/env bash

make tests

# Limpio contadores
lcov -z -d code/main/

# Corro las pruebas
./runTests.sh

# Genero informe
lcov -c --directory code/main/ --no-external -o testResult.info
genhtml testResult.info --output-directory coverageInfo
# Lo abro con un navegador
xdg-open coverageInfo/index.html
