#ifndef TOYROBOT_ROBOT_H
#define TOYROBOT_ROBOT_H

#include <iostream>
#include <memory>
#include <unordered_map>
#include "coordinates.h"
#include "grid.h"


namespace ToyRobot
{
    class IRobot
    {
        public:
            IRobot() = default;
            virtual ~IRobot() = default;

        protected:
            Coordinates location_;
            bool is_placed_ = false;
            int face_direction_angle_;
            std::string face_direction_;

        public:
            std::unordered_map<int, std::string> angle_direction_map_;
            std::unordered_map<int, Coordinates> angle_move_map_;
            std::unordered_map<std::string, int> rotation_map_;

        public:
            Coordinates GetLocation() { return location_; }
            bool IsPlaced() { return is_placed_; }
            int GetFaceDirectionAngle() { return face_direction_angle_; }
            std::string GetFaceDirection() { return face_direction_; }

            void SetLocation( Coordinates coordinates )
            {
                location_ = coordinates;
                is_placed_ = true;
            }

        public:
            virtual void SetFaceDirectionAngle( int degree ) = 0;
    };

    class Robot : public IRobot
    {
        public:
            Robot();
            ~Robot() = default;

        public:
            void SetFaceDirectionAngle( int degree ) override;
    };
}

#endif