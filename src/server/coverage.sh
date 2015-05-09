#!/usr/bin/env bash
# Limpio contadores
lcov -z -d main/
# Creo carpeta de BD
rm -rf tests/database/testdb
mkdir -p tests/database/testdb
# Corro las pruebas
tests/tests
# Genero informe
lcov -c -d main/ -o testResult.info
genhtml testResult.info --output-directory html
# Lo abro con un navegador
xdg-open html/index.html
