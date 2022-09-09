cmake_minimum_required( VERSION 3.22 )

project( ToyRobot VERSION 1.0 )

set( CMAKE_CXX_STANDARD 17 )
set( CMAKE_CXX_STANDARD_REQUIRED True )

set( LIB_DIR "${CMAKE_CURRENT_SOURCE_DIR}/lib" )
add_subdirectory( ${LIB_DIR} )
include_directories( ${LIB_DIR} )
link_directories( ${LIB_DIR} )

set( TARGET toy_robot )

add_executable( ${TARGET} main.cpp )

target_link_libraries( ${TARGET} LIB_TOYROBOT )