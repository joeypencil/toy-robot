#ifndef TOYROBOT_GRID_CPP_UT
#define TOYROBOT_GRID_CPP_UT

#include <gtest/gtest.h>
#include <memory>
#include "coordinates.h"
#include "grid.h"

using namespace ToyRobot;


namespace ToyRobotUnitTest
{
    TEST( GridTest, CanCheckLocations )
    {
        Coordinates dimensions( 4, 4 );
        auto grid = std::make_shared<Grid>( dimensions );

        Coordinates location_valid( 1, 3 );
        EXPECT_TRUE( grid->IsWithinGrid( location_valid ) );

        Coordinates location_invalid( 5, 5 );
        EXPECT_FALSE( grid->IsWithinGrid( location_invalid ) );
    }

    TEST( GridTest, WillThrowOnInvalidDimensions )
    {
        Coordinates dimension_zero( 0, 4 );
        EXPECT_THROW( Grid grid( dimension_zero ), const char* );

        Coordinates dimension_negative( 3, -1 );
        EXPECT_THROW( Grid grid( dimension_negative ), const char* );
    }
}

#endif