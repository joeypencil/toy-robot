#include "input_reader.h"


namespace ToyRobot
{
    void ConsoleReader::ReadLines()
    {
        std::string line;
        
        while( std::getline( std::cin, line ) )
        {
            if( ! line.empty() )
            {
                clean_command( line );
                command_queue_.push( line );
            }
            else
                break;
        }
    }

    FileReader::FileReader( std::string &file_path )
    {
        file_path_ = file_path;
    }

    void FileReader::ReadLines()
    {
        std::ifstream filestream;
        filestream.open( file_path_ );

        if( ! filestream )
        {
            std::cerr << "ERROR: Could not open file '" << file_path_ << "'" << std::endl;
            exit( 1 );
        }

        std::string line;

        while( ! filestream.eof() )
        {
            std::getline( filestream, line );

            if( ! line.empty() )
            {
                clean_command( line );
                command_queue_.push( line );
            }
        }

        filestream.close();
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