//
// Position.hpp for cpp_arcade in /home/antoine/Documents/Projets/C++/cpp_arcade
//
// Made by Antoine MOREL
// Login   <antoine.morel@epitech.eu@epitech.net>
//
// Started on  Sun Mar 19 12:03:14 2017 Antoine MOREL
// Last update Sat Apr 08 14:45:35 2017 Antoine MOREL
//

#ifndef		CPP_ARCADE_POSITION_HPP_
#define		CPP_ARCADE_POSITION_HPP_

#include	"GUI/IPosition.hpp"

namespace ARCADE
{
  namespace AcQt
  {
    class Position : public GUI::IPosition {
    private:
      unsigned int	_x;
      unsigned int	_y;

    public:
      Position(unsigned int y, unsigned int x);
      Position(const Position &src);
      ~Position();

    public:
      unsigned int	getX() const;
      unsigned int	getY() const;
      void		setX(unsigned int);
      void		setY(unsigned int);
    };

    extern "C" GUI::IPosition	&createPosition(unsigned int y, unsigned int x);
  }
}

#endif		/* !CPP_ARCADE_POSITION_HPP_ */
