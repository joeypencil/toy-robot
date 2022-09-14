#ifndef TOYROBOT_INPUT_READER_CPP_UT
#define TOYROBOT_INPUT_READER_CPP_UT

#include <gtest/gtest.h>
#include "input_reader.h"

using namespace ToyRobot;


namespace ToyRobotUnitTest
{
    TEST( InputReaderTest, Can_trim_leading_spaces )
    {
        std::string command = "   move";
        trim_left( command );
        EXPECT_EQ( command, "move" );
    }

    TEST( InputReaderTest, Can_trim_trailing_spaces )
    {
        std::string command = "report   ";
        trim_right( command );
        EXPECT_EQ( command, "report" );
    }

    TEST( InputReaderTest, Can_clean_command )
    {
        std::string command_rotate = "  left   ";
        clean_command( command_rotate );
        EXPECT_EQ( command_rotate, "LEFT" );

        std::string command_place = "   place 1,3,east   ";
        clean_command( command_place );
        EXPECT_EQ( command_place, "PLACE 1,3,EAST" );

        std::string command_place_with_arg_spaces = "   place 3, 5, north   ";
        clean_command( command_place_with_arg_spaces );
        EXPECT_EQ( command_place_with_arg_spaces, "PLACE 3, 5, NORTH" );
    }
}

#endif