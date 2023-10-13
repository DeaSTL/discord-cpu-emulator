CC = g++
CFLAGS = -Wall -Wextra -Wpedantic -g -std=c++20
LIBS = -ldpp

BUILD_DIR = build
SRC_DIR = src
TEST_DIR = test
ASSEMBLER_DIR = assembler
INCLUDE_DIR = /usr/local/include
LIB_DIR = /usr/local/lib

BUILD_MODULES = $(wildcard $(SRC_DIR)/*.cpp) $(wildcard $(SRC_DIR)/$(ASSEMBLER_DIR)/*.cpp)


export LD_LIBRARY_PATH=/usr/local/lib

build:
	$(CC) $(BUILD_MODULES) -I $(INCLUDE_DIR) $(CFLAGS) -L$(LIB_DIR) $(LIBS) -o $(BUILD_DIR)/main.o

run:
	make build
	$(BUILD_DIR)/main.o

test:
	$(CC) $(filter-out $(SRC_DIR)/main.cpp, $(wildcard $(SRC_DIR)/*.cpp)) $(TEST_DIR)/*.cpp -I $(INCLUDE_DIR) $(CFLAGS) -L$(LIB_DIR) $(LIBS) -o $(BUILD_DIR)/test.o
	$(BUILD_DIR)/test.o

clean:
	rm -rf $(BUILD_DIR)/*.o

.PHONY: build run clean test
