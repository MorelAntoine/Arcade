##
## Makefile for arcade in /home/antoine/Documents/Projets/C++/cpp_arcade/lib
## 
## Made by antoine
## Login   <antoine.morel@epitech.eu>
## 
## Started on  Sun Mar 19 16:57:43 2017 antoine
## Last update Sat Apr  8 12:33:33 2017 antoine
##

all			:
				make -C ./Sfml/
				make -C ./Ncurses/
				make -C ./Qt/

clean			:
				make -C ./Sfml/ clean
				make -C ./Ncurses/ clean
				make -C ./Qt/ clean

fclean			:	clean
				make -C ./Sfml/ fclean
				make -C ./Ncurses/ fclean
				make -C ./Qt/ fclean

re			:	fclean all
