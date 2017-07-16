//
// Window.cpp for cpp_arcade in /home/antoine/Documents/Projets/C++/cpp_arcade
//
// Made by Antoine MOREL
// Login   <antoine.morel@epitech.eu@epitech.net>
//
// Started on  Sun Mar 19 16:02:43 2017 Antoine MOREL
// Last update Sat Apr 08 15:02:45 2017 Antoine MOREL
//

#include		<sstream>
#include		<QtGui/QPainter>
#include		"AcQt/Window.hpp"
#include		"AcQt/KeyboardEvent.hpp"

/*
** Elementary
*/

ARCADE::AcQt::Window::Window(const std::string windowName, int height,
			     int width)
{
  int			argc(1);
  char			*argv[1];

  this->_windowName = new char[windowName.size()];
  this->_windowName = const_cast<char *>(windowName.c_str());
  argv[0] = this->_windowName;
  this->_app = new QApplication(argc, argv);
  QTimer::singleShot(1, this->_app, SLOT(quit()));
  this->_app->exec();
  this->_window = new Widget(height, width);
  this->_window->show();
}

ARCADE::AcQt::Window::~Window() {
  this->Close();
}

/*
** Draw
*/

bool			ARCADE::AcQt::Window::drawPixel(const GUI::IPixel &pixel)
{
  Position		pos(pixel.getPosition().getY(), pixel.getPosition().getX());
  Pixel			*pix = new Pixel(pos, pixel.getColor());

  this->_window->_vPixel.push_back(pix);
  return (true);
}

bool			ARCADE::AcQt::Window::drawSquare(const GUI::IPosition &posBegin,
							     const GUI::IPosition &posEnd,
							     const GUI::Color &color)
{
  Position		pos(posBegin.getY(), posBegin.getX());
  Pixel			pixel(pos, color);
  unsigned int		tmp(posBegin.getX());

  while (pos.getY() < posEnd.getY())
  {
    pos.setX(tmp);
    while (pos.getX() < posEnd.getX())
    {
      pixel.setPosition(pos);
      this->drawPixel(pixel);
      pos.setX(pos.getX() + 20);
    }
    pos.setY(pos.getY() + 20);
  }
  return (true);
}

bool			ARCADE::AcQt::Window::drawText(const GUI::IText &text)
{
  Text			*txt;
  std::istringstream	iss(text.getText());
  std::string		string;
  Position		position(text.getPosition().getY() + 20, text.getPosition().getX());

  while (getline(iss, string, '\n'))
  {
    txt = new Text(string, text.getColorFore(), text.getColorBack(), position);
    this->_window->_vText.push_back(txt);
    position.setY(position.getY() + 20);
  }
  return (true);
}

/*
** Event
*/

int			ARCADE::AcQt::Window::getTouch() const
{
  switch (this->_window->getKeyPress())
  {
    case Qt::Key_Up:
      return (static_cast<int>(GUI::Events::IKeyboardEvent::KeyboardEvents::TOP));
    case Qt::Key_Down:
      return (static_cast<int>(GUI::Events::IKeyboardEvent::KeyboardEvents::BOTTOM));
    case Qt::Key_Left:
      return (static_cast<int>(GUI::Events::IKeyboardEvent::KeyboardEvents::LEFT));
    case Qt::Key_Right:
      return (static_cast<int>(GUI::Events::IKeyboardEvent::KeyboardEvents::RIGHT));
    case Qt::Key_Return:
      return (static_cast<int>(GUI::Events::IKeyboardEvent::KeyboardEvents::ENTER));
    case Qt::Key_Escape:
      return (static_cast<int>(GUI::Events::IKeyboardEvent::KeyboardEvents::ESCAPE));
    case Qt::Key_Backspace:
      return (static_cast<int>(GUI::Events::IKeyboardEvent::KeyboardEvents::BACKSPACE));
    case Qt::Key_2:
      return (static_cast<int>(GUI::Events::IKeyboardEvent::KeyboardEvents::NUM2));
    case Qt::Key_3:
      return (static_cast<int>(GUI::Events::IKeyboardEvent::KeyboardEvents::NUM3));
    case Qt::Key_4:
      return (static_cast<int>(GUI::Events::IKeyboardEvent::KeyboardEvents::NUM4));
    case Qt::Key_5:
      return (static_cast<int>(GUI::Events::IKeyboardEvent::KeyboardEvents::NUM5));
    case Qt::Key_8:
      return (static_cast<int>(GUI::Events::IKeyboardEvent::KeyboardEvents::NUM8));
    case Qt::Key_9:
      return (static_cast<int>(GUI::Events::IKeyboardEvent::KeyboardEvents::NUM9));
    case Qt::Key_Space:
      return (static_cast<int>(GUI::Events::IKeyboardEvent::KeyboardEvents::SPACE));
    default:
      if (this->_window->getKeyPress() >= Qt::Key_A &&
	  this->_window->getKeyPress() <= Qt::Key_Z)
	return (this->_window->getKeyPress() - Qt::Key_A + 'a');
      return (static_cast<int>(GUI::Events::IKeyboardEvent::KeyboardEvents::NOTHING));
  }
}

GUI::Events::IEvent	*ARCADE::AcQt::Window::getLastEvent()
{
  GUI::Events::IEvent 	*event;

  if (this->getTouch() != static_cast<int>(GUI::Events::IKeyboardEvent::KeyboardEvents::NOTHING)) {
    event = new ARCADE::AcQt::KeyboardEvent(this->getTouch());
    this->_window->setKeyPress(-1);
    return (event);
  }
  this->_window->setKeyPress(-1);
  return (NULL);
}

/*
** Management
*/

bool			ARCADE::AcQt::Window::display()
{
  this->_app->processEvents();
  this->_window->repaint();
  this->_window->cleanContainers();
  return (true);
}

bool			ARCADE::AcQt::Window::Close()
{
  this->_window->close();
  return (true);
}

GUI::IWindow		&ARCADE::AcQt::createWindow(const std::string windowName,
							int height, int width)
{
  ARCADE::AcQt::Window	*window = new Window(windowName, height * 20, width * 20);
  return (*window);
}
