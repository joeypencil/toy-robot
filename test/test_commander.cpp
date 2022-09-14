#ifndef TOYROBOT_COMMANDER_CPP_UT
#define TOYROBOT_COMMANDER_CPP_UT

#include <gtest/gtest.h>
#include "commander.h"

using namespace ToyRobot;


namespace ToyRobotUnitTest
{
    class CommanderTest : public ::testing::Test
    {
        protected:
            virtual void SetUp()
            {
                input_reader_ = std::make_shared<ConsoleReader>();

                dimensions_ = Coordinates( 4, 4 );
                grid_ = std::make_shared<Grid>( dimensions_ );

                commander_ = std::make_unique<Commander>( input_reader_, grid_ );
            }

        public:
            std::shared_ptr<ConsoleReader> input_reader_ = nullptr;

            std::shared_ptr<Grid> grid_ = nullptr;
            Coordinates dimensions_;

            std::unique_ptr<Commander> commander_ = nullptr;
            bool is_matched_;
            Matches matches_;

            std::string command_place_ = "PLACE 2,1,WEST";
            std::string command_move_ = "MOVE";
            std::string command_left_ = "LEFT";
            std::string command_right_ = "RIGHT";
            std::string command_report_ = "REPORT";
    };

    TEST_F( CommanderTest, Can_regex_match_place_command )
    {
        is_matched_ = Commander::IsRegexMatch( command_place_, matches_, commander_->command_regexes_.at( "PLACE" ) );

        EXPECT_TRUE( is_matched_ );
        EXPECT_GE( matches_.size(), 5 );
    }

    TEST_F( CommanderTest, Can_regex_match_move_command )
    {
        is_matched_ = Commander::IsRegexMatch( command_move_, matches_, commander_->command_regexes_.at( "MOVE" ) );

        EXPECT_TRUE( is_matched_ );
        EXPECT_GE( matches_.size(), 1 );
    }

    TEST_F( CommanderTest, Can_regex_match_rotate_command )
    {
        is_matched_ = Commander::IsRegexMatch( command_left_, matches_, commander_->command_regexes_.at( "ROTATE" ) );

        EXPECT_TRUE( is_matched_ );
        EXPECT_GE( matches_.size(), 1 );

        is_matched_ = Commander::IsRegexMatch( command_right_, matches_, commander_->command_regexes_.at( "ROTATE" ) );

        EXPECT_TRUE( is_matched_ );
        EXPECT_GE( matches_.size(), 1 );
    }

    TEST_F( CommanderTest, Can_regex_match_report_command )
    {
        is_matched_ = Commander::IsRegexMatch( command_report_, matches_, commander_->command_regexes_.at( "REPORT" ) );

        EXPECT_TRUE( is_matched_ );
        EXPECT_GE( matches_.size(), 1 );
    }
}

#endif