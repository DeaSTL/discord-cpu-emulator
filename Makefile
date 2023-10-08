CC = g++
CFLAGS = -Wall -g
LIBS = -ldpp

BUILD_DIR = build
SRC_DIR = src
INCLUDE_DIR = /usr/local/include



build:
	$(CC) $(SRC_DIR)/*.cpp -I $(INCLUDE_DIR) $(CFLAGS) $(LIBS) -o $(BUILD_DIR)/main.o

run:
	make build
	$(BUILD_DIR)/main.o

clean:
	rm -rf $(BUILD_DIR)/*.o

.PHONY: build run clean
