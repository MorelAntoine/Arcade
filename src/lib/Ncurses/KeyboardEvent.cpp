//
// KeyboardEvent.cpp for cpp_arcade in /home/antoine/Documents/Projets/C++/cpp_arcade
//
// Made by Antoine MOREL
// Login   <antoine.morel@epitech.eu@epitech.net>
//
// Started on  Mon Mar 20 17:37:49 2017 Antoine MOREL
// Last update Sat Apr 08 14:52:12 2017 Antoine MOREL
//

#include	"Ncurses/KeyboardEvent.hpp"

/*
** Elementary
*/

ARCADE::Ncurses::KeyboardEvent::KeyboardEvent(const int c) : content(c)
{
}

ARCADE::Ncurses::KeyboardEvent::~KeyboardEvent() {}

/*
** Getters
*/

int		ARCADE::Ncurses::KeyboardEvent::getContent() const
{
  return (this->content);
}

GUI::Events::EventType ARCADE::Ncurses::KeyboardEvent::getType() const
{
  return (GUI::Events::EventType::KEYBOARD);
}

/*
** Management
*/

GUI::Events::IEvent &ARCADE::Ncurses::createKeyboardEvent(const int c)
{
  ARCADE::Ncurses::KeyboardEvent	*event = new KeyboardEvent(c);
  return (*event);
}
