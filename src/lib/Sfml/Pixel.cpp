//
// Pixel.cpp for cpp_arcade in /home/antoine/Documents/Projets/C++/cpp_arcade
//
// Made by Antoine MOREL
// Login   <antoine.morel@epitech.eu@epitech.net>
//
// Started on  Sun Mar 19 16:52:05 2017 Antoine MOREL
// Last update Sat Apr 08 15:05:25 2017 Antoine MOREL
//

#include	"Sfml/Pixel.hpp"

/*
** Elementary
*/

ARCADE::Sfml::Pixel::Pixel(const ARCADE::Sfml::Position &pos, const GUI::Color &color) : _position(pos), _color(color)
{
}

ARCADE::Sfml::Pixel::~Pixel() {}

/*
** Getters
*/

const GUI::IPosition	&ARCADE::Sfml::Pixel::getPosition() const
{
  return (this->_position);
}

const GUI::Color	&ARCADE::Sfml::Pixel::getColor() const
{
  return (this->_color);
}

/*
** Management
*/

GUI::IPixel		&ARCADE::Sfml::createPixel(const GUI::IPosition &pos,
						      const GUI::Color &color)
{
  ARCADE::Sfml::Position	position(pos.getY(), pos.getX());
  ARCADE::Sfml::Pixel		*pixel = new Pixel(position, color);
  return (*pixel);
}
