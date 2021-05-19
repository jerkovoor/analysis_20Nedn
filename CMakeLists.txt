cmake_minimum_required(VERSION 2.8)
project(20NeAnalysis)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_MACOSX_RPATH 1)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")
list(APPEND CMAKE_PREFIX_PATH $ENV{ROOTSYS})
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -O3")
# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -O0 -g")

#Find ROOT
find_package(ROOT REQUIRED)
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
include_directories(${ROOT_INCLUDE_DIR})
link_directories(${ROOT_LIBRARY_DIR})

#---Define useful ROOT functions and macros (e.g. ROOT_GENERATE_DICTIONARY)
include(${ROOT_USE_FILE})
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/build")

set(SCRIPTS
    geometry_e20003.txt
    )

foreach(_script ${SCRIPTS})
    configure_file(
        ${PROJECT_SOURCE_DIR}/${_script}
        ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${_script}
        COPYONLY
    )
endforeach()

ROOT_GENERATE_DICTIONARY(G__analysis_20Nedn ${CMAKE_CURRENT_SOURCE_DIR}/analysis_20Nedn.h LINKDEF ${CMAKE_CURRENT_SOURCE_DIR}/LinkDefanalysis_20Nedn.h)
add_library(analysis_20NednLibrary SHARED analysis_20Nedn.cpp G__analysis_20Nedn.cxx)
target_link_libraries(analysis_20NednLibrary ${ROOT_LIBRARIES} Spectrum)
add_executable(analysis analysis_20NednRun.cpp)
target_link_libraries(analysis analysis_20NednLibrary)
