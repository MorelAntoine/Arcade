#ifndef CPP_ARCADE_SNAKE_HPP
#define CPP_ARCADE_SNAKE_HPP

#include 	<chrono>
#include	"IGame.hpp"

namespace	Game
{
  class Snake : public Game::IGame
  {
  public:
    Snake();
    virtual ~Snake();

  protected:
    arcade::GetMap	*_map;
    arcade::WhereAmI	*_pos;
    unsigned long int	_score;
    arcade::CommandType	_previous;
    uint16_t		_map_size;
    std::chrono::milliseconds	_time;
    bool		_deactivateTimer;
    char		_gameOver;
    int			_refresh;

  public:
    bool		putAction(const arcade::CommandType);
    arcade::GetMap	&getMap() const;
    arcade::WhereAmI	&getWhereAmI() const;
    unsigned long int	getScore() const;
    std::string		getName() const;
    void		deactivateTimer();

  public:
    static bool		readGame(int fd, char *buff, unsigned int size);

  protected:
    bool		moveSnake();
    bool		checkSnakePos();
    bool		checkDude();
    void		moveDirection(const arcade::CommandType);
    void		generateDude();
    void		expandSnake();
    void		updateTime();
    void		speed();
    bool		checkDudeUnderSnake(int, int);

  };
};

#endif /* !CPP_ARCADE_SNAKE_HPP_ */
