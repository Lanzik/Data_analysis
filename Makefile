CC = g++
CCFLAGS = -std=c++11

BUILD_DIR = build

all: Goodreads.out

Goodreads.out: $(BUILD_DIR)/main.o $(BUILD_DIR)/Goodreads.o $(BUILD_DIR)/Author.o $(BUILD_DIR)/Book.o $(BUILD_DIR)/User.o $(BUILD_DIR)/Review.o
	$(CC) $(BUILD_DIR)/main.o $(BUILD_DIR)/Goodreads.o $(BUILD_DIR)/Author.o $(BUILD_DIR)/Book.o $(BUILD_DIR)/User.o $(BUILD_DIR)/Review.o -o Goodreads.out

$(BUILD_DIR)/main.o: main.cpp Goodreads.hpp Author.hpp Book.hpp User.hpp Review.hpp
	$(CC) -c main.cpp -o $(BUILD_DIR)/main.o

$(BUILD_DIR)/Goodreads.o: Goodreads.cpp Goodreads.hpp
	$(CC) -c Goodreads.cpp -o $(BUILD_DIR)/Goodreads.o

$(BUILD_DIR)/Author.o: Author.cpp Author.hpp
	$(CC) -c Author.cpp -o $(BUILD_DIR)/Author.o

$(BUILD_DIR)/Book.o: Book.cpp Book.hpp
	$(CC) -c Book.cpp -o $(BUILD_DIR)/Book.o

$(BUILD_DIR)/User.o: User.cpp User.hpp
	$(CC) -c User.cpp -o $(BUILD_DIR)/User.o

$(BUILD_DIR)/Review.o: Review.cpp Review.hpp User.hpp
	$(CC) -c Review.cpp -o $(BUILD_DIR)/Review.o


.PHONY: clean
clean:
	rm -rf build/ utrip.out && mkdir -p build
