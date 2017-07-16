#ifndef		GUI_ITEXT_HPP_
# define	GUI_ITEXT_HPP_

# include	<string>
# include	"GUI/IPosition.hpp"
# include	"GUI/Color.hpp"

namespace		GUI
{
  class			IText
  {
  public:
    virtual ~IText() {}

    virtual const IPosition	&getPosition() const = 0;
    virtual const Color		&getColorFore() const = 0;
    virtual const Color		&getColorBack() const = 0;
    virtual const std::string	&getText() const = 0;
  };
};

extern "C"  GUI::IText		&createText(const std::string &, const GUI::Color &, const GUI::Color &, const GUI::IPosition &);


#endif
