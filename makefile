# folders
INCLUDE = include
BIN		= bin
SRC		= src
OBJ		= obj

# compiler setup
CC		= gcc
CFLAGS	= -Wall -Wextra -O3 -DNDEBUG -std=c11
LDFLAGS	= -lX11 -lm -lpthread

# files
SRCS    = $(wildcard $(SRC)/*.c)
OBJS	= $(patsubst $(SRC)/%.c, $(OBJ)/%.o, $(SRCS))
TARGET	= $(BIN)/Xraycaster

all:$(TARGET)

$(TARGET): $(OBJS)
	mkdir -p $(BIN)
	$(CC) $(CFLAGS) $(OBJS) -o $@ $(LDFLAGS)

$(OBJ)/%.o: $(SRC)/%.c
	mkdir -p $(OBJ)
	$(CC) $(CFLAGS) -c $< -o $@ -I $(INCLUDE)

clean:
	rm -f $(OBJ)/* $(BIN)/*
	rm -rf bin obj

memcheck:
	valgrind --leak-check=full \
			 --show-leak-kinds=all \
			 --track-origins=yes \
			 --verbose \
			 --log-file=memcheck.txt \
			 ./${TARGET}
	less memcheck.txt
	rm memcheck.txt
