//
// Centipede.hpp for centipefde in /home/dylan/Documents/TEK2/cpp_arcade/src/Games/Centipede
// 
// Made by Dylan Deu
// Login   <dylan.deu@epitech.eu>
// 
// Started on  Fri Mar 31 14:41:49 2017 Dylan Deu
// Last update Fri Mar 31 14:41:53 2017 Dylan Deu
//

#ifndef			CENTIPEDE_HPP_
# define		CENTIPEDE_HPP_

#include 		<chrono>
#include		<vector>
#include		"IGame.hpp"
#include		"Obstacle.hpp"

namespace		Game
{
  class			Centipede : public Game::IGame
  {
  public:
    Centipede();
    virtual ~Centipede();

  private:
    bool				_generate;
    bool				_deactivateTimer;
    arcade::GetMap			*_map;
    arcade::WhereAmI			*_pos;
    int					_nbCentipede;
    unsigned long int			_score;
    unsigned long int			_evilDudeSize;
    std::chrono::milliseconds		_time;
    std::vector<arcade::Position>	_shootPos;
    std::vector<arcade::Position>	_evilDudePos;
    std::vector<Game::Obstacle *>	*_obstacles;
    int					_refresh;

  public:
    bool		putAction(const arcade::CommandType action);
    void		deactivateTimer(void);
    arcade::GetMap	&getMap() const;
    arcade::WhereAmI	&getWhereAmI() const;
    unsigned long int	getScore() const;
    std::string		getName() const;

  public:
    static bool		readGame(int fd, char *buff, unsigned int size);

  private:
    void		moveDude();
    void		putDudeOnMap();
    void		regenerateEvilDude();
    void		regenerateObstacle();
    bool		generateObstacle();
    void		movePlayer(const arcade::CommandType action);
    void		moveMyShoot();
    void		checkKill();
    void		destroyBlock(unsigned int x, unsigned int y);
    void		destroySnake(unsigned int x, unsigned int y);
    void		updateTime();
    bool		amIDead();
    void		speed();

  };
};

#endif			/*! CENTIPEDE_HPP_ */
