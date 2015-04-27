
find_path(CPPUNIT_ROOT_DIR
NAMES cppunit
)
find_library(CPPUNIT_LIBRARIES
NAMES cppunit
HINTS ${CPPUNIT_ROOT_DIR}
)
find_path(CPPUNIT_INCLUDE_DIRS
NAMES cppunit
HINTS ${CPPUNIT_ROOT_DIR}
)
include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(CppUnit DEFAULT_MSG
CPPUNIT_LIBRARIES
CPPUNIT_INCLUDE_DIRS
)
mark_as_advanced(
CPPUNIT_ROOT_DIR
CPPUNIT_LIBRARIES
CPPUNIT_INCLUDE_DIRS
)
