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

            CommandPlace command_place;
            command_place.SetGrid( grid_ );
            command_place.SetRobot( robot_ );
            command_place.SetLocation( Coordinates( x, y ) );
            command_place.SetFaceDirection( face_direction );
            command_place.Execute();
        }
        else
        {
            if( robot_->IsPlaced() )
            {
                if( IsRegexMatch( command, matches, command_regexes_.at( "MOVE" ) ) )
                {
                    CommandMove command_move;
                    command_move.SetGrid( grid_ );
                    command_move.SetRobot( robot_ );
                    command_move.Execute();
                }
                else if( IsRegexMatch( command, matches, command_regexes_.at( "ROTATE" ) ) )
                {
                    std::string rotation_direction = matches.str( 1 );

                    CommandRotate command_rotate;
                    command_rotate.SetGrid( grid_ );
                    command_rotate.SetRobot( robot_ );
                    command_rotate.SetRotationDirection( rotation_direction );
                    command_rotate.Execute();
                }
                else if( IsRegexMatch( command, matches, command_regexes_.at( "REPORT" ) ) )
                {
                    CommandReport command_report;
                    command_report.SetGrid( grid_ );
                    command_report.SetRobot( robot_ );
                    command_report.Execute();
                }
            }
        }
    }

    bool Commander::IsRegexMatch( const std::string &command, Matches &matches, const Regex &regex )
    {
        return ( std::regex_search( command, matches, regex ) ) ? true : false;
    }
}