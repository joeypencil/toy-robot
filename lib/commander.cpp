#include "commander.h"


namespace ToyRobot
{
    Commander::Commander( InputReaderPtr input_reader, GridPtr grid )
    {
        input_reader_ = input_reader;
        grid_ = grid;
    }

    void Commander::TrackRobot( RobotPtr robot )
    {
        robot_ = robot;
    }

    void Commander::PlayWithRobot()
    {
        while( input_reader_->ReadCommand() )
        {
            InterpretCommand( input_reader_->command_ );
        }
    }

    void Commander::InterpretCommand( std::string &command )
    {
        Matches matches;

        if( IsRegexMatch( command, matches, command_regexes_.at( "PLACE" ) ) )
        {
            if( matches.size() < 5 )
                return;

            int x, y;
            std::string face_direction;
            int face_direction_angle;

            x = stoi( matches.str( 2 ) );
            y = stoi( matches.str( 3 ) );
            face_direction = matches.str( 4 );

            CommandController controller( std::make_unique<CommandPlace>( grid_, robot_, Coordinates( x, y ), face_direction ) );
            controller.Execute();
        }
        else
        {
            if( robot_->IsPlaced() )
            {
                if( IsRegexMatch( command, matches, command_regexes_.at( "MOVE" ) ) )
                {
                    CommandController controller( std::make_unique<CommandMove>( grid_, robot_ ) );
                    controller.Execute();
                }
                else if( IsRegexMatch( command, matches, command_regexes_.at( "ROTATE" ) ) )
                {
                    std::string rotation_direction = matches.str( 1 );

                    CommandController controller( std::make_unique<CommandRotate>( robot_, rotation_direction ) );
                    controller.Execute();
                }
                else if( IsRegexMatch( command, matches, command_regexes_.at( "REPORT" ) ) )
                {
                    CommandController controller( std::make_unique<CommandReport>( robot_ ) );
                    controller.Execute();
                }
            }
        }
    }

    bool Commander::IsRegexMatch( const std::string &command, Matches &matches, const Regex &regex )
    {
        return ( std::regex_search( command, matches, regex ) ) ? true : false;
    }
}