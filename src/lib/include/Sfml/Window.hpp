//
// Window.hpp for cpp_arcade in /home/antoine/Documents/Projets/C++/cpp_arcade
//
// Made by Antoine MOREL
// Login   <antoine.morel@epitech.eu@epitech.net>
//
// Started on  Sun Mar 19 12:02:25 2017 Antoine MOREL
// Last update Sun Mar 19 19:26:32 2017 Dylan Deu
//

#ifndef		CPP_ARCADE_WINDOW_HPP_
#define		CPP_ARCADE_WINDOW_HPP_

#include	<SFML/Graphics.hpp>
#include	<SFML/Window.hpp>
#include	"GUI/IWindow.hpp"
#include	"Sfml/Pixel.hpp"

namespace ARCADE
{
  namespace Sfml
  {
    class Window : public GUI::IWindow {
    private:
      sf::RenderWindow		_window;

    public:
      explicit Window(const std::string windowName, int height, int width);
      ~Window();

    public:
      bool			drawPixel(const GUI::IPixel &pixel);
      bool			drawSquare(const GUI::IPosition &posBegin, const GUI::IPosition &posEnd, const GUI::Color &color);
      bool			drawText(const GUI::IText &text);
      GUI::Events::IEvent 	*getLastEvent();
      sf::Color			convertColor(const GUI::Color &) const;
      int			getTouch(const sf::Keyboard::Key &) const;
      bool			display();
      bool			Close();
    };

    extern "C" GUI::IWindow	&createWindow(const std::string windowName, int height, int width);
  }
}

#endif		/* !CPP_ARCADE_WINDOW_HPP_ */
