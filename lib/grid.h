#ifndef TOYROBOT_GRID_H
#define TOYROBOT_GRID_H


namespace ToyRobot
{
    struct Coordinates
    {
        int x;
        int y;

        Coordinates() = default;
        Coordinates( int a, int b )
        {
            x = a;
            y = b;
        }
    };

    class Grid
    {
        public:
            Grid() = delete;
            ~Grid() = default;
            explicit Grid( Coordinates &coordinates );

        private:
            Coordinates coordinates_;

        public:
            bool IsWithinGrid( Coordinates &coordinates );
    };
}

#endif