TARGET = BlackHole #This is what you get for trying to make the Wormhole

#C compiler
CC = gcc
DEBUG ?=
CC_FLAG = -std=c11 -Wall $(DEBUG)

#Remove command
RM = rm
RM_FLAG = -rf

# Basic directories
LIB = lib
SRC = src
BIN = bin

# Objects
OBJ = main graph

#===================================================================
all: $(addsuffix .o, $(OBJ) )
	$(CC) $(CC_FLAG) $(addprefix $(BIN)/, $(addsuffix .o, $(OBJ) ) ) -o $(TARGET).out -lm

main.o: $(SRC)/main.c graph.o
	$(CC) $(CC_FLAG) -c $(SRC)/main.c -o $(BIN)/main.o

graph.o: $(SRC)/graph.c $(SRC)/graph.h
	$(CC) $(CC_FLAG) -c $(SRC)/graph.c -o $(BIN)/graph.o

clean:
	$(RM) $(RM_FLAG) $(BIN)/*.o
	$(RM) $(RM_FLAG) $(TARGET).out
