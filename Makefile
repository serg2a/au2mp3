CC := gcc
CFLAGS := -I $(INCLUDE_DIR) -Wall -O2

TARGET_EXEC := au2mp3 
BUILD_DIR := build
SRC_DIRS := src
INCLUDE_DIR := include
BIN_DIR := ~/bin/

#SRCS := $(shell find . -name *.cpp -or -name *.c)

SRCS := $(wildcard $(SRC_DIST)/*.c)
OBJS := $(SRCS:%=$(BUILD_DIR)/%.o)

$(BUILD_DIR)/$(TARGET_EXEC): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $@

$(BUILD_DIR)/%.c.o: %.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

install: $(BUILD_DIR)/$(TARGET_EXEC)
	cp $< $(BIN_DIR)

uninstall: $(BIN_DIR)/$(TARGET_EXEC)
	rm -r $<

.PHONY: clean
clean:
	rm -r $(BUILD_DIR)
