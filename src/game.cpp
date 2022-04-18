#include "game.h"
#include <iostream>
#include "SDL.h"


Game::Game(std::size_t grid_width, std::size_t grid_height)
    : snake(grid_width, grid_height),
      _grid_width{grid_width},
      _grid_height{grid_height},
      engine(dev()),
      random_w(0, static_cast<int>(grid_width - 1)),
      random_h(0, static_cast<int>(grid_height - 1)),
      random_obst_dir(0,static_cast<int>(7))
{
  PlaceObstacles(3);
  PlaceFood();
}

void Game::Run(Controller const &controller, Renderer &renderer,
               std::size_t target_frame_duration) {
  Uint32 title_timestamp = SDL_GetTicks();
  Uint32 frame_start;
  Uint32 frame_end;
  Uint32 frame_duration;
  int frame_count = 0;
  bool running = true;

  while (running) {
    frame_start = SDL_GetTicks();

    // Input, Update, Render - the main game loop.
    controller.HandleInput(running, snake);
    Update();
    renderer.Render(snake, food, obstacles);

    frame_end = SDL_GetTicks();

    // Keep track of how long each loop through the input/update/render cycle
    // takes.
    frame_count++;
    frame_duration = frame_end - frame_start;

    // After every second, update the window title.
    if (frame_end - title_timestamp >= 1000) {
      renderer.UpdateWindowTitle(score, frame_count);
      frame_count = 0;
      title_timestamp = frame_end;
    }

    // If the time for this frame is too small (i.e. frame_duration is
    // smaller than the target ms_per_frame), delay the loop to
    // achieve the correct frame rate.
    if (frame_duration < target_frame_duration) {
      SDL_Delay(target_frame_duration - frame_duration);
    }
  }
}

void Game::PlaceFood() {
  int x, y;
  while (true) {
    x = random_w(engine);
    y = random_h(engine);
    // Check that the location is not occupied by a snake item before placing
    // food.
    if (!snake.SnakeCell(x, y)) {
      bool is_obstacle_location = false;
      for (const Obstacle& obstacle : obstacles )
      {
        if (x == obstacle.get_x() && y == obstacle.get_y())
          is_obstacle_location = true;
      }
      if(is_obstacle_location)
        continue;

      food.x = x;
      food.y = y;
      return;
    }
  }
}

void Game::PlaceObstacles (int n) {
  for (int i = 0; i < n ; ++i) {
    int x,y;
    while (true) {
      x = random_w(engine);
      y = random_h(engine);

      // Check that the location is not occupied by a snake item before placing obstacle.
      if (!snake.SnakeCell(x, y)) {
        int obst_dir = random_obst_dir(engine);
        std::cout << "Obstacle " << i << ": X= " << x << "   Y= " << y << "   Dir: " << obst_dir << std::endl; 
        obstacles.emplace_back(x,y, _grid_width, _grid_height, obst_dir);
        break;
      }
    
    }
  }
}

void Game::Update() {
  if (!snake.alive) return;

  snake.Update();

  int new_x = static_cast<int>(snake.head_x);
  int new_y = static_cast<int>(snake.head_y);

  bool is_obstacle_location = false;
  for (const Obstacle& obstacle : obstacles)
  {
     if (new_x == obstacle.get_x() && new_y == obstacle.get_y())
       is_obstacle_location = true;
  }
  if (is_obstacle_location)
  {
    snake.alive = false;
    return;
  }
  // Check if there's food over here
  if (food.x == new_x && food.y == new_y) {
    score++;
    PlaceFood();
    // Grow snake and increase speed.
    snake.GrowBody();
    snake.speed += 0.02;
  }
  for (Obstacle& obstacle : obstacles)
  {
      obstacle.update();
  }
}

int Game::GetScore() const { return score; }
int Game::GetSize() const { return snake.size; }