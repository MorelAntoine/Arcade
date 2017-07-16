##
## Makefile for cpp_arcade in /home/dylan/Documents/TEK2/cpp_arcade/src/Arcade
## 
## Made by Dylan Deu
## Login   <dylan.deu@epitech.eu>
## 
## Started on  Sat Mar 18 17:57:11 2017 Dylan Deu
## Last update Tue Mar 21 15:20:17 2017 Dylan Deu
##

CC	=	g++

NAME	=	../../arcade

SRCS	=	srcs/Arcade.cpp			\
		srcs/Exception.cpp		\
		srcs/main.cpp

OBJS	=	$(SRCS:.cpp=.o)

RM	=	rm -f

CPPFLAGS	=	-Wall -Wextra -Werror -std=c++11

CPPFLAGS	+=	-ldl

CPPFLAGS	+=	-I ./incs/

CPPFLAGS	+=	-I ../lib/include

CPPFLAGS	+=	-I ../Games/incs

CPPFLAGS	+=	-I ../Games

all:		$(OBJS)
		$(CC) -o $(NAME) $(OBJS) $(CPPFLAGS)

clean:
		$(RM) $(OBJS)

fclean:		clean
		$(RM) $(NAME)

re:		fclean all
