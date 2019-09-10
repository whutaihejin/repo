cmake_minimum_required(VERSION 3.6)

project(far)

set(CMAKE_CXX_FLAGS "-gdwarf-2 -g -pipe -std=c++11 -fPIC -fno-omit-frame-pointer")

add_library(far event_loop.cc)

add_executable(event_loop_test event_loop_test.cc)
target_link_libraries(event_loop_test far)

add_executable(event_loop_test2 event_loop_test2.cc)
target_link_libraries(event_loop_test2 far)

install(TARGETS event_loop_test DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/target)
install(TARGETS event_loop_test2 DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/target)
