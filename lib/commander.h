#ifndef TOYROBOT_COMMANDER_H
#define TOYROBOT_COMMANDER_H

#include <memory>
#include <unordered_map>
#include <regex>
#include "input_reader.h"
#include "grid.h"
#include "robot.h"
#include "command.h"
#include "command_controller.h"

typedef std::regex Regex;
typedef std::smatch Matches;
typedef std::shared_ptr<ToyRobot::IInputReader> InputReaderPtr;
typedef std::shared_ptr<ToyRobot::IGrid> GridPtr;
typedef std::shared_ptr<ToyRobot::IRobot> RobotPtr;


namespace ToyRobot
{
    class Commander
    {
        public:
            Commander() = delete;
            ~Commander() = default;

            Commander( InputReaderPtr input_reader, GridPtr grid );

        private:
            InputReaderPtr input_reader_ = nullptr;
            GridPtr grid_ = nullptr;
            RobotPtr robot_ = nullptr;

        public:
            const std::unordered_map<std::string, const Regex> command_regexes_
            {
                { "PLACE", Regex( "(PLACE)\\s+(\\d+)\\s*,\\s*(\\d+)\\s*,\\s*(NORTH|SOUTH|EAST|WEST)" ) },
                { "MOVE", Regex( "(MOVE)" ) },
                { "ROTATE", Regex( "(LEFT|RIGHT)" ) },
                { "REPORT", Regex( "(REPORT)" ) },
            };

        public:
            void TrackRobot( RobotPtr robot );
            void PlayWithRobot();
            void InterpretCommand( std::string &command );
            static bool IsRegexMatch( const std::string &command, Matches &matches, const Regex &regex );
    };
}

#endif