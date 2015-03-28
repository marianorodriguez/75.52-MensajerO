project(mensajero)

cmake_minimum_required(VERSION 2.8)

#########
# Flags #
#########

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

###############
# Bibliotecas #
###############

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${PROJECT_SOURCE_DIR}/3rd-party/Modules/")

set(ROCKSDB_ROOT_DIR "${PROJECT_SOURCE_DIR}/3rd-party/rocksdb")

find_package(RocksDB)

############
# Includes #
############

set (JSONCPP_PATH "3rd-party/jsoncpp")
set (MONGOOSECPP_PATH "3rd-party/mongoose-cpp")

# Compilo libs

add_subdirectory(${MONGOOSECPP_PATH})
add_subdirectory(${JSONCPP_PATH})

include_directories(${ROCKSDB_INCLUDE_DIRS})
include_directories(${JSONCPP_PATH})
include_directories(${MONGOOSECPP_PATH})

message(STATUS "ROCKSDB_INCLUDE_DIRS = ${ROCKSDB_INCLUDE_DIRS}")

# json cpp mete su lib en una carpeta rara
#find_library(JSONCPP_LIB libjson ${JSONCPP_PATH}/src/lib_json)

###########
# Modulos #
###########

add_subdirectory(main)

# Tests
set (CPPUNIT_INCLUDE_PATH "../include/cppunit" CACHE_PATH "Directorio de Cpp-Unit")
add_subdirectory(tests)

#########
# Debug #
#########

#get_cmake_property(_variableNames VARIABLES)
#foreach (_variableName ${_variableNames})
#    message(STATUS "${_variableName}=${${_variableName}}")
#endforeach()
