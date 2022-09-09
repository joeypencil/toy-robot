#ifndef TOYROBOT_ROBOT_H
#define TOYROBOT_ROBOT_H

#include <iostream>
#include <memory>
#include <unordered_map>
#include "grid.h"


namespace ToyRobot
{
    class Robot
    {
        public:
            Robot() = delete;
            ~Robot() = default;
            explicit Robot( std::shared_ptr<Grid> grid );

        private:
            std::shared_ptr<Grid> grid_ = nullptr;
            Coordinates coordinates_;
            bool is_placed_ = false;
            int face_direction_angle_;
            std::string face_direction_;

        public:
            std::unordered_map<int, std::string> angle_direction_map_
            {
                { 0, "NORTH" },
                { 90, "EAST" },
                { 180, "SOUTH" },
                { 270, "WEST" }
            };

            std::unordered_map<int, Coordinates> angle_coordinates_map_
            {
                { 0, Coordinates( 0, 1 ) },    // NORTH
                { 90, Coordinates( 1, 0 ) },   // EAST
                { 180, Coordinates( 0, -1 ) }, // SOUTH
                { 270, Coordinates( -1, 0 ) }  // WEST
            };

            std::unordered_map<std::string, int> rotation_map_
            {
                { "LEFT", -90 },
                { "RIGHT", 90 }
            };

        public:
            std::shared_ptr<Grid> GetGrid();
            Coordinates GetCoordinates();
            bool IsPlaced();
            int GetFaceDirectionAngle();
            std::string GetFaceDirection();

            void SetCoordinates( Coordinates coordinates );
            void SetFaceDirectionAngle( int degree );
    };
}

#endif