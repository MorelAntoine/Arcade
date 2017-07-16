//
// Exception.cpp for cpp_arcade in /home/dylan/Documents/TEK2/cpp_arcade
//
// Made by Dylan Deu
// Login   <dylan.deu@epitech.net>
//
// Started on  Thu Mar 23 13:26:48 2017 Dylan Deu
// Last update Thu Mar 23 13:26:48 2017 Dylan Deu
//

#include		"Exception.hpp"

Arcade::Exception::Exception(const std::string &error) : std::runtime_error(error)
{
}
