//
// Window.cpp for cpp_arcade in /home/antoine/Documents/Projets/C++/cpp_arcade
//
// Made by Antoine MOREL
// Login   <antoine.morel@epitech.eu@epitech.net>
//
// Started on  Sun Mar 19 16:02:43 2017 Antoine MOREL
// Last update Sat Apr 08 14:54:11 2017 Antoine MOREL
//

#include	"Ncurses/Window.hpp"
#include	"Ncurses/KeyboardEvent.hpp"

/*
** Elementary
*/

ARCADE::Ncurses::Window::Window(const std::string windowName, int height,
			     int width)
{
  static_cast<void>(windowName);
  initscr();
  cbreak();
  noecho();
  curs_set(0);
  start_color();
  this->_window = newwin(height, width, 0, 0);
  keypad(this->_window, TRUE);
  nodelay(this->_window, TRUE);
  if (has_colors() == FALSE)
    this->hasColor = false;
  else
    this->hasColor = true;
}

ARCADE::Ncurses::Window::~Window() {
  this->Close();
}

/*
** Draw
*/

bool		ARCADE::Ncurses::Window::drawPixel(const GUI::IPixel &pixel)
{
  short		color(this->convertColor(pixel.getColor()));
  ARCADE::Ncurses::Position	pos(pixel.getPosition().getY(), pixel.getPosition().getX());

  if (this->hasColor) {
    init_pair(color, COLOR_BLACK, color);
    wattron(this->_window, COLOR_PAIR(color));
    mvwprintw(this->_window, pos.getY(), pos.getX(), " ");
    wattroff(this->_window, COLOR_PAIR(color));
  } else {
    mvwprintw(this->_window, pos.getY(), pos.getX(), " ");
  }
  return (true);
}

bool		ARCADE::Ncurses::Window::drawSquare(const GUI::IPosition &posBegin,
							const GUI::IPosition &posEnd,
							const GUI::Color &color)
{
  ARCADE::Ncurses::Position	pos(posBegin.getY(), posBegin.getX());
  unsigned int			idx_x;
  unsigned int			idx_y;
  short				pix_color(this->convertColor(color));

  if (this->hasColor) {
    init_pair(pix_color, COLOR_BLACK, pix_color);
    wattron(this->_window, COLOR_PAIR(pix_color));
  }
  idx_y = pos.getY();
  while (idx_y < posEnd.getY()) {
    idx_x = pos.getX();
    while (idx_x < posEnd.getX()) {
      mvwprintw(this->_window, idx_y, idx_x, " ");
      idx_x++;
    }
    idx_y++;
  }
  if (this->hasColor)
    wattroff(this->_window, COLOR_PAIR(pix_color));
  return (true);
}

short		ARCADE::Ncurses::Window::convertColor(const GUI::Color &color) const
{
  switch (color)
  {

    case GUI::Color::C_BLACK:
      return (COLOR_BLACK);
    case GUI::Color::C_BLUE:
      return (COLOR_BLUE);
    case GUI::Color::C_CYAN:
      return (COLOR_CYAN);
    case GUI::Color::C_GREEN:
      return (COLOR_GREEN);
    case GUI::Color::C_MAGENTA:
      return (COLOR_MAGENTA);
    case GUI::Color::C_RED:
      return (COLOR_RED);
    case GUI::Color::C_YELLOW:
      return (COLOR_YELLOW);
    default:
      return (COLOR_WHITE);
  }
}

bool		ARCADE::Ncurses::Window::drawText(const GUI::IText &text)
{
  short		colorFore(this->convertColor(text.getColorFore()));
  short		colorBack(this->convertColor(text.getColorBack()));

  if (this->hasColor) {
    init_pair(colorBack, colorFore, colorBack);
    wattron(this->_window, COLOR_PAIR(colorBack));
    mvwprintw(this->_window, text.getPosition().getY(), text.getPosition().getX(), "%s", text.getText().c_str());
    wattroff(this->_window, COLOR_PAIR(colorBack));
  } else
    mvwprintw(this->_window, text.getPosition().getY(), text.getPosition().getX(), "%s", text.getText().c_str());
  return (true);
}

/*
** Event
*/

int		ARCADE::Ncurses::Window::getTouch(const int &code) const
{
  switch (code) {
    case KEY_UP:
      return (static_cast<int>(GUI::Events::IKeyboardEvent::KeyboardEvents::TOP));
    case KEY_DOWN:
      return (static_cast<int>(GUI::Events::IKeyboardEvent::KeyboardEvents::BOTTOM));
    case KEY_LEFT:
      return (static_cast<int>(GUI::Events::IKeyboardEvent::KeyboardEvents::LEFT));
    case KEY_RIGHT:
      return (static_cast<int>(GUI::Events::IKeyboardEvent::KeyboardEvents::RIGHT));
    case 10:
      return (static_cast<int>(GUI::Events::IKeyboardEvent::KeyboardEvents::ENTER));
    case 27:
      return (static_cast<int>(GUI::Events::IKeyboardEvent::KeyboardEvents::ESCAPE));
    case KEY_BACKSPACE:
      return (static_cast<int>(GUI::Events::IKeyboardEvent::KeyboardEvents::BACKSPACE));
    case 50:
      return (static_cast<int>(GUI::Events::IKeyboardEvent::KeyboardEvents::NUM2));
    case 51:
      return (static_cast<int>(GUI::Events::IKeyboardEvent::KeyboardEvents::NUM3));
    case 52:
      return (static_cast<int>(GUI::Events::IKeyboardEvent::KeyboardEvents::NUM4));
    case 53:
      return (static_cast<int>(GUI::Events::IKeyboardEvent::KeyboardEvents::NUM5));
    case 56:
      return (static_cast<int>(GUI::Events::IKeyboardEvent::KeyboardEvents::NUM8));
    case 57:
      return (static_cast<int>(GUI::Events::IKeyboardEvent::KeyboardEvents::NUM9));
    case 32:
      return (static_cast<int>(GUI::Events::IKeyboardEvent::KeyboardEvents::SPACE));
    default:
      if (code >= 'a' && code <= 'z')
	return (code);
      return (static_cast<int>(GUI::Events::IKeyboardEvent::KeyboardEvents::NOTHING));
  }
}

GUI::Events::IEvent	*ARCADE::Ncurses::Window::getLastEvent()
{
  GUI::Events::IEvent 	*event;
  int			key;
  int			code;

  key = wgetch(this->_window);
  if (key == ERR)
    return (NULL);
  code = this->getTouch(key);
  event = &createKeyboardEvent(code);
  return (event);
}

/*
** Management
*/

bool		ARCADE::Ncurses::Window::display()
{
  wrefresh(this->_window);
  return (true);
}

bool		ARCADE::Ncurses::Window::Close()
{
  delwin(this->_window);
  endwin();
  return (true);
}

GUI::IWindow	&ARCADE::Ncurses::createWindow(const std::string windowName,
						   int height, int width)
{
  ARCADE::Ncurses::Window	*window = new Window(windowName, height * 10, width * 10);
  return (*window);
}
