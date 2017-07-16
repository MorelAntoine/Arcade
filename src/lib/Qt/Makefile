##
## Makefile for arcade in /home/antoine/Documents/Projets/C++/cpp_arcade/src/lib/Qt
## 
## Made by antoine
## Login   <antoine.morel@epitech.eu>
## 
## Started on  Thu Apr  6 14:14:44 2017 antoine
## Last update Fri Apr  7 11:20:03 2017 antoine
##

NAME		=	../../../lib/lib_arcade_qt.so

SRCS		=	Pixel.cpp		\
			Position.cpp		\
			Text.cpp		\
			Window.cpp		\
			KeyboardEvent.cpp	\
			Widget.cpp

OBJS		=	$(SRCS:.cpp=.o)

DEFINES       = -DQT_NO_DEBUG -DQT_GUI_LIB -DQT_CORE_LIB -DQT_SHARED

CPPFLAGS      = -std=c++11 -m64 -pipe -O2 -Wall -W -D_REENTRANT $(DEFINES) -fPIC

CPPFLAGS      += -I../include/ -I/usr/share/qt4/mkspecs/linux-g++-64 -I. -I/usr/include/qt4/QtCore -I/usr/include/qt4/QtGui -I/usr/include/qt4 -I. -I./incs/ -I.

LIBS          =  -lQtGui -lQtCore -lpthread

CC		=	g++

RM		=	rm -rf

all		:	$(NAME)

$(NAME)		:	$(OBJS)
			echo ${PWD}
			$(CC) -shared -o $(NAME) $(OBJS) -L./lib/ -Wl,-Bdynamic $(LIBS)

clean		:
			$(RM) $(OBJS)

fclean		:	clean
			$(RM) $(NAME)

re		:	fclean all
