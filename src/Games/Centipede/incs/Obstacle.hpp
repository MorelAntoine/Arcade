//
// Obstacle.hpp for cpp_arcade in /home/dylan/Documents/TEK2/cpp_arcade
//
// Made by Dylan Deu
// Login   <dylan.deu@epitech.net>
//
// Started on  Tue Apr 04 16:49:37 2017 Dylan Deu
// Last update Tue Apr 04 16:49:37 2017 Dylan Deu
//

#ifndef			CPP_ARCADE_OBSTACLE_HPP
# define		CPP_ARCADE_OBSTACLE_HPP

#include		"Protocol.hpp"

namespace		Game
{
  class			Obstacle
  {
  public:
    Obstacle();
    virtual ~Obstacle() {}

  private:
    unsigned int	_live;
    arcade::Position	_pos;

  public:
    void		setLive(unsigned int);
    unsigned int	getLive(void);
    void		setPos(unsigned int x, unsigned int y);
    arcade::Position	getPos(void);
  };
};

#endif /* !CPP_ARCADE_OBSTACLE_HPP_ */
