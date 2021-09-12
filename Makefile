NAME = vector

SRCS = main.cpp
OBJ 	=	$(SRCS:.cpp=.o)
CC = clang++

CFLAGS  = -Wall -Wextra -Werror
all:	$(NAME)

$(NAME):	$(OBJ) vector.hpp iterator.hpp
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

.cpp.o:
	$(CC) $(CFLAGS) -c $< -o $(<:.cpp=.o)

check:
	clang++ check.cpp

clean:
	rm -rf $(OBJ)

fclean:	clean
	rm -rf $(NAME) a.out

re:	fclean $(NAME)

.PHONY:	all clean fclean re
