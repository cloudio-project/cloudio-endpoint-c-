set(FIND_CPP_PROPERTIES_PATHS /libraryFolder/cpp-properties)

find_path(CPP_PROPERTIES_INCLUDE_DIR Properties.h Properties.h
        PATH_SUFFIXES include
        PATHS ${FIND_CPP_PROPERTIES_PATHS})

find_library(CPP_PROPERTIES_LIBRARY
        NAMES cppproperties
        PATH_SUFFIXES lib
        PATHS ${FIND_CPP_PROPERTIES_PATHS})

