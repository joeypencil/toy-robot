#ifndef TOYROBOT_COMMAND_CONTROLLER_H
#define TOYROBOT_COMMAND_CONTROLLER_H

#include "command.h"

typedef std::shared_ptr<ToyRobot::Command> CommandPtr;


namespace ToyRobot
{
    class CommandController
    {
        public:
            CommandController( CommandPtr command )
            {
                command_ = command;
            }
            ~CommandController() = default;

        private:
            CommandPtr command_ = nullptr;

        public:
            void Execute() { command_->Execute(); }
    };
}

#endif