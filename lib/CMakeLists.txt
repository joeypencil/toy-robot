set( TARGET LIB_TOYROBOT )

add_library( ${TARGET} 
    coordinates.h
    coordinates.cpp
    grid.h
    grid.cpp
    robot.h
    robot.cpp
    input_reader.h
    input_reader.cpp
    commander.h
    commander.cpp
    command.h
    command.cpp
    command_controller.h
)