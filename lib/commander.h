#ifndef TOYROBOT_COMMANDER_H
#define TOYROBOT_COMMANDER_H

#include <memory>
#include <queue>
#include <unordered_map>
#include <regex>
#include <string>
#include "input_reader.h"
#include "robot.h"

typedef std::regex Regex;
typedef std::smatch Matches;


namespace ToyRobot
{
    class Commander
    {
        public:
            Commander() = default;
            ~Commander() = default;
            Commander( std::shared_ptr<IInputReader> input_reader );

        private:
            std::unique_ptr<Robot> robot_ = nullptr;
            std::shared_ptr<IInputReader> input_reader_ = nullptr;

            std::unordered_map<std::string, Regex> command_regexes_
            {
                { "PLACE", Regex( "(PLACE)\\s+(\\d+),\\s*(\\d+),\\s*(NORTH|SOUTH|EAST|WEST)" ) },
                { "MOVE", Regex( "(MOVE)" ) },
                { "ROTATE", Regex( "(LEFT|RIGHT)" ) },
                { "REPORT", Regex( "(REPORT)" ) },
            };

        public:
            void TrackRobot( std::unique_ptr<Robot> robot );
            void PlayWithRobot();
            void InterpretCommand( std::string command );

        private:
            bool IsRegexMatch( std::string &command, Matches &matches, Regex &regex );

            void CommandPlace( Matches &matches );
            void CommandMove();
            void CommandRotate( Matches &matches );
            void CommandReport();
    };
}

#endif