cmake_minimum_required(VERSION 3.2)

project(far)

set(CMAKE_CXX_FLAGS "-gdwarf-2 -g -pipe -std=c++11 -fPIC -fno-omit-frame-pointer")

add_library(far event_loop.cc poller.cc channel.cc)

# add_executable(event_loop_test event_loop_test.cc)
# target_link_libraries(event_loop_test far)
# 
# add_executable(event_loop_test2 event_loop_test2.cc)
# target_link_libraries(event_loop_test2 far)
# 
# add_executable(reactor_test event_loop_test.cc)
# target_link_libraries(reactor_test far)

file(GLOB src_tests "*_test.cc")

foreach (srct ${src_tests})
    message(STATUS "process test file -> ${srct}")
    get_filename_component(entry ${srct} NAME)
    string(REGEX REPLACE "(.*).cc" "\\1" target ${entry})
    add_executable(${target} ${srct})
    target_link_libraries(${target} far)
    install(TARGETS ${target} DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/target)
endforeach()

# install(TARGETS event_loop_test DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/target)
# install(TARGETS event_loop_test2 DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/target)
