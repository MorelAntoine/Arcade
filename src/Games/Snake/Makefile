##
## Makefile for snake in /home/dylan/Documents/TEK2/cpp_arcade/src/Games/Snake
## 
## Made by Dylan Deu
## Login   <dylan.deu@epitech.eu>
## 
## Started on  Thu Mar 23 12:50:16 2017 Dylan Deu
## Last update Wed Apr  5 18:57:54 2017 Dylan Deu
##

CC		=	g++

RM		=	rm -f

NAME		=	../../../games/lib_arcade_snake.so

SRCS		=	srcs/Snake.cpp		\
			srcs/Exception.cpp	\
			srcs/play.cpp

OBJS		=	$(SRCS:.cpp=.o)

CPPFLAGS	=	-std=c++11 -fPIC -Wall -W -Wextra

CPPFLAGS	+=	-I./incs/ -I../incs/ -I../ -I../../Arcade/incs/ -I../../lib/include/

all:			$(NAME)

$(NAME):		$(OBJS)
			$(CC) -o $(NAME) -shared $(OBJS)

clean:
			$(RM) $(OBJS)

fclean:			clean
			$(RM) $(NAME)

re:			fclean all
