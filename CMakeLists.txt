##

if (NOT(EXE))
  set(EXE edge-detect)
endif()

if (NOT(CMAKE_BUILD_TYPE STREQUAL "Release"))
  set(FLAG_DEBUG -DDEBUG)
endif()

project(${EXE})

# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

cmake_minimum_required(VERSION 3.10 FATAL_ERROR)

find_package(OpenCV 4.1 REQUIRED)

set(CMAKE_CXX_FLAGS "-std=c++11 -O3 -march=native")

add_definitions(-DTBB_SUPPRESS_DEPRECATED_MESSAGES ${FLAG_DEBUG})

if(APPLE)
	include_directories(/opt/local/include)
	link_directories(/opt/local/lib)
endif(APPLE)


# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

file (GLOB_RECURSE SOURCE_FILES
  ${CMAKE_CURRENT_SOURCE_DIR}/edge-detect.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/pipeline-edge.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/pipeline-inlet.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/pipeline-outlet.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/sobel-filter.cpp
)

add_executable (${EXE} ${SOURCE_FILES})

target_link_libraries (${EXE} PRIVATE
	${OpenCV_LIBS}
	tbb pthread
)

# end
