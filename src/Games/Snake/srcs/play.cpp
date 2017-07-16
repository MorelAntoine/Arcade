//
// play.cpp for cpp_arcade in /home/dylan/Documents/TEK2/cpp_arcade
//
// Made by Dylan Deu
// Login   <dylan.deu@epitech.net>
//
// Started on  Wed Apr 05 18:37:10 2017 Dylan Deu
// Last update Wed Apr 05 18:37:10 2017 Dylan Deu
//

#include		<iostream>
#include		<unistd.h>
#include		"Snake.hpp"

void			Play(void)
{
  Game::IGame		&game = *(new::Game::Snake());
  char			str[3];
  arcade::CommandType	cmd;
  bool			play(true);

  game.deactivateTimer();
  while (Game::Snake::readGame(0, str, 2))
  {
    cmd = static_cast<arcade::CommandType>(static_cast<short int>(str[0]));
    if (cmd == arcade::CommandType::GET_MAP)
    {
	write(1, &game.getMap(), sizeof(arcade::GetMap));
	write(1, &game.getMap().tile, sizeof(arcade::TileType) * game.getMap().height * game.getMap().width);
    }
    else if (cmd == arcade::CommandType::WHERE_AM_I)
    {
	write(1, &game.getWhereAmI(), sizeof(arcade::WhereAmI));
	write(1, &game.getWhereAmI().position, sizeof(arcade::Position) * game.getWhereAmI().lenght);
    }
    else if (play)
    {
      game.putAction(cmd);
      if (cmd == arcade::CommandType::GO_LEFT || cmd == arcade::CommandType::GO_RIGHT ||
	cmd == arcade::CommandType::GO_DOWN || cmd == arcade::CommandType::GO_UP)
	play = false;
    }
    else if (!play)
      play = true;
  }
}
