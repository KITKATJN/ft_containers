NAME = test

SRCS = main.cpp ft_containers/mapTest.cpp #testContainers/setTest.cpp #testContainers/vectorTest.cpp testContainers/stackTest.cpp

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
