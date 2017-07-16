//
// Position.cpp for cpp_arcade in /home/antoine/Documents/Projets/C++/cpp_arcade
//
// Made by Antoine MOREL
// Login   <antoine.morel@epitech.eu@epitech.net>
//
// Started on  Sun Mar 19 16:46:13 2017 Antoine MOREL
// Last update Wed Mar 22 14:42:09 2017 Antoine MOREL
//

#include	"Ncurses/Position.hpp"

/*
** Elementary
*/

ARCADE::Ncurses::Position::Position(unsigned int y, unsigned int x) : _x(x), _y(y)
{
}

ARCADE::Ncurses::Position::Position(const Position &src) : _x(src.getX()), _y(src.getY())
{
}

ARCADE::Ncurses::Position::~Position()
{
}

/*
** Getters
*/

unsigned int		ARCADE::Ncurses::Position::getX() const
{
  return (this->_x);
}

unsigned int		ARCADE::Ncurses::Position::getY() const
{
  return (this->_y);
}

/*
** Management
*/

GUI::IPosition		&ARCADE::Ncurses::createPosition(unsigned int y, unsigned int x)
{
  ARCADE::Ncurses::Position	*position = new Position(y, x);
  return (*position);
}
