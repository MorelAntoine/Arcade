//
// Window.hpp for cpp_arcade in /home/antoine/Documents/Projets/C++/cpp_arcade
//
// Made by Antoine MOREL
// Login   <antoine.morel@epitech.eu@epitech.net>
//
// Started on  Sun Mar 19 12:02:25 2017 Antoine MOREL
// Last update Wed Mar 22 14:46:34 2017 Antoine MOREL
//

#ifndef		CPP_ARCADE_WINDOW_HPP_
# define	CPP_ARCADE_WINDOW_HPP_

#include	<ncurses.h>
#include	"GUI/IWindow.hpp"
#include	"Ncurses/Pixel.hpp"

namespace ARCADE
{
  namespace Ncurses
  {
    class Window : public GUI::IWindow {
    private:
      WINDOW			*_window;
      bool			hasColor;

    public:
      explicit Window(const std::string windowName, int height, int width);
      ~Window();

    public:
      bool			drawPixel(const GUI::IPixel &pixel);
      bool			drawSquare(const GUI::IPosition &posBegin, const GUI::IPosition &posEnd, const GUI::Color &color);
      bool			drawText(const GUI::IText &text);
      GUI::Events::IEvent 	*getLastEvent();
      short			convertColor(const GUI::Color &) const;
      int			getTouch(const int &) const;
      bool			display();
      bool			Close();
    };

    extern "C" GUI::IWindow	&createWindow(const std::string windowName, int height, int width);
  }
}

#endif		/* !CPP_ARCADE_WINDOW_HPP_ */
