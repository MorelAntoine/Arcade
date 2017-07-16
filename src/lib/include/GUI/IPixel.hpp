#ifndef		GUI_IPIXEL_HPP_
# define	GUI_IPIXEL_HPP_

# include	<string>
# include	"GUI/IPosition.hpp"
# include	"GUI/Color.hpp"

namespace		GUI
{
  class			IPixel
  {
  public:
    virtual ~IPixel() {}

    virtual const IPosition	&getPosition() const = 0;
    virtual const Color		&getColor() const = 0;
  };
};

extern "C" GUI::IPixel	&createPixel(const GUI::IPosition &, const GUI::Color &);

#endif
