//
// Position.cpp for cpp_arcade in /home/antoine/Documents/Projets/C++/cpp_arcade
//
// Made by Antoine MOREL
// Login   <antoine.morel@epitech.eu@epitech.net>
//
// Started on  Sun Mar 19 16:46:13 2017 Antoine MOREL
// Last update Sat Apr 08 15:00:31 2017 Antoine MOREL
//

#include	"AcQt/Position.hpp"

/*
** Elementary
*/

ARCADE::AcQt::Position::Position(unsigned int y, unsigned int x) : _x(x), _y(y)
{
}

ARCADE::AcQt::Position::Position(const Position &src) : _x(src.getX()), _y(src.getY())
{
}

ARCADE::AcQt::Position::~Position()
{
}

/*
** Getters
*/

unsigned int	ARCADE::AcQt::Position::getX() const
{
  return (this->_x);
}

unsigned int	ARCADE::AcQt::Position::getY() const
{
  return (this->_y);
}

void		ARCADE::AcQt::Position::setX(unsigned int value)
{
  this->_x = value;
}

void		ARCADE::AcQt::Position::setY(unsigned int value)
{
  this->_y = value;
}

/*
** Management
*/

GUI::IPosition	&ARCADE::AcQt::createPosition(unsigned int y, unsigned int x)
{
  ARCADE::AcQt::Position	*position = new Position(y * 20, x * 20);
  return (*position);
}
