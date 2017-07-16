//
// play.cpp for cpp_arcade in /home/dylan/Documents/TEK2/cpp_arcade
//
// Made by Dylan Deu
// Login   <dylan.deu@epitech.net>
//
// Started on  Wed Apr 05 18:37:10 2017 Dylan Deu
// Last update Wed Apr  5 20:50:12 2017 Dylan Deu
//

#include		<iostream>
#include		<fstream>
#include		<unistd.h>
#include		"Centipede.hpp"

void			Play(void)
{
  Game::IGame		&game = *(new::Game::Centipede());
  arcade::CommandType	cmd;
  char			str[3];

  game.deactivateTimer();
  while (Game::Centipede::readGame(0, str, 2))
  {
    cmd = static_cast<arcade::CommandType>(static_cast<short int>(str[0]));
    switch (cmd) {
      case arcade::CommandType::GET_MAP : {
	  write(1, &game.getMap(), sizeof(arcade::GetMap));
	  write(1, &game.getMap().tile, sizeof(arcade::TileType) * game.getMap().height * game.getMap().width);
	break;
      }
      case arcade::CommandType::WHERE_AM_I : {
	write(1, &game.getWhereAmI(), sizeof(arcade::WhereAmI));
	write(1, &game.getWhereAmI().position, sizeof(arcade::Position) * game.getWhereAmI().lenght);
	break;
      }
      default : {
	  game.putAction(cmd);
	break;
      }
    }
  }
}
