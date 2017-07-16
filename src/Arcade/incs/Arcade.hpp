//
// Arcade.hpp for cpp_arcade in /home/dylan/Documents/TEK2/cpp_arcade
//
// Made by Dylan Deu
// Login   <dylan.deu@epitech.net>
//
// Started on  Sun Mar 19 18:11:18 2017 Dylan Deu
// Last update Sun Mar 19 18:11:18 2017 Dylan Deu
//

#ifndef		ARCADE_ARCADE_HPP_
# define	ARCADE_ARCADE_HPP_

# include	<vector>
# include	<string>
# include	"GUI/GUI.hpp"


namespace	Arcade
{
  class		Arcade
  {
  protected:
    void			*graphicalLib;
    void			*gameLib;
    std::string			_graphicalLibName;
    std::string			_gameLibName;
    std::string			_name;
    std::vector<std::string>	gamesLib;
    std::vector<std::string>	graphicsLib;

  public:
    GUI::IPixel		&(*createPixel)(const GUI::IPosition &, const GUI::Color &);
    GUI::IPosition	&(*createPosition)(unsigned int, unsigned int);
    GUI::IText		&(*createText)(const std::string &, const GUI::Color &, const GUI::Color &, const GUI::IPosition &);
    GUI::IWindow	&(*createWindow)(const std::string, int, int);
    Game::IGame		&(*createGame)(void);

  public:
    Arcade();
    virtual ~Arcade();
    Arcade(const Arcade &);

  public:
    void	loadGraphicLibrary(const std::string &);
    void	loadGamesLibrary(const std::string &);
    void	getLibsDir();
    void	playGame();
    void	fillMenu(unsigned long index, GUI::IWindow &, unsigned int);
    bool	makeEvent(Game::IGame &, const GUI::Events::IKeyboardEvent *);
    void	displayGame(Game::IGame &, GUI::IWindow &);
    void	gameOver(Game::IGame &);
    void	displayFinalScore(GUI::IWindow &, Game::IGame &, std::vector<std::pair<std::string, unsigned long int>> &);
    void	saveScore(const std::string &, const std::string &, const std::string &);
    void	switchGraphicLib(GUI::Events::IKeyboardEvent::KeyboardEvents);
    void	switchGameLib(GUI::Events::IKeyboardEvent::KeyboardEvents);
    void	closeLib();
    void	Menu();

  private:
    void	*openLib(const std::string &);
    void	loadGraphicsFunction();
    void	loadGameFunction();
    void	getDirContent(const std::string &, std::vector<std::string> &);
    void	delEvent(const GUI::Events::IEvent *&);
    void	delGame(Game::IGame *&);
    void	delWin(GUI::IWindow *&);
    void	getBestScore(std::vector<std::pair<std::string, unsigned long int>> &, const std::string &);
    void	blinkingName(unsigned long index, GUI::IWindow &);
    void	putInstructions(GUI::IWindow &);
  };
};

#endif
