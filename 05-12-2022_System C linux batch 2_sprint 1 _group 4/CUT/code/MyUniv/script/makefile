CC = gcc
INC = ./include
SRC = src
OBJ = obj
BIN = ./bin

CFLAGS = -c -g -Wall

LDFLAGS = -o
IFLAGS = -I $(INC)


all: MyUniv

MyUniv: $(OBJ)/main.o $(OBJ)/user.o $(OBJ)/admin.o $(OBJ)/courses.o $(OBJ)/chapters.o $(OBJ)/link.o $(OBJ)/common.o $(OBJ)/bookmark.o $(OBJ)/application.o
	$(CC) $(LDFLAGS) $(BIN)/MyUniv $(OBJ)/main.o $(OBJ)/user.o $(OBJ)/admin.o $(OBJ)/courses.o $(OBJ)/chapters.o $(OBJ)/link.o $(OBJ)/common.o $(OBJ)/bookmark.o $(OBJ)/application.o

$(OBJ)/main.o: $(SRC)/main.c
	$(CC) $(CFLAGS) $(SRC)/main.c $(IFLAGS)
	mv main.o $(OBJ)/

$(OBJ)/user.o: $(SRC)/user.c
	$(CC) $(CFLAGS) $(SRC)/user.c $(IFLAGS)
	mv user.o $(OBJ)/

$(OBJ)/admin.o: $(SRC)/admin.c
	$(CC) $(CFLAGS) $(SRC)/admin.c $(IFLAGS)
	mv admin.o $(OBJ)/

$(OBJ)/courses.o: $(SRC)/courses.c
	$(CC) $(CFLAGS) $(SRC)/courses.c $(IFLAGS)
	mv courses.o $(OBJ)/

$(OBJ)/chapters.o: $(SRC)/chapters.c
	$(CC) $(CFLAGS) $(SRC)/chapters.c $(IFLAGS)
	mv chapters.o $(OBJ)/

$(OBJ)/link.o: $(SRC)/link.c
	$(CC) $(CFLAGS) $(SRC)/link.c $(IFLAGS)
	mv link.o $(OBJ)/


$(OBJ)/common.o: $(SRC)/common.c
	$(CC) $(CFLAGS) $(SRC)/common.c $(IFLAGS)
	mv common.o $(OBJ)/

$(OBJ)/bookmark.o: $(SRC)/bookmark.c
	$(CC) $(CFLAGS) $(SRC)/bookmark.c $(IFLAGS)
	mv bookmark.o $(OBJ)/
	
$(OBJ)/application.o: $(SRC)/application.c
	$(CC) $(CFLAGS) $(SRC)/application.c $(IFLAGS)
	mv application.o $(OBJ)/

clean:
	rm -f *.out *.o
	rm -f $(OBJ)/*.o
	rm -f $(BIN)/*
	@echo "Cleaning Done!"

