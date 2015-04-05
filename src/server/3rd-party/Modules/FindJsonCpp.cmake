# Try to find JsonCpp headers and library.
#
# Usage of this module as follows:
#
# find_package(JsonCpp)
# See FindRocksDB.cmake for reference
find_path(JSONCPP_ROOT_DIR
NAMES json.h
)
find_library(JSONCPP_LIBRARIES
NAMES jsoncpp
HINTS ${JSONCPP_ROOT_DIR}
)
find_path(JSONCPP_INCLUDE_DIRS
NAMES json.h
HINTS ${JSONCPP_ROOT_DIR}
)
include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(JsonCpp DEFAULT_MSG
JSONCPP_LIBRARIES
JSONCPP_INCLUDE_DIRS
)
mark_as_advanced(
JSONCPP_ROOT_DIR
JSONCPP_LIBRARIES
JSONCPP_INCLUDE_DIRS
)
