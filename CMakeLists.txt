# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

if (NOT(EXE))
  set(EXE edge-detect)
endif()

if (CMAKE_BUILD_TYPE STREQUAL "Release")
  set(FLAG_DEBUG)
else()
  set(FLAG_DEBUG -D_DEBUG_)
endif()

project(${EXE})

# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

cmake_minimum_required(VERSION 3.10 FATAL_ERROR)
find_package(OpenCV REQUIRED)

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
else()
  include_directories(/usr/local/include)
  link_directories(/usr/local/lib)
endif()

# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

file (GLOB_RECURSE SOURCE_FILES
  ${CMAKE_CURRENT_SOURCE_DIR}/edge-detect.cpp
)

set(CMAKE_CXX_FLAGS "-std=c++11 -O3")
add_definitions(${FLAG_DEBUG})
add_executable (${EXE} ${SOURCE_FILES})

target_link_libraries (${EXE} PRIVATE
  ${OpenCV_LIBS}
  tbb
)

# end
