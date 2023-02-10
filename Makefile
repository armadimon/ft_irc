NAME = ircserv

CXX = c++

FLAGS = -Wall -Wextra -Werror -std=c++98

SRC =	main.cpp \
		srcs/Client.cpp \
		srcs/Server.cpp

OBJ = $(SRC:.cpp=.o)

.cpp.o :
	$(CXX) $(FLAGS) -c $< -o $@

all: $(NAME)

$(NAME): $(OBJ)
	$(CXX) $(FLAGS) $(OBJ) -o $(NAME)

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY : all clean fclean re