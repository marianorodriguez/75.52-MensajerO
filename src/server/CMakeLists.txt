project(mensajero)

cmake_minimum_required(VERSION 2.8)

#########
# Flags #
#########

set (CMAKE_BUILD_TYPE "Debug")

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Wextra -Wno-unused-parameter")

###############
# Bibliotecas #
###############

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${PROJECT_SOURCE_DIR}/3rd-party/Modules/")

set(ROCKSDB_ROOT_DIR "${PROJECT_SOURCE_DIR}/3rd-party/rocksdb/")
set(JSONCPP_ROOT_DIR "${PROJECT_SOURCE_DIR}/3rd-party/jsoncpp/")
set(CPPUNIT_ROOT_DIR "${PROJECT_SOURCE_DIR}/3rd-party/cppunit/")

find_package(RocksDB)
find_package(JsonCpp)
find_package(CppUnit)

############
# Includes #
############

set (MONGOOSECPP_PATH "3rd-party/mongoose-cpp")

# Compilo libs

add_subdirectory(${MONGOOSECPP_PATH})

include_directories(${ROCKSDB_INCLUDE_DIRS})
include_directories(${JSONCPP_INCLUDE_DIRS})
include_directories(${CPPUNIT_INCLUDE_DIRS})
include_directories(${MONGOOSECPP_PATH})

message(STATUS "JSONCPP_INCLUDE_DIRS = ${JSONCPP_INCLUDE_DIRS}")
message(STATUS "JSONCPP_LIBRARIES = ${JSONCPP_LIBRARIES}")
message(STATUS "ROCKSDB_INCLUDE_DIRS = ${ROCKSDB_INCLUDE_DIRS}")
message(STATUS "CPPUNIT_INCLUDE_DIRS = ${CPPUNIT_INCLUDE_DIRS}")
message(STATUS "CPPUNIT_LIBRARIES = ${CPPUNIT_LIBRARIES}")

###########
# Modulos #
###########

add_subdirectory(main)

# Tests
enable_testing()
add_subdirectory(tests)

#########
# Debug #
#########

#get_cmake_property(_variableNames VARIABLES)
#foreach (_variableName ${_variableNames})
#    message(STATUS "${_variableName}=${${_variableName}}")
#endforeach()
