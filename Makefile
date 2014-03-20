CC=/usr/bin/g++
SOURCE=main.o board.o game.o node.o
OBJECTS=$(SOURCE:.cpp=.o)
EXECUTABLE=checkgame

all: $(SOURCE) $(EXECUTABLE) clean

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(OBJECTS) -o $@

.o:
	$(CC) -c $< -o $@

run:
	./checkgame

clean:
	rm -rf *.o