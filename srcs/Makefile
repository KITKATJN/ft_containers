# Regular Colors
Black='\033[0;30m'        # Black
Red='\033[0;31m'          # Red
Green=\033[0;32m        # Green
Yellow='\033[0;33m'       # Yellow
Blue='\033[0;34m'         # Blue
Purple='\033[0;35m'       # Purple
Cyan='\033[0;36m'         # Cyan
White='\033[0;37m'        # White

# Bold
BBlack='\033[1;30m'       # Black
BRed='\033[1;31m'         # Red
BGreen=\033[1;32m       # Green
BYellow='\033[1;33m'      # Yellow
BBlue='\033[1;34m'        # Blue
BPurple='\033[1;35m'      # Purple
BCyan='\033[1;36m'        # Cyan
BWhite='\033[1;37m'       # White

RESET =\033[0m

name	= ft_containers
srcdir	= srcs
objdir	= objs
incdir	= utils

vector_n	= vector
vector_s	= $(srcdir)/vector_main.cpp $(srcdir)/vector_test.cpp $(srcdir)/utils.cpp
vector_h	= vector.hpp
vector_o	= $(vector_s:$(srcdir)/%.cpp=$(objdir)/%.o)
vector_d	= $(vector_o:%.o=%.d)

map_n	= map
map_s	= $(srcdir)/map_main.cpp $(srcdir)/map_extend_test.cpp $(srcdir)/map_test.cpp $(srcdir)/utils.cpp
map_h	= map.hpp
map_o	= $(map_s:$(srcdir)/%.cpp=$(objdir)/%.o)
map_d	= $(map_o:%.o=%.d)

set_n	= set
set_s	= $(srcdir)/set_main.cpp $(srcdir)/set_test.cpp $(srcdir)/utils.cpp
set_h	= set.hpp
set_o	= $(set_s:$(srcdir)/%.cpp=$(objdir)/%.o)
set_d	= $(set_o:%.o=%.d)

stack_n	= stack
stack_s	= $(srcdir)/stack_main.cpp  $(srcdir)/utils.cpp $(srcdir)/stack_test.cpp
stack_h	= stack.hpp
stack_o	= $(stack_s:$(srcdir)/%.cpp=$(objdir)/%.o)
stack_d	= $(stack_o:%.o=%.d)

sanit 	= -fsanitize=address
linker	= clang++
flags	= -Wall -Wextra -Werror -g -std=c++98 -O2
sanit	= -fsanitize=address
std		= -std=c++98


all:	$(name)

test:	$(name)
	@echo "${BGreen}\n"
	@echo "======================VECTOR======================\n"
	@echo "${RESET}"
	@./$(vector_n)
	@echo "${BGreen}\n"
	@echo "======================STACK======================\n"
	@echo "${RESET}"
	@./$(stack_n)
	@echo "${BGreen}\n"
	@echo "======================SET======================\n"
	@echo "${RESET}"
	@./$(set_n)
	@echo "${BGreen}\n"
	@echo "======================MAP======================\n"
	@echo "${RESET}"
	@./$(map_n)

$(name):	$(vector_n) $(set_n) $(map_n) $(stack_n)

# VECTOR
$(vector_n):	$(vector_o)
		@$(linker) $(flags) $^ -o $(vector_n)
		@echo "Compiled${Green}["$@"]${RESET}\n"

-include $(vector_d)
$(objdir)/%.o:	$(srcdir)/%.cpp Makefile
		@mkdir -p $(objdir)
		@$(linker) $(flags) -MMD -c $< -o $@

# MAP
$(map_n):	$(map_o)
		@$(linker) $(flags) $^ -o $(map_n)
		@echo "Compiled${Green}["$@"]${RESET}\n"

-include $(map_d)
$(objdir)/%.o:	$(srcdir)/%.cpp Makefile
		@mkdir -p $(objdir)
		@$(linker) $(flags) -MMD -c $< -o $@

# set
$(set_n):	$(set_o)
		@$(linker) $(flags) $^ -o $(set_n)
		@echo "Compiled${Green}["$@"]${RESET}\n"

-include $(set_d)
$(objdir)/%.o:	$(srcdir)/%.cpp Makefile
		@mkdir -p $(objdir)
		@$(linker) $(flags) -MMD -c $< -o $@

# stack
$(stack_n):	$(stack_o)
		@$(linker) $(flags) $^ -o $(stack_n)
		@echo "Compiled${Green}["$@"]${RESET}\n"

-include $(stack_d)
$(objdir)/%.o:	$(srcdir)/%.cpp Makefile
		@mkdir -p $(objdir)
		@$(linker) $(flags) -MMD -c $< -o $@

clean:
		rm -rf $(objdir)

fclean:	clean
		rm -f $(vector_n) $(map_n) $(set_n) $(stack_n)

re:		fclean all

# leaks:
# 	@leaks --atExit -- ./$(name)
