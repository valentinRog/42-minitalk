SERVER = server

CLIENT = client

SERVER_SRC = 	server.c

CLIENT_SRC = 	client.c

UTILS_SRC =	 	utils/put.c\
				utils/atoi.c

CC = gcc

CFLAGS = -Wall -Wextra -Werror

SERVER_OBJ = $(SERVER_SRC:.c=.o)

CLIENT_OBJ = $(CLIENT_SRC:.c=.o)

UTILS_OBJ = $(UTILS_SRC:.c=.o)

all: $(SERVER) $(CLIENT)

$(SERVER): $(SERVER_OBJ) $(UTILS_SRC)
	$(CC) $(CFLAGS) -I. $(SERVER_OBJ) $(UTILS_SRC) -o $@

$(CLIENT): $(CLIENT_OBJ) $(UTILS_SRC)
	$(CC) $(CFLAGS) -I. $(CLIENT_OBJ) $(UTILS_SRC) -o $@

clean:
	$(RM) $(SERVER_OBJ) $(CLIENT_OBJ)

fclean: clean
	$(RM) $(SERVER) $(CLIENT)

re: fclean all