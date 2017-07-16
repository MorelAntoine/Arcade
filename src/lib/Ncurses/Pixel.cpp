//
// Pixel.cpp for cpp_arcade in /home/antoine/Documents/Projets/C++/cpp_arcade
//
// Made by Antoine MOREL
// Login   <antoine.morel@epitech.eu@epitech.net>
//
// Started on  Sun Mar 19 16:52:05 2017 Antoine MOREL
// Last update Sat Apr 08 14:52:48 2017 Antoine MOREL
//

#include	"Ncurses/Pixel.hpp"

/*
** Elementary
*/

ARCADE::Ncurses::Pixel::Pixel(const ARCADE::Ncurses::Position &pos, const GUI::Color &color) : _position(pos), _color(color)
{
}

ARCADE::Ncurses::Pixel::~Pixel() {}

/*
** Getters
*/

const GUI::IPosition	&ARCADE::Ncurses::Pixel::getPosition() const
{
  return (this->_position);
}

const GUI::Color & ARCADE::Ncurses::Pixel::getColor() const
{
  return (this->_color);
}

/*
** Management
*/

GUI::IPixel		&ARCADE::Ncurses::createPixel(const GUI::IPosition &pos,
							 const GUI::Color &color)
{
  ARCADE::Ncurses::Position	position(pos.getY(), pos.getX());
  ARCADE::Ncurses::Pixel	*pixel = new Pixel(position, color);
  return (*pixel);
}
