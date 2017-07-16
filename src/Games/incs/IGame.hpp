#ifndef		GAME_IGAME_HPP_
# define	GAME_IGAME_HPP_

# include	<string>
# include	"Protocol.hpp"

namespace	Game
{
  class		IGame
  {
  public:
    virtual	~IGame() {};

    virtual bool		putAction(const arcade::CommandType action) = 0;
    virtual arcade::GetMap	&getMap() const = 0;
    virtual arcade::WhereAmI	&getWhereAmI() const = 0;
    virtual unsigned long int	getScore() const = 0;
    virtual std::string		getName() const = 0;
    virtual void		deactivateTimer(void) = 0;
  };
};

extern "C" Game::IGame		&createGame();
extern "C" void			Play();

#endif
