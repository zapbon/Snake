#ifndef OBSTACLE_H
#define OBSTACLE_H


class Obstacle {

enum class Direction{
    north,
    north_east,
    east,
    south_east,
    south,
    south_west,
    west,
    north_west
};

    public:
    Obstacle ();
    Obstacle (int pos_x, int pos_y, int grid_width, int grid_height, int dir);
        void update ();
        int get_x () const {return _x;}
        int get_y () const {return _y;}


    private:
        float _x;
        float _y;
        float _speed;
        Direction _dir;
        int _width;
        int _height;

};

#endif