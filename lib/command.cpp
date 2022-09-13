#include "command.h"


namespace ToyRobot
{
    void CommandPlace::SetLocation( Coordinates location )
    {
        location_ = location;
    }

    void CommandPlace::SetFaceDirection( std::string &face_direction )
    {
        face_direction_ = face_direction;
    }

    void CommandPlace::Execute()
    {
        if( ! grid_->IsWithinGrid( location_ ) )
            return;

        int angle = 0;

        std::for_each( robot_->angle_direction_map_.begin(), robot_->angle_direction_map_.end(),
            [=, &angle]( const std::pair<int, std::string> &angle_map )
            {
                if( angle_map.second == face_direction_ )
                    angle = angle_map.first;
            }
        );

        robot_->SetLocation( location_ );
        robot_->SetFaceDirectionAngle( angle );
    }

    void CommandMove::Execute()
    {
        Coordinates current_location = robot_->GetLocation();
        int face_direction_angle = robot_->GetFaceDirectionAngle();
        Coordinates pending_move;
        
        try
        {
            pending_move = robot_->angle_move_map_.at( face_direction_angle );
        }
        catch( std::out_of_range &ex )
        {
            std::cerr << "ERROR: No move coordinates found for angle " << face_direction_angle << std::endl;
            return;
        }

        int pending_x = current_location.GetX() + pending_move.GetX();
        int pending_y = current_location.GetY() + pending_move.GetY();

        Coordinates pending_location( pending_x, pending_y );

        if( grid_->IsWithinGrid( pending_location ) )
            robot_->SetLocation( pending_location );
    }

    void CommandRotate::SetRotationDirection( std::string &rotation_direction )
    {
        rotation_direction_ = rotation_direction;
    }

    void CommandRotate::Execute()
    {
        int current_face_direction_angle = robot_->GetFaceDirectionAngle();
        
        robot_->SetFaceDirectionAngle( current_face_direction_angle + robot_->rotation_map_.at( rotation_direction_ ) );
    }

    void CommandReport::Execute()
    {
        Coordinates coordinates = robot_->GetLocation();

        std::cout << coordinates.GetX() << "," << coordinates.GetY() << "," << robot_->GetFaceDirection() << std::endl;
    }
}