#ifndef TOYROBOT_GRID_H
#define TOYROBOT_GRID_H

#include "coordinates.h"


namespace ToyRobot
{
    class IGrid
    {
        public:
            IGrid() = default;
            virtual ~IGrid() = default;

        protected:
            Coordinates dimensions_;

        public:
            virtual bool IsWithinGrid( Coordinates coordinates ) = 0;
    };

    class Grid : public IGrid
    {
        public:
            Grid() = delete;
            ~Grid() = default;

            explicit Grid( Coordinates dimensions );

        public:
            bool IsWithinGrid( Coordinates coordinates ) override;
    };
}

#endif