#include "input_reader.h"
#include "grid.h"
#include "robot.h"
#include "commander.h"

using namespace ToyRobot;


int main( int argc, char *argv[] )
{
    if( argc > 2 )
    {
        std::cerr << "ERROR: Unsupported number of arguments." << std::endl;
        return 1;
    }

    int length = 4, width = 4;
    Coordinates coordinates( length, width );
    auto grid = std::make_shared<Grid>( coordinates );
    auto robot = std::make_unique<Robot>( grid );

    if( argc < 2 )
    {
        auto console_reader = std::make_shared<ConsoleReader>();

        auto commander = std::make_unique<Commander>( console_reader );
        commander->TrackRobot( move( robot ) );
        commander->PlayWithRobot();
    }
    else if( argc == 2 )
    {
        std::string filename( argv[1] );
        auto file_reader = std::make_shared<FileReader>();
        file_reader->SetFilepath( filename );

        if( ! file_reader->ReadAllLines() )
            return 1;

        auto commander = std::make_unique<Commander>( file_reader );
        commander->TrackRobot( move( robot ) );
        commander->PlayWithRobot();
    }

    return 0;
}