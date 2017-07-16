//
// KeyboardEvent.cpp for cpp_arcade in /home/antoine/Documents/Projets/C++/cpp_arcade
//
// Made by Antoine MOREL
// Login   <antoine.morel@epitech.eu@epitech.net>
//
// Started on  Mon Mar 20 17:37:49 2017 Antoine MOREL
// Last update Sat Apr 08 15:05:18 2017 Antoine MOREL
//

#include	"Sfml/KeyboardEvent.hpp"

/*
** Elementary
*/

ARCADE::Sfml::KeyboardEvent::KeyboardEvent(const int c) : content(c)
{
}

ARCADE::Sfml::KeyboardEvent::~KeyboardEvent() {}

/*
** Getters
*/

int		ARCADE::Sfml::KeyboardEvent::getContent() const
{
  return (this->content);
}

GUI::Events::EventType	ARCADE::Sfml::KeyboardEvent::getType() const
{
  return (GUI::Events::EventType::KEYBOARD);
}

/*
** Management
*/

GUI::Events::IEvent	&ARCADE::Sfml::createKeyboardEvent(const int c)
{
  ARCADE::Sfml::KeyboardEvent	*event = new KeyboardEvent(c);
  return (*event);
}
