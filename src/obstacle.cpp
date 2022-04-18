#include "obstacle.h"
#include <cmath>

Obstacle::Obstacle (){}
Obstacle::Obstacle (int pos_x, int pos_y, int grid_width, int grid_height, int dir)
    :   _x{pos_x},
        _y{pos_y},
        _speed{0.05f},
        _width{grid_width},
        _height{grid_height}
{
    switch (dir) {
        case(0) :
        _dir = Direction::north;
        break;
        case(1) :
        _dir = Direction::north_east;
        break;
        case(2) :
        _dir = Direction::east;
        break;
        case(3) :
        _dir = Direction::south_east;
        break;
        case(4) :
        _dir = Direction::south;
        break;
        case(5) :
        _dir = Direction::south_west;
        break;
        case(6) :
        _dir = Direction::west;
        break;
        case(7) :
        _dir = Direction::north_west;
        break;   
            
    }
}

void Obstacle::update () {
    switch (_dir) {
        case Direction::north:
        _y -= _speed;
        break;

        case Direction::north_east:
        _y -= _speed;
        _x += _speed;
        break;

        case Direction::east:
        _x += _speed;
        break;

        case Direction::south_east:
        _x += _speed;
        _y += _speed;
        break;

        case Direction::south:
        _y += _speed;
        break;

        case Direction::south_west:
        _y += _speed;
        _x -= _speed;
        break;

        case Direction::west:
        _x -= _speed;
        break;

        case Direction::north_west:
        _x -= _speed;
        _y -= _speed;
        break;
   }
  _x = fmod(_x + _width, _width);
  _y = fmod(_y + _height, _height);
}