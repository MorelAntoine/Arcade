//
// Pixel.hpp for cpp_arcade in /home/antoine/Documents/Projets/C++/cpp_arcade
//
// Made by Antoine MOREL
// Login   <antoine.morel@epitech.eu@epitech.net>
//
// Started on  Sun Mar 19 12:03:28 2017 Antoine MOREL
// Last update Sat Apr 08 14:45:24 2017 Antoine MOREL
//

#ifndef		CPP_ARCADE_PIXEL_HPP
#define		CPP_ARCADE_PIXEL_HPP

#include	"GUI/IPixel.hpp"
#include	"AcQt/Position.hpp"

namespace ARCADE
{
  namespace AcQt
  {
    class Pixel : public GUI::IPixel {
    private:
      ARCADE::AcQt::Position	_position;
      GUI::Color		_color;

    public:
      explicit Pixel(const ARCADE::AcQt::Position &pos, const GUI::Color &color);
      ~Pixel();

    public:
      const GUI::IPosition	&getPosition() const;
      const GUI::Color		&getColor() const;
      void			setPosition(const Position &);
    };

    extern "C" GUI::IPixel	&createPixel(const GUI::IPosition &, const GUI::Color &);
  }
}

#endif		/* !CPP_ARCADE_PIXEL_HPP_ */
