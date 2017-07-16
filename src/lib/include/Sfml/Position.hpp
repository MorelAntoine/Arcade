//
// Position.hpp for cpp_arcade in /home/antoine/Documents/Projets/C++/cpp_arcade
//
// Made by Antoine MOREL
// Login   <antoine.morel@epitech.eu@epitech.net>
//
// Started on  Sun Mar 19 12:03:14 2017 Antoine MOREL
// Last update Mon Mar 20 21:45:42 2017 Dylan Deu
//

#ifndef		CPP_ARCADE_POSITION_HPP_
#define		CPP_ARCADE_POSITION_HPP_

#include	"GUI/IPosition.hpp"

namespace ARCADE
{
  namespace Sfml
  {
    class Position : public GUI::IPosition {
    private:
      unsigned int		_x;
      unsigned int		_y;

    public:
      Position(unsigned int x, unsigned int y);
      Position(const Position &src);
      ~Position();

    public:
      unsigned int		getX() const;
      unsigned int		getY() const;
    };

    extern "C" GUI::IPosition	&createPosition(unsigned int y, unsigned int x);
  }
}

#endif		/* !CPP_ARCADE_POSITION_HPP_ */
