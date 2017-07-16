//
// KeyboardEvent.cpp for cpp_arcade in /home/antoine/Documents/Projets/C++/cpp_arcade
//
// Made by Antoine MOREL
// Login   <antoine.morel@epitech.eu@epitech.net>
//
// Started on  Mon Mar 20 17:37:49 2017 Antoine MOREL
// Last update Sat Apr 08 14:59:21 2017 Antoine MOREL
//

#include	"AcQt/KeyboardEvent.hpp"

/*
** Elementary
*/

ARCADE::AcQt::KeyboardEvent::KeyboardEvent(const int c) : content(c)
{
}

ARCADE::AcQt::KeyboardEvent::~KeyboardEvent() {}

/*
** Getters
*/

int		ARCADE::AcQt::KeyboardEvent::getContent() const
{
  return (this->content);
}

GUI::Events::EventType ARCADE::AcQt::KeyboardEvent::getType() const
{
  return (GUI::Events::EventType::KEYBOARD);
}

/*
** Management
*/

GUI::Events::IEvent &ARCADE::AcQt::createKeyboardEvent(const int c)
{
  ARCADE::AcQt::KeyboardEvent	*event = new KeyboardEvent(c);
  return (*event);
}
