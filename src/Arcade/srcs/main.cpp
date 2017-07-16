//
// main.cpp for cpp_arcade in /home/dylan/Documents/TEK2/cpp_arcade
//
// Made by Dylan Deu
// Login   <dylan.deu@epitech.net>
//
// Started on  Sat Mar 18 18:14:06 2017 Dylan Deu
// Last update Wed Mar 22 21:20:44 2017 Dylan Deu
//


#include	<iostream>
#include	"Arcade.hpp"
#include	"Exception.hpp"

int		main(int ac, char **av)
{
  if (ac != 2)
  {
    std::cerr << "Not enough arguments !" << std::endl;
    return (1);
  }

  Arcade::Arcade	*arcade = new Arcade::Arcade();
  try
  {
    arcade->loadGraphicLibrary(av[1]);
    arcade->getLibsDir();
    arcade->loadGamesLibrary("");
    arcade->playGame();
  }
  catch (const Arcade::Exception *error)
  {
    std::cerr << error->what() << std::endl;
    return (1);
  }
  arcade->closeLib();
  delete arcade;
  return (0);
}
