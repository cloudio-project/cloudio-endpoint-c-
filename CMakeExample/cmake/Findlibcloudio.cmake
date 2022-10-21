set(FIND_CLOUDIO_PATHS /libraryFolder/cloudio-endpoint-cpp)

find_path(CLOUDIO_INCLUDE_DIR CloudioEndpoint.h
        PATH_SUFFIXES include
        PATHS ${FIND_CLOUDIO_PATHS})

find_library(CLOUDIO_LIBRARY
        NAMES cloudio_endpoint_cpp
        PATH_SUFFIXES cmake-build-debug
        PATHS ${FIND_CLOUDIO_PATHS})

