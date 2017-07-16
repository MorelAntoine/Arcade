//
// Text.cpp for cpp_arcade in /home/antoine/Documents/Projets/C++/cpp_arcade
//
// Made by Antoine MOREL
// Login   <antoine.morel@epitech.eu@epitech.net>
//
// Started on  Sun Mar 19 16:41:38 2017 Antoine MOREL
// Last update Wed Mar 22 14:45:15 2017 Antoine MOREL
//

#include	"Ncurses/Text.hpp"

/*
** Elementary
*/

ARCADE::Ncurses::Text::Text(const std::string &str, const GUI::Color &colorText,
			 const GUI::Color &fond,
			 const GUI::IPosition &pos): position(pos.getY(), pos.getX()),
						     colorText(colorText),
						     colorFond(fond),
						     text(str)
{
}

ARCADE::Ncurses::Text::~Text() {}

/*
** Getters
*/

const std::string	&ARCADE::Ncurses::Text::getText() const
{
  return (this->text);
}

const GUI::IPosition	&ARCADE::Ncurses::Text::getPosition() const
{
  return (this->position);
}

const GUI::Color	&ARCADE::Ncurses::Text::getColorFore() const
{
  return (this->colorText);
}

const GUI::Color	&ARCADE::Ncurses::Text::getColorBack() const
{
  return (this->colorFond);
}

/*
** Management
*/

GUI::IText		&ARCADE::Ncurses::createText(const std::string &str, const GUI::Color &colorText,
						       const GUI::Color &fond, const GUI::IPosition &pos)
{
  ARCADE::Ncurses::Text		*text = new Text(str, colorText, fond, pos);
  return (*text);
}
