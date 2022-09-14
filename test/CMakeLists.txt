include( FetchContent )
FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG release-1.12.1
)

# For Windows: Prevent overriding the parent project's compiler/linker settings
set( gtest_force_shared_crt ON CACHE BOOL "" FORCE )
FetchContent_MakeAvailable( googletest )

enable_testing()

set( TARGET_TEST toy_robot_unit_test )
add_executable( ${TARGET_TEST}
    test_grid.cpp
    test_input_reader.cpp
    test_robot.cpp
    test_commander.cpp
)
target_link_libraries(
    ${TARGET_TEST}
    GTest::gtest_main
    LIB_TOYROBOT
)

include( GoogleTest )
gtest_discover_tests( ${TARGET_TEST} )