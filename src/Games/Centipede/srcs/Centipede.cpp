//
// Centipede.cpp for cpp_arcade in /home/dylan/Documents/TEK2/cpp_arcade
//
// Made by Dylan Deu
// Login   <dylan.deu@epitech.net>
//
// Started on  Fri Mar 31 14:48:25 2017 Dylan Deu
// Last update Tue Apr 04 17:33:17 2017 Dylan Deu
//

#include 		<iostream>
#include		<unistd.h>
#include		"Protocol.hpp"
#include		"Obstacle.hpp"
#include		"Centipede.hpp"

Game::Centipede::Centipede()
{
  unsigned int		index(0);
  unsigned int		x;
  unsigned int		y(0);

  this->_refresh = 200;
  this->_nbCentipede = 0;
  this->_evilDudeSize = 10;
  this->_score = 0;
  this->_generate = true;
  this->_obstacles = new std::vector<Game::Obstacle *>;
  this->_deactivateTimer = false;

  this->_map = new arcade::GetMap[sizeof(arcade::GetMap) + (40 * 40 * sizeof(arcade::TileType))];
  this->_map->type = arcade::CommandType::GET_MAP;
  this->_map->width = 40;
  this->_map->height = 40;
  while (y < this->_map->width)
  {
    x = 0;
    while (x < this->_map->width)
    {
      this->_map->tile[y * this->_map->width + x] = arcade::TileType::EMPTY;
      x++;
    }
    y++;
  }

  this->_pos = new arcade::WhereAmI[sizeof(arcade::WhereAmI) + (sizeof(arcade::Position))];
  this->_pos->type = arcade::CommandType::WHERE_AM_I;
  this->_pos->lenght = 1;
  this->_pos->position->y = static_cast<uint16_t>(this->_map->height - 1);
  this->_pos->position->x = static_cast<uint16_t>(this->_map->width / 2);

  this->_evilDudePos.reserve(this->_evilDudeSize);
  while (index < this->_evilDudeSize)
  {
    arcade::Position		pos;

    if (index == 0)
    {
      pos.x = 0;
      pos.y = 0;
    }
    else
    {
      pos.x = 42;
      pos.y = 42;
    }
    this->_evilDudePos.push_back(pos);
    index++;
  }

  this->_generate = this->generateObstacle();
  this->putDudeOnMap();
  this->updateTime();
}

Game::Centipede::~Centipede()
{
  if (this->_map)
  {
    delete[](this->_map);
    this->_map = NULL;
  }
  if (this->_pos)
  {
    delete[](this->_pos);
    this->_pos = NULL;
  }
  while (!this->_obstacles->empty())
  {
    delete ((*this->_obstacles)[0]);
    this->_obstacles->erase(this->_obstacles->begin());
  }
  if (this->_obstacles)
  {
    delete(this->_obstacles);
    this->_obstacles = NULL;
  }
}

void			Game::Centipede::moveDude()
{
  unsigned int		index(0);

  while (index < this->_evilDudePos.size())
  {
    if ((this->_evilDudePos[index].x == this->_map->width && this->_evilDudePos[index].y == this->_map->height)
      || (this->_evilDudePos[index].x == 0 && this->_evilDudePos[index].y == this->_map->height - 1)
      || (this->_evilDudePos[index].y >= this->_map->height && this->_evilDudePos[index].x != 42))
    {
      if (!this->_evilDudePos.empty())
	this->_evilDudePos.erase(this->_evilDudePos.begin() + index);
    }
    if (this->_evilDudePos[index].x == 42)
    {
      this->_evilDudePos[index].x = 0;
      this->_evilDudePos[index].y = 0;
      break;
    }
    if (this->_evilDudePos[index].y % 2 == 0)
    {
      if ((this->_evilDudePos[index].x + 1 >= this->_map->width)
	    || (this->_map->tile[this->_evilDudePos[index].y * this->_map->width + (this->_evilDudePos[index].x + 1)] == arcade::TileType::OBSTACLE))
      {
	this->_evilDudePos[index].y += 1;
	if (this->_evilDudePos[index].y == this->_map->height - 1 && this->_score >= 50)
	  this->_score -= 50;
      }
      else
	this->_evilDudePos[index].x += 1;
    }
    else
    {
      if ((this->_evilDudePos[index].x - 1 < 0) || (this->_map->tile[this->_evilDudePos[index].y * this->_map->width + (this->_evilDudePos[index].x - 1)] == arcade::TileType::OBSTACLE))
      {
	this->_evilDudePos[index].y += 1;
	if (this->_evilDudePos[index].y == this->_map->height - 1 && this->_score >= 50)
	  this->_score -= 50;
      }
      else
	this->_evilDudePos[index].x -= 1;
    }
    index++;
  }
}

void			Game::Centipede::putDudeOnMap()
{
  unsigned int		x;
  unsigned int		y(0);
  unsigned int		index(0);

  while (y < this->_map->height)
  {
    x = 0;
    while (x < this->_map->width)
    {
      if (this->_map->tile[y * this->_map->width + x] == arcade::TileType::EVIL_DUDE)
	this->_map->tile[y * this->_map->width + x] = arcade::TileType::EMPTY;
      if (this->_map->tile[y * this->_map->width + x] == arcade::TileType::OBSTACLE)
	this->_map->tile[y * this->_map->width + x] = arcade::TileType::EMPTY;
      if (this->_map->tile[y * this->_map->width + x] == arcade::TileType::MY_SHOOT)
	this->_map->tile[y * this->_map->width + x] = arcade::TileType::EMPTY;
      x++;
    }
    y++;
  }
  while (index < this->_evilDudePos.size())
  {
    if (this->_evilDudePos[index].x != 42)
      this->_map->tile[this->_evilDudePos[index].y * this->_map->width + this->_evilDudePos[index].x] = arcade::TileType::EVIL_DUDE;
    index++;
  }
  index = 0;
  while (index < this->_obstacles->size())
  {
    this->_map->tile[(*this->_obstacles)[index]->getPos().y * this->_map->height + (*this->_obstacles)[index]->getPos().x] = arcade::TileType::OBSTACLE;
    index++;
  }
  index = 0;
  while (index < this->_shootPos.size())
  {
    this->_map->tile[this->_shootPos[index].y * this->_map->height + this->_shootPos[index].x] = arcade::TileType::MY_SHOOT;
    index++;
  }
}

bool			Game::Centipede::generateObstacle()
{
  int		y(0);
  int		x;

  while (y < this->_map->height - 2)
  {
    Game::Obstacle	*obs1 = new Game::Obstacle();
    Game::Obstacle	*obs2 = new Game::Obstacle();

    x = rand() % this->_map->width;
    if (x == 0 && y == 0)
      x += 1;
    obs1->setPos(x, y);

    x = rand() % this->_map->width;
    if (x == 0 && y == 0)
      x += 1;
    obs2->setPos(x, y);

    this->_obstacles->push_back(obs1);
    this->_obstacles->push_back(obs2);
    y++;
  }
  return (false);
}

void			Game::Centipede::regenerateObstacle()
{
  this->_nbCentipede = 0;
  this->_generate = true;
  while (!this->_obstacles->empty())
    this->_obstacles->erase(this->_obstacles->begin());
}

void			Game::Centipede::movePlayer(const arcade::CommandType type)
{
  switch(type)
  {
    case arcade::CommandType::GO_LEFT : {
      if (this->_pos->position->x - 1 >= 0 && this->_map->tile[this->_pos->position->y * this->_map->width + (this->_pos->position->x - 1)] != arcade::TileType::OBSTACLE)
	this->_pos->position->x -= 1;
      break;
    }
    case arcade::CommandType::GO_RIGHT : {
      if (this->_pos->position->x + 1 < this->_map->width && this->_map->tile[this->_pos->position->y * this->_map->width + (this->_pos->position->x + 1)] != arcade::TileType::OBSTACLE)
	this->_pos->position->x += 1;
      break;
    }
    case arcade::CommandType::GO_DOWN : {
      if (this->_pos->position->y + 1 < this->_map->width && this->_map->tile[(this->_pos->position->y + 1) * this->_map->width + this->_pos->position->x] != arcade::TileType::OBSTACLE)
      	this->_pos->position->y += 1;
      break;
    }
    case arcade::CommandType::GO_UP : {
      if (this->_pos->position->y - 1 > (this->_map->width - (this->_map->height * 0.2)) && this->_map->tile[(this->_pos->position->y - 1) * this->_map->width + this->_pos->position->x] != arcade::TileType::OBSTACLE)
	this->_pos->position->y -= 1;
      break;
    }
    case arcade::CommandType::SHOOT : {
      if (this->_map->tile[(this->_pos->position->y - 1) * this->_map->height + this->_pos->position->x] == arcade::TileType::MY_SHOOT
	|| this->_map->tile[(this->_pos->position->y - 2) * this->_map->height + this->_pos->position->x] == arcade::TileType::MY_SHOOT)
	break;

      arcade::Position	pos;

      pos.x = this->_pos->position->x;
      pos.y = this->_pos->position->y - 1;
      this->_shootPos.push_back(pos);
      break;
    }
    default :
      break;
  }
}

void			Game::Centipede::moveMyShoot()
{
  unsigned int		index(0);

  while (index < this->_shootPos.size())
  {
    if (this->_shootPos[index].y - 1 < 0)
    {
      this->_shootPos.erase(this->_shootPos.begin() + index);
      index -= 1;
      continue;
    }
    this->_shootPos[index].y -= 1;
    index++;
  }
}

void			Game::Centipede::destroyBlock(unsigned int x, unsigned int y)
{
  unsigned int		index(0);

  while (index < this->_obstacles->size())
  {
    if ((*this->_obstacles)[index]->getPos().x == x && (*this->_obstacles)[index]->getPos().y == y)
    {
      (*this->_obstacles)[index]->setLive(1);
      if ((*this->_obstacles)[index]->getLive() == 0)
      {
	delete ((*this->_obstacles)[index]);
	this->_obstacles->erase(this->_obstacles->begin() + index);
	this->_score += 10;
	index -= 1;
      }
    }
    index++;
  }
}

void			Game::Centipede::destroySnake(unsigned int x, unsigned int y)
{
  unsigned int		index(0);

  while (index < this->_evilDudePos.size())
  {
    if (this->_evilDudePos[index].x == x && this->_evilDudePos[index].y == y)
    {
      Game::Obstacle	*obs = new Game::Obstacle();

      obs->setPos(this->_evilDudePos[index].x, this->_evilDudePos[index].y);
      this->_map->tile[obs->getPos().y * this->_map->width + obs->getPos().x] = arcade::TileType::OBSTACLE;
      this->_obstacles->push_back(obs);
      this->_evilDudePos.erase(this->_evilDudePos.begin() + index);
      index -= 1;
      this->_score += 100;
    }
    index++;
  }
}

void			Game::Centipede::checkKill()
{
  int		index(0);
  int		indexDude;

  while (index < static_cast<int>(this->_shootPos.size()))
  {
    indexDude = 0;
    while (indexDude < static_cast<int>(this->_evilDudePos.size()))
    {
      if (this->_shootPos[index].x == this->_evilDudePos[indexDude].x &&
	  this->_shootPos[index].y == this->_evilDudePos[indexDude].y)
      {
	this->destroySnake(this->_evilDudePos[indexDude].x, this->_evilDudePos[indexDude].y);
	if (!this->_shootPos.empty())
	  this->_shootPos.erase(this->_shootPos.begin() + index);
	index -= 1;
	if (index < 0)
	  index = 0;
	indexDude -= 1;
      }
      indexDude++;
    }
    if (this->_map->tile[this->_shootPos[index].y * this->_map->width + this->_shootPos[index].x] == arcade::TileType::OBSTACLE)
    {
      this->destroyBlock(this->_shootPos[index].x, this->_shootPos[index].y);
      if (!this->_shootPos.empty())
	this->_shootPos.erase(this->_shootPos.begin() + index);
      index -= 1;
    }
    index++;
  }
}

bool			Game::Centipede::amIDead()
{
  unsigned int		index(0);

  while (index < this->_evilDudePos.size())
  {
    if (this->_pos->position->x == this->_evilDudePos[index].x && this->_pos->position->y == this->_evilDudePos[index].y)
      return (true);
    index++;
  }
  return (false);
}

bool			Game::Centipede::putAction(const arcade::CommandType action)
{
  std::chrono::milliseconds	time;

  time = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch());
  if (this->_time.count() + this->_refresh > time.count() && action == arcade::CommandType::PLAY && !this->_deactivateTimer)
    return (true);
  this->speed();
  if (this->_evilDudePos.empty())
    regenerateEvilDude();
  if (this->_nbCentipede >= 10)
    regenerateObstacle();
  if (this->_generate)
    this->_generate = this->generateObstacle();
  this->moveMyShoot();
  this->movePlayer(action);
  this->checkKill();
  this->moveDude();
  if (this->amIDead())
    return (false);
  this->putDudeOnMap();
  this->updateTime();
  return (true);
}

void			Game::Centipede::speed()
{
  if (this->_refresh > 50)
    this->_refresh -= 1;
}

void			Game::Centipede::updateTime()
{
  this->_time = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch());
}

void			Game::Centipede::regenerateEvilDude()
{
  unsigned int		index(0);

  this->_nbCentipede += 1;
  this->_refresh = 200;
  while (index < this->_evilDudeSize)
  {
    arcade::Position	pos;

    pos.x = 42;
    pos.y = 42;
    this->_evilDudePos.push_back(pos);
    index++;
  }
}

bool			Game::Centipede::readGame(int fd, char *buff, unsigned int size)
{
  read(fd, buff, size);
  return (true);
}

void			Game::Centipede::deactivateTimer()
{
  this->_deactivateTimer = true;
}

arcade::GetMap		&Game::Centipede::getMap() const
{
  return (*(this->_map));
}

arcade::WhereAmI	&Game::Centipede::getWhereAmI() const
{
  return (*(this->_pos));
}

unsigned long int	Game::Centipede::getScore() const
{
  return (_score);
}

std::string		Game::Centipede::getName() const
{
  return ("centipede");
}

Game::IGame		&createGame(void)
{
  return (*(new Game::Centipede()));
}
