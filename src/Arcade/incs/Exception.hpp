#ifndef		ARCADE_EXCEPTION_HPP_
# define	ARCADE_EXCEPTION_HPP_

# include	<stdexcept>
# include	<string>

namespace	Arcade
{
  class		Exception : public std::runtime_error
  {
  public:
    Exception(const std::string &);
    virtual ~Exception() {}

  };
};

#endif
