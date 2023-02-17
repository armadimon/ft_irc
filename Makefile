NAME = ircserv

CXX = c++

FLAGS = -g -Wall -Wextra -Werror -std=c++98

SRC =	main.cpp \
		srcs/Utils.cpp \
		srcs/Client.cpp \
		srcs/Server.cpp \
		srcs/Channel.cpp \
		# srcs/Command.cpp \

CMD_SRC =	srcs/command/Join.cpp \
			srcs/command/Nick.cpp \
			srcs/command/Pass.cpp \
			srcs/command/PrivMsg.cpp \
			srcs/command/User.cpp \
			srcs/command/Kick.cpp \

OBJ = $(SRC:.cpp=.o)
CMD_OBJ = $(CMD_SRC:.cpp=.o)

.cpp.o :
	$(CXX) $(FLAGS) -c $< -o $@

all: $(NAME)

$(NAME): $(OBJ) $(CMD_OBJ)
	$(CXX) $(FLAGS) $(OBJ) $(CMD_OBJ) -o $(NAME)

clean:
	rm -rf $(OBJ) $(CMD_OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY : all clean fclean re