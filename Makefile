NAME			=	ircserver

INCS_DIR		=	includes
SRCS_DIR		=	sources
COMPILED_DIR	=	.objs

INCS_FILES		=	$(wildcard $(INCSS_DIR)/*.hpp) $(wildcard $(INCSS_DIR)/*/*.hpp) $(wildcard $(INCSS_DIR)/*/*/*.hpp) $(wildcard $(INCSS_DIR)/*/*/*/*.hpp)
SRCS_FILES		=	$(wildcard $(SRCS_DIR)/*.cpp) $(wildcard $(SRCS_DIR)/*/*.cpp) $(wildcard $(SRCS_DIR)/*/*/*.cpp) $(wildcard $(SRCS_DIR)/*/*/*/*.cpp)

OBJS			=	$(SRCS_FILES:$(SRCS_DIR)/%.cpp=$(COMPILED_DIR)/%.o)

CC				=	clang++
FLAGS			=	-Wall -Wextra -Werror -std=c++98

all: $(NAME)

$(COMPILED_DIR)/%.o:$(SRCS_DIR)/%.cpp	$(INCS_FILES)
	mkdir -p $(@D)
	$(CC) $(FLAGS) -I $(INCS_DIR) -o $@ -c $<

$(NAME): $(INCS_FILES) $(OBJS)
	$(CC) $(FLAGS) -I $(INCS_DIR) -o $(NAME) $(OBJS)

clean:
	rm -rf $(COMPILED_DIR)

fclean: clean
	rm -f $(NAME)

re:	fclean all

.PHONY: all clean fclean re