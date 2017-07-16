#ifndef		GUI_EVENTS_IKEYBOARD_EVENT_HPP_
# define	GUI_EVENTS_IKEYBOARD_EVENT_HPP_

#include	"GUI/Events/IEvent.hpp"

namespace	GUI
{
  namespace	Events
  {
    class	IKeyboardEvent : public IEvent
    {
    public:
      enum class	KeyboardEvents
      {
	NOTHING = 0,
	LEFT = 0x4b,
	RIGHT = 0x4d,
	TOP = 0x48,
	BOTTOM = 0x50,
	ENTER = '\n',
	ESCAPE = 27,
	BACKSPACE = 0xFF,
	NUM2 = 98,
	NUM3 = 99,
	NUM4 = 100,
	NUM5 = 101,
	NUM8 = 104,
	NUM9 = 105,
	SPACE = ' '
      };

    public:
      virtual 		~IKeyboardEvent() {}

      virtual int	getContent() const = 0;
    };
  };
};

extern "C" GUI::Events::IEvent	&createKeyboardEvent(const int);

#endif
