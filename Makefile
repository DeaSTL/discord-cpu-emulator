CC = g++
CFLAGS = -Wall -g -std=c++20
LIBS = -ldpp

BUILD_DIR = build
SRC_DIR = src
INCLUDE_DIR = /usr/local/include
LIB_DIR = /usr/local/lib


export LD_LIBRARY_PATH=/usr/local/lib

build:
	$(CC) $(SRC_DIR)/*.cpp -I $(INCLUDE_DIR) $(CFLAGS) -L$(LIB_DIR) $(LIBS) -o $(BUILD_DIR)/main.o

run:
	make build
	$(BUILD_DIR)/main.o

clean:
	rm -rf $(BUILD_DIR)/*.o

.PHONY: build run clean
