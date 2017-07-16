//
// Snake.cpp for cpp_arcade in /home/dylan/Documents/TEK2/cpp_arcade
//
// Made by Dylan Deu
// Login   <dylan.deu@epitech.net>
//
// Started on  Thu Mar 23 13:21:48 2017 Dylan Deu
// Last update Wed Apr 05 18:43:07 2017 Dylan Deu
//

#include		<iostream>
#include		<unistd.h>
#include		"Snake.hpp"
#include		"Exception.hpp"

Game::Snake::Snake()
{
  int		x;
  int		y(0);

  this->_score = 0;
  this->_deactivateTimer = false;
  this->_gameOver = 0;
  this->_map_size = 20;
  this->_refresh = 300;
  this->_map = static_cast<arcade::GetMap *>(malloc(sizeof(arcade::GetMap) + (this->_map_size * this->_map_size * sizeof(arcade::TileType))));
  if (this->_map == NULL)
    throw new Games::Exception("Error: Malloc failed");
  this->_map->type = arcade::CommandType::GET_MAP;
  this->_map->height = this->_map_size;
  this->_map->width = this->_map_size;
  while (y < this->_map_size)
  {
    x = 0;
    while (x < this->_map_size)
    {
      this->_map->tile[y * this->_map_size + x] = arcade::TileType::EMPTY;
      x++;
    }
    y++;
  }

  this->_previous = arcade::CommandType::GO_UP;
  this->_pos = static_cast<arcade::WhereAmI *>(malloc(sizeof(arcade::WhereAmI) + (sizeof(arcade::Position) * 4)));
  if (this->_pos == NULL)
    throw new Games::Exception("Error: Malloc fail");
  this->_pos->lenght = 4;
  this->_pos->type = arcade::CommandType::WHERE_AM_I;
  this->_pos->position[0].x = 10;
  this->_pos->position[0].y = 8;
  this->_pos->position[1].x = 10;
  this->_pos->position[1].y = 9;
  this->_pos->position[2].x = 10;
  this->_pos->position[2].y = 10;
  this->_pos->position[3].x = 10;
  this->_pos->position[3].y = 11;
  this->generateDude();
  this->updateTime();
}

Game::Snake::~Snake()
{
  if (this->_map != NULL)
    free(this->_map);
  if (this->_pos != NULL)
    free(this->_pos);
}

bool			Game::Snake::checkDudeUnderSnake(int x, int y)
{
  int			index(0);

  while (index < this->_pos->lenght)
  {
    if (this->_pos->position[index].x == x && this->_pos->position[index].y == y)
      return (true);
    index++;
  }
  return (false);
}

void			Game::Snake::generateDude()
{
  int			x;
  int			y;
  int			loop(0);

  srand(time(NULL));
  while (loop < 100)
  {
    x = rand() % this->_map_size;
    y = rand() % this->_map_size;
    if (this->_map->tile[y * this->_map_size + x] == arcade::TileType::EMPTY && !checkDudeUnderSnake(x, y))
    {
      this->_map->tile[y * this->_map_size + x] = arcade::TileType::POWERUP;
      break;
    }
    loop++;
  }
  if (loop >= 5)
  {
    y = 0;
    while (y < this->_map_size)
    {
      x = 0;
      while (x < this->_map_size)
      {
	if (this->_map->tile[y * this->_map_size + x] == arcade::TileType::EMPTY && !checkDudeUnderSnake(x, y))
	{
	  this->_map->tile[y * this->_map_size + x] = arcade::TileType::POWERUP;
	  break;
	}
	x++;
      }
      if (this->_map->tile[y * this->_map_size + x] == arcade::TileType::POWERUP)
	break;
      y++;
    }
  }
}

bool			Game::Snake::checkSnakePos()
{
  int			index(1);
  int			x(this->_pos->position[0].x);
  int			y(this->_pos->position[0].y);

  if (this->_pos->lenght >= this->_map_size * this->_map_size)
    return (false);
  if (x < 0 || x >= this->_map_size)
    return (false);
  if (y < 0 || y >= this->_map_size)
    return (false);
  while (index < this->_pos->lenght)
  {
    if (this->_pos->position[index].x == x && this->_pos->position[index].y == y)
    {
      this->_gameOver = 1;
      return (false);
    }
    index++;
  }
  return (true);
}

void			Game::Snake::updateTime()
{
  this->_time = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch());
}

bool			Game::Snake::moveSnake()
{
  int			index(this->_pos->lenght);

  index--;
  while (index >= 1)
  {
    this->_pos->position[index].x = this->_pos->position[index - 1].x;
    this->_pos->position[index].y = this->_pos->position[index - 1].y;
    index--;
  }
  switch (this->_previous) {
    case arcade::CommandType::GO_LEFT : {
      this->_pos->position[0].x -= 1;
      break;
    }
    case arcade::CommandType::GO_RIGHT : {
      this->_pos->position[0].x += 1;
      break;
    }
    case arcade::CommandType::GO_UP : {
      this->_pos->position[0].y -= 1;
      break;
    }
    case arcade::CommandType::GO_DOWN : {
      this->_pos->position[0].y += 1;
      break;
    }
    default :
      break;
  }
  return (true);
}

void			Game::Snake::moveDirection(const arcade::CommandType type)
{
  switch (type)
  {
    case arcade::CommandType::GO_LEFT : {
      if (this->_previous == arcade::CommandType::GO_DOWN)
	this->_previous = arcade::CommandType::GO_LEFT;
      else if (this->_previous == arcade::CommandType::GO_UP)
	this->_previous = arcade::CommandType::GO_LEFT;
      break;
    }
    case arcade::CommandType::GO_RIGHT : {
      if (this->_previous == arcade::CommandType::GO_UP)
	this->_previous = arcade::CommandType::GO_RIGHT;
      else if (this->_previous == arcade::CommandType::GO_DOWN)
	this->_previous = arcade::CommandType::GO_RIGHT;
      break;
    }
    case arcade::CommandType::GO_UP :
    {
      if (this->_previous == arcade::CommandType::GO_LEFT ||
	  this->_previous == arcade::CommandType::GO_RIGHT)
	this->_previous = arcade::CommandType::GO_UP;
      break;
    }
    case arcade::CommandType::GO_DOWN : {
      if (this->_previous == arcade::CommandType::GO_LEFT ||
	  this->_previous == arcade::CommandType::GO_RIGHT)
	this->_previous = arcade::CommandType::GO_DOWN;
      break;
    }
    default:
      break;
  }
}

bool			Game::Snake::checkDude()
{
  if (this->_map->tile[this->_pos->position[0].y * this->_map_size + this->_pos->position[0].x] == arcade::TileType::POWERUP)
  {
    this->_map->tile[this->_pos->position[0].y * this->_map_size + this->_pos->position[0].x] = arcade::TileType::EMPTY;
    this->_score += 10;
    return (true);
  }
  return (false);
}

void			Game::Snake::expandSnake()
{
  int			index(this->_pos->lenght);

  this->_pos = static_cast<arcade::WhereAmI *>(realloc(this->_pos, sizeof(arcade::WhereAmI) + (sizeof(arcade::Position) * (this->_pos->lenght + 1))));
  if (this->_pos == NULL)
    throw new Games::Exception("Error: Realloc failed");
  if (this->_pos->position[index - 1].x == this->_pos->position[index - 2].x)
  {
    if (this->_pos->position[index - 2].y < this->_pos->position[index - 1].y)
      this->_pos->position[index].y = this->_pos->position[index - 1].y + 1;
    else
      this->_pos->position[index].y = this->_pos->position[index - 1].y - 1;
    this->_pos->position[index].x = this->_pos->position[index - 1].x;
  }
  else if (this->_pos->position[index - 1].y == this->_pos->position[index - 2].y)
  {
    if (this->_pos->position[index - 2].x < this->_pos->position[index - 1].x)
      this->_pos->position[index].x = this->_pos->position[index - 1].x + 1;
    else
      this->_pos->position[index].x = this->_pos->position[index - 1].x - 1;
    this->_pos->position[index].y = this->_pos->position[index - 1].y;
  }
  this->_pos->lenght += 1;
}

bool			Game::Snake::putAction(const arcade::CommandType type)
{
  std::chrono::milliseconds	time;

  time = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch());
  if (this->_gameOver == 1)
    return (false);
  if (((this->_time.count() + this->_refresh > time.count() && type == arcade::CommandType::PLAY) ||
       (this->_time.count() + this->_refresh > time.count() && type == arcade::CommandType::GO_FORWARD)) && !this->_deactivateTimer)
    return (true);
  this->speed();
  this->moveDirection(type);
  this->moveSnake();
  if (!this->checkSnakePos())
    return (false);
  if (checkDude())
  {
    this->generateDude();
    this->expandSnake();
  }
  this->updateTime();
  return (true);
}

void			Game::Snake::speed()
{
  if (this->_refresh > 100)
    this->_refresh -= 1;
}

bool			Game::Snake::readGame(int fd, char *buff, unsigned int size)
{
  read(fd, buff, size);
  return (true);
}

void			Game::Snake::deactivateTimer(void)
{
  this->_deactivateTimer = true;
}

arcade::GetMap		&Game::Snake::getMap(void) const
{
  return (*(this->_map));
}

arcade::WhereAmI	&Game::Snake::getWhereAmI(void) const
{
  return (*(this->_pos));
}

unsigned long int	Game::Snake::getScore(void) const
{
  return (this->_score);
}

std::string		Game::Snake::getName(void) const
{
  return ("snake");
}

Game::IGame		&createGame(void)
{
  return (*(new Game::Snake()));
}
