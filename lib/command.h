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

        protected:
            GridPtr grid_ = nullptr;
            RobotPtr robot_ = nullptr;

        public:
            virtual void Execute() = 0;
    };

    class CommandPlace : public Command
    {
        public:
            CommandPlace() = delete;
            ~CommandPlace() = default;

            CommandPlace( GridPtr grid, RobotPtr robot, Coordinates location, std::string &face_direction );

        private:
            Coordinates location_;
            std::string face_direction_;

        public:
            void Execute() override;
    };

    class CommandMove : public Command
    {
        public:
            CommandMove() = delete;
            ~CommandMove() = default;

            CommandMove( GridPtr grid, RobotPtr robot );

        public:
            void Execute() override;
    };

    class CommandRotate : public Command
    {
        public:
            CommandRotate() = delete;
            ~CommandRotate() = default;

            CommandRotate( RobotPtr robot, std::string &rotation_direction );

        private:
            std::string rotation_direction_;

        public:
            void Execute() override;
    };

    class CommandReport : public Command
    {
        public:
            CommandReport() = delete;
            ~CommandReport() = default;

            CommandReport( RobotPtr robot );

        public:
            void Execute() override;
    };
}

#endif