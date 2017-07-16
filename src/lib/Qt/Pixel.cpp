//
// Pixel.cpp for cpp_arcade in /home/antoine/Documents/Projets/C++/cpp_arcade
//
// Made by Antoine MOREL
// Login   <antoine.morel@epitech.eu@epitech.net>
//
// Started on  Sun Mar 19 16:52:05 2017 Antoine MOREL
// Last update Sat Apr 08 14:59:51 2017 Antoine MOREL
//

#include	"AcQt/Pixel.hpp"

/*
** Elementary
*/

ARCADE::AcQt::Pixel::Pixel(const ARCADE::AcQt::Position &pos, const GUI::Color &color) : _position(pos), _color(color)
{
}

ARCADE::AcQt::Pixel::~Pixel() {}

/*
** Getters
*/

const GUI::IPosition	&ARCADE::AcQt::Pixel::getPosition() const
{
  return (this->_position);
}

const GUI::Color	&ARCADE::AcQt::Pixel::getColor() const
{
  return (this->_color);
}

void			ARCADE::AcQt::Pixel::setPosition(const Position &pos)
{
  this->_position = pos;
}

/*
** Management
*/

GUI::IPixel		&ARCADE::AcQt::createPixel(const GUI::IPosition &pos,
						      const GUI::Color &color)
{
  ARCADE::AcQt::Position	position(pos.getY(), pos.getX());
  ARCADE::AcQt::Pixel		*pixel = new Pixel(position, color);
  return (*pixel);
}
