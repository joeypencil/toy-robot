#ifndef TOYROBOT_COMMAND_H
#define TOYROBOT_COMMAND_H

#include <regex>
#include "grid.h"
#include "robot.h"

typedef std::regex Regex;
typedef std::smatch Matches;
typedef std::shared_ptr<ToyRobot::IGrid> GridPtr;
typedef std::shared_ptr<ToyRobot::IRobot> RobotPtr;


namespace ToyRobot
{
    class Command
    {
        public:
            Command() = default;
            virtual ~Command() = default;

        public:
            GridPtr grid_ = nullptr;
            RobotPtr robot_ = nullptr;

        public:
            void SetGrid( GridPtr grid ) { grid_ = grid; }
            void SetRobot( RobotPtr robot ) { robot_ = robot; }

        public:
            virtual void Execute() = 0;
    };

    class CommandPlace : public Command
    {
        public:
            CommandPlace() = default;
            ~CommandPlace() = default;

        private:
            Coordinates location_;
            std::string face_direction_;

        public:
            void SetLocation( Coordinates location );
            void SetFaceDirection( std::string &face_direction );

        public:
            void Execute() override;
    };

    class CommandMove : public Command
    {
        public:
            CommandMove() = default;
            ~CommandMove() = default;

        public:
            void Execute() override;
    };

    class CommandRotate : public Command
    {
        public:
            CommandRotate() = default;
            ~CommandRotate() = default;

        private:
            std::string rotation_direction_;

        public:
            void SetRotationDirection( std::string &rotation_direction );

        public:
            void Execute() override;
    };

    class CommandReport : public Command
    {
        public:
            CommandReport() = default;
            ~CommandReport() = default;

        public:
            void Execute() override;
    };
}

#endif