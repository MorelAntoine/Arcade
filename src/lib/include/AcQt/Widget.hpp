//
// Widget.hpp for cpp_arcade in /home/antoine/Documents/Projets/C++/cpp_arcade
//
// Made by Antoine MOREL
// Login   <antoine.morel@epitech.eu@epitech.net>
//
// Started on  Fri Apr 07 11:10:31 2017 Antoine MOREL
// Last update Sat Apr 08 14:45:51 2017 Antoine MOREL
//

#ifndef		CPP_ARCADE_WIDGET_HPP
#define		CPP_ARCADE_WIDGET_HPP

#include	<QtGui/QtGui>
#include	<vector>
#include	"AcQt/Pixel.hpp"
#include	"AcQt/Text.hpp"

namespace ARCADE
{
  namespace AcQt
  {
    class Widget : public QWidget {
    private:
      int					_keyPress;
    public:
      std::vector<ARCADE::AcQt::Pixel*>		_vPixel;
      std::vector<ARCADE::AcQt::Text*>		_vText;

    public:
      explicit Widget(int, int);
      ~Widget();

    public:
      int					getKeyPress() const;
      void					setKeyPress(int value);
      std::vector<ARCADE::AcQt::Pixel*>		getVPixel();
      std::vector<ARCADE::AcQt::Text*>		getVText();

    public:
      void					cleanContainers();
    private:
      Qt::GlobalColor				convertColor(const GUI::Color &) const;
    protected:
      void					paintEvent(QPaintEvent *);
      void					keyPressEvent(QKeyEvent *);
      void					keyReleaseEvent(QKeyEvent *);
    };
  }
}

#endif		/* !CPP_ARCADE_WIDGET_HPP_ */
