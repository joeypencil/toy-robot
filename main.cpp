#include "input_reader.h"
#include "grid.h"
#include "robot.h"
#include "commander.h"

using namespace ToyRobot;


int main( int argc, char **argv )
{
    Coordinates coordinates( 4, 4 );
    std::shared_ptr<Grid> grid = std::make_shared<Grid>( coordinates );
    std::unique_ptr<Robot> robot = std::make_unique<Robot>( grid );

    if( argc < 2 )
    {
        std::shared_ptr<ConsoleReader> console_reader = std::make_shared<ConsoleReader>();

        std::unique_ptr<Commander> commander = std::make_unique<Commander>( console_reader );
        commander->TrackRobot( move( robot ) );
        commander->PlayWithRobot();
    }
    else if( argc == 2 )
    {
        std::string filename( argv[1] );
        std::shared_ptr<FileReader> file_reader = std::make_shared<FileReader>();
        file_reader->SetFilepath( filename );
        file_reader->ReadAllLines();

        std::unique_ptr<Commander> commander = std::make_unique<Commander>( file_reader );
        commander->TrackRobot( move( robot ) );
        commander->PlayWithRobot();
    }
    else
    {
        std::cerr << "ERROR: Unsupported number of arguments." << std::endl;
        return 1;
    }

    return 0;
}