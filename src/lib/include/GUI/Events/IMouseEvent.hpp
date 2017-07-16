#ifndef		GUI_EVENTS_IMOUSE_EVENT_HPP_
# define	GUI_EVENTS_IMOUSE_EVENT_HPP_

# include "GUI/Events/IEvent.hpp"

namespace		GUI
{
  namespace		Events
  {
    enum class		MouseValue
    {
      RIGHT = 0,
      LEFT = 1
    };

    class		IMouseEvent : public IEvent
    {
    public:
      virtual		~IMouseEvent() {}

      virtual const MouseValue	&getContent() const = 0;
    };
  };
};

extern "C" GUI::Events::IEvent	&createMouseEvent(const GUI::Events::MouseValue &);

#endif
