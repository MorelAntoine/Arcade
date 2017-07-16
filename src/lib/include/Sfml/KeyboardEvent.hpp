//
// KeyboardEvent.hpp for cpp_arcade in /home/antoine/Documents/Projets/C++/cpp_arcade
//
// Made by Antoine MOREL
// Login   <antoine.morel@epitech.eu@epitech.net>
//
// Started on  Mon Mar 20 17:33:20 2017 Antoine MOREL
// Last update Mon Mar 20 17:33:20 2017 Antoine MOREL
//

#ifndef		CPP_ARCADE_KEYBOARDEVENT_HPP_
#define		CPP_ARCADE_KEYBOARDEVENT_HPP_

#include	<SFML/Graphics.hpp>
#include	"GUI/Events/IKeyboardEvent.hpp"

namespace ARCADE
{
  namespace Sfml
  {
    class KeyboardEvent : public GUI::Events::IKeyboardEvent {
    private:
      int				content;

    public:
      KeyboardEvent(const int);
      virtual ~KeyboardEvent();

    public:
      virtual int			getContent() const;
      virtual GUI::Events::EventType	getType() const;
    };

    extern "C" GUI::Events::IEvent	&createKeyboardEvent(const int);
  }
}

#endif		/* !CPP_ARCADE_KEYBOARDEVENT_HPP_ */
