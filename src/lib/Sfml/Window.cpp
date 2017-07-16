//
// Window.cpp for cpp_arcade in /home/antoine/Documents/Projets/C++/cpp_arcade
//
// Made by Antoine MOREL
// Login   <antoine.morel@epitech.eu@epitech.net>
//
// Started on  Sun Mar 19 16:02:43 2017 Antoine MOREL
// Last update Thu Mar 23 13:13:20 2017 Antoine MOREL
//

#include		<SFML/Window/Event.hpp>
#include		"Sfml/Window.hpp"
#include		"Sfml/KeyboardEvent.hpp"

/*
** Elementary
*/

ARCADE::Sfml::Window::Window(const std::string windowName, int height,
			     int width) : _window(sf::VideoMode(width, height), windowName)
{
}

ARCADE::Sfml::Window::~Window() {
  this->Close();
}

/*
** Draw
*/

bool			ARCADE::Sfml::Window::drawPixel(const GUI::IPixel &pixel)
{
  sf::RectangleShape		rectangle(sf::Vector2f(20, 20));
  ARCADE::Sfml::Position	position(pixel.getPosition().getY(), pixel.getPosition().getX());

  rectangle.setPosition(position.getY(), position.getX());
  rectangle.setFillColor(this->convertColor(pixel.getColor()));
  this->_window.draw(rectangle);
  return (true);
}

bool			ARCADE::Sfml::Window::drawSquare(const GUI::IPosition &posBegin,
							     const GUI::IPosition &posEnd,
							     const GUI::Color &color)
{
  sf::RectangleShape	rectangle;
  float			height;
  float			width;

  height = posEnd.getY() - posBegin.getY();
  width = posEnd.getX() - posBegin.getX();
  rectangle.setPosition(posBegin.getY(), posBegin.getX());
  rectangle.setSize(sf::Vector2f(height, width));
  rectangle.setFillColor(this->convertColor(color));
  this->_window.draw(rectangle);
  return (true);
}

sf::Color		ARCADE::Sfml::Window::convertColor(const GUI::Color &color) const
{
  switch (color) {
    case GUI::Color::C_BLACK:
      return (sf::Color::Black);
    case GUI::Color::C_BLUE:
      return (sf::Color::Blue);
    case GUI::Color::C_CYAN:
      return (sf::Color::Cyan);
    case GUI::Color::C_GREEN:
      return (sf::Color::Green);
    case GUI::Color::C_MAGENTA:
      return (sf::Color::Magenta);
    case GUI::Color::C_RED:
      return (sf::Color::Red);
    case GUI::Color::C_YELLOW:
      return (sf::Color::Yellow);
    default:
      return (sf::Color::White);
  }
}

bool			ARCADE::Sfml::Window::drawText(const GUI::IText &text)
{
  sf::Text		str;
  sf::Font		font;
  ARCADE::Sfml::Position	position(text.getPosition().getY(), text.getPosition().getX());

  if (!font.loadFromFile("./src/lib/fonts/arcade.ttf"))
    return (false);
  str.setFont(font);
  str.setString(text.getText());
  str.setCharacterSize(12);
  str.setColor(this->convertColor(text.getColorFore()));
  str.setPosition(position.getY(), position.getX());
  this->_window.draw(str);
  return (true);
}

/*
** Event
*/

int			ARCADE::Sfml::Window::getTouch(const sf::Keyboard::Key &code) const
{
  switch (code)
  {
    case sf::Keyboard::Up:
      return (static_cast<int>(GUI::Events::IKeyboardEvent::KeyboardEvents::TOP));
    case sf::Keyboard::Down:
      return (static_cast<int>(GUI::Events::IKeyboardEvent::KeyboardEvents::BOTTOM));
    case sf::Keyboard::Left:
      return (static_cast<int>(GUI::Events::IKeyboardEvent::KeyboardEvents::LEFT));
    case sf::Keyboard::Right:
      return (static_cast<int>(GUI::Events::IKeyboardEvent::KeyboardEvents::RIGHT));
    case sf::Keyboard::Return:
      return (static_cast<int>(GUI::Events::IKeyboardEvent::KeyboardEvents::ENTER));
    case sf::Keyboard::Escape:
      return (static_cast<int>(GUI::Events::IKeyboardEvent::KeyboardEvents::ESCAPE));
    case sf::Keyboard::BackSpace:
      return (static_cast<int>(GUI::Events::IKeyboardEvent::KeyboardEvents::BACKSPACE));
    case sf::Keyboard::Num2:
      return (static_cast<int>(GUI::Events::IKeyboardEvent::KeyboardEvents::NUM2));
    case sf::Keyboard::Num3:
      return (static_cast<int>(GUI::Events::IKeyboardEvent::KeyboardEvents::NUM3));
    case sf::Keyboard::Num4:
      return (static_cast<int>(GUI::Events::IKeyboardEvent::KeyboardEvents::NUM4));
    case sf::Keyboard::Num5:
      return (static_cast<int>(GUI::Events::IKeyboardEvent::KeyboardEvents::NUM5));
    case sf::Keyboard::Num8:
      return (static_cast<int>(GUI::Events::IKeyboardEvent::KeyboardEvents::NUM8));
    case sf::Keyboard::Num9:
      return (static_cast<int>(GUI::Events::IKeyboardEvent::KeyboardEvents::NUM9));
    case sf::Keyboard::Space:
      return (static_cast<int>(GUI::Events::IKeyboardEvent::KeyboardEvents::SPACE));
    default:
      if (code >= sf::Keyboard::A && code <= sf::Keyboard::Z)
	return (code + 'a');
      return (static_cast<int>(GUI::Events::IKeyboardEvent::KeyboardEvents::NOTHING));
  }
}

GUI::Events::IEvent	*ARCADE::Sfml::Window::getLastEvent()
{
  GUI::Events::IEvent 	*event;
  sf::Event		sfEvent;
  int			keyboardEvents;

  event = NULL;
  if (this->_window.pollEvent(sfEvent)) {
    if (sfEvent.type == sfEvent.KeyPressed) {
      keyboardEvents = this->getTouch(sfEvent.key.code);
      if (keyboardEvents == static_cast<int>(GUI::Events::IKeyboardEvent::KeyboardEvents::NOTHING))
	return (NULL);
      event = new ARCADE::Sfml::KeyboardEvent(keyboardEvents);
      return (event);
    }
  }
  return (event);
}

/*
** Management
*/

bool			ARCADE::Sfml::Window::display()
{
  this->_window.display();
  this->_window.clear(sf::Color::Black);
  return (true);
}

bool			ARCADE::Sfml::Window::Close()
{
  this->_window.close();
  return (true);
}

GUI::IWindow		&ARCADE::Sfml::createWindow(const std::string windowName,
							int height, int width)
{
  ARCADE::Sfml::Window	*window = new Window(windowName, height * 20, width * 20);
  return (*window);
}
