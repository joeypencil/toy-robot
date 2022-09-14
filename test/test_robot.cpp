#ifndef TOYROBOT_ROBOT_CPP_UT
#define TOYROBOT_ROBOT_CPP_UT

#include <gtest/gtest.h>
#include "robot.h"

using namespace ToyRobot;


namespace ToyRobotUnitTest
{
    class RobotTest : public ::testing::Test
    {
        protected:
            virtual void SetUp()
            {
                location_ = Coordinates( 1, 1 );
                robot_ = std::make_shared<Robot>();
            }

        public:
            Coordinates location_;
            std::shared_ptr<Robot> robot_;
    };

    TEST_F( RobotTest, Robot_is_initially_not_placed )
    {
        EXPECT_FALSE( robot_->IsPlaced() );
    }

    TEST_F( RobotTest, Robot_is_placed_upon_setting_location )
    {
        robot_->SetLocation( location_ );
        EXPECT_TRUE( robot_->IsPlaced() );
    }

    TEST_F( RobotTest, Robot_facing_correct_direction_based_on_angle )
    {
        robot_->SetFaceDirectionAngle( 0 );
        EXPECT_EQ( robot_->GetFaceDirection(), "NORTH" );

        robot_->SetFaceDirectionAngle( 90 );
        EXPECT_EQ( robot_->GetFaceDirection(), "EAST" );

        robot_->SetFaceDirectionAngle( 180 );
        EXPECT_EQ( robot_->GetFaceDirection(), "SOUTH" );

        robot_->SetFaceDirectionAngle( 270 );
        EXPECT_EQ( robot_->GetFaceDirection(), "WEST" );
    }

    TEST_F( RobotTest, Robot_facing_correct_direction_on_beyond_boundary_angle_value )
    {
        robot_->SetFaceDirectionAngle( 360 );
        EXPECT_EQ( robot_->GetFaceDirection(), "NORTH" );

        robot_->SetFaceDirectionAngle( -90 );
        EXPECT_EQ( robot_->GetFaceDirection(), "WEST" );
    }
}

#endif