CC = gcc
CFLAGS = -Wall -Wextra -I./include
LDFLAGS = -lSDL2
SRC_DIR = src/game-loop
BUILD_DIR = build
GAME_SRCS = $(wildcard $(SRC_DIR)/*.c)
GAME_OBJS = $(GAME_SRCS:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)
MAIN_SRC = main.c
MAIN_OBJ = $(BUILD_DIR)/main.o
TARGET = bitcraft
all: $(BUILD_DIR) $(TARGET)
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)
$(TARGET): $(MAIN_OBJ) $(GAME_OBJS)
	$(CC) $(MAIN_OBJ) $(GAME_OBJS) -o $(TARGET) $(LDFLAGS)
$(BUILD_DIR)/main.o: $(MAIN_SRC)
	$(CC) $(CFLAGS) -c $< -o $@
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@
clean:
	rm -rf $(BUILD_DIR) $(TARGET)
.PHONY: all clean

