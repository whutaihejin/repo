cmake_minimum_required(VERSION 2.8)
# project info
project(leetcode)
set(CMAKE_CXX_STANDARD 11)

# build flags
#option(TARGET_DEBUG_MODE "Build the project with debug mode" OFF)
set(CMAKE_CXX_FLAGS "-g -pipe -std=c++0x -fPIC -DGTEST_HAS_TR1_TUPLE=0")
if (TARGET_DEBUG_MODE) 
  set(CMAKE_BUILD_TYPE "Debug")
  set(CMAKE_CXX_FLAGS_DEBUG "-W -Wall -O0 -ftest-coverage -fprofile-arcs")
else(TARGET_DEBUG_MODE)
  set(CMAKE_BUILD_TYPE "Release")
  set(CMAKE_CXX_FLAGS_RELEASE "-O2")
endif(TARGET_DEBUG_MODE)

# work home & library home
set(work_home ${CMAKE_CURRENT_SOURCE_DIR})
set(library_home ${work_home}/third-party)
set(include_list ${work_home}/src)

# googletest lib
set(googletest_library ${library_home}/googletest-release-1.6.0)
list(APPEND include_list ${googletest_library})
list(APPEND include_list ${googletest_library}/include)
file(GLOB_RECURSE googletest_source ${googletest_library}/src/*.cc)

# build googletest static library
include_directories(${include_list})
add_library(googletest STATIC ${googletest_source})

# build self leetcode library
file(GLOB_RECURSE leetcode_source ${work_home}/src/lib/*.cc)
add_library(leetcode STATIC ${leetcode_source})

foreach(include_entry ${include_list})
  message(STATUS ${include_entry})
endforeach()

# for the source 
file(GLOB source_list "${work_home}/src/*.cc")

# for compile the source
foreach(origin_source ${source_list})
  get_filename_component(source ${origin_source} NAME)
  string(REGEX REPLACE "(.*).cc$" "\\1" target ${source})
  add_executable(${target} ${origin_source})
  target_link_libraries(${target} -pthread googletest leetcode)
endforeach()

# for install the targets
foreach(origin_source ${source_list})
  get_filename_component(source ${origin_source} NAME)
  string(REGEX REPLACE "(.*).cc$" "\\1" target ${source})
  install(TARGETS ${target} DESTINATION ${work_home}/bin)
endforeach()
