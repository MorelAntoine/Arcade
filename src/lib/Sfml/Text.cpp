//
// Text.cpp for cpp_arcade in /home/antoine/Documents/Projets/C++/cpp_arcade
//
// Made by Antoine MOREL
// Login   <antoine.morel@epitech.eu@epitech.net>
//
// Started on  Sun Mar 19 16:41:38 2017 Antoine MOREL
// Last update Sat Apr 08 15:06:18 2017 Antoine MOREL
//

#include	"Sfml/Text.hpp"

/*
** Elementary
*/

ARCADE::Sfml::Text::Text(const std::string &str, const GUI::Color &colorText,
			 const GUI::Color &fond,
			 const GUI::IPosition &pos): position(pos.getY(), pos.getX()),
						     colorText(colorText),
						     colorFond(fond),
						     text(str)
{
}

ARCADE::Sfml::Text::~Text() {}

/*
** Getters
*/

const std::string	&ARCADE::Sfml::Text::getText() const
{
  return (this->text);
}

const GUI::IPosition	&ARCADE::Sfml::Text::getPosition() const
{
  return (this->position);
}

const GUI::Color	&ARCADE::Sfml::Text::getColorFore() const
{
  return (this->colorText);
}

const GUI::Color	&ARCADE::Sfml::Text::getColorBack() const
{
  return (this->colorFond);
}

/*
** Management
*/

GUI::IText		&ARCADE::Sfml::createText(const std::string &str, const GUI::Color &colorText, const GUI::Color &fond,
						    const GUI::IPosition &pos)
{
  ARCADE::Sfml::Text	*text = new Text(str, colorText, fond, pos);
  return (*text);
}
