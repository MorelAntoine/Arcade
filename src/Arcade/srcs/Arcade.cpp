//
// Arcade.cpp for cpp_arcade in /home/dylan/Documents/TEK2/cpp_arcade
//
// Made by Dylan Deu
// Login   <dylan.deu@epitech.net>
//
// Started on  Sat Mar 18 18:13:20 2017 Dylan Deu
// Last update Thu Mar 23 08:40:30 2017 Dylan Deu
//

#include		<dlfcn.h>
#include		<dirent.h>
#include		<iostream>
#include		<fstream>
#include		<unistd.h>
#include		<algorithm>
#include		"Arcade.hpp"
#include		"Exception.hpp"
#include		"IGame.hpp"
#include		"Protocol.hpp"

Arcade::Arcade::Arcade() : graphicalLib(NULL), gameLib(NULL), _name("")
{
}

Arcade::Arcade::~Arcade()
{
}

Arcade::Arcade::Arcade(const Arcade &other)
{
  this->graphicalLib = other.graphicalLib;
}

void			Arcade::Arcade::loadGraphicLibrary(const std::string &lib)
{
  if (lib.size() < 4)
    throw new Exception("Bad arguments\nUsage: ./arcade lib/lib_arcade_XXXXX.so");
  this->_graphicalLibName = lib.substr(4, lib.npos);
  this->graphicalLib = Arcade::openLib(lib);
  if (this->graphicalLib == NULL)
    throw new Exception("Error when opening the graphical library.");
  this->loadGraphicsFunction();
}

void			*Arcade::Arcade::openLib(const std::string &lib)
{
  void			*handler;

  handler = dlopen(lib.c_str(), RTLD_LAZY);
  return (handler);
}

void			Arcade::Arcade::loadGraphicsFunction()
{
  this->createPixel = (GUI::IPixel &(*)(const GUI::IPosition &, const GUI::Color &))dlsym(this->graphicalLib, "createPixel");
  if (this->createPixel == NULL)
    throw new Exception("Error while loading createPixel function.");
  this->createPosition = (GUI::IPosition & (*)(unsigned int, unsigned int))dlsym(this->graphicalLib, "createPosition");
  if (this->createPosition == NULL)
    throw new Exception("Error while loading createPosition function.");
  this->createText = (GUI::IText &(*)(const std::string &, const GUI::Color &, const GUI::Color &, const GUI::IPosition &))dlsym(this->graphicalLib, "createText");
  if (this->createText == NULL)
    throw new Exception("Error while loading createText function.");
  this->createWindow = (GUI::IWindow &(*)(const std::string, int, int))dlsym(this->graphicalLib, "createWindow");
  if (this->createWindow == NULL)
    throw new Exception("Error while loading createWindow function.");
}

void			Arcade::Arcade::loadGameFunction()
{
  this->createGame = (Game::IGame &(*)(void))dlsym(this->gameLib, "createGame");
  if (this->createGame == NULL)
    throw new Exception("Error while loading the createGameF function.");
}

void Arcade::Arcade::getLibsDir()
{
  Arcade::getDirContent("lib/", this->graphicsLib);
  Arcade::getDirContent("games/", this->gamesLib);
  if (this->graphicsLib.empty())
    throw new Exception("Error: No graphics library in the directory");
  if (this->gamesLib.empty())
    throw new Exception("Error: No games library in the directory");
}

void			Arcade::Arcade::getDirContent(const std::string &dirName, std::vector<std::string> &lib)
{
  struct dirent		*dir;
  DIR			*rep;
  std::string		libName;

  rep = opendir(dirName.c_str());
  if (rep == NULL)
    throw new Exception("Error: Fail to open the directory");
  while ((dir = readdir(rep)))
  {
    libName = dir->d_name;
    if (libName[0] != '.')
      lib.push_back(libName);
  }
  if (closedir(rep) == -1)
    throw new Exception("Error: Fail to close the directory");
}

void			Arcade::Arcade::loadGamesLibrary(const std::string &name)
{
  std::string		otherName;

  otherName = "games/";
  if (name.empty())
  {
    this->Menu();
    otherName += this->_gameLibName;
    this->gameLib = Arcade::openLib(otherName);
  }
  else
  {
    this->gameLib = Arcade::openLib(name);
    if (name.size() < 6)
      throw new Exception("Error: Can't open the game library");
    this->_gameLibName = name.substr(6, name.npos);
  }
  if (this->gameLib == NULL)
    throw new Exception("Error: Fail to open game library");
  this->loadGameFunction();
}

void			Arcade::Arcade::Menu()
{
  unsigned long			index(0);
  std::string			name("");
  std::string			tmpName;
  short int			loop(0);
  GUI::IWindow			&win = Arcade::createWindow("Menu", 100, 100);
  const GUI::Events::IEvent		*event;
  const GUI::Events::IKeyboardEvent	*eventKeyBoard;

  while (loop != 1)
  {
    this->fillMenu(index, win, 0);
    this->putInstructions(win);
    win.display();
    event = win.getLastEvent();
    eventKeyBoard = dynamic_cast<const GUI::Events::IKeyboardEvent *>(event);
    if (eventKeyBoard != NULL)
    {
      switch (eventKeyBoard->getContent())
      {
	case static_cast<int>(GUI::Events::IKeyboardEvent::KeyboardEvents::ENTER) : {
	  if (!this->_name.empty())
	    loop = 1;
	  else
	    this->blinkingName(index, win);
	  break;
	}
	case static_cast<int>(GUI::Events::IKeyboardEvent::KeyboardEvents::BOTTOM) : {
	  index = (index == this->gamesLib.size() - 1) ? 0 : index + 1;
	  break;
	}
	case static_cast<int>(GUI::Events::IKeyboardEvent::KeyboardEvents::TOP) : {
	  index = (index == 0) ? this->gamesLib.size() - 1 : index - 1;
	  break;
	}
	case static_cast<int>(GUI::Events::IKeyboardEvent::KeyboardEvents::BACKSPACE) : {
	  if (!this->_name.empty())
	  {
	    tmpName = this->_name.substr(0, this->_name.size() - 1);
	    this->_name = tmpName;
	  }
	}
	default:
	{
	  if (eventKeyBoard->getContent() >= 'a' &&
	      eventKeyBoard->getContent() <= 'z')
	  {
	    this->_name += eventKeyBoard->getContent();
	    if (this->_name.size() == 1)
	      this->_name[0] -= 32;
	  }
	  break;
	}
      }
      delete event;
    }
  }
  delete &win;
  this->_gameLibName = this->gamesLib[index];
}

void			Arcade::Arcade::putInstructions(GUI::IWindow &win)
{
  std::string		instructions;
  GUI::IPosition	&pos = this->createPosition(this->gamesLib.size() + 8, 0);

  instructions = "  '2' : Previous graphics library.\n";
  instructions += "  '3' : Next graphics library.\n";
  instructions += "  '4' : Previous game.\n";
  instructions += "  '5' : Next game.\n";
  instructions += "  '8' : Restart the game.\n";
  instructions += "  '9' : Go back to the menu.\n";
  instructions += "  'p' : Pause.\n";
  instructions += "  Escape : Exit.";
  GUI::IText		&txt = this->createText(instructions, GUI::Color::C_WHITE, GUI::Color::C_BLACK, pos);
  if (!win.drawText(txt))
    throw new Exception("Can't load the font");
}

void			Arcade::Arcade::fillMenu(unsigned long index, GUI::IWindow &win,
						     unsigned int blinkingName)
{
  unsigned long			pos(0);
  std::string			games;
  std::string			name;
  GUI::Color			color(GUI::Color::C_WHITE);
  GUI::Color			fontColor(GUI::Color::C_BLACK);
  GUI::IPosition		&posBegin = Arcade::createPosition(0, 0);
  GUI::IPosition		&posEnd = Arcade::createPosition(99, 99);
  GUI::IPosition		&posTxt = Arcade::createPosition(4, 1);
  GUI::IPosition		&posName = Arcade::createPosition(1, 1);

  name = "Enter your name : ";
  name += this->_name;
  if (blinkingName > 0 && blinkingName % 2 == 1)
  {
    color = GUI::Color::C_RED;
    fontColor = GUI::Color::C_RED;
  }
  GUI::IText			&txtName = Arcade::createText(name, color, fontColor, posName);
  win.drawSquare(posBegin, posEnd, GUI::Color::C_BLACK);
  delete &posBegin;
  delete &posEnd;

  if (!win.drawText(txtName))
    throw new Exception("Can't load the font");
  delete &txtName;
  delete &posName;
  games = "Choose the game :\n";
  while (pos < this->gamesLib.size())
  {
    if (pos == index)
      games += "-> ";
    else
      games += "   ";
    games += this->gamesLib[pos];
    games += "\n";
    pos++;
  }
  GUI::IText			&txt = Arcade::createText(games, GUI::Color::C_WHITE, GUI::Color::C_BLACK, posTxt);
  if (!win.drawText(txt))
    throw new Exception("Can't load the font");
  delete &txt;
  delete &posTxt;
}

void				Arcade::Arcade::blinkingName(unsigned long index, GUI::IWindow &win)
{
  unsigned int			loop(1);

  while (loop < 8)
  {
    this->fillMenu(index, win, loop);
    this->putInstructions(win);
    win.display();
    usleep(90000);
    loop++;
  }
}

bool			Arcade::Arcade::makeEvent(Game::IGame &game, const GUI::Events::IKeyboardEvent *eventKeyboard)
{
  switch (eventKeyboard->getContent())
  {
    case static_cast<int>(GUI::Events::IKeyboardEvent::KeyboardEvents::TOP) : {
      game.putAction(arcade::CommandType::GO_UP);
      break;
    }
    case static_cast<int>(GUI::Events::IKeyboardEvent::KeyboardEvents::BOTTOM) : {
      game.putAction(arcade::CommandType::GO_DOWN);
      break;
    }
    case static_cast<int>(GUI::Events::IKeyboardEvent::KeyboardEvents::LEFT) : {
      game.putAction(arcade::CommandType::GO_LEFT);
      break;
    }
    case static_cast<int>(GUI::Events::IKeyboardEvent::KeyboardEvents::RIGHT) : {
      game.putAction(arcade::CommandType::GO_RIGHT);
      break;
    }
    case static_cast<int>(GUI::Events::IKeyboardEvent::KeyboardEvents::SPACE) : {
      game.putAction(arcade::CommandType::SHOOT);
      break;
    }
    default: {
      return (false);
    }
  }
  return (true);
}

void			Arcade::Arcade::displayGame(Game::IGame &game, GUI::IWindow &win)
{
  std::string	scoreTxt("Your score: ");
  GUI::IPosition	&posScore = Arcade::createPosition(0, 0);
  GUI::IPosition	&posBeginMap = Arcade::createPosition(2, 0);
  GUI::IPosition	&posEndMap = Arcade::createPosition(game.getMap().height + 2, game.getMap().width);
  GUI::IPosition	&posBegin = Arcade::createPosition(0, 0);
  GUI::IPosition	&posEnd = Arcade::createPosition(2, game.getMap().width);
  GUI::Color 		color(GUI::Color::C_WHITE);
  unsigned int		x;
  unsigned int		y(0);

  scoreTxt += std::to_string(game.getScore());
  GUI::IText		&score = Arcade::createText(scoreTxt, GUI::Color::C_WHITE, GUI::Color::C_BLACK, posScore);

  win.drawSquare(posBegin, posEnd, GUI::Color::C_BLACK);
  delete &posBegin;
  delete &posEnd;

  if (!win.drawText(score))
    throw new Exception("Can't load the font");
  delete &score;
  delete &posScore;

  win.drawSquare(posBeginMap, posEndMap, GUI::Color::C_WHITE);
  delete &posBeginMap;
  delete &posEndMap;
  while (y < game.getMap().height)
  {
    x = 0;
    while (x < game.getMap().width)
    {
      if (game.getMap().tile[y * game.getMap().width + x] != arcade::TileType::EMPTY)
      {
	switch (game.getMap().tile[y * game.getMap().width + x])
	{
	  case arcade::TileType::EVIL_DUDE : {
	    color = GUI::Color::C_RED;
	    break;
	  }
	  case arcade::TileType::BLOCK : {
	    color = GUI::Color::C_GREEN;
	    break;
	  }
	  case arcade::TileType::OBSTACLE : {
	    color = GUI::Color::C_BLUE;
	    break;
	  }
	  case arcade::TileType::MY_SHOOT : {
	    color = GUI::Color::C_CYAN;
	    break;
	  }
	  case arcade::TileType::POWERUP : {
	    color = GUI::Color::C_MAGENTA;
	    break;
	  }
	  case arcade::TileType::OTHER : {
	    color = GUI::Color::C_YELLOW;
	    break;
	  }
	  default:
	    break;
	}

	GUI::IPosition	&pos = Arcade::createPosition(y + 2, x);
	GUI::IPixel		&pix = Arcade::createPixel(pos, color);
	win.drawPixel(pix);
	delete &pos;
	delete &pix;
      }
      x++;
    }
    y++;
  }

  x = 0;
  while (x < game.getWhereAmI().lenght)
  {
    GUI::IPosition	&pos = Arcade::createPosition(game.getWhereAmI().position[x].y + 2, game.getWhereAmI().position[x].x);
    GUI::IPixel		&pix = Arcade::createPixel(pos, GUI::Color::C_GREEN);
    win.drawPixel(pix);
    delete &pos;
    delete &pix;
    x++;
  }
  win.display();
}

void			Arcade::Arcade::switchGraphicLib(GUI::Events::IKeyboardEvent::KeyboardEvents type)
{
  int			index(0);
  std::string		lib("lib/");

  std::vector<std::string>::iterator pos;
  pos = std::find(this->graphicsLib.begin(), this->graphicsLib.end(), this->_graphicalLibName);
  if (type == GUI::Events::IKeyboardEvent::KeyboardEvents::NUM2)
  {
    index = std::distance(this->graphicsLib.begin(), pos);
    if (index - 1 < 0)
      index = this->graphicsLib.size() - 1;
    else
      index -= 1;
    lib += this->graphicsLib[index];
    this->_graphicalLibName = this->graphicsLib[index];
    if (!this->graphicalLib)
      dlclose(this->graphicalLib);
    this->loadGraphicLibrary(lib);
  }
  else
  {
    if (pos != this->graphicsLib.end())
      index = (std::distance(this->graphicsLib.begin(), pos) + 1) % this->graphicsLib.size();
    lib += this->graphicsLib[index];
    this->_graphicalLibName = this->graphicsLib[index];
    if (!this->graphicalLib)
      dlclose(this->graphicalLib);
    this->loadGraphicLibrary(lib);
  }
}

void			Arcade::Arcade::switchGameLib(GUI::Events::IKeyboardEvent::KeyboardEvents type)
{
  int			index(0);
  std::string		lib("games/");

  std::vector<std::string>::iterator pos;
  pos = std::find(this->gamesLib.begin(), this->gamesLib.end(), this->_gameLibName);
  if (type == GUI::Events::IKeyboardEvent::KeyboardEvents::NUM4)
  {
    index = std::distance(this->gamesLib.begin(), pos);
    if (index - 1 < 0)
      index = this->gamesLib.size() - 1;
    else
      index -= 1;
    lib += this->gamesLib[index];
    this->_gameLibName = this->gamesLib[index];
    if (!this->gameLib)
      dlclose(this->gameLib);
    this->loadGamesLibrary(lib);
  }
  else
  {
    if (pos != this->graphicsLib.end())
      index = (std::distance(this->gamesLib.begin(), pos) + 1) % this->gamesLib.size();
    lib += this->gamesLib[index];
    this->_gameLibName = this->gamesLib[index];
    if (!this->gameLib)
      dlclose(this->gameLib);
    this->loadGamesLibrary(lib);
  }
}

void			Arcade::Arcade::playGame()
{
  Game::IGame				*game = &this->createGame();
  GUI::IWindow				*win = &Arcade::createWindow(game->getName(), game->getMap().height + 2, game->getMap().width);
  const GUI::Events::IEvent		*event;
  const GUI::Events::IKeyboardEvent	*eventKeyboard;
  int					loop(0);
  bool					stop(false);

  while (loop != 1)
  {
    this->displayGame(*game, *win);
    event = win->getLastEvent();
    eventKeyboard = dynamic_cast<const GUI::Events::IKeyboardEvent *>(event);
    if (event != NULL)
    {
      switch (eventKeyboard->getContent())
      {
	case static_cast<int>(GUI::Events::IKeyboardEvent::KeyboardEvents::ESCAPE) : {
	  loop = 1;
	  break;
	}
	case static_cast<int>('p') : {
	  if (!stop)
	    stop = true;
	  else
	    stop = false;
	  break;
	}
	case static_cast<int>(GUI::Events::IKeyboardEvent::KeyboardEvents::NUM2) : {
	  this->delEvent(event);
	  this->delWin(win);
	  switchGraphicLib(GUI::Events::IKeyboardEvent::KeyboardEvents::NUM2);
	  win = &Arcade::createWindow(game->getName(), game->getMap().height + 2,
				      game->getMap().width);
	  break;
	}
	case static_cast<int>(GUI::Events::IKeyboardEvent::KeyboardEvents::NUM3) : {
	  this->delEvent(event);
	  this->delWin(win);
	  switchGraphicLib(GUI::Events::IKeyboardEvent::KeyboardEvents::NUM3);
	  win = &Arcade::createWindow(game->getName(), game->getMap().height + 2,
				      game->getMap().width);
	  break;
	}
	case static_cast<int>(GUI::Events::IKeyboardEvent::KeyboardEvents::NUM4) : {
	  this->delEvent(event);
	  this->delGame(game);
	  this->delWin(win);
	  switchGameLib(GUI::Events::IKeyboardEvent::KeyboardEvents::NUM4);
	  game = &this->createGame();
	  win = &Arcade::createWindow(game->getName(), game->getMap().height + 2,
				      game->getMap().width);
	  break;
	}
	case static_cast<int>(GUI::Events::IKeyboardEvent::KeyboardEvents::NUM5) : {
	  this->delEvent(event);
	  this->delGame(game);
	  this->delWin(win);
	  switchGameLib(GUI::Events::IKeyboardEvent::KeyboardEvents::NUM5);
	  game = &this->createGame();
	  win = &Arcade::createWindow(game->getName(), game->getMap().height + 2,
				      game->getMap().width);
	  break;
	}
	case static_cast<int>(GUI::Events::IKeyboardEvent::KeyboardEvents::NUM9) : {
	  this->delEvent(event);
	  this->delGame(game);
	  this->delWin(win);
	  this->Menu();
	  this->playGame();
	  return;
	}
	case static_cast<int>(GUI::Events::IKeyboardEvent::KeyboardEvents::NUM8) : {
	  this->delEvent(event);
	  this->delGame(game);
	  game = &Arcade::createGame();
	  break;
	}
	default: {
	  if (!stop)
	    makeEvent(*game, eventKeyboard);
	  break;
	}
      }
    }
    else if (!stop)
      if (!game->putAction(arcade::CommandType::PLAY))
	loop = 1;
    this->delEvent(event);
  }
  this->delEvent(event);
  delete win;
  saveScore(game->getName(), this->_name, std::to_string(game->getScore()));
  gameOver(*game);
  delete game;
}

void			Arcade::Arcade::displayFinalScore(GUI::IWindow &win, Game::IGame &game, std::vector<std::pair<std::string, unsigned long int>> &listBestScores)
{
  GUI::IPosition	&posBegin = Arcade::createPosition(0, 0);
  GUI::IPosition	&posEnd = Arcade::createPosition(30, 40);
  GUI::IPosition	&pos = Arcade::createPosition(2, 14);
  GUI::IPosition	&posBestScore = Arcade::createPosition(6, 14);
  std::string		gameOver;
  std::string		bestScore;
  unsigned int		index(0);

  win.drawSquare(posBegin, posEnd, GUI::Color::C_BLACK);
  delete &posBegin;
  delete &posEnd;

  gameOver = "Game Over !!!";
  GUI::IText		&txt = Arcade::createText(gameOver, GUI::Color::C_WHITE, GUI::Color::C_BLACK, pos);
  if (!win.drawText(txt))
    throw new Exception("Can't load the font");
  delete &pos;
  delete &txt;


  gameOver.clear();
  gameOver = "Your score: ";
  gameOver += std::to_string(game.getScore());
  GUI::IPosition	&pos2 = Arcade::createPosition(3, 14);
  GUI::IText		&txt2 = Arcade::createText(gameOver, GUI::Color::C_WHITE, GUI::Color::C_BLACK, pos2);
  if (!win.drawText(txt2))
    throw new Exception("Can't load the font");
  delete &pos2;
  delete &txt2;

  bestScore = "Best scores for the ";
  bestScore += game.getName();
  GUI::IText		&bestScoreTxt = Arcade::createText(bestScore, GUI::Color::C_WHITE, GUI::Color::C_BLACK, posBestScore);
  if (!win.drawText(bestScoreTxt))
    throw new Exception("Can't load the font");

  delete &posBestScore;
  delete &bestScoreTxt;

  while (index < listBestScores.size() && index < 5)
  {
    bestScore.clear();
    bestScore = listBestScores[index].first;
    bestScore += " : ";
    bestScore += std::to_string(listBestScores[index].second);

    GUI::IPosition	&posBestScore = Arcade::createPosition(8 + index, 14);
    GUI::IText		&bestScoreTxt = Arcade::createText(bestScore, GUI::Color::C_WHITE, GUI::Color::C_BLACK, posBestScore);
    if (!win.drawText(bestScoreTxt))
      throw new Exception("Can't load the font");
    delete &posBestScore;
    delete &bestScoreTxt;
    index++;
  }


  GUI::IPosition	&posInstruction = Arcade::createPosition(14, 4);
  std::string		instruction;

  instruction = "'m': Go back to the Menu\tEscape: Quit the game";
  GUI::IText		&objInstruction = Arcade::createText(instruction, GUI::Color::C_WHITE, GUI::Color::C_BLACK, posInstruction);
  if (!win.drawText(objInstruction))
    throw new Exception("Can't load the font");
  delete &posInstruction;
  delete &objInstruction;
}

void			Arcade::Arcade::gameOver(Game::IGame &game)
{
  const GUI::Events::IEvent		*event;
  const GUI::Events::IKeyboardEvent	*eventKeyboard;
  GUI::IWindow				&win = Arcade::createWindow("Game Over", 30, 40);
  std::vector<std::pair<std::string, unsigned long int>>	bestScores;
  int					loop(0);

  this->getBestScore(bestScores, game.getName());
  while (loop != 1)
  {
    displayFinalScore(win, game, bestScores);
    win.display();
    event = win.getLastEvent();
    eventKeyboard = dynamic_cast<const GUI::Events::IKeyboardEvent *>(event);
    if (event != NULL)
    {
      if (eventKeyboard->getContent() ==
	  static_cast<int>(GUI::Events::IKeyboardEvent::KeyboardEvents::ESCAPE))
	loop = 1;
      else if (eventKeyboard->getContent() == 'm')
      {
	delete &win;
	this->loadGamesLibrary("");
	this->playGame();
	return;
      }
    }
    if (!event)
      delete event;
    if (eventKeyboard != NULL)
      delete eventKeyboard;
  }
  delete &win;
}

void			Arcade::Arcade::saveScore(const std::string &game,
						      const std::string &name,
						      const std::string &score)
{
  std::ofstream		file(game, std::ofstream::app);

  if (file)
  {
    if (!name.empty())
      file << name << " " << score << std::endl;
    else
      file << "UnknowPlayer " << score << std::endl;
  }
  else
    throw new Exception("Error when opening the score file\n");
}

void			Arcade::Arcade::closeLib()
{
  if (!this->graphicalLib)
    dlclose(this->graphicalLib);
  if (!this->gameLib)
    dlclose(this->gameLib);
}

void			Arcade::Arcade::getBestScore(std::vector<std::pair<std::string, unsigned long int>> &list, const std::string &fileName)
{
  unsigned int		index(0);
  std::ifstream		file(fileName);
  std::string		line;
  std::pair<std::string, unsigned long int>	elem;

  if (file)
  {
    while (file >> elem.first >> elem.second)
      list.push_back(elem);
  }
  while (index + 1< list.size())
  {
    if (list[index].second < list[index + 1].second)
    {
      elem = list[index];
      list[index] = list[index + 1];
      list[index + 1] = elem;
      index = 0;
    }
    else
      index++;
  }
}

void			Arcade::Arcade::delEvent(const GUI::Events::IEvent *&event)
{
  if (event)
  {
    delete event;
    event = NULL;
  }
}

void			Arcade::Arcade::delGame(Game::IGame *&game)
{
  if (game)
  {
    delete game;
    game = NULL;
  }
}

void			Arcade::Arcade::delWin(GUI::IWindow *&win)
{
  if (win)
  {
    delete win;
    win = NULL;
  }
}
