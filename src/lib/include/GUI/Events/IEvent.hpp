//
// IEvent.hpp for cpp_arcade in /home/antoine/Documents/Projets/C++/cpp_arcade
//
// Made by Antoine MOREL
// Login   <antoine.morel@epitech.eu@epitech.net>
//
// Started on  Mon Mar 20 17:31:50 2017 Antoine MOREL
// Last update Mon Mar 20 17:31:50 2017 Antoine MOREL
//

#ifndef		GUI_EVENTS_IEVENT_HPP_
# define	GUI_EVENTS_IEVENT_HPP_

#include	"GUI/Events/EventType.hpp"

namespace		GUI
{
  namespace		Events
  {
    class		IEvent
    {
    public:
      virtual ~IEvent() {}

      virtual EventType	getType() const = 0;
    };
  };
};

#endif
