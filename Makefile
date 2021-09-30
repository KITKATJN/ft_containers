NAME = test

SRCS = main.cpp ft_containers/tests/mapTest.cpp ft_containers/tests/vectorTest.cpp ft_containers/tests/stackTest.cpp #testContainers/setTest.cpp

OBJS = $(SRCS:.cpp=.o)

CLANG = clang++ -g -Wall -Werror -Wextra
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
