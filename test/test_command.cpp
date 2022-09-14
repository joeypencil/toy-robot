#ifndef TOYROBOT_COMMAND_CPP_UT
#define TOYROBOT_COMMAND_CPP_UT

#include <gtest/gtest.h>
#include "command.h"

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
                CommandPlace command_place;
                command_place.SetGrid( grid_ );
                command_place.SetRobot( robot_ );
                command_place.SetLocation( location_ );
                command_place.SetFaceDirection( face_direction_ );
                command_place.Execute();
            }

            void PrepareCommand( std::shared_ptr<Command> command )
            {
                command->SetGrid( grid_ );
                command->SetRobot( robot_ );
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
        auto command_place = std::make_shared<CommandPlace>();
        PrepareCommand( command_place );
        command_place->SetLocation( location_ );
        command_place->SetFaceDirection( face_direction_ );
        command_place->Execute();

        ObtainRobotStatus();
        EXPECT_EQ( robot_status_.current_x_, 1 );
        EXPECT_EQ( robot_status_.current_y_, 1 );
        EXPECT_EQ( robot_status_.current_face_direction_, "NORTH" );
        EXPECT_TRUE( robot_status_.is_placed_ );
    }

    TEST_F( CommandTest, Can_execute_command_move )
    {
        PlaceRobot();
        
        auto command_move = std::make_shared<CommandMove>();
        PrepareCommand( command_move );
        command_move->Execute();

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

        auto command_rotate = std::make_shared<CommandRotate>();
        PrepareCommand( command_rotate );
        command_rotate->SetRotationDirection( left );
        command_rotate->Execute();

        ObtainRobotStatus();
        EXPECT_EQ( robot_status_.current_x_, 1 );
        EXPECT_EQ( robot_status_.current_y_, 1 );
        EXPECT_EQ( robot_status_.current_face_direction_, "WEST" );

        command_rotate->SetRotationDirection( right );
        command_rotate->Execute();
        command_rotate->Execute();

        ObtainRobotStatus();
        EXPECT_EQ( robot_status_.current_x_, 1 );
        EXPECT_EQ( robot_status_.current_y_, 1 );
        EXPECT_EQ( robot_status_.current_face_direction_, "EAST" );
    }
}

#endif