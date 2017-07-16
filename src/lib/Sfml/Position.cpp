//
// Position.cpp for cpp_arcade in /home/antoine/Documents/Projets/C++/cpp_arcade
//
// Made by Antoine MOREL
// Login   <antoine.morel@epitech.eu@epitech.net>
//
// Started on  Sun Mar 19 16:46:13 2017 Antoine MOREL
// Last update Sat Apr 08 15:05:49 2017 Antoine MOREL
//

#include	"Sfml/Position.hpp"

/*
** Elementary
*/

ARCADE::Sfml::Position::Position(unsigned int y, unsigned int x) : _x(x), _y(y)
{
}

ARCADE::Sfml::Position::Position(const Position &src) : _x(src.getX()), _y(src.getY())
{
}

ARCADE::Sfml::Position::~Position()
{
}

/*
** Getters
*/

unsigned int	ARCADE::Sfml::Position::getX() const
{
  return (this->_x);
}

unsigned int	ARCADE::Sfml::Position::getY() const
{
  return (this->_y);
}

/*
** Management
*/

GUI::IPosition	&ARCADE::Sfml::createPosition(unsigned int y, unsigned int x)
{
  ARCADE::Sfml::Position	*position = new Position(x * 20, y * 20);
  return (*position);
}
