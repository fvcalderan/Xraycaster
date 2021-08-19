# folders
INCLUDE = include
BIN		= bin
SRC		= src
OBJ		= obj

# compiler setup
CC		= gcc
CFLAGS	= -Wall -Wextra -O3 -DNDEBUG
LDFLAGS	= -lX11 -lm -lpthread

# files
SRCS    = $(wildcard $(SRC)/*.c)
OBJS	= $(patsubst $(SRC)/%.c, $(OBJ)/%.o, $(SRCS))
TARGET	= $(BIN)/Xraycaster

all:$(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $@ $(LDFLAGS)

$(OBJ)/%.o: $(SRC)/%.c
	$(CC) $(CFLAGS) -c $< -o $@ -I $(INCLUDE)

clean:
	rm -f $(OBJ)/* $(BIN)/*
