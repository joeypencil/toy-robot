#include "robot.h"


namespace ToyRobot
{
    Robot::Robot()
    {
        FillNavigationMaps();
    }

    void Robot::FillNavigationMaps()
    {
        angle_direction_map_ =
        {
            { 0, "NORTH" },
            { 90, "EAST" },
            { 180, "SOUTH" },
            { 270, "WEST" }
        };

        angle_move_map_ = 
        {
            { 0, Coordinates( 0, 1 ) },    // NORTH
            { 90, Coordinates( 1, 0 ) },   // EAST
            { 180, Coordinates( 0, -1 ) }, // SOUTH
            { 270, Coordinates( -1, 0 ) }  // WEST
        };

        rotation_map_ = 
        {
            { "LEFT", -90 },
            { "RIGHT", 90 }
        };
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