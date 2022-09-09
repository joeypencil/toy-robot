#include "input_reader.h"
#include "grid.h"
#include "robot.h"
#include "commander.h"

using namespace ToyRobot;


int main( int argc, char **argv )
{
    Coordinates coordinates( 4, 4 );
    std::shared_ptr<Grid> grid = std::make_shared<Grid>( coordinates );
    std::shared_ptr<Robot> robot = std::make_shared<Robot>( grid );

    if( argc < 2 )
    {
        std::unique_ptr<ConsoleReader> console_reader = std::make_unique<ConsoleReader>();
        console_reader->ReadLines();

        std::unique_ptr<Commander> commander = std::make_unique<Commander>( robot, console_reader->command_queue_ );
        commander->InterpretCommands();
    }
    else if( argc == 2 )
    {
        std::string filename( argv[1] );
        std::unique_ptr<FileReader> file_reader = std::make_unique<FileReader>( filename );
        file_reader->ReadLines();

        std::unique_ptr<Commander> commander = std::make_unique<Commander>( robot, file_reader->command_queue_ );
        commander->InterpretCommands();
    }
    else
    {
        std::cerr << "ERROR: Unsupported number of arguments." << std::endl;
        return 1;
    }

    return 0;
}