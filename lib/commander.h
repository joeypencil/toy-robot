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
            Commander() = delete;
            ~Commander() = default;
            explicit Commander( std::queue<std::string> &command_queue );

        private:
            std::unique_ptr<Robot> robot_ = nullptr;
            std::queue<std::string> &command_queue_;

            std::unordered_map<std::string, Regex> command_regexes_
            {
                { "PLACE", Regex( "(PLACE)\\s+(\\d+),\\s*(\\d+),\\s*(NORTH|SOUTH|EAST|WEST)" ) },
                { "MOVE", Regex( "(MOVE)" ) },
                { "ROTATE", Regex( "(LEFT|RIGHT)" ) },
                { "REPORT", Regex( "(REPORT)" ) },
            };

        public:
            void TrackRobot( std::unique_ptr<Robot> robot );
            void InterpretCommands();

        private:
            bool IsRegexMatch( std::string &command, Matches &matches, Regex &regex );

            void CommandPlace( Matches &matches );
            void CommandMove();
            void CommandRotate( Matches &matches );
            void CommandReport();
    };
}

#endif