NAME = test

SRCS = main.cpp mapTest.cpp vectorTest.cpp stackTest.cpp setTest.cpp

OBJS = $(SRCS:.cpp=.o)

CLANG = clang++ -std=c++98 -g -Wall -Werror -Wextra -fsanitize=address
all: $(NAME)

$(NAME): $(OBJS)
	$(CLANG) $(OBJS) -o $(NAME)

$(OBJS): %.o : %.cpp
	$(CLANG) -c $< -o $@

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -rf $(NAME)

re: fclean all
