#ifndef TOYROBOT_COMMAND_CPP_UT
#define TOYROBOT_COMMAND_CPP_UT

#include <gtest/gtest.h>
#include "command.h"
#include "command_controller.h"

using namespace ToyRobot;


namespace ToyRobotUnitTest
{
    class CommandTest : public ::testing::Test
    {
        protected:
            virtual void SetUp()
            {
                dimensions_ = Coordinates( 4, 4 );
                grid_ = std::make_shared<Grid>( dimensions_ );

                robot_ = std::make_shared<Robot>();
                location_ = Coordinates( 1, 1 );
            }

        public:
            Coordinates dimensions_;
            GridPtr grid_ = nullptr;

            RobotPtr robot_ = nullptr;
            Coordinates location_;
            std::string face_direction_ = "NORTH";

            struct RobotStatus
            {
                int current_x_;
                int current_y_;
                std::string current_face_direction_;
                bool is_placed_;
            };

            RobotStatus robot_status_;

        public:
            void PlaceRobot()
            {
                CommandController controller( std::make_unique<CommandPlace>( grid_, robot_, location_, face_direction_ ) );
                controller.Execute();
            }

            void ObtainRobotStatus()
            {
                Coordinates current_location_ = robot_->GetLocation();
                robot_status_.current_x_ = current_location_.GetX();
                robot_status_.current_y_ = current_location_.GetY();

                robot_status_.current_face_direction_ = robot_->GetFaceDirection();
                robot_status_.is_placed_ = robot_->IsPlaced();
            }
    };

    TEST_F( CommandTest, Can_execute_command_place )
    {
        PlaceRobot();

        ObtainRobotStatus();
        EXPECT_EQ( robot_status_.current_x_, 1 );
        EXPECT_EQ( robot_status_.current_y_, 1 );
        EXPECT_EQ( robot_status_.current_face_direction_, "NORTH" );
        EXPECT_TRUE( robot_status_.is_placed_ );
    }

    TEST_F( CommandTest, Can_execute_command_move )
    {
        PlaceRobot();
        
        CommandController controller( std::make_unique<CommandMove>( grid_, robot_ ) );
        controller.Execute();

        ObtainRobotStatus();
        EXPECT_EQ( robot_status_.current_x_, 1 );
        EXPECT_EQ( robot_status_.current_y_, 2 );
        EXPECT_EQ( robot_status_.current_face_direction_, "NORTH" );
    }

    TEST_F( CommandTest, Can_execute_command_rotate )
    {
        PlaceRobot();
        std::string left = "LEFT";
        std::string right = "RIGHT";

        CommandController controller_left( std::make_unique<CommandRotate>( robot_, left ) );
        controller_left.Execute();

        ObtainRobotStatus();
        EXPECT_EQ( robot_status_.current_x_, 1 );
        EXPECT_EQ( robot_status_.current_y_, 1 );
        EXPECT_EQ( robot_status_.current_face_direction_, "WEST" );

        CommandController controller_right( std::make_unique<CommandRotate>( robot_, right ) );
        controller_right.Execute();
        controller_right.Execute();

        ObtainRobotStatus();
        EXPECT_EQ( robot_status_.current_x_, 1 );
        EXPECT_EQ( robot_status_.current_y_, 1 );
        EXPECT_EQ( robot_status_.current_face_direction_, "EAST" );
    }
}

#endif