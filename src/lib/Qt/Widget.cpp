//
// Widget.cpp for cpp_arcade in /home/antoine/Documents/Projets/C++/cpp_arcade
//
// Made by Antoine MOREL
// Login   <antoine.morel@epitech.eu@epitech.net>
//
// Started on  Fri Apr 07 11:13:45 2017 Antoine MOREL
// Last update Sat Apr 08 15:02:25 2017 Antoine MOREL
//

#include	"AcQt/Widget.hpp"

/*
** Elementary
*/

ARCADE::AcQt::Widget::Widget(int height, int width)
  : _keyPress(0), _vPixel(), _vText()
{
  this->setFixedSize(width, height);
}

ARCADE::AcQt::Widget::~Widget()
{
}

/*
** Getters & setters
*/

int		ARCADE::AcQt::Widget::getKeyPress() const
{
  return (this->_keyPress);
}

std::vector<ARCADE::AcQt::Pixel*>	ARCADE::AcQt::Widget::getVPixel()
{
  return (this->_vPixel);
}

std::vector<ARCADE::AcQt::Text*>	ARCADE::AcQt::Widget::getVText()
{
  return (this->_vText);
}

void		ARCADE::AcQt::Widget::setKeyPress(int value)
{
  this->_keyPress = value;
}

/*
** Management
*/

Qt::GlobalColor	ARCADE::AcQt::Widget::convertColor(const GUI::Color &color) const
{
  if (color == GUI::Color::C_BLACK)
    return (Qt::black);
  if (color == GUI::Color::C_BLUE)
    return (Qt::blue);
  if (color == GUI::Color::C_CYAN)
    return (Qt::cyan);
  if (color == GUI::Color::C_GREEN)
    return (Qt::green);
  if (color == GUI::Color::C_MAGENTA)
    return (Qt::magenta);
  if (color == GUI::Color::C_RED)
    return (Qt::red);
  if (color == GUI::Color::C_YELLOW)
    return (Qt::yellow);
  return (Qt::white);
}

void		ARCADE::AcQt::Widget::paintEvent(QPaintEvent *event)
{
  std::vector<Pixel*>::iterator	itP;
  std::vector<Text*>::iterator	itT;
  QPainter			painter(this);
  QRect				rect(0, 0, 0, 0);
  QString			str;

  static_cast<void>(event);
  itP = this->_vPixel.begin();
  while (itP != this->_vPixel.end())
  {
    rect.setX((*itP)->getPosition().getX());
    rect.setY((*itP)->getPosition().getY());
    rect.setWidth(20);
    rect.setHeight(20);
    painter.setPen(this->convertColor((*itP)->getColor()));
    painter.fillRect(rect, this->convertColor((*itP)->getColor()));
    painter.drawRect(rect);
    itP++;
  }
  itT = this->_vText.begin();
  while (itT != this->_vText.end())
  {
    painter.setPen(this->convertColor((*itT)->getColorFore()));
    painter.setBrush(this->convertColor((*itT)->getColorBack()));
    str = str.fromStdString((*itT)->getText());
    painter.drawText((*itT)->getPosition().getX(), (*itT)->getPosition().getY(), str);
    itT++;
  }
  painter.end();
}

void		ARCADE::AcQt::Widget::keyPressEvent(QKeyEvent *event)
{
  static_cast<void>(event);
  this->_keyPress = event->key();
}

void		ARCADE::AcQt::Widget::keyReleaseEvent(QKeyEvent *event)
{
  static_cast<void>(event);
  this->_keyPress = 0;
}

void		ARCADE::AcQt::Widget::cleanContainers()
{
  size_t	idx(0);

  while (idx < this->_vPixel.size())
  {
    delete this->_vPixel[idx];
    idx++;
  }
  idx = 0;
  while (idx < this->_vText.size())
  {
    delete this->_vText[idx];
    idx++;
  }
  this->_vPixel.clear();
  this->_vText.clear();
}
