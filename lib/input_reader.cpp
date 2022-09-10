#include "input_reader.h"


namespace ToyRobot
{
    bool ConsoleReader::ReadCommand()
    {
        std::getline( std::cin, command_ );

        if( ! command_.empty() )
        {
            clean_command( command_ );
            return true;
        }

        return false;
    }

    FileReader::~FileReader()
    {
        filestream_.close();
    }

    void FileReader::SetFilepath( std::string &file_path )
    {
        file_path_ = file_path;
    }

    void FileReader::ReadAllLines()
    {
        filestream_.open( file_path_ );

        if( ! filestream_.is_open() )
        {
            std::cerr << "ERROR: Unable to open file '" << file_path_ << "'" << std::endl;
            filestream_.close();
            exit( 1 );
        }

        while( ! filestream_.eof() )
        {
            std::string line;
            std::getline( filestream_, line );

            if( ! line.empty() )
            {
                clean_command( line );
                command_queue_.push( line );
            }
        }

        filestream_.close();
    }

    bool FileReader::ReadCommand()
    {
        if( ! command_queue_.empty() )
        {
            command_ = command_queue_.front();
            command_queue_.pop();
            return true;
        }

        return false;
    }

    void trim_left( std::string &command )
    {
        command.erase( command.begin(), std::find_if( command.begin(), command.end(), 
            []( unsigned char ch )
            {
                return ! std::isspace( ch );
            } 
            ) );
    }

    void trim_right( std::string &command )
    {
        command.erase( std::find_if( command.rbegin(), command.rend(),
            []( unsigned char ch )
            {
                return ! std::isspace( ch );
            }
            ).base(), command.end() );
    }

    void clean_command( std::string &command )
    {
        trim_left( command );
        trim_right( command );
        std::transform( command.begin(), command.end(), command.begin(), ::toupper );
    }
}