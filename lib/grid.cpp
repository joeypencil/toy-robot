#include "grid.h"


namespace ToyRobot
{
    Grid::Grid( Coordinates dimensions )
    {
        try
        {
            if( dimensions.GetX() < 1 || dimensions.GetY() < 1 )
                throw std::invalid_argument( "Grid::Grid(): Any dimension of grid cannot be lower than 1." );
        }
        catch( std::invalid_argument const &ex )
        {
            std::cerr << ex.what() << std::endl;
            exit( EXIT_FAILURE );
        }

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