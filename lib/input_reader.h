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
            std::queue<std::string> command_queue_;

        public:
            virtual void ReadLines() = 0;
    };

    class ConsoleReader : public IInputReader
    {
        public:
            ConsoleReader() = default;
            ~ConsoleReader() = default;

        public:
            void ReadLines() override;
    };

    class FileReader : public IInputReader
    {
        public:
            FileReader() = delete;
            ~FileReader() = default;
            explicit FileReader( std::string &file_path );

        private:
            std::string file_path_;

        public:
            void ReadLines() override;
    };

    static void trim_left( std::string &command );
    static void trim_right( std::string &command );
    static void clean_command( std::string &command );
}

#endif