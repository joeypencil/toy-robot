#ifndef TOYROBOT_COORDINATES_H
#define TOYROBOT_COORDINATES_H


namespace ToyRobot
{
    class Coordinates
    {
        public:
            Coordinates() = default;
            ~Coordinates() = default;

            explicit Coordinates( const int &x, const int &y );

        private:
            int x_;
            int y_;

        public:
            int GetX();
            int GetY();

            void SetX( int x );
            void SetY( int y );
    };
}

#endif