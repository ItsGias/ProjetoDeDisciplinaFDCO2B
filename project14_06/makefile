SRC=./*.c
INCLUDE=-I./
BIN=./main

all:
	gcc $(SRC) -g -lm -lcurl $(INCLUDE) -o $(BIN)
	
run:
	$(BIN)

clean:
	rm $(BIN)
	
valgrind:
	valgrind --tool=memcheck --leak-check=full --track-origins=yes --show-leak-kinds=all --show-reachable=yes ./$(BIN)