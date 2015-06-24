# Creo carpeta de BD
rm -rf database/test
mkdir -p database/test/testdb
mkdir -p database/test/testServices/chats
mkdir -p database/test/testServices/users
# Corro las pruebas
code/tests/tests

rm -rf database/test

