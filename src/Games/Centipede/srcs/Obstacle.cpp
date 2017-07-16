//
// Obstacle.cpp for cpp_arcade in /home/dylan/Documents/TEK2/cpp_arcade
//
// Made by Dylan Deu
// Login   <dylan.deu@epitech.net>
//
// Started on  Tue Apr 04 16:54:10 2017 Dylan Deu
// Last update Tue Apr 04 16:54:10 2017 Dylan Deu
//

#include		"Obstacle.hpp"

Game::Obstacle::Obstacle() : _live(5)
{
  _pos.x = 0;
  _pos.y = 0;
}

void			Game::Obstacle::setPos(unsigned int x, unsigned int y)
{
  this->_pos.x = x;
  this->_pos.y = y;
}

void			Game::Obstacle::setLive(unsigned int live)
{
  this->_live -= live;
}

unsigned int		Game::Obstacle::getLive(void)
{
  return (this->_live);
}

arcade::Position	Game::Obstacle::getPos(void)
{
  return (this->_pos);
}
