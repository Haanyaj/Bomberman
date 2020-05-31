##
## EPITECH PROJECT, 2018
## Makefile
## File description:
## bonus
##

NAME	=		bomberman

SRC_DIR	=		src
OBJ_DIR	=		obj
CC	    =		g++

CPPFLAGS =		-I include/ -ldl

SRC		=		$(wildcard $(SRC_DIR)/*.cpp)

OBJ		=		$(SRC:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)

all:		$(OBJ)	
	@$(CC) -o $(NAME) $(OBJ) $(CPPFLAGS)

$(OBJ_DIR)/%.o:	$(SRC_DIR)/%.cpp
				@printf "[\033[0;32mcompiled\033[0m] % 29s\n" $< | tr ' ' '.'
				@$(CC) $(CPPFLAGS) -c -o $@ $<

clean:
				@rm -f $(OBJ)

fclean:			clean

re:				fclean all

