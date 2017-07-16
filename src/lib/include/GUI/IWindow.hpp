#ifndef		GUI_IWINDOW_HPP_
# define	GUI_IWINDOW_HPP_

# include	<string>
# include	"GUI/IPixel.hpp"
# include	"GUI/IPosition.hpp"
# include	"GUI/IText.hpp"
# include	"GUI/Color.hpp"
#include	"Events/IEvent.hpp"

namespace			GUI
{
  class				IWindow
  {
  public:
    virtual ~IWindow() {};

    virtual bool			Close() = 0;

    virtual bool			drawPixel(const IPixel &pixel) = 0;
    virtual bool			drawSquare(const IPosition &posBegin, const IPosition &posEnd, const Color &color) = 0;
    virtual bool			drawText(const IText &text) = 0;
    virtual const Events::IEvent	*getLastEvent() = 0;

    virtual bool			display() = 0;
  };
};

extern "C" GUI::IWindow		&createWindow(const std::string windowName, int height, int width);

#endif
