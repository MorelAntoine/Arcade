//
// Text.cpp for cpp_arcade in /home/antoine/Documents/Projets/C++/cpp_arcade
//
// Made by Antoine MOREL
// Login   <antoine.morel@epitech.eu@epitech.net>
//
// Started on  Sun Mar 19 16:41:38 2017 Antoine MOREL
// Last update Sat Apr 08 15:02:32 2017 Antoine MOREL
//

#include		"AcQt/Text.hpp"

/*
** Elementary
*/

ARCADE::AcQt::Text::Text(const std::string &str, const GUI::Color &colorText,
			 const GUI::Color &fond,
			 const GUI::IPosition &pos): position(pos.getY(), pos.getX()),
						     colorText(colorText),
						     colorFond(fond),
						     text(str)
{
}

ARCADE::AcQt::Text::~Text() {}

/*
** Getters
*/

const std::string	&ARCADE::AcQt::Text::getText() const
{
  return (this->text);
}

const GUI::IPosition	&ARCADE::AcQt::Text::getPosition() const
{
  return (this->position);
}

const GUI::Color	&ARCADE::AcQt::Text::getColorFore() const
{
  return (this->colorText);
}

const GUI::Color	&ARCADE::AcQt::Text::getColorBack() const
{
  return (this->colorFond);
}

/*
** Management
*/

GUI::IText		&ARCADE::AcQt::createText(const std::string &str, const GUI::Color &colorText, const GUI::Color &fond,
						    const GUI::IPosition &pos)
{
  ARCADE::AcQt::Text	*text = new Text(str, colorText, fond, pos);
  return (*text);
}
