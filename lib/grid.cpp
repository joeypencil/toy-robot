#include "grid.h"


namespace ToyRobot
{
    Grid::Grid( Coordinates dimensions )
    {
        if( dimensions.GetX() < 1 || dimensions.GetY() < 1 )
            throw "Grid::Grid(): Any dimension of grid cannot be lower than 1.";

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