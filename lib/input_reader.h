#ifndef TOYROBOT_INPUT_READER_H
#define TOYROBOT_INPUT_READER_H

#include <iostream>
#include <cstdlib>
#include <algorithm>
#include <string>
#include <fstream>
#include <queue>


namespace ToyRobot
{
    class IInputReader
    {
        public:
            IInputReader() = default;
            virtual ~IInputReader() = default;

        public:
            std::string command_;

        public:
            virtual bool ReadCommand() = 0;
    };

    class ConsoleReader : public IInputReader
    {
        public:
            ConsoleReader() = default;
            ~ConsoleReader() = default;

        public:
            bool ReadCommand() override;
    };

    class FileReader : public IInputReader
    {
        public:
            FileReader() = default;
            ~FileReader() = default;

        private:
            std::string file_path_;
            std::ifstream filestream_;
            std::queue<std::string> command_queue_;

        public:
            void SetFilepath( const std::string &file_path );
            bool ReadAllLines();

        public:
            bool ReadCommand() override;
    };

    void trim_left( std::string &command );
    void trim_right( std::string &command );
    void clean_command( std::string &command );
}

#endif