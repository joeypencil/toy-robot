#include "robot.h"


namespace ToyRobot
{
    Robot::Robot( std::shared_ptr<Grid> grid )
    {
        grid_ = grid;
    }

    std::shared_ptr<Grid> Robot::GetGrid()
    {
        return grid_;
    }

    Coordinates Robot::GetCoordinates()
    {
        return coordinates_;
    }

    bool Robot::IsPlaced()
    {
        return is_placed_;
    }

    int Robot::GetFaceDirectionAngle()
    {
        return face_direction_angle_;
    }

    std::string Robot::GetFaceDirection()
    {
        return face_direction_;
    }

    void Robot::SetCoordinates( Coordinates coordinates )
    {
        coordinates_.x = coordinates.x;
        coordinates_.y = coordinates.y;
        is_placed_ = true;
    }

    void Robot::SetFaceDirectionAngle( int degree )
    {
        int current_angle = face_direction_angle_;
        face_direction_angle_ = degree;

        if( face_direction_angle_ >= 360 )  // Facing WEST then turned RIGHT, should face NORTH.
            face_direction_angle_ = 0;
        else if( face_direction_angle_ < 0 )    // Facing NORTH then turned LEFT, should face WEST.
            face_direction_angle_ = 270;

        try
        {
            face_direction_ = angle_direction_map_.at( face_direction_angle_ );
        }
        catch( std::out_of_range &ex )
        {
            std::cerr << "ERROR: No direction found for angle " << degree << std::endl;
            face_direction_angle_ = current_angle;
        }
    }
}