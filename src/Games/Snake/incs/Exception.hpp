#ifndef CPP_ARCADE_EXCEPTION_HPP
#define CPP_ARCADE_EXCEPTION_HPP

# include       <stdexcept>
# include       <string>

namespace       Games
{
  class         Exception : public std::runtime_error
  {
  public:
    Exception(const std::string &error);

  };
};


#endif /* !CPP_ARCADE_EXCEPTION_HPP_ */
