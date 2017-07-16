#ifndef		GUI_IPOSITION_HPP_
# define	GUI_IPOSITION_HPP_

# include	<string>

namespace		GUI
{
  class			IPosition
  {
  public:
    virtual ~IPosition() {}

    virtual unsigned int	getX() const = 0;
    virtual unsigned int	getY() const = 0;
  };
};

extern "C" GUI::IPosition	&createPosition(unsigned int y, unsigned int x);

#endif
