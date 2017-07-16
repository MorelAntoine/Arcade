##
## Makefile for centipede in /home/dylan/Documents/TEK2/cpp_arcade/src/Games/Centipede
## 
## Made by Dylan Deu
## Login   <dylan.deu@epitech.eu>
## 
## Started on  Fri Mar 31 15:09:11 2017 Dylan Deu
## Last update Wed Apr  5 18:57:39 2017 Dylan Deu
##

NAME		=	../../../games/lib_arcade_centipede.so

CC		=	g++

RM		=	rm -f

SRCS		=	srcs/Exception.cpp		\
			srcs/Centipede.cpp		\
			srcs/Obstacle.cpp		\
			srcs/play.cpp

OBJS		=	$(SRCS:.cpp=.o)

CPPFLAGS	=	-std=c++11 -fPIC -Wall -W -Wextra

CPPFLAGS	+=	-I./incs -I../incs -I../ -I../../Arcade/incs -I../../lib/include/

all:			$(NAME)

$(NAME):		$(OBJS)
			$(CC) -o $(NAME) -shared $(OBJS)

clean:
			$(RM) $(OBJS)

fclean:			clean
			$(RM) $(NAME)

re:			fclean all
