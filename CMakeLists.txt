cmake_minimum_required( VERSION 3.22 )

project( ToyRobot VERSION 1.0 )

set( CMAKE_CXX_STANDARD 17 )
set( CMAKE_CXX_STANDARD_REQUIRED True )

option( BUILD_UNIT_TEST "Build unit tests?" ON )
set( UNIT_TEST_DIR "${CMAKE_CURRENT_SOURCE_DIR}/test" )

set( LIB_DIR "${CMAKE_CURRENT_SOURCE_DIR}/lib" )
add_subdirectory( ${LIB_DIR} )
include_directories( ${LIB_DIR} )
link_directories( ${LIB_DIR} )

if( ${BUILD_UNIT_TEST} )
    add_subdirectory( ${UNIT_TEST_DIR} )
endif()

set( TARGET_MAIN toy_robot )
add_executable( ${TARGET_MAIN} main.cpp )
target_link_libraries( ${TARGET_MAIN} LIB_TOYROBOT )

