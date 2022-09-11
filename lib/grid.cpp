#include "grid.h"


namespace ToyRobot
{
    Grid::Grid( Coordinates dimensions )
    {
        dimensions_.SetX( dimensions.GetX() );
        dimensions_.SetY( dimensions.GetY() );
    }

    bool Grid::IsWithinGrid( Coordinates coordinates )
    {
        return ( ( coordinates.GetX() >= 0 && coordinates.GetX() <= dimensions_.GetX() )
            && ( coordinates.GetY() >= 0 && coordinates.GetY() <= dimensions_.GetY() )
            ) ? true : false;
    }
}