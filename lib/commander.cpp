#include "commander.h"


namespace ToyRobot
{
    Commander::Commander( std::shared_ptr<IInputReader> input_reader )
    {
        input_reader_ = input_reader;
    }

    void Commander::TrackRobot( std::unique_ptr<Robot> robot )
    {
        robot_ = move( robot );
    }

    void Commander::PlayWithRobot()
    {
        while( input_reader_->ReadCommand() )
        {
            InterpretCommand( input_reader_->command_ );
        }
    }

    void Commander::InterpretCommand( std::string command )
    {
        Matches matches;

        if( IsRegexMatch( command, matches, command_regexes_["PLACE"] ) )
            CommandPlace( matches );
        else
        {
            if( robot_->IsPlaced() )
            {
                if( IsRegexMatch( command, matches, command_regexes_["REPORT"] ) )
                    CommandReport();
                else if( IsRegexMatch( command, matches, command_regexes_["MOVE"] ) )
                    CommandMove();
                else if( IsRegexMatch( command, matches, command_regexes_["ROTATE"] ) )
                    CommandRotate( matches );
            }
        }
    }

    bool Commander::IsRegexMatch( std::string &command, Matches &matches, Regex &regex )
    {
        return ( std::regex_search( command, matches, regex ) ) ? true : false;
    }

    void Commander::CommandPlace( Matches &matches )
    {
        if( matches.size() < 5 )
            return;

        int x, y;
        std::string face_direction;
        int face_direction_angle;

        x = stoi( matches.str( 2 ) );
        y = stoi( matches.str( 3 ) );
        face_direction = matches.str( 4 );

        if( ! robot_->GetGrid()->IsWithinGrid( Coordinates( x, y ) ) )
            return;

        std::for_each( robot_->angle_direction_map_.begin(), robot_->angle_direction_map_.end(),
            [&face_direction, &face_direction_angle]( const std::pair<int, std::string> &angle_map )
            {
                if( angle_map.second == face_direction )
                    face_direction_angle = angle_map.first;
            }
        );

        robot_->SetCoordinates( Coordinates( x, y ) );
        robot_->SetFaceDirectionAngle( face_direction_angle );
    }

    void Commander::CommandMove()
    {
        Coordinates current_coordinates = robot_->GetCoordinates();
        int face_direction_angle = robot_->GetFaceDirectionAngle();
        
        Coordinates pending_move;

        std::for_each( robot_->angle_coordinates_map_.begin(), robot_->angle_coordinates_map_.end(),
            [&face_direction_angle, &pending_move]( const std::pair<int, Coordinates> &angle_map )
            {
                if( angle_map.first == face_direction_angle )
                    pending_move = angle_map.second;
            }
        );

        Coordinates pending_location( current_coordinates.x + pending_move.x, current_coordinates.y + pending_move.y );

        if( robot_->GetGrid()->IsWithinGrid( pending_location ) )
            robot_->SetCoordinates( pending_location );
    }

    void Commander::CommandRotate( Matches &matches )
    {
        int current_face_direction_angle = robot_->GetFaceDirectionAngle();
        robot_->SetFaceDirectionAngle( current_face_direction_angle + robot_->rotation_map_[matches.str( 1 )] );
    }

    void Commander::CommandReport()
    {
        Coordinates coordinates = robot_->GetCoordinates();

        std::cout << coordinates.x << "," << coordinates.y << "," << robot_->GetFaceDirection() << std::endl;
    }
}