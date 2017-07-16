//
// Exception.cpp for cpp_arcade in /home/dylan/Documents/TEK2/cpp_arcade
//
// Made by Dylan Deu
// Login   <dylan.deu@epitech.net>
//
// Started on  Sat Mar 18 18:18:23 2017 Dylan Deu
// Last update Tue Mar 21 10:25:31 2017 Dylan Deu
//

#include		"Exception.hpp"

Arcade::Exception::Exception(const std::string &error) : std::runtime_error(error)
{

}
