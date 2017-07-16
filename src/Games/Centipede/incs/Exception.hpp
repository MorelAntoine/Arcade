#ifndef CPP_ARCADE_EXCEPTION_HPP
#define CPP_ARCADE_EXCEPTION_HPP

#include	<stdexcept>

namespace	Arcade
{
  class		Exception : public std::runtime_error
  {
  public:
    Exception(const std::string &);
    virtual ~Exception() {}

  };
};

#endif /* !CPP_ARCADE_EXCEPTION_HPP_ */
