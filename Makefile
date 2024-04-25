TARGET_EXEC := stdi

BUILD_DIR := ./target
SRC_DIRS := ./src

SRCS := $(shell find $(SRC_DIRS) -name '*.c')

OBJS := $(SRCS:%.c=$(BUILD_DIR)/%.o)

CC = gcc
CFLAGS = -g3 -Wall -Wextra -Werror -pedantic

$(TARGET_EXEC): $(OBJS)
	$(CC) $(OBJS) -o $@

$(BUILD_DIR)/%.o: %.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: clean
clean:
	rm -r $(BUILD_DIR)