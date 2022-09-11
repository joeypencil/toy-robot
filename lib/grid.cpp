#include "grid.h"


namespace ToyRobot
{
    Grid::Grid( const Coordinates &coordinates )
    {
        coordinates_.x = coordinates.x;
        coordinates_.y = coordinates.y;
    }

    bool Grid::IsWithinGrid( const Coordinates &coordinates ) const
    {
        return ( ( coordinates.x >= 0 && coordinates.x <= coordinates_.x )
            && ( coordinates.y >= 0 && coordinates.y <= coordinates_.y )
            ) ? true : false;
    }
}