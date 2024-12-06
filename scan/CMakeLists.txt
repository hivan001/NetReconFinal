# Minimum required version of CMake
cmake_minimum_required(VERSION 3.10)

# Project name and C++ standard
project(net_recon VERSION 1.0 LANGUAGES CXX)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Path to the ASIO header files (assume ASIO is in the 'include/' folder)
include_directories(${CMAKE_SOURCE_DIR}/include/asio-1.30.2/include)

# List of source files
set(MAIN_SOURCES
    src/main.cpp
)
file(
GLOB SRC_SOURCES
    src/TcpScan.cpp
    src/BaseScan.cpp
    src/WriteResults.cpp
    src/Menu.cpp
)

set(ALL_SOURCES ${MAIN_SOURCES} ${SRC_SOURCES})

# List of header files (optional, but good for IDEs)
set(HEADERS
    src/BaseScan.h
    src/TcpScan.h
    src/WriteResults.h
    src/Menu.h
)

find_package(nlohmann_json 3.0.0 REQUIRED)

add_subdirectory(test)
# Add the source files to be compiled
add_executable(net_recon ${ALL_SOURCES} ${HEADERS})

add_library(scan_lib STATIC ${ALL_SOURCES})


# Link the pthread library, required for ASIO multithreading
target_link_libraries(net_recon PRIVATE scan_lib pthread nlohmann_json::nlohmann_json)

add_definitions(-DASIO_STANDALONE)

