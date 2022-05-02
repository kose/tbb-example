##

if (NOT(EXE))
  set(EXE edge-detect)
endif()

if (NOT(CMAKE_BUILD_TYPE STREQUAL "Release"))
  set(FLAG_DEBUG -D_DEBUG_)
endif()

project(${EXE})

# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

cmake_minimum_required(VERSION 3.10 FATAL_ERROR)
find_package(OpenCV 4.1 REQUIRED)

#
# TBB
#
if (EXISTS $ENV{TBB_DIR})
  include_directories($ENV{TBB_DIR}/../include)
  link_directories($ENV{TBB_DIR}/../lib)
endif()

#
# lib
#
string(TOLOWER ${CMAKE_SYSTEM_PROCESSOR} ARCH)

#
# M1(arm64:homebrew) or not
#
if (ARCH STREQUAL "arm64")
  include_directories(/opt/homebrew/include)
  link_directories(/opt/homebrew/lib)
  set(CMAKE_CXX_FLAGS "-std=c++11 -O3 -Wno-deprecated-declarations")
else()
  include_directories(/usr/local/include)
  link_directories(/usr/local/lib)
  set(CMAKE_CXX_FLAGS "-std=c++11 -O3 -march=native -Wno-deprecated ")
endif()

# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

file (GLOB_RECURSE SOURCE_FILES
  ${CMAKE_CURRENT_SOURCE_DIR}/edge-detect.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/pipeline-edge.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/pipeline-inlet.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/pipeline-outlet.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/sobel-filter.cpp
)

add_definitions(-DTBB_SUPPRESS_DEPRECATED_MESSAGES ${FLAG_DEBUG})
add_executable (${EXE} ${SOURCE_FILES})

target_link_libraries (${EXE} PRIVATE
  ${OpenCV_LIBS}
  tbb
)

# end
