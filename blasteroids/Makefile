# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -g
LDFLAGS = $(shell pkg-config --libs allegro-5 allegro_font-5 allegro_ttf-5 allegro_primitives-5 allegro_main-5)
INCLUDES = -I.

# Source files
SRC_DIR = .
SRCS = $(wildcard $(SRC_DIR)/*.c)
OBJS = $(SRCS:.c=.o)

# Target executable
TARGET = blasteroids

# Default target
all: $(TARGET)

# Link object files to create the executable
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ $^ $(LDFLAGS)

# Compile .c files to .o files
%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# Clean build artifacts
clean:
	rm -f $(OBJS) $(TARGET)

# Install dependencies (for macOS)
install-deps:
	brew install allegro

# Run the game
run: $(TARGET)
	./$(TARGET)

# Debug with gdb
debug: $(TARGET)
	gdb ./$(TARGET)

# Phony targets (don't represent files)
.PHONY: all clean install-deps run debug