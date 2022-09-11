#include "coordinates.h"


namespace ToyRobot
{
    Coordinates::Coordinates( const int &x, const int &y )
    {
        x_ = x;
        y_ = y;
    }

    int Coordinates::GetX()
    {
        return x_;
    }

    int Coordinates::GetY()
    {
        return y_;
    }

    void Coordinates::SetX( int x )
    {
        x_ = x;
    }

    void Coordinates::SetY( int y )
    {
        y_ = y;
    }
}