##
## Makefile for arcade in /home/antoine/Documents/c++/cpp_arcade
## 
## Made by antoine
## Login   <antoine.morel@epitech.eu>
## 
## Started on  Thu Mar 16 13:36:50 2017 antoine
## Last update Thu Apr  6 13:20:30 2017 Dylan Deu
##

LIB			=	no

all			:
ifeq ($(LIB),yes)
	make -C ./src/lib
endif

				make -C ./src/Arcade
				make -C ./src/Games/Snake
				make -C ./src/Games/Centipede

clean			:
				make -C ./src/Arcade clean
				make -C ./src/lib clean
				make -C ./src/Games/Snake clean
				make -C ./src/Games/Centipede clean

fclean			:	clean
				make -C ./src/Arcade fclean
				make -C ./src/lib fclean
				make -C ./src/Games/Snake fclean
				make -C ./src/Games/Centipede fclean

re			:	fclean all
