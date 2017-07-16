##
## Makefile for arcade in /home/antoine/Documents/Projets/C++/cpp_arcade/lib
## 
## Made by antoine
## Login   <antoine.morel@epitech.eu>
## 
## Started on  Sun Mar 19 16:57:43 2017 antoine
## Last update Wed Apr  5 17:59:34 2017 Dylan Deu
##

NAME		=	../../../lib/lib_arcade_ncurses.so

SRCS		=	Pixel.cpp		\
			Position.cpp	\
			Text.cpp		\
			Window.cpp		\
			KeyboardEvent.cpp

OBJS		=	$(SRCS:.cpp=.o)

CPPFLAGS	=	-std=c++11 -Wall -W -Wextra -fPIC

CPPFLAGS	+=	-I../include/

CC		=	g++

RM		=	rm -rf

all		:	$(NAME)

$(NAME)		:	$(OBJS)
			$(CC) -shared -o $(NAME) $(OBJS) -L./lib/ -Wl,-Bdynamic -lncurses
clean		:
			$(RM) $(OBJS)

fclean		:	clean
			$(RM) $(NAME)

re		:	fclean all
