set( TARGET LIB_TOYROBOT )

add_library( ${TARGET} 
    grid.h
    grid.cpp
    robot.h
    robot.cpp
    input_reader.h
    input_reader.cpp
    commander.h
    commander.cpp
)