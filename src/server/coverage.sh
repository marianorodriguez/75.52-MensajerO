#!/usr/bin/env bash
# Limpio contadores
lcov -z -d code/main/
# Creo carpeta de BD
mkdir -p database/users
mkdir -p database/chats
# Corro las pruebas
code/tests/tests
# Genero informe
lcov -c -d code/main/ -o testResult.info
genhtml testResult.info --output-directory html
# Lo abro con un navegador
xdg-open html/index.html
