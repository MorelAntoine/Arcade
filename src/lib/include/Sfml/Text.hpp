//
// Text.hpp for cpp_arcade in /home/antoine/Documents/Projets/C++/cpp_arcade
//
// Made by Antoine MOREL
// Login   <antoine.morel@epitech.eu@epitech.net>
//
// Started on  Sun Mar 19 12:02:54 2017 Antoine MOREL
// Last update Sun Mar 19 12:02:54 2017 Antoine MOREL
//

#ifndef		CPP_ARCADE_TEXT_HPP_
#define		CPP_ARCADE_TEXT_HPP_

#include	<string>
#include	"GUI/IText.hpp"
#include	"Position.hpp"

namespace ARCADE
{
  namespace Sfml
  {
    class Text : public GUI::IText {
    private:
      ARCADE::Sfml::Position	position;
      GUI::Color 		colorText;
      GUI::Color 		colorFond;
      std::string		text;

    public:
      Text(const std::string &str, const GUI::Color &colorText, const GUI::Color &fond, const GUI::IPosition &pos);
      ~Text();

    public:
      const GUI::IPosition	&getPosition() const;
      const GUI::Color		&getColorFore() const;
      const GUI::Color		&getColorBack() const;
      const std::string		&getText() const;
    };

    extern "C" GUI::IText	&createText(const std::string &str, const GUI::Color &colorText, const GUI::Color &fond, const GUI::IPosition &pos);
  }
}

#endif		/* !CPP_ARCADE_TEXT_HPP_ */
