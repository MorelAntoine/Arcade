//
// Window.hpp for cpp_arcade in /home/antoine/Documents/Projets/C++/cpp_arcade
//
// Made by Antoine MOREL
// Login   <antoine.morel@epitech.eu@epitech.net>
//
// Started on  Sun Mar 19 12:02:25 2017 Antoine MOREL
// Last update Fri Apr 07 10:10:10 2017 Antoine MOREL
//

#ifndef		CPP_ARCADE_WINDOW_HPP_
#define		CPP_ARCADE_WINDOW_HPP_

#include	<QtGui/QtGui>
#include	<QtGui/QApplication>
#include	<QtGui/QWidget>
#include	"GUI/IWindow.hpp"
#include	"AcQt/Pixel.hpp"
#include	"AcQt/Widget.hpp"

namespace ARCADE
{
  namespace AcQt
  {
    class Window : public GUI::IWindow {
    private:
      QApplication		*_app;
      Widget			*_window;
      char			*_windowName;

    public:
      explicit Window(const std::string windowName, int height, int width);
      ~Window();

    public:
      bool			drawPixel(const GUI::IPixel &pixel);
      bool			drawSquare(const GUI::IPosition &posBegin, const GUI::IPosition &posEnd, const GUI::Color &color);
      bool			drawText(const GUI::IText &text);
      GUI::Events::IEvent 	*getLastEvent();
      int			getTouch() const;
      bool			display();
      bool			Close();
    };

    extern "C" GUI::IWindow	&createWindow(const std::string windowName, int height, int width);
  }
}

#endif		/* !CPP_ARCADE_WINDOW_HPP_ */
